#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sqlite3.h"
#include <signal.h>
#include <time.h>
#include <winsock.h>
#include <pthread.h>
#include <windows.h>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "pthreadVC2.lib")
#define  N  32
#define  M  512
#define  R  1   //  user register
#define  L  2   //  user login
#define  Q  3   //  query word
#define  H  4   //  history record
#define  F  5
#define  G  6
#define  O  7 
#define  P 8
#define  A 9 //SIGN CAT
#define AM  10  //add message
#define SM  11 //select message
//定义数据库
#define passwdBASE "my.db"

typedef struct
{
	int connectfd;
	int permis_id; // 0 超级用户  1管理员  2 普通员工
	int type;
	char name[N];          //user_name 主键
	char  real_name[N];       //真实姓名
	char   phone_num[N];
	char   mail[N];              //邮箱
	char address[M];         //地址                 
	char passwd[256];  	// 密码
	char data[512];
	char data1[512];
	char data2[60];
} MyMSG;
sqlite3 *db;
void do_register(int connectfd, MyMSG *msg, sqlite3 *db);
void do_login(int connectfd, MyMSG *msg, sqlite3 *db);
void do_query(int connectfd, MyMSG *msg, sqlite3 *db);
void do_history(int connectfd, MyMSG *msg, sqlite3 *db);
void do_dele_root(int connectfd, MyMSG *msg, sqlite3*db);
void do_sign(int connectfd, MyMSG *msg, sqlite3 *db);
void do_sign_cat(int connectfd, MyMSG *msg, sqlite3 *db);
int history_callback_cat(void *arg, int f_num, char **f_value, char **f_name);

int  do_dele(int connectfd, MyMSG *msg, sqlite3 *db);
void do_find_root(int connectfd, MyMSG *msg, sqlite3 *db);
int  do_searchword(int connectfd, MyMSG *msg);
void getpasswd(char data[]);
int history_callback(void *arg, int f_num, char **f_value, char **f_name);

int history_callback1(void *arg, int f_num, char **f_value, char **f_name);
void * func_chuli(void *pth_agv);
void do_change(int connectfd, MyMSG *msg, sqlite3 *db);
void do_find(int connectfd, MyMSG *msg, sqlite3 *db);

void do_addMess(int connectfd, MyMSG *msg, sqlite3 *db);
void do_selectMess(int connectfd, MyMSG *msg, sqlite3 *db);


int main(int argc, char *argv[])
{
	int listenfd, err, num_of_pthread = 0;
	struct sockaddr_in server_addr;
	pid_t pid;
	MyMSG msg[1000];
	pthread_t thread;

	//打开数据库（如果数据库已经创建好了，调用函数后，之后利用指针操作数据库）
	//数据库里面有两个表，一个负责存放用户名和密码，用户名唯一，另一个负责存放历史记录
	if (sqlite3_open(passwdBASE, &db) != SQLITE_OK)
	{
		printf("error : %s\n", sqlite3_errmsg(db));
		exit(-1);
	}
	WSADATA  Ws;
	if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)//使用Winsock库函数之前,必须先调用函数WSAStartup,该函数负责初始化动态连接库Ws2_32.dll.
	{
		printf("Init Windows Socket Failed::%d\n", GetLastError());
		return -1;
	}
	if ((listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	//bzero(&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(8003);
	memset(server_addr.sin_zero, 0x00, 8);

	if (bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}

	if (listen(listenfd, 5) < 0)
	{
		perror("fail to listen");
		exit(-1);
	}


	while (1)
	{
		if ((msg[num_of_pthread].connectfd = accept(listenfd, NULL, NULL)) < 0)
		{
			perror("fail to accept");
			exit(-1);
		}

		//close(connectfd);
		// 创建线程

		//err = pthread_create(&thread, NULL, func_chuli, &msg[num_of_pthread]);
		//printf("msg[num_of_pthread].connectfd:%d\n", msg[num_of_pthread].connectfd);
		func_chuli(&msg[num_of_pthread]);
		

		/*if (err)
		{
			fprintf(stderr, "pthread creat error : %s \n", strerror(err));
			_close(msg[num_of_pthread].connectfd);
			return -1;
		}*/

		//num_of_pthread++;
		memset(&msg, '\0', sizeof(msg[0]));

	}
	return 0;
}



void do_client(int connectfd, sqlite3 *db)
{
	MyMSG msg;

	//根据接收到的type判断对应执行的代码
	while (recv(connectfd, (char*)&msg, sizeof(MyMSG), 0) > 0)  // receive request
	{
		//printf("type = %d\n", msg.type);
		switch (msg.type)
		{
		case R:
			do_register(connectfd, &msg, db);
			break;
		case L:
			do_login(connectfd, &msg, db);
			break;
		case Q:
			do_change(connectfd, &msg, db);
			break;
		case H:
			do_sign(connectfd, &msg, db);
			break;
		case F:
			do_find(connectfd, &msg, db);
			break;
		case G:
			do_find_root(connectfd, &msg, db);
			break;
		case O:
			do_dele(connectfd, &msg, db);
			break;
		case P:
			do_dele_root(connectfd, &msg, db);
			break;
		case A:
			do_sign_cat(connectfd, &msg, db);
			break;
		case AM:
			do_addMess(connectfd, &msg, db);
			break;
		case SM:
			do_selectMess(connectfd, &msg, db);
			break;
		}
	}
	printf("一个客户端下线lo\n");
	return;
}

void * func_chuli(void *pth_agv)
{

	//pthread_detach(pthread_self());
	//指针处理
	MyMSG * msg = (MyMSG *)pth_agv;
	do_client(msg->connectfd, db);
	return NULL;
}


//普通员工信息注销


int do_dele(int connectfd, MyMSG *msg, sqlite3 *db)
{

	char sqlstr[500] = { 0 };
	char *errmsg, **result;
	int nrow, ncolumn;

	sprintf(sqlstr, " delete from project  where name = '%s' ", msg->name);

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		printf("error : %s\n", errmsg);
		return -1;
	}

	strcpy(msg->data, "ok1");
	send(connectfd, (char*)msg, sizeof(MyMSG), 0);
	sqlite3_free_table(result);
	return 0;
}


