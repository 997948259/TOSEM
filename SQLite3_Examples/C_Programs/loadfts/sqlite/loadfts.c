/*
** 2014-07-28
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
**
** This file implements a utility program that will load many disk
** files (all files under a given directory) into a FTS table.  This is
** used for performance testing of FTS3, FTS4, and FTS5.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include "sqlite3.h"

/*
** Implementation of the "readtext(X)" SQL function.  The entire content
** of the file named X is read and returned as a TEXT value. It is assumed
** the file contains UTF-8 text. NULL is returned if the file does not 
** exist or is unreadable.
*/
sqlite3 *db;
sqlite3 *db1;
static void readfileFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  const char *zName;
  FILE *in;
  long nIn;
  void *pBuf;

  zName = (const char*)sqlite3_value_text(argv[0]);
  if( zName==0 ) return;
  in = fopen(zName, "rb");
  if( in==0 ) return;
  fseek(in, 0, SEEK_END);
  nIn = ftell(in);
  rewind(in);
  pBuf = sqlite3_malloc( nIn );
  if( pBuf && 1==fread(pBuf, nIn, 1, in) ){
    sqlite3_result_text(context, pBuf, nIn, sqlite3_free);
  }else{
    sqlite3_free(pBuf);
  }
  fclose(in);
}

/*
** Print usage text for this program and exit.
*/
static void showHelp(const char *zArgv0){
  printf("\n"
"Usage: %s SWITCHES... DB\n"
"\n"
"  This program opens the database named on the command line and attempts to\n"
"  create an FTS table named \"fts\" with a single column. If successful, it\n"
"  recursively traverses the directory named by the -dir option and inserts\n"
"  the contents of each file into the fts table. All files are assumed to\n"
"  contain UTF-8 text.\n"
"\n"
"Switches are:\n"
"  -fts [345]       FTS version to use (default=5)\n"
"  -idx [01]        Create a mapping from filename to rowid (default=0)\n"
"  -dir <path>      Root of directory tree to load data from (default=.)\n"
"  -trans <integer> Number of inserts per transaction (default=1)\n"
, zArgv0
);
  exit(1);
}

/*
** Exit with a message based on the argument and the current value of errno.
*/
static void error_out(const char *zText){
  fprintf(stderr, "%s: %s\n", zText, strerror(errno));
  exit(-1);
}

/*
** Exit with a message based on the first argument and the error message
** currently stored in database handle db.
*/
static void sqlite_error_out(const char *zText){
  fprintf(stderr, "%s: %s\n", zText, sqlite3_errmsg(db));
  exit(-1);
}

/*
** Context object for visit_file().
*/
int nRowPerTrans;
sqlite3_stmt *pstmt;
/*
** Callback used with traverse(). The first argument points to an object
** of type VisitContext. This function inserts the contents of the text
** file zPath into the FTS table.
*/
void visit_file(const char *zPath){
  int rc;
  /* printf("%s\n", zPath); */
  sqlite3_bind_text(pstmt, 1, zPath, -1, SQLITE_STATIC);
  sqlite3_step(pstmt);
  rc = sqlite3_reset(pstmt);
  if( rc!=SQLITE_OK ){
    sqlite_error_out("insert");
  }else if( nRowPerTrans>0 
         && (sqlite3_last_insert_rowid(db) % nRowPerTrans)==0 
  ){
    sqlite3_exec(db, "COMMIT ; BEGIN", 0, 0, 0);
  }
}

/*
** Recursively traverse directory zDir. For each file that is not a 
** directory, invoke the supplied callback with its path.
*/
static void traverse(
  const char *zDir,               /* Directory to traverse */
  void (*xCallback)( const char *zPath)
){
  DIR *d;
  struct dirent *e;

  d = opendir(zDir);
  if( d==0 ) error_out("opendir()");

  for(e=readdir(d); e; e=readdir(d)){
    if( strcmp(e->d_name, ".")==0 || strcmp(e->d_name, "..")==0 ) continue;
    char *zPath = sqlite3_mprintf("%s/%s", zDir, e->d_name);
    if (e->d_type & DT_DIR) {
      traverse(zPath, xCallback);
    }else{
      xCallback(zPath);
    }
    sqlite3_free(zPath);
  }

  closedir(d);
}

