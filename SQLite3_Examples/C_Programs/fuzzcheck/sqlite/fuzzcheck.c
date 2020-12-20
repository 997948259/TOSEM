
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "sqlite3.h"

/*
** Files in the virtual file system.
*/
typedef struct VFile VFile;
struct VFile {
  char *zFilename;        /* Filename.  NULL for delete-on-close. From malloc() */
  int sz;                 /* Size of the file in bytes */
  int nRef;               /* Number of references to this file */
  unsigned char *a;       /* Content of the file.  From malloc() */
};
typedef struct VHandle VHandle;
struct VHandle {
  sqlite3_file base;      /* Base class.  Must be first */
  VFile *pVFile;          /* The underlying file */
};

/*
** The value of a database file template, or of an SQL script
*/
typedef struct Blob Blob;
struct Blob {
  Blob *pNext;            /* Next in a list */
  int id;                 /* Id of this Blob */
  int seq;                /* Sequence number */
  int sz;                 /* Size of this Blob in bytes */
  unsigned char a[1];     /* Blob content.  Extra space allocated as needed. */
};

/*
** All global variables are gathered into the "g" singleton.
*/

  const char *zArgv0;              /* Name of program */
  VFile aFile[10];            /* The virtual filesystem */
  int nDb;                         /* Number of template databases */
  Blob *pFirstDb;                  /* Content of first template database */
  int nSql;                        /* Number of SQL scripts */
  Blob *pFirstSql;                 /* First SQL script */
  unsigned int uRandom;            /* Seed for the SQLite PRNG */
  char zTestName[100];             /* Name of current test */



/*
** This an SQL progress handler.  After an SQL statement has run for
** many steps, we want to interrupt it.  This guards against infinite
** loops from recursive common table expressions.
**
** *pVdbeLimitFlag is true if the --limit-vdbe command-line option is used.
** In that case, hitting the progress handler is a fatal error.
*/
static int progressHandler(void *pVdbeLimitFlag){
  //if( *(int*)pVdbeLimitFlag ) fatalError("too many VDBE cycles");
  return 1;
}

/*
** Reallocate memory.  Show and error and quit if unable.
*/
static void *safe_realloc(void *pOld, int szNew){
  void *pNew = realloc(pOld, szNew<=0 ? 1 : szNew);
  //if( pNew==0 ) fatalError("unable to realloc for %d bytes", szNew);
  return pNew;
}

/*
** Initialize the virtual file system.
*/
static void formatVfs(void){
  int i;
  for(i=0; i<10; i++){
    aFile[i].sz = -1;
    aFile[i].zFilename = 0;
    aFile[i].a = 0;
    aFile[i].nRef = 0;
  }
}


/*
** Erase all information in the virtual file system.
*/
static void reformatVfs(void){
  int i;
  for(i=0; i<10; i++){
    if( aFile[i].sz<0 ) continue;
    if( aFile[i].zFilename ){
      free(aFile[i].zFilename);
      aFile[i].zFilename = 0;
    }
    aFile[i].sz = -1;
    free(aFile[i].a);
    aFile[i].a = 0;
    aFile[i].nRef = 0;
  }
}

/*
** Find a VFile by name
*/
static VFile *findVFile(const char *zName){
  int i;
  if( zName==0 ) return 0;
  for(i=0; i<10; i++){
    if( aFile[i].zFilename==0 ) continue;   
    if( strcmp(aFile[i].zFilename, zName)==0 ) return &aFile[i];
  }
  return 0;
}

/*
** Find a VFile by name.  Create it if it does not already exist and
** initialize it to the size and content given.
**
** Return NULL only if the filesystem is full.
*/
static VFile *createVFile_fuzzcheck(const char *zName, int sz, unsigned char *pData){
  VFile *pNew = findVFile(zName);
  int i;
  if( pNew ) return pNew;
  for(i=0; i<10 && aFile[i].sz>=0; i++){}
  if( i>=10 ) return 0;
  pNew = &aFile[i];
  if( zName ){
    int nName = (int)strlen(zName)+1;
    pNew->zFilename = safe_realloc(0, nName);
    memcpy(pNew->zFilename, zName, nName);
  }else{
    pNew->zFilename = 0;
  }
  pNew->nRef = 0;
  pNew->sz = sz;
  pNew->a = safe_realloc(0, sz);
  if( sz>0 ) memcpy(pNew->a, pData, sz);
  return pNew;
}


