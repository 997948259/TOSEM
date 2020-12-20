</
define p:sqlite3_mprintf_call=1;
define q:sqlite3_free_call=1;
alw(p->som(q))
/>
frame(db,db1,nRowPerTrans,pstmt) and (
 function showHelp ( char *zArgv0 )
 {
     output ("\nUsage: ",zArgv0," SWITCHES... DB\n\n  This program opens the database named on the command line and attempts to\n  create an FTS table named \"fts\" with a single column. If successful, it\n  recursively traverses the directory named by the -dir option and inserts\n  the contents of each file into the fts table. All files are assumed to\n  contain UTF-8 text.\n\nSwitches are:\n  -fts [345]       FTS version to use (default=5)\n  -idx [01]        Create a mapping from filename to rowid (default=0)\n  -dir <path>      Root of directory tree to load data from (default=.)\n  -trans <integer> Number of inserts per transaction (default=1)\n") and skip
     
 };
 function sqlite_error_out ( char *zText )
 {
     frame(sqlite_error_out_temp$_1) and ( 
     int sqlite_error_out_temp$_1 and skip;
     sqlite_error_out_temp$_1:=sqlite3_errmsg(db,RValue);
     fprintf(stderr,"%s: %s\n",zText,sqlite_error_out_temp$_1) and skip
     )
     }; 
      int nRowPerTrans and skip;
 function visit_file ( char *zPath )
 {
     frame(visit_file_rc,tmp) and ( 
     int visit_file_rc and skip;
	 int tmp<==0 and skip;
     sqlite3_bind_text(pstmt,1,zPath,-1,0,RValue) and skip;
     sqlite3_step(pstmt,RValue) and skip;
     visit_file_rc:=sqlite3_reset(pstmt,RValue);
     if(visit_file_rc!=0) then 
     {
         sqlite_error_out("insert")
     }
     else
     {
		tmp<==sqlite3_last_insert_rowid(db,RValue) % nRowPerTrans and skip;
         if(nRowPerTrans>0 AND tmp=0) then 
         {
             sqlite3_exec(db,"COMMIT ; BEGIN",0,0,0,RValue) and skip
             
         }
         else 
         {
              skip 
         }
     }
     )
     }; 
  function main ( int RValue )
 {
     frame(verifystat,i,main_argc,main_argv,main_iFts,main_bMap,main_zDir,main_i,main_rc,main_nRowPerTrans,main_zSql,main_nCmd,main_aCmd,main_zOpt,main_zArg,return) and (
     int return<==0 and skip;
     int main_argc<==6 and skip;
     //char *main_argv[]<=={"loadfts.exe","-fts","3","-dir","./loadfts","loadfts.db"} and skip;
	 //printf("main_zOpt:%s",main_argv[0]) and skip;
	char **main_argv<==(char **) malloc( 6*sizeof(char *) ) and skip; //返回一个指向指针类型数据的首地址
	 int i<==0 and skip;
    while(i<6 )
    {
        main_argv[i]<==(char *)malloc(10) and skip;
		i:=i+1
    };
	int verifystat<==0 and skip;
	 while(verifystat<5509518)
	 {
		verifystat:=verifystat+1
	 };
	strcpy(main_argv[0],"loadfts.exe") and skip;
	strcpy(main_argv[1],"-fts") and skip;
	strcpy(main_argv[2],"3") and skip;
	strcpy(main_argv[3],"-dir") and skip;
	strcpy(main_argv[4],"./loadfts") and skip;
	strcpy(main_argv[5],"loadfts.db") and skip;
     int main_iFts<==5 and skip;
     int main_bMap<==0 and skip;
     char *main_zDir<=="." and skip;
     int main_i<==0 and skip;
     int main_rc and skip;
     int main_nRowPerTrans<==0 and skip;
     char *main_zSql and skip;
     int main_nCmd<==0 and skip;
     char **main_aCmd<==0 and skip;
     if(main_argc % 2) then 
     {
		
         showHelp(main_argv[0])
     }
     else 
     {
          skip 
     };
     main_i:=1;
     
     while(main_i<(main_argc-1))
     {
         char *main_zOpt<==main_argv[main_i] and skip;
         char *main_zArg<==main_argv[main_i+1] and skip;
         if(strcmp(main_zOpt,"-fts")=0) then 
         {
			
             main_iFts:=atoi(main_zArg);
             if(main_iFts!=3 AND main_iFts!=4 AND main_iFts!=5) then 
             {
                 showHelp(main_argv[0])
             }
             else 
             {
                  skip 
             }
             
         }
         else
         {
             if(strcmp(main_zOpt,"-trans")=0) then 
             {
                 main_nRowPerTrans:=atoi(main_zArg)
             }
             else
             {
                 if(strcmp(main_zOpt,"-idx")=0) then 
                 {
                     main_bMap:=atoi(main_zArg);
                     if(main_bMap!=0 AND main_bMap!=1) then 
                     {
                         showHelp(main_argv[0])
                     }
                     else 
                     {
                          skip 
                     }
                 }
                 else
                 {
                     if(strcmp(main_zOpt,"-dir")=0) then 
                     {
                         main_zDir:=main_zArg
                     }
                     else
                     {
                         if(strcmp(main_zOpt,"-special")=0) then 
                         {
                             main_nCmd:=main_nCmd+1;
                             main_aCmd:=sqlite3_realloc(main_aCmd,4*main_nCmd,RValue);
                             main_aCmd[main_nCmd-1]:=main_zArg
                         }
                         else
                         {
							printf("cccc\n") and skip;
                             showHelp(main_argv[0])
                         }
                     }
                 }
             }
         };
         main_i:=main_i+2
         
     };
	 
     remove(main_argv[main_argc-1]) and skip;
     main_rc:=sqlite3_open(main_argv[main_argc-1],&db,RValue);
     if(main_rc!=0) then 
     {
         sqlite_error_out("sqlite3_open()")
     }
     else 
     {
          skip 
     };
     //main_rc:=sqlite3_create_function(db,"readtext",1,1,0,readfileFunc,0,0,RValue);
	   main_rc := my_sqlite3_create_function();
     if(main_rc!=0) then 
     {
         sqlite_error_out("sqlite3_create_function()")
     }
     else 
     {
          skip 
     };
     main_zSql:=sqlite3_mprintf("CREATE VIRTUAL TABLE fts USING fts%d(content)",main_iFts,RValue);
     main_rc:=sqlite3_exec(db,main_zSql,0,0,0,RValue);
     if(main_rc!=0) then 
     {
         sqlite_error_out("sqlite3_exec(1)")
     }
     else 
     {
          skip 
     };
     sqlite3_free(main_zSql,RValue) and skip;
     main_i:=0;
     
     while(main_i<main_nCmd)
     {
         main_zSql:=sqlite3_mprintf("INSERT INTO fts(fts) VALUES(%Q)",main_aCmd[main_i],RValue);
         main_rc:=sqlite3_exec(db,main_zSql,0,0,0,RValue);
         if(main_rc!=0) then 
         {
             sqlite_error_out("sqlite3_exec(1)")
         }
         else 
         {
              skip 
         };
         sqlite3_free(main_zSql,RValue) and skip;
         main_i:=main_i+1
         
     };
     db1:=db;
     main_rc:=sqlite3_prepare_v2(db,"INSERT INTO fts VALUES(readtext(?))",-1,&pstmt,0,RValue);
     if(main_rc!=0) then 
     {
         sqlite_error_out("sqlite3_prepare_v2(1)")
     }
     else 
     {
          skip 
     };
     if(main_nRowPerTrans>0) then 
     {
         sqlite3_exec(db,"BEGIN",0,0,0,RValue) and skip
     }
     else 
     {
          skip 
     };
     traverse(main_zDir,visit_file,RValue) and skip;
     if(main_nRowPerTrans>0) then 
     {
         sqlite3_exec(db,"COMMIT",0,0,0,RValue) and skip
     }
     else 
     {
          skip 
     };
     if(main_rc!=0) then 
     {
         sqlite_error_out("sqlite3_exec(1)")
     }
     else 
     {
          skip 
     };
     sqlite3_finalize(pstmt,RValue) and skip;
     sqlite3_close(db,RValue) and skip;
     sqlite3_free(main_aCmd,RValue) and skip;
     return<==1 and RValue:=0;
     skip
     )
 };
  main(RValue)
 )