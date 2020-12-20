</
define p:sqlite3_column_blob_call=1;
define q:sqlite3_column_bytes_call=1;
alw(q->p)
/>

 frame(g) and (
struct GlobalVars {
char *zArgv0 and 
int iOomCntdown and 
int nOomFault and 
int bOomOnce and 
int bOomEnable and 
int nOomBrkpt and 
char zTestName[100] 
};
GlobalVars g and skip;
 function oomFault (  )
 {
     g.nOomBrkpt:=g.nOomBrkpt+1
     
 };
 function shellLog ( void *pNotUsed,int iErrCode,char *zMsg )
 {
     output ("LOG: (",iErrCode,") ",zMsg,"\n") and skip;
     fflush(stdout) and skip
     
 };
 function shellLogNoop ( void *pNotUsed,int iErrCode,char *zMsg )
 {
     frame(return) and ( 
     int return<==0 and skip;
      return<==1 and skip
     )
     }; 
  function callback1 ( void *NotUsed,int argc,char **argv,char **colv,int RValue )
 {
     frame(execCallback_i,execCallback_cnt,return) and ( 
     int return<==0 and skip;
     int execCallback_i and skip;
     int execCallback_cnt<==0 and skip;
     output ("ROW #",(execCallback_cnt+1),"u:\n") and skip;
     if(argv) then 
     {
         execCallback_i:=0;
         
         while(execCallback_i<argc)
         {
             output (" ",colv[execCallback_i],"=") and skip;
             if(argv[execCallback_i]) then 
             {
                 output ("[",argv[execCallback_i],"]\n") and skip
                 
             }
             else
             {
                 output ("NULL\n") and skip
             };
             execCallback_i:=execCallback_i+1
             
         }
         
     }
     else 
     {
          skip 
     };
     fflush(stdout) and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function execNoop ( void *NotUsed,int argc,char **argv,char **colv,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function traceCallback ( void *NotUsed,char *zMsg )
 {
     output ("TRACE: ",zMsg,"\n") and skip;
     fflush(stdout) and skip
     
 };
 function traceNoop ( void *NotUsed,char *zMsg )
 {
     frame(return) and ( 
     int return<==0 and skip;
      return<==1 and skip
     )
     }; 
      struct Str {
     char *z and 
     int n and 
     int nAlloc and 
     int oomErr 
 };
 function StrInit ( Str *p )
 {
     memset(p,0,sizeof((* p))) and skip
     
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
             StrAppend_1_zNew:=sqlite3_realloc(p->z,(int)StrAppend_1_nNew,RValue);
             if(StrAppend_1_zNew=0) then 
             {
                 sqlite3_free(p->z,RValue) and skip;
                 memset(p,0,sizeof((* p))) and skip;
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
 struct EvalResult {
 char *z and 
 char *zSep and 
 int szSep and 
 int nAlloc and 
 int nUsed 
 };
 function callback ( void *pCtx,int argc,char **argv,char **colnames,int RValue )
 {
     frame(p,callback_i,callback_z,callback_sz,callback_1_zNew,return) and ( 
     int return<==0 and skip;
     EvalResult *p<==(EvalResult *)pCtx and skip;
     int callback_i and skip;
     callback_i:=0;
     
     while( return=0 AND  callback_i<argc)
     {
         char *callback_z<==( if(argv[callback_i]) then argv[callback_i] else "") and skip;
         int callback_sz and skip;
         callback_sz:=strlen(callback_z);
         if((int)callback_sz+p->nUsed+p->szSep+1>p->nAlloc) then 
         {
             char *callback_1_zNew and skip;
             p->nAlloc:=p->nAlloc*2+callback_sz+p->szSep+1;
             callback_1_zNew:=( if(p->nAlloc<=0x7fffffff) then sqlite3_realloc(p->z,(int)p->nAlloc,RValue) else 0);
             if(callback_1_zNew=0) then 
             {
                 sqlite3_free(p->z,RValue) and skip;
                 memset(p,0,sizeof((* p))) and skip;
                 return<==1 and RValue:=1;
                 skip
                 
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 p->z:=callback_1_zNew
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
             if(p->nUsed>0) then 
             {
                 memcpy(&p->z[p->nUsed],p->zSep,p->szSep) and skip;
                 p->nUsed:=p->nUsed+p->szSep
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
         memcpy(&p->z[p->nUsed],callback_z,callback_sz) and skip;
         p->nUsed:=p->nUsed+callback_sz;
         callback_i:=callback_i+1
         
     };
     if(return=0)   then 
     {
         return<==1 and RValue:=0;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function showHelp (  )
 {
     output ("Usage: ",g.zArgv0," [options] ?FILE...?\n") and skip;
     output ("Read SQL text from FILE... (or from standard input if FILE... is omitted)\nand then evaluate each block of SQL contained therein.\nOptions:\n  --autovacuum          Enable AUTOVACUUM mode\n  --database FILE       Use database FILE instead of an in-memory database\n  --disable-lookaside   Turn off lookaside memory\n  --heap SZ MIN         Memory allocator uses SZ bytes & min allocation MIN\n  --help                Show this help text\n  --lookaside N SZ      Configure lookaside for N slots of SZ bytes each\n  --oom                 Run each test multiple times in a simulated OOM loop\n  --pagesize N          Set the page size to N\n  --pcache N SZ         Configure N pages of pagecache each of size SZ bytes\n  -q                    Reduced output\n  --quiet               Reduced output\n  --scratch N SZ        Configure scratch memory for N slots of SZ bytes each\n  --unique-cases FILE   Write all unique test cases to FILE\n  --utf16be             Set text encoding to UTF-16BE\n  --utf16le             Set text encoding to UTF-16LE\n  -v                    Increased output\n  --verbose             Increased output\n") and skip
     
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
  function main ( int RValue )
 {
     frame(verifystat,main_zIn,main_nAlloc,main_nIn,main_got,main_rc,main_i,main_iNext,db,main_zErrMsg,main_zEncoding,main_nHeap,main_mnHeap,main_nLook,main_szLook,main_nPCache,main_szPCache,main_nScratch,main_szScratch,main_pageSize,main_pHeap,main_pLook,main_pPCache,main_pScratch,main_doAutovac,main_zSql,main_zToFree,main_verboseFlag,main_quietFlag,main_nTest,main_multiTest,main_lastPct,db1,pStmt2,main_zDataOut,main_nHeader,main_oomFlag,main_oomCnt,main_zErrBuf,main_zFailCode,main_zPrompt,main_nInFile,main_azInFile,main_jj,main_iBegin,main_iStart,main_iEnd,main_zDbName,main_in,main_3_j,main_3_k,main_cSaved,main_13_14_16_pct,main_21_sql,stmt,main_21_25_26_27_temp$_1,count$,main_40_iElapse,main_41_n,main_41_out,main_41_43_temp$_2,main_41_43_temp$_3,main_41_43_temp$_4,return,break$) and (
     int break$<==0 and skip;
     int return<==0 and skip;
     char *main_zIn<==0 and skip;
     int main_nAlloc<==0 and skip;
     int main_nIn<==0 and skip;
     int main_got and skip;
     int main_rc<==0 and skip;
     int main_i and skip;
     int main_iNext and skip;
     char *main_zErrMsg<==0 and skip;
     char *main_zEncoding<==0 and skip;
     int main_nHeap<==0,main_mnHeap<==0 and skip;
     int main_nLook<==0,main_szLook<==0 and skip;
     int main_nPCache<==0,main_szPCache<==0 and skip;
     int main_nScratch<==0,main_szScratch<==0 and skip;
     int main_pageSize<==0 and skip;
     void *main_pHeap<==0 and skip;
     void *main_pLook<==0 and skip;
     void *main_pPCache<==0 and skip;
     void *main_pScratch<==0 and skip;
     int main_doAutovac<==0 and skip;
     char *main_zSql and skip;
     char *main_zToFree<==0 and skip;
     int main_verboseFlag<==0 and skip;
     int main_quietFlag<==0 and skip;
     int main_nTest<==0 and skip;
     int main_multiTest<==0 and skip;
     int main_lastPct<==-1 and skip;
     char *main_zDataOut<==0 and skip;
     int main_nHeader<==0 and skip;
     int main_oomFlag<==0 and skip;
     int main_oomCnt<==0 and skip;
     char main_zErrBuf[200] and skip;
     char *main_zFailCode and skip;
     char *main_zPrompt and skip;
     int main_nInFile<==0 and skip;
     char main_azInFile[20,20] and skip;
     int main_jj and skip;
     int main_iBegin and skip;
     int main_iStart,main_iEnd and skip;
     char *main_zDbName<==0 and skip;
     main_iBegin:=timeOfDay(RValue);
     sqlite3_shutdown(RValue) and skip;
     main_zFailCode:=getenv("TEST_FAILURE",RValue);
     g.zArgv0:="";
     main_zPrompt:="<stdin>";
     main_zDataOut:="fuzzershell_b.txt";
     main_nInFile:=main_nInFile+1;
     //main_azInFile:=realloc(main_azInFile,sizeof((main_azInFile[0]))*main_nInFile);
     //main_azInFile[main_nInFile-1]:="fuzzershell_a.txt";
	 strcpy(main_azInFile[main_nInFile-1],"fuzzershell_a.txt") and skip;
     //sqlite3_config(16, shellLogNoop,0,RValue) and skip;
	 int verifystat<==0 and skip;
	 while(verifystat<8430560)
	 {
		verifystat:=verifystat+1
	 };
     if(main_zDataOut) then 
     {
         main_rc:=sqlite3_open(":memory:",&db1,RValue);
         main_rc:=sqlite3_exec(db1,"CREATE TABLE testcase(sql BLOB PRIMARY KEY, tm) WITHOUT ROWID;",0,0,0,RValue);
         main_rc:=sqlite3_prepare_v2(db1,"INSERT OR IGNORE INTO testcase(sql,tm)VALUES(?1,?2)",-1,&pStmt2,0,RValue)
         
     }
     else 
     {
          skip 
     };
     if(main_nInFile=0) then 
     {
         main_nInFile:=1
     }
     else 
     {
          skip 
     };
     main_nAlloc:=1000;
     main_zIn:=malloc(main_nAlloc);
     main_jj:=0;
     
     while(main_jj<main_nInFile)
     {
         FILE *main_in and skip;
         if(main_azInFile) then 
         {
             int main_3_j,main_3_k and skip;
             main_in:=fopen(main_azInFile[main_jj],"rb");
             main_zPrompt:=main_azInFile[main_jj];
             main_3_k<==0 and main_3_j<==main_3_k and skip;
             
             while(main_zPrompt[main_3_j])
             {
                 if(main_zPrompt[main_3_j]='/') then 
                 {
                     main_3_k:=main_3_j+1
                 }
                 else 
                 {
                      skip 
                 };
                 main_3_j:=main_3_j+1
                 
             };
             main_zPrompt:=main_zPrompt+main_3_k
             
         }
         else
         {
             main_in:=stdin;
             main_zPrompt:="<stdin>"
         };
		 
         break$<==0 and skip;
         while( break$=0 AND  !feof(main_in,RValue))
         {
             main_got:=fread(main_zIn+main_nIn,1,main_nAlloc-main_nIn-1,main_in);
             main_nIn:=main_nIn+(int)main_got;
             main_zIn[main_nIn]:=0;
             if(main_got=0) then 
             {
                 break$<==1 and skip
              }
             else 
             {
                  skip 
             };
             if(break$=0)   then
             {
                 if(main_nAlloc-main_nIn-1<100) then 
                 {
                     main_nAlloc:=main_nAlloc+main_nAlloc+1000;
                     main_zIn:=realloc(main_zIn,main_nAlloc)
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
         break$<==0 and skip;
         if(main_in!=stdin) then 
         {
             fclose(main_in) and skip
         }
         else 
         {
              skip 
         };
         main_lastPct:=-1;
         break$<==0 and skip;
         main_i:=0;
         
         while( break$=0 AND  main_i<main_nIn)
         {
             if(main_zIn[main_i]!='#') then 
             {
                 break$<==1 and skip
              }
             else 
             {
                  skip 
             };
             if(break$=0)   then
             {
                 main_iNext:=main_i+1;
                 
                 while(main_iNext<main_nIn AND main_zIn[main_iNext]!='\n')
                 {
                     main_iNext:=main_iNext+1
                     
                 };
                 main_i:=main_iNext+1
             }
             else
             {
                 skip
             }
             
         };
		 
         break$<==0 and skip;
         main_nHeader:=main_i;
         break$<==0 and skip;
         while( break$=0 AND  main_i<main_nIn)
         {
             char main_cSaved and skip;
             main_iNext:=main_i;
             
             while(main_iNext<main_nIn AND strncmp(&main_zIn[main_iNext],"****<",6,RValue)!=0)
             {
                 main_iNext:=main_iNext+1
                 
             };
             main_cSaved:=main_zIn[main_iNext];
             main_zIn[main_iNext]:=0;
             main_zSql:=&main_zIn[main_i];
             if(main_verboseFlag) then 
             {
                 output ("INPUT (offset: ",main_i,", size: ",(int)strlen(&main_zIn[main_i]),"): [",&main_zIn[main_i],"]\n") and skip
                 
             }
             else
             {
                 if(main_multiTest AND !main_quietFlag) then 
                 {
                     if(main_oomFlag) then 
                     {
                         output (g.zTestName,"\n","\n") and skip
                     }
                     else
                     {
                         int main_13_14_16_pct<==(10*main_iNext)/ main_nIn and skip;
                         if(main_13_14_16_pct!=main_lastPct) then 
                         {
                             if(main_lastPct<0) then 
                             {
                                 output (main_zPrompt,":",":") and skip
                             }
                             else 
                             {
                                  skip 
                             };
                             //output (main_13_14_16_pct*10,) and skip;
							 printf(" %d%%", main_13_14_16_pct*10) and skip;
                             main_lastPct:=main_13_14_16_pct
                             
                         }
                         else 
                         {
                              skip 
                         }
                     }
                 }
                 else
                 {
                     if(main_nInFile>1) then 
                     {
                         output (main_zPrompt,"\n","\n") and skip
                         
                     }
                     else 
                     {
                          skip 
                     }
                 }
             };
			 
             fflush(stdout) and skip;
             main_oomCnt:=0;
             int count$<==0 and skip;
             while( ( count$=0 OR main_oomCnt>0))
             {
				
                 count$:=count$+1;
                 Str main_21_sql and skip;
				 
                 if(main_zDbName) then 
                 {
                     main_rc:=sqlite3_open_v2(main_zDbName,&db,0x00000002,0,RValue)
                     
                 }
                 else
                 {
                     main_rc:=sqlite3_open_v2("main.db",&db,0x00000002 | 0x00000004 | 0x00000080,0,RValue)
                 };
				 
                 sqlite3_limit(db,0,1000000,RValue) and skip;
                 main_iStart:=timeOfDay(RValue);
				 
                 if(sqlite3_table_column_metadata(db,0,"autoexec","sql",0,0,0,0,0,RValue)=0) then 
                 {
                     main_rc:=sqlite3_prepare_v2(db,"SELECT sql FROM autoexec",-1,&stmt,0,RValue);
                     if(main_rc=0) then 
                     {
                         while(sqlite3_step(stmt,RValue)=100)
                         {
                             int main_21_25_26_27_temp$_1 and skip;
                             main_21_25_26_27_temp$_1:=sqlite3_column_text(stmt,0,RValue);
                             StrAppend(&main_21_sql,(char *)main_21_25_26_27_temp$_1);
                             StrAppend(&main_21_sql,"\n")
                         }
                         
                     }
                     else 
                     {
                          skip 
                     };
                     sqlite3_finalize(stmt,RValue) and skip;
                     main_zSql:=StrStr(&main_21_sql,RValue)
                     
                 }
                 else 
                 {
                      skip 
                 };
                 g.bOomEnable:=1;
                 if(main_verboseFlag) then 
                 {
                     main_zErrMsg:=0;
                     main_rc:=sqlite3_exec(db,main_zSql,callback1,0,&main_zErrMsg,RValue);
                     if(main_zErrMsg) then 
                     {
                         //sqlite3_snprintf(200,main_zErrBuf,"%z",main_zErrMsg,RValue) and skip;
                         main_zErrMsg:=0
                         
                     }
                     else 
                     {
                          skip 
                     }
                     
                 }
                 else
                 {
                     main_rc:=sqlite3_exec(db,main_zSql,execNoop,0,0,RValue)
                 };
                 g.bOomEnable:=0;
                 main_iEnd:=timeOfDay(RValue);
                 //StrFree(&main_21_sql);
                 main_rc:=sqlite3_close(db,RValue)
             };
             if(main_zDataOut) then 
             {
                 sqlite3_bind_blob(pStmt2,1,&main_zIn[main_i],main_iNext-main_i,0,RValue) and skip;
                 sqlite3_bind_int64(pStmt2,2,main_iEnd-main_iStart,RValue) and skip;
                 main_rc:=sqlite3_step(pStmt2,RValue);
                 sqlite3_reset(pStmt2,RValue) and skip
                 
             }
             else 
             {
                  skip 
             };
             if(main_zToFree) then 
             {
                 sqlite3_free(main_zToFree,RValue) and skip;
                 main_zToFree:=0
                 
             }
             else 
             {
                  skip 
             };
             main_zIn[main_iNext]:=main_cSaved;
             if(main_verboseFlag) then 
             {
                 output ("RESULT-CODE: ",main_rc,"\n") and skip;
                 if(main_zErrMsg) then 
                 {
                     output ("ERROR-MSG: [",main_zErrBuf,"]\n") and skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 fflush(stdout) and skip
                 
             }
             else 
             {
                  skip 
             };
             if(main_zFailCode) then 
             {
                 if(main_zFailCode[0]='5' AND main_zFailCode[1]=0) then 
                 {
                     skip
                 }
                 else
                 {
                     if(main_zFailCode[0]!=0) then 
                     {
                         output ("\nExit early due to TEST_FAILURE being set") and skip;
                         break$<==1 and skip
                          
                     }
                     else 
                     {
                          skip 
                     }
                 }
                 
             }
             else 
             {
                  skip 
             };
             if(break$=0)   then 
             {
                 main_i:=main_iNext and main_nTest:=main_nTest+1
             }
             else
             {
                 skip
             }
             
         };
         break$<==0 and skip;
         if(!main_verboseFlag AND main_multiTest AND !main_quietFlag AND !main_oomFlag) then 
         {
             output ("\n") and skip
         }
         else 
         {
              skip 
         };
         main_jj:=main_jj+1
         
     };
     if(main_nTest>1 AND !main_quietFlag) then 
     {
         int main_40_iElapse<==timeOfDay(RValue) and skip;
		 main_40_iElapse:=main_40_iElapse-main_iBegin and skip
         
     }
     else 
     {
          skip 
     };
	 
     if(main_zDataOut) then 
     {
         int main_41_n<==0 and skip;
         FILE *main_41_out and skip;
         main_41_out:=fopen(main_zDataOut,"wb");
         if(main_nHeader>0) then 
         {
             fwrite(main_zIn,main_nHeader,1,main_41_out) and skip
         }
         else 
         {
              skip 
         };
         sqlite3_finalize(pStmt2,RValue) and skip;
         main_rc:=sqlite3_prepare_v2(db1,"SELECT sql, tm FROM testcase ORDER BY tm, sql",-1,&pStmt2,0,RValue);
         while(sqlite3_step(pStmt2,RValue)=100)
         {
             int main_41_43_temp$_2 and skip;
             main_41_43_temp$_2:=sqlite3_column_int(pStmt2,1,RValue);
             fprintf(main_41_out,"/****<%d:%dms>****/",(main_41_n+1),main_41_43_temp$_2) and skip;
             main_41_n:=main_41_n+1;
             int main_41_43_temp$_3 and skip;
             main_41_43_temp$_3:=sqlite3_column_bytes(pStmt2,0,RValue);
             int main_41_43_temp$_4 and skip;
             main_41_43_temp$_4:=sqlite3_column_blob(pStmt2,0,RValue);
             fwrite(main_41_43_temp$_4,main_41_43_temp$_3,1,main_41_out) and skip
         };
         fclose(main_41_out) and skip;
         sqlite3_finalize(pStmt2,RValue) and skip;
         sqlite3_close(db1,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     free(main_zIn) and skip;
     free(main_pHeap) and skip;
     free(main_pLook) and skip;
     free(main_pScratch) and skip;
     free(main_pPCache) and skip;
     return<==1 and RValue:=0;
     skip
     )
 };
  main(RValue)
 )

