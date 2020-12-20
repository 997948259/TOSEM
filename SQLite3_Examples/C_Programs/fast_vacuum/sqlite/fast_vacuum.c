/*
** 2013-10-01
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
** This program implements a high-speed version of the VACUUM command.
** It repacks an SQLite database to remove as much unused space as
** possible and to relocate content sequentially in the file.
**
** This program runs faster and uses less temporary disk space than the
** built-in VACUUM command.  On the other hand, this program has a number
** of important restrictions relative to the built-in VACUUM command.
**
**  (1)  The caller must ensure that no other processes are accessing the
**       database file while the vacuum is taking place.  The usual SQLite
**       file locking is insufficient for this.  The caller must use
**       external means to make sure only this one routine is reading and
**       writing the database.
**
**  (2)  Database reconfiguration such as page size or auto_vacuum changes
**       are not supported by this utility.
**
**  (3)  The database file might be renamed if a power loss or crash
**       occurs at just the wrong moment.  Recovery must be prepared to
**       to deal with the possibly changed filename.
**
** This program is intended as a *Demonstration Only*.  The intent of this
** program is to provide example code that application developers can use
** when creating similar functionality in their applications.
**
** To compile this program:
**
**     cc fast_vacuum.c sqlite3.c
**
** Add whatever linker options are required.  (Example: "-ldl -lpthread").
** Then to run the program:
**
**    ./a.out file-to-vacuum
**
*/
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

/*
** Finalize a prepared statement.  If an error has occurred, print the
** error message and exit.
*/
sqlite3_stmt *pStmt1;
sqlite3_stmt *pStmt2;
sqlite3 *db;
static void vacuumFinalize1(){
  db = sqlite3_db_handle(pStmt1);
  int rc = sqlite3_finalize(pStmt1);
  if( rc ){
    fprintf(stderr, "finalize error: %s\n", sqlite3_errmsg(db));
    exit(1);
  }
}

static void vacuumFinalize2(){
	db = sqlite3_db_handle(pStmt2);
	int rc = sqlite3_finalize(pStmt2);
	if (rc){
		fprintf(stderr, "finalize error: %s\n", sqlite3_errmsg(db));
		exit(1);
	}
}

/*
** Execute zSql on database db. The SQL text is printed to standard
** output.  If an error occurs, print an error message and exit the
** process.
*/
static void execSql(const char *zSql){
  pStmt1=NULL;
  if( !zSql ){
    fprintf(stderr, "out of memory!\n");
    exit(1);
  }
  printf("%s;\n", zSql);
  if (SQLITE_OK != sqlite3_prepare(db, zSql, -1, &pStmt1, 0)){
    fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
    exit(1);
  }
  sqlite3_step(pStmt1);
  vacuumFinalize1();
}

/*
** Execute zSql on database db. The zSql statement returns exactly
** one column. Execute this return value as SQL on the same database.
**
** The zSql statement is printed on standard output prior to being
** run.  If any errors occur, an error is printed and the process
** exits.
*/
static void execExecSql(const char *zSql){
	pStmt2 = NULL;
  int rc;

  printf("%s;\n", zSql);
  rc = sqlite3_prepare(db, zSql, -1, &pStmt2, 0);
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
    exit(1);
  }
  while (SQLITE_ROW == sqlite3_step(pStmt2)){
	  execSql((char*)sqlite3_column_text(pStmt2, 0));
  }
  vacuumFinalize2();
}


