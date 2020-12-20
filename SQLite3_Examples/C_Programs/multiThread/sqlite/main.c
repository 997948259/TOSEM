#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "sqlite3.h"
#include <windows.h>
#pragma comment(lib, "pthreadVC2.lib")

#define MAXTHREAD 10
#define MINBUSYTIME 2000
sqlite3 *dbArray[10];
/*struct {
	int threadParam;
	pthread_t threadId;
} aux[MAXTHREAD];*/
pthread_t aux[MAXTHREAD];
static int execSql(int threadId, const char *sql) {
	int rc = SQLITE_OK;
	if (dbArray[threadId] == NULL) {
		return 1;
	}
	rc = sqlite3_exec(dbArray[threadId], sql, NULL, 0, NULL);
	if (rc && (rc != SQLITE_CONSTRAINT)) {
		printf("Error %d (%s) Query:%s\n", rc, sqlite3_errmsg(dbArray[threadId]), sql);
	}
	return rc;
}


static int openDatabase(int threadId, const char *databaseName) {
	int rc = sqlite3_open(databaseName, &dbArray[threadId]);
	if (rc == SQLITE_OK) {
		const char *pragma = "PRAGMA journal_mode = WAL;"
			"PRAGMA foreign_keys = ON;";
		// we may add a static parameter here -> "PRAGMA busy_timeout = 30000;";
		rc = sqlite3_exec(dbArray[threadId], pragma, NULL, 0, NULL);
		if (rc != SQLITE_OK) {
			printf("%s (%s)", sqlite3_errmsg(dbArray[threadId]), databaseName);
		}
		else {
			int timeOut = MAXTHREAD * 200;
			if (timeOut < MINBUSYTIME) {
				timeOut = MINBUSYTIME;     // at least one second time out
			}
			printf("Busy time out set to %d\n", timeOut);
			rc = sqlite3_busy_timeout(dbArray[threadId], timeOut);
		}
	}
	else {
		printf("CAN'T OPEN DATABASE %s - %s", databaseName, sqlite3_errstr(rc));
	}
	return rc;
}

static int stress(int threadId, int inserts) {
	int rc = 0;
	const char *insert = "insert into busy (thread, sequence) values (%d,%d);";
	char query[1000];
	int count;
	execSql(threadId, "BEGIN IMMEDIATE");
	for (count = 1; count <= inserts; count++) {
		sprintf(query, insert, threadId, count);
		rc = execSql(threadId, query);
		if (rc != SQLITE_OK) {
			printf("Aborting thread %d after %d iterations\n", threadId, count);
			break;
		}
	}
	execSql(threadId, "COMMIT");
	return rc;
}

static int delete (int threadId) {
	int rc = 0;
	const char *delete = "delete from busy;";
	int count;
	for (count = 1; count <= 5; count++) {
		Sleep(1);
		execSql(threadId, "BEGIN IMMEDIATE");
		rc = execSql(threadId, delete);
		execSql(threadId, "COMMIT");
		if (rc != SQLITE_OK) {
			printf("Aborting thread DELETE after %d iterations\n", count);
			break;
		}
	}
	return rc;
}

void busyThread(void *arg) {
	int threadId = *(int *)arg;
	
	int rc = openDatabase(threadId, "../busy.db3");
	sqlite3_exec(dbArray[threadId], "create table busy(thread INT, sequence INT)", NULL, NULL, NULL);
	if (rc == SQLITE_OK) {
		printf("Thread %d started\n", threadId);
		if (threadId == 1) {
			rc = delete(threadId);
		}
		else {
			rc = stress(threadId, 1000);
		}
		printf("Thread %d finished\n", threadId);
	}
}

int main(int argc, char** argv) {
	int threads;
	sqlite3 *db = NULL;
	int rc = sqlite3_open("../busy.db3", &db);
	sqlite3_exec(db, "create table busy(thread INT, sequence INT)", NULL, NULL, NULL);
	sqlite3_close(db);
	int threadParam[MAXTHREAD];
	for (threads = 0; threads < MAXTHREAD; threads++) {
		//aux[threads].threadId = (pthread_t)0;
		//aux[threads].threadParam = threads + 1;
		threadParam[threads] = threads + 1;
		pthread_create(&aux[threads], NULL, (void *)&busyThread, (void *)&threadParam[threads]);
	}
	for (threads = 0; threads < MAXTHREAD; threads++) {
		pthread_join(aux[threads], NULL);
	}
	return (EXIT_SUCCESS);
}