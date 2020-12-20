#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>
#include <time.h>
#include <thread>
#include <math.h>
#include <windows.h>

char * err; 
int opTime[4][4]; 
char sqll[4000]; 
double max=0,min=0; 
int GetRandomIndex()
{
	return rand()*3; 
}

void OpenDataBase(sqlite3 **db)
{
	int ret = sqlite3_open("./sqlite3-demo.db",db); 

	if(ret != SQLITE_OK){
        fprintf(stderr,"Cannot open db: %s\n",sqlite3_errmsg(*db));
		getchar(); 
        exit(1);
    }
	
}


int GetRec(void *params,int n_column,char **column_value,char **column_name)
{
	char buf[130]; 
	for(int i = 1; i < n_column; i++)
	{
		memcpy(buf,column_value[i],strlen(column_value[i])); 
	}

	return 0; 
}

void ReadOperation(int threadIndex)
{
	sqlite3 *dbHandle; 

	char *sqlc = "select * from t where id = "; 

	

	char sqlExp[50] = {0}; 
	int ret; 
	for(int i = 0; i < 2; i++)
	{
		memset(sqlExp,0,sizeof(sqlExp));
		sprintf(sqlExp,"%s%d",sqlc,GetRandomIndex()); 
		OpenDataBase(&dbHandle); 
		ret = 0xf; 
		int startTime = GetTickCount(); 
		while(ret != SQLITE_OK)
		{
			ret = sqlite3_exec(dbHandle,sqlExp,GetRec,NULL,&err); 
			if(ret != SQLITE_OK)
			{
				//printf("read error\n%s\n",err); 
			}
		}
		opTime[threadIndex][i] = GetTickCount() - startTime; 
		sqlite3_free(err); 
		sqlite3_close(dbHandle);
	}
	

}

void WriteOperation(int threadIndex)
{
	sqlite3 *dbHandle; 

	char *sqlc = "insert into t values() "; 


	char sqlExp[50] = {0}; 
	int ret = 0xf; 
	for(int i = 0; i < 2; i++)
	{

		OpenDataBase(&dbHandle); 
		
		ret = 0xf; 
		int startTime = GetTickCount(); 
		while(ret != SQLITE_OK)
		{
			ret = sqlite3_exec(dbHandle,sqll,NULL,NULL,&err); 
			if(ret != SQLITE_OK)
			{
				//printf("insert error!!!press enter continue\n%s\n",err); 
				//getchar(); 
			}
		}
		opTime[threadIndex][i] = GetTickCount() - startTime; 
		sqlite3_free(err); 
		sqlite3_close(dbHandle); 
	}



}


void RWOperation(int threadIndex)
{
	sqlite3 *dbHandle; 

	char *sqlc = "select * from t where id = "; 


	char sqlExp[50] = {0}; 
	int ret = 0xf; 
	for(int i = 0; i < 2; i++)
	{

		if(threadIndex % 2 != 0)
		{
			memset(sqlExp,0,sizeof(sqlExp));
			sprintf(sqlExp,"%s%d",sqlc,GetRandomIndex()); 
			ret = 0xf;
			int startTime = GetTickCount(); 
			OpenDataBase(&dbHandle);
			while(ret != SQLITE_OK)
			{
				ret = sqlite3_exec(dbHandle,sqlExp,GetRec,NULL,&err); 
				if(ret != SQLITE_OK)
				{
					//printf("RW:select error!!!press enter continue\n%s\n",err); 
					//getchar(); 
				}
			}
			opTime[threadIndex][i] = GetTickCount() - startTime; 
			sqlite3_free(err); 
			sqlite3_close(dbHandle);

			OpenDataBase(&dbHandle);
			ret = 0xf;
			startTime = GetTickCount(); 
			while(ret != SQLITE_OK)
			{
				ret = sqlite3_exec(dbHandle,sqll,NULL,NULL,&err); 
				if(ret != SQLITE_OK)
				{
					//printf("RW:insert error!!!press enter continue\n%s\n",err); 
					//getchar(); 
				}
			}
			opTime[threadIndex][i+2] = GetTickCount() - startTime; 
			sqlite3_close(dbHandle);
		}else{


			OpenDataBase(&dbHandle);
			ret = 0xf;
			int startTime = GetTickCount(); 
			while(ret != SQLITE_OK)
			{
				ret = sqlite3_exec(dbHandle,sqll,NULL,NULL,&err); 
				if(ret != SQLITE_OK)
				{
					//printf("RW:insert error!!!press enter continue\n%s\n",err); 
					//getchar(); 
				}
			}
			opTime[threadIndex][i+2] = GetTickCount() - startTime; 
			sqlite3_close(dbHandle);

			memset(sqlExp,0,sizeof(sqlExp));
			sprintf(sqlExp,"%s%d",sqlc,GetRandomIndex()); 
			ret = 0xf;
			startTime = GetTickCount(); 
			OpenDataBase(&dbHandle);
			while(ret != SQLITE_OK)
			{
				ret = sqlite3_exec(dbHandle,sqlExp,GetRec,NULL,&err); 
				if(ret != SQLITE_OK)
				{
					//printf("RW:select error!!!press enter continue\n%s\n",err); 
					//getchar(); 
				}
			}
			opTime[threadIndex][i] = GetTickCount() - startTime; 
			sqlite3_free(err); 
			sqlite3_close(dbHandle);
		}
	}

	
}