// root版指定信息删除
void do_dele_root(int connectfd, MyMSG *msg, sqlite3*db)
{
	if (msg->permis_id >= 2)
	{
		return;
	}
	char sqlstr[500] = { 0 };
	char *errmsg, **result;
	int nrow, ncolumn;

	strcpy(msg->name, msg->data1);

	sprintf(sqlstr, " delete from project  where name = '%s' ", msg->data1);

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		printf("error : %s\n", errmsg);
	}


	strcpy(msg->data1, "删除成功\n");

	send(connectfd, (char*)msg, sizeof(MyMSG), 0);

	sqlite3_free_table(result);
	return;
}



//root版信息修改

void do_change(int connectfd, MyMSG *msg, sqlite3 *db)
{
	char sqlstr[2048] = { 0 };
	char *errmsg, **result;
	int nrow, ncolumn, flag = -1;
	char temp[20] = { 0 };
	if (msg->permis_id == 0)
	{
		;

	}
	else
	{
		if (strcmp(msg->data, "permis_id") == 0)
		{
			strcpy(temp, "权限不允许\n");
			send(connectfd, temp, sizeof(temp), 0);
			return;
		}

	}
	if (msg->permis_id == 0)
		sprintf(sqlstr, "update project set '%s'='%s'  where name = '%s' ", msg->data, msg->data1, msg->data2);
	else
		sprintf(sqlstr, "update project set '%s'='%s'  where name = '%s' ", msg->data, msg->data1, msg->name);
	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		printf("error : %s\n", errmsg);

		send(connectfd, temp, sizeof(temp), 0);
		sqlite3_free_table(result);
		return;
	}

	strcpy(temp, "ok");
	send(connectfd, temp, sizeof(temp), 0);

	sqlite3_free_table(result);
	return;
}


//员工版信息查询


void do_find(int connectfd, MyMSG *msg, sqlite3 *db)
{


	char sqlstr[500] = { 0 };
	char *errmsg, **result;
	int nrow, ncolumn;

	sprintf(sqlstr, "select * from project where name = '%s' and passwd = '%s'", msg->name, msg->passwd);

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{

		printf("error : %s\n", errmsg);
	}

	if (nrow == 0)
	{
		//strcpy(msg->passwd, "name or password is wrony!!!");
	}
	else
	{

		strcpy(msg->real_name, *(result + 6));
		strcpy(msg->name, *(result + 7));
		strcpy(msg->phone_num, *(result + 8));
		strcpy(msg->mail, *(result + 9));
		strcpy(msg->passwd, *(result + 10));
	}

	send(connectfd, (char*)msg, sizeof(MyMSG), 0);
	sqlite3_free_table(result);
	return;

}


