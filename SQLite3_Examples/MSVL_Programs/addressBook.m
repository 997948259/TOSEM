</
define p:sqlite3_prepare_v2_call=1;
define q:sqlite3_finalize_call=1;
alw(p->som(q))
/>

frame(loopTime) and 
(
int loopTime<==0 and skip;
function pad(char ac, int ai)
{
	frame(i) and(
	if (ai<1) then
	{
		skip
	}
	else
	{
		int i <== 0 and skip;
		while(i<ai)
		{
			putchar(ac) and skip;
			i:=i+1
		}
	}
)
};

function padln(char ac, int ai)
{
	pad(ac, ai);
	printf("\n") and skip
};

function card_to_ord(int ai,char* RValue){
frame(yc,pcr,ilb1_d,returnFlag,pcr1) and(
	if (ai<0) then
	{
		char* pcr1 <== (char*)calloc(20, sizeof(char*))and skip;
		strcpy(pcr1,"Invalid parameter!") and skip;
		RValue:=pcr1
	}
	else
	{
		char yc[20] and skip;
		char* pcr <== (char*)calloc(20, sizeof(char*))and skip;
		int final_d <== ai % 10 and skip;
		int ilb1_d <== (ai / 10) % 10 and skip;
		int returnFlag <== 0 and skip;
		if (ilb1_d = 1) then
		{
			if (final_d = 1 OR final_d = 2 OR final_d = 3) then
			{
				sprintf(yc, "%d%s", ai, "th") and skip;
				strcpy(pcr, yc) and skip;
				returnFlag<==1 and skip;
				RValue:=pcr;
				skip
			}
		};
		if(returnFlag = 0) then
		{
			if(final_d=1)then
			{
				sprintf(yc, "%d%s", ai, "st") and skip
			}
			else
			{
				if(final_d=1)then
				{
					sprintf(yc, "%d%s", ai, "nd") and skip
				}
				else
				{
					if(final_d=1)then
					{
						sprintf(yc, "%d%s", ai, "rd") and skip
					}
					else
					{
						sprintf(yc, "%d%s", ai, "th") and skip
					}
				}
				
			};
			strcpy(pcr, yc) and skip;
			RValue:=pcr;
			skip
		}
	}
)
};

function show_main_menu(){
	frame(yc,ia,flag,verifystat) and (
    padln('=',80);
    pad(' ',26);
    printf("Address Book For Students V1.0\n") and skip;
    pad(' ',70);
    printf("By QGBCS\n") and skip;
    pad('=',80);
    printf("%d Add \n",1) and skip;
    printf("%d Delete\n",2) and skip;
    printf("%d Scan \n",3) and skip;
    printf("%d Find \n",4) and skip;
    printf("%d Sort\n",5) and skip;
    printf("%d Count\n",6) and skip;
    printf("%d EXIT!\n",7) and skip;
	int verifystat<==0 and skip;
	while(verifystat<746000)
	 {
		verifystat:=verifystat+1
	 };
    char yc[2] and skip;
    int ia<==0 and skip;
	int flag<==0 and skip;
    while(flag=0 AND loopTime<10)
	{
		loopTime:=loopTime+1;
        //scanf("%s",yc) and skip;
        //ia<==atoi(yc) and skip;
		ia <== 1 and skip;
        printf("input is %d\n",ia) and skip;
        if(ia<1 OR ia>7) then
		{
            printf("Illegal requests, please retry!\n") and skip;
            show_main_menu()
        }
		else
		{
            flag<==1 and skip
        }
    };
	if(ia=1) then
	{
		add_info();
        show_main_menu()
	}
	else
	{
		if(ia=2) then
		{
			del_info();
			show_main_menu()
		}
		else
		{
			if(ia=4) then
			{
				find_info(-1,"");
				show_main_menu()
			}
			else
			{
				if(ia=3) then
				{
					find_info(0,"%");
					show_main_menu()
				}
				else
				{
					if(ia=5) then
					{
						sort_info();
						show_main_menu()
					}
					else
					{
						if(ia=6) then
						{
							printf("The total number of records is %d\n",sqlite_get_row_count()) and skip;
							show_main_menu()
						}
						else
						{
							if(ia=7) then
							{
								sqlite3_close(gp_sqlite3) and skip;/*****close database !*****/
								printf("Program Exit!\n") and skip
							}
							
						}
						
					}
				}
			}
		}
	}
)
};

/**每条记录回调一次该函数，有多少条就回调多少次**/
function select_callback_list(void * data, int col_count, char ** col_values, char ** col_Name,int RValue)
{
	frame(i) and
	(
		int i<==0 and skip;
		while(i < col_count)
		{
			//printf( "%-12.12s|", col_values[i] == 0 ? "NULL" : col_values[i] ) and skip;
			if(col_values[i] = 0) then
			{
				printf( "%-12.12s|", "NULL" ) and skip
			}
			else
			{
				printf( "%-12.12s|", col_values[i] ) and skip
			};
			i:=i+1
		};
		printf("\n") and skip;
		RValue:=0;
		skip
	)
};

/**每条记录回调一次该函数，有多少条就回调多少次**/
function select_callback(void * data, int col_count, char ** col_values, char ** col_Name,int RValue){

	frame(i) and
	(
		int i<==0 and skip;
		while(i < col_count)
		{
			//printf( "%-12.12s|", col_values[i] == 0 ? "NULL" : col_values[i] ) and skip;
			if(col_values[i] = 0) then
			{
				printf( "%-7s= %s\n", "NULL" ) and skip
			}
			else
			{
				printf( "%-7s= %s\n", col_values[i] ) and skip
			};
			i:=i+1
		};
		extern padln('-',35) and skip;
		RValue:=0;
		skip
	)
};

function sort_info()
{
	frame(yc,ia,ysql,ysql_p,i,icols,pErrMsg,pc,psql) and 
	(
		printf("please select a column to sort:(input a number)\n") and skip;
		printf("1(Sorting by id) \n") and skip;
		printf("2(Sorting by name) \n") and skip;
		pad('-',80);
		char yc[1] and skip;
		char *pc and skip;
		int ia<==0 and skip;
		scanf("%c",&yc) and skip;
		ia<==atoi(yc) and skip;
		ia:=ia-1;/**input is 1-2**/
		//pstmt<==sqlite_get_stmt() and skip;
		char* psql<=="select * from users;" and skip;
		sqlite3_prepare_v2(gp_sqlite3,psql,strlen(psql),&pstmt,NULL) and skip;

		pc<==sqlite3_column_name(pstmt,ia) and skip;
		printf("You selected %d(%s)\n",ia+1,pc) and skip;

		char ysql[50] and skip;
		char ysql_p[]<=={"select * from users order by %s asc;"} and skip;
		sprintf(ysql,ysql_p,pc) and skip;
		pad('*',33);
		printf("Sorting by %-4s",pc) and skip;
		pad('*',32);
		int i<==0 and skip;
		int icols<==sqlite_get_col_count() and skip;
		while(i<icols)
		{
			pc<==sqlite3_column_name(pstmt,i) and skip;
			printf( "%-12s|", pc) and skip;
			i:=i+1
		};
		printf("\n") and skip;
		pad('-',80);
		char * pErrMsg <== 0 and skip;
		sqlite3_exec(gp_sqlite3,ysql, select_callback_list, 0, &pErrMsg) and skip;
		pad('*',36);
		printf("  End  ") and skip;
		padln('*',36)
	)
};

function del_info(){
	frame(pc,check,ysql,ir) and (
    char *pc<==find_info(-1,"") and skip;
    char check  and skip;
	char ysql[50] and skip;
    printf("Are you sure you want to delete above infomation?(y/n)\n") and skip;
    scanf("%c",&check) and skip;
    if(check='y' OR check='Y') then
	{//qgb:testedv
        printf("Input is %c\n",check) and skip;
        sprintf(ysql,"delete from users %s",pc) and skip;
        int ir <== sqlite_exec(ysql) and skip;
		if(ir=0) then
		{
			printf("Delete success!\n") and skip
		}
		else
		{
			printf("Error:Unknown.code=%d \n",ir) and skip
		}
    }
	else
	{
        printf("Input is %c\nDelete abort!\n",check) and skip
    }
)
};

function find_info(int ai_col, char* apc_keyword,int RValue){
	frame(ysql,ysql_part,icols,pcin,pc,ypc,yc,itmp,is_user,i,ia,pErrMsg,yc_return,pcr,psql) and(
    char ysql[50] and skip;
	char ysql_part[100] and skip;
    int icols and skip;
    //pstmt<==sqlite_get_stmt() and skip;
	char* psql<=="select * from users;" and skip;
    sqlite3_prepare_v2(gp_sqlite3,psql,strlen(psql),&pstmt,NULL) and skip;
    icols<==sqlite_get_col_count() and skip;
    strcpy(ysql_part,"select * from users where %s like '%s';") and skip;
	char *pcin and skip;
	char *pc and skip;
	char **ypc <== (char**)malloc(icols*sizeof(char *)) and skip;
	char yc[20] and skip;
    int itmp<==1 and skip;

    if(ai_col>=0 AND ai_col<icols) then
	{
        itmp<==0 and skip
    };
    int is_user<==itmp and skip;
    int i<==0 and skip;
    if(is_user) then
	{
        printf("please select a column to find:(input a number)\n") and skip;
        i<==0 and skip;
		while(i<icols)
		{
            pc<==sqlite3_column_name(pstmt,i) and skip;
            printf("%d(%s)\n",i+1,pc) and skip;
			i:=i+1
        };
        pad('-',80);
        int ia<==0 and skip;
		scanf("%s",yc) and skip;
        ia<==atoi(yc) and skip ;
        ia<==ia-1 and skip;/**input is 1-6**/
        pc<==sqlite3_column_name(pstmt,ia) and skip;
        printf("You selected %d(%s)\n",ia+1,pc) and skip;
        pad('-',80);
        printf("please input keyword:(This parameter supports wildcards '%%'.)\n") and skip;
        pcin<==sql_input_keyword() and skip;
        sprintf(ysql,ysql_part,pc,pcin) and skip
    }/** User input end!**/
    else
	{
        pc<==sqlite3_column_name(pstmt,ai_col) and skip;
        sprintf(ysql,ysql_part,pc,apc_keyword) and skip
    };
    char * pErrMsg <== 0 and skip;
    pad('*',35);
    printf("  Result  ") and skip;
    padln('*',35);
    sqlite3_exec(gp_sqlite3,ysql, select_callback, 0, &pErrMsg) and skip;
    pad('*',35);
    printf("  End  ") and skip;
    padln('*',37);
    if(is_user) then
	{
        //char yc_return[20] and skip;
		//strcpy(yc_return," where %s like '%s';") and skip;
        sprintf(ysql," where %s like '%s';",pc,pcin) and skip;
        char* pcr<==(char*)calloc(50,sizeof(char*)) and skip;
        strcpy(pcr,ysql) and skip;
		RValue:=pcr;
		skip
    }
)
};

function add_info(){
	frame(pc,psql,icols,ypc,ycheck,i) and(
    //pstmt<==sqlite_get_stmt() and skip;
	char* psql<=="select * from users;" and skip;
    sqlite3_prepare_v2(gp_sqlite3,psql,strlen(psql),&pstmt,NULL) and skip;
	char *pc and skip;
    int icols<==sqlite_get_col_count() and skip;
	char **ypc <== (char**)malloc(icols*sizeof(char *)) and skip;
	char ycheck[1]<=="Y" and skip;
    printf("columns count is %d\n",icols) and skip;
    int i<==0 and skip;
    while(i<icols)
	{
        pc<==sqlite3_column_name(pstmt,i) and skip;
        printf("please input column%d %s:\n",i,pc) and skip;
        ypc[i]<==sql_input_keyword() and skip;
		i:=i+1
    };
    pad('-',80);
	i<==0 and skip;
    while(i<icols)
	{
        pc<==sqlite3_column_name(pstmt,i) and skip;
        printf("column%d %-7s is:%s\n",i,pc,ypc[i]) and skip;
		i:=i+1
    };
    pad('-',80);
    printf("Save this ?(y/n)\n") and skip;
    if(ycheck[0]='y' OR ycheck[0]='Y')then
	{//qgb:tested
        sqlite_save(icols,ypc)
    }
	else
	{
        printf("Input is %s\nSave abort!\n",ycheck) and skip
    }
	//sqlite3_finalize(pstmt);
    //pause();
    //color("0a");
	)
};

function sqlite_connect()
{/** 连接数据库**/
	frame(result,ret) and (
    int result <== 0 and skip;
    int ret <== sqlite3_open("./AddressBook.db", &gp_sqlite3) and skip;
    if( ret != 0 ) then 
	{
        fprintf(stderr, "Can not open database： %s\n", sqlite3_errmsg(gp_sqlite3)) and skip
    }
	else
	{
		if(db_isNull()) then
		{
			printf("d") and skip;
			sqlite_create_table()
		}  
    }
)
};

function sql_input_keyword(char* RValue){
    char c<=='\0' and skip;
	char yc[50] and skip;
    char* pcr<==(char*)calloc(50,sizeof(char*)) and skip;
    int i<==0 and skip;
	int ia<==0 and skip;
	int ibreak<==0 and skip;
	int inputNULL<==1 and skip;
	strcpy(pcr, "1") and skip;
	RValue:=pcr;
	skip
};

/*sqlite3_stmt* sqlite_get_stmt(){
    sqlite3_stmt *pstmt;
    char* psql="select * from users;";
    sqlite3_prepare_v2(gp_sqlite3,psql,strlen(psql),&pstmt,NULL);
    return pstmt;
}*/

function sqlite_get_col_count(int RValue)
{
	frame(iclos,psql) and (
	char* psql<=="select * from users;" and skip;
    sqlite3_prepare_v2(gp_sqlite3,psql,strlen(psql),&pstmt,NULL) and skip;
    int icols<==sqlite3_column_count(pstmt) and skip;
    RValue:= icols
)
};

function sqlite_get_row_count(int RValue)
{
	frame(pc_ErrMsg,ir,ppc_r,i_row,i_col) and (
    char *pc_ErrMsg <== 0 and skip;
    int ir<==0 and skip;
    char **ppc_r and skip;
    int i_row<==0 and skip;
    int i_col<==0 and skip;
    ir<==sqlite3_get_table(gp_sqlite3,"select * from users;",&ppc_r,&i_row,&i_col,&pc_ErrMsg) and skip;
    RValue:= i_row;
	skip
)
};

function db_isNull(int RValue){
	frame(pc_ErrMsg,ir,ppc_r,i_row,i_col) and (
    char *pc_ErrMsg <== 0 and skip;
    int ir<==0 and skip;
    char **ppc_r and skip;
    int i_row<==0 and skip;
    int i_col<==0 and skip;
    ir<==sqlite3_get_table(gp_sqlite3,"select * from users;",&ppc_r,&i_row,&i_col,&pc_ErrMsg) and skip;
    if(ir=0) then
	{
        if(i_col=0) then
		{
			RValue:= 1
		}
        else
        {
			RValue:= 0
		}
    }
	else
	{
         RValue:= 1
    }
)
};

function sqlite_create_table()
{
	frame(sSQL1,pErrMsg,result) and(
    char * sSQL1 <== "create table users(id varchar(20) PRIMARY KEY,
                                                        name varchar(10),
                                                        sex varchar(1),
                                                        address varchar(100),
                                                        tel varchar(12), 
                                                        qq varchar(15));" and skip;
    char * pErrMsg <== 0 and skip;
    int result<==sqlite3_exec( gp_sqlite3, sSQL1, 0, 0, &pErrMsg ) and skip;
    if( result != 0 ) then
	{
        fprintf(stderr, "建表错误: %s|错误码=%d\n", pErrMsg,result) and skip;
        sqlite3_free(pErrMsg)
    }
)
};

