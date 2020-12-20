</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

function execSql ( int threadId,char *sql,int RValue )
 {
     frame(execSql_rc,return) and ( 
     int return<==0 and skip;
     int execSql_rc<==0 and skip;
     if(db=NULL) then 
     {
         return<==1 and RValue:=1;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         execSql_rc:=sqlite3_exec(db,sql,NULL,0,NULL,RValue);
         if(execSql_rc AND (execSql_rc!=19)) then 
         {
             output ("Error ",execSql_rc," (",sqlite3_errmsg(db,RValue),") Query:",sql,"\n") and skip
             
         }
         else 
         {
              skip 
         };
         return<==1 and RValue:=execSql_rc;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function openDatabase ( int threadId,char *databaseName,int RValue )
 {
     frame(openDatabase_rc,openDatabase_1_pragma,openDatabase_1_3_timeOut,return) and ( 
     int return<==0 and skip;
     int openDatabase_rc and skip;
     openDatabase_rc:=sqlite3_open(databaseName,&db,RValue);
	 sqlite3_exec(db,"create table busy(thread INT, sequence INT)",NULL,NULL,NULL,RValue) and skip;
     if(openDatabase_rc=0) then 
     {
         char *openDatabase_1_pragma<=="PRAGMA journal_mode = WAL;PRAGMA foreign_keys = ON;" and skip;
         openDatabase_rc:=sqlite3_exec(db,openDatabase_1_pragma,NULL,0,NULL,RValue);
         if(openDatabase_rc!=0) then 
         {
             output (sqlite3_errmsg(db,RValue)," (",databaseName,")",")") and skip
         }
         else
         {
             int openDatabase_1_3_timeOut<==10*200 and skip;
             if(openDatabase_1_3_timeOut<2000) then 
             {
                 openDatabase_1_3_timeOut:=2000
                 
             }
             else 
             {
                  skip 
             };
             output ("Busy time out set to ",openDatabase_1_3_timeOut,"\n") and skip;
             openDatabase_rc:=sqlite3_busy_timeout(db,openDatabase_1_3_timeOut,RValue)
         }
         
     }
     else
     {
         output ("CAN'T OPEN DATABASE ",databaseName," - ",sqlite3_errstr(openDatabase_rc,RValue)) and skip
     };
     return<==1 and RValue:=openDatabase_rc;
     skip
     )
     }; 
  function stress ( int threadId,int inserts,int RValue )
 {
     frame(stress_rc,stress_insert,stress_query,stress_count,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     int stress_rc<==0 and skip;
     char *stress_insert<=="insert into busy (thread, sequence) values (%d,%d);" and skip;
     char stress_query[1000] and skip;
     int stress_count and skip;
     execSql(threadId,"BEGIN IMMEDIATE",RValue);
     break$<==0 and skip;
     stress_count:=1;
     
     while( break$=0 AND  stress_count<=inserts)
     {
         sprintf(stress_query,stress_insert,threadId,stress_count) and skip;
         stress_rc:=execSql(threadId,stress_query,RValue);
         if(stress_rc!=0) then 
         {
             output ("Aborting thread ",threadId," after ",stress_count," iterations\n") and skip;
             break$<==1 and skip
              
         }
         else 
         {
              skip 
         };
         if(break$=0)   then
         {
             stress_count:=stress_count+1
         }
         else
         {
             skip
         }
         
     };
     break$<==0 and skip;
     execSql(threadId,"COMMIT",RValue);
     return<==1 and RValue:=stress_rc;
     skip
     )
     }; 
  function delete ( int threadId,int RValue )
 {
     frame(delete_rc,delete_delete,delete_count,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     int delete_rc<==0 and skip;
     char *delete_delete<=="delete from busy;" and skip;
     int delete_count and skip;
     break$<==0 and skip;
     delete_count:=1;
     
     while( break$=0 AND  delete_count<=5)
     {
         Sleep(1) and skip;
         execSql(threadId,"BEGIN IMMEDIATE",RValue);
         delete_rc:=execSql(threadId,delete_delete,RValue);
         execSql(threadId,"COMMIT",RValue);
         if(delete_rc!=0) then 
         {
             output ("Aborting thread DELETE after ",delete_count," iterations\n") and skip;
             break$<==1 and skip
              
         }
         else 
         {
              skip 
         };
         if(break$=0)   then
         {
             delete_count:=delete_count+1
         }
         else
         {
             skip
         }
         
     };
     break$<==0 and skip;
     return<==1 and RValue:=delete_rc;
     skip
     )
     }; 
  function busyThread ( int busyThread_threadId )
 {
	
     frame(busyThread_rc) and ( 
     int busyThread_rc and skip;
	 
     busyThread_rc:=openDatabase(busyThread_threadId,"../busy.db3",RValue);
	 
     sqlite3_exec(db,"create table busy(thread INT, sequence INT)",NULL,NULL,NULL,RValue) and skip;
     
	 if(busyThread_rc=0) then 
     {
         output ("Thread ",busyThread_threadId," started\n") and skip;
         if(busyThread_threadId=1) then 
         {
             busyThread_rc:=delete(busyThread_threadId,RValue)
             
         }
         else
         {
             busyThread_rc:=stress(busyThread_threadId,1000,RValue)
         };
         output ("Thread ",busyThread_threadId," finished\n") and skip
         
     }
     else 
     {
          skip 
     }
     )
     }; 
frame(main_threads,verifystat,main_rc,main_threadParam,return,aux) and (
     int return<==0 and skip;
     int main_threads and skip;
     int main_rc and skip;
     int main_threadParam[10] and skip;
     main_threads:=0;
     int verifystat<==0 and skip;
	 while(verifystat<3506000)
	 {
		verifystat:=verifystat+1
	 };
     while(main_threads<10)
     {
         main_threadParam[main_threads]:=main_threads+1;
         //pthread_create(&aux[main_threads],NULL,(void *)&busyThread,(void *)&main_threadParam[main_threads],RValue) and skip;
		 busyThread(main_threadParam[main_threads]);
         main_threads:=main_threads+1
         
     };
     main_threads:=0;
     /*while(main_threads<10)
     {
         pthread_join(aux[main_threads],NULL,RValue) and skip;
		 output("bbb") and skip;
         main_threads:=main_threads+1
         
     };*/
     return<==1 and skip;
     skip
     )