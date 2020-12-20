#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sqlite3.h"
#include <winsock.h>
#include <pthread.h>
#include <windows.h>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")

#define  N  32
#define  R  1   //  user register
#define  L  2   //  user login
#define  Q  3   //  query word
#define  H  4   //  history record
#define  F  5
#define  G  6
#define  O  7 //dele
#define  A  9  //SIGN _CAT
#define  P  8 //DELE_ROOT
#define  AM 10  //add message
#define  SM 11 //select message

#define DATABASE "my.db"
/*
typedef struct
{
int cc;
int type;
char name[N];
int id;
char data[256];   // password or word or remark
} MyMSG;
*/

#define M 512
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

void do_register(int socketfd, MyMSG *msg);
int do_login(int socketfd, MyMSG *msg);
void do_query(int socketfd, MyMSG *msg);
void do_history(int socketfd, MyMSG *msg);
void do_sign(int socketfd, MyMSG * msg);
int init_View();
int do_rootView(int socketfd, MyMSG *msg);
int do_sign_cat(int socketfd, MyMSG *msg);
int do_adminView(int socketfd, MyMSG *msg);
int do_staffView(int socketfd, MyMSG *msg);
void do_dele_root(int socketfd, MyMSG * msg);
void do_dele(int socketfd, MyMSG *msg);
void do_find(int socketfd, MyMSG * msg);

int do_selectMess(int socketfd, MyMSG *msg);
int do_addMess(int socketfd, MyMSG *msg);

