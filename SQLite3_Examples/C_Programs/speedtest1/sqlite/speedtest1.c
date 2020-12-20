/*
** A program for performance testing.
**
** The available command-line options are described below:
*/

static const char zHelp[] =
  "Usage: %s [--options] DATABASE\n"
  "Options:\n"
  "  --autovacuum        Enable AUTOVACUUM mode\n"
  "  --cachesize N       Set the cache size to N\n" 
  "  --exclusive         Enable locking_mode=EXCLUSIVE\n"
  "  --explain           Like --sqlonly but with added EXPLAIN keywords\n"
  "  --heap SZ MIN       Memory allocator uses SZ bytes & min allocation MIN\n"
  "  --incrvacuum        Enable incremenatal vacuum mode\n"
  "  --journal M         Set the journal_mode to M\n"
  "  --key KEY           Set the encryption key to KEY\n"
  "  --lookaside N SZ    Configure lookaside for N slots of SZ bytes each\n"
  "  --mmap SZ           MMAP the first SZ bytes of the database file\n"
  "  --multithread       Set multithreaded mode\n"
  "  --nomemstat         Disable memory statistics\n"
  "  --nosync            Set PRAGMA synchronous=OFF\n"
  "  --notnull           Add NOT NULL constraints to table columns\n"
  "  --pagesize N        Set the page size to N\n"
  "  --pcache N SZ       Configure N pages of pagecache each of size SZ bytes\n"
  "  --primarykey        Use PRIMARY KEY instead of UNIQUE where appropriate\n"
  "  --repeat N          Repeat each SELECT N times (default: 1)\n"
  "  --reprepare         Reprepare each statement upon every invocation\n"
  "  --scratch N SZ      Configure scratch memory for N slots of SZ bytes each\n"
  "  --serialized        Set serialized threading mode\n"
  "  --singlethread      Set single-threaded mode - disables all mutexing\n"
  "  --sqlonly           No-op.  Only show the SQL that would have been run.\n"
  "  --shrink-memory     Invoke sqlite3_db_release_memory() frequently.\n"
  "  --size N            Relative test size.  Default=100\n"
  "  --stats             Show statistics at the end\n"
  "  --temp N            N from 0 to 9.  0: no temp table. 9: all temp tables\n"
  "  --testset T         Run test-set T (main, cte, rtree, orm, debug)\n"
  "  --trace             Turn on SQL tracing\n"
  "  --threads N         Use up to N threads for sorting\n"
  "  --utf16be           Set text encoding to UTF-16BE\n"
  "  --utf16le           Set text encoding to UTF-16LE\n"
  "  --verify            Run additional verification steps.\n"
  "  --without-rowid     Use WITHOUT ROWID where appropriate\n"
;


#include "sqlite3.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
# include <io.h>

/* All global state is held in this structure */
  sqlite3 *db;               /* The open database connection */
  sqlite3_stmt *pstmt;       /* Current SQL statement */
  int iStart;      /* Start-time for the current test */
  int iTotal;      /* Total time */
  int bWithoutRowid;         /* True for --without-rowid */
  int bReprepare;            /* True to reprepare the SQL on each rerun */
  int bSqlOnly;              /* True to print the SQL once only */
  int bExplain;              /* Print SQL with EXPLAIN prefix */
  int bVerify;               /* Try to verify that results are correct */
  int bMemShrink;            /* Call sqlite3_db_release_memory() often */
  int eTemp;                 /* 0: no TEMP.  9: always TEMP. */
  int szTest;                /* Scale factor for test iterations */
  int nRepeat;               /* Repeat selects this many times */
  const char *zWR;           /* Might be WITHOUT ROWID */
  const char *zNN;           /* Might be NOT NULL */
  const char *zPK;           /* Might be UNIQUE or PRIMARY KEY */
  unsigned int x, y;         /* Pseudo-random number generator state */
  int nResult;               /* Size of the current result */
  char zResult[3000];        /* Text of the current result */

