</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

frame(zHelp,db,pstmt,iStart,iTotal,bWithoutRowid,bReprepare,bSqlOnly,bExplain,bVerify,bMemShrink,eTemp,szTest,nRepeat,zWR,zNN,zPK,x,y,nResult,zResult,zName,zDots,zSqlSpeedtest1,zSqlPrepare,doAutovac,cacheSize,doExclusive,nHeap,mnHeap,doIncrvac,zJMode,zKey,nLook,szLook,noSync,pageSize,nPCache,szPCache,doPCache,nScratch,szScratch,showStats,nThread,mmapSize,zTSet,doTrace,zEncoding,zDbName,pHeap,pLook,pPCache,pScratch,iCur,iHi,i,rc) and (
char zHelp[2090]<=="Usage: %s [--options] DATABASE\nOptions:\n  --autovacuum        Enable AUTOVACUUM mode\n  --cachesize N       Set the cache size to N\n  --exclusive         Enable locking_mode=EXCLUSIVE\n  --explain           Like --sqlonly but with added EXPLAIN keywords\n  --heap SZ MIN       Memory allocator uses SZ bytes & min allocation MIN\n  --incrvacuum        Enable incremenatal vacuum mode\n  --journal M         Set the journal_mode to M\n  --key KEY           Set the encryption key to KEY\n  --lookaside N SZ    Configure lookaside for N slots of SZ bytes each\n  --mmap SZ           MMAP the first SZ bytes of the database file\n  --multithread       Set multithreaded mode\n  --nomemstat         Disable memory statistics\n  --nosync            Set PRAGMA synchronous=OFF\n  --notnull           Add NOT NULL constraints to table columns\n  --pagesize N        Set the page size to N\n  --pcache N SZ       Configure N pages of pagecache each of size SZ bytes\n  --primarykey        Use PRIMARY KEY instead of UNIQUE where appropriate\n  --repeat N          Repeat each SELECT N times (default: 1)\n  --reprepare         Reprepare each statement upon every invocation\n  --scratch N SZ      Configure scratch memory for N slots of SZ bytes each\n  --serialized        Set serialized threading mode\n  --singlethread      Set single-threaded mode - disables all mutexing\n  --sqlonly           No-op.  Only show the SQL that would have been run.\n  --shrink-memory     Invoke sqlite3_db_release_memory() frequently.\n  --size N            Relative test size.  Default=100\n  --stats             Show statistics at the end\n  --temp N            N from 0 to 9.  0: no temp table. 9: all temp tables\n  --testset T         Run test-set T (main, cte, rtree, orm, debug)\n  --trace             Turn on SQL tracing\n  --threads N         Use up to N threads for sorting\n  --utf16be           Set text encoding to UTF-16BE\n  --utf16le           Set text encoding to UTF-16LE\n  --verify            Run additional verification steps.\n  --without-rowid     Use WITHOUT ROWID where appropriate\n" and skip;
int iStart and skip;
int iTotal and skip;
int bWithoutRowid and skip;
int bReprepare and skip;
int bSqlOnly and skip;
int bExplain and skip;
int bVerify and skip;
int bMemShrink and skip;
int eTemp and skip;
int szTest and skip;
int nRepeat and skip;
char *zWR and skip;
char *zNN and skip;
char *zPK and skip;
int x,y and skip;
int nResult and skip;
char zResult[3000] and skip;
 function isTemp ( int N,char* RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=( if(eTemp>=N) then " TEMP" else "");
     skip
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
  function speedtest1_random ( int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     x:=(x>>1) ^ ((1+~(x & 1)) & 0xd0000001);
     y:=y*1103515245+12345;
     return<==1 and RValue:=x ^ y;
     skip
     )
     }; 
  function swizzle ( int in,int limit,int RValue )
 {
     frame(swizzle_out,return) and ( 
     int return<==0 and skip;
     int swizzle_out<==0 and skip;
     while(limit)
     {
         swizzle_out:=(swizzle_out<<1) | (in & 1);
         in:=in>> (1 );
         limit:=limit>> (1 )
     };
     return<==1 and RValue:=swizzle_out;
     skip
     )
     }; 
  function roundup_allones ( int limit,int RValue )
 {
     frame(roundup_allones_m,return) and ( 
     int return<==0 and skip;
     int roundup_allones_m<==1 and skip;
     while(roundup_allones_m<limit)
     {
         roundup_allones_m:=(roundup_allones_m<<1)+1
     };
     return<==1 and RValue:=roundup_allones_m;
     skip
     )
     }; 
      char *zName and skip;
     char zDots[72]<=="......................................................................." and skip;
 function speedtest1_begin_test ( int iTestNum,char *zName )
 {
     frame(speedtest1_begin_test_n) and ( 
     int speedtest1_begin_test_n and skip;
     speedtest1_begin_test_n:=(int)strlen(zName);
     if(bSqlOnly) then 
     {
         printf("/* %4d - %s%.*s */\n", iTestNum, zName, 60-speedtest1_begin_test_n, zDots) and skip
         
     }
     else
     {
		 printf("%4d - %s%.*s ", iTestNum, zName, 60-speedtest1_begin_test_n, zDots) and skip;
         fflush(stdout) and skip
     };
     sqlite3_free(zName,RValue) and skip;
     nResult:=0;
     x:=0xad131d0b;
     y:=0x44f9eac8
     )
     }; 
  function speedtest1_end_test()
 {
     frame(speedtest1_end_test_iElapseTime) and ( 
     int speedtest1_end_test_iElapseTime<==iStart and skip;
     if(!bSqlOnly) then 
     {
         iTotal:=iTotal+speedtest1_end_test_iElapseTime;
		 printf("%4d.%03ds\n", (int)(speedtest1_end_test_iElapseTime/1000), (int)(speedtest1_end_test_iElapseTime%1000)) and skip
         
     }
     else 
     {
          skip 
     };
     if(pstmt) then 
     {
         sqlite3_finalize(pstmt,RValue) and skip;
         pstmt:=0
         
     }
     else 
     {
          skip 
     }
     )
     }; 
  function speedtest1_final (  )
 {
     if(!bSqlOnly) then 
     {
	 		 printf("       TOTAL%.*s %4d.%03ds\n", 60-5, zDots,
           (int)(iTotal/1000), (int)(iTotal/1000)) and skip
         
     }
     else 
     {
          skip 
     }
     
 };
 function printSql ( char *zSql )
 {
     frame(printSql_n) and ( 
     int printSql_n and skip;
     printSql_n:=(int)strlen(zSql);
     while(printSql_n>0 AND (zSql[printSql_n-1]=';' OR isspace((unsigned char)(zSql[printSql_n-1]))))
     {
         printSql_n:=printSql_n-1
     };
     if(bExplain) then 
     {
         output ("EXPLAIN ") and skip
     }
     else 
     {
          skip 
     };
     output (printSql_n,";\n",";\n") and skip;
     if(bExplain AND (sqlite3_strglob("CREATE *",zSql,RValue)=0 OR sqlite3_strglob("DROP *",zSql,RValue)=0 OR sqlite3_strglob("ALTER *",zSql,RValue)=0)) then 
     {
         output (printSql_n,";\n",";\n") and skip
         
     }
     else 
     {
          skip 
     }
     )
     }; 
  function speedtest1_shrink_memory (  )
 {
     if(bMemShrink) then 
     {
         sqlite3_db_release_memory(db,RValue) and skip
     }
     else 
     {
          skip 
     }
     
 };
 char *zSqlSpeedtest1 and skip;
 function speedtest1_exec ( char *zSqlSpeedtest1 )
 {
     frame(speedtest1_exec_2_zErrMsg,speedtest1_exec_2_rc) and ( 
     if(bSqlOnly) then 
     {
         printSql(zSqlSpeedtest1)
         
     }
     else
     {
         char *speedtest1_exec_2_zErrMsg<==0 and skip;
         int speedtest1_exec_2_rc and skip;
         speedtest1_exec_2_rc:=sqlite3_exec(db,zSqlSpeedtest1,0,0,&speedtest1_exec_2_zErrMsg,RValue)
     };
     speedtest1_shrink_memory()
     )
     }; 
      char *zSqlPrepare and skip;
 function speedtest1_prepare ( char *zSqlPrepare )
 {
     frame(speedtest1_prepare_2_rc) and ( 
     if(bSqlOnly) then 
     {
         printSql(zSqlPrepare)
         
     }
     else
     {
         int speedtest1_prepare_2_rc and skip;
         if(pstmt) then 
         {
             sqlite3_finalize(pstmt,RValue) and skip
         }
         else 
         {
              skip 
         };
         speedtest1_prepare_2_rc:=sqlite3_prepare_v2(db,zSqlPrepare,-1,&pstmt,0,RValue)
     };
     sqlite3_free(zSqlPrepare,RValue) and skip
     )
     }; 
  function speedtest1_run (  )
 {
     frame(speedtest1_run_i,speedtest1_run_n,speedtest1_run_len$,speedtest1_run_2_z,speedtest1_run_6_pNew,speedtest1_run_6_temp$_1,return) and ( 
     int return<==0 and skip;
     int speedtest1_run_i,speedtest1_run_n,speedtest1_run_len$ and skip;
     if(bSqlOnly) then 
     {
          return<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         nResult:=0;
         while(sqlite3_step(pstmt,RValue)=100)
         {
             speedtest1_run_n:=sqlite3_column_count(pstmt,RValue);
             speedtest1_run_i:=0;
             
             while(speedtest1_run_i<speedtest1_run_n)
             {
                 char *speedtest1_run_2_z and skip;
                 speedtest1_run_2_z:=(char *)sqlite3_column_text(pstmt,speedtest1_run_i,RValue);
                 if(speedtest1_run_2_z=0) then 
                 {
                     speedtest1_run_2_z:="nil"
                 }
                 else 
                 {
                      skip 
                 };
                 speedtest1_run_len$:=(int)strlen(speedtest1_run_2_z);
                 if(nResult+speedtest1_run_len$<3000-2) then 
                 {
                     if(nResult>0) then 
                     {
                         zResult[nResult]:=' ';
                         nResult:=nResult+1
                     }
                     else 
                     {
                          skip 
                     };
                     memcpy(zResult+nResult,speedtest1_run_2_z,speedtest1_run_len$+1) and skip;
                     nResult:=nResult+speedtest1_run_len$
                     
                 }
                 else 
                 {
                      skip 
                 };
                 speedtest1_run_i:=speedtest1_run_i+1
                 
             }
         };
         if(bReprepare) then 
         {
             int speedtest1_run_6_temp$_1 and skip;
             speedtest1_run_6_temp$_1:=sqlite3_sql(pstmt,RValue);
             sqlite3_prepare_v2(db,speedtest1_run_6_temp$_1,-1,&stmt,0,RValue) and skip;
             sqlite3_finalize(pstmt,RValue) and skip;
             pstmt:=stmt
             
         }
         else
         {
             sqlite3_reset(pstmt,RValue) and skip
         };
         speedtest1_shrink_memory()
     }
     else
     {
         skip
     }
     )
     }; 
  function traceCallback ( void *NotUsed,char *zSql )
 {
     frame(traceCallback_n) and ( 
     int traceCallback_n and skip;
     traceCallback_n:=(int)strlen(zSql);
     while(traceCallback_n>0 AND (zSql[traceCallback_n-1]=';' OR isspace((unsigned char)(zSql[traceCallback_n-1]))))
     {
         traceCallback_n:=traceCallback_n-1
     };
     fprintf(stderr,"%.*s;\n",traceCallback_n,zSql) and skip
     )
     }; 
  function est_square_root ( int x,int RValue )
 {
     frame(est_square_root_y0,est_square_root_y1,est_square_root_n,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     int est_square_root_y0<==x/ 2 and skip;
     int est_square_root_y1 and skip;
     int est_square_root_n and skip;
     break$<==0 and skip;
     est_square_root_n:=0;
     
     while( break$=0 AND  est_square_root_y0>0 AND est_square_root_n<10)
     {
         est_square_root_y1:=(est_square_root_y0+x/ est_square_root_y0)/ 2;
         if(est_square_root_y1=est_square_root_y0) then 
         {
             break$<==1 and skip
          }
         else 
         {
              skip 
         };
         if(break$=0)   then
         {
             est_square_root_y0:=est_square_root_y1;
             est_square_root_n:=est_square_root_n+1
         }
         else
         {
             skip
         }
         
     };
     break$<==0 and skip;
     return<==1 and RValue:=est_square_root_y0;
     skip
     )
     }; 
  function testset_main (  )
 {
     frame(verifystat,testset_main_i,testset_main_n,testset_main_sz,testset_main_maxb,testset_main_x1,testset_main_x2,testset_main_len$,testset_main_zNum,testset_main_temp$_1,testset_main_temp$_2,testset_main_temp$_3,testset_main_temp$_4,testset_main_temp$_5,testset_main_temp$_6,testset_main_temp$_7,testset_main_temp$_8) and ( 
     int testset_main_i and skip;
     int testset_main_n and skip;
     int testset_main_sz and skip;
     int testset_main_maxb and skip;
     int testset_main_x1<==0,testset_main_x2<==0 and skip;
     int testset_main_len$<==0 and skip;
     char testset_main_zNum[2000] and skip;
     testset_main_n<==szTest and testset_main_sz<==testset_main_n and skip;
     testset_main_zNum[0]:=0;
     testset_main_maxb:=roundup_allones(testset_main_sz,RValue);
     zName:=sqlite3_mprintf("%d INSERTs into table with no index",testset_main_n,RValue);
     speedtest1_begin_test(100,zName);
     speedtest1_exec("BEGIN");
     char* testset_main_temp$_1 and skip;
     testset_main_temp$_1:=isTemp(9,RValue);
     zSqlSpeedtest1:=sqlite3_mprintf("CREATE%s TABLE t1(a INTEGER %s, b INTEGER %s, c TEXT %s);",testset_main_temp$_1,zNN,zNN,zNN,RValue);
     speedtest1_exec(zSqlSpeedtest1);
     zSqlPrepare:=sqlite3_mprintf("INSERT INTO t1 VALUES(?1,?2,?3); --  %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     int verifystat<==0 and skip;
	 while(verifystat<47800421)
	 {
		verifystat:=verifystat+1
	 };
     while(testset_main_i<=testset_main_n)
     {
         testset_main_x1:=swizzle(testset_main_i,testset_main_maxb,RValue);
         speedtest1_numbername(testset_main_x1,testset_main_zNum,2000,RValue) and skip;
         sqlite3_bind_int64(pstmt,1,(int)testset_main_x1,RValue) and skip;
         sqlite3_bind_int(pstmt,2,testset_main_i,RValue) and skip;
         sqlite3_bind_text(pstmt,3,testset_main_zNum,-1,0,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     testset_main_n:=testset_main_sz;
     zName:=sqlite3_mprintf("%d ordered INSERTS with one index/PK",testset_main_n,RValue);
     speedtest1_begin_test(110,zName);
     speedtest1_exec("BEGIN");
     char* testset_main_temp$_2 and skip;
     testset_main_temp$_2:=isTemp(5,RValue);
     zSqlSpeedtest1:=sqlite3_mprintf("CREATE%s TABLE t2(a INTEGER %s %s, b INTEGER %s, c TEXT %s) %s",testset_main_temp$_2,zNN,zPK,zNN,zNN,zWR,RValue);
     speedtest1_exec(zSqlSpeedtest1);
     zSqlPrepare:=sqlite3_mprintf("INSERT INTO t2 VALUES(?1,?2,?3); -- %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         testset_main_x1:=swizzle(testset_main_i,testset_main_maxb,RValue);
         speedtest1_numbername(testset_main_x1,testset_main_zNum,2000,RValue) and skip;
         sqlite3_bind_int(pstmt,1,testset_main_i,RValue) and skip;
         sqlite3_bind_int64(pstmt,2,(int)testset_main_x1,RValue) and skip;
         sqlite3_bind_text(pstmt,3,testset_main_zNum,-1,0,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     testset_main_n:=testset_main_sz;
     zName:=sqlite3_mprintf("%d unordered INSERTS with one index/PK",testset_main_n,RValue);
     speedtest1_begin_test(120,zName);
     speedtest1_exec("BEGIN");
     char* testset_main_temp$_3 and skip;
     testset_main_temp$_3:=isTemp(3,RValue);
     zSqlSpeedtest1:=sqlite3_mprintf("CREATE%s TABLE t3(a INTEGER %s %s, b INTEGER %s, c TEXT %s) %s",testset_main_temp$_3,zNN,zPK,zNN,zNN,zWR,RValue);
     speedtest1_exec(zSqlSpeedtest1);
     zSqlPrepare:=sqlite3_mprintf("INSERT INTO t3 VALUES(?1,?2,?3); -- %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         testset_main_x1:=swizzle(testset_main_i,testset_main_maxb,RValue);
         speedtest1_numbername(testset_main_x1,testset_main_zNum,2000,RValue) and skip;
         sqlite3_bind_int(pstmt,2,testset_main_i,RValue) and skip;
         sqlite3_bind_int64(pstmt,1,(int)testset_main_x1,RValue) and skip;
         sqlite3_bind_text(pstmt,3,testset_main_zNum,-1,0,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     testset_main_n:=25;
     zName:=sqlite3_mprintf("%d SELECTS, numeric BETWEEN, unindexed",testset_main_n,RValue);
     speedtest1_begin_test(130,zName);
     speedtest1_exec("BEGIN");
     zSqlPrepare:=sqlite3_mprintf("SELECT count(*), avg(b), sum(length(c)), group_concat(c) FROM t1\n WHERE b BETWEEN ?1 AND ?2; -- %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         if((testset_main_i-1) % nRepeat=0) then 
         {
             testset_main_x1:=speedtest1_random(RValue) % testset_main_maxb;
             testset_main_x2:=speedtest1_random(RValue) % 10+testset_main_sz/ 5000+testset_main_x1
             
         }
         else 
         {
              skip 
         };
         sqlite3_bind_int(pstmt,1,testset_main_x1,RValue) and skip;
         sqlite3_bind_int(pstmt,2,testset_main_x2,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     testset_main_n:=10;
     zName:=sqlite3_mprintf("%d SELECTS, LIKE, unindexed",testset_main_n,RValue);
     speedtest1_begin_test(140,zName);
     speedtest1_exec("BEGIN");
     zSqlPrepare:=sqlite3_mprintf("SELECT count(*), avg(b), sum(length(c)), group_concat(c) FROM t1\n WHERE c LIKE ?1; -- %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         if((testset_main_i-1) % nRepeat=0) then 
         {
             testset_main_x1:=speedtest1_random(RValue) % testset_main_maxb;
             testset_main_zNum[0]:='%';
             testset_main_len$:=speedtest1_numbername(testset_main_i,testset_main_zNum+1,2000-2,RValue);
             testset_main_zNum[testset_main_len$]:='%';
             testset_main_zNum[testset_main_len$+1]:=0
             
         }
         else 
         {
              skip 
         };
         sqlite3_bind_text(pstmt,1,testset_main_zNum,testset_main_len$+1,0,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     testset_main_n:=10;
     zName:=sqlite3_mprintf("%d SELECTS w/ORDER BY, unindexed",testset_main_n,RValue);
     speedtest1_begin_test(142,zName);
     speedtest1_exec("BEGIN");
     zSqlPrepare:=sqlite3_mprintf("SELECT a, b, c FROM t1 WHERE c LIKE ?1\n ORDER BY a; -- %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         if((testset_main_i-1) % nRepeat=0) then 
         {
             testset_main_x1:=speedtest1_random(RValue) % testset_main_maxb;
             testset_main_zNum[0]:='%';
             testset_main_len$:=speedtest1_numbername(testset_main_i,testset_main_zNum+1,2000-2,RValue);
             testset_main_zNum[testset_main_len$]:='%';
             testset_main_zNum[testset_main_len$+1]:=0
             
         }
         else 
         {
              skip 
         };
         sqlite3_bind_text(pstmt,1,testset_main_zNum,testset_main_len$+1,0,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     testset_main_n:=10;
     zName:=sqlite3_mprintf("%d SELECTS w/ORDER BY and LIMIT, unindexed",testset_main_n,RValue);
     speedtest1_begin_test(145,zName);
     speedtest1_exec("BEGIN");
     zSqlPrepare:=sqlite3_mprintf("SELECT a, b, c FROM t1 WHERE c LIKE ?1\n ORDER BY a LIMIT 10; -- %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         if((testset_main_i-1) % nRepeat=0) then 
         {
             testset_main_x1:=speedtest1_random(RValue) % testset_main_maxb;
             testset_main_zNum[0]:='%';
             testset_main_len$:=speedtest1_numbername(testset_main_i,testset_main_zNum+1,2000-2,RValue);
             testset_main_zNum[testset_main_len$]:='%';
             testset_main_zNum[testset_main_len$+1]:=0
             
         }
         else 
         {
              skip 
         };
         sqlite3_bind_text(pstmt,1,testset_main_zNum,testset_main_len$+1,0,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     zName:=sqlite3_mprintf("CREATE INDEX five times",RValue);
     speedtest1_begin_test(150,zName);
     speedtest1_exec("BEGIN;");
     speedtest1_exec("CREATE UNIQUE INDEX t1b ON t1(b);");
     speedtest1_exec("CREATE INDEX t1c ON t1(c);");
     speedtest1_exec("CREATE UNIQUE INDEX t2b ON t2(b);");
     speedtest1_exec("CREATE INDEX t2c ON t2(c DESC);");
     speedtest1_exec("CREATE INDEX t3bc ON t3(b,c);");
     speedtest1_exec("COMMIT;");
     speedtest1_end_test();
     testset_main_n:=testset_main_sz/ 5;
     zName:=sqlite3_mprintf("%d SELECTS, numeric BETWEEN, indexed",testset_main_n,RValue);
     speedtest1_begin_test(160,zName);
     speedtest1_exec("BEGIN");
     zSqlPrepare:=sqlite3_mprintf("SELECT count(*), avg(b), sum(length(c)), group_concat(a) FROM t1\n WHERE b BETWEEN ?1 AND ?2; -- %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         if((testset_main_i-1) % nRepeat=0) then 
         {
             testset_main_x1:=speedtest1_random(RValue) % testset_main_maxb;
             testset_main_x2:=speedtest1_random(RValue) % 10+testset_main_sz/ 5000+testset_main_x1
             
         }
         else 
         {
              skip 
         };
         sqlite3_bind_int(pstmt,1,testset_main_x1,RValue) and skip;
         sqlite3_bind_int(pstmt,2,testset_main_x2,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     testset_main_n:=testset_main_sz/ 5;
     zName:=sqlite3_mprintf("%d SELECTS, numeric BETWEEN, PK",testset_main_n,RValue);
     speedtest1_begin_test(161,zName);
     speedtest1_exec("BEGIN");
     zSqlPrepare:=sqlite3_mprintf("SELECT count(*), avg(b), sum(length(c)), group_concat(a) FROM t2\n WHERE a BETWEEN ?1 AND ?2; -- %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         if((testset_main_i-1) % nRepeat=0) then 
         {
             testset_main_x1:=speedtest1_random(RValue) % testset_main_maxb;
             testset_main_x2:=speedtest1_random(RValue) % 10+testset_main_sz/ 5000+testset_main_x1
             
         }
         else 
         {
              skip 
         };
         sqlite3_bind_int(pstmt,1,testset_main_x1,RValue) and skip;
         sqlite3_bind_int(pstmt,2,testset_main_x2,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     testset_main_n:=testset_main_sz/ 5;
     zName:=sqlite3_mprintf("%d SELECTS, text BETWEEN, indexed",testset_main_n,RValue);
     speedtest1_begin_test(170,zName);
     speedtest1_exec("BEGIN");
     zSqlPrepare:=sqlite3_mprintf("SELECT count(*), avg(b), sum(length(c)), group_concat(a) FROM t1\n WHERE c BETWEEN ?1 AND (?1||'~'); -- %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         if((testset_main_i-1) % nRepeat=0) then 
         {
             testset_main_x1:=swizzle(testset_main_i,testset_main_maxb,RValue);
             testset_main_len$:=speedtest1_numbername(testset_main_x1,testset_main_zNum,2000-1,RValue)
             
         }
         else 
         {
              skip 
         };
         sqlite3_bind_text(pstmt,1,testset_main_zNum,testset_main_len$,0,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     testset_main_n:=testset_main_sz;
     zName:=sqlite3_mprintf("%d INSERTS with three indexes",testset_main_n,RValue);
     speedtest1_begin_test(180,zName);
     speedtest1_exec("BEGIN");
     char* testset_main_temp$_4 and skip;
     testset_main_temp$_4:=isTemp(1,RValue);
     zSqlSpeedtest1:=sqlite3_mprintf("CREATE%s TABLE t4(\n  a INTEGER %s %s,\n  b INTEGER %s,\n  c TEXT %s\n) %s",testset_main_temp$_4,zNN,zPK,zNN,zNN,zWR,RValue);
     speedtest1_exec(zSqlSpeedtest1);
     speedtest1_exec("CREATE INDEX t4b ON t4(b)");
     speedtest1_exec("CREATE INDEX t4c ON t4(c)");
     speedtest1_exec("INSERT INTO t4 SELECT * FROM t1");
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     testset_main_n:=testset_main_sz;
     zName:=sqlite3_mprintf("DELETE and REFILL one table",testset_main_n,RValue);
     speedtest1_begin_test(190,zName);
     speedtest1_exec("DELETE FROM t2;");
     speedtest1_exec("INSERT INTO t2 SELECT * FROM t1;");
     speedtest1_end_test();
     zName:=sqlite3_mprintf("VACUUM",RValue);
     speedtest1_begin_test(200,zName);
     speedtest1_exec("VACUUM");
     speedtest1_end_test();
     zName:=sqlite3_mprintf("ALTER TABLE ADD COLUMN, and query",RValue);
     speedtest1_begin_test(210,zName);
     speedtest1_exec("ALTER TABLE t2 ADD COLUMN d DEFAULT 123");
     speedtest1_exec("SELECT sum(d) FROM t2");
     speedtest1_end_test();
     testset_main_n:=testset_main_sz/ 5;
     zName:=sqlite3_mprintf("%d UPDATES, numeric BETWEEN, indexed",testset_main_n,RValue);
     speedtest1_begin_test(230,zName);
     speedtest1_exec("BEGIN");
     zSqlPrepare:=sqlite3_mprintf("UPDATE t2 SET d=b*2 WHERE b BETWEEN ?1 AND ?2; -- %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         testset_main_x1:=speedtest1_random(RValue) % testset_main_maxb;
         testset_main_x2:=speedtest1_random(RValue) % 10+testset_main_sz/ 5000+testset_main_x1;
         sqlite3_bind_int(pstmt,1,testset_main_x1,RValue) and skip;
         sqlite3_bind_int(pstmt,2,testset_main_x2,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     testset_main_n:=testset_main_sz;
     zName:=sqlite3_mprintf("%d UPDATES of individual rows",testset_main_n,RValue);
     speedtest1_begin_test(240,zName);
     speedtest1_exec("BEGIN");
     zSqlPrepare:=sqlite3_mprintf("UPDATE t2 SET d=b*3 WHERE a=?1; -- %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         testset_main_x1:=speedtest1_random(RValue) % testset_main_sz+1;
         sqlite3_bind_int(pstmt,1,testset_main_x1,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     zName:=sqlite3_mprintf("One big UPDATE of the whole %d-row table",testset_main_sz,RValue);
     speedtest1_begin_test(250,zName);
     speedtest1_exec("UPDATE t2 SET d=b*4");
     speedtest1_end_test();
     zName:=sqlite3_mprintf("Query added column after filling",RValue);
     speedtest1_begin_test(260,zName);
     speedtest1_exec("SELECT sum(d) FROM t2");
     speedtest1_end_test();
     testset_main_n:=testset_main_sz/ 5;
     zName:=sqlite3_mprintf("%d DELETEs, numeric BETWEEN, indexed",testset_main_n,RValue);
     speedtest1_begin_test(270,zName);
     speedtest1_exec("BEGIN");
     zSqlPrepare:=sqlite3_mprintf("DELETE FROM t2 WHERE b BETWEEN ?1 AND ?2; -- %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         testset_main_x1:=speedtest1_random(RValue) % testset_main_maxb+1;
         testset_main_x2:=speedtest1_random(RValue) % 10+testset_main_sz/ 5000+testset_main_x1;
         sqlite3_bind_int(pstmt,1,testset_main_x1,RValue) and skip;
         sqlite3_bind_int(pstmt,2,testset_main_x2,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     testset_main_n:=testset_main_sz;
     zName:=sqlite3_mprintf("%d DELETEs of individual rows",testset_main_n,RValue);
     speedtest1_begin_test(280,zName);
     speedtest1_exec("BEGIN");
     zSqlPrepare:=sqlite3_mprintf("DELETE FROM t3 WHERE a=?1; -- %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         testset_main_x1:=speedtest1_random(RValue) % testset_main_sz+1;
         sqlite3_bind_int(pstmt,1,testset_main_x1,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
	 zName := sqlite3_mprintf("Refill two %d-row tables using REPLACE", testset_main_sz);
     speedtest1_begin_test(290,zName);
     speedtest1_exec("REPLACE INTO t2(a,b,c) SELECT a,b,c FROM t1");
     speedtest1_exec("REPLACE INTO t3(a,b,c) SELECT a,b,c FROM t1");
     speedtest1_end_test();
	 zName := sqlite3_mprintf("Refill a %d-row table using (b&1)==(a&1)", testset_main_sz);
     speedtest1_begin_test(300,zName);
     speedtest1_exec("DELETE FROM t2;");
     speedtest1_exec("INSERT INTO t2(a,b,c)\n SELECT a,b,c FROM t1  WHERE (b&1)==(a&1);");
     speedtest1_exec("INSERT INTO t2(a,b,c)\n SELECT a,b,c FROM t1  WHERE (b&1)<>(a&1);");
     speedtest1_end_test();
     testset_main_n:=testset_main_sz/ 5;
     zName:=sqlite3_mprintf("%d four-ways joins",testset_main_n,RValue);
     speedtest1_begin_test(310,zName);
     speedtest1_exec("BEGIN");
     zSqlPrepare:=sqlite3_mprintf("SELECT t1.c FROM t1, t2, t3, t4\n WHERE t4.a BETWEEN ?1 AND ?2\n   AND t3.a=t4.b\n   AND t2.a=t3.b\n   AND t1.c=t2.c",RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         testset_main_x1:=speedtest1_random(RValue) % testset_main_sz+1;
         testset_main_x2:=speedtest1_random(RValue) % 10+testset_main_x1+4;
         sqlite3_bind_int(pstmt,1,testset_main_x1,RValue) and skip;
         sqlite3_bind_int(pstmt,2,testset_main_x2,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     zName:=sqlite3_mprintf("subquery in result set",testset_main_n,RValue);
     speedtest1_begin_test(320,zName);
     zSqlPrepare:=sqlite3_mprintf("SELECT sum(a), max(c),\n       avg((SELECT a FROM t2 WHERE 5+t2.b=t1.b) AND rowid<?1), max(c)\n FROM t1 WHERE rowid<?1;",RValue);
     speedtest1_prepare(zSqlPrepare);
     int testset_main_temp$_5 and skip;
     testset_main_temp$_5:=est_square_root(szTest,RValue);
     sqlite3_bind_int(pstmt,1,testset_main_temp$_5*50,RValue) and skip;
     speedtest1_run();
     speedtest1_end_test();
     testset_main_n<==szTest and testset_main_sz<==testset_main_n and skip;
     testset_main_zNum[0]:=0;
     testset_main_maxb:=roundup_allones(testset_main_sz/ 3,RValue);
     zName:=sqlite3_mprintf("%d REPLACE ops on an IPK",testset_main_n,RValue);
     speedtest1_begin_test(400,zName);
     speedtest1_exec("BEGIN");
     char* testset_main_temp$_6 and skip;
     testset_main_temp$_6:=isTemp(9,RValue);
     zSqlSpeedtest1:=sqlite3_mprintf("CREATE%s TABLE t5(a INTEGER PRIMARY KEY, b %s);",testset_main_temp$_6,zNN,RValue);
     speedtest1_exec(zSqlSpeedtest1);
     zSqlPrepare:=sqlite3_mprintf("REPLACE INTO t5 VALUES(?1,?2); --  %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         testset_main_x1:=swizzle(testset_main_i,testset_main_maxb,RValue);
         speedtest1_numbername(testset_main_i,testset_main_zNum,2000,RValue) and skip;
         sqlite3_bind_int(pstmt,1,(int)testset_main_x1,RValue) and skip;
         sqlite3_bind_text(pstmt,2,testset_main_zNum,-1,0,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     zName:=sqlite3_mprintf("%d SELECTS on an IPK",testset_main_n,RValue);
     speedtest1_begin_test(410,zName);
     zSqlPrepare:=sqlite3_mprintf("SELECT b FROM t5 WHERE a=?1; --  %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         testset_main_x1:=swizzle(testset_main_i,testset_main_maxb,RValue);
         sqlite3_bind_int(pstmt,1,(int)testset_main_x1,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_end_test();
     testset_main_n<==szTest and testset_main_sz<==testset_main_n and skip;
     testset_main_zNum[0]:=0;
     testset_main_maxb:=roundup_allones(testset_main_sz/ 3,RValue);
     zName:=sqlite3_mprintf("%d REPLACE on TEXT PK",testset_main_n,RValue);
     speedtest1_begin_test(500,zName);
     speedtest1_exec("BEGIN");
     char* testset_main_temp$_8 and skip;
     testset_main_temp$_8:=isTemp(9,RValue);
     zSqlSpeedtest1:=sqlite3_mprintf("CREATE%s TABLE t6(a TEXT PRIMARY KEY, b %s)%s;",testset_main_temp$_8,zNN,"WITHOUT ROWID",RValue);
     speedtest1_exec(zSqlSpeedtest1);
     zSqlPrepare:=sqlite3_mprintf("REPLACE INTO t6 VALUES(?1,?2); --  %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         testset_main_x1:=swizzle(testset_main_i,testset_main_maxb,RValue);
         speedtest1_numbername(testset_main_x1,testset_main_zNum,2000,RValue) and skip;
         sqlite3_bind_int(pstmt,2,testset_main_i,RValue) and skip;
         sqlite3_bind_text(pstmt,1,testset_main_zNum,-1,0,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_exec("COMMIT");
     speedtest1_end_test();
     zName:=sqlite3_mprintf("%d SELECTS on a TEXT PK",testset_main_n,RValue);
     speedtest1_begin_test(510,zName);
     zSqlPrepare:=sqlite3_mprintf("SELECT b FROM t6 WHERE a=?1; --  %d times",testset_main_n,RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_main_i:=1;
     
     while(testset_main_i<=testset_main_n)
     {
         testset_main_x1:=swizzle(testset_main_i,testset_main_maxb,RValue);
         speedtest1_numbername(testset_main_x1,testset_main_zNum,2000,RValue) and skip;
         sqlite3_bind_text(pstmt,1,testset_main_zNum,-1,0,RValue) and skip;
         speedtest1_run();
         testset_main_i:=testset_main_i+1
         
     };
     speedtest1_end_test();
     zName:=sqlite3_mprintf("%d SELECT DISTINCT",testset_main_n,RValue);
     speedtest1_begin_test(520,zName);
     speedtest1_exec("SELECT DISTINCT b FROM t5;");
     speedtest1_exec("SELECT DISTINCT b FROM t6;");
     speedtest1_end_test();
     zName:=sqlite3_mprintf("PRAGMA integrity_check",RValue);
     speedtest1_begin_test(980,zName);
     speedtest1_exec("PRAGMA integrity_check");
     speedtest1_end_test();
     zName:=sqlite3_mprintf("ANALYZE",RValue);
     speedtest1_begin_test(990,zName);
     speedtest1_exec("ANALYZE");
     speedtest1_end_test()
     )
     }; 
  function testset_cte (  )
 {
     frame(testset_cte_azPuzzle,testset_cte_zPuz,testset_cte_rSpacing,testset_cte_nElem) and ( 
     char *testset_cte_azPuzzle[]<=={"534...9..67.195....98....6.8...6...34..8.3..1....2...6.6....28....419..5...28..79","53....9..6..195....98....6.8...6...34..8.3..1....2...6.6....28....419..5....8..79","53.......6..195....98....6.8...6...34..8.3..1....2...6.6....28....419..5....8..79"} and skip;
     char *testset_cte_zPuz and skip;
     float testset_cte_rSpacing and skip;
     int testset_cte_nElem and skip;
     if(szTest<25) then 
     {
         testset_cte_zPuz:=testset_cte_azPuzzle[0]
         
     }
     else
     {
         if(szTest<70) then 
         {
             testset_cte_zPuz:=testset_cte_azPuzzle[1]
         }
         else
         {
             testset_cte_zPuz:=testset_cte_azPuzzle[2]
         }
     };
     zName:=sqlite3_mprintf("Sudoku with recursive 'digits'",RValue);
     speedtest1_begin_test(100,zName);
     zSqlPrepare:=sqlite3_mprintf("WITH RECURSIVE\n  input(sud) AS (VALUES(?1)),\n  digits(z,lp) AS (\n    VALUES('1', 1)\n    UNION ALL\n    SELECT CAST(lp+1 AS TEXT), lp+1 FROM digits WHERE lp<9\n  ),\n  x(s, ind) AS (\n    SELECT sud, instr(sud, '.') FROM input\n    UNION ALL\n    SELECT\n      substr(s, 1, ind-1) || z || substr(s, ind+1),\n      instr( substr(s, 1, ind-1) || z || substr(s, ind+1), '.' )\n     FROM x, digits AS z\n    WHERE ind>0\n      AND NOT EXISTS (\n            SELECT 1\n              FROM digits AS lp\n             WHERE z.z = substr(s, ((ind-1)/9)*9 + lp, 1)\n                OR z.z = substr(s, ((ind-1)%%9) + (lp-1)*9 + 1, 1)\n                OR z.z = substr(s, (((ind-1)/3) %% 3) * 3\n                        + ((ind-1)/27) * 27 + lp\n                        + ((lp-1) / 3) * 6, 1)\n         )\n  )\nSELECT s FROM x WHERE ind=0;",RValue);
     speedtest1_prepare(zSqlPrepare);
     sqlite3_bind_text(pstmt,1,testset_cte_zPuz,-1,0,RValue) and skip;
     speedtest1_run();
     speedtest1_end_test();
     zName:=sqlite3_mprintf("Sudoku with VALUES 'digits'",RValue);
     speedtest1_begin_test(200,zName);
     zSqlPrepare:=sqlite3_mprintf("WITH RECURSIVE\n  input(sud) AS (VALUES(?1)),\n  digits(z,lp) AS (VALUES('1',1),('2',2),('3',3),('4',4),('5',5),\n                         ('6',6),('7',7),('8',8),('9',9)),\n  x(s, ind) AS (\n    SELECT sud, instr(sud, '.') FROM input\n    UNION ALL\n    SELECT\n      substr(s, 1, ind-1) || z || substr(s, ind+1),\n      instr( substr(s, 1, ind-1) || z || substr(s, ind+1), '.' )\n     FROM x, digits AS z\n    WHERE ind>0\n      AND NOT EXISTS (\n            SELECT 1\n              FROM digits AS lp\n             WHERE z.z = substr(s, ((ind-1)/9)*9 + lp, 1)\n                OR z.z = substr(s, ((ind-1)%%9) + (lp-1)*9 + 1, 1)\n                OR z.z = substr(s, (((ind-1)/3) %% 3) * 3\n                        + ((ind-1)/27) * 27 + lp\n                        + ((lp-1) / 3) * 6, 1)\n         )\n  )\nSELECT s FROM x WHERE ind=0;",RValue);
     speedtest1_prepare(zSqlPrepare);
     sqlite3_bind_text(pstmt,1,testset_cte_zPuz,-1,0,RValue) and skip;
     speedtest1_run();
     speedtest1_end_test();
     testset_cte_rSpacing:=5.0/ szTest;
     zName:=sqlite3_mprintf("Mandelbrot Set with spacing=%f",testset_cte_rSpacing,RValue);
     speedtest1_begin_test(300,zName);
     zSqlPrepare:=sqlite3_mprintf("WITH RECURSIVE \n  xaxis(x) AS (VALUES(-2.0) UNION ALL SELECT x+?1 FROM xaxis WHERE x<1.2),\n  yaxis(y) AS (VALUES(-1.0) UNION ALL SELECT y+?2 FROM yaxis WHERE y<1.0),\n  m(iter, cx, cy, x, y) AS (\n    SELECT 0, x, y, 0.0, 0.0 FROM xaxis, yaxis\n    UNION ALL\n    SELECT iter+1, cx, cy, x*x-y*y + cx, 2.0*x*y + cy FROM m \n     WHERE (x*x + y*y) < 4.0 AND iter<28\n  ),\n  m2(iter, cx, cy) AS (\n    SELECT max(iter), cx, cy FROM m GROUP BY cx, cy\n  ),\n  a(t) AS (\n    SELECT group_concat( substr(' .+*#', 1+min(iter/7,4), 1), '') \n    FROM m2 GROUP BY cy\n  )\nSELECT group_concat(rtrim(t),x'0a') FROM a;",RValue);
     speedtest1_prepare(zSqlPrepare);
     sqlite3_bind_double(pstmt,1,testset_cte_rSpacing*0.05,RValue) and skip;
     sqlite3_bind_double(pstmt,2,testset_cte_rSpacing,RValue) and skip;
     speedtest1_run();
     speedtest1_end_test();
     testset_cte_nElem:=10000*szTest;
     zName:=sqlite3_mprintf("EXCEPT operator on %d-element tables",testset_cte_nElem,RValue);
     speedtest1_begin_test(400,zName);
     zSqlPrepare:=sqlite3_mprintf("WITH RECURSIVE \n  t1(x) AS (VALUES(2) UNION ALL SELECT x+2 FROM t1 WHERE x<%d),\n  t2(y) AS (VALUES(3) UNION ALL SELECT y+3 FROM t2 WHERE y<%d)\nSELECT count(x), avg(x) FROM (\n  SELECT x FROM t1 EXCEPT SELECT y FROM t2 ORDER BY 1\n);",testset_cte_nElem,testset_cte_nElem,RValue);
     speedtest1_prepare(zSqlPrepare);
     speedtest1_run();
     speedtest1_end_test()
     )
     }; 
  function testset_orm (  )
 {
     frame(testset_orm_i,testset_orm_j,testset_orm_n,testset_orm_nRow,testset_orm_x1,testset_orm_len$,testset_orm_zNum,testset_orm_zType,nm_1$,switch$,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     int testset_orm_i,testset_orm_j,testset_orm_n and skip;
     int testset_orm_nRow and skip;
     int testset_orm_x1,testset_orm_len$ and skip;
     char testset_orm_zNum[2000] and skip;
     char testset_orm_zType[120]<=="IBBIIITIVVITBTBFBFITTFBTBVBVIFTBBFITFFVBIFIVBVVVBTVTIBBFFIVIBTBTVTTFTVTVFFIITIFBITFTTFFFVBIIBTTITFTFFVVVFIIITVBBVFFTVVB" and skip;
     testset_orm_n<==szTest*250 and testset_orm_nRow<==testset_orm_n and skip;
     zName:=sqlite3_mprintf("Fill %d rows",testset_orm_n,RValue);
     speedtest1_begin_test(100,zName);
     zSqlSpeedtest1:=sqlite3_mprintf("BEGIN;CREATE TABLE ZLOOKSLIKECOREDATA (  ZPK INTEGER PRIMARY KEY,  ZTERMFITTINGHOUSINGCOMMAND INTEGER,  ZBRIEFGOBYDODGERHEIGHT BLOB,  ZCAPABLETRIPDOORALMOND BLOB,  ZDEPOSITPAIRCOLLEGECOMET INTEGER,  ZFRAMEENTERSIMPLEMOUTH INTEGER,  ZHOPEFULGATEHOLECHALK INTEGER,  ZSLEEPYUSERGRANDBOWL TIMESTAMP,  ZDEWPEACHCAREERCELERY INTEGER,  ZHANGERLITHIUMDINNERMEET VARCHAR,  ZCLUBRELEASELIZARDADVICE VARCHAR,  ZCHARGECLICKHUMANEHIRE INTEGER,  ZFINGERDUEPIZZAOPTION TIMESTAMP,  ZFLYINGDOCTORTABLEMELODY BLOB,  ZLONGFINLEAVEIMAGEOIL TIMESTAMP,  ZFAMILYVISUALOWNERMATTER BLOB,  ZGOLDYOUNGINITIALNOSE FLOAT,  ZCAUSESALAMITERMCYAN BLOB,  ZSPREADMOTORBISCUITBACON FLOAT,  ZGIFTICEFISHGLUEHAIR INTEGER,  ZNOTICEPEARPOLICYJUICE TIMESTAMP,  ZBANKBUFFALORECOVERORBIT TIMESTAMP,  ZLONGDIETESSAYNATURE FLOAT,  ZACTIONRANGEELEGANTNEUTRON BLOB,  ZCADETBRIGHTPLANETBANK TIMESTAMP,  ZAIRFORGIVEHEADFROG BLOB,  ZSHARKJUSTFRUITMOVIE VARCHAR,  ZFARMERMORNINGMIRRORCONCERN BLOB,  ZWOODPOETRYCOBBLERBENCH VARCHAR,  ZHAFNIUMSCRIPTSALADMOTOR INTEGER,  ZPROBLEMCLUBPOPOVERJELLY FLOAT,  ZEIGHTLEADERWORKERMOST TIMESTAMP,  ZGLASSRESERVEBARIUMMEAL BLOB,  ZCLAMBITARUGULAFAJITA BLOB,  ZDECADEJOYOUSWAVEHABIT FLOAT,  ZCOMPANYSUMMERFIBERELF INTEGER,  ZTREATTESTQUILLCHARGE TIMESTAMP,  ZBROWBALANCEKEYCHOWDER FLOAT,  ZPEACHCOPPERDINNERLAKE FLOAT,  ZDRYWALLBEYONDBROWNBOWL VARCHAR,  ZBELLYCRASHITEMLACK BLOB,  ZTENNISCYCLEBILLOFFICER INTEGER,  ZMALLEQUIPTHANKSGLUE FLOAT,  ZMISSREPLYHUMANLIVING INTEGER,  ZKIWIVISUALPRIDEAPPLE VARCHAR,  ZWISHHITSKINMOTOR BLOB,  ZCALMRACCOONPROGRAMDEBIT VARCHAR,  ZSHINYASSISTLIVINGCRAB VARCHAR,  ZRESOLVEWRISTWRAPAPPLE VARCHAR,  ZAPPEALSIMPLESECONDHOUSING BLOB,  ZCORNERANCHORTAPEDIVER TIMESTAMP,  ZMEMORYREQUESTSOURCEBIG VARCHAR,  ZTRYFACTKEEPMILK TIMESTAMP,  ZDIVERPAINTLEATHEREASY INTEGER,  ZSORTMISTYQUOTECABBAGE BLOB,  ZTUNEGASBUFFALOCAPITAL BLOB,  ZFILLSTOPLAWJOYFUL FLOAT,  ZSTEELCAREFULPLATENUMBER FLOAT,  ZGIVEVIVIDDIVINEMEANING INTEGER,  ZTREATPACKFUTURECONVERT VARCHAR,  ZCALMLYGEMFINISHEFFECT INTEGER,  ZCABBAGESOCKEASEMINUTE BLOB,  ZPLANETFAMILYPUREMEMORY TIMESTAMP,  ZMERRYCRACKTRAINLEADER BLOB,  ZMINORWAYPAPERCLASSY TIMESTAMP,  ZEAGLELINEMINEMAIL VARCHAR,  ZRESORTYARDGREENLET TIMESTAMP,  ZYARDOREGANOVIVIDJEWEL TIMESTAMP,  ZPURECAKEVIVIDNEATLY FLOAT,  ZASKCONTACTMONITORFUN TIMESTAMP,  ZMOVEWHOGAMMAINCH VARCHAR,  ZLETTUCEBIRDMEETDEBATE TIMESTAMP,  ZGENENATURALHEARINGKITE VARCHAR,  ZMUFFINDRYERDRAWFORTUNE FLOAT,  ZGRAYSURVEYWIRELOVE FLOAT,  ZPLIERSPRINTASKOREGANO INTEGER,  ZTRAVELDRIVERCONTESTLILY INTEGER,  ZHUMORSPICESANDKIDNEY TIMESTAMP,  ZARSENICSAMPLEWAITMUON INTEGER,  ZLACEADDRESSGROUNDCAREFUL FLOAT,  ZBAMBOOMESSWASABIEVENING BLOB,  ZONERELEASEAVERAGENURSE INTEGER,  ZRADIANTWHENTRYCARD TIMESTAMP,  ZREWARDINSIDEMANGOINTENSE FLOAT,  ZNEATSTEWPARTIRON TIMESTAMP,  ZOUTSIDEPEAHENCOUNTICE TIMESTAMP,  ZCREAMEVENINGLIPBRANCH FLOAT,  ZWHALEMATHAVOCADOCOPPER FLOAT,  ZLIFEUSELEAFYBELL FLOAT,  ZWEALTHLINENGLEEFULDAY VARCHAR,  ZFACEINVITETALKGOLD BLOB,  ZWESTAMOUNTAFFECTHEARING INTEGER,  ZDELAYOUTCOMEHORNAGENCY INTEGER,  ZBIGTHINKCONVERTECONOMY BLOB,  ZBASEGOUDAREGULARFORGIVE TIMESTAMP,  ZPATTERNCLORINEGRANDCOLBY TIMESTAMP,  ZCYANBASEFEEDADROIT INTEGER,  ZCARRYFLOORMINNOWDRAGON TIMESTAMP,  ZIMAGEPENCILOTHERBOTTOM FLOAT,  ZXENONFLIGHTPALEAPPLE TIMESTAMP,  ZHERRINGJOKEFEATUREHOPEFUL FLOAT,  ZCAPYEARLYRIVETBRUSH FLOAT,  ZAGEREEDFROGBASKET VARCHAR,  ZUSUALBODYHALIBUTDIAMOND VARCHAR,  ZFOOTTAPWORDENTRY VARCHAR,  ZDISHKEEPBLESTMONITOR FLOAT,  ZBROADABLESOLIDCASUAL INTEGER,  ZSQUAREGLEEFULCHILDLIGHT INTEGER,  ZHOLIDAYHEADPONYDETAIL INTEGER,  ZGENERALRESORTSKYOPEN TIMESTAMP,  ZGLADSPRAYKIDNEYGUPPY VARCHAR,  ZSWIMHEAVYMENTIONKIND BLOB,  ZMESSYSULFURDREAMFESTIVE BLOB,  ZSKYSKYCLASSICBRIEF VARCHAR,  ZDILLASKHOKILEMON FLOAT,  ZJUNIORSHOWPRESSNOVA FLOAT,  ZSIZETOEAWARDFRESH TIMESTAMP,  ZKEYFAILAPRICOTMETAL VARCHAR,  ZHANDYREPAIRPROTONAIRPORT VARCHAR,  ZPOSTPROTEINHANDLEACTOR BLOB);",RValue);
     speedtest1_exec(zSqlSpeedtest1);
     zSqlPrepare:=sqlite3_mprintf("INSERT INTO ZLOOKSLIKECOREDATA(ZPK,ZAIRFORGIVEHEADFROG,ZGIFTICEFISHGLUEHAIR,ZDELAYOUTCOMEHORNAGENCY,ZSLEEPYUSERGRANDBOWL,ZGLASSRESERVEBARIUMMEAL,ZBRIEFGOBYDODGERHEIGHT,ZBAMBOOMESSWASABIEVENING,ZFARMERMORNINGMIRRORCONCERN,ZTREATPACKFUTURECONVERT,ZCAUSESALAMITERMCYAN,ZCALMRACCOONPROGRAMDEBIT,ZHOLIDAYHEADPONYDETAIL,ZWOODPOETRYCOBBLERBENCH,ZHAFNIUMSCRIPTSALADMOTOR,ZUSUALBODYHALIBUTDIAMOND,ZOUTSIDEPEAHENCOUNTICE,ZDIVERPAINTLEATHEREASY,ZWESTAMOUNTAFFECTHEARING,ZSIZETOEAWARDFRESH,ZDEWPEACHCAREERCELERY,ZSTEELCAREFULPLATENUMBER,ZCYANBASEFEEDADROIT,ZCALMLYGEMFINISHEFFECT,ZHANDYREPAIRPROTONAIRPORT,ZGENENATURALHEARINGKITE,ZBROADABLESOLIDCASUAL,ZPOSTPROTEINHANDLEACTOR,ZLACEADDRESSGROUNDCAREFUL,ZIMAGEPENCILOTHERBOTTOM,ZPROBLEMCLUBPOPOVERJELLY,ZPATTERNCLORINEGRANDCOLBY,ZNEATSTEWPARTIRON,ZAPPEALSIMPLESECONDHOUSING,ZMOVEWHOGAMMAINCH,ZTENNISCYCLEBILLOFFICER,ZSHARKJUSTFRUITMOVIE,ZKEYFAILAPRICOTMETAL,ZCOMPANYSUMMERFIBERELF,ZTERMFITTINGHOUSINGCOMMAND,ZRESORTYARDGREENLET,ZCABBAGESOCKEASEMINUTE,ZSQUAREGLEEFULCHILDLIGHT,ZONERELEASEAVERAGENURSE,ZBIGTHINKCONVERTECONOMY,ZPLIERSPRINTASKOREGANO,ZDECADEJOYOUSWAVEHABIT,ZDRYWALLBEYONDBROWNBOWL,ZCLUBRELEASELIZARDADVICE,ZWHALEMATHAVOCADOCOPPER,ZBELLYCRASHITEMLACK,ZLETTUCEBIRDMEETDEBATE,ZCAPABLETRIPDOORALMOND,ZRADIANTWHENTRYCARD,ZCAPYEARLYRIVETBRUSH,ZAGEREEDFROGBASKET,ZSWIMHEAVYMENTIONKIND,ZTRAVELDRIVERCONTESTLILY,ZGLADSPRAYKIDNEYGUPPY,ZBANKBUFFALORECOVERORBIT,ZFINGERDUEPIZZAOPTION,ZCLAMBITARUGULAFAJITA,ZLONGFINLEAVEIMAGEOIL,ZLONGDIETESSAYNATURE,ZJUNIORSHOWPRESSNOVA,ZHOPEFULGATEHOLECHALK,ZDEPOSITPAIRCOLLEGECOMET,ZWEALTHLINENGLEEFULDAY,ZFILLSTOPLAWJOYFUL,ZTUNEGASBUFFALOCAPITAL,ZGRAYSURVEYWIRELOVE,ZCORNERANCHORTAPEDIVER,ZREWARDINSIDEMANGOINTENSE,ZCADETBRIGHTPLANETBANK,ZPLANETFAMILYPUREMEMORY,ZTREATTESTQUILLCHARGE,ZCREAMEVENINGLIPBRANCH,ZSKYSKYCLASSICBRIEF,ZARSENICSAMPLEWAITMUON,ZBROWBALANCEKEYCHOWDER,ZFLYINGDOCTORTABLEMELODY,ZHANGERLITHIUMDINNERMEET,ZNOTICEPEARPOLICYJUICE,ZSHINYASSISTLIVINGCRAB,ZLIFEUSELEAFYBELL,ZFACEINVITETALKGOLD,ZGENERALRESORTSKYOPEN,ZPURECAKEVIVIDNEATLY,ZKIWIVISUALPRIDEAPPLE,ZMESSYSULFURDREAMFESTIVE,ZCHARGECLICKHUMANEHIRE,ZHERRINGJOKEFEATUREHOPEFUL,ZYARDOREGANOVIVIDJEWEL,ZFOOTTAPWORDENTRY,ZWISHHITSKINMOTOR,ZBASEGOUDAREGULARFORGIVE,ZMUFFINDRYERDRAWFORTUNE,ZACTIONRANGEELEGANTNEUTRON,ZTRYFACTKEEPMILK,ZPEACHCOPPERDINNERLAKE,ZFRAMEENTERSIMPLEMOUTH,ZMERRYCRACKTRAINLEADER,ZMEMORYREQUESTSOURCEBIG,ZCARRYFLOORMINNOWDRAGON,ZMINORWAYPAPERCLASSY,ZDILLASKHOKILEMON,ZRESOLVEWRISTWRAPAPPLE,ZASKCONTACTMONITORFUN,ZGIVEVIVIDDIVINEMEANING,ZEIGHTLEADERWORKERMOST,ZMISSREPLYHUMANLIVING,ZXENONFLIGHTPALEAPPLE,ZSORTMISTYQUOTECABBAGE,ZEAGLELINEMINEMAIL,ZFAMILYVISUALOWNERMATTER,ZSPREADMOTORBISCUITBACON,ZDISHKEEPBLESTMONITOR,ZMALLEQUIPTHANKSGLUE,ZGOLDYOUNGINITIALNOSE,ZHUMORSPICESANDKIDNEY)VALUES(?1,?26,?20,?93,?8,?33,?3,?81,?28,?60,?18,?47,?109,?29,?30,?104,?86,?54,?92,?117,?9,?58,?97,?61,?119,?73,?107,?120,?80,?99,?31,?96,?85,?50,?71,?42,?27,?118,?36,?2,?67,?62,?108,?82,?94,?76,?35,?40,?11,?88,?41,?72,?4,?83,?102,?103,?112,?77,?111,?22,?13,?34,?15,?23,?116,?7,?5,?90,?57,?56,?75,?51,?84,?25,?63,?37,?87,?114,?79,?38,?14,?10,?21,?48,?89,?91,?110,?69,?45,?113,?12,?101,?68,?105,?46,?95,?74,?24,?53,?39,?6,?64,?52,?98,?65,?115,?49,?70,?59,?32,?44,?100,?55,?66,?16,?19,?106,?43,?17,?78);",RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_orm_i:=0;
     
     while(testset_orm_i<testset_orm_n)
     {
         testset_orm_x1:=speedtest1_random(RValue);
         speedtest1_numbername(testset_orm_x1 % 1000,testset_orm_zNum,2000,RValue) and skip;
         testset_orm_len$:=(int)strlen(testset_orm_zNum);
         sqlite3_bind_int(pstmt,1,testset_orm_i ^ 15,RValue) and skip;
         testset_orm_j:=0;
         
         while(testset_orm_zType[testset_orm_j])
         {
             int switch$ and skip;
             break$<==0 and skip;
              switch$<==0 and skip;
              int nm_1$ and skip;
             nm_1$ := testset_orm_zType[testset_orm_j];
             if (nm_1$='I' OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip
                 
             }
             else
             {
                 skip
             };
             if (nm_1$='T' OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 sqlite3_bind_int64(pstmt,testset_orm_j+2,testset_orm_x1,RValue) and skip;
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_1$='F' OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 sqlite3_bind_double(pstmt,testset_orm_j+2,(float)testset_orm_x1,RValue) and skip;
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_1$='V' OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip
                 
             }
             else
             {
                 skip
             };
             if (nm_1$='B' OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 sqlite3_bind_text64(pstmt,testset_orm_j+2,testset_orm_zNum,testset_orm_len$,0,1,RValue) and skip;
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             testset_orm_j:=testset_orm_j+1
             
         };
         speedtest1_run();
         testset_orm_i:=testset_orm_i+1
         
     };
     speedtest1_exec("COMMIT;");
     speedtest1_end_test();
     testset_orm_n:=szTest*250;
     zName:=sqlite3_mprintf("Query %d rows by rowid",testset_orm_n,RValue);
     speedtest1_begin_test(110,zName);
     zSqlPrepare:=sqlite3_mprintf("SELECT ZCYANBASEFEEDADROIT,ZJUNIORSHOWPRESSNOVA,ZCAUSESALAMITERMCYAN,ZHOPEFULGATEHOLECHALK,ZHUMORSPICESANDKIDNEY,ZSWIMHEAVYMENTIONKIND,ZMOVEWHOGAMMAINCH,ZAPPEALSIMPLESECONDHOUSING,ZHAFNIUMSCRIPTSALADMOTOR,ZNEATSTEWPARTIRON,ZLONGFINLEAVEIMAGEOIL,ZDEWPEACHCAREERCELERY,ZXENONFLIGHTPALEAPPLE,ZCALMRACCOONPROGRAMDEBIT,ZUSUALBODYHALIBUTDIAMOND,ZTRYFACTKEEPMILK,ZWEALTHLINENGLEEFULDAY,ZLONGDIETESSAYNATURE,ZLIFEUSELEAFYBELL,ZTREATPACKFUTURECONVERT,ZMEMORYREQUESTSOURCEBIG,ZYARDOREGANOVIVIDJEWEL,ZDEPOSITPAIRCOLLEGECOMET,ZSLEEPYUSERGRANDBOWL,ZBRIEFGOBYDODGERHEIGHT,ZCLUBRELEASELIZARDADVICE,ZCAPABLETRIPDOORALMOND,ZDRYWALLBEYONDBROWNBOWL,ZASKCONTACTMONITORFUN,ZKIWIVISUALPRIDEAPPLE,ZNOTICEPEARPOLICYJUICE,ZPEACHCOPPERDINNERLAKE,ZSTEELCAREFULPLATENUMBER,ZGLADSPRAYKIDNEYGUPPY,ZCOMPANYSUMMERFIBERELF,ZTENNISCYCLEBILLOFFICER,ZIMAGEPENCILOTHERBOTTOM,ZWESTAMOUNTAFFECTHEARING,ZDIVERPAINTLEATHEREASY,ZSKYSKYCLASSICBRIEF,ZMESSYSULFURDREAMFESTIVE,ZMERRYCRACKTRAINLEADER,ZBROADABLESOLIDCASUAL,ZGLASSRESERVEBARIUMMEAL,ZTUNEGASBUFFALOCAPITAL,ZBANKBUFFALORECOVERORBIT,ZTREATTESTQUILLCHARGE,ZBAMBOOMESSWASABIEVENING,ZREWARDINSIDEMANGOINTENSE,ZEAGLELINEMINEMAIL,ZCALMLYGEMFINISHEFFECT,ZKEYFAILAPRICOTMETAL,ZFINGERDUEPIZZAOPTION,ZCADETBRIGHTPLANETBANK,ZGOLDYOUNGINITIALNOSE,ZMISSREPLYHUMANLIVING,ZEIGHTLEADERWORKERMOST,ZFRAMEENTERSIMPLEMOUTH,ZBIGTHINKCONVERTECONOMY,ZFACEINVITETALKGOLD,ZPOSTPROTEINHANDLEACTOR,ZHERRINGJOKEFEATUREHOPEFUL,ZCABBAGESOCKEASEMINUTE,ZMUFFINDRYERDRAWFORTUNE,ZPROBLEMCLUBPOPOVERJELLY,ZGIVEVIVIDDIVINEMEANING,ZGENENATURALHEARINGKITE,ZGENERALRESORTSKYOPEN,ZLETTUCEBIRDMEETDEBATE,ZBASEGOUDAREGULARFORGIVE,ZCHARGECLICKHUMANEHIRE,ZPLANETFAMILYPUREMEMORY,ZMINORWAYPAPERCLASSY,ZCAPYEARLYRIVETBRUSH,ZSIZETOEAWARDFRESH,ZARSENICSAMPLEWAITMUON,ZSQUAREGLEEFULCHILDLIGHT,ZSHINYASSISTLIVINGCRAB,ZCORNERANCHORTAPEDIVER,ZDECADEJOYOUSWAVEHABIT,ZTRAVELDRIVERCONTESTLILY,ZFLYINGDOCTORTABLEMELODY,ZSHARKJUSTFRUITMOVIE,ZFAMILYVISUALOWNERMATTER,ZFARMERMORNINGMIRRORCONCERN,ZGIFTICEFISHGLUEHAIR,ZOUTSIDEPEAHENCOUNTICE,ZSPREADMOTORBISCUITBACON,ZWISHHITSKINMOTOR,ZHOLIDAYHEADPONYDETAIL,ZWOODPOETRYCOBBLERBENCH,ZAIRFORGIVEHEADFROG,ZBROWBALANCEKEYCHOWDER,ZDISHKEEPBLESTMONITOR,ZCLAMBITARUGULAFAJITA,ZPLIERSPRINTASKOREGANO,ZRADIANTWHENTRYCARD,ZDELAYOUTCOMEHORNAGENCY,ZPURECAKEVIVIDNEATLY,ZPATTERNCLORINEGRANDCOLBY,ZHANDYREPAIRPROTONAIRPORT,ZAGEREEDFROGBASKET,ZSORTMISTYQUOTECABBAGE,ZFOOTTAPWORDENTRY,ZRESOLVEWRISTWRAPAPPLE,ZDILLASKHOKILEMON,ZFILLSTOPLAWJOYFUL,ZACTIONRANGEELEGANTNEUTRON,ZRESORTYARDGREENLET,ZCREAMEVENINGLIPBRANCH,ZWHALEMATHAVOCADOCOPPER,ZGRAYSURVEYWIRELOVE,ZBELLYCRASHITEMLACK,ZHANGERLITHIUMDINNERMEET,ZCARRYFLOORMINNOWDRAGON,ZMALLEQUIPTHANKSGLUE,ZTERMFITTINGHOUSINGCOMMAND,ZONERELEASEAVERAGENURSE,ZLACEADDRESSGROUNDCAREFUL FROM ZLOOKSLIKECOREDATA WHERE ZPK=?1;",RValue);
     speedtest1_prepare(zSqlPrepare);
     testset_orm_i:=0;
     
     while(testset_orm_i<testset_orm_n)
     {
         testset_orm_x1:=speedtest1_random(RValue) % testset_orm_nRow;
         sqlite3_bind_int(pstmt,1,testset_orm_x1,RValue) and skip;
         speedtest1_run();
         testset_orm_i:=testset_orm_i+1
         
     };
     speedtest1_end_test()
     )
     }; 
  function testset_debug1 (  )
 {
     frame(testset_debug1_i,testset_debug1_n,testset_debug1_x1,testset_debug1_x2,testset_debug1_zNum) and ( 
     int testset_debug1_i,testset_debug1_n and skip;
     int testset_debug1_x1,testset_debug1_x2 and skip;
     char testset_debug1_zNum[2000] and skip;
     testset_debug1_n:=szTest;
     testset_debug1_i:=1;
     
     while(testset_debug1_i<=testset_debug1_n)
     {
         testset_debug1_x1:=swizzle(testset_debug1_i,testset_debug1_n,RValue);
         testset_debug1_x2:=swizzle(testset_debug1_x1,testset_debug1_n,RValue);
         speedtest1_numbername(testset_debug1_x1,testset_debug1_zNum,2000,RValue) and skip;
         output (testset_debug1_i," ",testset_debug1_x1," ",testset_debug1_x2," ",testset_debug1_zNum,"\n","\n") and skip;
         testset_debug1_i:=testset_debug1_i+1
         
     }
     )
     }; 
  function main ( int RValue )
 {
     frame(main_doAutovac,main_cacheSize,main_doExclusive,main_nHeap,main_mnHeap,main_doIncrvac,main_zJMode,main_zKey,main_nLook,main_szLook,main_noSync,main_pageSize,main_nPCache,main_szPCache,main_doPCache,main_nScratch,main_szScratch,main_showStats,main_nThread,main_mmapSize,main_zTSet,main_doTrace,main_zEncoding,main_zDbName,main_pHeap,main_pLook,main_pPCache,main_pScratch,main_iCur,main_iHi,main_i,main_rc,return) and ( 
     int return<==0 and skip;
     int main_doAutovac<==0 and skip;
     int main_cacheSize<==0 and skip;
     int main_doExclusive<==0 and skip;
     int main_nHeap<==0,main_mnHeap<==0 and skip;
     int main_doIncrvac<==0 and skip;
     char *main_zJMode<==0 and skip;
     char *main_zKey<==0 and skip;
     int main_nLook<==-1,main_szLook<==0 and skip;
     int main_noSync<==0 and skip;
     int main_pageSize<==0 and skip;
     int main_nPCache<==0,main_szPCache<==0 and skip;
     int main_doPCache<==0 and skip;
     int main_nScratch<==0,main_szScratch<==0 and skip;
     int main_showStats<==0 and skip;
     int main_nThread<==0 and skip;
     int main_mmapSize<==0 and skip;
     char *main_zTSet<=="main" and skip;
     int main_doTrace<==0 and skip;
     char *main_zEncoding<==0 and skip;
     char *main_zDbName<==0 and skip;
     void *main_pHeap<==0 and skip;
     void *main_pLook<==0 and skip;
     void *main_pPCache<==0 and skip;
     void *main_pScratch<==0 and skip;
     int main_iCur,main_iHi and skip;
     int main_i and skip;
     int main_rc and skip;
     output ("-- Speedtest1 for SQLite ",sqlite3_libversion(RValue)," ",sqlite3_sourceid(RValue),"\n") and skip;
     zWR:="";
     zNN:="";
     zPK:="UNIQUE";
     szTest:=100;
     nRepeat:=1;
     main_zDbName:="speedtest1.db";
     if(main_zDbName!=0) then 
     {
         _unlink(main_zDbName) and skip
     }
     else 
     {
          skip 
     };
     if(main_nHeap>0) then 
     {
         main_pHeap:=malloc(main_nHeap);
         main_rc:=sqlite3_config(8,main_pHeap,main_nHeap,main_mnHeap,RValue)
         
     }
     else 
     {
          skip 
     };
     if(main_doPCache) then 
     {
         if(main_nPCache>0 AND main_szPCache>0) then 
         {
             main_pPCache:=malloc(main_nPCache*(int)main_szPCache)
             
         }
         else 
         {
              skip 
         };
         main_rc:=sqlite3_config(7,main_pPCache,main_szPCache,main_nPCache,RValue)
         
     }
     else 
     {
          skip 
     };
     if(main_nScratch>0 AND main_szScratch>0) then 
     {
         main_pScratch:=malloc(main_nScratch*(int)main_szScratch);
         main_rc:=sqlite3_config(6,main_pScratch,main_szScratch,main_nScratch,RValue)
         
     }
     else 
     {
          skip 
     };
     if(main_nLook>=0) then 
     {
         sqlite3_config(13,0,0,RValue) and skip
         
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
     if(main_nLook>0 AND main_szLook>0) then 
     {
         main_pLook:=malloc(main_nLook*main_szLook);
         main_rc:=sqlite3_db_config(db,1001,main_pLook,main_szLook,main_nLook,RValue)
         
     }
     else 
     {
          skip 
     };
     if(main_mmapSize>0) then 
     {
         zSqlSpeedtest1:=sqlite3_mprintf("PRAGMA mmap_size=%d",main_mmapSize,RValue);
         speedtest1_exec(zSqlSpeedtest1)
         
     }
     else 
     {
          skip 
     };
     zSqlSpeedtest1:=sqlite3_mprintf("PRAGMA threads=%d",main_nThread,RValue);
     speedtest1_exec(zSqlSpeedtest1);
     if(main_zKey) then 
     {
         zSqlSpeedtest1:=sqlite3_mprintf("PRAGMA key('%s')",main_zKey,RValue);
         speedtest1_exec(zSqlSpeedtest1)
         
     }
     else 
     {
          skip 
     };
     if(main_zEncoding) then 
     {
         zSqlSpeedtest1:=sqlite3_mprintf("PRAGMA encoding=%s",main_zEncoding,RValue);
         speedtest1_exec(zSqlSpeedtest1)
         
     }
     else 
     {
          skip 
     };
     if(main_doAutovac) then 
     {
         speedtest1_exec("PRAGMA auto_vacuum=FULL")
         
     }
     else
     {
         if(main_doIncrvac) then 
         {
             speedtest1_exec("PRAGMA auto_vacuum=INCREMENTAL")
             
         }
         else 
         {
              skip 
         }
     };
     if(main_pageSize) then 
     {
         zSqlSpeedtest1:=sqlite3_mprintf("PRAGMA page_size=%d",main_pageSize,RValue);
         speedtest1_exec(zSqlSpeedtest1)
         
     }
     else 
     {
          skip 
     };
     if(main_cacheSize) then 
     {
         zSqlSpeedtest1:=sqlite3_mprintf("PRAGMA cache_size=%d",main_cacheSize,RValue);
         speedtest1_exec(zSqlSpeedtest1)
         
     }
     else 
     {
          skip 
     };
     if(main_noSync) then 
     {
         speedtest1_exec("PRAGMA synchronous=OFF")
     }
     else 
     {
          skip 
     };
     if(main_doExclusive) then 
     {
         speedtest1_exec("PRAGMA locking_mode=EXCLUSIVE")
         
     }
     else 
     {
          skip 
     };
     if(main_zJMode) then 
     {
         zSqlSpeedtest1:=sqlite3_mprintf("PRAGMA journal_mode=%s",main_zJMode,RValue);
         speedtest1_exec(zSqlSpeedtest1)
         
     }
     else 
     {
          skip 
     };
     if(bExplain) then 
     {
         output (".explain\n.echo on\n") and skip
     }
     else 
     {
          skip 
     };
     if(strcmp(main_zTSet,"main")=0) then 
     {
         testset_main()
         
     }
     else
     {
         if(strcmp(main_zTSet,"debug1")=0) then 
         {
             testset_debug1()
         }
         else
         {
             if(strcmp(main_zTSet,"orm")=0) then 
             {
                 testset_orm()
             }
             else
             {
                 if(strcmp(main_zTSet,"cte")=0) then 
                 {
                     testset_cte()
                     
                 }
                 else 
                 {
                      skip 
                 }
             }
         }
     };
     speedtest1_final();
     if(main_showStats) then 
     {
         sqlite3_db_status(db,0,&main_iCur,&main_iHi,0,RValue) and skip;
         output ("-- Lookaside Slots Used:        ",main_iCur," (max ",main_iHi,")\n") and skip;
         sqlite3_db_status(db,4,&main_iCur,&main_iHi,0,RValue) and skip;
         output ("-- Successful lookasides:       ",main_iHi,"\n") and skip;
         sqlite3_db_status(db,5,&main_iCur,&main_iHi,0,RValue) and skip;
         output ("-- Lookaside size faults:       ",main_iHi,"\n") and skip;
         sqlite3_db_status(db,6,&main_iCur,&main_iHi,0,RValue) and skip;
         output ("-- Lookaside OOM faults:        ",main_iHi,"\n") and skip;
         sqlite3_db_status(db,1,&main_iCur,&main_iHi,0,RValue) and skip;
         output ("-- Pager Heap Usage:            ",main_iCur," bytes\n") and skip;
         sqlite3_db_status(db,7,&main_iCur,&main_iHi,1,RValue) and skip;
         output ("-- Page cache hits:             ",main_iCur,"\n") and skip;
         sqlite3_db_status(db,8,&main_iCur,&main_iHi,1,RValue) and skip;
         output ("-- Page cache misses:           ",main_iCur,"\n") and skip;
         sqlite3_db_status(db,9,&main_iCur,&main_iHi,1,RValue) and skip;
         output ("-- Page cache writes:           ",main_iCur,"\n") and skip;
         sqlite3_db_status(db,2,&main_iCur,&main_iHi,0,RValue) and skip;
         output ("-- Schema Heap Usage:           ",main_iCur," bytes\n") and skip;
         sqlite3_db_status(db,3,&main_iCur,&main_iHi,0,RValue) and skip;
         output ("-- Statement Heap Usage:        ",main_iCur," bytes\n") and skip
         
     }
     else 
     {
          skip 
     };
     sqlite3_close(db,RValue) and skip;
     if(main_showStats) then 
     {
         sqlite3_status(0,&main_iCur,&main_iHi,0,RValue) and skip;
         output ("-- Memory Used (bytes):         ",main_iCur," (max ",main_iHi,")\n") and skip;
         sqlite3_status(9,&main_iCur,&main_iHi,0,RValue) and skip;
         output ("-- Outstanding Allocations:     ",main_iCur," (max ",main_iHi,")\n") and skip;
         sqlite3_status(2,&main_iCur,&main_iHi,0,RValue) and skip;
         output ("-- Pcache Overflow Bytes:       ",main_iCur," (max ",main_iHi,")\n") and skip;
         sqlite3_status(4,&main_iCur,&main_iHi,0,RValue) and skip;
         output ("-- Scratch Overflow Bytes:      ",main_iCur," (max ",main_iHi,")\n") and skip;
         sqlite3_status(5,&main_iCur,&main_iHi,0,RValue) and skip;
         output ("-- Largest Allocation:          ",main_iHi," bytes\n") and skip;
         sqlite3_status(7,&main_iCur,&main_iHi,0,RValue) and skip;
         output ("-- Largest Pcache Allocation:   ",main_iHi," bytes\n") and skip;
         sqlite3_status(8,&main_iCur,&main_iHi,0,RValue) and skip;
         output ("-- Largest Scratch Allocation:  ",main_iHi," bytes\n") and skip
         
     }
     else 
     {
          skip 
     };
     free(main_pLook) and skip;
     free(main_pPCache) and skip;
     free(main_pScratch) and skip;
     free(main_pHeap) and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
      int doAutovac<==0 and skip;
     int cacheSize<==0 and skip;
     int doExclusive<==0 and skip;
     int nHeap<==0,mnHeap<==0 and skip;
     int doIncrvac<==0 and skip;
     char *zJMode<==0 and skip;
     char *zKey<==0 and skip;
     int nLook<==-1,szLook<==0 and skip;
     int noSync<==0 and skip;
     int pageSize<==0 and skip;
     int nPCache<==0,szPCache<==0 and skip;
     int doPCache<==0 and skip;
     int nScratch<==0,szScratch<==0 and skip;
     int showStats<==0 and skip;
     int nThread<==0 and skip;
     int mmapSize<==0 and skip;
     char *zTSet<=="main" and skip;
     int doTrace<==0 and skip;
     char *zEncoding<==0 and skip;
     char *zDbName<==0 and skip;
     void *pHeap<==0 and skip;
     void *pLook<==0 and skip;
     void *pPCache<==0 and skip;
     void *pScratch<==0 and skip;
     int iCur,iHi and skip;
     int i and skip;
     int rc and skip;
     main(RValue)
     )