int main(int argc, char *argv[])
{
	int socketfd;
	struct sockaddr_in server_addr;
	MyMSG msg;
	WSADATA  Ws;
	if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)//使用Winsock库函数之前,必须先调用函数WSAStartup,该函数负责初始化动态连接库Ws2_32.dll.
	{
		printf("Init Windows Socket Failed::%d\n", GetLastError());
		return -1;
	}
	if ((socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}
	memset(&msg, 0,sizeof(msg));
	memset(&server_addr, 0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(8004);
	if (connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("fail to connect");
		exit(-1);
	}

	while (1)
	{
		switch (init_View())
		{
		case 1:
			do_register(socketfd, &msg);
			break;
		case 2:

			switch (do_login(socketfd, &msg))
			{
			case 0: //进入root操作
				do_rootView(socketfd, &msg);
				break;
			case 1: //进入管理员操作
				do_adminView(socketfd, &msg);
				break;
			case 2: //进入员工操作
				do_staffView(socketfd, &msg);
				break;
			default:
				break;
			}
			break;
		case 3:
			close(socketfd);
			exit(0);
		}
	}

	return 0;
}

//查询选项界面
int do_staffView(int socketfd, MyMSG *msg)
{
	int n = 0;
	int flag = 0;
	char del[N];

	while (1)
	{
		printf("***************************\n");
		printf("***************************\n");
		printf("**** 欢迎进入员工界面  ****\n");
		printf("***************************\n");
		printf("**** 1.签到打卡        ****\n");
		printf("**** 2.查看公告        ****\n");
		printf("**** 3.查看个人信息    ****\n");
		printf("**** 4.修改个人信息    ****\n");
		printf("**** 5.注销个人信息    ****\n");
		printf("**** 6.退出            ****\n");
		printf("***************************\n");

		while (1)
		{
			printf("please choose:");
			scanf("%d", &n);
			gets(del); //消除命令行字符或字符串

			if (n >= 1 && n <= 7) break;
			else
			{
				printf("Input_next error!\n");
				continue;
			}

			//free(del); //清空数组
		}

		switch (n)
		{
		case 1:   //签到打卡
			do_sign(socketfd, msg);
			break;
		case 2:   //查看公告
			do_selectMess(socketfd, msg);
			break;
		case 3:  //查看个人信息
			do_find(socketfd, msg);
			break;
		case 4:  //修改个人信息
			do_query(socketfd, msg);
			break;
		case 5:  //注销个人信息
			do_dele(socketfd, msg);
			flag = 1;
			break;
		case 6:  //退出
			flag = 1;
			break;
		}
		if (flag == 1) break;
	}
	return flag;
}

int init_View(void)
{
	int n = 0;
	char del[N];
	/*printf("******************************\n");
	printf("**** 欢迎来到员工管理系统 ****\n");
	printf("******************************\n");
	printf("**** 输入：        |如|   ****\n");
	printf("**** 1.注册        |来|   ****\n");
	printf("**** 2.登录        |佛|   ****\n");
	printf("**** 3.退出        |组|   ****\n");
	printf("******************************\n");*/
	while (1)
	{
		printf("请选择:");
		//scanf("%d", &n);
		//gets(del);
		n = 2;//不让用户输入了，直接选择1
		if ((n == 1) || (n == 2) || (n == 3)) return n;
		else
		{
			printf("输入有误,请重试!\n");
			continue;
		}
	}

	return 0;
}

/***************root***************/

int do_rootView(int socketfd, MyMSG *msg)
{
	printf("***************************\n");
	printf("**** 欢迎进root界面    ****\n");
	printf("***************************\n");
	printf("**** 1.修改信息        ****\n");
	printf("**** 2.帐号查看        ****\n");
	printf("**** 3.删除指定        ****\n");
	printf("**** 4.查看导出        ****\n");
	printf("**** 5.退出            ****\n");
	printf("***************************\n");

	int n = 0;
	int flag = 1;
	char del[N];

	while (flag)
	{
		printf("请输入>>>");
		scanf("%d", &n);
		gets(del);

		switch (n)
		{
		case 1:   //修改信息
			do_query(socketfd, msg);
			break;
		case 2:   //帐号查看
			do_find(socketfd, msg);
			break;
		case 4:   //查看导出
			do_history(socketfd, msg);
			break;
		case 3:    //删除指定
			do_dele_root(socketfd, msg);
			break;
		case 5:     //退出
			printf("退出登录...\n");
			flag = 0;
			break;
		default:
			printf("Input error, Please again.\n");
			break;
		}
	}

	return 0;
}


/**************************/
//管理员界面
int do_adminView(int socketfd, MyMSG *msg)
{
	printf("***************************\n");
	printf("**** 欢迎进入管理员界面****\n");
	printf("***************************\n");
	printf("**** 1.帐号查看        ****\n");
	printf("**** 2.删除用户        ****\n");
	printf("**** 3.发布公告        ****\n");
	printf("**** 4.查看历史公告    ****\n");
	printf("**** 5.查看考勤记录    ****\n");
	printf("**** 6.退出            ****\n");
	printf("***************************\n");

	int n = 0;
	int flag = 1;
	char del[N];

	while (flag)
	{
		printf("请输入>>>");
		scanf("%d", &n);
		gets(del);

		switch (n)
		{
		case 1: //查看用户
			do_find(socketfd, msg);
			break;
		case 2: //删除用户
			do_dele_root(socketfd, msg);
			break;
		case 3: //发布公告
			do_addMess(socketfd, msg);
			break;
		case 4:
			do_selectMess(socketfd, msg);
			break;
		case 5:
			do_sign_cat(socketfd, msg);
			break;
		case 6:
			printf("退出登录...\n");
			flag = 0;
			break;
		default:
			printf("Input error, Please again.\n");
			break;
		}
	}

	return 0;
}

/************************/



void do_find(int socketfd, MyMSG * msg)
{
	msg->type = F;
	send(socketfd, msg, sizeof(MyMSG), 0);
	recv(socketfd, msg, sizeof(MyMSG), 0);
	printf("%s\n", msg->real_name);
	printf("%s\n", msg->name);
	printf("%s\n", msg->phone_num);
	printf("%s\n", msg->mail);
	printf("%s\n", msg->passwd);
}


void do_dele_root(int socketfd, MyMSG * msg)
{
	msg->type = P;
	printf("请输入你要删除的用户名\n");
	scanf("%s", msg->data1);
	send(socketfd, msg, sizeof(MyMSG), 0);
	printf("ll\n");
	recv(socketfd, msg, sizeof(MyMSG), 0);
	printf("%s\n", msg->data1);
}


void do_sign(int socketfd, MyMSG * msg)
{
	msg->type = H;
	printf("%s\n", msg->real_name);
	printf("欢迎签到\n");
	send(socketfd, msg, sizeof(MyMSG), 0);
	recv(socketfd, msg, sizeof(MyMSG), 0);

	printf("%s %s %s签到成功\n", msg->real_name, msg->name, msg->data);
}


//注册
void do_register(int socketfd, MyMSG *msg)
{
	msg->type = R;

	/*printf("请输入真实姓名:");
	scanf("%s", msg->real_name);

	printf("请输入用户名:");
	scanf("%s", msg->name);


	printf("请输入电话号:");
	scanf("%s", msg->phone_num);


	printf("请输入邮箱:");
	scanf("%s", msg->mail);

	printf("请设置密码:");
	scanf("%s", msg->passwd);*/

	strcpy(msg->real_name, "yubin");
	strcpy(msg->name, "yubin");
	strcpy(msg->phone_num, "yubin");
	strcpy(msg->mail, "yubin");
	strcpy(msg->passwd, "yubin");


	send(socketfd, msg, sizeof(MyMSG), 0);

	recv(socketfd, msg, sizeof(MyMSG), 0);

	printf("注册: %s\n", msg->passwd);

	return;
}

//登录
int do_login(int socketfd, MyMSG *msg)
{
	msg->type = L;

	//printf("请输入用户名:");
	//scanf("%s", msg->name);
	strcpy(msg->name, "yubin");

	//printf("请输入密码:");
	//scanf("%s", msg->passwd);
	strcpy(msg->passwd, "yubin");

	send(socketfd, msg, sizeof(MyMSG), 0);

	recv(socketfd, msg, sizeof(MyMSG), 0);


	if (strncmp(msg->data, "欢迎超级用户", 256) == 0)
	{
		printf("欢迎超级用户登录\n");
		memset(msg->data, 'c', sizeof(msg->data));
		return 0;
	}


	else if (strncmp(msg->data, "欢迎管理员用户", 256) == 0)
	{
		printf("欢迎管理员用户登录\n");
		memset(msg->data, 'c', sizeof(msg->data));
		return 1;
	}

	else if (strncmp(msg->data, "欢迎普通用户", 256) == 0)
	{
		printf("欢迎普通用户登录\n");
		memset(msg->data, 'c', sizeof(msg->data));
		return 2;
	}
	else;

	//printf("用户名或者密码错误\n");

	return -1;
}

//修改信息
void do_query(int socketfd, MyMSG *msg)
{
	msg->type = Q;
	puts("---------");


	{
		if (msg->permis_id == 0)
		{
			printf("修改某用户权限 输入:permis_idnumber name xxxx \n ");
			printf("权限值permis_idnumber为0或1或3\n ");
			printf("请输入>>>");
			scanf("%s %s %s", msg->data, msg->data1, msg->data2);
		}
		else
		{
			printf("或输入 修改姓名：   real_name xxxx \n ");
			printf("或输入 修改用户名： name xxxx \n ");
			printf("或输入 修改密码：   passwd xxxx \n ");
			printf("或输入 修改邮箱ID:  mail xxxx \n ");
			printf("或输入 修改电话号:  phone_num xxxx \n ");
			printf("请输入>>>");
			scanf("%s %s", msg->data, msg->data1);
		}







		send(socketfd, msg, sizeof(MyMSG), 0);

		char temp[20] = { 0 };
		recv(socketfd, temp, sizeof(temp), 0);

		if (strcmp(temp, "ok") == 0)
		{
			printf("******修改成功 %s = %s\n", msg->data, msg->data1);
		}
		else{
			printf("修改失败\n");
		}
	}

	return;
}



void do_dele(int socketfd, MyMSG *msg)
{
	msg->type = O;
	puts("---------\n");
	char op = 'n';


	printf("你确定要注销吗，确定按y，退回按n \n ");
	op = getchar();
	if (op == 'y')
	{
		send(socketfd, msg, sizeof(MyMSG), 0);
	}
	else return;

	recv(socketfd, msg, sizeof(MyMSG), 0);

	if (strcmp(msg->data, "ok1") == 0)
	{
		printf("******删除成功***********n");
	}
	else{
		printf("修改失败\n");
	}
	return;
}



//查询历史记录
void do_history(int socketfd, MyMSG *msg)
{
	msg->type = G;
	int option = 1;
	send(socketfd, msg, sizeof(MyMSG), 0);



	FILE*fp = fopen("1.txt", "w+");
	if (fp == NULL)
	{
		printf("fail to cr\n");
	}
	printf("  %-12s %-12s %-12s %-12s %-12s \n", "姓名", "帐号", "电话", "邮箱", "密码");
	fprintf(fp, "  %-12s %-12s %-12s %-12s %-12s \n", "姓名", "帐号", "电话", "邮箱", "密码");
	while (strcmp(msg->data, "ok_ok") != 0)
	{
		recv(socketfd, msg, sizeof(MyMSG), 0);
		if (msg->data[0] == '\0')
		{
			break;
		}

		printf("  %-s\n", msg->data1);
		fprintf(fp, "  %s\n", msg->data1);

	}

	fflush(NULL);
	fclose(fp);
	strcpy(msg->data, "nook");
	return;
}

int  do_sign_cat(int socketfd, MyMSG *msg)
{
	msg->type = A;
	int option = 1;
	send(socketfd, msg, sizeof(MyMSG), 0);

	FILE*fp = fopen("kaoqin.txt", "w+");
	if (fp == NULL)
	{
		printf("fail to cr\n");

	}
	printf("            %-12s   %-12s  %-12s  %-12s \n", "姓名", "帐号", "电话", "签到时间");
	fprintf(fp, "          %-12s  %-12s   %-12s  %-12s \n", "姓名", "帐号", "电话", "签到时间");
	while (strcmp(msg->data, "ok_ok_op") != 0)
	{
		recv(socketfd, msg, sizeof(MyMSG), 0);
		if (msg->data[0] == '\0')
		{
			break;
		}

		printf("  %-s\n", msg->data1);
		fprintf(fp, "  %-s\n", msg->data1);

	}

	fflush(NULL);
	fclose(fp);
	strcpy(msg->data, "n_ook_op");
	return;
}


//发表公告
int do_addMess(int socketfd, MyMSG *msg)
{
	msg->type = AM;

	printf("请输入公告消息：");
	gets(msg->data);

	send(socketfd, msg, sizeof(MyMSG), 0);
	memset(msg->data, '\0', 256);
	recv(socketfd, msg, sizeof(MyMSG), 0);

	if (strncmp(msg->data, "OK", 3) == 0)
	{
		printf("公告发布: OK!\n");
		return 1;
	}

	printf("公告发布: %s\n", msg->data);

	return 0;
}

//查看公告
int do_selectMess(int socketfd, MyMSG *msg)
{
	msg->type = SM;

	send(socketfd, msg, sizeof(MyMSG), 0);


	printf("公告如下：\n");
	while (1)
	{
		memset(msg->data, '\0', sizeof(msg->data));
		recv(socketfd, msg, sizeof(MyMSG), 0);
		fflush(NULL);

		if (strncmp(msg->data, "NO", 3) == 0)
		{
			printf("查看公告失败！请重试.\n");
			break;
		}
		if (msg->data[0] == '\0') break;

		printf("%s\n", msg->data);
	}

	printf("以上是查询结果.\n");

	return 0;
}
