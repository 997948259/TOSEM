 </
define p:sqlite3_get_table_call=1;
define q:sqlite3_free_call=1;
alw(p->som(q))
/>
struct MyMSG
{
	int connectfd and 
	int permis_id and 
	int type and 
	char name[32]and           
	char  real_name[32] and     
	char   phone_num[32] and
	char   mail[32] and       
	char address[512] and                        
	char passwd[256] and 
	char data[512] and
	char data1[512] and
	char data2[60]
};

function do_register(int connectfd, MyMSG *msg)
{
	frame(msg,connectfd) and (
	char sqlstr[1024] and skip;
	char *errmsg and skip;

	sprintf(sqlstr, "insert into project values('%s','%s',%s,'%s','%s',3)", msg->real_name, msg->name, msg->phone_num, msg->mail, msg->passwd) and skip;

	if (sqlite3_exec(db, sqlstr, NULL, NULL, &errmsg) != 0) then
	{
		printf("user %s already exist!!!", msg->name) and skip
		//sqlite3_free(errmsg);
	}
	else
	{
		strcpy(msg->passwd, "OK") and skip
	};

	printf("%s %s", msg->name, msg->passwd) and skip;
	send(connectfd, (char*)msg, sizeof(MyMSG), 0) and skip
	)
};

//普通员工信息注销
function do_dele(int connectfd, MyMSG *msg, int RValue)
{

	char sqlstr[500] and skip;
	char *errmsg, **result and skip;
	int nrow, ncolumn and skip;
	sprintf(sqlstr, " delete from project  where name = '%s' ", msg->name) and skip;

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != 0) then
	{
		printf("error : %s\n", errmsg) and skip;
		RValue:= -1;
		skip
	}
	else
	{
		strcpy(msg->data, "ok1") and skip;
		send(connectfd, (char*)msg, sizeof(MyMSG), 0) and skip;
		sqlite3_free_table(result) and skip;
		RValue:=0;
		skip
	}
};

// root版指定信息删除
function do_dele_root(int connectfd, MyMSG *msg)
{
	if (msg->permis_id >= 2) then
	{
		skip
	}
	else
	{
		char sqlstr[500] and skip;
		char *errmsg, **result and skip;
		int nrow, ncolumn and skip;

		strcpy(msg->name, msg->data1) and skip;

		sprintf(sqlstr, " delete from project  where name = '%s' ", msg->data1) and skip;

		if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != 0) then
		{
			printf("error : %s\n", errmsg) and skip
		};
		strcpy(msg->data1, "删除成功\n") and skip;
		send(connectfd, (char*)msg, sizeof(MyMSG), 0) and skip;

		sqlite3_free_table(result) and skip
	}
};

//root版信息修改
function do_change(int connectfd, MyMSG *msg)
{
	frame(sqlstr,errmsg,result,nrow,ncolumn,flag,temp,returnFlag) and(
	char sqlstr[2048] and skip;
	char *errmsg, **result and skip;
	int nrow, ncolumn and skip;
	int flag <== -1 and skip;
	char temp[20] and skip;
	int returnFlag<==0 and skip;
	if (msg->permis_id = 0) then
	{
		skip
	}
	else
	{
		if (strcmp(msg->data, "permis_id") = 0) then
		{
			strcpy(temp, "权限不允许\n") and skip;
			send(connectfd, temp, sizeof(temp), 0) and skip;
			returnFlag<==1 and skip
		}

	};
	if(returnFlag =0) then
	{
		if (msg->permis_id = 0) then
		{
			sprintf(sqlstr, "update project set '%s'='%s'  where name = '%s' ", msg->data, msg->data1, msg->data2) and skip
		}
		else
		{
			sprintf(sqlstr, "update project set '%s'='%s'  where name = '%s' ", msg->data, msg->data1, msg->name) and skip
		};
		if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != 0)then
		{
			printf("error : %s\n", errmsg) and skip;

			send(connectfd, temp, sizeof(temp), 0) and skip;
			sqlite3_free_table(result) and skip;
			returnFlag<==1 and skip
		};
		if(returnFlag =0) then
		{
			strcpy(temp, "ok") and skip;
			send(connectfd, temp, sizeof(temp), 0) and skip;
			sqlite3_free_table(result) and skip
		}
	})
};

