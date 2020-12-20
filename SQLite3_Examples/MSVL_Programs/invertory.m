/* </
define p:sqlite3_mprintf_call=1;
define q:sqlite3_free_call=1;
alw(p->som(q))
/>*/
</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>
frame(loopTime) and (
int loopTime<==0 and skip;
function callback1(void *data, int argc, char **argv, char **azColName,int RValue)
{
	RValue:=1;
	skip
};

function callback(void *data, int argc, char **argv, char **azColName,int RValue){
	frame(i) and (
	int i<==0 and skip;
	while(i<argc)
	{
		if(argv[i]=NULL) then
		{
			printf("%s: %s\n", azColName[i], "NULL")
		}
		else
		{
			printf("%s: %s\n", azColName[i], argv[i])
		};
		i:=i+1
	};
	printf("\n") and skip;
	RValue:=1;
	skip
	)
};

function validate(char *a,int RValue)
{
	frame(x,flag) and(
	int x<==0 and skip;
	int flag<==0 and skip;
	while(x<strlen(a) AND flag=0)
	{
		if (!isdigit(a[x])) then
		{
			flag<==1 and skip;
			RValue:=1
		};
		x:=x+1	 
	};
	if(flag=0) then
	{
		RValue:=0
	}
	)
};
function addItem() {
	frame(zErrMsg,rc,sql,choice,itemname,price,flag) and
	(
		char *zErrMsg <== 0 and skip;
		int rc and skip;
		char *sql and skip;
		char choice and skip;
		char itemname[512] and skip;
		char price[512] and skip;

		rc <== sqlite3_open("inventory.db", &db) and skip;
		if (rc) then
		{
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db)) and skip
		}
		else
		{
			int flag <== 0 and skip;
			while (flag = 0)
			{
				printf("Item Name: ") and skip;
				//gets(itemname) and skip;
				strcpy(itemname,"book") and skip;//自动输入"book"
				itemname[strlen(itemname) - 1] <== '\0' and skip;
				flag <== 1 and skip;//不用循环了
				if (itemname[0] = '\0') then
				{
					flag <== 0 and skip//赋为0，还得循环
				}
			};
			flag <== 0 and skip;
			while (flag = 0)
			{
				printf("Price: ") and skip;
				//if (gets(price) != NULL) then
				strcpy(price,"1") and skip;
				if(price != NULL) then
				{
					char *chk and skip;
					double tmp <== strtod(price, &chk) and skip;
					//price[strlen(price) - 1] <== '\0' and skip;
					if (price[0] = '\0') then
					{
						printf("Please input a valid price\n") and skip;
						flag <== 0 and skip
					}
					else
					{
						if (isspace(*chk) OR *chk = 0) then
						{
							flag <== 1 and skip
						}
						else {
							fprintf(stderr, "%s is not a valid valid price\n", price) and skip;
							flag <== 0 and skip
						}
					}

				}
			};
			rc <== sqlite3_exec(db, "create table STOCK_ITEM (ITEM_NAME CHAR(512),PRICE CHAR(512))", NULL, 0, &zErrMsg) and skip;
			sql <== sqlite3_mprintf("INSERT INTO STOCK_ITEM (ITEM_NAME,PRICE) values ('%s','%s');", itemname, price) and skip;
			rc <== sqlite3_exec(db, sql, callback1, 0, &zErrMsg) and skip;
			if (rc != 0) then
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg) and skip;
				sqlite3_free(zErrMsg) and skip
			}
			else 
			{
				fprintf(stdout, "ITEM SUCCESSFULLY ADDED!") and skip
			};
			Display()
		}
	)
};

function Display()
{
	frame(flag,choice) and(
	int flag <== 0 and skip;
	char choice and skip;
	while (flag = 0)
	{
		printf("\n\nWould you like to add another item? (Y/N) ") and skip;
		//scanf(" %c", &choice) and skip;
		choice<=='N' and skip;
		if (choice = 'y' OR choice = 'Y') then
		{
			addItem();
			flag <== 1 and skip
		}
		else
		{
			if (choice = 'n' OR choice = 'N') then
			{
				main1();
				flag <== 1 and skip
			}
		}
	}
	)
};