int main()
{
	sqlite3 *dbHandle; 

	double aversum = 0.0; 

	OpenDataBase(&dbHandle); 
	sqlite3_exec(dbHandle,"create table t(id int primary key,msg varchar(128),msg1 varchar(128))",NULL,NULL,&err); 
	sqlite3_close(dbHandle); 


	double min1=0,max1=0; 
	char sqlr2[350]; 
	char aaa[135]={0}; 
	aaa[0] = '\"'; 
	//aaa[1]= '\"'; 
	memset(aaa+1,'q',128); 
	aaa[129] = '\"'; 
	aaa[130] = ','; 
	printf("aaa:%s", aaa);
	memset(sqlr2,0,350); 
	
	for(int i=0;i<2;i++)
		strcat(sqlr2,aaa); 
	int len = strlen(sqlr2); 
	sqlr2[len-1] = 0; 
	printf("len-1:%d", len-1);
	printf("sqlr2:%s", sqlr2);
	sprintf(sqll, "insert into t (msg,msg1) values (%s)",sqlr2);
	
	memset(opTime,0,sizeof(opTime));
	
	
	for(int i = 0; i < 4; i++)
	{
		//threadArray[i] = new std::thread(ReadOperation,i); 
		ReadOperation(i);
	}

	//WaitEnd(); 
	 
	printf("-------------read start----------------\n");
	
	
	
	for(int i = 0; i < 4; i++)
	{
		double sum = 0.0; 

		printf("thread %d result :",i+1);
		for(int j = 0; j < 2; j++)
		{
			printf(" %3.3f",(double)opTime[i][j]/1000); 
			sum += (double)opTime[i][j]; 
		}
		max = max > sum ? max : sum; 
		if(i == 0)
		  min = sum; 
		min = min < sum ? min:sum; 
		printf("\nsum:%3.3f\naverage:%3.3f\n\n",sum / 1000,sum / 10000); 
		aversum += sum; 
	}

	printf("per thread per operation:%3.3f\nmax:%3.3f\nmin:%3.3f\n",aversum / 160000,max/1000,min/1000); 
	printf("-------------read end----------------\n\n");
	//getchar(); 
	memset(opTime,0,sizeof(opTime)); 

	min = 0; 
	max = 0; 

	aversum = 0.0; 
	for(int i = 0; i < 4; i++)
	{
		//threadArray[i] = new std::thread(WriteOperation,i); 
		WriteOperation(i);
	}

	//WaitEnd();
	printf("-------------write start----------------\n");
	for(int i = 0; i < 4; i++)
	{
		double sum = 0; 

		printf("thread %d result read :",i+1);
		for(int j = 0; j < 2; j++)
		{
			printf(" %3.3f",(double)opTime[i][j] / 1000); 
			sum += (double)opTime[i][j]; 
		}
		
		double s = sum / 2; 
		max = max > sum ? max : sum; 
		if(i == 0)
		  min = sum; 
		min = min < sum ? min:sum; 
		printf("\nsum:%3.3f\naverage:%3.3f\n\n",sum / 1000,s / 1000); 
		aversum += sum; 
	}

	printf("per thread per operation:%3.3f\nmax:%3.3f\nmin:%3.3f\n",aversum / 40000,max /1000,min/1000); 
	printf("-------------write end----------------\n\n");
	//getchar(); 
	memset(opTime,0,sizeof(opTime)); 
	
	min = 0;
	max =0 ; 
	
	aversum = 0.0;
	for(int i = 0; i < 4; i++)
	{
		RWOperation(i);
	}

	double aversumx = 0.0; 
	aversum = 0.0; 
	printf("-------------RW start----------------\n");
	for(int i = 0; i < 4; i++)
	{
		double sum = 0; 

		printf("thread %d result read ",i+1);
		for(int j = 0; j < 2; j++)
		{
			printf(" %3.3f",(double)opTime[i][j] / 1000 ); 
			sum += (double)opTime[i][j]; 
		}
		max = max > sum ? max : sum; 
		if(i == 0)
		  min = sum; 
		min = min < sum ? min:sum; 
		printf("\nsum:%3.3f\naverrage:%3.3f\n\n",sum / 1000,sum / 10000); 
		aversumx += sum; 



		sum = 0.0; 

		printf("thread %d result write	 ",i+1);
		for(int j = 0; j < 2; j++)
		{
			printf(" %3.3f",(double)opTime[i][j+10] / 1000); 
			sum += (double)opTime[i][j+2]; 
		}
		max1 = max1 > sum ? max1 : sum; 
		if(i == 0)
		  min1 = sum; 
		min1 = min1 < sum ? min1:sum; 
		printf("\nsum:%3.3f\naverage:%3.3f\n\n",sum / 1000,sum / 10000); 
		aversum += sum; 

	}
	printf("per thread per operation:\nread:%3.3f\nwrite:%3.3f\nmax read :%3.3f\nmin read:%3.3f\nmax write:%3.3f\nmin write:%3.3f",aversumx / 40000,aversum / 40000,max / 1000,min / 1000, max1 / 1000, min1/ 1000); 
	printf("-------------RW end----------------\n\n");

	memset(opTime,0,sizeof(opTime)); 

	//getchar();
}