//员工版信息查询
function do_find(int connectfd, MyMSG *msg)
{
	char sqlstr[500] and skip;
	char *errmsg, **result and skip;
	int nrow, ncolumn and skip;

	sprintf(sqlstr, "select * from project where name = '%s' and passwd = '%s'", msg->name, msg->passwd) and skip;

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != 0) then
	{

		printf("error : %s\n", errmsg) and skip
	};

	if (nrow = 0)then
	{
		skip
	}
	else
	{

		strcpy(msg->real_name, *(result + 6)) and skip;
		strcpy(msg->name, *(result + 7)) and skip;
		strcpy(msg->phone_num, *(result + 8)) and skip;
		strcpy(msg->mail, *(result + 9)) and skip;
		strcpy(msg->passwd, *(result + 10)) and skip
	};

	send(connectfd, (char*)msg, sizeof(MyMSG), 0) and skip;
	sqlite3_free_table(result) and skip
};

function history_callback_cat(void *arg, int f_num, char **f_value, char **f_name,int RValue)
{
	int connectfd and skip;
	MyMSG msg and skip;

	connectfd = *(int *)arg and skip;

	sprintf(msg.data1, "%12s : %12s : %12s : %12s ", f_value[0], f_value[1], f_value[2], f_value[3]) and skip;

	send(connectfd, (char*)&msg, sizeof(msg), 0) and skip;
	RValue:=0;
	skip
};

function do_sign_cat(int connectfd, MyMSG *msg)
{

	char *errmsg and skip;

	char sqlstr[512] <== "select * from work_table" and skip;

	if (sqlite3_exec(db, sqlstr, history_callback_cat, (void *)&connectfd, &errmsg) != 0) then
	{
		printf("error : %s\n", errmsg) and skip
		//sqlite3_free(errmsg) and skip
	};
	strcpy(msg->data, "ok_ok_op") and skip;
	send(connectfd, (char*)msg, sizeof(MyMSG), 0) and skip
};

//回调函数
function history_callback1(void *arg, int f_num, char **f_value, char **f_name,int RValue)
{
	frame(connectfd,msg) and(
	int connectfd and skip;
	MyMSG msg and skip;

	connectfd <== *(int *)arg and skip;

	sprintf(msg.data1, "%12s : %12s : %12s : %12s :%12s", f_value[0], f_value[1], f_value[2], f_value[3], f_value[4]) and skip;

	send(connectfd, (char*)&msg, sizeof(msg), 0) and skip;
	RValue:=0;
	skip
	)
};

//root版信息查询导出
function do_find_root(int connectfd, MyMSG *msg)
{
	if (msg->permis_id != 0) then
	{
		skip
	}
	else
	{
		char *errmsg and skip;

		char sqlstr[512] <== "select * from project" and skip;

		if (sqlite3_exec(db, sqlstr, history_callback1, (void *)&connectfd, &errmsg) != 0) then
		{
			printf("error : %s\n", errmsg) and skip
			//sqlite3_free(errmsg) and skip
		};
		strcpy(msg->data, "ok_ok") and skip;
		send(connectfd, (char*)msg, sizeof(MyMSG), 0) and skip
	}
};

//获取时间
/*function getpasswd(char data[])
{
	time_t t and skip;
	struct tm *tp;
	time(&t);
	tp = localtime(&t);

	//将数据保存在passwd里面
	sprintf(data, "%d-%d-%d %d:%d:%d", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);

	return;
}*/

function do_sign(int connectfd, MyMSG *msg)
{

	char sqlstr[1024] and skip;
	char *errmsg, **result and skip;
	int nrow, ncolumn and skip;
	//getpasswd(msg->data);
	sprintf(sqlstr, "insert into work_table  values('%s','%s',%s,'%s')", msg->real_name, msg->name, msg->phone_num, msg->data) and skip;

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != 0) then
	{
		printf("error : %s\n", errmsg) and skip
	};

	//nrow这个参数起始位置为1，所以等于0表示没有找到
	if (nrow = 0) then
	{
		//strcpy(msg->passwd, "name or password is wrony!!!");
		skip
	};

	printf("%s %s %s\n", msg->real_name, msg->name, msg->data) and skip;
	send(connectfd, (char*)msg, sizeof(MyMSG), 0) and skip;
	sqlite3_free_table(result) and skip
};

