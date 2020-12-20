/*
CSCE 3530 ATM Project - ATMserver.c
Jeremy Doss, Hollie King, Richard Sutton
4/2/2015
*/

#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"
#include <stdbool.h>
#include <winsock.h>
#include <windows.h>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE	4096
#define MSG_SIZE	4096
#define BACKLOG	5
#define LISTEN_PORT	8003

//Global Variables.
char clientArgs[16][128];
int argCnt;
char serverMsg[MSG_SIZE];
char msgBuf[BUF_SIZE];
int msg_length, bytes_sent;
int failedAttempts = 0;
int threadCount = BACKLOG;
int created = 0;
int totalMoney = 10000;

//sqlite3 globals.
sqlite3 *db;
char* sqlError = 0;
int rc;
int sargc;
char sargs[128][128];
char colNames[128][128];
int logged = 1;

//Global Socket Variables.
int sock_listen;				//Socket file descriptors.
int csock;
struct sockaddr_in addr_mine;	//Server address structure.
struct sockaddr_in addr_remote;	//Client address structure.

//Function prototypes.
void *atm_client_handler(void *arg);
void sendMsg();

//Database functions.
void databaseDriver();
bool initDB();
void runSQL(char* sql);

//ATM functions.
void CreateAccount();
void Authentication();
void Deposit();
void MachineFull();
void Withdraw();
void MachineEmpty();
void askBalance();
void showTransactions();
void requestStamps();
void stampsEmpty();
void logout();

//sqlite3 callback function.
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;

	sargc = argc;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		strcpy(sargs[i], argv[i]);
		strcpy(colNames[i], azColName[i]);
	}
	printf("~~~~~~~~~~~~~~~~DB ENTRY~~~~~~~~~~~~~~~~\n");
	return 0;
}

//Main server program.
int main(int argc, char *argv[]) {
	int status, *sock_tmp;
	char* sql;
	//void *thread_result;

	//Client socket file descriptor.
	int sock_aClient;
	int addr_size;
	int reuseaddr = 1;

	//initialize the sqlite3 database.
	if (!initDB()) {
		printf("Error! Failed to initialize the database!\n");
		exit(1);
	}

	//One-time table initialization.
	if (!created) {
		sql = "CREATE TABLE ATM(" \
			"FIRST TEXT PRIMARY KEY NOT NULL," \
			"LAST TEXT NOT NULL," \
			"PIN INT NOT NULL," \
			"DL INT NOT NULL," \
			"SSN INT NOT NULL," \
			"EMAIL CHAR(40)," \
			"BALANCE REAL," \
			"TRANSACTIONS INT NOT NULL );";

		//Execute SQL statement.
		runSQL(sql);
	}

	WSADATA  Ws;
	if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)//使用Winsock库函数之前,必须先调用函数WSAStartup,该函数负责初始化动态连接库Ws2_32.dll.
	{
		printf("Init Windows Socket Failed::%d\n", GetLastError());
		return -1;
	}
	//Create socket.
	sock_listen = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_listen < 0) {
		perror("Error! socket() failed!\n");
		exit(0);
	}

	//Store the input socket information.
	memset(&addr_mine, 0, sizeof(addr_mine));
	addr_mine.sin_family = AF_INET;
	addr_mine.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_mine.sin_port = htons((unsigned short)LISTEN_PORT);

	//Enable the socket to reuse the address.
	if (setsockopt(sock_listen, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(int)) == -1) {
		perror("setsockopt");
		_close(sock_listen);
		exit(1);
	}

	//Bind the port to socket.
	status = bind(sock_listen, (struct sockaddr *)&addr_mine, sizeof(addr_mine));
	if (status < 0) {
		perror("Error! bind() failed!\n");
		_close(sock_listen);
		exit(1);
	}

	//Listen on the desired port.
	status = listen(sock_listen, 5);
	if (status < 0) {
		perror("Error! listen() failed!\n");
		_close(sock_listen);
		exit(1);
	}

	addr_size = sizeof(struct sockaddr_in);

	printf("Socket established! Listening for a client...\n");

	//Main server loop that listens for new TCP connections.
	while (1) {
		if (threadCount < 1)
			Sleep(1);

		//sock_aClient = accept(sock_listen, (struct sockaddr *)&addr_remote, &addr_size);
		sock_aClient = accept(sock_listen, NULL, NULL);
		if (sock_aClient == -1) {
			printf("Error! Client not accepted!\n");
			_close(sock_listen);
			exit(1);
		}

		printf("IP address %s ", (char*)inet_ntoa(addr_remote.sin_addr));
		printf("is connected on port %d\n", htons(addr_remote.sin_port));

		sock_tmp = malloc(1);
		*sock_tmp = sock_aClient;

		//printf("Thread count = %d\n", threadCount);
		threadCount--;

		//status = pthread_create(&athread, NULL, atm_client_handler, (void *)sock_tmp);
		atm_client_handler((void *)sock_tmp);

		if (status != 0) {
			perror("Thread creation failed");
			_close(sock_listen);
			_close(sock_aClient);
			free(sock_tmp);
			exit(1);
		}
	}
	sqlite3_close(db);
	return 0;
}