/* Return " TEMP" or "", as appropriate for creating a table.
*/
static const char *isTemp(int N){
  return eTemp>=N ? " TEMP" : "";
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
  static const struct { char *zSuffix; int iMult; } aMult[] = {
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
	  while (isdigit(zArg[0])){
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


/* Return a pseudo-random unsigned integer */
unsigned int speedtest1_random(void){
  x = (x>>1) ^ ((1+~(x&1)) & 0xd0000001);
  y = y*1103515245 + 12345;
  return x ^ y;
}

/* Map the value in within the range of 1...limit into another
** number in a way that is chatic and invertable.
*/
unsigned swizzle(unsigned in, unsigned limit){
  unsigned out = 0;
  while( limit ){
    out = (out<<1) | (in&1);
    in >>= 1;
    limit >>= 1;
  }
  return out;
}

/* Round up a number so that it is a power of two minus one
*/
unsigned roundup_allones(unsigned limit){
  unsigned m = 1;
  while( m<limit ) m = (m<<1)+1;
  return m;
}

/* The speedtest1_numbername procedure below converts its argment (an integer)
** into a string which is the English-language name for that number.
** The returned string should be freed with sqlite3_free().
**
** Example:
**
**     speedtest1_numbername(123)   ->  "one hundred twenty three"
*/
int speedtest1_numbername(unsigned int n, char *zOut, int nOut){
  static const char *ones[] = {  "zero", "one", "two", "three", "four", "five", 
                  "six", "seven", "eight", "nine", "ten", "eleven", "twelve", 
                  "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                  "eighteen", "nineteen" };
  static const char *tens[] = { "", "ten", "twenty", "thirty", "forty",
                 "fifty", "sixty", "seventy", "eighty", "ninety" };
  int i = 0;

  if( n>=1000000000 ){
    i += speedtest1_numbername(n/1000000000, zOut+i, nOut-i);
    sqlite3_snprintf(nOut-i, zOut+i, " billion");
    i += (int)strlen(zOut+i);
    n = n % 1000000000;
  }
  if( n>=1000000 ){
    if( i && i<nOut-1 ) zOut[i++] = ' ';
    i += speedtest1_numbername(n/1000000, zOut+i, nOut-i);
    sqlite3_snprintf(nOut-i, zOut+i, " million");
    i += (int)strlen(zOut+i);
    n = n % 1000000;
  }
  if( n>=1000 ){
    if( i && i<nOut-1 ) zOut[i++] = ' ';
    i += speedtest1_numbername(n/1000, zOut+i, nOut-i);
    sqlite3_snprintf(nOut-i, zOut+i, " thousand");
    i += (int)strlen(zOut+i);
    n = n % 1000;
  }
  if( n>=100 ){
    if( i && i<nOut-1 ) zOut[i++] = ' ';
    sqlite3_snprintf(nOut-i, zOut+i, "%s hundred", ones[n/100]);
    i += (int)strlen(zOut+i);
    n = n % 100;
  }
  if( n>=20 ){
    if( i && i<nOut-1 ) zOut[i++] = ' ';
    sqlite3_snprintf(nOut-i, zOut+i, "%s", tens[n/10]);
    i += (int)strlen(zOut+i);
    n = n % 10;
  }
  if( n>0 ){
    if( i && i<nOut-1 ) zOut[i++] = ' ';
    sqlite3_snprintf(nOut-i, zOut+i, "%s", ones[n]);
    i += (int)strlen(zOut+i);
  }
  if( i==0 ){
    sqlite3_snprintf(nOut-i, zOut+i, "zero");
    i += (int)strlen(zOut+i);
  }
  return i;
}


/* Start a new test case */
char* zName;
static const char zDots[] =
  ".......................................................................";
void speedtest1_begin_test(int iTestNum, char *zName){
	int n = (int)strlen(zName);
  /*char *zName;
  va_list ap;
  va_start(ap, zTestName);
  zName = sqlite3_vmprintf(zTestName, ap);
  va_end(ap);
  n = (int)strlen(zName);
  if( n>60 ){
    zName[60] = 0;
    n = 60;
  }*/
  if( bSqlOnly ){
    printf("/* %4d - %s%.*s */\n", iTestNum, zName, 60-n, zDots);
  }else{
    printf("%4d - %s%.*s ", iTestNum, zName, 60-n, zDots);
    fflush(stdout);
  }
  sqlite3_free(zName);
  nResult = 0;
  x = 0xad131d0b;
  y = 0x44f9eac8;
}

/* Complete a test case */
void speedtest1_end_test(void){
  int iElapseTime =  iStart;
  if( !bSqlOnly ){
    iTotal += iElapseTime;
    printf("%4d.%03ds\n", (int)(iElapseTime/1000), (int)(iElapseTime%1000));
  }
  if( pstmt ){
    sqlite3_finalize(pstmt);
    pstmt = 0;
  }
}

/* Report end of testing */
void speedtest1_final(void){
  if( !bSqlOnly ){
    printf("       TOTAL%.*s %4d.%03ds\n", 60-5, zDots,
           (int)(iTotal/1000), (int)(iTotal%1000));
  }
}

/* Print an SQL statement to standard output */
static void printSql(const char *zSql){
  int n = (int)strlen(zSql);
  while (n>0 && (zSql[n - 1] == ';' || isspace((unsigned char)(zSql[n - 1])))){ n--; }
  if( bExplain ) printf("EXPLAIN ");
  printf("%.*s;\n", n, zSql);
  if( bExplain
   && ( sqlite3_strglob("CREATE *", zSql)==0
     || sqlite3_strglob("DROP *", zSql)==0
     || sqlite3_strglob("ALTER *", zSql)==0
      )
  ){
    printf("%.*s;\n", n, zSql);
  }
}

/* Shrink memory used, if appropriate and if the SQLite version is capable
** of doing so.
*/
void speedtest1_shrink_memory(void){
  if( bMemShrink ) sqlite3_db_release_memory(db);
}

/* Run SQL */
char *zSqlSpeedtest1;
void speedtest1_exec(char *zSqlSpeedtest1){
  
  if( bSqlOnly ){
	  printSql(zSqlSpeedtest1);
  }else{
    char *zErrMsg = 0;
	int rc = sqlite3_exec(db, zSqlSpeedtest1, 0, 0, &zErrMsg);
  }
  //sqlite3_free(zSqlSpeedtest1);
  speedtest1_shrink_memory();
}

/* Prepare an SQL statement */
char *zSqlPrepare;
void speedtest1_prepare(char *zSqlPrepare){

  if( bSqlOnly ){
	  printSql(zSqlPrepare);
  }else{
    int rc;
    if( pstmt ) sqlite3_finalize(pstmt);
	rc = sqlite3_prepare_v2(db, zSqlPrepare, -1, &pstmt, 0);
  }
  sqlite3_free(zSqlPrepare);
}

sqlite3_stmt *pNew;
/* Run an SQL statement previously prepared */
void speedtest1_run(void){
  int i, n, len;
  if( bSqlOnly ) return;
  assert( pstmt );
  nResult = 0;
  while( sqlite3_step(pstmt)==100 ){
    n = sqlite3_column_count(pstmt);
    for(i=0; i<n; i++){
      const char *z = (const char*)sqlite3_column_text(pstmt, i);
      if( z==0 ) z = "nil";
      len = (int)strlen(z);
      if( nResult+len<sizeof(zResult)-2 ){
        if( nResult>0 ) zResult[nResult++] = ' ';
        memcpy(zResult + nResult, z, len+1);
        nResult += len;
      }
    }
  }
  if( bReprepare ){
    
    sqlite3_prepare_v2(db, sqlite3_sql(pstmt), -1, &pNew, 0);
    sqlite3_finalize(pstmt);
    pstmt = pNew;
  }else
  {
    sqlite3_reset(pstmt);
  }
  speedtest1_shrink_memory();
}


static void traceCallback(void *NotUsed, const char *zSql){
  int n = (int)strlen(zSql);
  while (n>0 && (zSql[n - 1] == ';' || isspace((unsigned char)(zSql[n - 1])))) n--;
  fprintf(stderr,"%.*s;\n", n, zSql);
}

/* Estimate the square root of an integer */
static int est_square_root(int x){
  int y0 = x/2;
  int y1;
  int n;
  for(n=0; y0>0 && n<10; n++){
    y1 = (y0 + x/y0)/2;
    if( y1==y0 ) break;
    y0 = y1;
  }
  return y0;
}

/*
** The main and default testset
*/
void testset_main(void){
  int i;                        /* Loop counter */
  int n;                        /* iteration count */
  int sz;                       /* Size of the tables */
  int maxb;                     /* Maximum swizzled value */
  unsigned x1 = 0, x2 = 0;      /* Parameters */
  int len = 0;                  /* Length of the zNum[] string */
  char zNum[2000];              /* A number name */

  sz = n = szTest;
  zNum[0] = 0;
  maxb = roundup_allones(sz);
  zName = sqlite3_mprintf("%d INSERTs into table with no index", n);
  speedtest1_begin_test(100,zName);
  speedtest1_exec("BEGIN");

  zSqlSpeedtest1 = sqlite3_mprintf("CREATE%s TABLE t1(a INTEGER %s, b INTEGER %s, c TEXT %s);",
	  isTemp(9), zNN, zNN, zNN);

  speedtest1_exec(zSqlSpeedtest1);
  zSqlPrepare = sqlite3_mprintf("INSERT INTO t1 VALUES(?1,?2,?3); --  %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    x1 = swizzle(i,maxb);
    speedtest1_numbername(x1, zNum, sizeof(zNum));
    sqlite3_bind_int64(pstmt, 1, (int)x1);
    sqlite3_bind_int(pstmt, 2, i);
    sqlite3_bind_text(pstmt, 3, zNum, -1, 0);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = sz;
  zName = sqlite3_mprintf("%d ordered INSERTS with one index/PK", n);
  speedtest1_begin_test(110, zName);
  speedtest1_exec("BEGIN");
  zSqlSpeedtest1 = sqlite3_mprintf("CREATE%s TABLE t2(a INTEGER %s %s, b INTEGER %s, c TEXT %s) %s",
	  isTemp(5), zNN, zPK, zNN, zNN, zWR);
  speedtest1_exec(zSqlSpeedtest1);
  zSqlPrepare = sqlite3_mprintf("INSERT INTO t2 VALUES(?1,?2,?3); -- %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    x1 = swizzle(i,maxb);
    speedtest1_numbername(x1, zNum, sizeof(zNum));
    sqlite3_bind_int(pstmt, 1, i);
    sqlite3_bind_int64(pstmt, 2, (int)x1);
    sqlite3_bind_text(pstmt, 3, zNum, -1, 0);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = sz;
  zName = sqlite3_mprintf("%d unordered INSERTS with one index/PK", n);
  speedtest1_begin_test(120, zName);
  speedtest1_exec("BEGIN");
  zSqlSpeedtest1 = sqlite3_mprintf("CREATE%s TABLE t3(a INTEGER %s %s, b INTEGER %s, c TEXT %s) %s",
	  isTemp(3), zNN, zPK, zNN, zNN, zWR);
  speedtest1_exec(zSqlSpeedtest1);
  zSqlPrepare = sqlite3_mprintf("INSERT INTO t3 VALUES(?1,?2,?3); -- %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    x1 = swizzle(i,maxb);
    speedtest1_numbername(x1, zNum, sizeof(zNum));
    sqlite3_bind_int(pstmt, 2, i);
    sqlite3_bind_int64(pstmt, 1, (int)x1);
    sqlite3_bind_text(pstmt, 3, zNum, -1, 0);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  n = 25;
  zName = sqlite3_mprintf("%d SELECTS, numeric BETWEEN, unindexed", n);
  speedtest1_begin_test(130, zName);
  speedtest1_exec("BEGIN");
  zSqlPrepare = sqlite3_mprintf("SELECT count(*), avg(b), sum(length(c)), group_concat(c) FROM t1\n"
	  " WHERE b BETWEEN ?1 AND ?2; -- %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    if( (i-1)%nRepeat==0 ){
      x1 = speedtest1_random()%maxb;
      x2 = speedtest1_random()%10 + sz/5000 + x1;
    }
    sqlite3_bind_int(pstmt, 1, x1);
    sqlite3_bind_int(pstmt, 2, x2);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = 10;
  zName = sqlite3_mprintf("%d SELECTS, LIKE, unindexed", n);
  speedtest1_begin_test(140, zName);
  speedtest1_exec("BEGIN");
  zSqlPrepare = sqlite3_mprintf("SELECT count(*), avg(b), sum(length(c)), group_concat(c) FROM t1\n"
	  " WHERE c LIKE ?1; -- %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    if( (i-1)%nRepeat==0 ){
      x1 = speedtest1_random()%maxb;
      zNum[0] = '%';
      len = speedtest1_numbername(i, zNum+1, sizeof(zNum)-2);
      zNum[len] = '%';
      zNum[len+1] = 0;
    }
    sqlite3_bind_text(pstmt, 1, zNum, len+1, 0);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = 10;
  zName = sqlite3_mprintf("%d SELECTS w/ORDER BY, unindexed", n);
  speedtest1_begin_test(142, zName);
  speedtest1_exec("BEGIN");
  zSqlPrepare = sqlite3_mprintf("SELECT a, b, c FROM t1 WHERE c LIKE ?1\n"
	  " ORDER BY a; -- %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    if( (i-1)%nRepeat==0 ){
      x1 = speedtest1_random()%maxb;
      zNum[0] = '%';
      len = speedtest1_numbername(i, zNum+1, sizeof(zNum)-2);
      zNum[len] = '%';
      zNum[len+1] = 0;
    }
    sqlite3_bind_text(pstmt, 1, zNum, len+1, 0);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  n = 10; /* szTest/5; */
  zName = sqlite3_mprintf("%d SELECTS w/ORDER BY and LIMIT, unindexed", n);
  speedtest1_begin_test(145, zName);
  speedtest1_exec("BEGIN");
  zSqlPrepare = sqlite3_mprintf("SELECT a, b, c FROM t1 WHERE c LIKE ?1\n"
	  " ORDER BY a LIMIT 10; -- %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    if( (i-1)%nRepeat==0 ){
      x1 = speedtest1_random()%maxb;
      zNum[0] = '%';
      len = speedtest1_numbername(i, zNum+1, sizeof(zNum)-2);
      zNum[len] = '%';
      zNum[len+1] = 0;
    }
    sqlite3_bind_text(pstmt, 1, zNum, len+1, 0);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  zName = sqlite3_mprintf("CREATE INDEX five times");
  speedtest1_begin_test(150, zName);
  speedtest1_exec("BEGIN;");
  speedtest1_exec("CREATE UNIQUE INDEX t1b ON t1(b);");
  speedtest1_exec("CREATE INDEX t1c ON t1(c);");
  speedtest1_exec("CREATE UNIQUE INDEX t2b ON t2(b);");
  speedtest1_exec("CREATE INDEX t2c ON t2(c DESC);");
  speedtest1_exec("CREATE INDEX t3bc ON t3(b,c);");
  speedtest1_exec("COMMIT;");
  speedtest1_end_test();


  n = sz/5;
  zName = sqlite3_mprintf("%d SELECTS, numeric BETWEEN, indexed", n);
  speedtest1_begin_test(160,zName);
  speedtest1_exec("BEGIN");
  zSqlPrepare = sqlite3_mprintf("SELECT count(*), avg(b), sum(length(c)), group_concat(a) FROM t1\n"
	  " WHERE b BETWEEN ?1 AND ?2; -- %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    if( (i-1)%nRepeat==0 ){
      x1 = speedtest1_random()%maxb;
      x2 = speedtest1_random()%10 + sz/5000 + x1;
    }
    sqlite3_bind_int(pstmt, 1, x1);
    sqlite3_bind_int(pstmt, 2, x2);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = sz/5;
  zName = sqlite3_mprintf("%d SELECTS, numeric BETWEEN, PK", n);
  speedtest1_begin_test(161, zName);
  speedtest1_exec("BEGIN");
  zSqlPrepare = sqlite3_mprintf("SELECT count(*), avg(b), sum(length(c)), group_concat(a) FROM t2\n"
	  " WHERE a BETWEEN ?1 AND ?2; -- %d times", n);
  speedtest1_prepare(zSqlPrepare );
  for(i=1; i<=n; i++){
    if( (i-1)%nRepeat==0 ){
      x1 = speedtest1_random()%maxb;
      x2 = speedtest1_random()%10 + sz/5000 + x1;
    }
    sqlite3_bind_int(pstmt, 1, x1);
    sqlite3_bind_int(pstmt, 2, x2);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = sz/5;
  zName = sqlite3_mprintf("%d SELECTS, text BETWEEN, indexed", n);
  speedtest1_begin_test(170,zName);
  speedtest1_exec("BEGIN");
  zSqlPrepare = sqlite3_mprintf("SELECT count(*), avg(b), sum(length(c)), group_concat(a) FROM t1\n"
	  " WHERE c BETWEEN ?1 AND (?1||'~'); -- %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    if( (i-1)%nRepeat==0 ){
      x1 = swizzle(i, maxb);
      len = speedtest1_numbername(x1, zNum, sizeof(zNum)-1);
    }
    sqlite3_bind_text(pstmt, 1, zNum, len, 0);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  n = sz;
  zName = sqlite3_mprintf("%d INSERTS with three indexes", n);
  speedtest1_begin_test(180, zName);
  speedtest1_exec("BEGIN");
  zSqlSpeedtest1 = sqlite3_mprintf("CREATE%s TABLE t4(\n"
    "  a INTEGER %s %s,\n"
    "  b INTEGER %s,\n"
    "  c TEXT %s\n"
	") %s",
	isTemp(1), zNN, zPK, zNN, zNN, zWR);
  speedtest1_exec(zSqlSpeedtest1);
  speedtest1_exec("CREATE INDEX t4b ON t4(b)");
  speedtest1_exec("CREATE INDEX t4c ON t4(c)");
  speedtest1_exec("INSERT INTO t4 SELECT * FROM t1");
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  n = sz;
  zName = sqlite3_mprintf("DELETE and REFILL one table", n);
  speedtest1_begin_test(190, zName);
  speedtest1_exec("DELETE FROM t2;");
  speedtest1_exec("INSERT INTO t2 SELECT * FROM t1;");
  speedtest1_end_test();

  zName = sqlite3_mprintf("VACUUM");
  speedtest1_begin_test(200, zName);
  speedtest1_exec("VACUUM");
  speedtest1_end_test();

  zName = sqlite3_mprintf("ALTER TABLE ADD COLUMN, and query");
  speedtest1_begin_test(210, zName);
  speedtest1_exec("ALTER TABLE t2 ADD COLUMN d DEFAULT 123");
  speedtest1_exec("SELECT sum(d) FROM t2");
  speedtest1_end_test();


  n = sz/5;
  zName = sqlite3_mprintf("%d UPDATES, numeric BETWEEN, indexed", n);
  speedtest1_begin_test(230, zName);
  speedtest1_exec("BEGIN");
  zSqlPrepare = sqlite3_mprintf("UPDATE t2 SET d=b*2 WHERE b BETWEEN ?1 AND ?2; -- %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%maxb;
    x2 = speedtest1_random()%10 + sz/5000 + x1;
    sqlite3_bind_int(pstmt, 1, x1);
    sqlite3_bind_int(pstmt, 2, x2);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = sz;
  zName = sqlite3_mprintf("%d UPDATES of individual rows", n);
  speedtest1_begin_test(240, zName);
  speedtest1_exec("BEGIN");
  zSqlPrepare = sqlite3_mprintf("UPDATE t2 SET d=b*3 WHERE a=?1; -- %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%sz + 1;
    sqlite3_bind_int(pstmt, 1, x1);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  zName = sqlite3_mprintf("One big UPDATE of the whole %d-row table", sz);
  speedtest1_begin_test(250, zName);
  speedtest1_exec("UPDATE t2 SET d=b*4");
  speedtest1_end_test();

  zName = sqlite3_mprintf("Query added column after filling");
  speedtest1_begin_test(260, zName);
  speedtest1_exec("SELECT sum(d) FROM t2");
  speedtest1_end_test();



  n = sz/5;
  zName = sqlite3_mprintf("%d DELETEs, numeric BETWEEN, indexed", n);
  speedtest1_begin_test(270,zName );
  speedtest1_exec("BEGIN");
  zSqlPrepare = sqlite3_mprintf("DELETE FROM t2 WHERE b BETWEEN ?1 AND ?2; -- %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%maxb + 1;
    x2 = speedtest1_random()%10 + sz/5000 + x1;
    sqlite3_bind_int(pstmt, 1, x1);
    sqlite3_bind_int(pstmt, 2, x2);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = sz;
  zName = sqlite3_mprintf("%d DELETEs of individual rows", n);
  speedtest1_begin_test(280, zName);
  speedtest1_exec("BEGIN");
  zSqlPrepare = sqlite3_mprintf("DELETE FROM t3 WHERE a=?1; -- %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%sz + 1;
    sqlite3_bind_int(pstmt, 1, x1);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  zName = sqlite3_mprintf("Refill two %d-row tables using REPLACE", sz);
  speedtest1_begin_test(290, zName);
  speedtest1_exec("REPLACE INTO t2(a,b,c) SELECT a,b,c FROM t1");
  speedtest1_exec("REPLACE INTO t3(a,b,c) SELECT a,b,c FROM t1");
  speedtest1_end_test();

  zName = sqlite3_mprintf("Refill a %d-row table using (b&1)==(a&1)", sz);
  speedtest1_begin_test(300, zName);
  speedtest1_exec("DELETE FROM t2;");
  speedtest1_exec("INSERT INTO t2(a,b,c)\n"
                  " SELECT a,b,c FROM t1  WHERE (b&1)==(a&1);");
  speedtest1_exec("INSERT INTO t2(a,b,c)\n"
                  " SELECT a,b,c FROM t1  WHERE (b&1)<>(a&1);");
  speedtest1_end_test();


  n = sz/5;
  zName = sqlite3_mprintf("%d four-ways joins", n);
  speedtest1_begin_test(310, zName);
  speedtest1_exec("BEGIN");
  zSqlPrepare = sqlite3_mprintf("SELECT t1.c FROM t1, t2, t3, t4\n"
    " WHERE t4.a BETWEEN ?1 AND ?2\n"
    "   AND t3.a=t4.b\n"
    "   AND t2.a=t3.b\n"
	"   AND t1.c=t2.c");
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%sz + 1;
    x2 = speedtest1_random()%10 + x1 + 4;
    sqlite3_bind_int(pstmt, 1, x1);
    sqlite3_bind_int(pstmt, 2, x2);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  zName = sqlite3_mprintf("subquery in result set", n);
  speedtest1_begin_test(320, zName);
  zSqlPrepare = sqlite3_mprintf("SELECT sum(a), max(c),\n"
    "       avg((SELECT a FROM t2 WHERE 5+t2.b=t1.b) AND rowid<?1), max(c)\n"
	" FROM t1 WHERE rowid<?1;");
  speedtest1_prepare(zSqlPrepare);
  sqlite3_bind_int(pstmt, 1, est_square_root(szTest)*50);
  speedtest1_run();
  speedtest1_end_test();

  sz = n = szTest;
  zNum[0] = 0;
  maxb = roundup_allones(sz/3);
  zName = sqlite3_mprintf("%d REPLACE ops on an IPK", n);
  speedtest1_begin_test(400, zName);
  speedtest1_exec("BEGIN");
  zSqlSpeedtest1 = sqlite3_mprintf("CREATE%s TABLE t5(a INTEGER PRIMARY KEY, b %s);",
	  isTemp(9), zNN);
  speedtest1_exec(zSqlSpeedtest1);
  zSqlPrepare = sqlite3_mprintf("REPLACE INTO t5 VALUES(?1,?2); --  %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    x1 = swizzle(i,maxb);
    speedtest1_numbername(i, zNum, sizeof(zNum));
    sqlite3_bind_int(pstmt, 1, (int)x1);
    sqlite3_bind_text(pstmt, 2, zNum, -1, 0);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();
  zName = sqlite3_mprintf("%d SELECTS on an IPK", n);
  speedtest1_begin_test(410, zName);
  zSqlPrepare = sqlite3_mprintf("SELECT b FROM t5 WHERE a=?1; --  %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    x1 = swizzle(i,maxb);
    sqlite3_bind_int(pstmt, 1, (int)x1);
    speedtest1_run();
  }
  speedtest1_end_test();

  sz = n = szTest;
  zNum[0] = 0;
  maxb = roundup_allones(sz/3);
  zName = sqlite3_mprintf("%d REPLACE on TEXT PK", n);
  speedtest1_begin_test(500, zName);
  speedtest1_exec("BEGIN");
  zSqlSpeedtest1 = sqlite3_mprintf("CREATE%s TABLE t6(a TEXT PRIMARY KEY, b %s)%s;",
	  isTemp(9), zNN,
	  sqlite3_libversion_number() >= 3008002 ? "WITHOUT ROWID" : "");
  speedtest1_exec(zSqlSpeedtest1);
  zSqlPrepare = sqlite3_mprintf("REPLACE INTO t6 VALUES(?1,?2); --  %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    x1 = swizzle(i,maxb);
    speedtest1_numbername(x1, zNum, sizeof(zNum));
    sqlite3_bind_int(pstmt, 2, i);
    sqlite3_bind_text(pstmt, 1, zNum, -1, 0);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();
  zName = sqlite3_mprintf("%d SELECTS on a TEXT PK", n);
  speedtest1_begin_test(510, zName);
  zSqlPrepare = sqlite3_mprintf("SELECT b FROM t6 WHERE a=?1; --  %d times", n);
  speedtest1_prepare(zSqlPrepare);
  for(i=1; i<=n; i++){
    x1 = swizzle(i,maxb);
    speedtest1_numbername(x1, zNum, sizeof(zNum));
    sqlite3_bind_text(pstmt, 1, zNum, -1, 0);
    speedtest1_run();
  }
  speedtest1_end_test();
  zName = sqlite3_mprintf("%d SELECT DISTINCT", n);
  speedtest1_begin_test(520, zName);
  speedtest1_exec("SELECT DISTINCT b FROM t5;");
  speedtest1_exec("SELECT DISTINCT b FROM t6;");
  speedtest1_end_test();

  zName = sqlite3_mprintf("PRAGMA integrity_check");
  speedtest1_begin_test(980, zName);
  speedtest1_exec("PRAGMA integrity_check");
  speedtest1_end_test();

  zName = sqlite3_mprintf("ANALYZE");
  speedtest1_begin_test(990, zName);
  speedtest1_exec("ANALYZE");
  speedtest1_end_test();
}

/*
** A testset for common table expressions.  This exercises code
** for views, subqueries, co-routines, etc.
*/
void testset_cte(void){
  static const char *azPuzzle[] = {
    /* Easy */
    "534...9.."
    "67.195..."
    ".98....6."
    "8...6...3"
    "4..8.3..1"
    "....2...6"
    ".6....28."
    "...419..5"
    "...28..79",

    /* Medium */
    "53....9.."
    "6..195..."
    ".98....6."
    "8...6...3"
    "4..8.3..1"
    "....2...6"
    ".6....28."
    "...419..5"
    "....8..79",

    /* Hard */
    "53......."
    "6..195..."
    ".98....6."
    "8...6...3"
    "4..8.3..1"
    "....2...6"
    ".6....28."
    "...419..5"
    "....8..79",
  };
  const char *zPuz;
  double rSpacing;
  int nElem;

  if( szTest<25 ){
    zPuz = azPuzzle[0];
  }else if( szTest<70 ){
    zPuz = azPuzzle[1];
  }else{
    zPuz = azPuzzle[2];
  }
  zName = sqlite3_mprintf("Sudoku with recursive 'digits'");
  speedtest1_begin_test(100, zName);
  zSqlPrepare = sqlite3_mprintf("WITH RECURSIVE\n"
    "  input(sud) AS (VALUES(?1)),\n"
    "  digits(z,lp) AS (\n"
    "    VALUES('1', 1)\n"
    "    UNION ALL\n"
    "    SELECT CAST(lp+1 AS TEXT), lp+1 FROM digits WHERE lp<9\n"
    "  ),\n"
    "  x(s, ind) AS (\n"
    "    SELECT sud, instr(sud, '.') FROM input\n"
    "    UNION ALL\n"
    "    SELECT\n"
    "      substr(s, 1, ind-1) || z || substr(s, ind+1),\n"
    "      instr( substr(s, 1, ind-1) || z || substr(s, ind+1), '.' )\n"
    "     FROM x, digits AS z\n"
    "    WHERE ind>0\n"
    "      AND NOT EXISTS (\n"
    "            SELECT 1\n"
    "              FROM digits AS lp\n"
    "             WHERE z.z = substr(s, ((ind-1)/9)*9 + lp, 1)\n"
    "                OR z.z = substr(s, ((ind-1)%%9) + (lp-1)*9 + 1, 1)\n"
    "                OR z.z = substr(s, (((ind-1)/3) %% 3) * 3\n"
    "                        + ((ind-1)/27) * 27 + lp\n"
    "                        + ((lp-1) / 3) * 6, 1)\n"
    "         )\n"
    "  )\n"
	"SELECT s FROM x WHERE ind=0;");
  speedtest1_prepare(zSqlPrepare);
  sqlite3_bind_text(pstmt, 1, zPuz, -1, 0);
  speedtest1_run();
  speedtest1_end_test();

  zName = sqlite3_mprintf("Sudoku with VALUES 'digits'");
  speedtest1_begin_test(200, zName);
  zSqlPrepare = sqlite3_mprintf("WITH RECURSIVE\n"
    "  input(sud) AS (VALUES(?1)),\n"
    "  digits(z,lp) AS (VALUES('1',1),('2',2),('3',3),('4',4),('5',5),\n"
    "                         ('6',6),('7',7),('8',8),('9',9)),\n"
    "  x(s, ind) AS (\n"
    "    SELECT sud, instr(sud, '.') FROM input\n"
    "    UNION ALL\n"
    "    SELECT\n"
    "      substr(s, 1, ind-1) || z || substr(s, ind+1),\n"
    "      instr( substr(s, 1, ind-1) || z || substr(s, ind+1), '.' )\n"
    "     FROM x, digits AS z\n"
    "    WHERE ind>0\n"
    "      AND NOT EXISTS (\n"
    "            SELECT 1\n"
    "              FROM digits AS lp\n"
    "             WHERE z.z = substr(s, ((ind-1)/9)*9 + lp, 1)\n"
    "                OR z.z = substr(s, ((ind-1)%%9) + (lp-1)*9 + 1, 1)\n"
    "                OR z.z = substr(s, (((ind-1)/3) %% 3) * 3\n"
    "                        + ((ind-1)/27) * 27 + lp\n"
    "                        + ((lp-1) / 3) * 6, 1)\n"
    "         )\n"
    "  )\n"
	"SELECT s FROM x WHERE ind=0;");
  speedtest1_prepare(zSqlPrepare);
  sqlite3_bind_text(pstmt, 1, zPuz, -1, 0);
  speedtest1_run();
  speedtest1_end_test();

  rSpacing = 5.0/szTest;
  zName = sqlite3_mprintf("Mandelbrot Set with spacing=%f", rSpacing);
  speedtest1_begin_test(300, zName);
  zSqlPrepare = sqlite3_mprintf("WITH RECURSIVE \n"
   "  xaxis(x) AS (VALUES(-2.0) UNION ALL SELECT x+?1 FROM xaxis WHERE x<1.2),\n"
   "  yaxis(y) AS (VALUES(-1.0) UNION ALL SELECT y+?2 FROM yaxis WHERE y<1.0),\n"
   "  m(iter, cx, cy, x, y) AS (\n"
   "    SELECT 0, x, y, 0.0, 0.0 FROM xaxis, yaxis\n"
   "    UNION ALL\n"
   "    SELECT iter+1, cx, cy, x*x-y*y + cx, 2.0*x*y + cy FROM m \n"
   "     WHERE (x*x + y*y) < 4.0 AND iter<28\n"
   "  ),\n"
   "  m2(iter, cx, cy) AS (\n"
   "    SELECT max(iter), cx, cy FROM m GROUP BY cx, cy\n"
   "  ),\n"
   "  a(t) AS (\n"
   "    SELECT group_concat( substr(' .+*#', 1+min(iter/7,4), 1), '') \n"
   "    FROM m2 GROUP BY cy\n"
   "  )\n"
   "SELECT group_concat(rtrim(t),x'0a') FROM a;");
  speedtest1_prepare(zSqlPrepare);
  sqlite3_bind_double(pstmt, 1, rSpacing*0.05);
  sqlite3_bind_double(pstmt, 2, rSpacing);
  speedtest1_run();
  speedtest1_end_test();

  nElem = 10000*szTest;
  zName = sqlite3_mprintf("EXCEPT operator on %d-element tables", nElem);
  speedtest1_begin_test(400, zName);
  zSqlPrepare = sqlite3_mprintf("WITH RECURSIVE \n"
    "  t1(x) AS (VALUES(2) UNION ALL SELECT x+2 FROM t1 WHERE x<%d),\n"
    "  t2(y) AS (VALUES(3) UNION ALL SELECT y+3 FROM t2 WHERE y<%d)\n"
    "SELECT count(x), avg(x) FROM (\n"
    "  SELECT x FROM t1 EXCEPT SELECT y FROM t2 ORDER BY 1\n"
	");",
	nElem, nElem);
  speedtest1_prepare(zSqlPrepare);
  speedtest1_run();
  speedtest1_end_test();

}

/*
** A testset that does key/value storage on tables with many columns.
** This is the kind of workload generated by ORMs such as CoreData.
*/
void testset_orm(void){
  unsigned i, j, n;
  unsigned nRow;
  unsigned x1, len;
  char zNum[2000];              /* A number name */
  static const char zType[] =   /* Types for all non-PK columns, in order */
    "IBBIIITIVVITBTBFBFITTFBTBVBVIFTBBFITFFVBIFIVBVVVBTVTIBBFFIVIBTB"
    "TVTTFTVTVFFIITIFBITFTTFFFVBIIBTTITFTFFVVVFIIITVBBVFFTVVB";

  nRow = n = szTest*250;
  zName = sqlite3_mprintf("Fill %d rows", n);
  speedtest1_begin_test(100, zName);
  zSqlSpeedtest1 = sqlite3_mprintf("BEGIN;"
    "CREATE TABLE ZLOOKSLIKECOREDATA ("
    "  ZPK INTEGER PRIMARY KEY,"
    "  ZTERMFITTINGHOUSINGCOMMAND INTEGER,"
    "  ZBRIEFGOBYDODGERHEIGHT BLOB,"
    "  ZCAPABLETRIPDOORALMOND BLOB,"
    "  ZDEPOSITPAIRCOLLEGECOMET INTEGER,"
    "  ZFRAMEENTERSIMPLEMOUTH INTEGER,"
    "  ZHOPEFULGATEHOLECHALK INTEGER,"
    "  ZSLEEPYUSERGRANDBOWL TIMESTAMP,"
    "  ZDEWPEACHCAREERCELERY INTEGER,"
    "  ZHANGERLITHIUMDINNERMEET VARCHAR,"
    "  ZCLUBRELEASELIZARDADVICE VARCHAR,"
    "  ZCHARGECLICKHUMANEHIRE INTEGER,"
    "  ZFINGERDUEPIZZAOPTION TIMESTAMP,"
    "  ZFLYINGDOCTORTABLEMELODY BLOB,"
    "  ZLONGFINLEAVEIMAGEOIL TIMESTAMP,"
    "  ZFAMILYVISUALOWNERMATTER BLOB,"
    "  ZGOLDYOUNGINITIALNOSE FLOAT,"
    "  ZCAUSESALAMITERMCYAN BLOB,"
    "  ZSPREADMOTORBISCUITBACON FLOAT,"
    "  ZGIFTICEFISHGLUEHAIR INTEGER,"
    "  ZNOTICEPEARPOLICYJUICE TIMESTAMP,"
    "  ZBANKBUFFALORECOVERORBIT TIMESTAMP,"
    "  ZLONGDIETESSAYNATURE FLOAT,"
    "  ZACTIONRANGEELEGANTNEUTRON BLOB,"
    "  ZCADETBRIGHTPLANETBANK TIMESTAMP,"
    "  ZAIRFORGIVEHEADFROG BLOB,"
    "  ZSHARKJUSTFRUITMOVIE VARCHAR,"
    "  ZFARMERMORNINGMIRRORCONCERN BLOB,"
    "  ZWOODPOETRYCOBBLERBENCH VARCHAR,"
    "  ZHAFNIUMSCRIPTSALADMOTOR INTEGER,"
    "  ZPROBLEMCLUBPOPOVERJELLY FLOAT,"
    "  ZEIGHTLEADERWORKERMOST TIMESTAMP,"
    "  ZGLASSRESERVEBARIUMMEAL BLOB,"
    "  ZCLAMBITARUGULAFAJITA BLOB,"
    "  ZDECADEJOYOUSWAVEHABIT FLOAT,"
    "  ZCOMPANYSUMMERFIBERELF INTEGER,"
    "  ZTREATTESTQUILLCHARGE TIMESTAMP,"
    "  ZBROWBALANCEKEYCHOWDER FLOAT,"
    "  ZPEACHCOPPERDINNERLAKE FLOAT,"
    "  ZDRYWALLBEYONDBROWNBOWL VARCHAR,"
    "  ZBELLYCRASHITEMLACK BLOB,"
    "  ZTENNISCYCLEBILLOFFICER INTEGER,"
    "  ZMALLEQUIPTHANKSGLUE FLOAT,"
    "  ZMISSREPLYHUMANLIVING INTEGER,"
    "  ZKIWIVISUALPRIDEAPPLE VARCHAR,"
    "  ZWISHHITSKINMOTOR BLOB,"
    "  ZCALMRACCOONPROGRAMDEBIT VARCHAR,"
    "  ZSHINYASSISTLIVINGCRAB VARCHAR,"
    "  ZRESOLVEWRISTWRAPAPPLE VARCHAR,"
    "  ZAPPEALSIMPLESECONDHOUSING BLOB,"
    "  ZCORNERANCHORTAPEDIVER TIMESTAMP,"
    "  ZMEMORYREQUESTSOURCEBIG VARCHAR,"
    "  ZTRYFACTKEEPMILK TIMESTAMP,"
    "  ZDIVERPAINTLEATHEREASY INTEGER,"
    "  ZSORTMISTYQUOTECABBAGE BLOB,"
    "  ZTUNEGASBUFFALOCAPITAL BLOB,"
    "  ZFILLSTOPLAWJOYFUL FLOAT,"
    "  ZSTEELCAREFULPLATENUMBER FLOAT,"
    "  ZGIVEVIVIDDIVINEMEANING INTEGER,"
    "  ZTREATPACKFUTURECONVERT VARCHAR,"
    "  ZCALMLYGEMFINISHEFFECT INTEGER,"
    "  ZCABBAGESOCKEASEMINUTE BLOB,"
    "  ZPLANETFAMILYPUREMEMORY TIMESTAMP,"
    "  ZMERRYCRACKTRAINLEADER BLOB,"
    "  ZMINORWAYPAPERCLASSY TIMESTAMP,"
    "  ZEAGLELINEMINEMAIL VARCHAR,"
    "  ZRESORTYARDGREENLET TIMESTAMP,"
    "  ZYARDOREGANOVIVIDJEWEL TIMESTAMP,"
    "  ZPURECAKEVIVIDNEATLY FLOAT,"
    "  ZASKCONTACTMONITORFUN TIMESTAMP,"
    "  ZMOVEWHOGAMMAINCH VARCHAR,"
    "  ZLETTUCEBIRDMEETDEBATE TIMESTAMP,"
    "  ZGENENATURALHEARINGKITE VARCHAR,"
    "  ZMUFFINDRYERDRAWFORTUNE FLOAT,"
    "  ZGRAYSURVEYWIRELOVE FLOAT,"
    "  ZPLIERSPRINTASKOREGANO INTEGER,"
    "  ZTRAVELDRIVERCONTESTLILY INTEGER,"
    "  ZHUMORSPICESANDKIDNEY TIMESTAMP,"
    "  ZARSENICSAMPLEWAITMUON INTEGER,"
    "  ZLACEADDRESSGROUNDCAREFUL FLOAT,"
    "  ZBAMBOOMESSWASABIEVENING BLOB,"
    "  ZONERELEASEAVERAGENURSE INTEGER,"
    "  ZRADIANTWHENTRYCARD TIMESTAMP,"
    "  ZREWARDINSIDEMANGOINTENSE FLOAT,"
    "  ZNEATSTEWPARTIRON TIMESTAMP,"
    "  ZOUTSIDEPEAHENCOUNTICE TIMESTAMP,"
    "  ZCREAMEVENINGLIPBRANCH FLOAT,"
    "  ZWHALEMATHAVOCADOCOPPER FLOAT,"
    "  ZLIFEUSELEAFYBELL FLOAT,"
    "  ZWEALTHLINENGLEEFULDAY VARCHAR,"
    "  ZFACEINVITETALKGOLD BLOB,"
    "  ZWESTAMOUNTAFFECTHEARING INTEGER,"
    "  ZDELAYOUTCOMEHORNAGENCY INTEGER,"
    "  ZBIGTHINKCONVERTECONOMY BLOB,"
    "  ZBASEGOUDAREGULARFORGIVE TIMESTAMP,"
    "  ZPATTERNCLORINEGRANDCOLBY TIMESTAMP,"
    "  ZCYANBASEFEEDADROIT INTEGER,"
    "  ZCARRYFLOORMINNOWDRAGON TIMESTAMP,"
    "  ZIMAGEPENCILOTHERBOTTOM FLOAT,"
    "  ZXENONFLIGHTPALEAPPLE TIMESTAMP,"
    "  ZHERRINGJOKEFEATUREHOPEFUL FLOAT,"
    "  ZCAPYEARLYRIVETBRUSH FLOAT,"
    "  ZAGEREEDFROGBASKET VARCHAR,"
    "  ZUSUALBODYHALIBUTDIAMOND VARCHAR,"
    "  ZFOOTTAPWORDENTRY VARCHAR,"
    "  ZDISHKEEPBLESTMONITOR FLOAT,"
    "  ZBROADABLESOLIDCASUAL INTEGER,"
    "  ZSQUAREGLEEFULCHILDLIGHT INTEGER,"
    "  ZHOLIDAYHEADPONYDETAIL INTEGER,"
    "  ZGENERALRESORTSKYOPEN TIMESTAMP,"
    "  ZGLADSPRAYKIDNEYGUPPY VARCHAR,"
    "  ZSWIMHEAVYMENTIONKIND BLOB,"
    "  ZMESSYSULFURDREAMFESTIVE BLOB,"
    "  ZSKYSKYCLASSICBRIEF VARCHAR,"
    "  ZDILLASKHOKILEMON FLOAT,"
    "  ZJUNIORSHOWPRESSNOVA FLOAT,"
    "  ZSIZETOEAWARDFRESH TIMESTAMP,"
    "  ZKEYFAILAPRICOTMETAL VARCHAR,"
    "  ZHANDYREPAIRPROTONAIRPORT VARCHAR,"
    "  ZPOSTPROTEINHANDLEACTOR BLOB"
	");");
	speedtest1_exec(zSqlSpeedtest1);
	zSqlPrepare = sqlite3_mprintf("INSERT INTO ZLOOKSLIKECOREDATA(ZPK,ZAIRFORGIVEHEADFROG,"
    "ZGIFTICEFISHGLUEHAIR,ZDELAYOUTCOMEHORNAGENCY,ZSLEEPYUSERGRANDBOWL,"
    "ZGLASSRESERVEBARIUMMEAL,ZBRIEFGOBYDODGERHEIGHT,"
    "ZBAMBOOMESSWASABIEVENING,ZFARMERMORNINGMIRRORCONCERN,"
    "ZTREATPACKFUTURECONVERT,ZCAUSESALAMITERMCYAN,ZCALMRACCOONPROGRAMDEBIT,"
    "ZHOLIDAYHEADPONYDETAIL,ZWOODPOETRYCOBBLERBENCH,ZHAFNIUMSCRIPTSALADMOTOR,"
    "ZUSUALBODYHALIBUTDIAMOND,ZOUTSIDEPEAHENCOUNTICE,ZDIVERPAINTLEATHEREASY,"
    "ZWESTAMOUNTAFFECTHEARING,ZSIZETOEAWARDFRESH,ZDEWPEACHCAREERCELERY,"
    "ZSTEELCAREFULPLATENUMBER,ZCYANBASEFEEDADROIT,ZCALMLYGEMFINISHEFFECT,"
    "ZHANDYREPAIRPROTONAIRPORT,ZGENENATURALHEARINGKITE,ZBROADABLESOLIDCASUAL,"
    "ZPOSTPROTEINHANDLEACTOR,ZLACEADDRESSGROUNDCAREFUL,ZIMAGEPENCILOTHERBOTTOM,"
    "ZPROBLEMCLUBPOPOVERJELLY,ZPATTERNCLORINEGRANDCOLBY,ZNEATSTEWPARTIRON,"
    "ZAPPEALSIMPLESECONDHOUSING,ZMOVEWHOGAMMAINCH,ZTENNISCYCLEBILLOFFICER,"
    "ZSHARKJUSTFRUITMOVIE,ZKEYFAILAPRICOTMETAL,ZCOMPANYSUMMERFIBERELF,"
    "ZTERMFITTINGHOUSINGCOMMAND,ZRESORTYARDGREENLET,ZCABBAGESOCKEASEMINUTE,"
    "ZSQUAREGLEEFULCHILDLIGHT,ZONERELEASEAVERAGENURSE,ZBIGTHINKCONVERTECONOMY,"
    "ZPLIERSPRINTASKOREGANO,ZDECADEJOYOUSWAVEHABIT,ZDRYWALLBEYONDBROWNBOWL,"
    "ZCLUBRELEASELIZARDADVICE,ZWHALEMATHAVOCADOCOPPER,ZBELLYCRASHITEMLACK,"
    "ZLETTUCEBIRDMEETDEBATE,ZCAPABLETRIPDOORALMOND,ZRADIANTWHENTRYCARD,"
    "ZCAPYEARLYRIVETBRUSH,ZAGEREEDFROGBASKET,ZSWIMHEAVYMENTIONKIND,"
    "ZTRAVELDRIVERCONTESTLILY,ZGLADSPRAYKIDNEYGUPPY,ZBANKBUFFALORECOVERORBIT,"
    "ZFINGERDUEPIZZAOPTION,ZCLAMBITARUGULAFAJITA,ZLONGFINLEAVEIMAGEOIL,"
    "ZLONGDIETESSAYNATURE,ZJUNIORSHOWPRESSNOVA,ZHOPEFULGATEHOLECHALK,"
    "ZDEPOSITPAIRCOLLEGECOMET,ZWEALTHLINENGLEEFULDAY,ZFILLSTOPLAWJOYFUL,"
    "ZTUNEGASBUFFALOCAPITAL,ZGRAYSURVEYWIRELOVE,ZCORNERANCHORTAPEDIVER,"
    "ZREWARDINSIDEMANGOINTENSE,ZCADETBRIGHTPLANETBANK,ZPLANETFAMILYPUREMEMORY,"
    "ZTREATTESTQUILLCHARGE,ZCREAMEVENINGLIPBRANCH,ZSKYSKYCLASSICBRIEF,"
    "ZARSENICSAMPLEWAITMUON,ZBROWBALANCEKEYCHOWDER,ZFLYINGDOCTORTABLEMELODY,"
    "ZHANGERLITHIUMDINNERMEET,ZNOTICEPEARPOLICYJUICE,ZSHINYASSISTLIVINGCRAB,"
    "ZLIFEUSELEAFYBELL,ZFACEINVITETALKGOLD,ZGENERALRESORTSKYOPEN,"
    "ZPURECAKEVIVIDNEATLY,ZKIWIVISUALPRIDEAPPLE,ZMESSYSULFURDREAMFESTIVE,"
    "ZCHARGECLICKHUMANEHIRE,ZHERRINGJOKEFEATUREHOPEFUL,ZYARDOREGANOVIVIDJEWEL,"
    "ZFOOTTAPWORDENTRY,ZWISHHITSKINMOTOR,ZBASEGOUDAREGULARFORGIVE,"
    "ZMUFFINDRYERDRAWFORTUNE,ZACTIONRANGEELEGANTNEUTRON,ZTRYFACTKEEPMILK,"
    "ZPEACHCOPPERDINNERLAKE,ZFRAMEENTERSIMPLEMOUTH,ZMERRYCRACKTRAINLEADER,"
    "ZMEMORYREQUESTSOURCEBIG,ZCARRYFLOORMINNOWDRAGON,ZMINORWAYPAPERCLASSY,"
    "ZDILLASKHOKILEMON,ZRESOLVEWRISTWRAPAPPLE,ZASKCONTACTMONITORFUN,"
    "ZGIVEVIVIDDIVINEMEANING,ZEIGHTLEADERWORKERMOST,ZMISSREPLYHUMANLIVING,"
    "ZXENONFLIGHTPALEAPPLE,ZSORTMISTYQUOTECABBAGE,ZEAGLELINEMINEMAIL,"
    "ZFAMILYVISUALOWNERMATTER,ZSPREADMOTORBISCUITBACON,ZDISHKEEPBLESTMONITOR,"
    "ZMALLEQUIPTHANKSGLUE,ZGOLDYOUNGINITIALNOSE,ZHUMORSPICESANDKIDNEY)"
    "VALUES(?1,?26,?20,?93,?8,?33,?3,?81,?28,?60,?18,?47,?109,?29,?30,?104,?86,"
    "?54,?92,?117,?9,?58,?97,?61,?119,?73,?107,?120,?80,?99,?31,?96,?85,?50,?71,"
    "?42,?27,?118,?36,?2,?67,?62,?108,?82,?94,?76,?35,?40,?11,?88,?41,?72,?4,"
    "?83,?102,?103,?112,?77,?111,?22,?13,?34,?15,?23,?116,?7,?5,?90,?57,?56,"
    "?75,?51,?84,?25,?63,?37,?87,?114,?79,?38,?14,?10,?21,?48,?89,?91,?110,"
    "?69,?45,?113,?12,?101,?68,?105,?46,?95,?74,?24,?53,?39,?6,?64,?52,?98,"
	"?65,?115,?49,?70,?59,?32,?44,?100,?55,?66,?16,?19,?106,?43,?17,?78);");
	speedtest1_prepare(zSqlPrepare);

  for(i=0; i<n; i++){
    x1 = speedtest1_random();
    speedtest1_numbername(x1%1000, zNum, sizeof(zNum));
    len = (int)strlen(zNum);
    sqlite3_bind_int(pstmt, 1, i^0xf);
    for(j=0; zType[j]; j++){
      switch( zType[j] ){
        case 'I':
        case 'T':
          sqlite3_bind_int64(pstmt, j+2, x1);
          break;
        case 'F':
          sqlite3_bind_double(pstmt, j+2, (double)x1);
          break;
        case 'V':
        case 'B':
          sqlite3_bind_text64(pstmt, j+2, zNum, len,
                              0, 1);
          break;
      }
    }
    speedtest1_run();
  }
  speedtest1_exec("COMMIT;");
  speedtest1_end_test();

  n = szTest*250;
  zName = sqlite3_mprintf("Query %d rows by rowid", n);
  speedtest1_begin_test(110, zName);
  zSqlPrepare = sqlite3_mprintf("SELECT ZCYANBASEFEEDADROIT,ZJUNIORSHOWPRESSNOVA,ZCAUSESALAMITERMCYAN,"
    "ZHOPEFULGATEHOLECHALK,ZHUMORSPICESANDKIDNEY,ZSWIMHEAVYMENTIONKIND,"
    "ZMOVEWHOGAMMAINCH,ZAPPEALSIMPLESECONDHOUSING,ZHAFNIUMSCRIPTSALADMOTOR,"
    "ZNEATSTEWPARTIRON,ZLONGFINLEAVEIMAGEOIL,ZDEWPEACHCAREERCELERY,"
    "ZXENONFLIGHTPALEAPPLE,ZCALMRACCOONPROGRAMDEBIT,ZUSUALBODYHALIBUTDIAMOND,"
    "ZTRYFACTKEEPMILK,ZWEALTHLINENGLEEFULDAY,ZLONGDIETESSAYNATURE,"
    "ZLIFEUSELEAFYBELL,ZTREATPACKFUTURECONVERT,ZMEMORYREQUESTSOURCEBIG,"
    "ZYARDOREGANOVIVIDJEWEL,ZDEPOSITPAIRCOLLEGECOMET,ZSLEEPYUSERGRANDBOWL,"
    "ZBRIEFGOBYDODGERHEIGHT,ZCLUBRELEASELIZARDADVICE,ZCAPABLETRIPDOORALMOND,"
    "ZDRYWALLBEYONDBROWNBOWL,ZASKCONTACTMONITORFUN,ZKIWIVISUALPRIDEAPPLE,"
    "ZNOTICEPEARPOLICYJUICE,ZPEACHCOPPERDINNERLAKE,ZSTEELCAREFULPLATENUMBER,"
    "ZGLADSPRAYKIDNEYGUPPY,ZCOMPANYSUMMERFIBERELF,ZTENNISCYCLEBILLOFFICER,"
    "ZIMAGEPENCILOTHERBOTTOM,ZWESTAMOUNTAFFECTHEARING,ZDIVERPAINTLEATHEREASY,"
    "ZSKYSKYCLASSICBRIEF,ZMESSYSULFURDREAMFESTIVE,ZMERRYCRACKTRAINLEADER,"
    "ZBROADABLESOLIDCASUAL,ZGLASSRESERVEBARIUMMEAL,ZTUNEGASBUFFALOCAPITAL,"
    "ZBANKBUFFALORECOVERORBIT,ZTREATTESTQUILLCHARGE,ZBAMBOOMESSWASABIEVENING,"
    "ZREWARDINSIDEMANGOINTENSE,ZEAGLELINEMINEMAIL,ZCALMLYGEMFINISHEFFECT,"
    "ZKEYFAILAPRICOTMETAL,ZFINGERDUEPIZZAOPTION,ZCADETBRIGHTPLANETBANK,"
    "ZGOLDYOUNGINITIALNOSE,ZMISSREPLYHUMANLIVING,ZEIGHTLEADERWORKERMOST,"
    "ZFRAMEENTERSIMPLEMOUTH,ZBIGTHINKCONVERTECONOMY,ZFACEINVITETALKGOLD,"
    "ZPOSTPROTEINHANDLEACTOR,ZHERRINGJOKEFEATUREHOPEFUL,ZCABBAGESOCKEASEMINUTE,"
    "ZMUFFINDRYERDRAWFORTUNE,ZPROBLEMCLUBPOPOVERJELLY,ZGIVEVIVIDDIVINEMEANING,"
    "ZGENENATURALHEARINGKITE,ZGENERALRESORTSKYOPEN,ZLETTUCEBIRDMEETDEBATE,"
    "ZBASEGOUDAREGULARFORGIVE,ZCHARGECLICKHUMANEHIRE,ZPLANETFAMILYPUREMEMORY,"
    "ZMINORWAYPAPERCLASSY,ZCAPYEARLYRIVETBRUSH,ZSIZETOEAWARDFRESH,"
    "ZARSENICSAMPLEWAITMUON,ZSQUAREGLEEFULCHILDLIGHT,ZSHINYASSISTLIVINGCRAB,"
    "ZCORNERANCHORTAPEDIVER,ZDECADEJOYOUSWAVEHABIT,ZTRAVELDRIVERCONTESTLILY,"
    "ZFLYINGDOCTORTABLEMELODY,ZSHARKJUSTFRUITMOVIE,ZFAMILYVISUALOWNERMATTER,"
    "ZFARMERMORNINGMIRRORCONCERN,ZGIFTICEFISHGLUEHAIR,ZOUTSIDEPEAHENCOUNTICE,"
    "ZSPREADMOTORBISCUITBACON,ZWISHHITSKINMOTOR,ZHOLIDAYHEADPONYDETAIL,"
    "ZWOODPOETRYCOBBLERBENCH,ZAIRFORGIVEHEADFROG,ZBROWBALANCEKEYCHOWDER,"
    "ZDISHKEEPBLESTMONITOR,ZCLAMBITARUGULAFAJITA,ZPLIERSPRINTASKOREGANO,"
    "ZRADIANTWHENTRYCARD,ZDELAYOUTCOMEHORNAGENCY,ZPURECAKEVIVIDNEATLY,"
    "ZPATTERNCLORINEGRANDCOLBY,ZHANDYREPAIRPROTONAIRPORT,ZAGEREEDFROGBASKET,"
    "ZSORTMISTYQUOTECABBAGE,ZFOOTTAPWORDENTRY,ZRESOLVEWRISTWRAPAPPLE,"
    "ZDILLASKHOKILEMON,ZFILLSTOPLAWJOYFUL,ZACTIONRANGEELEGANTNEUTRON,"
    "ZRESORTYARDGREENLET,ZCREAMEVENINGLIPBRANCH,ZWHALEMATHAVOCADOCOPPER,"
    "ZGRAYSURVEYWIRELOVE,ZBELLYCRASHITEMLACK,ZHANGERLITHIUMDINNERMEET,"
    "ZCARRYFLOORMINNOWDRAGON,ZMALLEQUIPTHANKSGLUE,ZTERMFITTINGHOUSINGCOMMAND,"
    "ZONERELEASEAVERAGENURSE,ZLACEADDRESSGROUNDCAREFUL"
	" FROM ZLOOKSLIKECOREDATA WHERE ZPK=?1;");
  speedtest1_prepare(zSqlPrepare);
  for(i=0; i<n; i++){
    x1 = speedtest1_random()%nRow;
    sqlite3_bind_int(pstmt, 1, x1);
    speedtest1_run();
  }
  speedtest1_end_test();
}

/*
** A testset used for debugging speedtest1 itself.
*/
void testset_debug1(void){
  unsigned i, n;
  unsigned x1, x2;
  char zNum[2000];              /* A number name */

  n = szTest;
  for(i=1; i<=n; i++){
    x1 = swizzle(i, n);
    x2 = swizzle(x1, n);
    speedtest1_numbername(x1, zNum, sizeof(zNum));
    printf("%5d %5d %5d %s\n", i, x1, x2, zNum);
  }
}

int main(){
	
  int doAutovac = 0;            /* True for --autovacuum */
  int cacheSize = 0;            /* Desired cache size.  0 means default */
  int doExclusive = 0;          /* True for --exclusive */
  int nHeap = 0, mnHeap = 0;    /* Heap size from --heap */
  int doIncrvac = 0;            /* True for --incrvacuum */
  const char *zJMode = 0;       /* Journal mode */
  const char *zKey = 0;         /* Encryption key */
  int nLook = -1, szLook = 0;   /* --lookaside configuration */
  int noSync = 0;               /* True for --nosync */
  int pageSize = 0;             /* Desired page size.  0 means default */
  int nPCache = 0, szPCache = 0;/* --pcache configuration */
  int doPCache = 0;             /* True if --pcache is seen */
  int nScratch = 0, szScratch=0;/* --scratch configuration */
  int showStats = 0;            /* True for --stats */
  int nThread = 0;              /* --threads value */
  int mmapSize = 0;             /* How big of a memory map to use */
  const char *zTSet = "main";   /* Which --testset torun */
  int doTrace = 0;              /* True for --trace */
  const char *zEncoding = 0;    /* --utf16be or --utf16le */
  const char *zDbName = 0;      /* Name of the test database */

  void *pHeap = 0;              /* Allocated heap space */
  void *pLook = 0;              /* Allocated lookaside space */
  void *pPCache = 0;            /* Allocated storage for pcache */
  void *pScratch = 0;           /* Allocated storage for scratch */
  int iCur, iHi;                /* Stats values, current and "highwater" */
  int i;                        /* Loop counter */
  int rc;                       /* API return code */

  /* Display the version of SQLite being tested */
  printf("-- Speedtest1 for SQLite %s %.50s\n",
         sqlite3_libversion(), sqlite3_sourceid());

  /* Process command-line arguments */
  zWR = "";
  zNN = "";
  zPK = "UNIQUE";
  szTest = 100;
  nRepeat = 1;
  zDbName = "speedtest1.db";
  if( zDbName!=0 ) _unlink(zDbName);
  if( nHeap>0 ){
    pHeap = malloc( nHeap );
    
    rc = sqlite3_config(8, pHeap, nHeap, mnHeap);
    
  }
  if( doPCache ){
    if( nPCache>0 && szPCache>0 ){
      pPCache = malloc( nPCache*(int)szPCache );
      
    }
    rc = sqlite3_config(7, pPCache, szPCache, nPCache);
    
  }
  if( nScratch>0 && szScratch>0 ){
    pScratch = malloc( nScratch*(int)szScratch );
    
    rc = sqlite3_config(6, pScratch, szScratch, nScratch);
    
  }
  if( nLook>=0 ){
    sqlite3_config(13, 0, 0);
  }
 
  /* Open the database and the input file */
  if( sqlite3_open(zDbName, &db) ){
    
  }
  if( nLook>0 && szLook>0 ){
    pLook = malloc( nLook*szLook );
    rc = sqlite3_db_config(db, 1001, pLook, szLook,nLook);
    
  }

  /* Set database connection options */
  if( doTrace ) sqlite3_trace(db, traceCallback, 0);
  if( mmapSize>0 ){
	  zSqlSpeedtest1 = sqlite3_mprintf("PRAGMA mmap_size=%d", mmapSize);
	  speedtest1_exec(zSqlSpeedtest1);
  }
  zSqlSpeedtest1 = sqlite3_mprintf("PRAGMA threads=%d", nThread);
  speedtest1_exec(zSqlSpeedtest1);
  if( zKey ){
	  zSqlSpeedtest1 = sqlite3_mprintf("PRAGMA key('%s')", zKey);
	  speedtest1_exec(zSqlSpeedtest1);
  }
  if( zEncoding ){
	  zSqlSpeedtest1 = sqlite3_mprintf("PRAGMA encoding=%s", zEncoding);
	  speedtest1_exec(zSqlSpeedtest1);
  }
  if( doAutovac ){
    speedtest1_exec("PRAGMA auto_vacuum=FULL");
  }else if( doIncrvac ){
    speedtest1_exec("PRAGMA auto_vacuum=INCREMENTAL");
  }
  if( pageSize ){
	  zSqlSpeedtest1 = sqlite3_mprintf("PRAGMA page_size=%d", pageSize);
	  speedtest1_exec(zSqlSpeedtest1);
  }
  if( cacheSize ){
	  zSqlSpeedtest1 = sqlite3_mprintf("PRAGMA cache_size=%d", cacheSize);
	  speedtest1_exec(zSqlSpeedtest1);
  }
  if( noSync ) speedtest1_exec("PRAGMA synchronous=OFF");
  if( doExclusive ){
    speedtest1_exec("PRAGMA locking_mode=EXCLUSIVE");
  }
  if( zJMode ){
	  zSqlSpeedtest1 = sqlite3_mprintf("PRAGMA journal_mode=%s", zJMode);
	  speedtest1_exec(zSqlSpeedtest1);
  }

  if( bExplain ) printf(".explain\n.echo on\n");
  if( strcmp(zTSet,"main")==0 ){
    testset_main();
  }else if( strcmp(zTSet,"debug1")==0 ){
    testset_debug1();
  }else if( strcmp(zTSet,"orm")==0 ){
    testset_orm();
  }else if( strcmp(zTSet,"cte")==0 ){
    testset_cte();
  }
  speedtest1_final();

  /* Database connection statistics printed after both prepared statements
  ** have been finalized */
  if( showStats ){
    sqlite3_db_status(db, 0, &iCur, &iHi, 0);
    printf("-- Lookaside Slots Used:        %d (max %d)\n", iCur,iHi);
    sqlite3_db_status(db, 4, &iCur, &iHi, 0);
    printf("-- Successful lookasides:       %d\n", iHi);
    sqlite3_db_status(db, 5, &iCur,&iHi,0);
    printf("-- Lookaside size faults:       %d\n", iHi);
    sqlite3_db_status(db, 6, &iCur,&iHi,0);
    printf("-- Lookaside OOM faults:        %d\n", iHi);
    sqlite3_db_status(db, 1, &iCur, &iHi, 0);
    printf("-- Pager Heap Usage:            %d bytes\n", iCur);
    sqlite3_db_status(db, 7, &iCur, &iHi, 1);
    printf("-- Page cache hits:             %d\n", iCur);
    sqlite3_db_status(db, 8, &iCur, &iHi, 1);
    printf("-- Page cache misses:           %d\n", iCur);
    sqlite3_db_status(db, 9, &iCur, &iHi, 1);
    printf("-- Page cache writes:           %d\n", iCur); 
    sqlite3_db_status(db, 2, &iCur, &iHi, 0);
    printf("-- Schema Heap Usage:           %d bytes\n", iCur); 
    sqlite3_db_status(db, 3, &iCur, &iHi, 0);
    printf("-- Statement Heap Usage:        %d bytes\n", iCur); 
  }

  sqlite3_close(db);

  /* Global memory usage statistics printed after the database connection
  ** has closed.  Memory usage should be zero at this point. */
  if( showStats ){
    sqlite3_status(0, &iCur, &iHi, 0);
    printf("-- Memory Used (bytes):         %d (max %d)\n", iCur,iHi);
    sqlite3_status(9, &iCur, &iHi, 0);
    printf("-- Outstanding Allocations:     %d (max %d)\n", iCur,iHi);
    sqlite3_status(2, &iCur, &iHi, 0);
    printf("-- Pcache Overflow Bytes:       %d (max %d)\n", iCur,iHi);
    sqlite3_status(4, &iCur, &iHi, 0);
    printf("-- Scratch Overflow Bytes:      %d (max %d)\n", iCur,iHi);
    sqlite3_status(5, &iCur, &iHi, 0);
    printf("-- Largest Allocation:          %d bytes\n",iHi);
    sqlite3_status(7, &iCur, &iHi, 0);
    printf("-- Largest Pcache Allocation:   %d bytes\n",iHi);
    sqlite3_status(8, &iCur, &iHi, 0);
    printf("-- Largest Scratch Allocation:  %d bytes\n", iHi);
  }

  /* Release memory */
  free( pLook );
  free( pPCache );
  free( pScratch );
  free( pHeap );
  return 0;
}
