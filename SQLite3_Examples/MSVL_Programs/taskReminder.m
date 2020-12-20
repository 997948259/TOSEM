</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

frame(itxt,itxt_size,db,err_msg) and (
char itxt[10] and skip;
int itxt_size<==0 and skip;
struct task {
int id and 
char *todo 
};
char *err_msg<==0 and skip;
 function callback ( void *flag,int col_len,char **cell_data,char **col_name,int RValue )
 {
     frame(nm_1$,switch$,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     if(!flag) then 
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
         int switch$ and skip;
         break$<==0 and skip;
          switch$<==0 and skip;
          int nm_1$ and skip;
         nm_1$ := * (int *)flag;
         if (nm_1$=1 OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
			 output ("---------------------------------------------------------\n") and skip;
			 output ("Todo:\n") and skip;
			 output ("--   ",cell_data[1],"\n\n") and skip;
			 output ("TASK ID ",cell_data[0],"\n") and skip;
			 output ("---------------------------------------------------------\n") and skip;
             break$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_1$=0 OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             break$<==1 and skip
              
         }
         else
         {
             skip
         };
         return<==1 and RValue:=0;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function intialize_tasks_table ( int RValue )
 {
     frame(intialize_tasks_table_sql,return) and ( 
     int return<==0 and skip;
     char *intialize_tasks_table_sql and skip;
     intialize_tasks_table_sql:="CREATE TABLE IF NOT EXISTS TASKS (ID INTEGER PRIMARY KEY  AUTOINCREMENT   NOT NULL,TODO           TEXT    NOT NULL);";
     return<==1 and RValue:=sqlite3_exec(db,intialize_tasks_table_sql,callback,0,&err_msg,RValue);
     skip
     )
     }; 
  function intialize_db ( char *name,int RValue )
 {
     frame(intialize_db_rc,return) and ( 
     int return<==0 and skip;
     int intialize_db_rc and skip;
     intialize_db_rc:=sqlite3_open(name,&db,RValue);
     if(intialize_db_rc) then 
     {
         return<==1 and RValue:=-1;
         skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         intialize_db_rc:=intialize_tasks_table(RValue);
         if(intialize_db_rc!=0) then 
         {
             sqlite3_free(err_msg,RValue)
         }
         else
         {
             return<==1 and RValue:=-1;
             skip
         };
         if(return=0)  then
         {
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
  function get_all_tasks ( int RValue )
 {
     frame(get_all_tasks_rc,get_all_tasks_sql,get_all_tasks_flag,return) and ( 
     int return<==0 and skip;
     int get_all_tasks_rc and skip;
     char *get_all_tasks_sql and skip;
     get_all_tasks_sql:="SELECT * FROM TASKS;";
     int get_all_tasks_flag<==1 and skip;
     get_all_tasks_rc:=sqlite3_exec(db,get_all_tasks_sql,callback,(void *)&get_all_tasks_flag,&err_msg,RValue);
     if(get_all_tasks_rc!=0) then 
     {
         sqlite3_free(err_msg,RValue)
     }
     else
     {
         return<==1 and RValue:=0;
         skip
     };
     if(return=0)  then
     {
         return<==1 and RValue:=-1;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function get_task ( int id,int RValue )
 {
     frame(get_task_rc,get_task_sql,get_task_flag,return) and ( 
     int return<==0 and skip;
     int get_task_rc and skip;
     char *get_task_sql and skip;
     get_task_sql:=(char *)malloc(40*sizeof(char));
     sprintf(get_task_sql,"SELECT * FROM TASKS WHERE ID=%ld;",id) and skip;
     int get_task_flag<==0 and skip;
     get_task_rc:=sqlite3_exec(db,get_task_sql,callback,(void *)&get_task_flag,&err_msg,RValue);
     if(get_task_rc!=0) then 
     {
         sqlite3_free(err_msg,RValue)
     }
     else
     {
         return<==1 and RValue:=0;
         skip
     };
     if(return=0)  then
     {
         return<==1 and RValue:=-1;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function insert_task ( task tsk,int RValue )
 {
     frame(insert_task_sql,insert_task_temp$_1,insert_task_rc,return) and ( 
     int return<==0 and skip;
     char *insert_task_sql and skip;
     int insert_task_temp$_1 and skip;
     insert_task_temp$_1:=strlen(tsk.todo);
     insert_task_sql:=(char *)malloc((300+insert_task_temp$_1)*sizeof(char));
     int insert_task_rc and skip;
     sprintf(insert_task_sql,"INSERT INTO TASKS (TODO) VALUES (\"%s\");",tsk.todo) and skip;
     insert_task_rc:=sqlite3_exec(db,insert_task_sql,callback,0,&err_msg,RValue);
     if(insert_task_rc!=0) then 
     {
         output ("\n ",err_msg) and skip;
         sqlite3_free(err_msg,RValue) and skip;
         output ("\n ",err_msg) and skip
         
     }
     else
     {
         return<==1 and RValue:=0;
         skip
     };
     if(return=0)  then
     {
         return<==1 and RValue:=-1;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function edit_task ( task tsk,int RValue )
 {
     frame(edit_task_sql,edit_task_rc,edit_task_temp$_1,return) and ( 
     int return<==0 and skip;
     char *edit_task_sql and skip;
     int edit_task_rc and skip;
     int edit_task_temp$_1 and skip;
     edit_task_temp$_1:=strlen(tsk.todo);
     edit_task_sql:=(char *)malloc(1*100+edit_task_temp$_1*sizeof(char));
     sprintf(edit_task_sql,"UPDATE TASKS set TODO =\"%s\" where ID=%ld;",tsk.todo,tsk.id) and skip;
     edit_task_rc:=sqlite3_exec(db,edit_task_sql,callback,0,&err_msg,RValue);
     if(edit_task_rc!=0) then 
     {
         output (err_msg) and skip;
         sqlite3_free(err_msg,RValue)
         
     }
     else
     {
         return<==1 and RValue:=0;
         skip
     };
     if(return=0)  then
     {
         return<==1 and RValue:=-1;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function delete_task ( int id,int RValue )
 {
     frame(delete_task_sql,delete_task_rc,return) and ( 
     int return<==0 and skip;
     char *delete_task_sql and skip;
     int delete_task_rc and skip;
     delete_task_sql:=malloc(100*sizeof(char));
     sprintf(delete_task_sql,"DELETE FROM TASKS WHERE ID = %ld ;",id) and skip;
     delete_task_rc:=sqlite3_exec(db,delete_task_sql,callback,0,&err_msg,RValue);
     if(delete_task_rc!=0) then 
     {
         sqlite3_free(err_msg,RValue)
         
     }
     else
     {
         return<==1 and RValue:=0;
         skip
     };
     if(return=0)  then
     {
         return<==1 and RValue:=-1;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function close_db (  )
 {
     sqlite3_close(db,RValue)
     
 };
 function read_line ( char **text,int RValue )
 {
     frame(read_line_max,read_line_counter,read_line_ch,return) and ( 
     int return<==0 and skip;
     int read_line_max<==100 and skip;
     int read_line_counter<==0 and skip;
     * text:=(char *)realloc(* text,1*read_line_max);
     char read_line_ch and skip;
     //read_line_ch:=getchar() ;
	 read_line_ch:='I';
     while((read_line_ch)!='-')
     {
         * (* text+read_line_counter):=read_line_ch;
         read_line_counter:=read_line_counter+1;
         if(read_line_counter=read_line_max) then 
         {
             read_line_max:=read_line_max*2;
             * text:=(char *)realloc(* text,1*read_line_max)
             
         }
         else 
         {
              skip 
         };
         //read_line_ch:=getchar() 
		 read_line_ch:='-'
     };
     //getchar() and skip;
     * (* text+read_line_counter):=0;
     return<==1 and RValue:=read_line_counter;
     skip
     )
     }; 
  function welcome_screen (  )
 {
     output ("\033[H\033[J") and skip;
     output (" Welcome to Tasker :) \n") and skip
     
 };
 function help_screen (  )
 {
     output ("Use one of the next options \n") and skip;
     output ("    -t to add new task \n") and skip;
     output ("    -d to delete a task by id \n") and skip;
     output ("    -p to print all tasks \n") and skip;
     output ("    -h to show this screen \n") and skip;
     output ("    -q to close tasker \n") and skip
     
 };
 function delete_screen ( int RValue )
 {
     frame(delete_screen_itxt,delete_screen_itxt_size,delete_screen_id,return) and ( 
     int return<==0 and skip;
     output ("Enter id you want to delete\n") and skip;
     output ("->") and skip;
     char delete_screen_itxt[10] and skip;
     int delete_screen_itxt_size<==0 and skip;
     //gets(delete_screen_itxt,RValue) and skip;
	 delete_screen_itxt<=="1" and skip;
     int delete_screen_id and skip;
     if(!sscanf(delete_screen_itxt,"%ld",&delete_screen_id)) then 
     {
         output ("Surely I was waiting for a number\n") and skip;
         return<==1 and RValue:=-1;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         output ("\033[H\033[J") and skip;
         return<==1 and RValue:=delete_screen_id;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function add_task_todo_screen ( char **todo,int RValue )
 {
     frame(add_task_todo_screen_txt_size,return) and ( 
     int return<==0 and skip;
     output ("\033[H\033[J") and skip;
     output ("Make yourself home \n") and skip;
     output ("Write the Todo or Task you want to remember \n") and skip;
     output ("Press ESC then Enter to apply\n") and skip;
     output ("->") and skip;
     int add_task_todo_screen_txt_size and skip;
     add_task_todo_screen_txt_size:=read_line(&* todo,RValue);
     return<==1 and RValue:=add_task_todo_screen_txt_size;
     skip
     )
     }; 
 function create_task ( char *todo,int n,task* RValue )
 {
     frame(create_task_p,return) and ( 
     int return<==0 and skip;
     task *create_task_p and skip;
     create_task_p:=(task *)malloc(sizeof(task));
     create_task_p->todo:=(char *)malloc(n*sizeof(char));
     strcpy(create_task_p->todo,todo) and skip;
     return<==1 and RValue:=create_task_p;
     skip
     )
     }; 
  function main ( int RValue )
 {
     frame(verifystat,loopTime,main_tsk,main_1_3_5_7_8_id,main_1_3_5_7_10_11_todo,main_1_3_5_7_10_11_todo_size,break$,continue) and (
     int continue<==0 and skip;
	 int loopTime<==1 and skip;
     int break$<==0 and skip;
     welcome_screen();
     help_screen();
     intialize_db("tasker.db",RValue);
     intialize_tasks_table(RValue);
     task *main_tsk and skip;
     main_tsk:=(task *)malloc(sizeof(task));
     break$<==0 and skip;
	  int verifystat<==0 and skip;
	 while(verifystat<13464110)
	 {
		verifystat:=verifystat+1
	 };
     while( break$=0 AND  1)
     {
         continue<==0 and skip;
         output ("-> ") and skip;
         //gets(itxt,RValue) and skip;
		 if(loopTime=1)then
		 {
			itxt<=="-t" and skip
		 }
		 else 
		 {
			 if(loopTime=2)then
			 {
				itxt<=="-d" and skip
			 }
			 else 
			 {
				if(loopTime=3)then
				{
					itxt<=="-p" and skip
				}
				else 
				{
					itxt<=="-q" and skip
				}
			 }
		 };
		 loopTime:=loopTime+1;
         if(!strncmp(itxt,"-q",2,RValue)) then 
         {
             break$<==1 and skip
          }
         else
         {
             if(!strncmp(itxt,"-h",2,RValue)) then 
             {
                 help_screen()
             }
             else
             {
                 if(!strncmp(itxt,"-p",2,RValue)) then 
                 {
                     get_all_tasks(RValue)
                 }
                 else
                 {
                     if(!strncmp(itxt,"-d",2,RValue)) then 
                     {
                         int main_1_3_5_7_8_id and skip;
                         main_1_3_5_7_8_id:=delete_screen(RValue);
                         if(main_1_3_5_7_8_id=-1) then 
                         {
                             continue<==1 and skip
                          }
                         else 
                         {
                              skip 
                         };
                         if(continue=0)   then 
                         {
                             delete_task(main_1_3_5_7_8_id,RValue);
                             get_all_tasks(RValue)
                         }
                         else
                         {
                             skip
                         }
                     }
                     else
                     {
                         if(!strncmp(itxt,"-t",2,RValue)) then 
                         {
                             char *main_1_3_5_7_10_11_todo<==NULL and skip;
                             int main_1_3_5_7_10_11_todo_size and skip;
                             main_1_3_5_7_10_11_todo_size:=add_task_todo_screen(&main_1_3_5_7_10_11_todo,RValue);
                             main_tsk:=create_task(main_1_3_5_7_10_11_todo,main_1_3_5_7_10_11_todo_size,RValue);
                             insert_task(* main_tsk,RValue);
                             output ("Added :) \n") and skip
                             
                         }
                         else 
                         {
                              skip 
                         }
                     }
                 }
             }
         }
     };
     break$<==0 and skip;
     continue<==0 and skip;
     free(main_tsk) and skip;
     output ("Cya soon :)\n") and skip
     )
 };
  main(RValue)
 )
