</
define p:sqlite3_get_table_call=1;
define q:sqlite3_free_table_call=1;
alw(p->som(q))
/>

function do_insert(int RValue)
{
	frame(id,name,sec,score,sql,errmsg) and (
	int id and skip;
	char name[32] and skip;
	char sex and skip;
	int score and skip;
	char sql[128] and skip;
	char *errmsg and skip;

	printf("Input id:") and skip;
	scanf("%d", &id) and skip;

	printf("Input name:") and skip;
	scanf("%s", name) and skip;
	getchar() and skip;

	printf("Input sex:") and skip;
	scanf("%c", &sex) and skip;

	printf("Input score:") and skip;
	scanf("%d", &score) and skip;

	sprintf(sql, "insert into stu values(%d, '%s', '%c', %d)", id, name, sex, score) and skip;

	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0) then
	{
		printf("%s\n", errmsg) and skip
	}
	else
	{
		printf("Insert done.\n") and skip
	};
	RValue:=0;
	skip
)
};
function do_delete(int RValue)
{
	frame(id,sql,errmsg) and(
	int id and skip;
	char sql[128]  and skip;
	char *errmsg and skip;

	printf("Input id:") and skip;
	scanf("%d", &id) and skip;

	sprintf(sql, "delete from stu where id = %d", id) and skip;

	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0) then
	{
		printf("%s\n", errmsg) and skip
	}
	else
	{
		printf("Delete done.\n") and skip
	};
	RValue:=0;
	skip
)
};

function do_update(int RValue)
{
	frame(id,sql,name,errmsg) and(
	int id and skip;
	char sql[128] and skip;
	char name[32] <== "zhangsan" and skip;
	char *errmsg and skip;

	printf("Input id:") and skip;
	scanf("%d", &id) and skip;

	sprintf(sql, "update stu set name='%s' where id=%d", name, id) and skip;

	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0) then
	{
		printf("%s\n", errmsg) and skip
	}
	else
	{
		printf("update done.\n") and skip
	};
	RValue:=0;
	skip
)
};


function callback(void *arg, int f_num, char ** f_value, char ** f_name, int RValue)
{
	frame(i) and(
	int i <== 0 and skip;
	while(i<f_num)
	{
		printf("%-8s", f_value[i]) and skip;
		i:=i+1
	};
	putchar(10) and skip;
	RValue:=0;
	skip
)
};

function do_query(int RValue)
{
	frame(errmsg,sql) and (
	char *errmsg and skip;
	char sql[128] <== "select * from stu;" and skip;

	if (sqlite3_exec(db, sql, callback, NULL, &errmsg) != 0) then
	{
		printf("%s", errmsg) and skip
	}
	else
	{
		printf("select done.\n") and skip
	};
	RValue:=0;
	skip
)
};

function do_query1(int RValue)
{
	frame(errmsg,resultp,nrow,ncolumn,i,j,index) and(
	char *errmsg and skip;
	char ** resultp and skip;
	int nrow and skip;
	int ncolumn and skip;

	if (sqlite3_get_table(db, "select * from stu", &resultp, &nrow, &ncolumn, &errmsg) != 0) then
	{
		printf("%s\n", errmsg) and skip;
		RValue:=-1;
		skip
	}
	else
	{
		printf("query done.\n") and skip;
		int i <== 0 and skip;
		int j <== 0 and skip;
		int index <== ncolumn and skip;
		while(j<ncolumn)
		{
			printf("%-10s ", resultp[j]) and skip;
			j:=j+1 
		};
		putchar(10) and skip;
		i<==0 and skip;
		while(i<nrow)
		{
			j<==0 and skip;
			while(j<ncolumn)
			{
				printf("%-10s ", resultp[index]) and skip;
				index:=index+1;
				j:=j+1
			};
			putchar(10) and skip;
			i:=i+1
		};
		//sqlite3_free_table(resultp) and skip;
		RValue:=0;
		skip
	}
)
};

frame(errmsg,n,flag,loopTime,verifystat) and
(
	int loopTime<==0 and skip;
	char *errmsg and skip;
	int n and skip;
	int flag<==0 and skip;
	 int verifystat<==0 and skip;
	 while(verifystat<5736813)
	 {
		verifystat:=verifystat+1
	 };
	if (sqlite3_open("stu.db", &db) != 0) then
	{
		printf("%s\n", sqlite3_errmsg(db)) and skip
	}
	else
	{
		printf("open stu.db success.\n") and skip;
		if (sqlite3_exec(db, "create table if not exists stu(id int, name char , sex char , score int);", NULL, NULL, &errmsg) != 0) then
		{
			printf("%s\n", errmsg) and skip
		}
		else
		{
			printf("Create or open table success.\n") and skip
		};

		while (flag=0 AND loopTime<10)
		{
			loopTime:=loopTime+1;
			printf("********************************************\n") and skip;
			printf("1: insert  2:query  3:delete 4:update 5:quit\n") and skip;
			printf("********************************************\n") and skip;
			printf("Please select:") and skip;
			//scanf("%d", &n);
			n <== 2 and skip;
			if(n=1) then
			{
				do_insert()
			}
			else
			{
				if(n=2) then
				{
					do_query1()
				}
				else
				{
					if(n=3) then
					{
						do_delete()
					}
					else
					{
						if(n=4) then
						{
							do_update()
						}
						else
						{
							if(n=5) then
							{
								printf("main exit.\n") and skip;
								sqlite3_close(db) and skip;
								flag<==1 and skip
							}
							else
							{
								printf("Invalid data n.\n") and skip
							}
							
						}

					}
				}
			}
		}
	}
)