function sqlite_save(int ai_length,char *ayps[],int RValue){
	frame(ysql,i,ir) and (
    char ysql[99]<=="insert into users values(" and skip;
    int i<==0 and skip;
    while(i<ai_length)
	{
        if(i=0) then
		{
            sprintf(ysql,"%s'%s'",ysql,ayps[i]) and skip
        }
		else
		{
			sprintf(ysql,"%s,'%s'",ysql,ayps[i]) and skip
        };
		i:=i+1
   };
    sprintf(ysql,"%s%s",ysql,");") and skip;
    int ir<==sqlite_exec(ysql) and skip;
	if(ir=0) then
	{
		 printf("Save success!\n")
	}
	else
	{
		if(ir=19) then
		{
			 printf("Error:Record already exists!\n")
		}
		else
		{
			printf("Error:Unknown.code=%d \n",ir)
		}
	}
)
};

function sqlite_exec(char *apsql, int RValue){
	frame(pErrMsg,result) and(
    char *pErrMsg <== 0 and skip;
    int result<==sqlite3_exec( gp_sqlite3, apsql, 0, 0, &pErrMsg ) and skip;
    if( result != 0 ) then
	{
		sqlite3_free(pErrMsg)
    };
	RValue:= result
)
};



	sqlite_connect();
    show_main_menu()
)