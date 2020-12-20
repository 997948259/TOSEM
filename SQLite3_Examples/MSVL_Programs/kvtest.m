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


frame(i,zHelp,argc,argv,db,pstmt,pBlob) and (
char zHelp[1434]<=="Usage: kvtest COMMAND ARGS...\n\n   kvtest init DBFILE --count N --size M --pagesize X\n\n        Generate a new test database file named DBFILE containing N\n        BLOBs each of size M bytes.  The page size of the new database\n        file will be X.  Additional options:\n\n           --variance V           Randomly vary M by plus or minus V\n\n   kvtest export DBFILE DIRECTORY\n\n        Export all the blobs in the kv table of DBFILE into separate\n        files in DIRECTORY.\n\n   kvtest stat DBFILE\n\n        Display summary information about DBFILE\n\n   kvtest run DBFILE [options]\n\n        Run a performance test.  DBFILE can be either the name of a\n        database or a directory containing sample files.  Options:\n\n           --asc                  Read blobs in ascending order\n           --blob-api             Use the BLOB API\n           --cache-size N         Database cache size\n           --count N              Read N blobs\n           --desc                 Read blobs in descending order\n           --max-id N             Maximum blob key to use\n           --mmap N               Mmap as much as N bytes of DBFILE\n           --jmode MODE           Set MODE journal mode prior to starting\n           --random               Read blobs in a random order\n           --start N              Start reading with this blob key\n           --stats                Output operating stats before exiting\n" and skip;
int argc<==7 and skip;
//char *argv[]<=={"kvtest.exe","run","kvtest.db","--count","100","--max-id","100"} and skip;
char **argv<==(char **) malloc( 7*sizeof(char *) ) and skip; //返回一个指向指针类型数据的首地址
	 int i<==0 and skip;
    while(i<7 )
    {
        argv[i]<==(char *)malloc(20) and skip;
		i:=i+1
    };
	strcpy(argv[0],"kvtest.exe") and skip;
	strcpy(argv[1],"run") and skip;
	strcpy(argv[2],"kvtest.db") and skip;
	strcpy(argv[3],"--count") and skip;
	strcpy(argv[4],"100") and skip;
	strcpy(argv[5],"--max-id") and skip;
	strcpy(argv[6],"100") and skip;

 function showHelp (  )
 {
     fprintf(stdout,"%s",zHelp) and skip
     
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
  function randInt ( int RValue )
 {
     frame(randInt_x,randInt_y,return) and ( 
     int return<==0 and skip;
     int randInt_x<==0x333a13cd and skip;
     int randInt_y<==0xecb2adea and skip;
     randInt_x:=(randInt_x>>1) ^ ((1+~(randInt_x & 1)) & 0xd0000001);
     randInt_y:=randInt_y*1103515245+12345;
     return<==1 and RValue:=randInt_x ^ randInt_y;
     skip
     )
     }; 
 function initMain ( int RValue )
 {
     frame(initMain_zDb,initMain_i,initMain_rc,initMain_nCount,initMain_sz,initMain_iVariance,initMain_pgsz,initMain_zSql,initMain_zErrMsg,initMain_z,return,continue) and ( 
     int continue<==0 and skip;
     int return<==0 and skip;
     char *initMain_zDb and skip;
     int initMain_i,initMain_rc and skip;
     int initMain_nCount<==1000 and skip;
     int initMain_sz<==10000 and skip;
     int initMain_iVariance<==0 and skip;
     int initMain_pgsz<==4096 and skip;
     char *initMain_zSql and skip;
     char *initMain_zErrMsg<==0 and skip;
     initMain_zDb:=argv[2];
     continue<==0 and skip;
     initMain_i:=3;

     while(initMain_i<argc)
     {
          continue<==0 and skip;
         char *initMain_z<==argv[initMain_i] and skip;
         if(initMain_z[1]='-') then 
         {
             initMain_z:=initMain_z+1
         }
         else 
         {
              skip 
         };
         if(strcmp(initMain_z,"-count")=0) then 
         {
             initMain_nCount:=integerValue(argv[(initMain_i+1)],RValue);
             initMain_i:=initMain_i+1;
             continue<==1 and skip;
              initMain_i:=initMain_i+1
         }
         else 
         {
              skip 
         };
         if(continue=0)   then 
         {
             if(strcmp(initMain_z,"-size")=0) then 
             {
                 initMain_sz:=integerValue(argv[(initMain_i+1)],RValue);
                 initMain_i:=initMain_i+1;
                 continue<==1 and skip;
                  initMain_i:=initMain_i+1
             }
             else 
             {
                  skip 
             };
             if(continue=0)   then 
             {
                 if(strcmp(initMain_z,"-variance")=0) then 
                 {
                     initMain_iVariance:=integerValue(argv[(initMain_i+1)],RValue);
                     initMain_i:=initMain_i+1;
                     continue<==1 and skip;
                      initMain_i:=initMain_i+1
                 }
                 else 
                 {
                      skip 
                 };
                 if(continue=0)   then 
                 {
                     if(strcmp(initMain_z,"-pagesize")=0) then 
                     {
                         initMain_pgsz:=integerValue(argv[(initMain_i+1)],RValue);
                         initMain_i:=initMain_i+1;
                         continue<==1 and skip;
                          initMain_i:=initMain_i+1
                     }
                     else 
                     {
                          skip 
                     };
                     if(continue=0)   then 
                     {
                         initMain_i:=initMain_i+1
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
         }
         else
         {
             skip
         }
         
     };
     continue<==0 and skip;
     initMain_rc:=sqlite3_open(initMain_zDb,&db,RValue);
     initMain_zSql:=sqlite3_mprintf("DROP TABLE IF EXISTS kv;\nPRAGMA page_size=%d;\nVACUUM;\nBEGIN;\nCREATE TABLE kv(k INTEGER PRIMARY KEY, v BLOB);\nWITH RECURSIVE c(x) AS (VALUES(1) UNION ALL SELECT x+1 FROM c WHERE x<%d) INSERT INTO kv(k,v) SELECT x, randomblob(%d+(random()%%(%d))) FROM c;\nCOMMIT;\n",initMain_pgsz,initMain_nCount,initMain_sz,initMain_iVariance+1,RValue);
     initMain_rc:=sqlite3_exec(db,initMain_zSql,0,0,&initMain_zErrMsg,RValue);
     sqlite3_free(initMain_zSql,RValue) and skip;
     sqlite3_close(db,RValue) and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
 function statMain ( int RValue )
 {
     frame(statMain_zDb,statMain_i,statMain_rc,statMain_zSql,statMain_z,return) and ( 
     int return<==0 and skip;
     char *statMain_zDb and skip;
     int statMain_i,statMain_rc and skip;
     char *statMain_zSql and skip;
     statMain_zDb:=argv[2];
     statMain_i:=3;
     
     while(statMain_i<argc)
     {
         char *statMain_z<==argv[statMain_i] and skip;
         if(statMain_z[1]='-') then 
         {
             statMain_z:=statMain_z+1
         }
         else 
         {
              skip 
         };
         statMain_i:=statMain_i+1
         
     };
     statMain_rc:=sqlite3_open(statMain_zDb,&db,RValue);
     statMain_zSql:=sqlite3_mprintf("SELECT count(*), min(length(v)), max(length(v)), avg(length(v))  FROM kv",RValue);
     statMain_rc:=sqlite3_prepare_v2(db,statMain_zSql,-1,&pstmt,0,RValue);
     sqlite3_free(statMain_zSql,RValue) and skip;
     if(sqlite3_step(pstmt,RValue)=100) then 
     {
         output ("Number of entries:  ",sqlite3_column_int(pstmt,0,RValue),"\n") and skip;
         output ("Average value size: ",sqlite3_column_int(pstmt,3,RValue),"\n") and skip;
         output ("Minimum value size: ",sqlite3_column_int(pstmt,1,RValue),"\n") and skip;
         output ("Maximum value size: ",sqlite3_column_int(pstmt,2,RValue),"\n") and skip
         
     }
     else
     {
         output ("No rows\n") and skip
     };
     sqlite3_finalize(pstmt,RValue) and skip;
     statMain_zSql:=sqlite3_mprintf("PRAGMA page_size",RValue);
     statMain_rc:=sqlite3_prepare_v2(db,statMain_zSql,-1,&pstmt,0,RValue);
     sqlite3_free(statMain_zSql,RValue) and skip;
     if(sqlite3_step(pstmt,RValue)=100) then 
     {
         output ("Page-size:          ",sqlite3_column_int(pstmt,0,RValue),"\n") and skip
         
     }
     else 
     {
          skip 
     };
     sqlite3_finalize(pstmt,RValue) and skip;
     statMain_zSql:=sqlite3_mprintf("PRAGMA page_count",RValue);
     statMain_rc:=sqlite3_prepare_v2(db,statMain_zSql,-1,&pstmt,0,RValue);
     sqlite3_free(statMain_zSql,RValue) and skip;
     if(sqlite3_step(pstmt,RValue)=100) then 
     {
         output ("Page-count:         ",sqlite3_column_int(pstmt,0,RValue),"\n") and skip
         
     }
     else 
     {
          skip 
     };
     sqlite3_finalize(pstmt,RValue) and skip;
     sqlite3_close(db,RValue) and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function exportMain ( int RValue )
 {
     frame(exportMain_zDb,exportMain_zDir,exportMain_zSql,exportMain_rc,exportMain_zErrMsg,return) and ( 
     int return<==0 and skip;
     char *exportMain_zDb and skip;
     char *exportMain_zDir and skip;
     char *exportMain_zSql and skip;
     int exportMain_rc and skip;
     char *exportMain_zErrMsg<==0 and skip;
     exportMain_zDb:=argv[2];
     exportMain_zDir:=argv[3];
     exportMain_rc:=sqlite3_open(exportMain_zDb,&db,RValue);
     exportMain_zSql:=sqlite3_mprintf("SELECT writefile(printf('%s/%%06d',k),v) FROM kv;",exportMain_zDir,RValue);
     exportMain_rc:=sqlite3_exec(db,exportMain_zSql,0,0,&exportMain_zErrMsg,RValue);
     sqlite3_free(exportMain_zSql,RValue) and skip;
     sqlite3_close(db,RValue) and skip;
     output ("\n") and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function readFile ( char *zName,int *pnByte,unsigned char* RValue )
 {
     frame(readFile_in,readFile_nIn,readFile_nRead,readFile_pBuf,return) and ( 
     int return<==0 and skip;
     FILE *readFile_in and skip;
     int readFile_nIn and skip;
     int readFile_nRead and skip;
     unsigned char *readFile_pBuf and skip;
     readFile_nIn:=fileSize(zName,RValue);
     if(readFile_nIn<0) then 
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
         readFile_in:=fopen(zName,"rb");
         if(readFile_in=0) then 
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
             readFile_pBuf:=sqlite3_malloc64(readFile_nIn,RValue);
             if(readFile_pBuf=0) then 
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
                 readFile_nRead:=fread(readFile_pBuf,(int)readFile_nIn,1,readFile_in);
                 fclose(readFile_in) and skip;
                 if(readFile_nRead!=1) then 
                 {
                     sqlite3_free(readFile_pBuf,RValue) and skip;
                     return<==1 and RValue:=0;
                     skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 if(return=0)   then 
                 {
                     if(pnByte) then 
                     {
                         * pnByte:=(int)readFile_nIn
                     }
                     else 
                     {
                          skip 
                     };
                     return<==1 and RValue:=readFile_pBuf;
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
     }
     else
     {
         skip
     }
     )
     }; 
  function display_stats ( int bReset,int RValue )
 {
     frame(display_stats_iCur,display_stats_iHiwtr,display_stats_out,return) and ( 
     int return<==0 and skip;
     int display_stats_iCur and skip;
     int display_stats_iHiwtr and skip;
     FILE *display_stats_out<==stdout and skip;
     fprintf(display_stats_out,"\n") and skip;
     display_stats_iCur<==-1 and display_stats_iHiwtr<==display_stats_iCur and skip;
     sqlite3_status(0,&display_stats_iCur,&display_stats_iHiwtr,bReset,RValue) and skip;
     fprintf(display_stats_out,"Memory Used:                         %d (max %d) bytes\n",display_stats_iCur,display_stats_iHiwtr) and skip;
     display_stats_iCur<==-1 and display_stats_iHiwtr<==display_stats_iCur and skip;
     sqlite3_status(9,&display_stats_iCur,&display_stats_iHiwtr,bReset,RValue) and skip;
     fprintf(display_stats_out,"Number of Outstanding Allocations:   %d (max %d)\n",display_stats_iCur,display_stats_iHiwtr) and skip;
     display_stats_iCur<==-1 and display_stats_iHiwtr<==display_stats_iCur and skip;
     sqlite3_status(1,&display_stats_iCur,&display_stats_iHiwtr,bReset,RValue) and skip;
     fprintf(display_stats_out,"Number of Pcache Pages Used:         %d (max %d) pages\n",display_stats_iCur,display_stats_iHiwtr) and skip;
     display_stats_iCur<==-1 and display_stats_iHiwtr<==display_stats_iCur and skip;
     sqlite3_status(2,&display_stats_iCur,&display_stats_iHiwtr,bReset,RValue) and skip;
     fprintf(display_stats_out,"Number of Pcache Overflow Bytes:     %d (max %d) bytes\n",display_stats_iCur,display_stats_iHiwtr) and skip;
     display_stats_iCur<==-1 and display_stats_iHiwtr<==display_stats_iCur and skip;
     sqlite3_status(3,&display_stats_iCur,&display_stats_iHiwtr,bReset,RValue) and skip;
     fprintf(display_stats_out,"Number of Scratch Allocations Used:  %d (max %d)\n",display_stats_iCur,display_stats_iHiwtr) and skip;
     display_stats_iCur<==-1 and display_stats_iHiwtr<==display_stats_iCur and skip;
     sqlite3_status(4,&display_stats_iCur,&display_stats_iHiwtr,bReset,RValue) and skip;
     fprintf(display_stats_out,"Number of Scratch Overflow Bytes:    %d (max %d) bytes\n",display_stats_iCur,display_stats_iHiwtr) and skip;
     display_stats_iCur<==-1 and display_stats_iHiwtr<==display_stats_iCur and skip;
     sqlite3_status(5,&display_stats_iCur,&display_stats_iHiwtr,bReset,RValue) and skip;
     fprintf(display_stats_out,"Largest Allocation:                  %d bytes\n",display_stats_iHiwtr) and skip;
     display_stats_iCur<==-1 and display_stats_iHiwtr<==display_stats_iCur and skip;
     sqlite3_status(7,&display_stats_iCur,&display_stats_iHiwtr,bReset,RValue) and skip;
     fprintf(display_stats_out,"Largest Pcache Allocation:           %d bytes\n",display_stats_iHiwtr) and skip;
     display_stats_iCur<==-1 and display_stats_iHiwtr<==display_stats_iCur and skip;
     sqlite3_status(8,&display_stats_iCur,&display_stats_iHiwtr,bReset,RValue) and skip;
     fprintf(display_stats_out,"Largest Scratch Allocation:          %d bytes\n",display_stats_iHiwtr) and skip;
     display_stats_iCur<==-1 and display_stats_iHiwtr<==display_stats_iCur and skip;
     sqlite3_db_status(db,1,&display_stats_iCur,&display_stats_iHiwtr,bReset,RValue) and skip;
     fprintf(display_stats_out,"Pager Heap Usage:                    %d bytes\n",display_stats_iCur) and skip;
     display_stats_iCur<==-1 and display_stats_iHiwtr<==display_stats_iCur and skip;
     sqlite3_db_status(db,7,&display_stats_iCur,&display_stats_iHiwtr,1,RValue) and skip;
     fprintf(display_stats_out,"Page cache hits:                     %d\n",display_stats_iCur) and skip;
     display_stats_iCur<==-1 and display_stats_iHiwtr<==display_stats_iCur and skip;
     sqlite3_db_status(db,8,&display_stats_iCur,&display_stats_iHiwtr,1,RValue) and skip;
     fprintf(display_stats_out,"Page cache misses:                   %d\n",display_stats_iCur) and skip;
     display_stats_iCur<==-1 and display_stats_iHiwtr<==display_stats_iCur and skip;
     sqlite3_db_status(db,9,&display_stats_iCur,&display_stats_iHiwtr,1,RValue) and skip;
     fprintf(display_stats_out,"Page cache writes:                   %d\n",display_stats_iCur) and skip;
     display_stats_iCur<==-1 and display_stats_iHiwtr<==display_stats_iCur and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function runMain ( int RValue )
 {
     frame(verifystat,runMain_eType,runMain_zDb,runMain_i,runMain_rc,runMain_nCount,runMain_nExtra,runMain_iKey,runMain_iMax,runMain_iPagesize,runMain_iCache,runMain_bBlobApi,runMain_bStats,runMain_eOrder,runMain_tmStart,runMain_tmElapsed,runMain_mmapSize,runMain_nData,runMain_nTotal,runMain_pData,runMain_nAlloc,runMain_zJMode,runMain_z,runMain_13_zSql,runMain_13_18_temp$_1,runMain_23_zKey,nm_1$,switch$,return,break$,continue) and ( 
     int continue<==0 and skip;
     int break$<==0 and skip;
     int return<==0 and skip;
     int runMain_eType and skip;
     char *runMain_zDb and skip;
     int runMain_i and skip;
     int runMain_rc and skip;
     int runMain_nCount<==1000 and skip;
     int runMain_nExtra<==0 and skip;
     int runMain_iKey<==1 and skip;
     int runMain_iMax<==0 and skip;
     int runMain_iPagesize<==0 and skip;
     int runMain_iCache<==1000 and skip;
     int runMain_bBlobApi<==0 and skip;
     int runMain_bStats<==0 and skip;
     int runMain_eOrder<==1 and skip;
     int runMain_tmStart and skip;
     int runMain_tmElapsed and skip;
     int runMain_mmapSize<==0 and skip;
     int runMain_nData<==0 and skip;
     int runMain_nTotal<==0 and skip;
     unsigned char *runMain_pData<==0 and skip;
     int runMain_nAlloc<==0 and skip;
     char *runMain_zJMode<==0 and skip;
     runMain_zDb:=argv[2];
	 int verifystat<==0 and skip;
	 while(verifystat<19731771)
	 {
		verifystat:=verifystat+1
	 };
     runMain_eType:=pathType(runMain_zDb,RValue);
     continue<==0 and skip;
     runMain_i:=3;
     
     while(runMain_i<argc)
     {
          continue<==0 and skip;
         char *runMain_z<==argv[runMain_i] and skip;
         if(runMain_z[1]='-') then 
         {
             runMain_z:=runMain_z+1
         }
         else 
         {
              skip 
         };
         if(strcmp(runMain_z,"-count")=0) then 
         {
             runMain_nCount:=integerValue(argv[(runMain_i+1)],RValue);
             runMain_i:=runMain_i+1;
             continue<==1 and skip;
              runMain_i:=runMain_i+1
         }
         else 
         {
              skip 
         };
         if(continue=0)   then 
         {
             if(strcmp(runMain_z,"-mmap")=0) then 
             {
                 runMain_mmapSize:=integerValue(argv[(runMain_i+1)],RValue);
                 runMain_i:=runMain_i+1;
                 continue<==1 and skip;
                  runMain_i:=runMain_i+1
             }
             else 
             {
                  skip 
             };
             if(continue=0)   then 
             {
                 if(strcmp(runMain_z,"-max-id")=0) then 
                 {
                     runMain_iMax:=integerValue(argv[(runMain_i+1)],RValue);
                     runMain_i:=runMain_i+1;
                     continue<==1 and skip;
                      runMain_i:=runMain_i+1
                 }
                 else 
                 {
                      skip 
                 };
                 if(continue=0)   then 
                 {
                     if(strcmp(runMain_z,"-start")=0) then 
                     {
                         runMain_iKey:=integerValue(argv[(runMain_i+1)],RValue);
                         runMain_i:=runMain_i+1;
                         continue<==1 and skip;
                          runMain_i:=runMain_i+1
                     }
                     else 
                     {
                          skip 
                     };
                     if(continue=0)   then 
                     {
                         if(strcmp(runMain_z,"-cache-size")=0) then 
                         {
                             runMain_iCache:=integerValue(argv[(runMain_i+1)],RValue);
                             runMain_i:=runMain_i+1;
                             continue<==1 and skip;
                              runMain_i:=runMain_i+1
                         }
                         else 
                         {
                              skip 
                         };
                         if(continue=0)   then 
                         {
                             if(strcmp(runMain_z,"-jmode")=0) then 
                             {
                                 runMain_zJMode:=argv[(runMain_i+1)];
                                 runMain_i:=runMain_i+1;
                                 continue<==1 and skip;
                                  runMain_i:=runMain_i+1
                             }
                             else 
                             {
                                  skip 
                             };
                             if(continue=0)   then 
                             {
                                 if(strcmp(runMain_z,"-random")=0) then 
                                 {
                                     runMain_eOrder:=3;
                                     continue<==1 and skip;
                                      runMain_i:=runMain_i+1
                                 }
                                 else 
                                 {
                                      skip 
                                 };
                                 if(continue=0)   then 
                                 {
                                     if(strcmp(runMain_z,"-asc")=0) then 
                                     {
                                         runMain_eOrder:=1;
                                         continue<==1 and skip;
                                          runMain_i:=runMain_i+1
                                     }
                                     else 
                                     {
                                          skip 
                                     };
                                     if(continue=0)   then 
                                     {
                                         if(strcmp(runMain_z,"-desc")=0) then 
                                         {
                                             runMain_eOrder:=2;
                                             continue<==1 and skip;
                                              runMain_i:=runMain_i+1
                                         }
                                         else 
                                         {
                                              skip 
                                         };
                                         if(continue=0)   then 
                                         {
                                             if(strcmp(runMain_z,"-blob-api")=0) then 
                                             {
                                                 runMain_bBlobApi:=1;
                                                 continue<==1 and skip;
                                                  runMain_i:=runMain_i+1
                                             }
                                             else 
                                             {
                                                  skip 
                                             };
                                             if(continue=0)   then 
                                             {
                                                 if(strcmp(runMain_z,"-stats")=0) then 
                                                 {
                                                     runMain_bStats:=1;
                                                     continue<==1 and skip;
                                                      runMain_i:=runMain_i+1
                                                 }
                                                 else 
                                                 {
                                                      skip 
                                                 };
                                                 if(continue=0)   then 
                                                 {
                                                     runMain_i:=runMain_i+1
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
     runMain_tmStart:=0;
     if(runMain_eType=2) then 
     {
         char *runMain_13_zSql and skip;
         runMain_rc:=sqlite3_open(runMain_zDb,&db,RValue);
         runMain_13_zSql:=sqlite3_mprintf("PRAGMA mmap_size=%d",runMain_mmapSize,RValue);
         sqlite3_exec(db,runMain_13_zSql,0,0,0,RValue) and skip;
         runMain_13_zSql:=sqlite3_mprintf("PRAGMA cache_size=%d",runMain_iCache,RValue);
         sqlite3_exec(db,runMain_13_zSql,0,0,0,RValue) and skip;
         sqlite3_free(runMain_13_zSql,RValue) and skip;
         pstmt:=0;
         sqlite3_prepare_v2(db,"PRAGMA page_size",-1,&pstmt,0,RValue) and skip;
         if(sqlite3_step(pstmt,RValue)=100) then 
         {
             runMain_iPagesize:=sqlite3_column_int(pstmt,0,RValue)
             
         }
         else 
         {
              skip 
         };
         sqlite3_finalize(pstmt,RValue) and skip;
         sqlite3_prepare_v2(db,"PRAGMA cache_size",-1,&pstmt,0,RValue) and skip;
         if(sqlite3_step(pstmt,RValue)=100) then 
         {
             runMain_iCache:=sqlite3_column_int(pstmt,0,RValue)
             
         }
         else
         {
             runMain_iCache:=0
         };
         sqlite3_finalize(pstmt,RValue) and skip;
         pstmt:=0;
         if(runMain_zJMode) then 
         {
             runMain_13_zSql:=sqlite3_mprintf("PRAGMA journal_mode=%Q",runMain_zJMode,RValue);
             sqlite3_exec(db,runMain_13_zSql,0,0,0,RValue) and skip;
             sqlite3_free(runMain_13_zSql,RValue) and skip
             
         }
         else 
         {
              skip 
         };
         sqlite3_prepare_v2(db,"PRAGMA journal_mode",-1,&pstmt,0,RValue) and skip;
         if(sqlite3_step(pstmt,RValue)=100) then 
         {
             int runMain_13_18_temp$_1 and skip;
             runMain_13_18_temp$_1:=sqlite3_column_text(pstmt,0,RValue);
             runMain_zJMode:=sqlite3_mprintf("%s",runMain_13_18_temp$_1,RValue)
             
         }
         else
         {
             runMain_zJMode:="???"
         };
         sqlite3_finalize(pstmt,RValue) and skip;
         if(runMain_iMax<=0) then 
         {
             sqlite3_prepare_v2(db,"SELECT max(k) FROM kv",-1,&pstmt,0,RValue) and skip;
             if(sqlite3_step(pstmt,RValue)=100) then 
             {
                 runMain_iMax:=sqlite3_column_int(pstmt,0,RValue)
                 
             }
             else 
             {
                  skip 
             };
             sqlite3_finalize(pstmt,RValue) and skip
             
         }
         else 
         {
              skip 
         };
         pstmt:=0;
         sqlite3_exec(db,"BEGIN",0,0,0,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     if(runMain_iMax<=0) then 
     {
         runMain_iMax:=1000
     }
     else 
     {
          skip 
     };
     runMain_i:=0;
     
     while(runMain_i<runMain_nCount)
     {
         if(runMain_eType=1) then 
         {
             char *runMain_23_zKey and skip;
             runMain_23_zKey:=sqlite3_mprintf("%s/%06d",runMain_zDb,runMain_iKey,RValue);
             runMain_nData:=0;
             runMain_pData:=readFile(runMain_23_zKey,&runMain_nData,RValue);
             sqlite3_free(runMain_23_zKey,RValue) and skip;
             sqlite3_free(runMain_pData,RValue) and skip
             
         }
         else
         {
             if(runMain_bBlobApi) then 
             {
                 if(pBlob=0) then 
                 {
                     runMain_rc:=sqlite3_blob_open(db,"main","kv","v",runMain_iKey,0,&pBlob,RValue)
                     
                 }
                 else
                 {
                     runMain_rc:=sqlite3_blob_reopen(pBlob,runMain_iKey,RValue)
                 };
                 if(runMain_rc=0) then 
                 {
                     runMain_nData:=sqlite3_blob_bytes(pBlob,RValue);
                     if(runMain_nAlloc<runMain_nData+1) then 
                     {
                         runMain_nAlloc:=runMain_nData+100;
                         runMain_pData:=sqlite3_realloc(runMain_pData,runMain_nAlloc,RValue)
                         
                     }
                     else 
                     {
                          skip 
                     };
                     runMain_rc:=sqlite3_blob_read(pBlob,runMain_pData,runMain_nData,0,RValue)
                     
                 }
                 else 
                 {
                      skip 
                 }
             }
             else
             {
                 if(pstmt=0) then 
                 {
                     runMain_rc:=sqlite3_prepare_v2(db,"SELECT v FROM kv WHERE k=?1",-1,&pstmt,0,RValue)
                     
                 }
                 else
                 {
                     sqlite3_reset(pstmt,RValue) and skip
                 };
                 sqlite3_bind_int(pstmt,1,runMain_iKey,RValue) and skip;
                 runMain_rc:=sqlite3_step(pstmt,RValue);
                 if(runMain_rc=100) then 
                 {
                     runMain_nData<==sqlite3_column_bytes(pstmt,0,RValue) and skip;
                     runMain_pData<==(unsigned char *)sqlite3_column_blob(pstmt,0,RValue) and skip
                 }
                 else
                 {
                     runMain_nData:=0
                 }
             }
         };
         if(runMain_eOrder=1) then 
         {
             runMain_iKey:=runMain_iKey+1;
             if(runMain_iKey>runMain_iMax) then 
             {
                 runMain_iKey:=1
             }
             else 
             {
                  skip 
             }
             
         }
         else
         {
             if(runMain_eOrder=2) then 
             {
                 runMain_iKey:=runMain_iKey-1;
                 if(runMain_iKey<=0) then 
                 {
                     runMain_iKey:=runMain_iMax
                 }
                 else 
                 {
                      skip 
                 }
             }
             else
             {
                 runMain_iKey:=(randInt(RValue) % runMain_iMax)+1
             }
         };
         runMain_nTotal:=runMain_nTotal+runMain_nData;
         if(runMain_nData=0) then 
         {
             runMain_nCount:=runMain_nCount+1;
             runMain_nExtra:=runMain_nExtra+1
             
         }
         else 
         {
              skip 
         };
         runMain_i:=runMain_i+1
         
     };
     if(runMain_nAlloc) then 
     {
         sqlite3_free(runMain_pData,RValue) and skip
     }
     else 
     {
          skip 
     };
     if(pstmt) then 
     {
         sqlite3_finalize(pstmt,RValue) and skip
     }
     else 
     {
          skip 
     };
     if(pBlob) then 
     {
         sqlite3_blob_close(pBlob,RValue) and skip
     }
     else 
     {
          skip 
     };
     if(runMain_bStats) then 
     {
         display_stats(0,RValue)
         
     }
     else 
     {
          skip 
     };
     if(db) then 
     {
         sqlite3_close(db,RValue) and skip
     }
     else 
     {
          skip 
     };
     runMain_tmElapsed:=0;
     if(runMain_nExtra) then 
     {
         output (runMain_nCount," cycles due to ",runMain_nExtra," misses\n"," misses\n") and skip
         
     }
     else 
     {
          skip 
     };
     if(runMain_eType=2) then 
     {
         output ("SQLite version: ",sqlite3_libversion(RValue),"\n") and skip
         
     }
     else 
     {
          skip 
     };
     output ("--count ",runMain_nCount-runMain_nExtra," --max-id ",runMain_iMax) and skip;
     int switch$ and skip;
     break$<==0 and skip;
      switch$<==0 and skip;
      int nm_1$ and skip;
     nm_1$ := runMain_eOrder;
     if (nm_1$=3 OR (switch$=1 AND break$=0 AND return=0) ) then 
     {
         switch$<==1 and skip;
         output (" --random\n") and skip;
         break$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_1$=2 OR (switch$=1 AND break$=0 AND return=0) ) then 
     {
         switch$<==1 and skip;
         output (" --desc\n") and skip;
         break$<==1 and skip
          
     }
     else
     {
         skip
     };
     if(break$=0 AND return=0) then 
     {
         output (" --asc\n") and skip;
         break$<==1 and skip
          
     }
     else
     {
          skip
     };
     if(runMain_eType=2) then 
     {
         printf("--cache-size %d --jmode %s\n", runMain_iCache, runMain_zJMode) and skip;
         output ("--mmap ",runMain_mmapSize,( if(runMain_bBlobApi) then " --blob-api" else ""),"\n") and skip
     }
     else 
     {
          skip 
     };
     if(runMain_iPagesize) then 
     {
         output ("Database page size: ",runMain_iPagesize,"\n") and skip
     }
     else 
     {
          skip 
     };
     output ("Total elapsed time: ",runMain_tmElapsed/ 1000.0,"\n") and skip;
     output ("Microseconds per BLOB read: ",runMain_tmElapsed*1000.0/ runMain_nCount,"\n") and skip;
     output ("Content read rate: ",runMain_nTotal/ (1000.0*runMain_tmElapsed)," MB/s\n") and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function main ( int RValue )
 {
     frame(return) and (
     int return<==0 and skip;
     if(argc<3) then 
     {
         showHelp()
     }
     else 
     {
          skip 
     };
     if(strcmp(argv[1],"init")=0) then 
     {
         return<==1 and RValue:=initMain(RValue);
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         if(strcmp(argv[1],"export")=0) then 
         {
             return<==1 and RValue:=exportMain(RValue);
             skip
             
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             if(strcmp(argv[1],"run")=0) then 
             {
                 return<==1 and RValue:=runMain(RValue);
                 skip
                 
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 if(strcmp(argv[1],"stat")=0) then 
                 {
                     return<==1 and RValue:=statMain(RValue);
                     skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 if(return=0)   then 
                 {
                     showHelp();
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
  main(RValue)
 )