void do_sign_cat(int connectfd, MyMSG *msg, sqlite3 *db)
{


	char *errmsg;

	char sqlstr[512] = "select * from work_table";

	if (sqlite3_exec(db, sqlstr, history_callback_cat, (void *)&connectfd, &errmsg) != SQLITE_OK)
	{
		printf("error : %s\n", errmsg);
		sqlite3_free(errmsg);
	}
	strcpy(msg->data, "ok_ok_op");
	send(connectfd, (char*)msg, sizeof(MyMSG), 0);

	return;
}


int history_callback_cat(void *arg, int f_num, char **f_value, char **f_name)
{
	int connectfd;
	MyMSG msg;

	connectfd = *(int *)arg;

	sprintf(msg.data1, "%12s : %12s : %12s : %12s ", f_value[0], f_value[1], f_value[2], f_value[3]);

	send(connectfd, (char*)&msg, sizeof(msg), 0);

	return 0;


}




//root版信息查询导出


void do_find_root(int connectfd, MyMSG *msg, sqlite3 *db)
{

	if (msg->permis_id != 0)
	{
		return;
	}

	char *errmsg;

	char sqlstr[512] = "select * from project";

	if (sqlite3_exec(db, sqlstr, history_callback1, (void *)&connectfd, &errmsg) != SQLITE_OK)
	{
		printf("error : %s\n", errmsg);
		sqlite3_free(errmsg);
	}
	strcpy(msg->data, "ok_ok");
	send(connectfd, (char*)msg, sizeof(MyMSG), 0);

	return;
}

//回调函数
int history_callback1(void *arg, int f_num, char **f_value, char **f_name)
{
	int connectfd;
	MyMSG msg;

	connectfd = *(int *)arg;

	sprintf(msg.data1, "%12s : %12s : %12s : %12s :%12s", f_value[0], f_value[1], f_value[2], f_value[3], f_value[4]);

	send(connectfd, (char*)&msg, sizeof(msg), 0);

	return 0;


}


void do_sign(int connectfd, MyMSG *msg, sqlite3 *db)
{

	char sqlstr[1024] = { 0 };
	char *errmsg, **result;
	int nrow, ncolumn;
	getpasswd(msg->data);

	sprintf(sqlstr, "insert into work_table  values('%s','%s',%s,'%s')", msg->real_name, msg->name, msg->phone_num, msg->data);

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		printf("error : %s\n", errmsg);
	}

	//nrow这个参数起始位置为1，所以等于0表示没有找到
	if (nrow == 0)
	{
		//strcpy(msg->passwd, "name or password is wrony!!!");
	}

	printf("%s %s %s\n", msg->real_name, msg->name, msg->data);
	send(connectfd, (char*)msg, sizeof(MyMSG), 0);
	sqlite3_free_table(result);
	return;
}



//注册
void do_register(int connectfd, MyMSG *msg, sqlite3 *db)
{

	char sqlstr[1024] = { 0 };
	char *errmsg;
	//CREATE TABLE t1(a INT UNIQUE, b INTEGER, c TEXT, PRIMARY KEY(c));
	sqlite3_exec(db, "create table project(a text,b text,c text,d text,e text,f integer)", NULL, NULL, &errmsg);

	sprintf(sqlstr, "insert into project values('%s','%s',%s,'%s','%s',3)", msg->real_name, msg->name, msg->phone_num, msg->mail, msg->passwd);

	if (sqlite3_exec(db, sqlstr, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		//sprintf(msg->passwd, "user %s already exist!!!", msg->name);
		//sqlite3_free(errmsg);
	}
	else
	{
		strcpy(msg->passwd, "OK");
	}

	printf("%s %s", msg->name, msg->passwd);
	send(connectfd, (char*)msg, sizeof(MyMSG), 0);

	return;
}

//登录
void do_login(int connectfd, MyMSG *msg, sqlite3 *db)
{
	char sqlstr[500] = { 0 };
	char *errmsg, **result;
	int nrow, ncolumn;

	sprintf(sqlstr, "select * from project where name = '%s' and passwd = '%s'", msg->name, msg->passwd);

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		//printf("error : %s\n", errmsg);
		printf("error");
	}

	//nrow这个参数起始位置为1，所以等于0表示没有找到
	if (nrow == 0)
	{
		//	strcpy(msg->passwd, "name or password is wrony!!!");
	}
	else
	{
		//******************************************************** 登录成功，获取id。加到结构里面

		int i = 0;

		strcpy(msg->real_name, *(result + 6));
		strcpy(msg->name, *(result + 7));
		strcpy(msg->phone_num, *(result + 8));
		strcpy(msg->mail, *(result + 9));
		strcpy(msg->passwd, *(result + 10));

		printf("%d\n", atoi(*(result + 11)));
		msg->permis_id = atoi(*(result + 11));

		if (msg->permis_id == 0)
		{
			strncpy(msg->data, "欢迎超级用户", 256);
		}
		else if (msg->permis_id == 1)
		{

			strncpy(msg->data, "欢迎管理员用户", 256);
		}
		else

			strncpy(msg->data, "欢迎普通用户", 256);
	}

	send(connectfd, (char*)msg, sizeof(MyMSG), 0);
	sqlite3_free_table(result);

	return;
}