function getItemDetails(int itemno) {
	frame(zErrMsg,con,data,choice,str1,str2,num) and (
	char *zErrMsg <== 0 and skip;
	int con and skip;
	char* data <== NULL and skip;
	char choice and skip;
	char* str1 and skip;
	char str2[512] and skip;
	int num <== itemno and skip;
	str1 <== "SELECT * FROM STOCK_ITEM WHERE ITEM_NO =" and skip;
	itoa(num, str2, 10) and skip;
	char * sql <== (char *)malloc(1 + strlen(str1) + strlen(str2)) and skip;
	strcpy(sql, str1) and skip;
	strcat(sql, str2) and skip;

	con <== sqlite3_open("inventory.db", &db) and skip;
	if (con) then
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db)) and skip
	}
	else
	{
		fprintf(stderr, " -----------------\n") and skip;
		fprintf(stderr, "|   ITEM DETAILS  |\n") and skip;
		fprintf(stderr, " -----------------\n") and skip;
		con <== sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg) and skip;
		if (con != 0) then
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg) and skip;
			sqlite3_free(zErrMsg) and skip
		}
	}
)
};

function getStockQty(int itemno,int RValue) 
{
	frame(con,con2,stock,str1,str2,zErrMsg,num) and(
	int con and skip;
	int con2 and skip;
	int stock and skip;
	char* str1 and skip;
	char str2[512] and skip;
	char *zErrMsg <== 0 and skip;
	int num <== itemno and skip;
	str1 <== "SELECT QTY FROM STOCK_ITEM WHERE ITEM_NO =" and skip;
	itoa(num, str2, 10) and skip;
	char * sql <== (char *)malloc(1 + strlen(str1) + strlen(str2)) and skip;
	strcpy(sql, str1) and skip;
	strcat(sql, str2) and skip;

	con <== sqlite3_open("inventory.db", &db) and skip;
	if (con != 0) then 
	{ 
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db)) and skip;
		sqlite3_close(db) and skip;
		RValue:=1;
		skip 
	}
	else
	{	
		con <== sqlite3_prepare_v2(db, sql, -1, &stmt, 0) and skip;
		if (con != 0) then
		{ 
			fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db)) and skip;
			sqlite3_close(db) and skip;
			RValue:=1;
			skip
		}
		else
		{
			con <== sqlite3_step(stmt) and skip;
			if (con = 100) then 
			{
				stock <== sqlite3_column_int(stmt, 0) and skip
			};
			sqlite3_finalize(stmt) and skip;
			RValue:=stock;
			skip
		}
	}
)
};

function stockIn() 
{
	frame(itemno, input1, temp, con, res, qty, stock, result,buffer,choice,date,zErrMsg,insert_stock_logs,update_stock_quantity,status,sql,flag) and(
	int itemno, input1, temp, con, res, qty, stock, result and skip;
	char buffer[512] and skip;
	char choice and skip;
	char *date <== "2017-9-25" and skip;
	char *zErrMsg <== 0 and skip;
	char *insert_stock_logs and skip;
	char *update_stock_quantity and skip;
	char* status <== "STOCK-IN" and skip;
	char * sql <== "SELECT ITEM_NO FROM STOCK_ITEM" and skip;
	con <== sqlite3_open("inventory.db", &db) and skip;

	if (con != 0) then
	{ 
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db)) and skip;
		sqlite3_close(db) and skip
	};

	con <== sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) and skip;
	if (con != 0) then 
	{ 
		printf("Failed to fetch data from database\n\r") and skip;
		sqlite3_close(db) and skip
	};

	printf("\nInput Item No.: ") and skip;

	if (gets(buffer) != NULL) then
	{
		if (validate(buffer) = 0) then 
		{
			input1 <== atoi(buffer) and skip
		}
	};
	itemno <== input1 and skip;

	int flag <== 0 and skip;
	con <== sqlite3_step(stmt) and skip;
	if (con = 100) then
	{
		res <== sqlite3_column_int(stmt, 0) and skip;
		if (res = itemno) then
		{
			getItemDetails(itemno);
			flag <== 1
		}
	};
	while (con = 100 AND flag = 0)
	{
		con <== sqlite3_step(stmt) and skip;
		if (con = 100) then
		{
			res <== sqlite3_column_int(stmt, 0) and skip;
			if (res = itemno) then
			{
				getItemDetails(itemno);
				flag <== 1
			}
		}
	};

	printf("\nInput Quantity: ") and skip;
	scanf("%d", &qty) and skip;

	insert_stock_logs <== sqlite3_mprintf("INSERT INTO STOCK_LOGS (ITEM_NO,STATUS,DATE,QTY) values ('%d','%s','%s','%d');", itemno, status, date, qty) and skip;
	con <== sqlite3_exec(db, insert_stock_logs, callback1, 0, &zErrMsg) and skip;
	if (con != 0) then
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg) and skip;
		sqlite3_free(zErrMsg) and skip
	}
	else
	{
		fprintf(stdout, "STOCKS SUCCESSFULLY ADDED!") and skip
	};
	stock <== getStockQty(itemno) and skip;
	result <== (stock + qty) and skip;
	update_stock_quantity <== sqlite3_mprintf("UPDATE STOCK_ITEM SET QTY = %d WHERE ITEM_NO = %d ;", result, itemno) and skip;
	con <== sqlite3_exec(db, update_stock_quantity, callback1, 0, &zErrMsg) and skip;
	if (con != 0) then
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg) and skip;
		sqlite3_free(zErrMsg) and skip
	}
	else
	{
		skip
	};
	getItemDetails(itemno);
	sqlite3_close(db) and skip;
	main1()
)
};

