</
define p:sqlite3_column_bytes_call=1;
define q:sqlite3_column_blob_call=1;
alw(p->q)
/>


frame(zArgv0,nDb,pFirstDb,nSql,pFirstSql,zTestName,stmt,db) and (
struct Blob {
struct Blob *pNext and 
int id and 
int seq and 
int sz and 
char a[1] 
};
char *zArgv0 and skip;
int nDb and skip;
Blob *pFirstDb and skip;
int nSql and skip;
Blob *pFirstSql and skip;
char zTestName[100] and skip;
 function progressHandler ( void *pVdbeLimitFlag,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=1;
     skip
     )
     }; 
 function blobListLoadFromDb ( char *zSql,int onlyId,int *pN,Blob **ppList )
 {
     frame(blobListLoadFromDb_head$,blobListLoadFromDb_p,blobListLoadFromDb_n,blobListLoadFromDb_rc,blobListLoadFromDb_z2,blobListLoadFromDb_3_sz,blobListLoadFromDb_3_pNew,blobListLoadFromDb_3_temp$_1) and ( 
	 Blob blobListLoadFromDb_head$ and skip;
     Blob *blobListLoadFromDb_p and skip;
     int blobListLoadFromDb_n<==0 and skip;
     int blobListLoadFromDb_rc and skip;
     char *blobListLoadFromDb_z2 and skip;
	 
     if(onlyId>0) then 
     {
         blobListLoadFromDb_z2:=sqlite3_mprintf("%s WHERE rowid=%d",zSql,onlyId,RValue)
         
     }
     else
     {
         blobListLoadFromDb_z2:=sqlite3_mprintf("%s",zSql,RValue)
     };
     blobListLoadFromDb_rc:=sqlite3_prepare_v2(db,blobListLoadFromDb_z2,-1,&stmt,0,RValue);
     sqlite3_free(blobListLoadFromDb_z2,RValue) and skip;
	 
     blobListLoadFromDb_head$.pNext:=0;
     blobListLoadFromDb_p:=&blobListLoadFromDb_head$;
	 
     while(100=sqlite3_step(stmt,RValue))
     {
         int blobListLoadFromDb_3_sz and skip;
         blobListLoadFromDb_3_sz:=sqlite3_column_bytes(stmt,1,RValue);
         Blob *blobListLoadFromDb_3_pNew and skip;
         blobListLoadFromDb_3_pNew:=safe_realloc(0,20+blobListLoadFromDb_3_sz,RValue);
         blobListLoadFromDb_3_pNew->id:=sqlite3_column_int(stmt,0,RValue);
         blobListLoadFromDb_3_pNew->sz:=blobListLoadFromDb_3_sz;
         blobListLoadFromDb_3_pNew->seq:=blobListLoadFromDb_n;
         blobListLoadFromDb_n:=blobListLoadFromDb_n+1;
         blobListLoadFromDb_3_pNew->pNext:=0;
         int blobListLoadFromDb_3_temp$_1 and skip;
         blobListLoadFromDb_3_temp$_1:=sqlite3_column_blob(stmt,1,RValue);
         memcpy(blobListLoadFromDb_3_pNew->a,blobListLoadFromDb_3_temp$_1,blobListLoadFromDb_3_sz) and skip;
         blobListLoadFromDb_3_pNew->a[blobListLoadFromDb_3_sz]:=0;
         blobListLoadFromDb_p->pNext:=blobListLoadFromDb_3_pNew;
         blobListLoadFromDb_p:=blobListLoadFromDb_3_pNew
     };
	 
     sqlite3_finalize(stmt,RValue) and skip;
     * pN:=blobListLoadFromDb_n;
     * ppList:=blobListLoadFromDb_head$.pNext
     )
     }; 
  function blobListFree ( Blob *p )
 {
     frame(blobListFree_pNext) and ( 
     Blob *blobListFree_pNext and skip;
     while(p)
     {
         blobListFree_pNext:=p->pNext;
         free(p) and skip;
         p:=blobListFree_pNext
     }
     )
     }; 
  function runSql ( char *zSql,int runFlags )
 {
     frame(runSql_zMore,pstmt,runSql_1_3_z,runSql_1_3_n,runSql_1_9_12_nCol,runSql_1_9_12_13_i,runSql_1_9_12_13_eType,nm_1$,switch$,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     char *runSql_zMore and skip;
     struct sqlite3_stmt *pstmt and skip;
     break$<==0 and skip;
     while( break$=0 AND zSql AND zSql[0])
     {
         runSql_zMore:=0;
         pstmt:=0;
         sqlite3_prepare_v2(db,zSql,-1,&pstmt,&runSql_zMore,RValue) and skip;
         if(runSql_zMore=zSql) then 
         {
             break$<==1 and skip
          }
         else 
         {
              skip 
         };
         if(break$=0)   then
         {
             if(runFlags & 1) then 
             {
                 char *runSql_1_3_z<==zSql and skip;
                 int runSql_1_3_n and skip;
                 while(runSql_1_3_z<runSql_zMore AND isspace((unsigned char)(runSql_1_3_z[0])))
                 {
                     runSql_1_3_z:=runSql_1_3_z+1
                 };
                 runSql_1_3_n:=(int)(runSql_zMore-runSql_1_3_z);
                 while(runSql_1_3_n>0 AND isspace((unsigned char)(runSql_1_3_z[runSql_1_3_n-1])))
                 {
                     runSql_1_3_n:=runSql_1_3_n-1
                 };
                 if(runSql_1_3_n=0) then 
                 {
                     break$<==1 and skip
                  }
                 else 
                 {
                      skip 
                 };
                 if(break$=0)   then
                 {
                     if(pstmt=0) then 
                     {
						 printf("TRACE: %.*s (error: %s)\n", runSql_1_3_n, runSql_1_3_z, sqlite3_errmsg(db)) and skip
                     }
                     else
                     {
						 printf("TRACE: %.*s\n", runSql_1_3_n, runSql_1_3_z) and skip
                     }
                 }
                 else
                 {
                     skip
                 }
                 
             }
             else 
             {
                  skip 
             };
             if(break$=0)   then 
             {
                 zSql:=runSql_zMore;
                 if(pstmt) then 
                 {
                     if((runFlags & 2)=0) then 
                     {
                         while(100=sqlite3_step(pstmt,RValue))
                         {
							skip
                         }
                         
                     }
                     else
                     {
                         int runSql_1_9_12_nCol<==-1 and skip;
                         while(100=sqlite3_step(pstmt,RValue))
                         {
                             int runSql_1_9_12_13_i and skip;
                             if(runSql_1_9_12_nCol<0) then 
                             {
                                 runSql_1_9_12_nCol:=sqlite3_column_count(pstmt,RValue)
                                 
                             }
                             else
                             {
                                 if(runSql_1_9_12_nCol>0) then 
                                 {
                                     output ("--------------------------------------------\n") and skip
                                     
                                 }
                                 else 
                                 {
                                      skip 
                                 }
                             };
                             runSql_1_9_12_13_i:=0;
                             
                             while(runSql_1_9_12_13_i<runSql_1_9_12_nCol)
                             {
                                 int runSql_1_9_12_13_eType and skip;
                                 runSql_1_9_12_13_eType:=sqlite3_column_type(pstmt,runSql_1_9_12_13_i,RValue);
                                 output (sqlite3_column_name(pstmt,runSql_1_9_12_13_i,RValue)," = "," = ") and skip;
                                 int switch$ and skip;
                                 break$<==0 and skip;
                                  switch$<==0 and skip;
                                  int nm_1$ and skip;
                                 nm_1$ := runSql_1_9_12_13_eType;
                                 if (nm_1$=5 OR (switch$=1 AND break$=0 AND return=0) ) then 
                                 {
                                     switch$<==1 and skip;
                                     output ("NULL\n") and skip;
                                     break$<==1 and skip
                                      
                                 }
                                 else
                                 {
                                     skip
                                 };
                                 if (nm_1$=1 OR (switch$=1 AND break$=0 AND return=0) ) then 
                                 {
                                     switch$<==1 and skip;
                                     output ("INT ",sqlite3_column_text(pstmt,runSql_1_9_12_13_i,RValue),"\n") and skip;
                                     break$<==1 and skip
                                      
                                 }
                                 else
                                 {
                                     skip
                                 };
                                 if (nm_1$=2 OR (switch$=1 AND break$=0 AND return=0) ) then 
                                 {
                                     switch$<==1 and skip;
                                     output ("FLOAT ",sqlite3_column_text(pstmt,runSql_1_9_12_13_i,RValue),"\n") and skip;
                                     break$<==1 and skip
                                      
                                 }
                                 else
                                 {
                                     skip
                                 };
                                 if (nm_1$=3 OR (switch$=1 AND break$=0 AND return=0) ) then 
                                 {
                                     switch$<==1 and skip;
                                     output ("TEXT [",sqlite3_column_text(pstmt,runSql_1_9_12_13_i,RValue),"]\n") and skip;
                                     break$<==1 and skip
                                      
                                 }
                                 else
                                 {
                                     skip
                                 };
                                 if (nm_1$=4 OR (switch$=1 AND break$=0 AND return=0) ) then 
                                 {
                                     switch$<==1 and skip;
                                     output ("BLOB (",sqlite3_column_bytes(pstmt,runSql_1_9_12_13_i,RValue)," bytes)\n") and skip;
                                     break$<==1 and skip
                                      
                                 }
                                 else
                                 {
                                     skip
                                 };
                                 runSql_1_9_12_13_i:=runSql_1_9_12_13_i+1
                                 
                             }
                         }
                     };
                     sqlite3_finalize(pstmt,RValue) and skip
                 }
                 else
                 {
                     skip
                 }
             }
             else
             {
                 skip
             }
             
         }
         else 
         {
              skip 
         }
     };
     break$<==0 and skip
     )
     }; 
  function rebuild_database (  )
 {
     frame(rebuild_database_rc) and ( 
     int rebuild_database_rc and skip;
     rebuild_database_rc:=sqlite3_exec(db,"BEGIN;\nCREATE TEMP TABLE dbx AS SELECT DISTINCT dbcontent FROM db;\nDELETE FROM db;\nINSERT INTO db(dbid, dbcontent) SELECT NULL, dbcontent FROM dbx ORDER BY 2;\nDROP TABLE dbx;\nCREATE TEMP TABLE sx AS SELECT DISTINCT sqltext FROM xsql;\nDELETE FROM xsql;\nINSERT INTO xsql(sqlid,sqltext) SELECT NULL, sqltext FROM sx ORDER BY 2;\nDROP TABLE sx;\nCOMMIT;\nPRAGMA page_size=1024;\nVACUUM;\n",0,0,0,RValue)
     )
     }; 
  function hexDigitValue ( char c,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     if(c>='0' AND c<='9') then 
     {
         return<==1 and RValue:=c-'0';
         skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         if(c>='a' AND c<='f') then 
         {
             return<==1 and RValue:=c-'a'+10;
             skip
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             if(c>='A' AND c<='F') then 
             {
                 return<==1 and RValue:=c-'A'+10;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 return<==1 and RValue:=-1;
                 skip
             }
             else
             {
                 skip
             }
         }
         else
         {
             skip
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function showHelp (  )
 {
     output ("Usage: ",zArgv0," [options] SOURCE-DB ?ARGS...?\n") and skip;
     output ("Read databases and SQL scripts from SOURCE-DB and execute each script against\neach database, checking for crashes and memory leaks.\nOptions:\n  --cell-size-check    Set the PRAGMA cell_size_check=ON\n  --dbid N             Use only the database where dbid=N\n  --export-db DIR      Write databases to files(s) in DIR. Works with --dbid\n  --export-sql DIR     Write SQL to file(s) in DIR. Also works with --sqlid\n  --help               Show this help text\n  -q|--quiet           Reduced output\n  --limit-mem N        Limit memory used by test SQLite instance to N bytes\n  --limit-vdbe         Panic if any test runs for more than 100,000 cycles\n  --load-sql ARGS...   Load SQL scripts fro files into SOURCE-DB\n  --load-db ARGS...    Load template databases from files into SOURCE_DB\n  -m TEXT              Add a description to the database\n  --native-vfs         Use the native VFS for initially empty database files\n  --native-malloc      Turn off MEMSYS3/5 and Lookaside\n  --oss-fuzz           Enable OSS-FUZZ testing\n  --prng-seed N        Seed value for the PRGN inside of SQLite\n  --rebuild            Rebuild and vacuum the database file\n  --result-trace       Show the results of each SQL command\n  --sqlid N            Use only SQL where sqlid=N\n  --timeout N          Abort if any single test needs more than N seconds\n  -v|--verbose         Increased output.  Repeat for more output.\n") and skip
 };

function my_memset(void *str, int c, unsigned int count, void* RValue)       
{       
frame(s) and (
    void *s <== str and skip;       
    while (count)       
    {       
        *(char *) s <== (char) c and skip;       
        s <== (char *) s + 1 and skip; 
		count:=count-1    
    };
    RValue:= str;
	skip     
)  
};

 function main ( int RValue )
 {
     frame(verifystat,argc,argv,main_iBegin,main_quietFlag,main_verboseFlag,main_zInsSql,main_iFirstInsArg,stmt,main_rc,main_pSql,main_pDb,main_i,main_onlySqlid,main_onlyDbid,main_nativeFlag,main_rebuildFlag,main_vdbeLimitFlag,main_timeoutTest,main_runFlags,main_zMsg,main_nSrcDb,main_azSrcDb,main_iSrcDb,main_nTest,main_zDbName,main_zFailCode,main_cellSzCkFlag,main_sqlFuzz,main_iTimeout,main_nMem,main_nMemThisDb,main_zExpDb,main_zExpSql,main_pHeap,main_ossFuzz,main_ossFuzzThisDb,main_nativeMalloc,main_1_zSql,main_2_3_zName,main_8_9_zExDb,main_8_9_temp$_1,main_8_11_zExSql,main_8_11_temp$_2,main_openFlags,main_zVfs,main_24_25_prevAmt,main_24_25_idx,main_24_25_amt,count$,main_34_iElapse,return,continue) and (
     char* argv[2] and skip;
	 int argc<==2 and skip;
	 int continue<==0 and skip;
     int return<==0 and skip;
     int main_iBegin and skip;
     int main_quietFlag<==0 and skip;
     int main_verboseFlag<==0 and skip;
     char *main_zInsSql<==0 and skip;
     int main_iFirstInsArg<==0 and skip;
     int main_rc and skip;
     Blob *main_pSql and skip;
     Blob *main_pDb and skip;
     int main_i and skip;
     int main_onlySqlid<==-1 and skip;
     int main_onlyDbid<==-1 and skip;
     int main_nativeFlag<==0 and skip;
     int main_rebuildFlag<==0 and skip;
     int main_vdbeLimitFlag<==0 and skip;
     int main_timeoutTest<==0 and skip;
     int main_runFlags<==0 and skip;
     char *main_zMsg<==0 and skip;
     int main_nSrcDb<==0 and skip;
     char main_azSrcDb[1,20] and skip;
     int main_iSrcDb and skip;
     int main_nTest<==0 and skip;
     char *main_zDbName<=="" and skip;
     char *main_zFailCode<==0 and skip;
     int main_cellSzCkFlag<==0 and skip;
     int main_sqlFuzz<==0 and skip;
     int main_iTimeout<==120 and skip;
     int main_nMem<==0 and skip;
     int main_nMemThisDb<==0 and skip;
     char *main_zExpDb<==0 and skip;
     char *main_zExpSql<==0 and skip;
     void *main_pHeap<==0 and skip;
     int main_ossFuzz<==0 and skip;
     int main_ossFuzzThisDb<==0 and skip;
     int main_nativeMalloc<==0 and skip;
	  int main_24_25_prevAmt<==-1 and skip;
     main_iBegin:=0;
     zArgv0:=argv[0];
     main_zFailCode:=getenv("TEST_FAILURE",RValue);
     inmemVfsRegister1(1,RValue) and skip;
     main_nSrcDb:=main_nSrcDb+1;
	 strcpy(main_azSrcDb[main_nSrcDb-1],"fuzzdata4.db") and skip;
	 //main_azSrcDb[main_nSrcDb-1]= "fuzzdata4.db" and skip;
     main_iSrcDb:=0;
	 int verifystat<==0 and skip;
	 while(verifystat<6843456)
	 {
		verifystat:=verifystat+1
	 };
     while( return=0 AND  main_iSrcDb<main_nSrcDb)
     {
         main_rc:=sqlite3_open_v2("fuzzdata4.db",&db,2,"win32",RValue);
         main_rc:=sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS db(\n  dbid INTEGER PRIMARY KEY, -- database id\n  dbcontent BLOB            -- database disk file image\n);\nCREATE TABLE IF NOT EXISTS xsql(\n  sqlid INTEGER PRIMARY KEY,   -- SQL script id\n  sqltext TEXT                 -- Text of SQL statements to run\n);CREATE TABLE IF NOT EXISTS readme(\n  msg TEXT -- Human-readable description of this file\n);",0,0,0,RValue);
         if(main_zMsg) then 
         {
			
             char *main_1_zSql and skip;
             main_1_zSql:=sqlite3_mprintf("DELETE FROM readme; INSERT INTO readme(msg) VALUES(%Q)",main_zMsg,RValue);
             main_rc:=sqlite3_exec(db,main_1_zSql,0,0,0,RValue); 
             sqlite3_free(main_1_zSql,RValue) and skip
             
         }
         else 
         {
              skip 
         };
         main_ossFuzzThisDb:=main_ossFuzz;
         if(sqlite3_table_column_metadata(db,0,"config",0,0,0,0,0,0,RValue)=0) then 
         {
             main_rc:=sqlite3_prepare_v2(db,"SELECT name, value FROM config",-1,&stmt,0,RValue);
             while(100=sqlite3_step(stmt,RValue))
             {
                 continue<==0 and skip;
                 char *main_2_3_zName and skip;
                 main_2_3_zName:=(char *)sqlite3_column_text(stmt,0,RValue);
                 if(main_2_3_zName=0) then 
                 {
                     continue<==1 and skip;
                      main_iSrcDb:=main_iSrcDb+1}
                     else 
                     {
                          skip 
                     };
                     if(continue=0)   then 
                     {
                         if(strcmp(main_2_3_zName,"oss-fuzz")=0) then 
                         {
                             main_ossFuzzThisDb:=sqlite3_column_int(stmt,1,RValue);
                             if(main_verboseFlag) then 
                             {
                                 output ("Config: oss-fuzz=",main_ossFuzzThisDb,"\n") and skip
                             }
                             else 
                             {
                                  skip 
                             }
                         }
                         else
                         {
                             skip
                         }
                         
                     }
                     else 
                     {
                          skip 
                     }
                 };
                 continue<==0 and skip;
                 sqlite3_finalize(stmt,RValue) and skip
                 
             }
             else 
             {
                  skip 
             };
			 
             if(main_zInsSql) then 
             {
				 my_sqlite3_create_function2() and skip;
                 main_rc:=sqlite3_prepare_v2(db,main_zInsSql,-1,&stmt,0,RValue);
                 main_rc:=sqlite3_exec(db,"BEGIN",0,0,0,RValue);
                 main_i:=main_iFirstInsArg;
                 
                 while(main_i<argc)
                 {
                     sqlite3_bind_text(stmt,1,argv[main_i],-1,0,RValue) and skip;
                     sqlite3_step(stmt,RValue) and skip;
                     main_rc:=sqlite3_reset(stmt,RValue);
                     main_i:=main_i+1
                     
                 };
                 sqlite3_finalize(stmt,RValue) and skip;
                 main_rc:=sqlite3_exec(db,"COMMIT",0,0,0,RValue);
                 rebuild_database();
                 sqlite3_close(db,RValue) and skip;
                 return<==1 and RValue:=0;
                 skip
                 
             }
             else 
             {
                  skip 
             };
			 
             if(return=0)   then 
             {
			
                 main_rc:=sqlite3_exec(db,"PRAGMA query_only=1;",0,0,0,RValue);
				  
                 if(main_zExpDb!=0 OR main_zExpSql!=0) then 
                 {
					 my_sqlite3_write_function() and skip;
                     if(main_zExpDb!=0) then 
                     {
                         char *main_8_9_zExDb<=="SELECT writefile(printf('%s/db%06d.db',?1,dbid),dbcontent), dbid, printf('%s/db%06d.db',?1,dbid), length(dbcontent) FROM db WHERE ?2<0 OR dbid=?2;" and skip;
                         main_rc:=sqlite3_prepare_v2(db,main_8_9_zExDb,-1,&stmt,0,RValue);
                         int main_8_9_temp$_1 and skip;
                         main_8_9_temp$_1:=strlen(main_zExpDb);
                         sqlite3_bind_text64(stmt,1,main_zExpDb,main_8_9_temp$_1,0,1,RValue) and skip;
                         sqlite3_bind_int(stmt,2,main_onlyDbid,RValue) and skip;
                         while(sqlite3_step(stmt,RValue)=100)
                         {
                             output ("write db-",sqlite3_column_int(stmt,1,RValue)," (",sqlite3_column_int(stmt,3,RValue)," bytes) into ",sqlite3_column_text(stmt,2,RValue),"\n") and skip
                         };
                         sqlite3_finalize(stmt,RValue) and skip
                     }
                     else
                     {
                         skip
                     };
					 if(main_zExpSql!=0) then 
					 {
				 
						 char *main_8_11_zExSql<=="SELECT writefile(printf('%s/sql%06d.txt',?1,sqlid),sqltext), sqlid, printf('%s/sql%06d.txt',?1,sqlid), length(sqltext) FROM xsql WHERE ?2<0 OR sqlid=?2;" and skip;
						 main_rc:=sqlite3_prepare_v2(db,main_8_11_zExSql,-1,&stmt,0,RValue);
						 int main_8_11_temp$_2 and skip;
						 main_8_11_temp$_2:=strlen(main_zExpSql);
						 sqlite3_bind_text64(stmt,1,main_zExpSql,main_8_11_temp$_2,0,1,RValue) and skip;
						 sqlite3_bind_int(stmt,2,main_onlySqlid,RValue) and skip;
						 while(sqlite3_step(stmt,RValue)=100)
						 {
							 output ("write sql-",sqlite3_column_int(stmt,1,RValue)," (",sqlite3_column_int(stmt,3,RValue)," bytes) into ",sqlite3_column_text(stmt,2,RValue),"\n") and skip
						 };
						 sqlite3_finalize(stmt,RValue) and skip
                     
					 }
					 else 
					 {
						  skip 
					 };
					 sqlite3_close(db,RValue) and skip;
					 printf("return:%d",return) and skip;
					 return<==1 and RValue:=0;
					 skip
				}
                 else 
                 {
                      skip 
                 }
                 
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 blobListLoadFromDb("SELECT sqlid, sqltext FROM xsql",main_onlySqlid,&nSql,&pFirstSql);
                 blobListLoadFromDb("SELECT dbid, dbcontent FROM db",main_onlyDbid,&nDb,&pFirstDb);
				 
                 if(nDb=0) then 
                 {
					
                     pFirstDb:=safe_realloc(0,20,RValue);
                     my_memset(pFirstDb,0,20);
                     pFirstDb->id:=1;
                     pFirstDb->seq:=0;
                     nDb:=1;
                     main_sqlFuzz:=1
                 }
                 else
                 {
                     skip
                 }
                 
             }
             else 
             {
                  skip 
             };
             if(!main_quietFlag) then 
             {
                 main_zDbName:=main_azSrcDb[main_iSrcDb];
				 printf("main_zDbName:%s\n",main_zDbName) and skip;
                 main_i:=(int)strlen(main_zDbName)-1;
                 while(main_i>0 AND main_zDbName[main_i-1]!='/' AND main_zDbName[main_i-1]!='\\')
                 {
                     main_i:=main_i-1
                 };
				
                 main_zDbName:=main_zDbName+main_i;
                 sqlite3_prepare_v2(db,"SELECT msg FROM readme",-1,&stmt,0,RValue) and skip;
                 if(stmt AND sqlite3_step(stmt,RValue)=100) then 
                 {
                     output ("fuzzdata4.db: ",sqlite3_column_text(stmt,0,RValue),"\n") and skip
					  
                     
                 }
                 else 
                 {
                      skip 
                 };
                 sqlite3_finalize(stmt,RValue) and skip
                 
             }
             else 
             {
                  skip 
             };
			
             if(main_rebuildFlag) then 
             {
                 if(!main_quietFlag) then 
                 {
                     output (main_zDbName,": rebuilding... ",": rebuilding... ") and skip;
                     fflush(stdout) and skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 rebuild_database();
                 if(!main_quietFlag) then 
                 {
                     output ("done\n") and skip
                 }
                 else 
                 {
                      skip 
                 }
                 
             }
             else 
             {
                  skip 
             };
             sqlite3_close(db,RValue) and skip;
             sqlite3_shutdown(RValue) and skip;
             if(main_nMemThisDb>0 AND !main_nativeMalloc) then 
             {
                 main_pHeap:=realloc(main_pHeap,main_nMemThisDb);
                 sqlite3_config(8,main_pHeap,main_nMemThisDb,128,RValue) and skip
                 
             }
             else 
             {
                  skip 
             };
             if(main_nativeMalloc) then 
             {
                 sqlite3_config(13,0,0,RValue) and skip
                 
             }
             else 
             {
                  skip 
             };
             formatVfs(RValue) and skip;
             if(!main_verboseFlag AND !main_quietFlag) then 
             {
                 printf("fuzzdata4.db:") and skip
             }
             else 
             {
                  skip 
             };
             main_pSql:=pFirstSql;
             
             while(main_pSql)
             {
                 main_pDb:=pFirstDb;
                 
                 while(main_pDb)
                 {
                     int main_openFlags and skip;
                     char *main_zVfs<=="inmem" and skip;
                     sqlite3_snprintf(100,zTestName,"sqlid=%d,dbid=%d",main_pSql->id,main_pDb->id,RValue) and skip;
                     if(main_verboseFlag) then 
                     {
                         output (zTestName,"\n","\n") and skip;
                         fflush(stdout) and skip
                         
                     }
                     else
                     {
                         if(!main_quietFlag) then 
                         {
                            
                             int main_24_25_idx<==main_pSql->seq*nDb+main_pDb->id-1 and skip;
                             int main_24_25_amt<==main_24_25_idx*10/ (nDb*nSql) and skip;
                             if(main_24_25_amt!=main_24_25_prevAmt) then 
                             {
                                 printf(" %d%%", main_24_25_amt*10) and skip;
                                 fflush(stdout) and skip;
                                 main_24_25_prevAmt:=main_24_25_amt
                             }
                             else 
                             {
                                  skip 
                             }
                             
                         }
                         else 
                         {
                              skip 
                         }
                     };
                     createVFile_fuzzcheck("main.db",main_pDb->sz,main_pDb->a,RValue) and skip;
                     sqlite3_randomness(0,0,RValue) and skip;
                     main_openFlags:=4 | 2;
                     if(main_nativeFlag AND main_pDb->sz=0) then 
                     {
                         main_openFlags:=main_openFlags| (0x00000080);
                         main_zVfs:=0
                         
                     }
                     else 
                     {
                          skip 
                     };
                     main_rc:=sqlite3_open_v2("main.db",&db,main_openFlags,main_zVfs,RValue);
                     sqlite3_limit(db,0,100000000,RValue) and skip;
                     sqlite3_limit(db,8,50,RValue) and skip;
                     if(main_cellSzCkFlag) then 
                     {
                         runSql("PRAGMA cell_size_check=ON",main_runFlags)
                     }
                     else 
                     {
                          skip 
                     };
                     if(main_sqlFuzz OR main_vdbeLimitFlag) then 
                     {
                         sqlite3_progress_handler(db,100000,progressHandler,&main_vdbeLimitFlag,RValue) and skip
                         
                     }
                     else 
                     {
                          skip 
                     };
                     int count$<==0 and skip;
                     while( ( count$=0 OR main_timeoutTest))
                     {
                         count$:=count$+1;
                         runSql((char *)main_pSql->a,main_runFlags)
                     };
                     sqlite3_exec(db,"PRAGMA temp_store_directory=''",0,0,0,RValue) and skip;
                     sqlite3_close(db,RValue) and skip;
                     reformatVfs(RValue) and skip;
                     main_nTest:=main_nTest+1;
                     zTestName[0]:=0;
                     if(main_zFailCode) then 
                     {
                         if(main_zFailCode[0]!=0) then 
                         {
                             output ("\nExit early due to TEST_FAILURE being set\n") and skip;
                             main_iSrcDb:=main_nSrcDb-1
                             
                         }
                         else 
                         {
                              skip 
                         }
                         
                     }
                     else 
                     {
                          skip 
                     };
                     main_pDb:=main_pDb->pNext
                     
                 };
                 main_pSql:=main_pSql->pNext
                 
             };
             if(!main_quietFlag AND !main_verboseFlag) then 
             {
				 printf(" 100%% - %d tests\n", nDb*nSql) and skip
             }
             else 
             {
                  skip 
             };
             blobListFree(pFirstSql);
             blobListFree(pFirstDb);
             reformatVfs(RValue) and skip;
             main_iSrcDb:=main_iSrcDb+1
             
         };
         if(return=0)   then 
         {
             if(!main_quietFlag) then 
             {
                 int main_34_iElapse<==0 and skip;
                 output ("fuzzcheck: 0 errors out of ",main_nTest," tests in ",(int)(main_34_iElapse/ 1000),".",(int)(main_34_iElapse % 1000)," seconds\nSQLite ",sqlite3_libversion(RValue)," ",sqlite3_sourceid(RValue),"\n") and skip
                 
             }
             else 
             {
                  skip 
             };
             free(main_pHeap) and skip;
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