//获取时间


void getpasswd(char data[])
{
	time_t t;
	struct tm *tp;
	time(&t);
	tp = localtime(&t);

	//将数据保存在passwd里面
	sprintf(data, "%d-%d-%d %d:%d:%d", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);

	return;
}

//查询
void do_query(int connectfd, MyMSG *msg, sqlite3 *db)
{
	char sqlstr[128], *errmsg;
	char date[128];

	//时间
	getpasswd(date);

	sprintf(sqlstr, "insert into '%s' values('%s', '%s')", msg->name, msg->real_name, date);

	if (sqlite3_exec(db, sqlstr, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("error : %s\n", errmsg);
	}


	return;
}







//发布公告
void do_addMess(int connectfd, MyMSG *msg, sqlite3 *db)
{
	time_t t;
	struct tm *tp;
	char date[128];
	time(&t);
	tp = localtime(&t);

	printf("do_addMess called.\n");

	char sqlstr[128], *errmsg;

	sprintf(date, "%d-%d-%d %d:%d:%d",
		tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday,
		tp->tm_hour, tp->tm_min, tp->tm_sec);

	sprintf(sqlstr, "insert into table_message(messDate, message) values('%s', '%s')", date, msg->data);
	if (sqlite3_exec(db, sqlstr, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		strcpy(msg->data, "failed, please again.");
		send(connectfd, (char*)msg, sizeof(MyMSG), 0);
		printf("error : %s\n", errmsg);
	}

	memset(msg->data, '\0', 256);
	strcpy(msg->data, "OK");
	send(connectfd, (char*)msg, sizeof(MyMSG), 0);
	printf("do_addMess called affter.\n");

	return;
}

//查看公告
void do_selectMess(int connectfd, MyMSG *msg, sqlite3 *db)
{
	char sqlstr[512] = { 0 };
	char p;
	char *errmsg = &p;
	char result1;
	char *result2 = &result1;
	char **result3 = &result2;
	char ***result4 = &result3;
	int nrow, ncolumn;

	strcpy(sqlstr, "select * from table_message");

	if (sqlite3_get_table(db, sqlstr, result4, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		printf("error : %s\n", errmsg);
	}

	printf("nrow = %d  ncolumn = %d\n", nrow, ncolumn);

	if (nrow == 0)
	{
		printf("selec failed.\n");
		memset(msg->data, '\0', 256);
		strcpy(msg->data, "NO");
		send(connectfd, (char*)msg, sizeof(msg), 0);
		return;
	}

	int i = 0, j = 0;
	int index = ncolumn;

	for (i = 0; i < nrow; i++)
	{
		memset(msg->data, '\0', 256);
		for (j = 0; j < ncolumn; j++)
		{
			msg->type = 117;
			strcat(msg->data, result3[index++]);
			strcat(msg->data, "|");
		}
		//printf("%s\n", msg->data);
		send(connectfd, (char*)msg, sizeof(MyMSG), 0);
		Sleep(50);
	}


	msg->data[0] = '\0';
	send(connectfd, (char*)msg, sizeof(MyMSG), 0);
	printf("fasong affter.\n");

	sqlite3_free_table(result3);

	return;
}

