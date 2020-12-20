/********************************************
* CSCE 3530 --- Introduction to Networks   *
* Project 1 --- ATM Client-Server Program  *
* Hollie King, Jeremy Doss, Richard Sutton *
* Client.c                                 *
********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <winsock.h>
#include <windows.h>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")

#define BUFF_SIZE	1024
#define MSG_SIZE	256
#define TMP_SIZE	128
#define MAX_MONEY	25000

#define	SERVER_IP	"127.0.0.1" // cse01

#define SERVER_PORT	8004
//#define SERVER_PORT	63456

//Global variables
char clientMsg[MSG_SIZE], serverMsg[MSG_SIZE];
char serverArgs[16][128];
int csock, atm_money = 10000, atm_stamps = 500;

//Function prototypes
void Connection();
void UI();
void sendMsg();
void recvMsg();
void codeMsg();
bool CreateAccount();
bool Authenticate();
void Deposit();
void Withdraw();
void DisplayBalance();
void ShowLastNTransactions();
void BuyStamps();


/****************************************************************/
/*						CODE BEGINS HERE						*/
/****************************************************************/


//Connection establishes connection, takes user input,
//calls functions to complete user input,
//and sends/receives clientMsgs with the server
void Connection() {
	int i;
	int send_len, bytes_sent, bytes_received;
	struct sockaddr_in	addr_send;
	char text[BUFF_SIZE], buffer[BUFF_SIZE];
	WSADATA  Ws;
	if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)//使用Winsock库函数之前,必须先调用函数WSAStartup,该函数负责初始化动态连接库Ws2_32.dll.
	{
		printf("Init Windows Socket Failed::%d\n", GetLastError());
		return -1;
	}
	csock = socket(AF_INET, SOCK_STREAM, 0);

	if (csock == -1)
		perror("ERROR: socket failed");

	memset(&addr_send, 0, sizeof(addr_send));
	addr_send.sin_family = AF_INET;
	addr_send.sin_addr.s_addr = inet_addr(SERVER_IP);
	addr_send.sin_port = htons((unsigned short)SERVER_PORT);

	if ((i = connect(csock, (struct sockaddr *)&addr_send, sizeof(addr_send))) < 0) {
		printf("Error! connect() failed\n");
		close(csock);
		exit(0);
	}

	UI();

	//close(csock);
}
int loopTime = 1;//验证时使用，自动输入数据，就不用手工输入了
void UI() {
	int selection;
	bool loggedin = false, quit = false;
	
	while (!quit) {
		loggedin = false;
		memset(clientMsg, 0, sizeof(clientMsg));
		memset(serverMsg, 0, sizeof(serverMsg));

		printf("Please enter a number to to make a selection\n");
		printf("1. Login\n");
		printf("2. Create Account\n");
		printf("3. Exit\n");
		printf("ATM Client>: ");
		//scanf("%d", &selection);
		if (loopTime == 1)
		{
			selection = 2;
		}
		else if (loopTime == 2)
		{
			selection = 1;
		}
		else if (loopTime == 3)
		{
			selection = 3;
		}
		loopTime++;
		switch (selection) {
		case 1:
			loggedin = Authenticate();
			break;
		case 2:
			loggedin = CreateAccount();
			break;
		case 3:
			printf("Thank you for using our services. Goodbye.\n");
			quit = true;
			break;
		default:
			printf("Incorrect input!\n");
			break;
		}

		if (loggedin) {
			int innerLoopTime = 1;
			while (!quit) {
				memset(clientMsg, 0, sizeof(clientMsg));
				memset(serverMsg, 0, sizeof(serverMsg));

				printf("~~~~~~~~~~~~~~~~User Account Menu~~~~~~~~~~~~~~~~\n");
				printf("Please enter a number to make a selection!\n");
				printf("1. Deposit.\n");
				printf("2. Withdraw.\n");
				printf("3. Display Balance.\n");
				printf("4. Previous n Transactions.\n");
				printf("5. Purchase Stamps.\n");
				printf("6. End Transaction (Exit).\n");
				printf("ATM Client>: ");
				//scanf("%d", &selection);
				if (innerLoopTime == 1)
				{
					selection = 2;
				}
				else if (innerLoopTime == 2)
				{
					selection = 6;
				}
				innerLoopTime++;
				switch (selection) {
				case 1:
					Deposit();
					break;
				case 2:
					Withdraw();
					break;
				case 3:
					DisplayBalance();
					break;
				case 4:
					ShowLastNTransactions();
					break;
				case 5:
					BuyStamps();
					break;
				case 6:
					printf("Logging out\n");
					strcpy(clientMsg, "801");
					sendMsg();
					recvMsg();
					quit = true;
					break;
				default:
					printf("ERROR! Incorrect input!\n");
					break;
				}
			}
			quit = false;
		}
	}
}

