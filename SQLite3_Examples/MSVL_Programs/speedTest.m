</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

frame(err,opTime,sqll,max,min) and (
char *err and skip;
int opTime[4,4] and skip;
char sqll[4000] and skip;
float max<==0,min<==0 and skip;
 function GetRandomIndex ( int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=rand()*3;
     skip
     )
     }; 
  function OpenDataBase ( )
 {
     frame(OpenDataBase_ret,OpenDataBase_1_temp$_1) and ( 
     int OpenDataBase_ret and skip;
     OpenDataBase_ret:=sqlite3_open("./sqlite3-demo.db",&db);
     if(OpenDataBase_ret!=0) then 
     {
         int OpenDataBase_1_temp$_1 and skip;
         OpenDataBase_1_temp$_1:=sqlite3_errmsg(db);
         fprintf(stderr,"Cannot open db: %s\n",OpenDataBase_1_temp$_1) and skip;
         getchar() and skip
         
     }
     else 
     {
          skip 
     }
     )
     }; 
  function GetRec ( void *params,int n_column,char **column_value,char **column_name,int RValue )
 {
     frame(GetRec_buf,GetRec_i,GetRec_temp$_1,return) and ( 
     int return<==0 and skip;
     char GetRec_buf[130] and skip;
     int GetRec_i<==1 and skip;
     
     while(GetRec_i<n_column)
     {
         int GetRec_temp$_1 and skip;
         GetRec_temp$_1:=strlen(column_value[GetRec_i]);
         memcpy(GetRec_buf,column_value[GetRec_i],GetRec_temp$_1) and skip;
         GetRec_i:=GetRec_i+1
         
     };
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function ReadOperation ( int threadIndex )
 {
     frame(ReadOperation_dbHandle,ReadOperation_sqlc,ReadOperation_sqlExp,ReadOperation_ret,ReadOperation_i,ReadOperation_temp$_1,ReadOperation_startTime) and ( 
     char *ReadOperation_sqlc<=="select * from t where id = " and skip;
     char ReadOperation_sqlExp[50]<=={0} and skip;
     int ReadOperation_ret and skip;
     int ReadOperation_i<==0 and skip;
     
     while(ReadOperation_i<2)
     {
         memset(ReadOperation_sqlExp,0,50) and skip;
         int ReadOperation_temp$_1 and skip;
         ReadOperation_temp$_1:=GetRandomIndex(RValue);
         sprintf(ReadOperation_sqlExp,"%s%d",ReadOperation_sqlc,ReadOperation_temp$_1) and skip;
         OpenDataBase();
         ReadOperation_ret:=15;
         int ReadOperation_startTime and skip;
         ReadOperation_startTime:=GetTickCount();
         while(ReadOperation_ret!=0)
         {
             ReadOperation_ret:=sqlite3_exec(db,ReadOperation_sqlExp,GetRec,NULL,&err);
             if(ReadOperation_ret!=0) then 
             {
                 skip
                 
             }
             else 
             {
                  skip 
             }
         };
         opTime[threadIndex,ReadOperation_i]:=GetTickCount()-ReadOperation_startTime;
         sqlite3_free(err) and skip;
         sqlite3_close(db) and skip;
         ReadOperation_i:=ReadOperation_i+1
         
     }
     )
     }; 
  function WriteOperation ( int threadIndex )
 {
     frame(WriteOperation_dbHandle,WriteOperation_sqlc,WriteOperation_sqlExp,WriteOperation_ret,WriteOperation_i,WriteOperation_startTime) and ( 
     char *WriteOperation_sqlc<=="insert into t values() " and skip;
     char WriteOperation_sqlExp[50]<=={0} and skip;
     int WriteOperation_ret<==15 and skip;
     int WriteOperation_i<==0 and skip;
     
     while(WriteOperation_i<2)
     {
         OpenDataBase();
         WriteOperation_ret:=15;
         int WriteOperation_startTime and skip;
         WriteOperation_startTime:=GetTickCount();
         while(WriteOperation_ret!=0)
         {
             WriteOperation_ret:=sqlite3_exec(db,sqll,NULL,NULL,&err);
             if(WriteOperation_ret!=0) then 
             {
                 skip
                 
             }
             else 
             {
                  skip 
             }
         };
         opTime[threadIndex,WriteOperation_i]:=GetTickCount()-WriteOperation_startTime;
         sqlite3_free(err) and skip;
         sqlite3_close(db) and skip;
         WriteOperation_i:=WriteOperation_i+1
         
     }
     )
     }; 
  function RWOperation ( int threadIndex )
 {
     frame(RWOperation_dbHandle,RWOperation_sqlc,RWOperation_sqlExp,RWOperation_ret,RWOperation_i,RWOperation_1_temp$_1,RWOperation_1_startTime,RWOperation_6_startTime,RWOperation_6_temp$_2) and ( 
     char *RWOperation_sqlc<=="select * from t where id = " and skip;
     char RWOperation_sqlExp[50]<=={0} and skip;
     int RWOperation_ret<==15 and skip;
     int RWOperation_i<==0 and skip;
     
     while(RWOperation_i<2)
     {
         if(threadIndex % 2!=0) then 
         {
             memset(RWOperation_sqlExp,0,50) and skip;
             int RWOperation_1_temp$_1 and skip;
             RWOperation_1_temp$_1:=GetRandomIndex(RValue);
             sprintf(RWOperation_sqlExp,"%s%d",RWOperation_sqlc,RWOperation_1_temp$_1) and skip;
             RWOperation_ret:=15;
             int RWOperation_1_startTime and skip;
             RWOperation_1_startTime:=GetTickCount();
             OpenDataBase();
             while(RWOperation_ret!=0)
             {
                 RWOperation_ret:=sqlite3_exec(db,RWOperation_sqlExp,GetRec,NULL,&err);
                 if(RWOperation_ret!=0) then 
                 {
                     skip
                     
                 }
                 else 
                 {
                      skip 
                 }
             };
             opTime[threadIndex,RWOperation_i]:=GetTickCount()-RWOperation_1_startTime;
             sqlite3_free(err) and skip;
             sqlite3_close(db) and skip;
             OpenDataBase();
             RWOperation_ret:=15;
             RWOperation_1_startTime:=GetTickCount();
             while(RWOperation_ret!=0)
             {
                 RWOperation_ret:=sqlite3_exec(db,sqll,NULL,NULL,&err);
                 if(RWOperation_ret!=0) then 
                 {
                     skip
                     
                 }
                 else 
                 {
                      skip 
                 }
             };
             opTime[threadIndex,RWOperation_i+2]:=GetTickCount()-RWOperation_1_startTime;
             sqlite3_close(db) and skip
             
         }
         else
         {
             OpenDataBase();
             RWOperation_ret:=15;
             int RWOperation_6_startTime and skip;
             RWOperation_6_startTime:=GetTickCount();
             while(RWOperation_ret!=0)
             {
                 RWOperation_ret:=sqlite3_exec(db,sqll,NULL,NULL,&err);
                 if(RWOperation_ret!=0) then 
                 {
                     skip
                     
                 }
                 else 
                 {
                      skip 
                 }
             };
             opTime[threadIndex,RWOperation_i+2]:=GetTickCount()-RWOperation_6_startTime;
             sqlite3_close(db) and skip;
             memset(RWOperation_sqlExp,0,50) and skip;
             int RWOperation_6_temp$_2 and skip;
             RWOperation_6_temp$_2:=GetRandomIndex(RValue);
             sprintf(RWOperation_sqlExp,"%s%d",RWOperation_sqlc,RWOperation_6_temp$_2) and skip;
             RWOperation_ret:=15;
             RWOperation_6_startTime:=GetTickCount();
             OpenDataBase();
             while(RWOperation_ret!=0)
             {
                 RWOperation_ret:=sqlite3_exec(db,RWOperation_sqlExp,GetRec,NULL,&err);
                 if(RWOperation_ret!=0) then 
                 {
                     skip
                     
                 }
                 else 
                 {
                      skip 
                 }
             };
             opTime[threadIndex,RWOperation_i]:=GetTickCount()-RWOperation_6_startTime;
             sqlite3_free(err)  and skip;
             sqlite3_close(db) and skip
         };
         RWOperation_i:=RWOperation_i+1
         
     }
     )
     }; 
  function main ( int RValue )
 {
     frame(verifystat,main_dbHandle,main_aversum,main_min1,main_max1,main_sqlr2,main_aaa,main_i,main_len$,main_sum,main_j,main_s,main_aversumx) and (
     float main_aversum<==0.0 and skip;
     OpenDataBase();
     sqlite3_exec(db,"create table t(id int primary key,msg varchar(128),msg1 varchar(128))",NULL,NULL,&err) and skip;
     sqlite3_close(db) and skip;
     float main_min1<==0,main_max1<==0 and skip;
     char main_sqlr2[350] and skip;
     char main_aaa[131]<=={0} and skip;
     main_aaa[0]:='\"';
     memset(main_aaa+1,'q',128) and skip;
     main_aaa[129]:='\"';
     main_aaa[130]:=',';
     memset(main_sqlr2,0,350) and skip;
     int main_i<==0 and skip;
     int verifystat<==0 and skip;
	 while(verifystat<3469336)
	 {
		verifystat:=verifystat+1
	 };
     while(main_i<2)
     {
         strcat(main_sqlr2,main_aaa) and skip;
         main_i:=main_i+1
         
     };
     int main_len$ and skip;
     main_len$:=strlen(main_sqlr2);
     main_sqlr2[261]:=0;
	 //printf("main_sqlr2:%s",main_sqlr2) and skip;
     sprintf(sqll,"insert into t (msg,msg1) values (%s)",main_sqlr2) and skip;
     memset(opTime,0,64) and skip;
     main_i<==0 and skip;
     
     while(main_i<4)
     {
         ReadOperation(main_i);
         main_i:=main_i+1
         
     };
     output ("-------------read start----------------\n") and skip;
     main_i<==0 and skip;
     
     while(main_i<4)
     {
         float main_sum<==0.0 and skip;
         output ("thread ",main_i+1," result :") and skip;
         int main_j<==0 and skip;
         
         while(main_j<2)
         {
             output (" ",(float)opTime[main_i,main_j]/ 1000) and skip;
             main_sum:=main_sum+(float)opTime[main_i,main_j];
             main_j:=main_j+1
             
         };
         max:=( if(max>main_sum) then max else main_sum);
         if(main_i=0) then 
         {
             min:=main_sum
         }
         else 
         {
              skip 
         };
         min:=( if(min<main_sum) then min else main_sum);
         output ("\nsum:",main_sum/ 1000,"\naverage:",main_sum/ 10000,"\n\n") and skip;
         main_aversum:=main_aversum+main_sum;
         main_i:=main_i+1
         
     };
     output ("per thread per operation:",main_aversum/ 160000,"\nmax:",max/ 1000,"\nmin:",min/ 1000,"\n") and skip;
     output ("-------------read end----------------\n\n") and skip;
     memset(opTime,0,64) and skip;
     min:=0;
     max:=0;
     main_aversum:=0.0;
     main_i<==0 and skip;

     while(main_i<4)
     {
         WriteOperation(main_i);
         main_i:=main_i+1
         
     };
     output ("-------------write start----------------\n") and skip;
     main_i<==0 and skip;
     
     while(main_i<4)
     {
         main_sum<==0 and skip;
         output ("thread ",main_i+1," result read :") and skip;
         main_j<==0 and skip;
         
         while(main_j<2)
         {
             output (" ",(float)opTime[main_i,main_j]/ 1000) and skip;
             main_sum:=main_sum+(float)opTime[main_i,main_j];
             main_j:=main_j+1
             
         };
         float main_s<==main_sum/ 2 and skip;
         max:=( if(max>main_sum) then max else main_sum);
         if(main_i=0) then 
         {
             min:=main_sum
         }
         else 
         {
              skip 
         };
         min:=( if(min<main_sum) then min else main_sum);
         output ("\nsum:",main_sum/ 1000,"\naverage:",main_s/ 1000,"\n\n") and skip;
         main_aversum:=main_aversum+main_sum;
         main_i:=main_i+1
         
     };
     output ("per thread per operation:",main_aversum/ 40000,"\nmax:",max/ 1000,"\nmin:",min/ 1000,"\n") and skip;
     output ("-------------write end----------------\n\n") and skip;
     memset(opTime,0,64) and skip;
     min:=0;
     max:=0;
     main_aversum:=0.0;
     main_i<==0 and skip;
     
     while(main_i<4)
     {
         RWOperation(main_i);
         main_i:=main_i+1
         
     };
     float main_aversumx<==0.0 and skip;
     main_aversum:=0.0;
     output ("-------------RW start----------------\n") and skip;
     main_i<==0 and skip;
     
     while(main_i<4)
     {
         main_sum<==0 and skip;
         output ("thread ",main_i+1," result read ") and skip;
         main_j<==0 and skip;
         
         while(main_j<2)
         {
             output (" ",(float)opTime[main_i,main_j]/ 1000) and skip;
             main_sum:=main_sum+(float)opTime[main_i,main_j];
             main_j:=main_j+1
             
         };
         max:=( if(max>main_sum) then max else main_sum);
         if(main_i=0) then 
         {
             min:=main_sum
         }
         else 
         {
              skip 
         };
         min:=( if(min<main_sum) then min else main_sum);
         output ("\nsum:",main_sum/ 1000,"\naverrage:",main_sum/ 10000,"\n\n") and skip;
         main_aversumx:=main_aversumx+main_sum;
         main_sum:=0.0;
         output ("thread ",main_i+1," result write	 ") and skip;
         main_j<==0 and skip;
         
         while(main_j<2)
         {
             output (" ",(float)opTime[main_i,main_j+10]/ 1000) and skip;
             main_sum:=main_sum+(float)opTime[main_i,main_j+2];
             main_j:=main_j+1
             
         };
         main_max1:=( if(main_max1>main_sum) then main_max1 else main_sum);
         if(main_i=0) then 
         {
             main_min1:=main_sum
         }
         else 
         {
              skip 
         };
         main_min1:=( if(main_min1<main_sum) then main_min1 else main_sum);
         output ("\nsum:",main_sum/ 1000,"\naverage:",main_sum/ 10000,"\n\n") and skip;
         main_aversum:=main_aversum+main_sum;
         main_i:=main_i+1
         
     };
     output ("per thread per operation:\nread:",main_aversumx/ 40000,"\nwrite:",main_aversum/ 40000,"\nmax read :",max/ 1000,"\nmin read:",min/ 1000,"\nmax write:",main_max1/ 1000,"\nmin write:",main_min1/ 1000) and skip;
     output ("-------------RW end----------------\n\n") and skip;
     memset(opTime,0,64) and skip
     )
 };
  main(RValue)
 )