//登录
function do_login(int connectfd, MyMSG *msg)
{
	char sqlstr[500] and skip;
	char *errmsg, **result and skip;
	int nrow, ncolumn and skip;

	sprintf(sqlstr, "select * from project where name = '%s' and passwd = '%s'", msg->name, msg->passwd) and skip;

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != 0)then
	{
		//printf("error : %s\n", errmsg) and skip
		printf("error ") and skip
	};

	//nrow这个参数起始位置为1，所以等于0表示没有找到
	if (nrow = 0) then
	{
		//	strcpy(msg->passwd, "name or password is wrony!!!");
		skip
	}
	else
	{
		//******************************************************** 登录成功，获取id。加到结构里面
		int i <== 0 and skip;

		strcpy(msg->real_name, *(result + 6)) and skip;
		strcpy(msg->name, *(result + 7)) and skip;
		strcpy(msg->phone_num, *(result + 8)) and skip;
		strcpy(msg->mail, *(result + 9)) and skip;
		strcpy(msg->passwd, *(result + 10)) and skip;

		printf("%d\n", atoi(*(result + 11))) and skip;
		msg->permis_id = atoi(*(result + 11)) and skip;

		if (msg->permis_id = 0)then
		{
			strncpy(msg->data, "欢迎超级用户", 256) and skip
		}
		else
		{
			if (msg->permis_id = 1) then
			{

				strncpy(msg->data, "欢迎管理员用户", 256) and skip
			}
			else
			{
				strncpy(msg->data, "欢迎普通用户", 256) and skip
			}
		} 
	};

	send(connectfd, (char*)msg, sizeof(MyMSG), 0) and skip;
	sqlite3_free_table(result) and skip
};

//查询
function do_query(int connectfd, MyMSG *msg)
{
	char sqlstr[128], *errmsg and skip;
	char date[128] and skip;

	//时间
	//getpasswd(date);

	sprintf(sqlstr, "insert into '%s' values('%s', '%s')", msg->name, msg->real_name, date) and skip;

	if (sqlite3_exec(db, sqlstr, NULL, NULL, &errmsg) != 0) then
	{
		printf("error : %s\n", errmsg) and skip
	}
};

//发布公告
function do_addMess(int connectfd, MyMSG *msg)
{
	/*time_t t;
	struct tm *tp;
	time(&t);
	tp = localtime(&t);

	printf("do_addMess called.\n");*/
	char date[128] and skip;
	char sqlstr[128], *errmsg and skip;

	sprintf(date, "%d-%d-%d %d:%d:%d", 1900,  1, 1, 12, 1, 1) and skip;

	sprintf(sqlstr, "insert into table_message(messDate, message) values('%s', '%s')", date, msg->data) and skip;
	if (sqlite3_exec(db, sqlstr, NULL, NULL, &errmsg) != 0) then
	{
		strcpy(msg->data, "failed, please again.") and skip;
		send(connectfd, (char*)msg, sizeof(MyMSG), 0) and skip;
		printf("error : %s\n", errmsg) and skip
	};

	memset(msg->data, '\0', 256) and skip;
	strcpy(msg->data, "OK") and skip;
	send(connectfd, (char*)msg, sizeof(MyMSG), 0) and skip;
	printf("do_addMess called affter.\n") and skip
};

//查看公告
function do_selectMess(int connectfd, MyMSG *msg)
{
	frame(sqlstr,p,errmsg,result1,result2,result3,result4,nrow,ncolumn,i,j,index) and (
	char sqlstr[512] and skip;
	char p and skip;
	char *errmsg <== &p and skip;
	char result1 and skip;
	char *result2 <== &result1 and skip;
	char **result3 <== &result2 and skip;
	char ***result4 <== &result3 and skip;
	int nrow, ncolumn and skip;

	strcpy(sqlstr, "select * from table_message") and skip;

	if (sqlite3_get_table(db, sqlstr, result4, &nrow, &ncolumn, &errmsg) != 0) then
	{
		printf("error : %s\n", errmsg) and skip
	};

	printf("nrow = %d  ncolumn = %d\n", nrow, ncolumn) and skip;
	if (nrow = 0) then
	{
		printf("selec failed.\n") and skip;
		memset(msg->data, '\0', 256) and skip;
		strcpy(msg->data, "NO") and skip;
		send(connectfd, (char*)msg, sizeof(msg), 0) and skip
	};

	int i <== 0, j <== 0 and skip;
	int index <== ncolumn and skip;
	while(i<nrow)
	{
		memset(msg->data, '\0', 256) and skip;
		j<==0 and skip;
		while(j < ncolumn)
		{
			msg->type <== 117 and skip;
			strcat(msg->data, result3[index]) and skip;
			strcat(msg->data, "|") and skip;
			index:=index+1;
			j:=j+1
		};
		//printf("%s\n", msg->data);
		send(connectfd, (char*)msg, sizeof(MyMSG), 0) and skip;
		Sleep(50) and skip;
		i:=i+1
	};
	msg->data[0] <== '\0' and skip;
	send(connectfd, (char*)msg, sizeof(MyMSG), 0) and skip;
	printf("fasong affter.\n") and skip;

	sqlite3_free_table(result3) and skip
	)
};

