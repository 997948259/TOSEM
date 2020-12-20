</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

 function showHelp ( char *zArgv0 )
 {
     output ("Usage: ",zArgv0," [options] DATABASE ...\n") and skip;
     output ("Read databases into an in-memory filesystem.  Run test SQL as specified\nby command-line arguments or from\n\n    SELECT group_concat(sql) FROM autoexec;\n\nOptions:\n  --help              Show this help text\n  -q|--quiet          Reduced output\n  --limit-mem N       Limit memory used by test SQLite instances to N bytes\n  --limit-vdbe        Panic if any test runs for more than 100,000 cycles\n  --no-lookaside      Disable the lookaside memory allocator\n  --timeout N         Timeout after N seconds.\n  --trace             Show the results of each SQL command\n  -v|--verbose        Increased output.  Repeat for more output.\n") and skip
     
 };
 struct Str {
 char *z and 
 int n and 
 int nAlloc and 
 int oomErr 
 };
 function StrInit ( Str *p )
 {
     //memset(p,0,sizeof((* p))) and skip
	 p->z:=NULL;
	 p->n:=0;
	 p->nAlloc:=0;
	 p->oomErr:=0
     
 };
 function StrAppend ( Str *p,char *z )
 {
     frame(StrAppend_n,StrAppend_1_zNew,StrAppend_1_nNew,return) and ( 
     int return<==0 and skip;
     int StrAppend_n and skip;
     StrAppend_n:=strlen(z);
	
     if(p->n+StrAppend_n>=p->nAlloc) then 
     {
         char *StrAppend_1_zNew and skip;
         int StrAppend_1_nNew and skip;
         if(p->oomErr) then 
         {
              return<==1 and skip
         }
         else 
         {
              skip 
         };
		  
         if(return=0)   then 
         {
             StrAppend_1_nNew:=p->nAlloc*2+100+StrAppend_n;
             StrAppend_1_zNew:=sqlite3_realloc64(p->z,StrAppend_1_nNew,RValue);
             if(StrAppend_1_zNew=0) then 
             {
				
                 sqlite3_free(p->z,RValue) and skip;
				 p->z:=NULL;
				 p->n:=0;
				 p->nAlloc:=0;
				 p->oomErr:=0;
                 p->oomErr:=1;
                  return<==1 and skip
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
             p->z:=StrAppend_1_zNew;
             p->nAlloc:=StrAppend_1_nNew
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
     if(return=0)  then
     {
         memcpy(p->z+p->n,z,(int)StrAppend_n) and skip;
         p->n:=p->n+StrAppend_n;
         p->z[p->n]:=0
     }
     else
     {
         skip
     }
     )
     }; 
  function StrStr ( Str *p,char* RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=p->z;
     skip
     )
     }; 
  function StrFree ( Str *p )
 {
     sqlite3_free(p->z,RValue) and skip;
     StrInit(p)
     
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
  function sqlLog ( void *pNotUsed,int iErrCode,char *zMsg )
 {
     output ("LOG: (",iErrCode,") ",zMsg,"\n") and skip;
     fflush(stdout) and skip
     
 };
 function progressHandler ( void *pVdbeLimitFlag,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=1;
     skip
     )
     }; 
  function runSql ( struct sqlite3 *db,char *zSql,int runFlags )
 {
     frame(runSql_zMore,runSql_zEnd,stmt,runSql_1_3_z,runSql_1_3_n,runSql_1_9_12_nCol,runSql_1_9_12_nRow,runSql_1_9_12_i,runSql_1_9_12_eType,nm_1$,switch$,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     char *runSql_zMore and skip;
     char *runSql_zEnd<==&zSql[strlen(zSql)] and skip;
     break$<==0 and skip;
     while( break$=0 AND zSql AND zSql[0])
     {
         runSql_zMore:=0;
         stmt:=0;
         sqlite3_prepare_v2(db,zSql,-1,&stmt,&runSql_zMore,RValue) and skip;
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
                     if(stmt=0) then 
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
                 if(stmt) then 
                 {
                     if((runFlags & 2)=0) then 
                     {
                         while(100=sqlite3_step(stmt,RValue))
                         {
							skip
                         }
                         
                     }
                     else
                     {
                         int runSql_1_9_12_nCol<==-1 and skip;
                         int runSql_1_9_12_nRow and skip;
                         runSql_1_9_12_nRow:=0;
                         
                         while(100=sqlite3_step(stmt,RValue))
                         {
                             int runSql_1_9_12_i and skip;
                             if(runSql_1_9_12_nCol<0) then 
                             {
                                 runSql_1_9_12_nCol:=sqlite3_column_count(stmt,RValue)
                                 
                             }
                             else 
                             {
                                  skip 
                             };
                             runSql_1_9_12_i:=0;
                             
                             while(runSql_1_9_12_i<runSql_1_9_12_nCol)
                             {
                                 int runSql_1_9_12_eType and skip;
                                 runSql_1_9_12_eType:=sqlite3_column_type(stmt,runSql_1_9_12_i,RValue);
                                 output ("ROW[",runSql_1_9_12_nRow,"].",sqlite3_column_name(stmt,runSql_1_9_12_i,RValue)," = ") and skip;
                                 int switch$ and skip;
                                 break$<==0 and skip;
                                  switch$<==0 and skip;
                                  int nm_1$ and skip;
                                 nm_1$ := runSql_1_9_12_eType;
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
                                     output ("INT ",sqlite3_column_text(stmt,runSql_1_9_12_i,RValue),"\n") and skip;
                                     break$<==1 and skip
                                      
                                 }
                                 else
                                 {
                                     skip
                                 };
                                 if (nm_1$=2 OR (switch$=1 AND break$=0 AND return=0) ) then 
                                 {
                                     switch$<==1 and skip;
                                     output ("FLOAT ",sqlite3_column_text(stmt,runSql_1_9_12_i,RValue),"\n") and skip;
                                     break$<==1 and skip
                                      
                                 }
                                 else
                                 {
                                     skip
                                 };
                                 if (nm_1$=3 OR (switch$=1 AND break$=0 AND return=0) ) then 
                                 {
                                     switch$<==1 and skip;
                                     output ("TEXT [",sqlite3_column_text(stmt,runSql_1_9_12_i,RValue),"]\n") and skip;
                                     break$<==1 and skip
                                      
                                 }
                                 else
                                 {
                                     skip
                                 };
                                 if (nm_1$=4 OR (switch$=1 AND break$=0 AND return=0) ) then 
                                 {
                                     switch$<==1 and skip;
                                     output ("BLOB (",sqlite3_column_bytes(stmt,runSql_1_9_12_i,RValue)," bytes)\n") and skip;
                                     break$<==1 and skip
                                      
                                 }
                                 else
                                 {
                                     skip
                                 };
                                 runSql_1_9_12_i:=runSql_1_9_12_i+1
                                 
                             };
                             runSql_1_9_12_nRow:=runSql_1_9_12_nRow+1
                             
                         }
                     };
                     sqlite3_finalize(stmt,RValue) and skip
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
  function main ( int RValue )
 {
     frame(verifystat,main_i,main_nDb,main_azDb,main_verboseFlag,main_noLookaside,main_vdbeLimitFlag,main_nHeap,main_iTimeout,main_rc,db,pstmt,main_sql,main_runFlags,main_3_pHeap,main_9_10_temp$_1,main_temp$_2,return,continue) and (
     int continue<==0 and skip;
     int return<==0 and skip;
     int main_i and skip;
     int main_nDb<==0 and skip;
     char *main_azDb[2] and skip;
     int main_verboseFlag<==0 and skip;
     int main_noLookaside<==0 and skip;
     int main_vdbeLimitFlag<==0 and skip;
     int main_nHeap<==0 and skip;
     int main_iTimeout<==0 and skip;
     int main_rc and skip;
     Str main_sql and skip;
     int main_runFlags<==0 and skip;
	 int verifystat<==0 and skip;
	 while(verifystat<10201303)
	 {
		verifystat:=verifystat+1
	 };
     //main_azDb:=realloc(main_azDb,sizeof((main_azDb[0]))*(main_nDb+1));
     main_azDb[main_nDb]:=(char *)malloc(10);
	 strcpy(main_azDb[main_nDb],"dbfuzz.db") and skip;
     main_nDb:=main_nDb+1;
	 printf("main_azDb[0]:%s\n",main_azDb[0]) and skip;
     if(main_verboseFlag) then 
     {
         sqlite3_config(16,sqlLog,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     if(main_nHeap>0) then 
     {
         void *main_3_pHeap and skip;
         main_3_pHeap:=malloc(main_nHeap);
         main_rc:=sqlite3_config(8,main_3_pHeap,main_nHeap,32,RValue)
         
     }
     else 
     {
          skip 
     };
     if(main_noLookaside) then 
     {
         sqlite3_config(13,0,0,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     inmemVfsRegister(RValue) and skip;
     formatVfs(RValue) and skip;
     StrInit(&main_sql);
     continue<==0 and skip;
     main_i:=0;
    
     while(main_i<main_nDb)
     {
          continue<==0 and skip;
         if(main_verboseFlag AND main_nDb>1) then 
         {
             output ("DATABASE-FILE: ",main_azDb[main_i],"\n") and skip;
             fflush(stdout) and skip
             
         }
         else 
         {
              skip 
         };
         createVFile("test.db",main_azDb[main_i],RValue) and skip;
		
         main_rc:=sqlite3_open_v2("test.db",&db,2,"inmem",RValue);
		 
         if(main_rc) then 
         {
             output ("cannot open test.db for \"",main_azDb[main_i],"\"\n") and skip;
             reformatVfs(RValue) and skip;
             continue<==1 and skip;
              main_i:=main_i+1
         }
         else 
         {
              skip 
         };
		 
         if(continue=0)   then 
         {
             if(main_vdbeLimitFlag) then 
             {
                 sqlite3_progress_handler(db,100000,progressHandler,&main_vdbeLimitFlag,RValue) and skip
                 
             }
             else 
             {
                  skip 
             };
             main_rc:=sqlite3_prepare_v2(db,"SELECT sql FROM autoexec",-1,&pstmt,0,RValue);
             if(main_rc=0) then 
             {
                 while(100=sqlite3_step(pstmt,RValue))
                 {
                     int main_9_10_temp$_1 and skip;
                     main_9_10_temp$_1:=sqlite3_column_text(pstmt,0,RValue);
                     StrAppend(&main_sql,(char *)main_9_10_temp$_1);
                     StrAppend(&main_sql,"\n")
                 }
                 
             }
             else 
             {
                  skip 
             };
             sqlite3_finalize(pstmt,RValue) and skip;
			
             StrAppend(&main_sql,"PRAGMA integrity_check;\n");

             char* main_temp$_2 and skip;
             main_temp$_2:=StrStr(&main_sql,RValue);
			 
             runSql(db,main_temp$_2,main_runFlags);
             sqlite3_close(db,RValue) and skip;
             reformatVfs(RValue) and skip;
			  
             StrFree(&main_sql);
             main_i:=main_i+1
         }
         else
         {
             skip
         }
         
     };
	  
     continue<==0 and skip;
     StrFree(&main_sql);
     reformatVfs(RValue) and skip;
     return<==1 and RValue:=0;
     skip
     )
 };
  main(RValue)