function stockOut() {
	frame(itemno,con,res,qty,stock,result,choice,date,zErrMsg,insert_stock_logs,update_stock_quantity,status,item,sql,flag) and(
	int itemno and skip;
	int con and skip;
	int res and skip;
	int qty and skip;
	int stock and skip;
	int result and skip;
	char choice and skip;
	char *date <== "2017-9-25" and skip;
	char *zErrMsg <== 0 and skip;
	char *insert_stock_logs and skip;
	char *update_stock_quantity and skip;
	char* status <== "STOCK-OUT" and skip;
	char *item and skip;

	char * sql <== "SELECT ITEM_NO FROM STOCK_ITEM" and skip;
	con <== sqlite3_open("inventory.db", &db) and skip;

	if (con != 0) then 
	{ 
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db)) and skip;
		sqlite3_close(db) and skip
	};

	con <== sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) and skip;
	if (con != 0) then
	{ 
		printf("Failed to fetch data from database\n\r") and skip;
		sqlite3_close(db) and skip
	};

	printf("Input Item No.: ") and skip;
	scanf("%d", &itemno) and skip;
	int flag <== 0 and skip;

	con <== sqlite3_step(stmt) and skip;
	if (con = 100) then 
	{ 
		res <== sqlite3_column_int(stmt, 0) and skip;
		if (res = itemno) then
		{
			getItemDetails(itemno);
			flag <== 1 and skip
		}
	};
	while (con = 100 AND flag = 0)
	{
		con <== sqlite3_step(stmt) and skip;
		if (con = 100) then 
		{ 
			res <== sqlite3_column_int(stmt, 0) and skip;
			if (res = itemno) then
			{
				getItemDetails(itemno);
				flag <== 1 and skip
			}
		}
	};

	printf("\nInput Quantity: ") and skip;
	scanf("%d", &qty) and skip;

	insert_stock_logs <== sqlite3_mprintf("INSERT INTO STOCK_LOGS (ITEM_NO,STATUS,DATE,QTY) values ('%d','%s','%s','%d');", itemno, status, date, qty) and skip;
	con <== sqlite3_exec(db, insert_stock_logs, callback1, 0, &zErrMsg) and skip;
	if (con != 0) then
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg) and skip;
		sqlite3_free(zErrMsg) and skip
	}
	else
	{
		fprintf(stdout, "STOCKS SUCCESSFULLY ADDED!") and skip
	};
	stock <== getStockQty(itemno) and skip;
	result <== (stock - qty) and skip;
	update_stock_quantity <== sqlite3_mprintf("UPDATE STOCK_ITEM SET QTY = %d WHERE ITEM_NO = %d ;", result, itemno) and skip;
	/* Execute SQL statement */
	con <== sqlite3_exec(db, update_stock_quantity, callback1, 0, &zErrMsg) and skip;
	if (con != 0) then
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg) and skip;
		sqlite3_free(zErrMsg) and skip
	}
	else
	{
		skip
	};
	getItemDetails(itemno);
	printf("\n\nWould you like to stock another item? (Y/N) ") and skip;
	scanf(" %c", &choice) and skip;
	sqlite3_close(db) and skip;
	main1()
)
};

