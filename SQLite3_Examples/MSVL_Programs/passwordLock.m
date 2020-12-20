 </
define p:sqlite3_get_table_call=1;
define q:sqlite3_free_table_call=1;
alw(p->som(q))
/>
struct MSG{
	char name[128] and
	char pass[128]
};

function usr_delete(MSG* msg)
{
	char* errmsg and skip;
	char sql[128] and skip;

	sprintf(sql, "delete from usr where name='%s'", msg->name) and skip;

	if (sqlite3_open("pass.db", &db) != 0)then
	{
		printf("open failed:%s\n", sqlite3_errmsg(db)) and skip
	}
	else
	{
		if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0) then
		{
			printf("delete failed:%s\n", errmsg) and skip;
			sqlite3_free(errmsg) and skip;
			printf("%s already exist!\n", msg->name) and skip
		}
		else
		{
			printf("delete success!\n") and skip
		};
		sqlite3_close(db) and skip
	}
};

function encode(char str[], int n)
{
	frame(c,i) and (
	char c and skip;
	int i<==0 and skip;
	while(i<strlen(str))
	{
		c <== str[i] and skip;
		if ((c >= 'a') AND (c <= 'z')) then
		{
			if ((c + n % 26) <= 'z') then
			{
				str[i] <== (char)(c + n % 26) and skip
			}
			else
			{
				str[i] <== (char)('a' + ((n - ('z' - c) - 1) % 26)) and skip
			}
		}
		else
		{
			if ((c >= 'A') AND (c <= 'Z')) then
			{
				if ((c + n % 26) <= 'Z') then
				{
					str[i] <== (char)(c + n % 26) and skip
				}
				else
				{
					str[i] <== (char)('A' + ((n - ('Z' - c) - 1) % 26)) and skip
				}
			}	
			else
			{
				str[i] <== c and skip
			}
		};
		if ((c >= '0') AND (c <= '9')) then
		{
			if ((c + n % 9) <= '9') then
			{
				str[i] <== (char)(c + n % 9) and skip
			}
			else
			{
				str[i] <== (char)('0' + ((n - ('9' - c) - 1) % 9)) and skip
			}
		};
		i:=i+1
	};
	printf("\n out:") and skip;
	puts(str) and skip
	)
};

function usr_jiemi(MSG* msg)
{
	frame(str,i) and (
	char str[20] and skip;
	int i and skip;
	printf("please input you want to jiemi:\n") and skip;
	scanf("%s", str) and skip;
	i<==1 and skip;
	while(i<=25)
	{
		printf("%d", i) and skip;
		encode(str, 1);
		i:=i+1
	}
	)
};