//Client handler.
void *atm_client_handler(void *client_desc) {
	int msg_size, i;
	char buff[BUF_SIZE];
	char *tmp = NULL;
	char temp[4096];
	csock = *(int*)client_desc;

	printf("Client handler entered...\n");

	//if (!logged) {
	//sprintf(temp, "SELECT * FROM ATM", sargs[0]);
	//runSQL(temp);
	//}

	//Message receiving loop.
	while ((msg_size = recv(csock, buff, BUF_SIZE, 0)) > 0) {
		//Set terminating character to NULL.
		buff[msg_size] = 0;

		//Debug message.
		printf("Received message '%s'\n", buff);

		//Tokenate the string into parts.
		i = 0;
		tmp = strtok(buff, " ");
		while (tmp != NULL) {
			strcpy(clientArgs[i], tmp);
			tmp = strtok(NULL, " ");
			i++;

			//DEBUG: Print the client arguments.
			//printf("Argument[%d] = %s\n", i, clientArgs[i]);
		}

		argCnt = i;

		//Use the array of arguments clientArgs[] to send data to database.
		databaseDriver();
	}

	logged = 0;

	//DEBUG
	printf("Exiting the client handler...\n");

	//Close the socket.
	//_close(sock_listen);
	//free(client_desc);

	//Close the thread.
	threadCount++;
	//pthread_exit("Exiting...\n");
}

//Sends codes back to the client.
void sendMsg() {
	//Send the message to the server socket.
	msg_length = strlen(serverMsg);

	if (msg_length > BUF_SIZE) {
		printf("Error! Message length too long!\n");
		return;
	}
	else {
		strcpy(msgBuf, serverMsg);
		bytes_sent = send(csock, msgBuf, msg_length, 0);
	}

	//Reset the client message.
	memset(serverMsg, 0, sizeof(serverMsg));
	memset(msgBuf, 0, sizeof(msgBuf));
}

bool initDB() {
	rc = sqlite3_open("atm.db", &db);

	if (rc) {
		printf("Cannot open the database: %s\n", sqlite3_errmsg(db));
		return 0;
	}
	else {
		printf("The database opened successfully!\n");
		sqlite3_close(db);
		return 1;
	}
}

void runSQL(char* sql) {
	rc = sqlite3_open("atm.db", &db);
	if (rc) {
		printf("Cannot open the database: %s\n", sqlite3_errmsg(db));
		return;
	}

	//Execute SQL statement.
	rc = sqlite3_exec(db, sql, callback, 0, &sqlError);

	if (rc != SQLITE_OK) {
		printf("SQL error: %s\n", sqlError);
		sqlite3_free(sqlError);
	}
	//else
	//printf("SQL success!\n");

	sqlite3_close(db);
}

void databaseDriver() {
	//Access clientArgs[] globally.
	if (strcmp(clientArgs[0], "101") == 0)
		CreateAccount();
	else if (strcmp(clientArgs[0], "201") == 0)
		Authentication();
	else if (strcmp(clientArgs[0], "301") == 0)
		Deposit();
	else if (strcmp(clientArgs[0], "302") == 0)
		MachineFull();
	else if (strcmp(clientArgs[0], "401") == 0)
		Withdraw();
	else if (strcmp(clientArgs[0], "402") == 0)
		MachineEmpty();
	else if (strcmp(clientArgs[0], "501") == 0)
		askBalance();
	else if (strcmp(clientArgs[0], "601") == 0)
		showTransactions();
	else if (strcmp(clientArgs[0], "701") == 0)
		requestStamps();
	else if (strcmp(clientArgs[0], "702") == 0)
		stampsEmpty();
	else if (strcmp(clientArgs[0], "801") == 0)
		logout();
	else
		printf("Incorrect command received from client.\n");
}

//101 - Create an account.
void CreateAccount() {
	char temp[4096];

	//Verify creation, build message.
	/*if (strlen(clientArgs[1]) >= 20 || strlen(clientArgs[2]) >= 20 || strlen(clientArgs[3]) != 4 ||
		strlen(clientArgs[4]) != 8 || strlen(clientArgs[5]) != 9 || strlen(clientArgs[6]) >= 40) {
		strcpy(serverMsg, "103");	//Incorrect fields.
	}
	else*/ 
	{
		sprintf(temp, "SELECT * FROM ATM where FIRST='%s'", clientArgs[1]);

		runSQL(temp);

		//Debug.
		//printf("FIRST = '%s'\n", sargs[0]);

		if (strcmp(sargs[0], clientArgs[1]) != 0) {
			printf("Creating a new account for %s!\n", clientArgs[1]);

			sprintf(temp, "INSERT INTO ATM (FIRST,LAST,PIN,DL,SSN,EMAIL,BALANCE,TRANSACTIONS) VALUES ('%s', '%s', %s, %s, %s, '%s', 100.00, 5 );",
				clientArgs[1], clientArgs[2], clientArgs[3], clientArgs[4], clientArgs[5], clientArgs[6]);

			runSQL(temp);
			logged = 1;


			strcpy(serverMsg, "104");		//Account created.
		}
		else {
			printf("That account already exists!\n");
			strcpy(serverMsg, "105");		//Account exists.
			logged = 0;
		}
	}
	//Send and clear message.
	sendMsg();
}

