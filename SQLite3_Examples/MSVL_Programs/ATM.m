</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

frame(clientArgs,argCnt,serverMsg,msgBuf,msg_length,bytes_sent,failedAttempts,threadCount,created,totalMoney,sqlError,rc,sargc,sargs,colNames,logged,sock_listen,csock) and (
char clientArgs[16,128] and skip;
int argCnt and skip;
char serverMsg[4096] and skip;
char msgBuf[4096] and skip;
int msg_length,bytes_sent and skip;
int failedAttempts<==0 and skip;
int threadCount<==5 and skip;
int created<==0 and skip;
int totalMoney<==10000 and skip;
char *sqlError<==0 and skip;
int rc and skip;
int sargc and skip;
char sargs[128,128] and skip;
char colNames[128,128] and skip;
int logged<==1 and skip;
int sock_listen and skip;
int csock and skip;
 function callback ( void *NotUsed,int argc,char **argv,char **azColName,int RValue )
 {
     frame(callback_i,return) and ( 
     int return<==0 and skip;
     int callback_i and skip;
     sargc:=argc;
     callback_i:=0;
     
     while(callback_i<argc)
     {
         if(argv[callback_i]=NULL) then 
         {
             output (azColName[callback_i]," = ","NULL","\n","\n") and skip
             
         }
         else
         {
             output (azColName[callback_i]," = ",argv[callback_i],"\n","\n") and skip
         };
         strcpy(sargs[callback_i],argv[callback_i]) and skip;
         strcpy(colNames[callback_i],azColName[callback_i]) and skip;
         callback_i:=callback_i+1
         
     };
     output ("~~~~~~~~~~~~~~~~DB ENTRY~~~~~~~~~~~~~~~~\n") and skip;
     return<==1 and skip;
	 RValue:=0;
     skip
     )
     }; 
  function main ( int RValue )
 {
     frame(verifystat,main_status,main_sock_tmp,main_sql,main_sock_aClient,main_addr_size,main_reuseaddr,return) and ( 
     int return<==0 and skip;
     int main_status,*main_sock_tmp and skip;
     char *main_sql and skip;
     int main_sock_aClient and skip;
     int main_addr_size and skip;
     int main_reuseaddr<==1 and skip;
	 int verifystat<==0 and skip;
	 while(verifystat<35246854)
	 {
		verifystat:=verifystat+1
	 };
     if(!initDB(RValue)) then 
     {
         output ("Error! Failed to initialize the database!\n") and skip
         
     }
     else 
     {
          skip 
     };
     if(!created) then 
     {
         main_sql:="CREATE TABLE ATM(FIRST TEXT PRIMARY KEY NOT NULL,LAST TEXT NOT NULL,PIN INT NOT NULL,DL INT NOT NULL,SSN INT NOT NULL,EMAIL CHAR(40),BALANCE REAL,TRANSACTIONS INT NOT NULL );";
         runSQL(main_sql,RValue)
         
     }
     else 
     {
          skip 
     };
     output ("Socket established! Listening for a client...\n") and skip;
     //while(1)
	 if(1) then
     {
         if(threadCount<1) then 
         {
             Sleep(1) and skip
         }
         else 
         {
              skip 
         };
         //main_sock_aClient:=accept(sock_listen,NULL,NULL,RValue);
		 main_sock_aClient:=MyAccept(listenfd);
         if(main_sock_aClient=-1) then 
         {
             output ("Error! Client not accepted!\n") and skip
             
         }
         else 
         {
              skip 
         };
         main_sock_tmp:=malloc(1);
         * main_sock_tmp:=main_sock_aClient;
         threadCount:=threadCount-1;
         atm_client_handler((void *)main_sock_tmp,RValue)
         /*if(main_status!=0) then 
         {
             perror("Thread creation failed") and skip;
             free(main_sock_tmp) and skip
             
         }
         else 
         {
              skip 
         }*/
     };
     sqlite3_close(db,RValue) and skip;
     return<==1 and skip;
	 RValue:=0;
     skip
     )
     }; 
  function atm_client_handler ( void *client_desc )
 {
     frame(atm_client_handler_msg_size,atm_client_handler_i,atm_client_handler_buff,atm_client_handler_tmp,atm_client_handler_temp) and ( 
     int atm_client_handler_msg_size,atm_client_handler_i and skip;
     char atm_client_handler_buff[4096] and skip;
     char *atm_client_handler_tmp<==NULL and skip;
     char atm_client_handler_temp[4096] and skip;
     csock:=* (int *)client_desc;
     output ("Client handler entered...\n") and skip;
     atm_client_handler_msg_size:=recv(csock,atm_client_handler_buff,4096,0,RValue) ;
     while((atm_client_handler_msg_size)>0)
     {
         atm_client_handler_buff[atm_client_handler_msg_size]:=0;
         output ("Received message '",atm_client_handler_buff,"'\n") and skip;
         atm_client_handler_i:=0;
         atm_client_handler_tmp:=strtok(atm_client_handler_buff," ",RValue);
         while(atm_client_handler_tmp!=NULL)
         {
             strcpy(clientArgs[atm_client_handler_i],atm_client_handler_tmp) and skip;
             atm_client_handler_tmp:=strtok(NULL," ",RValue);
             atm_client_handler_i:=atm_client_handler_i+1
         };
         argCnt:=atm_client_handler_i;
         databaseDriver(RValue);
         atm_client_handler_msg_size:=recv(csock,atm_client_handler_buff,4096,0,RValue) 
     };
     logged:=0;
     output ("Exiting the client handler...\n") and skip;
     threadCount:=threadCount+1
     )
     }; 
  function sendMsg (  )
 {
     frame(return) and ( 
     int return<==0 and skip;
     msg_length:=strlen(serverMsg);
     if(msg_length>4096) then 
     {
         output ("Error! Message length too long!\n") and skip;
          return<==1 and skip
         
     }
     else
     {
         strcpy(msgBuf,serverMsg) and skip;
         bytes_sent:=send(csock,msgBuf,msg_length,0,RValue)
     };
     if(return=0)  then
     {
         memset(serverMsg,0,4096) and skip;
         memset(msgBuf,0,4096) and skip
     }
     else
     {
         skip
     }
     )
     }; 
  function initDB ( int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     rc:=sqlite3_open("atm.db",&db,RValue);
     if(rc) then 
     {
         output ("Cannot open the database: ",sqlite3_errmsg(db,RValue),"\n") and skip;
         return<==1 and skip;
		 RValue:=0;
         skip
     }
     else
     {
         output ("The database opened successfully!\n") and skip;
         sqlite3_close(db,RValue) and skip;
         return<==1 and skip;
		 RValue:=1;
         skip
     }
     )
     }; 
  function runSQL ( char *sql )
 {
     frame(return) and ( 
     int return<==0 and skip;
     rc:=sqlite3_open("atm.db",&db,RValue);
     if(rc) then 
     {
         output ("Cannot open the database: ",sqlite3_errmsg(db,RValue),"\n") and skip;
          return<==1 and skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         rc:=sqlite3_exec(db,sql,callback,0,&sqlError);
         if(rc!=0) then 
         {
			//printf("SQL error: %s",sqlError) and skip;
             //output ("SQL error: ",sqlError,"\n") and skip;
             sqlite3_free(sqlError,RValue) and skip
             
         }
         else 
         {
              skip 
         };
         sqlite3_close(db,RValue) and skip
     }
     else
     {
         skip
     }
     )
     }; 
  function databaseDriver (  )
 {
     if(strcmp(clientArgs[0],"101")=0) then 
     {
         CreateAccount(RValue)
     }
     else
     {
         if(strcmp(clientArgs[0],"201")=0) then 
         {
             Authentication(RValue)
         }
         else
         {
             if(strcmp(clientArgs[0],"301")=0) then 
             {
                 Deposit(RValue)
             }
             else
             {
                 if(strcmp(clientArgs[0],"302")=0) then 
                 {
                     MachineFull(RValue)
                 }
                 else
                 {
                     if(strcmp(clientArgs[0],"401")=0) then 
                     {
                         Withdraw(RValue)
                     }
                     else
                     {
                         if(strcmp(clientArgs[0],"402")=0) then 
                         {
                             MachineEmpty(RValue)
                         }
                         else
                         {
                             if(strcmp(clientArgs[0],"501")=0) then 
                             {
                                 askBalance(RValue)
                             }
                             else
                             {
                                 if(strcmp(clientArgs[0],"601")=0) then 
                                 {
                                     showTransactions(RValue)
                                 }
                                 else
                                 {
                                     if(strcmp(clientArgs[0],"701")=0) then 
                                     {
                                         requestStamps(RValue)
                                     }
                                     else
                                     {
                                         if(strcmp(clientArgs[0],"702")=0) then 
                                         {
                                             stampsEmpty(RValue)
                                         }
                                         else
                                         {
                                             if(strcmp(clientArgs[0],"801")=0) then 
                                             {
                                                 logout(RValue)
                                             }
                                             else
                                             {
                                                 output ("Incorrect command received from client.\n") and skip
                                             }
                                         }
                                     }
                                 }
                             }
                         }
                     }
                 }
             }
         }
     }
     
 };
 function CreateAccount (  )
 {
     frame(CreateAccount_temp) and ( 
     char CreateAccount_temp[4096] and skip;
     sprintf(CreateAccount_temp,"SELECT * FROM ATM where FIRST='%s'",clientArgs[1]) and skip;
     runSQL(CreateAccount_temp);
     if(strcmp(sargs[0],clientArgs[1])!=0) then 
     {
         output ("Creating a new account for ",clientArgs[1],"!\n") and skip;
         sprintf(CreateAccount_temp,"INSERT INTO ATM (FIRST,LAST,PIN,DL,SSN,EMAIL,BALANCE,TRANSACTIONS) VALUES ('%s', '%s', %s, %s, %s, '%s', 100.00, 5 );",clientArgs[1],clientArgs[2],clientArgs[3],clientArgs[4],clientArgs[5],clientArgs[6]) and skip;
         runSQL(CreateAccount_temp);
         logged:=1;
         strcpy(serverMsg,"104") and skip
         
     }
     else
     {
         output ("That account already exists!\n") and skip;
         strcpy(serverMsg,"105") and skip;
         logged:=0
     };
     sendMsg()
     )
     }; 
  function Authentication (  )
 {
     frame(Authentication_temp,return) and ( 
     int return<==0 and skip;
     char Authentication_temp[4096] and skip;
     if(failedAttempts>=10) then 
     {
         strcpy(serverMsg,"204") and skip;
         failedAttempts:=0;
         sendMsg();
          return<==1 and skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         sprintf(Authentication_temp,"SELECT * FROM ATM where FIRST='%s'",clientArgs[1]) and skip;
		 printf("Authentication_temp:%s",Authentication_temp) and skip;
         runSQL(Authentication_temp);
		 printf("aaaa") and skip;
         if(strcmp(sargs[0],clientArgs[1])=0 AND strcmp(sargs[2],clientArgs[2])=0) then 
         {
             strcpy(serverMsg,"205") and skip;
             logged:=1;
             failedAttempts:=0
             
         }
         else
         {
             strcpy(serverMsg,"203") and skip;
             logged:=0;
             failedAttempts:=failedAttempts+1
         };
         sendMsg()
     }
     else
     {
         skip
     }
     )
     }; 
  function Deposit (  )
 {
     frame(Deposit_temp,Deposit_balance,return) and ( 
     int return<==0 and skip;
     char Deposit_temp[4096] and skip;
     int Deposit_balance and skip;
     if(!logged) then 
     {
          return<==1 and skip
     }
     else
     {
         Deposit_balance:=atoi(sargs[6]);
         Deposit_balance:=Deposit_balance+atoi(clientArgs[1]);
         output ("Updated balance for ",sargs[0]," = ",Deposit_balance,"\n") and skip;
         sprintf(Deposit_temp,"UPDATE ATM set BALANCE=%d where FIRST='%s'",Deposit_balance,sargs[0]) and skip;
         runSQL(Deposit_temp);
         sprintf(Deposit_temp,"SELECT * FROM ATM where FIRST='%s'",sargs[0]) and skip;
         runSQL(Deposit_temp);
         strcpy(serverMsg,"303 ") and skip;
         strcat(serverMsg,sargs[6]) and skip;
         sendMsg()
     }
     )
     }; 
  function MachineFull (  )
 {
     frame(return) and ( 
     int return<==0 and skip;
     if(!logged) then 
     {
          return<==1 and skip
     }
     else
     {
         strcpy(serverMsg,"305 ") and skip;
         strcat(serverMsg,sargs[6]) and skip
     };
     if(return=0)  then
     {
         sendMsg()
     }
     else
     {
         skip
     }
     )
     }; 
  function Withdraw (  )
 {
     frame(Withdraw_temp,Withdraw_value,Withdraw_balance,return) and ( 
     int return<==0 and skip;
     char Withdraw_temp[4096] and skip;
     int Withdraw_value,Withdraw_balance and skip;
     if(!logged) then 
     {
          return<==1 and skip
     }
     else
     {
         Withdraw_value:=atoi(clientArgs[1]);
         Withdraw_balance:=atoi(sargs[6]);
         output (Withdraw_balance,", ",Withdraw_value,"\n","\n") and skip;
         if((Withdraw_balance-Withdraw_value)<0) then 
         {
             output ("Insufficient funds!\n") and skip;
             strcpy(serverMsg,"404") and skip;
             sendMsg();
              return<==1 and skip
         }
         else
         {
             Withdraw_balance:=Withdraw_balance-Withdraw_value;
             sprintf(Withdraw_temp,"UPDATE ATM set BALANCE=%d where FIRST='%s'",Withdraw_balance,sargs[0]) and skip;
             runSQL(Withdraw_temp);
             sprintf(Withdraw_temp,"SELECT * FROM ATM where FIRST='%s'",sargs[0]) and skip;
             runSQL(Withdraw_temp);
             strcpy(serverMsg,"403 ") and skip;
             strcat(serverMsg,sargs[6]) and skip;
             sendMsg()
         }
     }
     )
     }; 
  function MachineEmpty (  )
 {
     frame(return) and ( 
     int return<==0 and skip;
     if(!logged) then 
     {
          return<==1 and skip
     }
     else
     {
         strcpy(serverMsg,"405") and skip;
         sendMsg()
     }
     )
     }; 
  function askBalance (  )
 {
     frame(askBalance_temp,return) and ( 
     int return<==0 and skip;
     char askBalance_temp[4096] and skip;
     if(!logged) then 
     {
          return<==1 and skip
     }
     else
     {
         sprintf(askBalance_temp,"SELECT * FROM ATM where FIRST='%s'",sargs[0]) and skip;
         runSQL(askBalance_temp);
         strcpy(serverMsg,"503 ") and skip;
         strcat(serverMsg,sargs[6]) and skip;
         sendMsg()
     }
     )
     }; 
  function showTransactions (  )
 {
     frame(showTransactions_temp,return) and ( 
     int return<==0 and skip;
     char showTransactions_temp[4096] and skip;
     if(!logged) then 
     {
          return<==1 and skip
     }
     else
     {
         sprintf(showTransactions_temp,"SELECT * FROM ATM where FIRST='%s'",sargs[0]) and skip;
         runSQL(showTransactions_temp);
         strcpy(serverMsg,"603 ") and skip;
         strcat(serverMsg,sargs[7]) and skip;
         sendMsg()
     }
     )
     }; 
  function requestStamps (  )
 {
     frame(return) and ( 
     int return<==0 and skip;
     if(!logged) then 
     {
          return<==1 and skip
     }
     else
     {
         strcpy(serverMsg,"704") and skip;
         sendMsg()
     }
     )
     }; 
  function stampsEmpty (  )
 {
     output ("Stamps are empty!\n") and skip;
     strcpy(serverMsg,"705") and skip;
     sendMsg()
     
 };
 function logout (  )
 {
     logged:=0;
     strcpy(serverMsg,"803") and skip;
     sendMsg()
     
     } ;
      main(RValue)
     )