function usr_jiami(MSG* msg)
{
	frame(result,row,column,errmsg,sql,c,i,n,str) and (
	printf("name:") and skip;
	scanf("%s", msg->name) and skip;
	printf("pass:") and skip;
	scanf("%s", msg->pass) and skip;

	char ** result and skip;
	int row, column and skip;
	char* errmsg and skip;
	char sql[128] and skip;

	sprintf(sql, "select * from usr where name='%s' and pass='%s'", msg->name, msg->pass) and skip;
	if (sqlite3_open("pass.db", &db) != 0) then
	{
		printf("open failed:%s\n", sqlite3_errmsg(db)) and skip
	}
	else
	{
		if (sqlite3_get_table(db, sql, &result, &row, &column, &errmsg) != 0) then
		{
			printf("select failed:%s\n", errmsg) and skip;
			sqlite3_free(errmsg) and skip;
			sqlite3_close(db) and skip
		}
		else
		{
			if (row = 1) then
			{
				char c and skip;
				int i, n and skip;
				char str[128] and skip;
				strcpy(str, msg->pass) and skip;
				printf("plaese enter the number of bits:") and skip;
				scanf("%d", &n) and skip;
				i<==0 and skip;
				while(i<strlen(str))
				{
					c <== str[i] and skip;
					if (c >= 'a' AND c <= 'z') then
					{
						if (c + n % 26 <= 'z') then
						{
							str[i] <== (char)(c + n % 26) and skip
						}
						else
						{
							str[i] <== (char)('a' + ((n - ('z' - c) - 1) % 26)) and skip
						}
					}
					else
					{
						if(c >= 'A' AND c <= 'Z') then
						{
							if (c + n % 26 <= 'Z') then
							{
								str[i] <== (char)(c + n % 26) and skip
							}
							else
							{
								str[i] <== (char)('A' + ((n - ('Z' - c) - 1) % 26)) and skip
							}
						}
						else
						{
							str[i] <== c and skip
						}
					};
					if (c >= '0' AND c <= '9') then
					{
						if (c + n % 9 <= '9') then
						{
							str[i] <== (char)(c + n % 9) and skip
						}
						else
						{
							str[i] <== (char)('0' + ((n - ('9' - c) - 1) % 9)) and skip
						}
					};
					i:=i+1
				};
				strcpy(msg->pass, str) and skip;
				sprintf(sql, "update usr set pass='%s' where name='%s'", msg->pass, msg->name) and skip;
				if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0) then
				{
					printf("jiami failed:%s\n", errmsg) and skip;
					sqlite3_free(errmsg) and skip;
					printf("%s can't find the name!jiami fialed!~~\n", msg->name) and skip
				}
				else
				{
					printf("jiami is success!^_^\n") and skip
				}
			}
			else
			{
				printf("name or pass wrong\n") and skip
			};
			sqlite3_close(db) and skip
		}
	}
	)
};
function usr_register(MSG* msg){
	frame(errmsg,sql) and (
	//printf("name:") and skip;
	//scanf("%s", msg->name) and skip;
	strcpy(msg->name,"yubin") and skip;
	//printf("pass:") and skip;
	//scanf("%s", msg->pass) and skip;
	strcpy(msg->pass,"123456") and skip;

	char* errmsg and skip;
	char sql[128] and skip;

	sprintf(sql, "insert into usr values('%s','%s')", msg->name, msg->pass) and skip;

	if (sqlite3_open("pass.db", &db) != 0) then
	{
		printf("open failed:%s\n", sqlite3_errmsg(db))
	}
	else
	{
		sqlite3_exec(db, "create table usr(name TEXT, pass TEXT)", NULL, NULL, NULL) and skip;
		if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0) then
		{
			printf("insert failed:%s\n", errmsg) and skip;
			sqlite3_free(errmsg) and skip;
			printf("%s already exist!\n", msg->name) and skip
		}
		else
		{
			printf("Register ok!\n") and skip
		};
		//memset(msg, 0, sizeof(MSG)) and skip;
		sqlite3_close(db) and skip
	}
	)
};
function usr_login(MSG* msg,int RValue){
	frame(result,row,column,errmsg,sql) and (
	//printf("name:") and skip;
	//scanf("%s", msg->name) and skip;
	strcpy(msg->name,"yubin") and skip;
	//printf("pass:") and skip;
	//scanf("%s", msg->pass) and skip;
	strcpy(msg->pass,"123456") and skip;

	char ** result and skip;
	int row, column and skip;
	char* errmsg and skip;
	char sql[128] and skip;

	sprintf(sql, "select * from usr where name='%s' and pass='%s'", msg->name, msg->pass) and skip;

	if (sqlite3_open("pass.db", &db) != 0) then
	{
		printf("open failed:%s\n", sqlite3_errmsg(db)) and skip;
		RValue:=-1;
		skip
	}
	else
	{
		if (sqlite3_get_table(db, sql, &result, &row, &column, &errmsg) != 0) then
		{
			printf("select failed:%s\n", errmsg) and skip;
			sqlite3_free(errmsg) and skip;
			sqlite3_close(db) and skip;
			RValue:=-1;
			skip
		}
		else
		{
			if (row = 1) then
			{
				printf("Welcome : Login success ^_^\n") and skip;
				RValue:=1;
				skip
			}
			else
			{
				printf("Name or password wrong!\n") and skip;
				sqlite3_close(db) and skip;
				RValue:=0;
				skip
			}
		}
	}
	)
};


frame(msg,scanfTime) and (
	MSG msg and skip;
	int scanfTime<==1 and skip;

function totalControl(MSG *msg)
{
	frame(n,returnFlag,verifystat) and(
	int n<==0 and skip;
	int returnFlag<==0 and skip;
	int verifystat<==0 and skip;
	 while(verifystat<6000407)
	 {
		verifystat:=verifystat+1
	 };
	while (returnFlag=0)
	{
		printf("***************************************************\n") and skip;
		printf("**** 1-register 2-login 3-jiami 4-jiemi 5-quit ****\n") and skip;
		printf("***************************************************\n") and skip;
		printf("please choose: ") and skip;
		//scanf("%d", &n) and skip;
		if(scanfTime=1)then
		{
			n<==1 and skip
		}
		else
		{
			if(scanfTime=2)then
			{
				n<==2 and skip
			}
			else 
			{
				if(scanfTime=3)then
				{
					n<==5 and skip
				}
			}
		};
		scanfTime:=scanfTime+1;
		if(n=1)then
		{
			usr_register(msg)
		}
		else
		{
			if(n=2) then
			{
				if (usr_login(msg) = 1) then
				{
					logControl(msg)
				}
			}
			else
			{
				if(n=3) then
				{
					usr_jiami(msg)
				}
				else
				{
					if(n=4) then
					{
						usr_jiemi(msg)
					}
					else
					{
						if(n=5) then
						{
							returnFlag<==1 and skip
						}
						else
						{
							printf("input [ 1-3 ]!\n")
						}
					}
				}
			}
		}
	}
	)
};

function logControl(MSG* msg)
{
	frame(n,returnFlag) and(
	int n<==0 and skip;
	int returnFlag<==0 and skip;
	while (returnFlag=0){
		printf("************************************************\n") and skip;
		printf("******** 1.log off   2.quit   3.delete  ********\n") and skip;
		printf("************************************************\n") and skip;
		printf("please choose:") and skip;
		scanf("%d", &n) and skip;
		if(n=1) then
		{
			totalControl(msg)
		}
		else
		{
			if(n=2) then
			{
				usr_delete(msg)
			}
			else
			{
				if(n=3) then
				{
					returnFlag<==1 and skip
				}
				else
				{
					printf("input [1-2]\n") and skip
				}
			}
		}
	}
	)
};

	
	totalControl(&msg)
)