int main(){
  int rc;                      /* Return code from SQLite interface calls */
  int r;            /* A random number */
  const char *zDbToVacuum;     /* Database to be vacuumed */
  char *zBackupDb;             /* Backup copy of the original database */
  char *zTempDb;               /* Temporary database */
  char *zSql;                  /* An SQL statement */

  /* Identify the database file to be vacuumed and open it.
  */
  zDbToVacuum = "fast_vacuum.db";
  printf("-- open database file \"%s\"\n", zDbToVacuum);
  rc = sqlite3_open(zDbToVacuum, &db);
  if( rc ){
    fprintf(stderr, "%s: %s\n", zDbToVacuum, sqlite3_errstr(rc));
    return 1;
  }

  /* Create names for two other files.  zTempDb will be a new database
  ** into which we construct a vacuumed copy of zDbToVacuum.  zBackupDb
  ** will be a new name for zDbToVacuum after it is vacuumed.
  */
  sqlite3_randomness(sizeof(r), &r);
  zTempDb = sqlite3_mprintf("%s-vacuum-%016llx", zDbToVacuum, r);
  zBackupDb = sqlite3_mprintf("%s-backup-%016llx", zDbToVacuum, r);

  /* Attach the zTempDb database to the database connection.
  */
  zSql = sqlite3_mprintf("ATTACH '%q' AS vacuum_db;", zTempDb);
  execSql(zSql);
  sqlite3_free(zSql);

  /* TODO:
  ** Set the page_size and auto_vacuum mode for zTempDb here, if desired.
  */

  /* The vacuum will occur inside of a transaction.  Set writable_schema
  ** to ON so that we can directly update the sqlite_master table in the
  ** zTempDb database.
  */
  execSql("PRAGMA writable_schema=ON");
  execSql("BEGIN");


  /* Query the schema of the main database. Create a mirror schema
  ** in the temporary database.
  */
  execExecSql(
      "SELECT 'CREATE TABLE vacuum_db.' || substr(sql,14) "
      "  FROM sqlite_master WHERE type='table' AND name!='sqlite_sequence'"
      "   AND rootpage>0"
  );
  execExecSql(
      "SELECT 'CREATE INDEX vacuum_db.' || substr(sql,14)"
      "  FROM sqlite_master WHERE sql LIKE 'CREATE INDEX %'"
  );
  execExecSql(
      "SELECT 'CREATE UNIQUE INDEX vacuum_db.' || substr(sql,21) "
      "  FROM sqlite_master WHERE sql LIKE 'CREATE UNIQUE INDEX %'"
  );

  /* Loop through the tables in the main database. For each, do
  ** an "INSERT INTO vacuum_db.xxx SELECT * FROM main.xxx;" to copy
  ** the contents to the temporary database.
  */
  execExecSql(
      "SELECT 'INSERT INTO vacuum_db.' || quote(name) "
      "|| ' SELECT * FROM main.' || quote(name) "
      "FROM main.sqlite_master "
      "WHERE type = 'table' AND name!='sqlite_sequence' "
      "  AND rootpage>0"
  );

  /* Copy over the sequence table
  */
  execExecSql(
      "SELECT 'DELETE FROM vacuum_db.' || quote(name) "
      "FROM vacuum_db.sqlite_master WHERE name='sqlite_sequence'"
  );
  execExecSql(
      "SELECT 'INSERT INTO vacuum_db.' || quote(name) "
      "|| ' SELECT * FROM main.' || quote(name) "
      "FROM vacuum_db.sqlite_master WHERE name=='sqlite_sequence'"
  );

  /* Copy the triggers, views, and virtual tables from the main database
  ** over to the temporary database.  None of these objects has any
  ** associated storage, so all we have to do is copy their entries
  ** from the SQLITE_MASTER table.
  */
  execSql(
      "INSERT INTO vacuum_db.sqlite_master "
      "  SELECT type, name, tbl_name, rootpage, sql"
      "    FROM main.sqlite_master"
      "   WHERE type='view' OR type='trigger'"
      "      OR (type='table' AND rootpage=0)"
  );

  /* Commit the transaction and close the database
  */
  execSql("COMMIT");
  printf("-- close database\n");
  sqlite3_close(db);


  /* At this point, zDbToVacuum is unchanged.  zTempDb contains a
  ** vacuumed copy of zDbToVacuum.  Rearrange filenames so that
  ** zTempDb becomes thenew zDbToVacuum.
  */
  printf("-- rename \"%s\" to \"%s\"\n", zDbToVacuum, zBackupDb);
  rename(zDbToVacuum, zBackupDb);
  printf("-- rename \"%s\" to \"%s\"\n", zTempDb, zDbToVacuum);
  rename(zTempDb, zDbToVacuum);
  _unlink(zBackupDb);
  /* Release allocated memory */
  sqlite3_free(zTempDb);
  sqlite3_free(zBackupDb);
  return 0;
}
