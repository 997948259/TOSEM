#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>

typedef struct College
{
	char* cName;
	char* state;
	int enrollment;
} College;

typedef struct Student
{
	int sID;
	char* sName;
	float GPA;
	int sizeHS;
} Student;

typedef struct Apply
{
	int sID;
	char* cName;
	char* major;
	char* decision;
} Apply;

static int view_all_callback(void* data, int argc, char** argv, char** azColName)
{
	int i;
	fprintf(stderr, "%s:\n", (const char*)data);
	for (i = 0; i < argc; i++)
	{
		printf("%s = %s, ", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

static int insert_table_callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	return 0;
}

static int create_table_callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	return 0;
}

int main(int argc, char* argv[])
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	char* sql;
	const char* data = "Callback function called";
	/* 创建数据库连接 */
	rc = sqlite3_open("DBforCourse.db3", &db);
	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}

	/* 建表*/
	sql = "create table College(cName text, state text, enrollment int);";
	rc = sqlite3_exec(db, sql, create_table_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "College Table created successfully\n");
	}
	sql = "create table Student(sID int, sName text, GPA float, sizeHS int);";
	rc = sqlite3_exec(db, sql, create_table_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Student Table created successfully\n");
	}
	sql = "create table Apply(sID int, cName text, major text, decision text);";
	rc = sqlite3_exec(db, sql, create_table_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Apply Table created successfully\n");
	}

	/* 加载文件*/
	College college[4];
	Student student[12];
	Apply apply[19];
	FILE* fp;
	char line[100];
	char delims[] = ",";
	char* result;
	int i = 0;
	if (fp = fopen("dbcollege.txt", "r"))
	{
		while (fgets(line, 100, fp) != NULL)
		{
			result = strtok(line, delims);
			college[i].cName = result;
			result = strtok(NULL, delims);
			college[i].state = result;
			result = strtok(NULL, delims);
			college[i].enrollment = atoi(result);
			//printf("%s, %s, %d\n", college[i].cName, college[i].state, college[i].enrollment);
			sql = sqlite3_mprintf("insert into College(cName, state, enrollment) values('%s', '%s', '%d');", college[i].cName, college[i].state, college[i].enrollment);
			rc = sqlite3_exec(db, sql, insert_table_callback, 0, &zErrMsg);
			if (rc != SQLITE_OK)
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}
			else {
				fprintf(stdout, "operations done successfully\n");
			}
			sqlite3_free(sql);
			i++;
		}
		fclose(fp);
	}
	result = NULL;
	i = 0;
	if (fp = fopen("dbstudent.txt", "r"))
	{
		while (fgets(line, 100, fp) != NULL)
		{
			result = strtok(line, delims);
			student[i].sID = atoi(result);
			result = strtok(NULL, delims);
			student[i].sName = result;
			result = strtok(NULL, delims);
			student[i].GPA = atof(result);
			result = strtok(NULL, delims);
			student[i].sizeHS = atoi(result);
			//printf("%d, %s, %f, %d\n", student[i].sID, student[i].sName, student[i].GPA, student[i].sizeHS);
			sql = sqlite3_mprintf("insert into Student(sID, sName, GPA, sizeHS) values('%d', '%s', '%f', '%d');", student[i].sID, student[i].sName, student[i].GPA, student[i].sizeHS);
			rc = sqlite3_exec(db, sql, insert_table_callback, 0, &zErrMsg);
			if (rc != SQLITE_OK)
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}
			else {
				fprintf(stdout, "operations done successfully\n");
			}
			sqlite3_free(sql);
			i++;
		}
		fclose(fp);

	}
	result = NULL;
	i = 0;
	if (fp = fopen("dbapply.txt", "r"))
	{
		while (fgets(line, 100, fp) != NULL)
		{
			result = strtok(line, delims);
			apply[i].sID = atoi(result);
			result = strtok(NULL, delims);
			apply[i].cName = result;
			result = strtok(NULL, delims);
			apply[i].major = result;
			result = strtok(NULL, delims);
			apply[i].decision = result;
			//printf("%d, %s, %s, %s\n", apply[i].sID, apply[i].cName, apply[i].major, apply[i].decision);
			sql = sqlite3_mprintf("insert into Apply(sID, cName, major, decision) values('%d', '%s', '%s', '%s');", apply[i].sID, apply[i].cName, apply[i].major, apply[i].decision);
			rc = sqlite3_exec(db, sql, insert_table_callback, 0, &zErrMsg);
			if (rc != SQLITE_OK)
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}
			else {
				fprintf(stdout, "operations done successfully\n");
			}
			sqlite3_free(sql);
			i++;
		}
		fclose(fp);
	}

	sql = "select * from College";
	rc = sqlite3_exec(db, sql, view_all_callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	sql = "select * from Student";
	rc = sqlite3_exec(db, sql, view_all_callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	sql = "select * from Apply";
	rc = sqlite3_exec(db, sql, view_all_callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	/* select in Student GPA > 3.6, return sID, sName and GPA*/
	sql = "select sID, sName, GPA from Student where GPA > 3.6;";
	rc = sqlite3_exec(db, sql, view_all_callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "operations done successfully\n");
	}

	/* select in Apply and Student distinct, return sName, cName*/
	sql = "select distinct sName, cName from Student natural join Apply;";
	rc = sqlite3_exec(db, sql, view_all_callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "operations done successfully\n");
	}

	/* select*/
	sql = "select sName, GPA, decision from Student, Apply where Student.sID = Apply.sID and sizeHS < 1000 and major = \"CS\" and cName = \"Stanford\";";
	rc = sqlite3_exec(db, sql, view_all_callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "operations done successfully\n");
	}

	/**/
	sql = "select distinct * from Apply, Student, College where Student.sID = Apply.sID and Apply.cName = College.cName order by GPA desc, enrollment;";
	rc = sqlite3_exec(db, sql, view_all_callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "operations done successfully\n");
	}

	/**/
	sql = "select sID, sName, GPA*(sizeHS / 1000) as newGPA from Student;";
	rc = sqlite3_exec(db, sql, view_all_callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "operations done successfully\n");
	}

	/**/
	sql = "select cName, max(enrollment) from College;";
	rc = sqlite3_exec(db, sql, view_all_callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "operations done successfully\n");
	}

	/**/
	sql = "select * from College natural join Student natural join Apply;";
	rc = sqlite3_exec(db, sql, view_all_callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "operations done successfully\n");
	}

	/**/
	sql = "select cName from Apply group by cName having count(major) < 5;";
	rc = sqlite3_exec(db, sql, view_all_callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "operations done successfully\n");
	}

	sqlite3_close(db);
	return 0;
}
