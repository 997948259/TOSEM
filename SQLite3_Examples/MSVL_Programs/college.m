</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

struct College {
char *cName and 
char *state and 
int enrollment 
};
struct Student {
int sID and 
char *sName and 
float GPA and 
int sizeHS 
};
struct Apply {
int sID and 
char *cName and 
char *major and 
char *decision 
};
 function view_all_callback ( void *data,int argc,char **argv,char **azColName,int RValue )
 {
     frame(view_all_callback_i,return) and ( 
     int return<==0 and skip;
     int view_all_callback_i and skip;
     fprintf(stderr,"%s:\n",(char *)data) and skip;
     view_all_callback_i:=0;
     
     while(view_all_callback_i<argc)
     {
         if(argv[view_all_callback_i]="NULL") then 
         {
             //output (azColName[view_all_callback_i]," = ","NULL",", ",", ") and skip
			 printf("%s = %s, ", azColName[view_all_callback_i], "NULL") and skip
             
         }
         else
         {
             //output (azColName[view_all_callback_i]," = ",argv[view_all_callback_i],", ",", ") and skip
			 printf("%s = %s, ", azColName[view_all_callback_i], argv[view_all_callback_i]) and skip
         };
         view_all_callback_i:=view_all_callback_i+1
         
     };
     output ("\n") and skip;
     return<==1 and skip;
	 RValue:=0;
     skip
     )
     }; 
  function insert_table_callback ( void *NotUsed,int argc,char **argv,char **azColName,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and skip;
	 RValue:=0;
     skip
     )
     }; 
  function create_table_callback ( void *NotUsed,int argc,char **argv,char **azColName,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and skip;
	 RValue:=0;
     skip
     )
     }; 

