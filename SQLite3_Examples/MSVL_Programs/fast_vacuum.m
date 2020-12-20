/*</
define p:sqlite3_mprintf_call=1;
define q:sqlite3_free_call=1;
alw(p->som(q))
/>*/

</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

frame(pStmt1,pStmt2,db) and (
 function vacuumFinalize1 (  )
 {
     frame(vacuumFinalize1_rc,vacuumFinalize1_1_temp$_1) and ( 
     db:=sqlite3_db_handle(pStmt1,RValue);
     int vacuumFinalize1_rc and skip;
     vacuumFinalize1_rc:=sqlite3_finalize(pStmt1,RValue);
     if(vacuumFinalize1_rc) then 
     {
         int vacuumFinalize1_1_temp$_1 and skip;
         vacuumFinalize1_1_temp$_1:=sqlite3_errmsg(db,RValue);
         fprintf(stderr,"finalize error: %s\n",vacuumFinalize1_1_temp$_1) and skip
         
     }
     else 
     {
          skip 
     }
     )
     }; 
  function vacuumFinalize2 (  )
 {
     frame(vacuumFinalize2_rc,vacuumFinalize2_1_temp$_1) and ( 
     db:=sqlite3_db_handle(pStmt2,RValue);
     int vacuumFinalize2_rc and skip;
     vacuumFinalize2_rc:=sqlite3_finalize(pStmt2,RValue);
     if(vacuumFinalize2_rc) then 
     {
         int vacuumFinalize2_1_temp$_1 and skip;
         vacuumFinalize2_1_temp$_1:=sqlite3_errmsg(db,RValue);
         fprintf(stderr,"finalize error: %s\n",vacuumFinalize2_1_temp$_1) and skip
     }
     else 
     {
          skip 
     }
     )
     }; 
  function execSql ( char *zSql )
 {
     frame(execSql_2_temp$_1) and ( 
     pStmt1:=NULL;
     if(!zSql) then 
     {
         fprintf(stderr,"out of memory!\n") and skip
     }
     else 
     {
          skip 
     };
	 printf("%s;\n", zSql) and skip;
     if(0!=sqlite3_prepare(db,zSql,-1,&pStmt1,0,RValue)) then 
     {
         int execSql_2_temp$_1 and skip;
         execSql_2_temp$_1:=sqlite3_errmsg(db,RValue);
         fprintf(stderr,"Error: %s\n",execSql_2_temp$_1) and skip
     }
     else 
     {
          skip 
     };
     sqlite3_step(pStmt1,RValue) and skip;
     vacuumFinalize1()
     )
     }; 
  function execExecSql ( char *zSql )
 {
     frame(execExecSql_rc,execExecSql_1_temp$_1,execExecSql_2_temp$_2) and ( 
     pStmt2:=NULL;
     int execExecSql_rc and skip;
	 printf("%s;\n", zSql) and skip;
     execExecSql_rc:=sqlite3_prepare(db,zSql,-1,&pStmt2,0,RValue);
     if(execExecSql_rc!=0) then 
     {
         int execExecSql_1_temp$_1 and skip;
         execExecSql_1_temp$_1:=sqlite3_errmsg(db,RValue);
         fprintf(stderr,"Error: %s\n",execExecSql_1_temp$_1) and skip
         
     }
     else 
     {
          skip 
     };
     while(100=sqlite3_step(pStmt2,RValue))
     {
         int execExecSql_2_temp$_2 and skip;
         execExecSql_2_temp$_2:=sqlite3_column_text(pStmt2,0,RValue);
         execSql((char *)execExecSql_2_temp$_2)
     };
     vacuumFinalize2()
     )
     }; 
 function main ( int RValue )
 {
     frame(verifystat,main_rc,main_r,main_zDbToVacuum,main_zBackupDb,main_zTempDb,main_zSql,main_1_temp$_1,return) and (
     int return<==0 and skip;
     int main_rc and skip;
     int main_r and skip;
     char *main_zDbToVacuum and skip;
     char *main_zBackupDb and skip;
     char *main_zTempDb and skip;
     char *main_zSql and skip;
     main_zDbToVacuum:="fast_vacuum.db";
     output ("-- open database file \"",main_zDbToVacuum,"\"\n") and skip;
     main_rc:=sqlite3_open(main_zDbToVacuum,&db,RValue);
	 int verifystat<==0 and skip;
	 while(verifystat<742536)
	 {
		verifystat:=verifystat+1
	 };
     if(main_rc) then 
     {
         int main_1_temp$_1 and skip;
         main_1_temp$_1:=sqlite3_errstr(main_rc,RValue);
         fprintf(stderr,"%s: %s\n",main_zDbToVacuum,main_1_temp$_1) and skip;
         return<==1 and RValue:=1;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         sqlite3_randomness(4,&main_r,RValue) and skip;
         main_zTempDb:=sqlite3_mprintf("%s-vacuum-%016llx",main_zDbToVacuum,main_r,RValue);
         main_zBackupDb:=sqlite3_mprintf("%s-backup-%016llx",main_zDbToVacuum,main_r,RValue);
         main_zSql:=sqlite3_mprintf("ATTACH '%q' AS vacuum_db;",main_zTempDb,RValue);
         execSql(main_zSql);
         sqlite3_free(main_zSql,RValue) and skip;
         execSql("PRAGMA writable_schema=ON");
         execSql("BEGIN");
         execExecSql("SELECT 'CREATE TABLE vacuum_db.' || substr(sql,14)   FROM sqlite_master WHERE type='table' AND name!='sqlite_sequence'   AND rootpage>0");
         execExecSql("SELECT 'CREATE INDEX vacuum_db.' || substr(sql,14)  FROM sqlite_master WHERE sql LIKE 'CREATE INDEX %'");
         execExecSql("SELECT 'CREATE UNIQUE INDEX vacuum_db.' || substr(sql,21)   FROM sqlite_master WHERE sql LIKE 'CREATE UNIQUE INDEX %'");
         execExecSql("SELECT 'INSERT INTO vacuum_db.' || quote(name) || ' SELECT * FROM main.' || quote(name) FROM main.sqlite_master WHERE type = 'table' AND name!='sqlite_sequence'   AND rootpage>0");
         execExecSql("SELECT 'DELETE FROM vacuum_db.' || quote(name) FROM vacuum_db.sqlite_master WHERE name='sqlite_sequence'");
         execExecSql("SELECT 'INSERT INTO vacuum_db.' || quote(name) || ' SELECT * FROM main.' || quote(name) FROM vacuum_db.sqlite_master WHERE name=='sqlite_sequence'");
         execSql("INSERT INTO vacuum_db.sqlite_master   SELECT type, name, tbl_name, rootpage, sql    FROM main.sqlite_master   WHERE type='view' OR type='trigger'      OR (type='table' AND rootpage=0)");
         execSql("COMMIT");
         output ("-- close database\n") and skip;
         sqlite3_close(db,RValue) and skip;
		 printf("-- rename \"%s\" to \"%s\"\n", main_zDbToVacuum, main_zBackupDb) and skip;
         rename(main_zDbToVacuum,main_zBackupDb) and skip;
		 printf("-- rename \"%s\" to \"%s\"\n", main_zTempDb, main_zDbToVacuum) and skip;
         rename(main_zTempDb,main_zDbToVacuum) and skip;
         _unlink(main_zBackupDb) and skip;
         sqlite3_free(main_zTempDb,RValue) and skip;
         sqlite3_free(main_zBackupDb,RValue) and skip;
         return<==1 and RValue:=0;
         skip
     }
     else
     {
         skip
     }
     )
 };
  main(RValue)
 )