void sendMsg() {
	int msg_length, bytes_sent;

	if (MSG_SIZE < strlen(clientMsg)) {
		printf("Error! clientMsg length too long!\n");
		return;
	}
	else {
		bytes_sent = send(csock, clientMsg, strlen(clientMsg), 0);
	}

	//Reset the client clientMsg.
	memset(clientMsg, 0, MSG_SIZE);
}

void recvMsg() {
	char msgBuf[BUFF_SIZE];
	char *temp = NULL;
	int msg_length, bytes_sent, i = 0;

	if ((msg_length = recv(csock, serverMsg, MSG_SIZE, 0)) > 0) {
		//Set terminating character to NULL.
		serverMsg[msg_length] = 0;

		//Debug clientMsg.
		printf("Received Msg '%s'\nlength = %d\n", serverMsg, strlen(serverMsg));

		strcpy(msgBuf, serverMsg);
		temp = strtok(msgBuf, " ");
		while (temp != NULL) {
			strcpy(serverArgs[i], temp);
			temp = strtok(NULL, " ");
			i++;
		}

		codeMsg();
	}
}

void codeMsg() {
	int i;
	if (strcmp(serverMsg, "103") == 0)
		printf("Account creation failed: Entry error\n");

	if (strcmp(serverMsg, "104") == 0)
		printf("Account creation successful\n");

	if (strcmp(serverMsg, "105") == 0)
		printf("Account creation failed: Duplicate Account\n");

	if (strcmp(serverMsg, "203") == 0)
		printf("Authentication failed\n");

	if (strcmp(serverMsg, "204") == 0)
		printf("Authentication exceeded\n");

	/*if (strcmp(serverMsg, "205") == 0)
	printf("Authentication successful\n");*/

	if (strcmp(serverMsg, "302") == 0)
		printf("ATM Machine Full\nAttendant notified\n");

	/*if (strcmp(serverMsg, "303") == 0)
	printf("Deposit successful\n");*/

	if (strcmp(serverMsg, "304") == 0)
		printf("Deposit failed. Entry error\n");

	if (strcmp(serverMsg, "402") == 0)
		printf(" ATM Empty\nAttendant notified\n");

	/*if (strcmp(serverMsg, "403") == 0)
	printf("Withdraw successful\n");*/

	if (strcmp(serverMsg, "404") == 0)
		printf("Withdraw failed. Funds low\n");

	if (strcmp(serverMsg, "405") == 0)
		printf("ATM Empty\nAttendant notified\n");

	//if (strcmp(serverMsg, "503") == 0)
	//

	//if (strcmp(serverMsg, "603") == 0)
	//

	if (strcmp(serverMsg, "702") == 0)
		printf("Out of stamps\nAttendant notified\n");

	if (strcmp(serverMsg, "703") == 0)
		printf("Stamps Withdraw failed. Funds low\n");

	/*if (strcmp(serverMsg, "704") == 0)
	printf("Stamps Withdraw successful\n");*/

	if (strcmp(serverMsg, "705") == 0)
		printf("Out of stamps\nAttendant notified\n");

	if (strcmp(serverMsg, "803") == 0)
		printf("Client disconnected.\nGood Bye\n");

	if (strcmp(serverMsg, "908") == 0)
		printf("Error: Missing fields\n");

	printf("\n");
}