frame(main_zErrMsg,verifystat,main_rc,main_sql,main_data,main_1_temp$_1,main_college,main_student,main_apply,main_fp,main_line,main_delims,main_result,main_i,return,RValue) and (
int return<==0 and skip;
int RValue<==0 and skip;
char *main_zErrMsg<==0 and skip;
int main_rc and skip;
char *main_sql and skip;
 char *main_data<=="Callback function called" and skip;
 _unlink("DBforCourse.db3") and skip;
 int verifystat<==0 and skip;
while(verifystat<74685400)
{
verifystat:=verifystat+1
};
 main_rc:=sqlite3_open("DBforCourse.db3",&db,RValue);
 if(main_rc) then 
 {
     int main_1_temp$_1 and skip;
     main_1_temp$_1:=sqlite3_errmsg(db,RValue);
     fprintf(stderr,"Can't open database: %s\n",main_1_temp$_1) and skip
     
 }
 else
 {
     fprintf(stderr,"Opened database successfully\n") and skip
 };
 main_sql:="create table College(cName text, state text, enrollment int);";
 main_rc:=sqlite3_exec(db,main_sql,create_table_callback,0,&main_zErrMsg,RValue);
 if(main_rc!=0) then 
 {
	printf("SQL error: %s\n",main_zErrMsg) and skip;
     //output ("SQL error: ",main_zErrMsg,"\n") and skip;
     sqlite3_free(main_zErrMsg,RValue)
     
 }
 else
 {
     fprintf(stdout,"College Table created successfully\n") and skip
 };
 main_sql:="create table Student(sID int, sName text, GPA float, sizeHS int);";
 main_rc:=sqlite3_exec(db,main_sql,create_table_callback,0,&main_zErrMsg,RValue);
 if(main_rc!=0) then 
 {
	printf("SQL error: %s\n",main_zErrMsg) and skip;
     //output ("SQL error: ",main_zErrMsg,"\n") and skip;
     sqlite3_free(main_zErrMsg,RValue)
     
 }
 else
 {
     fprintf(stdout,"Student Table created successfully\n") and skip
 };
 main_sql:="create table Apply(sID int, cName text, major text, decision text);";
 main_rc:=sqlite3_exec(db,main_sql,create_table_callback,0,&main_zErrMsg,RValue);
 if(main_rc!=0) then 
 {
	printf("SQL error: %s\n",main_zErrMsg) and skip;
     //output ("SQL error: ",main_zErrMsg,"\n") and skip;
     sqlite3_free(main_zErrMsg,RValue)
     
 }
 else
 {
     fprintf(stdout,"Apply Table created successfully\n") and skip
 };
 College main_college[4] and skip;
 Student main_student[12] and skip;
 Apply main_apply[19] and skip;
 FILE *main_fp and skip;
 char main_line[100] and skip;
 char main_delims[2]<=="," and skip;
 char *main_result and skip;
 int main_i<==0 and skip;
 main_fp:=fopen("dbcollege.txt","r") ;
 if(main_fp) then 
 {
     while(fgets(main_line,100,main_fp)!=NULL)
     {
         main_result:=strtok(main_line,main_delims,RValue);
         main_college[main_i].cName:=main_result;
         main_result:=strtok(NULL,main_delims,RValue);
         main_college[main_i].state:=main_result;
         main_result:=strtok(NULL,main_delims,RValue);
         main_college[main_i].enrollment:=atoi(main_result);
         main_sql:=sqlite3_mprintf("insert into College(cName, state, enrollment) values('%s', '%s', '%d');",main_college[main_i].cName,main_college[main_i].state,main_college[main_i].enrollment,RValue);
         main_rc:=sqlite3_exec(db,main_sql,insert_table_callback,0,&main_zErrMsg,RValue);
         if(main_rc!=0) then 
         {
             fprintf(stderr,"SQL error: %s\n",main_zErrMsg) and skip;
             sqlite3_free(main_zErrMsg,RValue)
             
         }
         else
         {
             fprintf(stdout,"operations done successfully\n") and skip
         };
         sqlite3_free(main_sql,RValue) and skip;
         main_i:=main_i+1
     };
     fclose(main_fp) and skip
     
 }
 else 
 {
      skip 
 };
 main_result:=NULL;
 main_i:=0;
 main_fp:=fopen("dbstudent.txt","r") ;
 if(main_fp) then 
 {
     while(fgets(main_line,100,main_fp)!=NULL)
     {
         main_result:=strtok(main_line,main_delims,RValue);
         main_student[main_i].sID:=atoi(main_result);
         main_result:=strtok(NULL,main_delims,RValue);
         main_student[main_i].sName:=main_result;
         main_result:=strtok(NULL,main_delims,RValue);
         main_student[main_i].GPA:=atof(main_result);
         main_result:=strtok(NULL,main_delims,RValue);
         main_student[main_i].sizeHS:=atoi(main_result);
         main_sql:=sqlite3_mprintf("insert into Student(sID, sName, GPA, sizeHS) values('%d', '%s', '%f', '%d');",main_student[main_i].sID,main_student[main_i].sName,main_student[main_i].GPA,main_student[main_i].sizeHS,RValue);
         main_rc:=sqlite3_exec(db,main_sql,insert_table_callback,0,&main_zErrMsg,RValue);
         if(main_rc!=0) then 
         {
             fprintf(stderr,"SQL error: %s\n",main_zErrMsg) and skip;
             sqlite3_free(main_zErrMsg,RValue)
             
         }
         else
         {
             fprintf(stdout,"operations done successfully\n") and skip
         };
         sqlite3_free(main_sql,RValue) and skip;
         main_i:=main_i+1
     };
     fclose(main_fp) and skip
     
 }
 else 
 {
      skip 
 };
 main_result:=NULL;
 main_i:=0;
 main_fp:=fopen("dbapply.txt","r") ;
 if(main_fp) then 
 {
     while(fgets(main_line,100,main_fp)!=NULL)
     {
         main_result:=strtok(main_line,main_delims,RValue);
         main_apply[main_i].sID:=atoi(main_result);
         main_result:=strtok(NULL,main_delims,RValue);
         main_apply[main_i].cName:=main_result;
         main_result:=strtok(NULL,main_delims,RValue);
         main_apply[main_i].major:=main_result;
         main_result:=strtok(NULL,main_delims,RValue);
         main_apply[main_i].decision:=main_result;
         main_sql:=sqlite3_mprintf("insert into Apply(sID, cName, major, decision) values('%d', '%s', '%s', '%s');",main_apply[main_i].sID,main_apply[main_i].cName,main_apply[main_i].major,main_apply[main_i].decision,RValue);
         main_rc:=sqlite3_exec(db,main_sql,insert_table_callback,0,&main_zErrMsg,RValue);
         if(main_rc!=0) then 
         {
             fprintf(stderr,"SQL error: %s\n",main_zErrMsg) and skip;
             sqlite3_free(main_zErrMsg,RValue)
             
         }
         else
         {
             fprintf(stdout,"operations done successfully\n") and skip
         };
         sqlite3_free(main_sql,RValue) and skip;
         main_i:=main_i+1
     };
     fclose(main_fp) and skip
     
 }
 else 
 {
      skip 
 };
 printf("aaaa\n") and skip;
 main_sql:="select * from College";
 main_rc:=sqlite3_exec(db,main_sql,view_all_callback,(void *)main_data,&main_zErrMsg,RValue);
 if(main_rc!=0) then 
 {
     fprintf(stderr,"SQL error: %s\n",main_zErrMsg) and skip;
     sqlite3_free(main_zErrMsg,RValue)
     
 }
 else 
 {
      skip 
 };
 main_sql:="select * from Student";
 main_rc:=sqlite3_exec(db,main_sql,view_all_callback,(void *)main_data,&main_zErrMsg,RValue);
 if(main_rc!=0) then 
 {
     fprintf(stderr,"SQL error: %s\n",main_zErrMsg) and skip;
     sqlite3_free(main_zErrMsg,RValue)
     
 }
 else 
 {
      skip 
 };
 main_sql:="select * from Apply";
 main_rc:=sqlite3_exec(db,main_sql,view_all_callback,(void *)main_data,&main_zErrMsg,RValue);
 if(main_rc!=0) then 
 {
     fprintf(stderr,"SQL error: %s\n",main_zErrMsg) and skip;
     sqlite3_free(main_zErrMsg,RValue)
     
 }
 else 
 {
      skip 
 };
 main_sql:="select sID, sName, GPA from Student where GPA > 3.6;";
 main_rc:=sqlite3_exec(db,main_sql,view_all_callback,(void *)main_data,&main_zErrMsg,RValue);
 if(main_rc!=0) then 
 {
     fprintf(stderr,"SQL error: %s\n",main_zErrMsg) and skip;
     sqlite3_free(main_zErrMsg,RValue)
     
 }
 else
 {
     fprintf(stdout,"operations done successfully\n") and skip
 };
 main_sql:="select distinct sName, cName from Student natural join Apply;";
 main_rc:=sqlite3_exec(db,main_sql,view_all_callback,(void *)main_data,&main_zErrMsg,RValue);
 if(main_rc!=0) then 
 {
     fprintf(stderr,"SQL error: %s\n",main_zErrMsg) and skip;
     sqlite3_free(main_zErrMsg,RValue)
     
 }
 else
 {
     fprintf(stdout,"operations done successfully\n") and skip
 };
 main_sql:="select sName, GPA, decision from Student, Apply where Student.sID = Apply.sID and sizeHS < 1000 and major = \"CS\" and cName = \"Stanford\";";
 main_rc:=sqlite3_exec(db,main_sql,view_all_callback,(void *)main_data,&main_zErrMsg,RValue);
 if(main_rc!=0) then 
 {
     fprintf(stderr,"SQL error: %s\n",main_zErrMsg) and skip;
     sqlite3_free(main_zErrMsg,RValue)
     
 }
 else
 {
     fprintf(stdout,"operations done successfully\n") and skip
 };
 main_sql:="select distinct * from Apply, Student, College where Student.sID = Apply.sID and Apply.cName = College.cName order by GPA desc, enrollment;";
 main_rc:=sqlite3_exec(db,main_sql,view_all_callback,(void *)main_data,&main_zErrMsg,RValue);
 if(main_rc!=0) then 
 {
     fprintf(stderr,"SQL error: %s\n",main_zErrMsg) and skip;
     sqlite3_free(main_zErrMsg,RValue)
     
 }
 else
 {
     fprintf(stdout,"operations done successfully\n") and skip
 };
 main_sql:="select sID, sName, GPA*(sizeHS / 1000) as newGPA from Student;";
 main_rc:=sqlite3_exec(db,main_sql,view_all_callback,(void *)main_data,&main_zErrMsg,RValue);
 if(main_rc!=0) then 
 {
     fprintf(stderr,"SQL error: %s\n",main_zErrMsg) and skip;
     sqlite3_free(main_zErrMsg,RValue)
     
 }
 else
 {
     fprintf(stdout,"operations done successfully\n") and skip
 };
 main_sql:="select cName, max(enrollment) from College;";
 main_rc:=sqlite3_exec(db,main_sql,view_all_callback,(void *)main_data,&main_zErrMsg,RValue);
 if(main_rc!=0) then 
 {
     fprintf(stderr,"SQL error: %s\n",main_zErrMsg) and skip;
     sqlite3_free(main_zErrMsg,RValue)
     
 }
 else
 {
     fprintf(stdout,"operations done successfully\n") and skip
 };
 main_sql:="select * from College natural join Student natural join Apply;";
 main_rc:=sqlite3_exec(db,main_sql,view_all_callback,(void *)main_data,&main_zErrMsg,RValue);
 if(main_rc!=0) then 
 {
     fprintf(stderr,"SQL error: %s\n",main_zErrMsg) and skip;
     sqlite3_free(main_zErrMsg,RValue)
     
 }
 else
 {
     fprintf(stdout,"operations done successfully\n") and skip
 };
 main_sql:="select cName from Apply group by cName having count(major) < 5;";
 main_rc:=sqlite3_exec(db,main_sql,view_all_callback,(void *)main_data,&main_zErrMsg,RValue);
 if(main_rc!=0) then 
 {
     fprintf(stderr,"SQL error: %s\n",main_zErrMsg) and skip;
     sqlite3_free(main_zErrMsg,RValue)
     
 }
 else
 {
     fprintf(stdout,"operations done successfully\n") and skip
 };
 sqlite3_close(db,RValue) and skip;
 return<==1 and skip;
 RValue:=0;
 skip
 )