function viewReport() {
	frame(rc,sql,data,choice,zErrMsg) and(
	char *zErrMsg <== 0 and skip;
	int rc and skip;
	char *sql and skip;
	char* data <== NULL and skip;
	char choice and skip;

	rc <== sqlite3_open("inventory.db", &db) and skip;
	if (rc) then
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db)) and skip
	}
	else
	{
		fprintf(stderr, " -----------------\n") and skip;
		fprintf(stderr, "| LIST OF STOCKS  |\n") and skip;
		fprintf(stderr, " -----------------\n") and skip;
		sql <== sqlite3_mprintf("SELECT * FROM STOCK_LOGS") and skip;
		rc <== sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg) and skip;
		if (rc != 0) then
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg) and skip;
			sqlite3_free(zErrMsg) and skip
		};
		sqlite3_close(db) and skip;

		printf("------------------------\n") and skip;
		printf("[1] Back to main menu\n") and skip;
		printf("[0] Exit Program: ") and skip;
		scanf(" %c", &choice) and skip;
		if(choice=1)then
		{
			main1()
		}
		else
		{
			skip
		}
	}
)	
};

function viewStocks() {
	frame(zErrMsg,rc,sql,data,choice) and(
	char *zErrMsg <== 0 and skip;
	int rc and skip;
	char *sql and skip;
	char* data <== NULL and skip;
	char choice and skip;

	rc <== sqlite3_open("inventory.db", &db) and skip;
	if (rc) then
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db)) and skip
	}
	else
	{
		fprintf(stderr, " -----------------\n") and skip;
		fprintf(stderr, "| LIST OF STOCKS  |\n") and skip;
		fprintf(stderr, " -----------------\n") and skip;
		sql <== sqlite3_mprintf("SELECT * FROM STOCK_ITEM") and skip;
		rc <== sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg) and skip;
		if (rc != 0) then
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg) and skip;
			sqlite3_free(zErrMsg) and skip
		};
		sqlite3_close(db) and skip;

		printf("------------------------\n") and skip;
		printf("[1] Back to main menu\n") and skip;
		printf("[0] Exit Program: ") and skip;
		scanf(" %c", &choice) and skip;
		if(choice=1)then
		{
			main1()
		}
		else
		{
			skip
		}
	}
)
};

function main1()
{
	frame(i,buffer,flag,verifystat) and(
	int i<==0 and skip;
	char buffer[512] and skip;
	int flag <== 0 and skip;
	int verifystat<==0 and skip;
	 while(verifystat<414500)
	 {
		verifystat:=verifystat+1
	 };
	while (flag = 0 AND loopTime<10)
	{
		printf(" ---------------------------------- \n") and skip;
		printf("|                                  |\n") and skip;
		printf("|             INVENTORY            |\n") and skip;
		printf("|              SYSTEM              |\n") and skip;
		printf("|                                  |\n") and skip;
		printf(" ---------------------------------- \n\n\n") and skip;
		printf("[1] Item Entry\n") and skip;
		printf("[2] View Stocks\n") and skip;
		printf("[3] Stock-in\n") and skip;
		printf("[4] Stock-out\n") and skip;
		printf("[5] View Report\n") and skip;
		printf("[0] Exit Program\n\n") and skip;
		printf("Enter Choice: ") and skip;
		//if (gets(buffer) != NULL) then //这句需要用户自己输入，改成自动输入，
		strcpy(buffer,"1") and skip;
		loopTime:=loopTime+1;
		if (buffer != NULL) then
		{
			i<==strlen(buffer) and skip;
			if (validate(buffer) = 0) then 
			{
				i <== atoi(buffer) and skip;
				if (i = 1) then
				{
					addItem()
				}
				else
				{
					if (i = 2) then
					{
						viewStocks()
					}
					else 
					{
						if (i = 3) then
						{
							stockIn()
						}
						else
						{
							if (i = 4) then
							{
								stockOut()
							}
							else
							{
								if (i = 5) then
								{
									viewReport()
								}
								else
								{
									if (i = 0) then
									{
										flag <== 1 and skip
									}
								}
							}
						} 
					}
				} 
			}
		}
	}
)
};


	main1()
)

