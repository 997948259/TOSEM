</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

frame(db,pstmt) and (
 function prepareAndRun ( char *zSql )
 {
     frame(prepareAndRun_stmtTail,prepareAndRun_rc,prepareAndRun_zMessage,prepareAndRun_iTime,prepareAndRun_1_nRow) and ( 
     char *prepareAndRun_stmtTail and skip;
     int prepareAndRun_rc and skip;
     char prepareAndRun_zMessage[1024] and skip;
     prepareAndRun_zMessage[1023]:='\0';
     int prepareAndRun_iTime and skip;
     sqlite3_snprintf(1023,prepareAndRun_zMessage,"sqlite3_prepare_v2: %s",zSql,RValue) and skip;
     prepareAndRun_rc:=sqlite3_prepare_v2(db,zSql,-1,&pstmt,&prepareAndRun_stmtTail,RValue);
     if(prepareAndRun_rc=0) then 
     {
		  int prepareAndRun_1_nRow<==0 and skip;
         sqlite3_snprintf(1023,prepareAndRun_zMessage,"sqlite3_step loop: %s",zSql,RValue) and skip;
         prepareAndRun_rc:=sqlite3_step(pstmt,RValue) ;
         while((prepareAndRun_rc)=100)
         {
             prepareAndRun_1_nRow:=prepareAndRun_1_nRow+1;
             prepareAndRun_rc:=sqlite3_step(pstmt,RValue) 
         };
         sqlite3_snprintf(1023,prepareAndRun_zMessage,"sqlite3_finalize: %s",zSql,RValue) and skip;
         prepareAndRun_rc:=sqlite3_finalize(pstmt,RValue)
         
     }
     else 
     {
          skip 
     }
     )
     }; 
  function stringcompare ( char *zLeft,char *zRight,int RValue )
 {
     frame(stringcompare_ii,return) and ( 
     int return<==0 and skip;
     int stringcompare_ii and skip;
     stringcompare_ii:=0;
     
     while( return=0 AND  zLeft[stringcompare_ii] AND zRight[stringcompare_ii])
     {
         if(zLeft[stringcompare_ii]!=zRight[stringcompare_ii]) then 
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
             stringcompare_ii:=stringcompare_ii+1
         }
         else
         {
             skip
         }
         
     };
     if(return=0)   then 
     {
         return<==1 and RValue:=(zLeft[stringcompare_ii]=zRight[stringcompare_ii]);
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
     frame(verifystat,i,main_argc,main_argv,main_zUsageMsg,main_zDb,main_zScript,main_zLog,main_logdata,main_ii,main_i,main_j,main_rc,main_zSql,main_nSql,main_9_temp$_1,main_10_isComplete,main_10_c,return) and (
     int return<==0 and skip;
     int main_argc<==8 and skip;
    // char *main_argv[]<=={"speedtest8inst1.exe","-db","speedtest8.db","-script","speedtest8.sql","-log","log.txt","-logdata"} and skip;
	 char **main_argv<==(char **) malloc( 8*sizeof(char *) ) and skip; //返回一个指向指针类型数据的首地址
	 int i<==0 and skip;
	 int verifystat<==0 and skip;
	 while(verifystat<9664443)
	 {
		verifystat:=verifystat+1
	 };
    while(i<8 )
    {
        main_argv[i]<==(char *)malloc(20) and skip;
		i:=i+1
    };
	strcpy(main_argv[0],"speedtest8inst1.exe") and skip;
	strcpy(main_argv[1],"-db") and skip;
	strcpy(main_argv[2],"speedtest8.db") and skip;
	strcpy(main_argv[3],"-script") and skip;
	strcpy(main_argv[4],"speedtest8.sql") and skip;
	strcpy(main_argv[5],"-log") and skip;
	strcpy(main_argv[6],"log.txt") and skip;
	strcpy(main_argv[7],"-logdata") and skip;

     char main_zUsageMsg[334]<=="Usage: %s options...\n  where available options are:\n\n    -db      DATABASE-FILE  (database file to operate on)\n    -script  SCRIPT-FILE    (script file to read sql from)\n    -log     LOG-FILE       (log file to create)\n    -logdata                (log all data to log file)\n\n  Options -db,main_-script and -log are compulsory\n\n" and skip;
     char *main_zDb<==0 and skip;
     char *main_zScript<==0 and skip;
     char *main_zLog<==0 and skip;
     int main_logdata<==0 and skip;
     int main_ii and skip;
     int main_i,main_j and skip;
     int main_rc and skip;
     char *main_zSql<==0 and skip;
     int main_nSql and skip;
     main_ii:=1;
     
     while(main_ii<main_argc)
     {
         if(stringcompare("-db",main_argv[main_ii],RValue) AND (main_ii+1)<main_argc) then 
         {
             main_zDb:=main_argv[(main_ii+1)];
             main_ii:=main_ii+1
             
         }
         else
         {
             if(stringcompare("-script",main_argv[main_ii],RValue) AND (main_ii+1)<main_argc) then 
             {
                 main_zScript:=main_argv[(main_ii+1)];
                 main_ii:=main_ii+1
             }
             else
             {
                 if(stringcompare("-log",main_argv[main_ii],RValue) AND (main_ii+1)<main_argc) then 
                 {
                     main_zLog:=main_argv[(main_ii+1)];
                     main_ii:=main_ii+1
                 }
                 else
                 {
                     if(stringcompare("-logdata",main_argv[main_ii],RValue)) then 
                     {
                         main_logdata:=1
                         
                     }
                     else 
                     {
                          skip 
                     }
                 }
             }
         };
         main_ii:=main_ii+1
         
     };
     main_zSql:=readScriptFile(main_zScript,&main_nSql,RValue);
     if(!main_zSql) then 
     {
         fprintf(stderr,"Failed to read script file\n") and skip;
         return<==1 and RValue:=-1;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         _unlink(main_zDb) and skip;
         main_rc:=sqlite3_open_v2(main_zDb,&db,2 | 4,NULL,RValue);
         if(main_rc!=0) then 
         {
             int main_9_temp$_1 and skip;
             main_9_temp$_1:=sqlite3_errmsg(db,RValue);
             fprintf(stderr,"Failed to open db: %s\n",main_9_temp$_1) and skip;
             return<==1 and RValue:=-2;
             skip
             
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             main_j<==0 and main_i<==main_j and skip;
             
             while(main_j<main_nSql)
             {
                 if(main_zSql[main_j]=';') then 
                 {
                     int main_10_isComplete and skip;
                     char main_10_c<==main_zSql[main_j+1] and skip;
                     main_zSql[main_j+1]:=0;
                     main_10_isComplete:=sqlite3_complete(&main_zSql[main_i],RValue);
                     main_zSql[main_j+1]:=main_10_c;
                     if(main_10_isComplete) then 
                     {
                         main_zSql[main_j]:=0;
                         while(main_i<main_j AND isspace((unsigned char)(main_zSql[main_i])))
                         {
                             main_i:=main_i+1
                         };
                         if(main_i<main_j) then 
                         {
                             prepareAndRun(&main_zSql[main_i])
                             
                         }
                         else 
                         {
                              skip 
                         };
                         main_zSql[main_j]:=';';
                         main_i:=main_j+1
                         
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
                 main_j:=main_j+1
                 
             };
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
     )
 };
  main(RValue)
 )
