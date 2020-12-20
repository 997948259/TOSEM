/*</
define p:sqlite3_column_bytes_call=1;
define q:sqlite3_column_blob_call=1;
alw(p->q)
/>*/
</
define p:sqlite3_mprintf_call=1;
define q:sqlite3_free_call=1;
alw(p->som(q))
/>


frame(zHelp,zTag,azMode,db,stmt,pstmt,pStmt1,pStmt2) and (
char zHelp[992]<=="Usage: wordcount [OPTIONS] DATABASE [INPUT]\n --all                Repeat the test for all test modes\n --cachesize NNN      Use a cache size of NNN\n --commit NNN         Commit after every NNN operations\n --delete             Use DELETE mode\n --insert             Use INSERT mode (the default)\n --journal MMMM       Use PRAGMA journal_mode=MMMM\n --nocase             Add the NOCASE collating sequence to the words.\n --nosync             Use PRAGMA synchronous=OFF\n --pagesize NNN       Use a page size of NNN\n --query              Use QUERY mode\n --replace            Use REPLACE mode\n --select             Use SELECT mode\n --stats              Show sqlite3_status() results at the end.\n --summary            Show summary information on the collected data.\n --timer              Time the operation of this program\n --trace              Enable sqlite3_trace() output.\n --update             Use UPDATE mode\n --without-rowid      Use a WITHOUT ROWID table to store the words.\n" and skip;
char *zTag<=="--" and skip;
 function usage (  )
 {
     output (zHelp) and skip
     
 };
 function traceCallback ( void *NotUsed,char *zSql )
 {
     output (zSql,";\n",";\n") and skip
     
 };
 function printResult ( void *NotUsed,int nArg,char **azArg,char **azNm,int RValue )
 {
     frame(printResult_i,return) and ( 
     int return<==0 and skip;
     int printResult_i and skip;
     output (zTag) and skip;
     printResult_i:=0;
     
     while(printResult_i<nArg)
     {
         output (" ",( if(azArg[printResult_i]) then azArg[printResult_i] else "(null)")) and skip;
         printResult_i:=printResult_i+1
         
     };
     output ("\n") and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function addCharToHash ( int *a,unsigned char x )
 {
     if(a[0]<4) then 
     {
         a[1]:=(a[1]<<8) | x;
         a[0]:=a[0]+1
     }
     else
     {
         a[2]:=(a[2]<<8) | x;
         a[0]:=a[0]+1;
         if(a[0]=8) then 
         {
             a[3]:=a[3]+a[1]+a[4];
             a[4]:=a[4]+a[2]+a[3];
             a[2]<==0 and a[1]<==a[2] and a[0]<==a[1] and skip
             
         }
         else 
         {
              skip 
         }
     }
     
 };
 function finalHash ( int *a,char *z )
 {
     a[3]:=a[3]+a[1]+a[4]+a[0];
     a[4]:=a[4]+a[2]+a[3];
     sqlite3_snprintf(17,z,"%08x%08x",a[3],a[4],RValue) and skip
     
 };
 char *azMode[]<=={"--insert","--replace","--select","--update","--delete","--query"} and skip;
 function allLoop ( int iMode,int *piLoopCnt,int *piMode2,int *pUseWithoutRowid,int RValue )
 {
     frame(allLoop_i,return) and ( 
     int return<==0 and skip;
     int allLoop_i and skip;
     if(iMode!=-1) then 
     {
         if(* piLoopCnt) then 
         {
             return<==1 and RValue:=0;
             skip
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             * piMode2:=iMode;
             * piLoopCnt:=1;
             return<==1 and RValue:=1;
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
     if(return=0)  then
     {
         if(return=0)   then 
         {
             if((* piLoopCnt)>=6*2) then 
             {
                 return<==1 and RValue:=0;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 allLoop_i:=(* piLoopCnt);
                 (* piLoopCnt):=(* piLoopCnt)+1;
                 * pUseWithoutRowid:=allLoop_i & 1;
                 * piMode2:=allLoop_i>>1;
                 return<==1 and RValue:=1;
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
     frame(verifystat,main_argc,main_argv,main_tmp,main_zFileToRead,main_zDbName,main_useWithoutRowid,main_iMode,main_iMode2,main_iLoopCnt,main_useNocase,main_doTrace,main_showStats,main_showSummary,main_showTimer,main_cacheSize,main_pageSize,main_commitInterval,main_noSync,main_zJMode,main_nOp,main_i,main_j,main_zSql,main_in,main_rc,main_iCur,main_iHiwtr,main_sumCnt,main_totalTime,main_zInput,main_z,count$,main_61_66_temp$_1,main_61_67_68_temp$_2,main_61_69_70_temp$_3,main_61_69_71_temp$_4,main_61_72_73_temp$_5,main_61_74_75_temp$_6,main_61_76_77_temp$_7,main_61_78_79_temp$_8,main_61_80_81_temp$_9,main_61_82_84_85_temp$_10,main_61_82_86_87_88_89_temp$_11,main_61_82_86_87_90_91_92_temp$_12,main_61_82_86_87_90_93_temp$_13,main_61_82_86_94_97_98_temp$_14,main_61_82_86_94_97_99_100_temp$_15,return,continue) and (
     int continue<==0 and skip;
     int return<==0 and skip;
     int main_argc<==4 and skip;
     char **main_argv and skip;
     main_argv:=(char **)malloc(4*sizeof(char *));
     int main_tmp<==0 and skip;
     while(main_tmp<4)
     {
         main_argv[main_tmp]:=(char *)malloc(20);
         main_tmp:=main_tmp+1
     };
	 int verifystat<==0 and skip;
	 while(verifystat<7122868)
	 {
		verifystat:=verifystat+1
	 };
     strcpy(main_argv[0],"wordcount.exe") and skip;
     strcpy(main_argv[1],"--insert") and skip;
     strcpy(main_argv[2],"wordcount.db") and skip;
     strcpy(main_argv[3],"wordcount.txt") and skip;
     char *main_zFileToRead<==0 and skip;
     char *main_zDbName<==0 and skip;
     int main_useWithoutRowid<==0 and skip;
     int main_iMode<==0 and skip;
     int main_iMode2 and skip;
     int main_iLoopCnt<==0 and skip;
     int main_useNocase<==0 and skip;
     int main_doTrace<==0 and skip;
     int main_showStats<==0 and skip;
     int main_showSummary<==0 and skip;
     int main_showTimer<==0 and skip;
     int main_cacheSize<==0 and skip;
     int main_pageSize<==0 and skip;
     int main_commitInterval<==0 and skip;
     int main_noSync<==0 and skip;
     char *main_zJMode<==0 and skip;
     int main_nOp<==0 and skip;
     int main_i,main_j and skip;
     char *main_zSql and skip;
     FILE *main_in and skip;
     int main_rc and skip;
     int main_iCur,main_iHiwtr and skip;
     int main_sumCnt<==0 and skip;
     int main_totalTime<==0 and skip;
     char main_zInput[2000] and skip;
     main_i:=1;
     
     while(main_i<main_argc)
     {
         char *main_z<==main_argv[main_i] and skip;
         if(main_z[0]='-') then 
         {
             int count$<==0 and skip;
             while( ( count$=0 OR main_z[0]='-'))
             {
                 count$:=count$+1;
                 main_z:=main_z+1
             };
             if(strcmp(main_z,"without-rowid")=0) then 
             {
                 main_useWithoutRowid:=1
             }
             else
             {
                 if(strcmp(main_z,"replace")=0) then 
                 {
                     main_iMode:=1
                 }
                 else
                 {
                     if(strcmp(main_z,"select")=0) then 
                     {
                         main_iMode:=2
                     }
                     else
                     {
                         if(strcmp(main_z,"insert")=0) then 
                         {
                             main_iMode:=0
                         }
                         else
                         {
                             if(strcmp(main_z,"update")=0) then 
                             {
                                 main_iMode:=3
                             }
                             else
                             {
                                 if(strcmp(main_z,"delete")=0) then 
                                 {
                                     main_iMode:=4
                                 }
                                 else
                                 {
                                     if(strcmp(main_z,"query")=0) then 
                                     {
                                         main_iMode:=5
                                     }
                                     else
                                     {
                                         if(strcmp(main_z,"all")=0) then 
                                         {
                                             main_iMode:=-1;
                                             main_showTimer:=-99
                                         }
                                         else
                                         {
                                             if(strcmp(main_z,"nocase")=0) then 
                                             {
                                                 main_useNocase:=1
                                             }
                                             else
                                             {
                                                 if(strcmp(main_z,"trace")=0) then 
                                                 {
                                                     main_doTrace:=1
                                                 }
                                                 else
                                                 {
                                                     if(strcmp(main_z,"nosync")=0) then 
                                                     {
                                                         main_noSync:=1
                                                     }
                                                     else
                                                     {
                                                         if(strcmp(main_z,"stats")=0) then 
                                                         {
                                                             main_showStats:=1
                                                         }
                                                         else
                                                         {
                                                             if(strcmp(main_z,"summary")=0) then 
                                                             {
                                                                 main_showSummary:=1
                                                             }
                                                             else
                                                             {
                                                                 if(strcmp(main_z,"timer")=0) then 
                                                                 {
                                                                     main_showTimer:=main_i
                                                                 }
                                                                 else
                                                                 {
                                                                     if(strcmp(main_z,"cachesize")=0 AND main_i<main_argc-1) then 
                                                                     {
                                                                         main_i:=main_i+1;
                                                                         main_cacheSize:=atoi(main_argv[main_i])
                                                                     }
                                                                     else
                                                                     {
                                                                         if(strcmp(main_z,"pagesize")=0 AND main_i<main_argc-1) then 
                                                                         {
                                                                             main_i:=main_i+1;
                                                                             main_pageSize:=atoi(main_argv[main_i])
                                                                         }
                                                                         else
                                                                         {
                                                                             if(strcmp(main_z,"commit")=0 AND main_i<main_argc-1) then 
                                                                             {
                                                                                 main_i:=main_i+1;
                                                                                 main_commitInterval:=atoi(main_argv[main_i])
                                                                             }
                                                                             else
                                                                             {
                                                                                 if(strcmp(main_z,"journal")=0 AND main_i<main_argc-1) then 
                                                                                 {
                                                                                     main_zJMode:=main_argv[(main_i+1)];
                                                                                     main_i:=main_i+1
                                                                                 }
                                                                                 else
                                                                                 {
                                                                                     if(strcmp(main_z,"tag")=0 AND main_i<main_argc-1) then 
                                                                                     {
                                                                                         zTag:=main_argv[(main_i+1)];
                                                                                         main_i:=main_i+1
                                                                                     }
                                                                                     else
                                                                                     {
                                                                                         if(strcmp(main_z,"help")=0 OR strcmp(main_z,"?")=0) then 
                                                                                         {
                                                                                             usage()
                                                                                         }
                                                                                         else
                                                                                         {
                                                                                             skip
                                                                                         }
                                                                                     }
                                                                                 }
                                                                             }
                                                                         }
                                                                     }
                                                                 }
                                                             }
                                                         }
                                                     }
                                                 }
                                             }
                                         }
                                     }
                                 }
                             }
                         }
                     }
                 }
             }
             
         }
         else
         {
             if(main_zDbName=0) then 
             {
                 main_zDbName:=main_argv[main_i]
             }
             else
             {
                 if(main_zFileToRead=0) then 
                 {
                     main_zFileToRead:=main_argv[main_i]
                 }
                 else
                 {
                     skip
                 }
             }
         };
         main_i:=main_i+1
         
     };
     if(main_zDbName=0) then 
     {
         usage()
         
     }
     else 
     {
          skip 
     };
     if(main_zDbName[0] AND strcmp(main_zDbName,":memory:")!=0) then 
     {
         _unlink(main_zDbName) and skip
         
     }
     else 
     {
          skip 
     };
     if(sqlite3_open(main_zDbName,&db,RValue)) then 
     {
         skip
         
     }
     else 
     {
          skip 
     };
     if(main_zFileToRead) then 
     {
         main_in:=fopen(main_zFileToRead,"rb");
         if(main_in=0) then 
         {
             skip
             
         }
         else 
         {
              skip 
         }
         
     }
     else
     {
         if(main_iMode=-1) then 
         {
             skip
             
         }
         else 
         {
              skip 
         };
         main_in:=fopen(main_zFileToRead,"rb")
     };
     if(main_pageSize) then 
     {
         main_zSql:=sqlite3_mprintf("PRAGMA page_size=%d",main_pageSize,RValue);
         sqlite3_exec(db,main_zSql,0,0,0,RValue) and skip;
         sqlite3_free(main_zSql,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     if(main_cacheSize) then 
     {
         main_zSql:=sqlite3_mprintf("PRAGMA cache_size=%d",main_cacheSize,RValue);
         sqlite3_exec(db,main_zSql,0,0,0,RValue) and skip;
         sqlite3_free(main_zSql,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     if(main_noSync) then 
     {
         sqlite3_exec(db,"PRAGMA synchronous=OFF",0,0,0,RValue) and skip
     }
     else 
     {
          skip 
     };
     if(main_zJMode) then 
     {
         main_zSql:=sqlite3_mprintf("PRAGMA journal_mode=%s",main_zJMode,RValue);
         sqlite3_exec(db,main_zSql,0,0,0,RValue) and skip;
         sqlite3_free(main_zSql,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     main_iLoopCnt:=0;
     while(allLoop(main_iMode,&main_iLoopCnt,&main_iMode2,&main_useWithoutRowid,RValue))
     {
         if(main_iMode=-1) then 
         {
             if(sqlite3_exec(db,"DROP TABLE IF EXISTS wordcount; VACUUM;",0,0,0,RValue)) then 
             {
                 skip
                 
             }
             else 
             {
                  skip 
             };
             rewind(main_in) and skip
             
         }
         else 
         {
              skip 
         };
         if(sqlite3_exec(db,"BEGIN IMMEDIATE",0,0,0,RValue)) then 
         {
             skip
             
         }
         else 
         {
              skip 
         };
         main_zSql:=sqlite3_mprintf("CREATE TABLE IF NOT EXISTS wordcount(\n  word TEXT PRIMARY KEY COLLATE %s,\n  cnt INTEGER\n)%s",( if(main_useNocase) then "nocase" else "binary"),( if(main_useWithoutRowid) then " WITHOUT ROWID" else ""),RValue);
         if(main_zSql=0) then 
         {
             skip
         }
         else 
         {
              skip 
         };
         main_rc:=sqlite3_exec(db,main_zSql,0,0,0,RValue);
         int main_61_66_temp$_1 and skip;
         main_61_66_temp$_1:=sqlite3_errmsg(db,RValue);
         if(main_rc) then 
         {
             skip
         }
         else 
         {
              skip 
         };
         sqlite3_free(main_zSql,RValue) and skip;
         if(main_iMode2=5) then 
         {
             main_rc:=sqlite3_prepare_v2(db,"SELECT cnt FROM wordcount WHERE word=?1",-1,&pStmt1,0,RValue);
             int main_61_67_68_temp$_2 and skip;
             main_61_67_68_temp$_2:=sqlite3_errmsg(db,RValue);
             if(main_rc) then 
             {
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
         if(main_iMode2=2) then 
         {
             main_rc:=sqlite3_prepare_v2(db,"SELECT 1 FROM wordcount WHERE word=?1",-1,&pStmt1,0,RValue);
             int main_61_69_70_temp$_3 and skip;
             main_61_69_70_temp$_3:=sqlite3_errmsg(db,RValue);
             if(main_rc) then 
             {
                 skip
             }
             else 
             {
                  skip 
             };
             main_rc:=sqlite3_prepare_v2(db,"INSERT INTO wordcount(word,cnt) VALUES(?1,1)",-1,&stmt,0,RValue);
             int main_61_69_71_temp$_4 and skip;
             main_61_69_71_temp$_4:=sqlite3_errmsg(db,RValue);
             if(main_rc) then 
             {
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
         if(main_iMode2=2 OR main_iMode2=3 OR main_iMode2=0) then 
         {
             main_rc:=sqlite3_prepare_v2(db,"UPDATE wordcount SET cnt=cnt+1 WHERE word=?1",-1,&pstmt,0,RValue);
             int main_61_72_73_temp$_5 and skip;
             main_61_72_73_temp$_5:=sqlite3_errmsg(db,RValue);
             if(main_rc) then 
             {
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
         if(main_iMode2=0) then 
         {
             main_rc:=sqlite3_prepare_v2(db,"INSERT OR IGNORE INTO wordcount(word,cnt) VALUES(?1,1)",-1,&stmt,0,RValue);
             int main_61_74_75_temp$_6 and skip;
             main_61_74_75_temp$_6:=sqlite3_errmsg(db,RValue);
             if(main_rc) then 
             {
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
         if(main_iMode2=3) then 
         {
             main_rc:=sqlite3_prepare_v2(db,"INSERT OR IGNORE INTO wordcount(word,cnt) VALUES(?1,0)",-1,&stmt,0,RValue);
             int main_61_76_77_temp$_7 and skip;
             main_61_76_77_temp$_7:=sqlite3_errmsg(db,RValue);
             if(main_rc) then 
             {
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
         if(main_iMode2=1) then 
         {
             main_rc:=sqlite3_prepare_v2(db,"REPLACE INTO wordcount(word,cnt)VALUES(?1,coalesce((SELECT cnt FROM wordcount WHERE word=?1),0)+1)",-1,&stmt,0,RValue);
             int main_61_78_79_temp$_8 and skip;
             main_61_78_79_temp$_8:=sqlite3_errmsg(db,RValue);
             if(main_rc) then 
             {
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
         if(main_iMode2=4) then 
         {
             main_rc:=sqlite3_prepare_v2(db,"DELETE FROM wordcount WHERE word=?1",-1,&pStmt2,0,RValue);
             int main_61_80_81_temp$_9 and skip;
             main_61_80_81_temp$_9:=sqlite3_errmsg(db,RValue);
             if(main_rc) then 
             {
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
         while(fgets(main_zInput,2000,main_in))
         {
             continue<==0 and skip;
             main_i:=0;
             
             while(main_zInput[main_i])
             {
                  continue<==0 and skip;
                 if(!isalpha((unsigned char)(main_zInput[main_i]))) then 
                 {
                     continue<==1 and skip;
                      main_i:=main_i+1
                 }
                 else 
                 {
                      skip 
                 };
                 if(continue=0)   then 
                 {
                     main_j:=main_i+1;
                     
                     while(isalpha((unsigned char)(main_zInput[main_j])))
                     {
                         main_j:=main_j+1
                         
                     };
                     if(main_iMode2=4) then 
                     {
                         sqlite3_bind_text(pStmt2,1,main_zInput+main_i,main_j-main_i,0,RValue) and skip;
                         if(sqlite3_step(pStmt2,RValue)!=101) then 
                         {
                             int main_61_82_84_85_temp$_10 and skip;
                             main_61_82_84_85_temp$_10:=sqlite3_errmsg(db,RValue);
                             skip
                             
                         }
                         else 
                         {
                              skip 
                         };
                         sqlite3_reset(pStmt2,RValue) and skip
                         
                     }
                     else
                     {
                         if(main_iMode2=2) then 
                         {
                             sqlite3_bind_text(pStmt1,1,main_zInput+main_i,main_j-main_i,0,RValue) and skip;
                             main_rc:=sqlite3_step(pStmt1,RValue);
                             sqlite3_reset(pStmt1,RValue) and skip;
                             if(main_rc=100) then 
                             {
                                 sqlite3_bind_text(pstmt,1,main_zInput+main_i,main_j-main_i,0,RValue) and skip;
                                 if(sqlite3_step(pstmt,RValue)!=101) then 
                                 {
                                     int main_61_82_86_87_88_89_temp$_11 and skip;
                                     main_61_82_86_87_88_89_temp$_11:=sqlite3_errmsg(db,RValue);
                                     skip
                                     
                                 }
                                 else 
                                 {
                                      skip 
                                 };
                                 sqlite3_reset(pstmt,RValue) and skip
                             }
                             else
                             {
                                 if(main_rc=101) then 
                                 {
                                     sqlite3_bind_text(stmt,1,main_zInput+main_i,main_j-main_i,0,RValue) and skip;
                                     if(sqlite3_step(stmt,RValue)!=101) then 
                                     {
                                         int main_61_82_86_87_90_91_92_temp$_12 and skip;
                                         main_61_82_86_87_90_91_92_temp$_12:=sqlite3_errmsg(db,RValue);
                                         skip
                                         
                                     }
                                     else 
                                     {
                                          skip 
                                     };
                                     sqlite3_reset(stmt,RValue) and skip
                                 }
                                 else
                                 {
                                     int main_61_82_86_87_90_93_temp$_13 and skip;
                                     main_61_82_86_87_90_93_temp$_13:=sqlite3_errmsg(db,RValue);
                                     skip
                                 }
                             }
                         }
                         else
                         {
                             if(main_iMode2=5) then 
                             {
                                 sqlite3_bind_text(pStmt1,1,main_zInput+main_i,main_j-main_i,0,RValue) and skip;
                                 if(sqlite3_step(pStmt1,RValue)=100) then 
                                 {
                                     main_sumCnt:=main_sumCnt+sqlite3_column_int64(pStmt1,0,RValue)
                                     
                                 }
                                 else 
                                 {
                                      skip 
                                 };
                                 sqlite3_reset(pStmt1,RValue) and skip
                             }
                             else
                             {
                                 sqlite3_bind_text(stmt,1,main_zInput+main_i,main_j-main_i,0,RValue) and skip;
                                 if(sqlite3_step(stmt,RValue)!=101) then 
                                 {
                                     int main_61_82_86_94_97_98_temp$_14 and skip;
                                     main_61_82_86_94_97_98_temp$_14:=sqlite3_errmsg(db,RValue);
                                     skip
                                     
                                 }
                                 else 
                                 {
                                      skip 
                                 };
                                 sqlite3_reset(stmt,RValue) and skip;
                                 if(main_iMode2=3 OR (main_iMode2=0 AND sqlite3_changes(db,RValue)=0)) then 
                                 {
                                     sqlite3_bind_text(pstmt,1,main_zInput+main_i,main_j-main_i,0,RValue) and skip;
                                     if(sqlite3_step(pstmt,RValue)!=101) then 
                                     {
                                         int main_61_82_86_94_97_99_100_temp$_15 and skip;
                                         main_61_82_86_94_97_99_100_temp$_15:=sqlite3_errmsg(db,RValue);
                                         skip
                                         
                                     }
                                     else 
                                     {
                                          skip 
                                     };
                                     sqlite3_reset(pstmt,RValue) and skip
                                     
                                 }
                                 else 
                                 {
                                      skip 
                                 }
                             }
                         }
                     };
                     main_i:=main_j-1;
                     main_nOp:=main_nOp+1;
                     if(main_commitInterval>0 AND (main_nOp % main_commitInterval)=0) then 
                     {
                         sqlite3_exec(db,"COMMIT; BEGIN IMMEDIATE",0,0,0,RValue) and skip
                         
                     }
                     else 
                     {
                          skip 
                     };
                     main_i:=main_i+1
                 }
                 else
                 {
                     skip
                 }
             };
             continue<==0 and skip
         };
         sqlite3_exec(db,"COMMIT",0,0,0,RValue) and skip;
         sqlite3_finalize(stmt,RValue) and skip;
         stmt:=0;
         sqlite3_finalize(pstmt,RValue) and skip;
         pstmt:=0;
         sqlite3_finalize(pStmt1,RValue) and skip;
         pStmt1:=0;
         sqlite3_finalize(pStmt2,RValue) and skip;
         pStmt2:=0;
         if(main_iMode2=5 AND main_iMode!=-1) then 
         {
             output (zTag," sum of cnt: ",main_sumCnt,"\n","\n") and skip;
             main_rc:=sqlite3_prepare_v2(db,"SELECT sum(cnt*cnt) FROM wordcount",-1,&pStmt1,0,RValue);
             if(main_rc=0 AND sqlite3_step(pStmt1,RValue)=100) then 
             {
                 output (zTag," double-check: ",sqlite3_column_int64(pStmt1,0,RValue),"\n","\n") and skip
                 
             }
             else 
             {
                  skip 
             };
             sqlite3_finalize(pStmt1,RValue) and skip
             
         }
         else 
         {
              skip 
         }
     };
     if(main_zFileToRead) then 
     {
         fclose(main_in) and skip
     }
     else 
     {
          skip 
     };
     if(main_showStats) then 
     {
         sqlite3_db_status(db,0,&main_iCur,&main_iHiwtr,0,RValue) and skip;
         output (zTag," Lookaside Slots Used:        ",main_iCur," (max ",main_iHiwtr,")\n",")\n") and skip;
         sqlite3_db_status(db,4,&main_iCur,&main_iHiwtr,0,RValue) and skip;
         output (zTag," Successful lookasides:       ",main_iHiwtr,"\n","\n") and skip;
         sqlite3_db_status(db,5,&main_iCur,&main_iHiwtr,0,RValue) and skip;
         output (zTag," Lookaside size faults:       ",main_iHiwtr,"\n","\n") and skip;
         sqlite3_db_status(db,6,&main_iCur,&main_iHiwtr,0,RValue) and skip;
         output (zTag," Lookaside OOM faults:        ",main_iHiwtr,"\n","\n") and skip;
         sqlite3_db_status(db,1,&main_iCur,&main_iHiwtr,0,RValue) and skip;
         output (zTag," Pager Heap Usage:            ",main_iCur," bytes\n"," bytes\n") and skip;
         sqlite3_db_status(db,7,&main_iCur,&main_iHiwtr,1,RValue) and skip;
         output (zTag," Page cache hits:             ",main_iCur,"\n","\n") and skip;
         sqlite3_db_status(db,8,&main_iCur,&main_iHiwtr,1,RValue) and skip;
         output (zTag," Page cache misses:           ",main_iCur,"\n","\n") and skip;
         sqlite3_db_status(db,9,&main_iCur,&main_iHiwtr,1,RValue) and skip;
         output (zTag," Page cache writes:           ",main_iCur,"\n","\n") and skip;
         sqlite3_db_status(db,2,&main_iCur,&main_iHiwtr,0,RValue) and skip;
         output (zTag," Schema Heap Usage:           ",main_iCur," bytes\n"," bytes\n") and skip;
         sqlite3_db_status(db,3,&main_iCur,&main_iHiwtr,0,RValue) and skip;
         output (zTag," Statement Heap Usage:        ",main_iCur," bytes\n"," bytes\n") and skip
         
     }
     else 
     {
          skip 
     };
     sqlite3_close(db,RValue) and skip;
     if(main_showStats) then 
     {
         sqlite3_status(0,&main_iCur,&main_iHiwtr,0,RValue) and skip;
         output (zTag," Memory Used (bytes):         ",main_iCur," (max ",main_iHiwtr,")\n",")\n") and skip;
         sqlite3_status(9,&main_iCur,&main_iHiwtr,0,RValue) and skip;
         output (zTag," Outstanding Allocations:     ",main_iCur," (max ",main_iHiwtr,")\n",")\n") and skip;
         sqlite3_status(2,&main_iCur,&main_iHiwtr,0,RValue) and skip;
         output (zTag," Pcache Overflow Bytes:       ",main_iCur," (max ",main_iHiwtr,")\n",")\n") and skip;
         sqlite3_status(4,&main_iCur,&main_iHiwtr,0,RValue) and skip;
         output (zTag," Scratch Overflow Bytes:      ",main_iCur," (max ",main_iHiwtr,")\n",")\n") and skip;
         sqlite3_status(5,&main_iCur,&main_iHiwtr,0,RValue) and skip;
         output (zTag," Largest Allocation:          ",main_iHiwtr," bytes\n"," bytes\n") and skip;
         sqlite3_status(7,&main_iCur,&main_iHiwtr,0,RValue) and skip;
         output (zTag," Largest Pcache Allocation:   ",main_iHiwtr," bytes\n"," bytes\n") and skip;
         sqlite3_status(8,&main_iCur,&main_iHiwtr,0,RValue) and skip;
         output (zTag," Largest Scratch Allocation:  ",main_iHiwtr," bytes\n"," bytes\n") and skip
         
     }
     else 
     {
          skip 
     };
     return<==1 and RValue:=0;
     skip
     )
 };
  main(RValue)
 )