//201 - User log in.
void Authentication() {
	char temp[4096];

	if (failedAttempts >= 10) {
		strcpy(serverMsg, "204");
		failedAttempts = 0;
		sendMsg();
		_close(sock_listen);
		return;
	}

	sprintf(temp, "SELECT * FROM ATM where FIRST='%s'", clientArgs[1]);
	runSQL(temp);

	if (strcmp(sargs[0], clientArgs[1]) == 0 && strcmp(sargs[2], clientArgs[2]) == 0) {
		//Access granted!
		strcpy(serverMsg, "205");
		logged = 1;
		failedAttempts = 0;

	}
	else {
		//Access denied...
		strcpy(serverMsg, "203");
		logged = 0;
		failedAttempts++;
	}
	sendMsg();
}

//301 - Make a deposit.
void Deposit() {
	char temp[4096];
	int balance;

	if (!logged) //Can return the '304' error code here. Unnecessary.
		return;
	else {
		balance = atoi(sargs[6]);
		balance += atoi(clientArgs[1]);

		printf("Updated balance for %s = %d\n", sargs[0], balance);

		sprintf(temp, "UPDATE ATM set BALANCE=%d where FIRST='%s'", balance, sargs[0]);
		runSQL(temp);

		sprintf(temp, "SELECT * FROM ATM where FIRST='%s'", sargs[0]);
		runSQL(temp);

		strcpy(serverMsg, "303 ");
		strcat(serverMsg, sargs[6]);

		sendMsg();
	}
}

//302 - ATM is full.
void MachineFull() {
	if (!logged)
		return;
	else {
		strcpy(serverMsg, "305 ");		//Deposit return.
		strcat(serverMsg, sargs[6]);		//Notify of balance.
	}
	//Send and clear message.
	sendMsg();
}

//401 - Withdraw money.
void Withdraw() {
	char temp[4096];
	int value, balance;

	if (!logged)
		return;
	else {
		value = atoi(clientArgs[1]);
		balance = atoi(sargs[6]);
		printf("%d, %d\n", balance, value);

		if ((balance - value) < 0) {
			printf("Insufficient funds!\n");
			strcpy(serverMsg, "404");
			sendMsg();
			return;
		}
		else {
			balance -= value;
			sprintf(temp, "UPDATE ATM set BALANCE=%d where FIRST='%s'", balance, sargs[0]);
			runSQL(temp);

			sprintf(temp, "SELECT * FROM ATM where FIRST='%s'", sargs[0]);
			runSQL(temp);

			strcpy(serverMsg, "403 ");
			strcat(serverMsg, sargs[6]);
			sendMsg();
		}
	}
}

//402 - Empty ATM.
void MachineEmpty() {
	if (!logged)
		return;
	else {
		strcpy(serverMsg, "405");
		sendMsg();
	}
}

//501 - Ask for current balance.
void askBalance() {
	char temp[4096];

	if (!logged)
		return;
	else {
		sprintf(temp, "SELECT * FROM ATM where FIRST='%s'", sargs[0]);
		runSQL(temp);
		//Verify creation, build message.
		strcpy(serverMsg, "503 ");
		strcat(serverMsg, sargs[6]);
		//Send and clear message.
		sendMsg();
	}
}

//601 - Return the number of transactions
void showTransactions() {
	char temp[4096];

	if (!logged)
		return;
	else {
		sprintf(temp, "SELECT * FROM ATM where FIRST='%s'", sargs[0]);
		runSQL(temp);

		strcpy(serverMsg, "603 ");
		strcat(serverMsg, sargs[7]);
		//Send and clear message.
		sendMsg();
	}
}

//701 - Request stamps.
void requestStamps() {
	if (!logged)
		return;
	else {
		//Success.
		strcpy(serverMsg, "704");
		//Send and clear message.
		sendMsg();
	}
}

//702 - ATM stamps are empty.
void stampsEmpty() {
	printf("Stamps are empty!\n");
	strcpy(serverMsg, "705");
	sendMsg();
}

void logout() {
	logged = 0;
	//Verify creation, build message.
	strcpy(serverMsg, "803");
	//Send and clear message.
	//_close(sock_listen);
	sendMsg();
}
