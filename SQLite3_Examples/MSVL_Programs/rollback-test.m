</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

frame(db,nReply,zReply) and (
 function usage ( char *argv0 )
 {
     fprintf(stderr,"Usage: %s new [-utf8] [-utf16le] [-utf16be] [-pagesize=N] DATABASE\n       %s check DATABASE\n       %s crash [-wal] DATABASE\n",argv0,argv0,argv0) and skip
     
 };
 function openDb ( char *zFilename,struct sqlite3* RValue )
 {
     frame(openDb_rc,openDb_1_temp$_1,return) and ( 
     int return<==0 and skip;
     int openDb_rc and skip;
     openDb_rc:=sqlite3_open(zFilename,&db,RValue);
     if(openDb_rc) then 
     {
         int openDb_1_temp$_1 and skip;
         openDb_1_temp$_1:=sqlite3_errmsg(db,RValue);
         fprintf(stderr,"Cannot open \"%s\": %s\n",zFilename,openDb_1_temp$_1) and skip;
         sqlite3_close(db,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     return<==1 and RValue:=db;
     skip
     )
     }; 
      int nReply<==0 and skip;
     char zReply[1000] and skip;
 function callback ( void *NotUsed,int nArg,char **azArg,char **azCol,int RValue )
 {
     frame(execCallback_i,execCallback_n,execCallback_z,return) and ( 
     int return<==0 and skip;
     int execCallback_i,execCallback_n and skip;
     char *execCallback_z and skip;
     execCallback_i:=0;
     
     while(execCallback_i<nArg)
     {
         execCallback_z:=azArg[execCallback_i];
         if(execCallback_z=0) then 
         {
             execCallback_z:="NULL"
         }
         else 
         {
              skip 
         };
         if(nReply>0 AND nReply<1000-1) then 
         {
             zReply[nReply]:=' ';
             nReply:=nReply+1
         }
         else 
         {
              skip 
         };
         execCallback_n:=strlen(execCallback_z);
         if(nReply+execCallback_n>=1000-1) then 
         {
             execCallback_n:=1000-nReply-1
         }
         else 
         {
              skip 
         };
         memcpy(&zReply[nReply],execCallback_z,execCallback_n) and skip;
         nReply:=nReply+execCallback_n;
         zReply[nReply]:=0;
         execCallback_i:=execCallback_i+1
         
     };
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function runSql ( char *zSql )
 {
     frame(runSql_zErr,runSql_rc) and ( 
     char *runSql_zErr<==0 and skip;
     int runSql_rc and skip;
     nReply:=0;
     runSql_rc:=sqlite3_exec(db,zSql,callback,0,&runSql_zErr,RValue);
     if(runSql_zErr) then 
     {
         skip
         
     }
     else 
     {
          skip 
     };
     if(runSql_rc) then 
     {
         skip
         
     }
     else 
     {
          skip 
     }
     )
     }; 
  function main ( int RValue )
 {
     frame(main_i,return,verifystat) and (
     int return<==0 and skip;
     int main_i and skip;
     db:=openDb("DATABASE",RValue);
     runSql("PRAGMA encoding=UTF8");
     runSql("BEGIN;CREATE TABLE t1(x INTEGER PRIMARY KEY, y);INSERT INTO t1(y) VALUES('abcdefghijklmnopqrstuvwxyz');INSERT INTO t1(y) VALUES('abcdefghijklmnopqrstuvwxyz');INSERT INTO t1(y) SELECT y FROM t1;INSERT INTO t1(y) SELECT y FROM t1;INSERT INTO t1(y) SELECT y FROM t1;INSERT INTO t1(y) SELECT y FROM t1;INSERT INTO t1(y) SELECT y FROM t1;INSERT INTO t1(y) SELECT y FROM t1;INSERT INTO t1(y) SELECT y FROM t1;INSERT INTO t1(y) SELECT y FROM t1;INSERT INTO t1(y) SELECT y FROM t1;UPDATE t1 SET y=(y || x);CREATE INDEX t1y ON t1(y);COMMIT;");
     sqlite3_close(db,RValue) and skip;
     db:=openDb("DATABASE",RValue);
     runSql("PRAGMA integrity_check");
	 int verifystat<==0 and skip;
	 while(verifystat<13540892)
	 {
		verifystat:=verifystat+1
	 };
     if(strcmp(zReply,"ok")!=0) then 
     {
         fprintf(stderr,"Integrity check: %s\n",zReply) and skip
     }
     else 
     {
          skip 
     };
     runSql("SELECT count(*) FROM t1 WHERE y<>('abcdefghijklmnopqrstuvwxyz' || x)");
     if(strcmp(zReply,"0")!=0) then 
     {
         fprintf(stderr,"Wrong content\n") and skip
         
     }
     else 
     {
          skip 
     };
     output ("Ok\n") and skip;
     db:=openDb("DATABASE",RValue);
     runSql("PRAGMA journal_mode=WAL");
     runSql("PRAGMA cache_size=10;BEGIN;UPDATE t1 SET y=(y || -x)");
     output ("Ok1\n") and skip;
     return<==1 and RValue:=0;
     skip
     )
 };
  main(RValue)
 )