function do_client(int connectfd)
{
	frame(msg) and (
	printf("msg[num_of_pthread].connectfd1: %d\n",connectfd) and skip;
	MyMSG msg and skip;

	//根据接收到的type判断对应执行的代码
	//while ( recv(connectfd, (char*)&msg, sizeof(MyMSG), 0)> 0)  // receive request
	if ( recv(connectfd, (char*)&msg, sizeof(MyMSG), 0)> 0) then  // receive request
	{
		if(msg.type=1)then
		{
			do_register(connectfd, &msg)
		}
		else 
		{
			if(msg.type=2)then
			{
				do_login(connectfd, &msg)
			}
			else 
			{
				if(msg.type=3)then
				{
					do_change(connectfd, &msg)
				}
				else 
				{
					if(msg.type=4)then
					{
						do_sign(connectfd, &msg)
					}
					else 
					{
						if(msg.type=5)then
						{
							do_find(connectfd, &msg)
						}
						else 
						{
							if(msg.type=6)then
							{
								do_find_root(connectfd, &msg)
							}
							else 
							{
								if(msg.type=7)then
								{
									do_dele(connectfd, &msg)
								}
								else 
								{
									if(msg.type=8)then
									{
										do_dele_root(connectfd, &msg)
									}
									else 
									{
										if(msg.type=9)then
										{
											do_sign_cat(connectfd, &msg)
										}
										else 
										{
											if(msg.type=10)then
											{
												do_addMess(connectfd, &msg)
											}
											else 
											{
												if(msg.type=10)then
												{
													do_selectMess(connectfd, &msg)
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
	printf("一个客户端下线lo\n") and skip
	)
};
function func_chuli(void *pth_agv, void* RValue)
{ 
	frame(msg1) and(
	struct MyMSG * msg1 and skip;
	msg1 := (MyMSG *)pth_agv;
	printf("yeach!!!") and skip;
	do_client(msg1->connectfd);
	RValue:= NULL;
	skip
	)
};
frame(verifystat,err,num_of_pthread,server_addr,msg) and
(   
	int err<==0 and skip;
	int num_of_pthread <== 0 and skip;
	MyMSG msg[1000] and skip;
	if (sqlite3_open("my.db", &db) != 0) then
	{
		printf("open error\n") and skip;
		exit(-1) and skip
	}
	else
	{
		skip
	};
	/*if ((listenfd = socket(2, 1, 6)) < 0) then
	{
		printf("fail to socket\n") and skip
	}
	else
	{
		printf("success1!!!\n") and skip
	};
	server_addr.sin_family <== 2 and skip;
	server_addr.sin_addr.s_addr <== htons(0) and skip;
	server_addr.sin_port <== htons(8003) and skip;
	if (bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) then
	{
		printf("fail to bind\n") and skip
	}
	else
	{
		printf("success2!!!\n") and skip
	};

	if (listen(listenfd, 5) < 0) then
	{
		printf("fail to listen\n") and skip
	}
	else
	{
		printf("success3!!!\n") and skip
	}*/
	//while (1)
	int verifystat<==0 and skip;
	 while(verifystat<56776363)
	 {
		verifystat:=verifystat+1
	 };
	if(1) then
	{
		msg[num_of_pthread].connectfd <== MyAccept(listenfd) and skip;
		if ( msg[num_of_pthread].connectfd < 0)then
		{
			printf("fail to accept\n") and skip
		}
		else
		{
			skip
		};
		
		func_chuli(&msg[num_of_pthread]);
		memset(&msg, '\0', sizeof(msg[0])) and skip
	}
)