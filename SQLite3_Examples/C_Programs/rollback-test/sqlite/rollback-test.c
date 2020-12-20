/*
** This program is used to generate and verify databases with hot journals.
** Use this program to generate a hot journal on one machine and verify
** that it rolls back correctly on another machine with a different
** architecture.
**
** Usage:
**
**     rollback-test new [-utf8] [-utf16le] [-utf16be] [-pagesize=N] DATABASE
**     rollback-test check DATABASE
**     rollback-test crash [-wal] [-rollback] DATABASE
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
sqlite3 *db;
static void usage(char *argv0){
  fprintf(stderr,
    "Usage: %s new [-utf8] [-utf16le] [-utf16be] [-pagesize=N] DATABASE\n"
    "       %s check DATABASE\n"
    "       %s crash [-wal] DATABASE\n",
    argv0, argv0, argv0
  );
  exit(1);
}

static sqlite3 *openDb(const char *zFilename){
  int rc;
  
  rc = sqlite3_open(zFilename, &db);
  if( rc ){
    fprintf(stderr, "Cannot open \"%s\": %s\n",
            zFilename, sqlite3_errmsg(db));
    sqlite3_close(db);
    //exit(1);
  }
  return db;
}

static int nReply = 0;
static char zReply[1000];

static int execCallback(void *NotUsed, int nArg, char **azArg, char **azCol){
  int i, n;
  char *z;
  for(i=0; i<nArg; i++){
    z = azArg[i];
    if( z==0 ) z = "NULL";
    if( nReply>0 && nReply<sizeof(zReply)-1 ) zReply[nReply++] = ' ';
    n = strlen(z);
    if( nReply+n>=sizeof(zReply)-1 ) n = sizeof(zReply) - nReply - 1;
    memcpy(&zReply[nReply], z, n);
    nReply += n;
    zReply[nReply] = 0;
  }
  return 0;
}

static void runSql( const char *zSql){
  char *zErr = 0;
  int rc;
  nReply = 0;
  rc = sqlite3_exec(db,zSql, execCallback, 0, &zErr);
  if( zErr ){
    //fprintf(stderr, "SQL error: %s\n", zErr);
    //exit(1);
  }
  if( rc ){
    //fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    //exit(1);
  }
}

int main(){
  int i;

  
    db = openDb("DATABASE");
	runSql( "PRAGMA encoding=UTF8");
    runSql(
       "BEGIN;"
       "CREATE TABLE t1(x INTEGER PRIMARY KEY, y);"
       "INSERT INTO t1(y) VALUES('abcdefghijklmnopqrstuvwxyz');"
       "INSERT INTO t1(y) VALUES('abcdefghijklmnopqrstuvwxyz');"
       "INSERT INTO t1(y) SELECT y FROM t1;" /* 4 */
       "INSERT INTO t1(y) SELECT y FROM t1;" /* 8 */
       "INSERT INTO t1(y) SELECT y FROM t1;" /* 16 */
       "INSERT INTO t1(y) SELECT y FROM t1;" /* 32 */
       "INSERT INTO t1(y) SELECT y FROM t1;" /* 64 */
       "INSERT INTO t1(y) SELECT y FROM t1;" /* 128 */
       "INSERT INTO t1(y) SELECT y FROM t1;" /* 256 */
       "INSERT INTO t1(y) SELECT y FROM t1;" /* 512 */
       "INSERT INTO t1(y) SELECT y FROM t1;" /* 1024 */
       "UPDATE t1 SET y=(y || x);"
       "CREATE INDEX t1y ON t1(y);"
       "COMMIT;"
    );
    sqlite3_close(db);
 
  
    db = openDb("DATABASE");
    runSql( "PRAGMA integrity_check");
    if( strcmp(zReply, "ok")!=0 ){
      fprintf(stderr, "Integrity check: %s\n", zReply);
      exit(1);
    }
    runSql( 
      "SELECT count(*) FROM t1 WHERE y<>('abcdefghijklmnopqrstuvwxyz' || x)"
    );
    if( strcmp(zReply, "0")!=0 ){
      fprintf(stderr, "Wrong content\n");
      exit(1);
    }
    printf("Ok\n");

	db = openDb("DATABASE");
	runSql("PRAGMA journal_mode=WAL");
    runSql(
      "PRAGMA cache_size=10;"
      "BEGIN;"
      "UPDATE t1 SET y=(y || -x)"
    );
	printf("Ok1\n");
  return 0;
}