bool CreateAccount() {
	char input[TMP_SIZE], total[MSG_SIZE];

	strcpy(total, "101 "); //action code

	printf("First Name: ");
	//scanf("%s", input);
	strcpy(input, "1");
	strcat(total, input);
	strcat(total, " ");

	printf("Last Name: ");
	//scanf("%s", input);
	strcpy(input, "1");
	strcat(total, input);
	strcat(total, " ");

	printf("Pin: ");
	//scanf("%s", input);
	strcpy(input, "1");

	strcat(total, input);
	strcat(total, " ");

	printf("DL: ");
	//scanf("%s", input);
	strcpy(input, "1");
	strcat(total, input);
	strcat(total, " ");

	printf("SSN: ");
	//scanf("%s", input);
	strcpy(input, "1");
	strcat(total, input);
	strcat(total, " ");

	printf("Email Address: ");
	//scanf("%s", input);
	strcpy(input, "1");
	strcat(total, input);

	strcpy(clientMsg, total);

	sendMsg();
	recvMsg();

	if (strcmp(serverMsg, "104") == 0)
		return true;
	else
		return false;
}

bool Authenticate() {
	char input[TMP_SIZE], total[MSG_SIZE];

	strcpy(total, "201 "); //action code

	printf("First Name: ");
	//scanf("%s", input);
	strcpy(input, "1");
	
	strcat(total, input);
	strcat(total, " ");

	printf("Pin: ");
	//scanf("%s", input);
	strcpy(input, "1");
	strcat(total, input);

	strcpy(clientMsg, total);

	sendMsg();
	recvMsg();

	if (strcmp(serverMsg, "205") == 0)
		return true;
	else
		return false;
}

void Deposit() {
	char input[TMP_SIZE], total[TMP_SIZE];
	char *balance;
	int money = 0;

	strcpy(total, "301 ");

	printf("Amount: ");
	scanf("%s", input);

	money = atoi(input);

	if ((money + atm_money) < MAX_MONEY) {
		strcat(total, input);

		strcpy(clientMsg, total);
		printf("%s\n\n", clientMsg);

		sendMsg();
		recvMsg();

		if (strcmp(serverArgs[0], "303") == 0) {
			printf("Current Balance: $%s\n", serverArgs[1]);
			printf("\n");
			atm_money += money;
		}
	}

	else if (MAX_MONEY < (money + atm_money)){
		strcpy(serverArgs[0], "302");
		codeMsg();
	}
}

void Withdraw() {
	char input[TMP_SIZE], total[TMP_SIZE];
	int money = 0;

	strcpy(total, "401 ");

	printf("Amount: ");
	//scanf("%s", input);
	strcpy(input, "1");

	money = atoi(input);

	if (0 < (atm_money - money)) {
		strcat(total, input);

		strcpy(clientMsg, total);
		printf("%s\n\n", clientMsg);

		sendMsg();
		recvMsg();

		if (strcmp(serverArgs[0], "403") == 0) {
			printf("Current Balance: $%s\n", serverArgs[1]);
			printf("\n");
			atm_money -= money;
		}
	}

	else if ((atm_money - money) < 0) {
		strcpy(serverMsg, "402");
		codeMsg();
	}
}

void DisplayBalance() {
	strcpy(clientMsg, "501");

	sendMsg();
	recvMsg();

	if (strcmp(serverArgs[0], "503") == 0) {
		printf("Current Balance: $%s\n", serverArgs[1]);
		printf("\n");
	}
}

void ShowLastNTransactions() {
	char input[TMP_SIZE], total[TMP_SIZE];
	int i = 0;

	strcpy(total, "601 ");

	printf("Number of Transactions: ");
	scanf("%s", input);
	strcat(total, input);

	strcpy(clientMsg, total);

	sendMsg();
	recvMsg();

	if (strcmp(serverMsg, "603") == 0) {
		printf("List of %c Transactions sent\n", serverMsg[4]);
		for (i = 6; i<strlen(serverMsg); i++)
			printf("%c", serverMsg[i]);
		printf("\n");
	}
}

void BuyStamps() {
	char input[TMP_SIZE], total[TMP_SIZE];

	strcpy(total, "701 ");

	printf("Number of stamps: ");
	scanf("%s", input);
	strcat(total, input);

	strcpy(clientMsg, total);

	sendMsg();
	recvMsg();

}

int main(int argc, char *argv[]) {
	Connection();

	return 0;
}