/*
** Implementation of the "readfile(X)" SQL function.  The entire content
** of the file named X is read and returned as a BLOB.  NULL is returned
** if the file does not exist or is unreadable.
*/
void readfileFunc(
	sqlite3_context *context,
	int argc,
	sqlite3_value **argv
	){
	const char *zName;
	FILE *in;
	long nIn;
	void *pBuf;

	zName = (const char*)sqlite3_value_text(argv[0]);
	if (zName == 0) return;
	in = fopen(zName, "rb");
	if (in == 0) return;
	fseek(in, 0, SEEK_END);
	nIn = ftell(in);
	rewind(in);
	pBuf = sqlite3_malloc(nIn);
	if (pBuf && 1 == fread(pBuf, nIn, 1, in)){
		sqlite3_result_text(context, (const char*)pBuf, nIn, sqlite3_free);
	}
	else{
		sqlite3_free(pBuf);
	}
	fclose(in);
}

/*
** Implementation of the "writefile(X,Y)" SQL function.  The argument Y
** is written into file X.  The number of bytes written is returned.  Or
** NULL is returned if something goes wrong, such as being unable to open
** file X for writing.
*/
static void writefileFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  FILE *out;
  const char *z;
  int rc;
  const char *zFile;

  (void)argc;
  zFile = (const char*)sqlite3_value_text(argv[0]);
  if( zFile==0 ) return;
  out = fopen(zFile, "wb");
  if( out==0 ) return;
  z = (const char*)sqlite3_value_blob(argv[1]);
  if( z==0 ){
    rc = 0;
  }else{
    rc = fwrite(z, 1, sqlite3_value_bytes(argv[1]), out);
  }
  fclose(out);
  sqlite3_result_int64(context, rc);
}


/*
** Load a list of Blob objects from the database
*/
sqlite3_stmt *stmt;
sqlite3 *db;
static void blobListLoadFromDb(
  const char *zSql,        /* Query used to extract the blobs */
  int onlyId,              /* Only load where id is this value */
  int *pN,                 /* OUT: Write number of blobs loaded here */
  Blob **ppList            /* OUT: Write the head of the blob list here */
){
  Blob head;
  Blob *p;
  
  int n = 0;
  int rc;
  char *z2;

  if( onlyId>0 ){
    z2 = sqlite3_mprintf("%s WHERE rowid=%d", zSql, onlyId);
  }else{
    z2 = sqlite3_mprintf("%s", zSql);
  }
  rc = sqlite3_prepare_v2(db, z2, -1, &stmt, 0);
  sqlite3_free(z2);
  head.pNext = 0;
  p = &head;
  while( 100==sqlite3_step(stmt) ){
    int sz = sqlite3_column_bytes(stmt, 1);
	Blob *pNew = safe_realloc(0, sizeof(*pNew) + sz);

    pNew->id = sqlite3_column_int(stmt, 0);
    pNew->sz = sz;
    pNew->seq = n++;
    pNew->pNext = 0;
    memcpy(pNew->a, sqlite3_column_blob(stmt,1), sz);
    pNew->a[sz] = 0;
    p->pNext = pNew;
    p = pNew;
  }
  sqlite3_finalize(stmt);
  *pN = n;
  *ppList = head.pNext;
}

/*
** Free a list of Blob objects
*/
static void blobListFree(Blob *p){
  Blob *pNext;
  while( p ){
    pNext = p->pNext;
    free(p);
    p = pNext;
  }
}


/* Return the current wall-clock time */
static int timeOfDay(void){
  static sqlite3_vfs *clockVfs = 0;
  int t;
  if( clockVfs==0 ) clockVfs = sqlite3_vfs_find(0);
  if( clockVfs->iVersion>=1 && clockVfs->xCurrentTimeInt64!=0 ){
    clockVfs->xCurrentTimeInt64(clockVfs, &t);
  }else{
    double r;
    clockVfs->xCurrentTime(clockVfs, &r);
    t = (int)(r*86400000.0);
  }
  return t;
}