int main(){
	int argc = 6;
	char* argv[] = { "loadfts.exe", "-fts", "3", "-dir", "./loadfts", "loadfts.db" };
  int iFts = 5;                   /* Value of -fts option */
  int bMap = 0;                   /* True to create mapping table */
  const char *zDir = ".";         /* Directory to scan */
  int i;
  int rc;
  int nRowPerTrans = 0;
  
  char *zSql;

  int nCmd = 0;
  char **aCmd = 0;

  if( argc % 2 ) showHelp(argv[0]);

  for(i=1; i<(argc-1); i+=2){
    char *zOpt = argv[i];
    char *zArg = argv[i+1];
    if( strcmp(zOpt, "-fts")==0 ){
      iFts = atoi(zArg);
      if( iFts!=3 && iFts!=4 && iFts!= 5) showHelp(argv[0]);
    }
    else if( strcmp(zOpt, "-trans")==0 ){
      nRowPerTrans = atoi(zArg);
    }
    else if( strcmp(zOpt, "-idx")==0 ){
      bMap = atoi(zArg);
      if( bMap!=0 && bMap!=1 ) showHelp(argv[0]);
    }
    else if( strcmp(zOpt, "-dir")==0 ){
      zDir = zArg;
    }
    else if( strcmp(zOpt, "-special")==0 ){
      nCmd++;
      aCmd = sqlite3_realloc(aCmd, sizeof(char*) * nCmd);
      aCmd[nCmd-1] = zArg;
    }
    else{
      showHelp(argv[0]);
    }
  }

  /* Open the database file */
  remove(argv[argc - 1]);
  rc = sqlite3_open(argv[argc-1], &db);
  if( rc!=SQLITE_OK ) sqlite_error_out("sqlite3_open()");

  rc = sqlite3_create_function(db, "readtext", 1, SQLITE_UTF8, 0, readfileFunc, 0, 0);

  if( rc!=SQLITE_OK ) sqlite_error_out("sqlite3_create_function()");

  /* Create the FTS table */
  zSql = sqlite3_mprintf("CREATE VIRTUAL TABLE fts USING fts%d(content)", iFts);
  rc = sqlite3_exec(db, zSql, 0, 0, 0);
  if( rc!=SQLITE_OK ) sqlite_error_out("sqlite3_exec(1)");
  sqlite3_free(zSql);

  for(i=0; i<nCmd; i++){
    zSql = sqlite3_mprintf("INSERT INTO fts(fts) VALUES(%Q)", aCmd[i]);
    rc = sqlite3_exec(db, zSql, 0, 0, 0);
    if( rc!=SQLITE_OK ) sqlite_error_out("sqlite3_exec(1)");
    sqlite3_free(zSql);
  }

  /* Compile the INSERT statement to write data to the FTS table. */
  //memset(&sCtx, 0, sizeof(VisitContext));
  db1 = db;
  rc = sqlite3_prepare_v2(db, 
      "INSERT INTO fts VALUES(readtext(?))", -1, &pstmt, 0
  );
  if( rc!=SQLITE_OK ) sqlite_error_out("sqlite3_prepare_v2(1)");

  /* Load all files in the directory hierarchy into the FTS table. */
  if( nRowPerTrans>0 ) sqlite3_exec(db, "BEGIN", 0, 0, 0);
  traverse(zDir, visit_file);
  if( nRowPerTrans>0 ) sqlite3_exec(db, "COMMIT", 0, 0, 0);

  
  if (rc != SQLITE_OK) sqlite_error_out("sqlite3_exec(1)");

  /* Clean up and exit. */
  sqlite3_finalize(pstmt);
  sqlite3_close(db);
  sqlite3_free(aCmd);
  return 0;
}
