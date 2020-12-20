#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"
typedef struct {
	char name[128];
	char pass[128];
}MSG;

int usr_jiami(MSG*);
int usr_login(MSG*);
int usr_register(MSG*);
int usr_delete(MSG*);
void encode(char str[], int n);
void logControl(MSG* msg);
void totalControl(MSG *msg)
{
	int n;
	while (1){
		printf("***************************************************\n");
		printf("**** 1-register 2-login 3-jiami 4-jiemi 5-quit ****\n");
		printf("***************************************************\n");
		printf("please choose: ");
		scanf("%d", &n);
		switch (n){
		case 1:
			usr_register(msg);
			break;
		case 2:
			if (usr_login(msg) == 1){
				logControl(msg);
			}
			break;
		case 3:
			usr_jiami(msg);
			break;
		case 4:
			usr_jiemi(msg);
			break;
		case 5:
			return 0;
		default:
			printf("input [ 1-3 ]!\n");
		}
	}
};
void logControl(MSG* msg)
{
	int n;
	while (1){
		printf("************************************************\n");
		printf("******** 1.log off   2.quit   3.delete  ********\n");
		printf("************************************************\n");
		printf("please choose:");
		scanf("%d", &n);
		switch (n){
		case 1:
			totalControl(msg);
			break;
		case 2:
			usr_delete(msg);
			break;
		case 3:
			return 0;
		default:
			printf("input [1-2]\n");
		}
	}
}
int main()
{
	MSG msg;
	totalControl(&msg);
	return 0;
}

int usr_delete(MSG* msg)
{
	sqlite3 *db;
	char* errmsg;
	char sql[128] = { 0 };

	sprintf(sql, "delete from usr where name='%s'", msg->name);

	if (sqlite3_open("pass.db", &db) != 0){
		printf("open failed:%s\n", sqlite3_errmsg(db));
		return -1;
	}
	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0){
		printf("delete failed:%s\n", errmsg);
		sqlite3_free(errmsg);
		printf("%s already exist!\n", msg->name);
	}
	else{
		printf("delete success!\n");
	}
	sqlite3_close(db);
	return 0;
}

void encode(char str[], int n)
{
	char c;
	unsigned int i;
	for (i = 0; i<strlen(str); i++)
	{
		c = str[i];
		if (c >= 'a'&&c <= 'z')
			if (c + n % 26 <= 'z')
				str[i] = (char)(c + n % 26);
			else
				str[i] = (char)('a' + ((n - ('z' - c) - 1) % 26));
		else if (c >= 'A'&&c <= 'Z')
			if (c + n % 26 <= 'Z')
				str[i] = (char)(c + n % 26);
			else
				str[i] = (char)('A' + ((n - ('Z' - c) - 1) % 26));
		else
			str[i] = c;
		if (c >= '0'&&c <= '9')
			if (c + n % 9 <= '9')
				str[i] = (char)(c + n % 9);
			else
				str[i] = (char)('0' + ((n - ('9' - c) - 1) % 9));
	}
	printf("\n out:");
	puts(str);
}
int usr_jiemi(MSG* msg)
{
	char str[20];
	int i;
	printf("please input you want to jiemi:\n");
	scanf("%s", str);
	for (i = 1; i <= 25; i++)
	{
		printf("%d", i);
		encode(str, 1);
	}
}
int usr_jiami(MSG* msg)
{

	printf("name:");
	scanf("%s", msg->name);
	printf("pass:");
	scanf("%s", msg->pass);

	sqlite3 *db;
	char ** result;
	int row, column;
	char* errmsg;
	char sql[128] = { 0 };

	sprintf(sql, "select * from usr where name='%s' and pass='%s'", \
		msg->name, msg->pass);
	if (sqlite3_open("pass.db", &db) != 0){
		printf("open failed:%s\n", sqlite3_errmsg(db));
		return -1;
	}

	if (sqlite3_get_table(db, sql, &result, &row, &column, &errmsg) != 0){
		printf("select failed:%s\n", errmsg);
		sqlite3_free(errmsg);
		sqlite3_close(db);
		return -1;
	}
	if (row == 1)
	{
		char c;
		int i, n;
		char str[128];
		strcpy(str, msg->pass);
		printf("plaese enter the number of bits:");
		scanf("%d", &n);
		for (i = 0; i<strlen(str); i++)
		{
			c = str[i];
			if (c >= 'a'&&c <= 'z')
				if (c + n % 26 <= 'z')
					str[i] = (char)(c + n % 26);
				else
					str[i] = (char)('a' + ((n - ('z' - c) - 1) % 26));
			else if (c >= 'A'&&c <= 'Z')
				if (c + n % 26 <= 'Z')
					str[i] = (char)(c + n % 26);
				else
					str[i] = (char)('A' + ((n - ('Z' - c) - 1) % 26));
			else
				str[i] = c;
			if (c >= '0'&&c <= '9')
				if (c + n % 9 <= '9')
					str[i] = (char)(c + n % 9);
				else
					str[i] = (char)('0' + ((n - ('9' - c) - 1) % 9));
		}
		strcpy(msg->pass, str);

		sprintf(sql, "update usr set pass='%s' where name='%s'", msg->pass, msg->name);
		if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0){
			printf("jiami failed:%s\n", errmsg);
			sqlite3_free(errmsg);
			printf("%s can't find the name!jiami fialed!~~\n", msg->name);

		}
		else{
			printf("jiami is success!^_^\n");
		}

	}
	else
	{
		printf("name or pass wrong\n");
	}
	sqlite3_close(db);
	return 0;
}
int usr_register(MSG* msg){
	printf("name:");
	scanf("%s", msg->name);
	printf("pass:");
	scanf("%s", msg->pass);

	sqlite3 *db;
	char* errmsg;
	char sql[128] = { 0 };

	sprintf(sql, "insert into usr values('%s','%s')", msg->name, msg->pass);

	if (sqlite3_open("pass.db", &db) != 0){
		printf("open failed:%s\n", sqlite3_errmsg(db));
		return -1;
	}
	sqlite3_exec(db, "create table usr(name TEXT, pass TEXT)", NULL, NULL, NULL);
	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0){
		printf("insert failed:%s\n", errmsg);
		sqlite3_free(errmsg);
		printf("%s already exist!\n", msg->name);
	}
	else{
		printf("Register ok!\n");
	}
	memset(msg, 0, sizeof(MSG));
	sqlite3_close(db);
	return 0;
}
int usr_login(MSG* msg){

	printf("name:");
	scanf("%s", msg->name);
	printf("pass:");
	scanf("%s", msg->pass);

	sqlite3 *db;
	char ** result;
	int row, column;
	char* errmsg;
	char sql[128] = { 0 };

	sprintf(sql, "select * from usr where name='%s' and pass='%s'", \
		msg->name, msg->pass);

	if (sqlite3_open("pass.db", &db) != 0){
		printf("open failed:%s\n", sqlite3_errmsg(db));
		return -1;
	}

	if (sqlite3_get_table(db, sql, &result, &row, &column, &errmsg) != 0){
		printf("select failed:%s\n", errmsg);
		sqlite3_free(errmsg);
		sqlite3_close(db);
		return -1;
	}
	if (row == 1){
		printf("Welcome : Login success ^_^\n");
		return 1;
	}
	else{
		printf("Name or password wrong!\n");
	}

	sqlite3_close(db);
	return 0;
}