/* Methods for the VHandle object
*/
static int inmemClose(sqlite3_file *pFile){
  VHandle *p = (VHandle*)pFile;
  VFile *pVFile = p->pVFile;
  pVFile->nRef--;
  if( pVFile->nRef==0 && pVFile->zFilename==0 ){
    pVFile->sz = -1;
    free(pVFile->a);
    pVFile->a = 0;
  }
  return SQLITE_OK;
}
static int inmemRead(
  sqlite3_file *pFile,   /* Read from this open file */
  void *pData,           /* Store content in this buffer */
  int iAmt,              /* Bytes of content */
  int iOfst    /* Start reading here */
){
  VHandle *pHandle = (VHandle*)pFile;
  VFile *pVFile = pHandle->pVFile;
  if( iOfst<0 || iOfst>=pVFile->sz ){
    memset(pData, 0, iAmt);
    return SQLITE_IOERR_SHORT_READ;
  }
  if( iOfst+iAmt>pVFile->sz ){
    memset(pData, 0, iAmt);
    iAmt = (int)(pVFile->sz - iOfst);
    memcpy(pData, pVFile->a, iAmt);
    return SQLITE_IOERR_SHORT_READ;
  }
  memcpy(pData, pVFile->a + iOfst, iAmt);
  return SQLITE_OK;
}
static int inmemWrite(
  sqlite3_file *pFile,   /* Write to this file */
  const void *pData,     /* Content to write */
  int iAmt,              /* bytes to write */
  int iOfst    /* Start writing here */
){
  VHandle *pHandle = (VHandle*)pFile;
  VFile *pVFile = pHandle->pVFile;
  if( iOfst+iAmt > pVFile->sz ){
    if( iOfst+iAmt >= 10000000 ){
      return SQLITE_FULL;
    }
    pVFile->a = safe_realloc(pVFile->a, (int)(iOfst+iAmt));
    if( iOfst > pVFile->sz ){
      memset(pVFile->a + pVFile->sz, 0, (int)(iOfst - pVFile->sz));
    }
    pVFile->sz = (int)(iOfst + iAmt);
  }
  memcpy(pVFile->a + iOfst, pData, iAmt);
  return SQLITE_OK;
}
static int inmemTruncate(sqlite3_file *pFile, int iSize){
  VHandle *pHandle = (VHandle*)pFile;
  VFile *pVFile = pHandle->pVFile;
  if( pVFile->sz>iSize && iSize>=0 ) pVFile->sz = (int)iSize;
  return SQLITE_OK;
}
static int inmemSync(sqlite3_file *pFile, int flags){
  return SQLITE_OK;
}
static int inmemFileSize(sqlite3_file *pFile, int *pSize){
  *pSize = ((VHandle*)pFile)->pVFile->sz;
  return SQLITE_OK;
}
static int inmemLock(sqlite3_file *pFile, int type){
  return SQLITE_OK;
}
static int inmemUnlock(sqlite3_file *pFile, int type){
  return SQLITE_OK;
}
static int inmemCheckReservedLock(sqlite3_file *pFile, int *pOut){
  *pOut = 0;
  return SQLITE_OK;
}
static int inmemFileControl(sqlite3_file *pFile, int op, void *pArg){
  return SQLITE_NOTFOUND;
}
static int inmemSectorSize(sqlite3_file *pFile){
  return 512;
}
static int inmemDeviceCharacteristics(sqlite3_file *pFile){
  return
      SQLITE_IOCAP_SAFE_APPEND |
      SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN |
      SQLITE_IOCAP_POWERSAFE_OVERWRITE;
}


/* Method table for VHandle
*/
static sqlite3_io_methods VHandleMethods = {
  /* iVersion  */    1,
  /* xClose    */    inmemClose,
  /* xRead     */    inmemRead,
  /* xWrite    */    inmemWrite,
  /* xTruncate */    inmemTruncate,
  /* xSync     */    inmemSync,
  /* xFileSize */    inmemFileSize,
  /* xLock     */    inmemLock,
  /* xUnlock   */    inmemUnlock,
  /* xCheck... */    inmemCheckReservedLock,
  /* xFileCtrl */    inmemFileControl,
  /* xSectorSz */    inmemSectorSize,
  /* xDevchar  */    inmemDeviceCharacteristics,
  /* xShmMap   */    0,
  /* xShmLock  */    0,
  /* xShmBarrier */  0,
  /* xShmUnmap */    0,
  /* xFetch    */    0,
  /* xUnfetch  */    0
};

/*
** Open a new file in the inmem VFS.  All files are anonymous and are
** delete-on-close.
*/
static int inmemOpen(
  sqlite3_vfs *pVfs,
  const char *zFilename,
  sqlite3_file *pFile,
  int openFlags,
  int *pOutFlags
){
  VFile *pVFile = createVFile_fuzzcheck(zFilename, 0, (unsigned char*)"");
  VHandle *pHandle = (VHandle*)pFile;
  if( pVFile==0 ){
    return SQLITE_FULL;
  }
  pHandle->pVFile = pVFile;
  pVFile->nRef++;
  pFile->pMethods = &VHandleMethods;
  if( pOutFlags ) *pOutFlags = openFlags;
  return SQLITE_OK;
}

