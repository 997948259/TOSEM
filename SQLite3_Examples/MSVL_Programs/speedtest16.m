</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

frame(db,pstmt,prepTime,runTime,finalizeTime) and (
 function asciiToUtf16le ( char *z, void* RValue )
 {
     frame(asciiToUtf16le_n,asciiToUtf16le_z16,asciiToUtf16le_i,asciiToUtf16le_j,return) and ( 
     int return<==0 and skip;
     int asciiToUtf16le_n and skip;
     asciiToUtf16le_n:=strlen(z);
     char *asciiToUtf16le_z16 and skip;
     int asciiToUtf16le_i,asciiToUtf16le_j and skip;
     asciiToUtf16le_z16:=malloc(asciiToUtf16le_n*2+2);
     asciiToUtf16le_j<==0 and asciiToUtf16le_i<==asciiToUtf16le_j and skip;
     
     while(asciiToUtf16le_i<=asciiToUtf16le_n)
     {
         asciiToUtf16le_z16[asciiToUtf16le_j]:=z[asciiToUtf16le_i];
         asciiToUtf16le_j:=asciiToUtf16le_j+1;
         asciiToUtf16le_z16[asciiToUtf16le_j]:=0;
         asciiToUtf16le_j:=asciiToUtf16le_j+1;
         asciiToUtf16le_i:=asciiToUtf16le_i+1
         
     };
     return<==1 and skip;
	  RValue:=(void *)asciiToUtf16le_z16
     )
     }; 
      int prepTime<==0 and skip;
     int runTime<==0 and skip;
     int finalizeTime<==0 and skip;
 function prepareAndRun ( char *zSql )
 {
     frame(prepareAndRun_utf16,prepareAndRun_stmtTail,prepareAndRun_iStart,prepareAndRun_iElapse,prepareAndRun_rc,prepareAndRun_1_nRow) and ( 
     void *prepareAndRun_utf16 and skip;
     void *prepareAndRun_stmtTail and skip;
     int prepareAndRun_iStart<==0 and skip;
     int prepareAndRun_iElapse<==0 and skip;
     int prepareAndRun_rc and skip;
     output ("****************************************************************\n") and skip;
	 printf("SQL statement: [%s]\n", zSql) and skip;
     prepareAndRun_utf16:=asciiToUtf16le(zSql,RValue);
     prepareAndRun_rc:=sqlite3_prepare16_v2(db,prepareAndRun_utf16,-1,&pstmt,&prepareAndRun_stmtTail,RValue);
     prepTime:=prepTime+prepareAndRun_iElapse;
     output ("sqlite3_prepare16_v2() returns ",prepareAndRun_rc," in ",prepareAndRun_iElapse,"ycles\n") and skip;
     if(prepareAndRun_rc=0) then 
     {
         int prepareAndRun_1_nRow<==0 and skip;
         prepareAndRun_rc:=sqlite3_step(pstmt,RValue) ;
         while((prepareAndRun_rc)=100)
         {
             prepareAndRun_1_nRow:=prepareAndRun_1_nRow+1;
             prepareAndRun_rc:=sqlite3_step(pstmt,RValue) 
         };
         runTime:=runTime+prepareAndRun_iElapse;
         output ("sqlite3_step() returns ",prepareAndRun_rc," after ",prepareAndRun_1_nRow," rows in ",prepareAndRun_iElapse,"ycles\n") and skip;
         prepareAndRun_rc:=sqlite3_finalize(pstmt,RValue);
         finalizeTime:=finalizeTime+prepareAndRun_iElapse;
         output ("sqlite3_finalize() returns ",prepareAndRun_rc," in ",prepareAndRun_iElapse,"ycles\n") and skip
         
     }
     else 
     {
          skip 
     };
     free(prepareAndRun_utf16) and skip
     )
     }; 
  function main ( int RValue )
 {
     frame(verifystat,i,main_argc,main_argv,main_utf16,main_rc,main_nSql,main_zSql,main_i,main_j,main_in,main_iStart,main_iElapse,main_iSetup,main_nStmt,main_nByte,main_2_isComplete,main_2_c,return) and (
     int return<==0 and skip;
     int main_argc<==3 and skip;
     //char *main_argv[]<=={"speedtest16.exe","speedtest16.db","speedtest16.sql"} and skip;
	 char **main_argv<==(char **) malloc( 3*sizeof(char *) ) and skip; //返回一个指向指针类型数据的首地址
	 int i<==0 and skip;
    while(i<3 )
    {
        main_argv[i]<==(char *)malloc(20) and skip;
		i:=i+1
    };
	int verifystat<==0 and skip;
	 while(verifystat<1414176)
	 {
		verifystat:=verifystat+1
	 };
	strcpy(main_argv[0],"speedtest16.exe") and skip;
	strcpy(main_argv[1],"speedtest16.db") and skip;
	strcpy(main_argv[2],"speedtest16.sql") and skip;
     void *main_utf16 and skip;
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
     if(main_argc!=3) then 
     {
         fprintf(stderr,"Usage: %s FILENAME SQL-SCRIPT\nRuns SQL-SCRIPT as UTF16 against a UTF16 database\n",main_argv[0]) and skip
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
     main_utf16:=asciiToUtf16le(main_argv[1],RValue);
     main_rc:=sqlite3_open16(main_utf16,&db,RValue);
     main_iSetup:=main_iElapse;
     output ("sqlite3_open16() returns ",main_rc," in ",main_iElapse,"ycles\n") and skip;
     free(main_utf16) and skip;
     main_j<==0 and main_i<==main_j and skip;
     
     while(main_j<main_nSql)
     {
         if(main_zSql[main_j]=';') then 
         {
             int main_2_isComplete and skip;
             char main_2_c<==main_zSql[main_j+1] and skip;
             main_zSql[main_j+1]:=0;
             main_2_isComplete:=sqlite3_complete(&main_zSql[main_i],RValue);
             main_zSql[main_j+1]:=main_2_c;
             if(main_2_isComplete) then 
             {
                 main_zSql[main_j]:=0;
                 while(main_i<main_j AND isspace((unsigned char)(main_zSql[main_i])))
                 {
                     main_i:=main_i+1
                 };
                 if(main_i<main_j) then 
                 {
                     main_nStmt:=main_nStmt+1;
                     main_nByte:=main_nByte+main_j-main_i;
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
     sqlite3_close(db,RValue) and skip;
     main_iSetup:=main_iSetup+main_iElapse;
     output ("sqlite3_close() returns in ",main_iElapse,"ycles\n") and skip;
     output ("\n") and skip;
     output ("Statements run:       ",main_nStmt,"\n") and skip;
     output ("Bytes of SQL text:    ",main_nByte,"\n") and skip;
     output ("Total prepare time:   ",prepTime,"ycles\n") and skip;
     output ("Total run time:       ",runTime,"ycles\n") and skip;
     output ("Total finalize time:  ",finalizeTime,"ycles\n") and skip;
     output ("Open/Close time:      ",main_iSetup,"ycles\n") and skip;
     output ("Total Time:           ",prepTime+runTime+finalizeTime+main_iSetup,"ycles\n") and skip;
     return<==1 and RValue:=0;
     skip
     )
 };
  main(RValue)
 )
