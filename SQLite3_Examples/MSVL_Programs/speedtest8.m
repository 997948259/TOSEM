</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

frame(prepTime,runTime,finalizeTime,db,pstmt) and (
 
 int prepTime<==0 and skip;
 int runTime<==0 and skip;
 int finalizeTime<==0 and skip;
 function prepareAndRun ( char *zSql,int bQuiet )
 {
     frame(prepareAndRun_stmtTail,prepareAndRun_iStart,prepareAndRun_iElapse,prepareAndRun_rc,prepareAndRun_4_nRow) and ( 
     char *prepareAndRun_stmtTail and skip;
     int prepareAndRun_iStart<==0 and skip;
     int prepareAndRun_iElapse<==0 and skip;
     int prepareAndRun_rc and skip;
     if(!bQuiet) then 
     {
         output ("***************************************************************\n") and skip
         
     }
     else 
     {
          skip 
     };
     if(!bQuiet) then 
     {
		 printf("SQL statement: [%s]\n", zSql) and skip
     }
     else 
     {
          skip 
     };
     prepareAndRun_rc:=sqlite3_prepare_v2(db,zSql,-1,&pstmt,&prepareAndRun_stmtTail,RValue);
     prepTime:=prepTime+prepareAndRun_iElapse;
     if(!bQuiet) then 
     {
         output ("sqlite3_prepare_v2() returns ",prepareAndRun_rc," in ",prepareAndRun_iElapse,"ycles\n") and skip
         
     }
     else 
     {
          skip 
     };
     if(prepareAndRun_rc=0) then 
     {
         int prepareAndRun_4_nRow<==0 and skip;
         prepareAndRun_rc:=sqlite3_step(pstmt,RValue) ;
         while((prepareAndRun_rc)=100)
         {
             prepareAndRun_4_nRow:=prepareAndRun_4_nRow+1;
             prepareAndRun_rc:=sqlite3_step(pstmt,RValue) 
         };
         runTime:=runTime+prepareAndRun_iElapse;
         if(!bQuiet) then 
         {
             output ("sqlite3_step() returns ",prepareAndRun_rc," after ",prepareAndRun_4_nRow," rows in ",prepareAndRun_iElapse,"ycles\n") and skip
             
         }
         else 
         {
              skip 
         };
         prepareAndRun_rc:=sqlite3_finalize(pstmt,RValue);
         finalizeTime:=finalizeTime+prepareAndRun_iElapse;
         if(!bQuiet) then 
         {
             output ("sqlite3_finalize() returns ",prepareAndRun_rc," in ",prepareAndRun_iElapse,"ycles\n") and skip
             
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
     frame(verifystat,i,main_argc,main_argv,main_rc,main_nSql,main_zSql,main_i,main_j,main_in,main_iStart,main_iElapse,main_iSetup,main_nStmt,main_nByte,main_zArgv0,main_bQuiet,main_3_isComplete,main_3_c,main_3_4_6_n,return) and (
     int return<==0 and skip;
     int main_argc<==3 and skip;
	 char **main_argv<==(char **) malloc( 6*sizeof(char *) ) and skip; //返回一个指向指针类型数据的首地址
	 int i<==0 and skip;
	 int verifystat<==0 and skip;
	 while(verifystat<13360347)
	 {
		verifystat:=verifystat+1
	 };
    while(i<3 )
    {
        main_argv[i]<==(char *)malloc(20) and skip;
		i:=i+1
    };
	strcpy(main_argv[0],"speedtest8.exe") and skip;
	strcpy(main_argv[1],"speedtest8.db") and skip;
	strcpy(main_argv[2],"speedtest8.sql") and skip;


     int main_rc and skip;
     int main_nSql and skip;
     char *main_zSql and skip;
     int main_i,main_j and skip;
     FILE *main_in and skip;
     int main_iStart<==0 and skip;
     int main_iElapse<==0 and skip;
     int main_iSetup<==0 and skip;
     int main_nStmt<==0 and skip;
     int main_nByte<==0 and skip;
     char *main_zArgv0<==main_argv[0] and skip;
     int main_bQuiet<==0 and skip;
     if(main_argc!=3) then 
     {
         fprintf(stderr,"Usage: %s [options] FILENAME SQL-SCRIPT\nRuns SQL-SCRIPT against a UTF8 database\n\toptions:\n\t-priority <value> : set priority of task\n\t-quiet : only display summary results\n",main_zArgv0) and skip
         
     }
     else 
     {
          skip 
     };
     main_in:=fopen(main_argv[2],"r");
     fseek(main_in,0,2) and skip;
     main_nSql:=ftell(main_in,RValue);
     main_zSql:=malloc(main_nSql+1);
     fseek(main_in,0,0) and skip;
     main_nSql:=fread(main_zSql,1,main_nSql,main_in);
     main_zSql[main_nSql]:=0;
     output ("SQLite version: ",sqlite3_libversion_number(RValue),"\n") and skip;
     _unlink(main_argv[1]) and skip;
     main_rc:=sqlite3_open(main_argv[1],&db,RValue);
	 printf("aaaa\n") and skip;
     main_iSetup:=main_iElapse;
     if(!main_bQuiet) then 
     {
         output ("sqlite3_open() returns ",main_rc," in ",main_iElapse,"ycles\n") and skip
     }
     else 
     {
          skip 
     };
     main_j<==0 and main_i<==main_j and skip;
     
     while(main_j<main_nSql)
     {
         if(main_zSql[main_j]=';') then 
         {
             int main_3_isComplete and skip;
             char main_3_c<==main_zSql[main_j+1] and skip;
             main_zSql[main_j+1]:=0;
             main_3_isComplete:=sqlite3_complete(&main_zSql[main_i],RValue);
             main_zSql[main_j+1]:=main_3_c;
             if(main_3_isComplete) then 
             {
                 main_zSql[main_j]:=0;
                 while(main_i<main_j AND isspace(main_zSql[main_i]))
                 {
                     main_i:=main_i+1
                 };
                 if(main_i<main_j) then 
                 {
                     int main_3_4_6_n<==main_j-main_i and skip;
                     if(main_3_4_6_n>=6 AND memcmp(&main_zSql[main_i],".crash",6,RValue)=0) then 
                     {
                          skip 
                     }
                     else 
                     {
                          skip 
                     };
                     main_nStmt:=main_nStmt+1;
                     main_nByte:=main_nByte+main_3_4_6_n;
                     prepareAndRun(&main_zSql[main_i],main_bQuiet)
                     
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
     sqlite3_close(db,RValue) and skip;
     main_iSetup:=main_iSetup+main_iElapse;
     if(!main_bQuiet) then 
     {
         output ("sqlite3_close() returns in ",main_iElapse,"ycles\n") and skip
     }
     else 
     {
          skip 
     };
     output ("\n") and skip;
     output ("Statements run:        ",main_nStmt," stmts\n") and skip;
     output ("Bytes of SQL text:     ",main_nByte," bytes\n") and skip;
     output ("Total prepare time:    ",prepTime,"ycles\n") and skip;
     output ("Total run time:        ",runTime,"ycles\n") and skip;
     output ("Total finalize time:   ",finalizeTime,"ycles\n") and skip;
     output ("Open/Close time:       ",main_iSetup,"ycles\n") and skip;
     output ("Total time:            ",prepTime+runTime+finalizeTime+main_iSetup,"ycles\n") and skip;
     return<==1 and RValue:=0;
     skip
     )
 };
  main(RValue)
 )