/*
** Delete a file by name
*/
static int inmemDelete(
  sqlite3_vfs *pVfs,
  const char *zFilename,
  int syncdir
){
  VFile *pVFile = findVFile(zFilename);
  if( pVFile==0 ) return SQLITE_OK;
  if( pVFile->nRef==0 ){
    free(pVFile->zFilename);
    pVFile->zFilename = 0;
    pVFile->sz = -1;
    free(pVFile->a);
    pVFile->a = 0;
    return SQLITE_OK;
  }
  return SQLITE_IOERR_DELETE;
}

/* Check for the existance of a file
*/
static int inmemAccess(
  sqlite3_vfs *pVfs,
  const char *zFilename,
  int flags,
  int *pResOut
){
  VFile *pVFile = findVFile(zFilename);
  *pResOut =  pVFile!=0;
  return SQLITE_OK;
}

/* Get the canonical pathname for a file
*/
static int inmemFullPathname(
  sqlite3_vfs *pVfs,
  const char *zFilename,
  int nOut,
  char *zOut
){
  sqlite3_snprintf(nOut, zOut, "%s", zFilename);
  return SQLITE_OK;
}

/* Always use the same random see, for repeatability.
*/
static int inmemRandomness(sqlite3_vfs *NotUsed, int nBuf, char *zBuf){
  memset(zBuf, 0, nBuf);
  memcpy(zBuf, &uRandom, nBuf<sizeof(uRandom) ? nBuf : sizeof(uRandom));
  return nBuf;
}

/*
** Register the VFS that reads from the aFile[] set of files.
*/
static void inmemVfsRegister(int makeDefault){
  static sqlite3_vfs inmemVfs;
  sqlite3_vfs *pDefault = sqlite3_vfs_find(0);
  inmemVfs.iVersion = 3;
  inmemVfs.szOsFile = sizeof(VHandle);
  inmemVfs.mxPathname = 200;
  inmemVfs.zName = "inmem";
  inmemVfs.xOpen = inmemOpen;
  inmemVfs.xDelete = inmemDelete;
  inmemVfs.xAccess = inmemAccess;
  inmemVfs.xFullPathname = inmemFullPathname;
  inmemVfs.xRandomness = inmemRandomness;
  inmemVfs.xSleep = pDefault->xSleep;
  inmemVfs.xCurrentTimeInt64 = pDefault->xCurrentTimeInt64;
  sqlite3_vfs_register(&inmemVfs, makeDefault);
};

/*
** Allowed values for the runFlags parameter to runSql()
*/
#define SQL_TRACE  0x0001     /* Print each SQL statement as it is prepared */
#define SQL_OUTPUT 0x0002     /* Show the SQL output */

/*
** Run multiple commands of SQL.  Similar to sqlite3_exec(), but does not
** stop if an error is encountered.
*/
sqlite3_stmt *pstmt;
static void runSql( const char *zSql, unsigned  runFlags){
  const char *zMore;
  

  while( zSql && zSql[0] ){
    zMore = 0;
    pstmt = 0;
    sqlite3_prepare_v2(db, zSql, -1, &pstmt, &zMore);
    if( zMore==zSql ) break;
    if( runFlags & SQL_TRACE ){
      const char *z = zSql;
      int n;
	  while (z<zMore && isspace((unsigned char)(z[0]))) z++;
      n = (int)(zMore - z);
	  while (n>0 && isspace((unsigned char)(z[n - 1]))) n--;
      if( n==0 ) break;
      if( pstmt==0 ){
        printf("TRACE: %.*s (error: %s)\n", n, z, sqlite3_errmsg(db));
      }else{
        printf("TRACE: %.*s\n", n, z);
      }
    }
    zSql = zMore;
    if( pstmt ){
      if( (runFlags & SQL_OUTPUT)==0 ){
        while( SQLITE_ROW==sqlite3_step(pstmt) ){}
      }else{
        int nCol = -1;
        while( SQLITE_ROW==sqlite3_step(pstmt) ){
          int i;
          if( nCol<0 ){
            nCol = sqlite3_column_count(pstmt);
          }else if( nCol>0 ){
            printf("--------------------------------------------\n");
          }
          for(i=0; i<nCol; i++){
            int eType = sqlite3_column_type(pstmt,i);
            printf("%s = ", sqlite3_column_name(pstmt,i));
            switch( eType ){
              case SQLITE_NULL: {
                printf("NULL\n");
                break;
              }
              case SQLITE_INTEGER: {
                printf("INT %s\n", sqlite3_column_text(pstmt,i));
                break;
              }
              case SQLITE_FLOAT: {
                printf("FLOAT %s\n", sqlite3_column_text(pstmt,i));
                break;
              }
              case SQLITE_TEXT: {
                printf("TEXT [%s]\n", sqlite3_column_text(pstmt,i));
                break;
              }
              case SQLITE_BLOB: {
                printf("BLOB (%d bytes)\n", sqlite3_column_bytes(pstmt,i));
                break;
              }
            }
          }
        }
      }         
      sqlite3_finalize(pstmt);
    }
  }
}

