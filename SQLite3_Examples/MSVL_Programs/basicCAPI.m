</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

frame(db_name) and (
char *db_name<==NULL and skip;
 function set_db_name ( char *v_db_name,int RValue )
 {
     frame(set_db_name_size,set_db_name_temp$_1,set_db_name_temp$_2,return) and ( 
     int return<==0 and skip;
     int set_db_name_size<==sizeof((v_db_name)) and skip;
     set_db_name_size:=strlen(v_db_name);
     int set_db_name_temp$_1 and skip;
     set_db_name_temp$_1:=strlen(v_db_name);
     db_name:=(char *)malloc(set_db_name_temp$_1+1);
     if(db_name=NULL) then 
     {
         fprintf(stdout,"set_db_name - malloc failed.") and skip;
         return<==1 and RValue:=-1;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         int set_db_name_temp$_2 and skip;
         set_db_name_temp$_2:=strlen(v_db_name);
         memcpy(db_name,v_db_name,set_db_name_temp$_2+1) and skip;
         return<==1 and RValue:=0;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function get_db_name ( char* RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=db_name;
     skip
     )
     }; 
  function variable_free ( int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     free(db_name) and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function db_connection ( int RValue )
 {
     frame(db_connection_connection_result,db_connection_1_temp$_1,return) and ( 
     int return<==0 and skip;
     int db_connection_connection_result and skip;
     db_connection_connection_result:=sqlite3_open(db_name,&db,RValue);
     if(db_connection_connection_result!=0) then 
     {
         int db_connection_1_temp$_1 and skip;
         db_connection_1_temp$_1:=sqlite3_errmsg(db,RValue);
         fprintf(stdout,"Can't open database: %s\n",db_connection_1_temp$_1) and skip;
         return<==1 and RValue:=-1;
         skip
     }
     else
     {
         fprintf(stdout,"Opened database successfully\n") and skip;
         return<==1 and RValue:=0;
         skip
     }
     )
     }; 
  function sqlite3_query_execute ( char *sql_query,int RValue )
 {
     frame(sqlite3_query_execute_result,sqlite3_query_execute_error_message,nm_1$,switch$,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     int sqlite3_query_execute_result and skip;
     char *sqlite3_query_execute_error_message<==NULL and skip;
     fprintf(stdout,"%s\n",sql_query) and skip;
     db_connection(RValue);
     sqlite3_query_execute_result:=sqlite3_exec(db,sql_query,0,0,&sqlite3_query_execute_error_message,RValue);
     sqlite3_close(db,RValue) and skip;
     while( return=0 AND  true)
     {
         int switch$ and skip;
         break$<==0 and skip;
          switch$<==0 and skip;
          int nm_1$ and skip;
         nm_1$ := sqlite3_query_execute_result;
         if (nm_1$=5 OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             fprintf(stdout,"busy, wait 0.1 seconds\n") and skip;
             Sleep(1) and skip;
             db_connection(RValue);
             sqlite3_query_execute_result:=sqlite3_exec(db,sql_query,0,0,&sqlite3_query_execute_error_message,RValue);
             sqlite3_close(db,RValue) and skip;
             break$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_1$=1 OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             fprintf(stdout,"SQL ERROR: %s \n",sqlite3_query_execute_error_message) and skip;
             sqlite3_free(sql_query,RValue) and skip;
             sqlite3_free(sqlite3_query_execute_error_message,RValue) and skip;
             return<==1 and RValue:=-1;
             skip
             
         }
         else
         {
             skip
         };
         if (nm_1$=0 OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             sqlite3_free(sql_query,RValue) and skip;
             return<==1 and RValue:=0;
             skip
             
         }
         else
         {
             skip
         };
         if (nm_1$=13 OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             break$<==1 and skip
              
         }
         else
         {
             skip
         }
     };
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function sqlite3_query_execute_delete_table ( char *table_name,int id,int RValue )
 {
     frame(sqlite3_query_execute_delete_table_result,sqlite3_query_execute_delete_table_error_message,sqlite3_query_execute_delete_table_sql_query,nm_2$,switch$,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     int sqlite3_query_execute_delete_table_result and skip;
     char *sqlite3_query_execute_delete_table_error_message<==NULL and skip;
     char *sqlite3_query_execute_delete_table_sql_query and skip;
     sqlite3_query_execute_delete_table_sql_query:=sqlite3_mprintf("DELETE FROM %q WHERE id=%d",table_name,id,RValue);
     fprintf(stdout,"%s\n",sqlite3_query_execute_delete_table_sql_query) and skip;
     db_connection(RValue);
     sqlite3_query_execute_delete_table_result:=sqlite3_exec(db,sqlite3_query_execute_delete_table_sql_query,0,0,&sqlite3_query_execute_delete_table_error_message,RValue);
     sqlite3_close(db,RValue) and skip;
     while( return=0 AND  true)
     {
         int switch$ and skip;
         break$<==0 and skip;
          switch$<==0 and skip;
          int nm_2$ and skip;
         nm_2$ := sqlite3_query_execute_delete_table_result;
         if (nm_2$=5 OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             fprintf(stdout,"busy, wait 0.1 seconds\n") and skip;
             Sleep(1) and skip;
             db_connection(RValue);
             sqlite3_query_execute_delete_table_result:=sqlite3_exec(db,sqlite3_query_execute_delete_table_sql_query,0,0,&sqlite3_query_execute_delete_table_error_message,RValue);
             sqlite3_close(db,RValue) and skip;
             break$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_2$=1 OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             fprintf(stdout,"SQL ERROR : %s\n",sqlite3_query_execute_delete_table_error_message) and skip;
             sqlite3_free(sqlite3_query_execute_delete_table_sql_query,RValue) and skip;
             sqlite3_free(sqlite3_query_execute_delete_table_error_message,RValue) and skip;
             return<==1 and RValue:=-1;
             skip
             
         }
         else
         {
             skip
         };
         if (nm_2$=0 OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             sqlite3_free(sqlite3_query_execute_delete_table_sql_query,RValue) and skip;
             return<==1 and RValue:=0;
             skip
             
         }
         else
         {
             skip
         };
         if (nm_2$=13 OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             break$<==1 and skip
              
         }
         else
         {
             skip
         }
     };
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function main ( int RValue )
 {
     frame(main_sql_query_test_create_table,verifystat,main_sql_query_test_update,return) and (
     int return<==0 and skip;
     set_db_name("test.db",RValue);
     _unlink("test.db") and skip;
	 int verifystat<==0 and skip;
	 while(verifystat<630000)
	 {
		verifystat:=verifystat+1
	 };
     char *main_sql_query_test_create_table and skip;
     main_sql_query_test_create_table:=sqlite3_mprintf("CREATE TABLE test(ID INT,NAME TEXT)",RValue);
     char *main_sql_query_test_update and skip;
     main_sql_query_test_update:=sqlite3_mprintf("UPDATE test SET id=1",RValue);
     if(sqlite3_query_execute(main_sql_query_test_create_table,RValue)) then 
     {
         fprintf(stdout,"Can't execute query\n") and skip;
         return<==1 and RValue:=-1;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         if(sqlite3_query_execute(main_sql_query_test_update,RValue)) then 
         {
             fprintf(stdout,"Can't execute query\n") and skip;
             return<==1 and RValue:=-1;
             skip
             
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             if(sqlite3_query_execute_delete_table("test",1,RValue)) then 
             {
                 fprintf(stdout,"Can't execute delete table query\n") and skip;
                 return<==1 and RValue:=-1;
                 skip
                 
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 variable_free(RValue);
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
     )
 };
  main(RValue)
 )