/*
** Rebuild the database file.
**
**    (1)  Remove duplicate entries
**    (2)  Put all entries in order
**    (3)  Vacuum
*/
static void rebuild_database(){
  int rc;
  rc = sqlite3_exec(db, 
     "BEGIN;\n"
     "CREATE TEMP TABLE dbx AS SELECT DISTINCT dbcontent FROM db;\n"
     "DELETE FROM db;\n"
     "INSERT INTO db(dbid, dbcontent) SELECT NULL, dbcontent FROM dbx ORDER BY 2;\n"
     "DROP TABLE dbx;\n"
     "CREATE TEMP TABLE sx AS SELECT DISTINCT sqltext FROM xsql;\n"
     "DELETE FROM xsql;\n"
     "INSERT INTO xsql(sqlid,sqltext) SELECT NULL, sqltext FROM sx ORDER BY 2;\n"
     "DROP TABLE sx;\n"
     "COMMIT;\n"
     "PRAGMA page_size=1024;\n"
     "VACUUM;\n", 0, 0, 0);
}

/*
** Return the value of a hexadecimal digit.  Return -1 if the input
** is not a hex digit.
*/
static int hexDigitValue(char c){
  if( c>='0' && c<='9' ) return c - '0';
  if( c>='a' && c<='f' ) return c - 'a' + 10;
  if( c>='A' && c<='F' ) return c - 'A' + 10;
  return -1;
}

/*
** Interpret zArg as an integer value, possibly with suffixes.
*/
static int integerValue(const char *zArg){
  int v = 0;
  static const struct 
  { 
	  char *zSuffix; int iMult; 
  } aMult[] = {
    { "KiB", 1024 },
    { "MiB", 1024*1024 },
    { "GiB", 1024*1024*1024 },
    { "KB",  1000 },
    { "MB",  1000000 },
    { "GB",  1000000000 },
    { "K",   1000 },
    { "M",   1000000 },
    { "G",   1000000000 },
  };
  int i;
  int isNeg = 0;
  if( zArg[0]=='-' ){
    isNeg = 1;
    zArg++;
  }else if( zArg[0]=='+' ){
    zArg++;
  }
  if( zArg[0]=='0' && zArg[1]=='x' ){
    int x;
    zArg += 2;
    while( (x = hexDigitValue(zArg[0]))>=0 ){
      v = (v<<4) + x;
      zArg++;
    }
  }else{
	  while (isdigit((unsigned char)(zArg[0]))){
      v = v*10 + zArg[0] - '0';
      zArg++;
    }
  }
  for(i=0; i<sizeof(aMult)/sizeof(aMult[0]); i++){
    if( sqlite3_stricmp(aMult[i].zSuffix, zArg)==0 ){
      v *= aMult[i].iMult;
      break;
    }
  }
  return (int)(isNeg? -v : v);
}

/*
** Print sketchy documentation for this utility program
*/
static void showHelp(void){
  printf("Usage: %s [options] SOURCE-DB ?ARGS...?\n", zArgv0);
  printf(
"Read databases and SQL scripts from SOURCE-DB and execute each script against\n"
"each database, checking for crashes and memory leaks.\n"
"Options:\n"
"  --cell-size-check    Set the PRAGMA cell_size_check=ON\n"
"  --dbid N             Use only the database where dbid=N\n"
"  --export-db DIR      Write databases to files(s) in DIR. Works with --dbid\n"
"  --export-sql DIR     Write SQL to file(s) in DIR. Also works with --sqlid\n"
"  --help               Show this help text\n"
"  -q|--quiet           Reduced output\n"
"  --limit-mem N        Limit memory used by test SQLite instance to N bytes\n"
"  --limit-vdbe         Panic if any test runs for more than 100,000 cycles\n"
"  --load-sql ARGS...   Load SQL scripts fro files into SOURCE-DB\n"
"  --load-db ARGS...    Load template databases from files into SOURCE_DB\n"
"  -m TEXT              Add a description to the database\n"
"  --native-vfs         Use the native VFS for initially empty database files\n"
"  --native-malloc      Turn off MEMSYS3/5 and Lookaside\n"
"  --oss-fuzz           Enable OSS-FUZZ testing\n"
"  --prng-seed N        Seed value for the PRGN inside of SQLite\n"
"  --rebuild            Rebuild and vacuum the database file\n"
"  --result-trace       Show the results of each SQL command\n"
"  --sqlid N            Use only SQL where sqlid=N\n"
"  --timeout N          Abort if any single test needs more than N seconds\n"
"  -v|--verbose         Increased output.  Repeat for more output.\n"
  );
}
int prevAmt = -1;
int main(int argc, char **argv){
  int iBegin;        /* Start time of this program */
  int quietFlag = 0;           /* True if --quiet or -q */
  int verboseFlag = 0;         /* True if --verbose or -v */
  char *zInsSql = 0;           /* SQL statement for --load-db or --load-sql */
  int iFirstInsArg = 0;        /* First argv[] to use for --load-db or --load-sql */
  sqlite3_stmt *pstmt;         /* A prepared statement */
  int rc;                      /* Result code from SQLite interface calls */
  Blob *pSql;                  /* For looping over SQL scripts */
  Blob *pDb;                   /* For looping over template databases */
  int i;                       /* Loop index for the argv[] loop */
  int onlySqlid = -1;          /* --sqlid */
  int onlyDbid = -1;           /* --dbid */
  int nativeFlag = 0;          /* --native-vfs */
  int rebuildFlag = 0;         /* --rebuild */
  int vdbeLimitFlag = 0;       /* --limit-vdbe */
  int timeoutTest = 0;         /* undocumented --timeout-test flag */
  int runFlags = 0;            /* Flags sent to runSql() */
  char *zMsg = 0;              /* Add this message */
  int nSrcDb = 0;              /* Number of source databases */
  char **azSrcDb = 0;          /* Array of source database names */
  int iSrcDb;                  /* Loop over all source databases */
  int nTest = 0;               /* Total number of tests performed */
  char *zDbName = "";          /* Appreviated name of a source database */
  const char *zFailCode = 0;   /* Value of the TEST_FAILURE environment variable */
  int cellSzCkFlag = 0;        /* --cell-size-check */
  int sqlFuzz = 0;             /* True for SQL fuzz testing. False for DB fuzz */
  int iTimeout = 120;          /* Default 120-second timeout */
  int nMem = 0;                /* Memory limit */
  int nMemThisDb = 0;          /* Memory limit set by the CONFIG table */
  char *zExpDb = 0;            /* Write Databases to files in this directory */
  char *zExpSql = 0;           /* Write SQL to files in this directory */
  void *pHeap = 0;             /* Heap for use by SQLite */
  int ossFuzz = 0;             /* enable OSS-FUZZ testing */
  int ossFuzzThisDb = 0;       /* ossFuzz value for this particular database */
  int nativeMalloc = 0;        /* Turn off MEMSYS3/5 and lookaside if true */


  iBegin = 0;
  zArgv0 = argv[0];
  zFailCode = getenv("TEST_FAILURE");

  inmemVfsRegister(1);
  
	nSrcDb++;
	azSrcDb = safe_realloc(azSrcDb, nSrcDb*sizeof(azSrcDb[0]));
	azSrcDb[nSrcDb - 1]="fuzzdata4.db";
	printf("main_azSrcDb[main_nSrcDb-1]:%s\n", azSrcDb[nSrcDb - 1]);
	//azSrcDb[nSrcDb-1] = argv[1];
    

  /* Process each source database separately */
  for(iSrcDb=0; iSrcDb<nSrcDb; iSrcDb++){
    rc = sqlite3_open_v2(azSrcDb[iSrcDb], &db,
                         2, "win32");
    rc = sqlite3_exec(db,
       "CREATE TABLE IF NOT EXISTS db(\n"
       "  dbid INTEGER PRIMARY KEY, -- database id\n"
       "  dbcontent BLOB            -- database disk file image\n"
       ");\n"
       "CREATE TABLE IF NOT EXISTS xsql(\n"
       "  sqlid INTEGER PRIMARY KEY,   -- SQL script id\n"
       "  sqltext TEXT                 -- Text of SQL statements to run\n"
       ");"
       "CREATE TABLE IF NOT EXISTS readme(\n"
       "  msg TEXT -- Human-readable description of this file\n"
       ");", 0, 0, 0);
    if( zMsg ){
      char *zSql;
      zSql = sqlite3_mprintf(
               "DELETE FROM readme; INSERT INTO readme(msg) VALUES(%Q)", zMsg);
      rc = sqlite3_exec(db, zSql, 0, 0, 0);
      sqlite3_free(zSql);
    }
    ossFuzzThisDb = ossFuzz;

    /* If the CONFIG(name,value) table exists, read db-specific settings
    ** from that table */
    if( sqlite3_table_column_metadata(db,0,"config",0,0,0,0,0,0)==SQLITE_OK ){
      rc = sqlite3_prepare_v2(db, "SELECT name, value FROM config", -1, &pstmt, 0);
      while( 100==sqlite3_step(pstmt) ){
        const char *zName = (const char *)sqlite3_column_text(pstmt,0);
        if( zName==0 ) continue;
        if( strcmp(zName, "oss-fuzz")==0 ){
          ossFuzzThisDb = sqlite3_column_int(pstmt,1);
          if( verboseFlag ) printf("Config: oss-fuzz=%d\n", ossFuzzThisDb);
        }
      }
      sqlite3_finalize(pstmt);
    }

    if( zInsSql ){
      sqlite3_create_function(db, "readfile", 1, 1, 0,
                              readfileFunc, 0, 0);
      rc = sqlite3_prepare_v2(db, zInsSql, -1, &pstmt, 0);
      
      rc = sqlite3_exec(db, "BEGIN", 0, 0, 0);
     
      for(i=iFirstInsArg; i<argc; i++){
        sqlite3_bind_text(pstmt, 1, argv[i], -1, 0);
        sqlite3_step(pstmt);
        rc = sqlite3_reset(pstmt);
        
      }
      sqlite3_finalize(pstmt);
      rc = sqlite3_exec(db, "COMMIT", 0, 0, 0);
      
      rebuild_database();
      sqlite3_close(db);
      return 0;
    }
    rc = sqlite3_exec(db, "PRAGMA query_only=1;", 0, 0, 0);
    
    if( zExpDb!=0 || zExpSql!=0 ){
      sqlite3_create_function(db, "writefile", 2, SQLITE_UTF8, 0,
                              writefileFunc, 0, 0);
      if( zExpDb!=0 ){
        const char *zExDb = 
          "SELECT writefile(printf('%s/db%06d.db',?1,dbid),dbcontent),"
          "       dbid, printf('%s/db%06d.db',?1,dbid), length(dbcontent)"
          "  FROM db WHERE ?2<0 OR dbid=?2;";
        rc = sqlite3_prepare_v2(db, zExDb, -1, &pstmt, 0);
        
        sqlite3_bind_text64(pstmt, 1, zExpDb, strlen(zExpDb),
                            0, 1);
        sqlite3_bind_int(pstmt, 2, onlyDbid);
        while( sqlite3_step(pstmt)==100 ){
          printf("write db-%d (%d bytes) into %s\n",
             sqlite3_column_int(pstmt,1),
             sqlite3_column_int(pstmt,3),
             sqlite3_column_text(pstmt,2));
        }
        sqlite3_finalize(pstmt);
      }
      if( zExpSql!=0 ){
        const char *zExSql = 
          "SELECT writefile(printf('%s/sql%06d.txt',?1,sqlid),sqltext),"
          "       sqlid, printf('%s/sql%06d.txt',?1,sqlid), length(sqltext)"
          "  FROM xsql WHERE ?2<0 OR sqlid=?2;";
        rc = sqlite3_prepare_v2(db, zExSql, -1, &pstmt, 0);
        
        sqlite3_bind_text64(pstmt, 1, zExpSql, strlen(zExpSql),
                            0, 1);
        sqlite3_bind_int(pstmt, 2, onlySqlid);
        while( sqlite3_step(pstmt)==100 ){
          printf("write sql-%d (%d bytes) into %s\n",
             sqlite3_column_int(pstmt,1),
             sqlite3_column_int(pstmt,3),
             sqlite3_column_text(pstmt,2));
        }
        sqlite3_finalize(pstmt);
      }
      sqlite3_close(db);
      return 0;
    }
  
    /* Load all SQL script content and all initial database images from the
    ** source db
    */
    blobListLoadFromDb( "SELECT sqlid, sqltext FROM xsql", onlySqlid,
                           &nSql, &pFirstSql);
    
    blobListLoadFromDb("SELECT dbid, dbcontent FROM db", onlyDbid,
                       &nDb, &pFirstDb);
    if( nDb==0 ){
      pFirstDb = safe_realloc(0, sizeof(Blob));
      memset(pFirstDb, 0, sizeof(Blob));
      pFirstDb->id = 1;
      pFirstDb->seq = 0;
      nDb = 1;
      sqlFuzz = 1;
    }
  
    /* Print the description, if there is one */
    if( !quietFlag ){
      zDbName = azSrcDb[iSrcDb];
      i = (int)strlen(zDbName) - 1;
      while( i>0 && zDbName[i-1]!='/' && zDbName[i-1]!='\\' ){ i--; }
      zDbName += i;
      sqlite3_prepare_v2(db, "SELECT msg FROM readme", -1, &pstmt, 0);
      if( pstmt && sqlite3_step(pstmt)==100 ){
        printf("%s: %s\n", zDbName, sqlite3_column_text(pstmt,0));
      }
      sqlite3_finalize(pstmt);
    }

    /* Rebuild the database, if requested */
    if( rebuildFlag ){
      if( !quietFlag ){
        printf("%s: rebuilding... ", zDbName);
        fflush(stdout);
      }
      rebuild_database();
      if( !quietFlag ) printf("done\n");
    }
  
    /* Close the source database.  Verify that no SQLite memory allocations are
    ** outstanding.
    */
    sqlite3_close(db);
   

    /* Limit available memory, if requested */
    sqlite3_shutdown();
    if( nMemThisDb>0 && !nativeMalloc ){
      pHeap = realloc(pHeap, nMemThisDb);
     
      sqlite3_config(8, pHeap, nMemThisDb, 128);
    }

    /* Disable lookaside with the --native-malloc option */
    if( nativeMalloc ){
      sqlite3_config(13, 0, 0);
    }
  
    /* Reset the in-memory virtual filesystem */
    formatVfs();
    
    /* Run a test using each SQL script against each database.
    */
    if( !verboseFlag && !quietFlag ) printf("%s:", zDbName);
    for(pSql=pFirstSql; pSql; pSql=pSql->pNext){
      for(pDb=pFirstDb; pDb; pDb=pDb->pNext){
        int openFlags;
        const char *zVfs = "inmem";
        sqlite3_snprintf(sizeof(zTestName), zTestName, "sqlid=%d,dbid=%d",
                         pSql->id, pDb->id);
        if( verboseFlag ){
          printf("%s\n", zTestName);
          fflush(stdout);
        }else if( !quietFlag ){
          
          int idx = pSql->seq*nDb + pDb->id - 1;
          int amt = idx*10/(nDb*nSql);
          if( amt!=prevAmt ){
            printf(" %d%%", amt*10);
            fflush(stdout);
            prevAmt = amt;
          }
        }
        createVFile_fuzzcheck("main.db", pDb->sz, pDb->a);
        sqlite3_randomness(0,0);
       
          openFlags = 4 | 2;
          if( nativeFlag && pDb->sz==0 ){
			  openFlags |= 0x00000080;
            zVfs = 0;
          }
          rc = sqlite3_open_v2("main.db", &db, openFlags, zVfs);
          
          sqlite3_limit(db, 0, 100000000);
          sqlite3_limit(db, 8, 50);
          if( cellSzCkFlag ) runSql( "PRAGMA cell_size_check=ON", runFlags);
          if( sqlFuzz || vdbeLimitFlag ){
            sqlite3_progress_handler(db, 100000, progressHandler, &vdbeLimitFlag);
          }
          do{
            runSql( (char*)pSql->a, runFlags);
          }while( timeoutTest );
          sqlite3_exec(db, "PRAGMA temp_store_directory=''", 0, 0, 0);
          sqlite3_close(db);
      

        reformatVfs();
        nTest++;
        zTestName[0] = 0;

        /* Simulate an error if the TEST_FAILURE environment variable is "5".
        ** This is used to verify that automated test script really do spot
        ** errors that occur in this test program.
        */
        if( zFailCode ){
           if( zFailCode[0]!=0 ){
            /* If TEST_FAILURE is something other than 5, just exit the test
            ** early */
            printf("\nExit early due to TEST_FAILURE being set\n");
            iSrcDb = nSrcDb-1;
          }
        }
      }
    }
    if( !quietFlag && !verboseFlag ){
      printf(" 100%% - %d tests\n", nDb*nSql);
    }
  
    /* Clean up at the end of processing a single source database
    */
    blobListFree(pFirstSql);
    blobListFree(pFirstDb);
    reformatVfs();
 
  } /* End loop over all source databases */

  if( !quietFlag ){
    int iElapse=0;
    printf("fuzzcheck: 0 errors out of %d tests in %d.%03d seconds\n"
           "SQLite %s %s\n",
           nTest, (int)(iElapse/1000), (int)(iElapse%1000),
           sqlite3_libversion(), sqlite3_sourceid());
  }
  free(azSrcDb);
  free(pHeap);
  return 0;
}
