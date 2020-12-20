#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <ctype.h>
#include "sqlite3.h"

char itxt[10];
size_t itxt_size =0;

typedef struct task{

	long id;
	char *todo;

}task;

sqlite3 *db;
char *err_msg = 0;

int callback(void *flag, int col_len, char **cell_data, char **col_name){
	if (!flag)
		return 0;
	switch (*(int*)flag)
	{
	case 1:
		print_task_screen(cell_data);
		break;
	case 0:
		break;
	}
	return 0;
}
int intialize_tasks_table(){
	char *sql;
	sql = "CREATE TABLE IF NOT EXISTS TASKS ("		 \
		"ID INTEGER PRIMARY KEY  AUTOINCREMENT   NOT NULL," \
		"TODO           TEXT    NOT NULL);";
	return sqlite3_exec(db, sql, *callback, 0, &err_msg);



}

/*
Opens DB and set the callback function
name : The name of the db
callback_function: callback_function used with the executions
*/
int intialize_db(char *name){
	int rc;
	rc = sqlite3_open(name, &db);
	if (rc)
		return -1;
	rc = intialize_tasks_table();
	if (rc != SQLITE_OK)
		sqlite3_free(err_msg);
	else
		return -1;
	return 0;
}


/*
Returns all the data in the DB to the callback function
*/
int get_all_tasks(){
	int rc;
	char* sql;
	sql = "SELECT * FROM TASKS;";
	int flag = 1;
	rc = sqlite3_exec(db, sql, *callback, (void*)&flag, &err_msg);
	if (rc != SQLITE_OK)
		sqlite3_free(err_msg);
	else
		return 0;
	return -1;
}

/*
Returns the equivelent task by id
*/
int get_task(long id){
	int rc;
	char* sql;
	sql = (char*)malloc(sizeof(char) * 40);
	sprintf(sql, "SELECT * FROM TASKS WHERE ID=%ld;", id);
	int flag = 0;
	rc = sqlite3_exec(db, sql, *callback, (void*)&flag, &err_msg);
	if (rc != SQLITE_OK)
		sqlite3_free(err_msg);
	else
		return 0;
	return -1;
}

int insert_task(task tsk){
	char *sql;
	sql = (char*)malloc(sizeof(char)*(300 + strlen(tsk.todo)));
	int rc;
	sprintf(sql, "INSERT INTO TASKS (TODO) VALUES (\"%s\");", tsk.todo);
	rc = sqlite3_exec(db, sql, *callback, 0, &err_msg);

	if (rc != SQLITE_OK)
	{
		printf("\n %s", err_msg);
		sqlite3_free(err_msg);
		printf("\n %s", err_msg);
	}
	else
		return 0;
	return -1;
}

int edit_task(task tsk){
	char *sql;
	int rc;
	sql = (char*)malloc(sizeof(char) * 100 + sizeof(char)*strlen(tsk.todo));
	sprintf(sql, "UPDATE TASKS set TODO =\"%s\" where ID=%ld;", tsk.todo, tsk.id);
	rc = sqlite3_exec(db, sql, *callback, 0, &err_msg);
	if (rc != SQLITE_OK)
	{
		printf("%s", err_msg);
		sqlite3_free(err_msg);
	}

	else
		return 0;
	return -1;
}

int delete_task(long id){
	char *sql;
	int rc;
	sql = malloc(sizeof(char) * 100);
	sprintf(sql, "DELETE FROM TASKS WHERE ID = %ld ;", id);
	rc = sqlite3_exec(db, sql, *callback, 0, &err_msg);
	if (rc != SQLITE_OK)
	{
		sqlite3_free(err_msg);
	}
	else
		return 0;
	return -1;
}
void close_db(){

	sqlite3_close(db);

}

/*
This library handles screens processes and prints, just for more tidy code

*/

unsigned int read_line(char **text){
	int max = 100;
	int counter = 0;
	*text = (char*)realloc(*text, sizeof(char)*max);
	char ch;
	while ((ch = getchar()) != '-')
	{
		*(*text + counter) = ch;
		counter++;
		if (counter == max)
		{
			max = max * 2;
			*text = (char*)realloc(*text, sizeof(char)*max);
		}
	}
	getchar(); // gets enter key from stdin to avoid wrong actions
	*(*text + counter) = 0;
	return counter;
}

void welcome_screen(){
	printf("\033[H\033[J");
	printf(" Welcome to Tasker :) \n");
}

void help_screen(){
	printf("Use one of the next options \n");
	printf("    -t to add new task \n");
	printf("    -d to delete a task by id \n");
	printf("    -p to print all tasks \n");
	printf("    -h to show this screen \n");
	printf("    -q to close tasker \n");
}

long delete_screen(){
	printf("Enter id you want to delete\n");
	printf("->");
	char itxt[10];
	size_t itxt_size = 0;
	//getline(&itxt,&itxt_size,stdin);    
	gets(itxt);
	long id;
	if (!sscanf(itxt, "%ld", &id))
	{
		printf("Surely I was waiting for a number\n");

		return -1;
	}
	printf("\033[H\033[J");
	return id;
}

unsigned int add_task_todo_screen(char **todo){
	printf("\033[H\033[J");
	printf("Make yourself home \n");
	printf("Write the Todo or Task you want to remember \n");
	printf("Press ESC then Enter to apply\n");
	printf("->");
	size_t txt_size = read_line(&*todo);
	return txt_size;
}

int print_task_screen(char **cell_data)
{

	printf("---------------------------------------------------------\n");
	printf("Todo:\n");
	printf("--   %s\n\n", cell_data[1]);
	printf("TASK ID %s\n", cell_data[0]);
	printf("---------------------------------------------------------\n");
}

task * create_task(const char *todo, size_t n){

	/*
	Return: pointer to the task created
	*/

	task * p = (task*)malloc(sizeof(task));
	p->todo = (char*)malloc(sizeof(char)*n);
	strcpy(p->todo, todo);
	return p;

}

int main(){
    welcome_screen();
    help_screen();
    intialize_db("tasker.db");
    intialize_tasks_table();
    task *tsk;
    tsk =(task*)  malloc(sizeof(task));
    while(1){
	printf("-> ");
    /*    int result = getline(&itxt,&itxt_size,stdin);
        if(result -1 != 2)
	{
	    printf("wrong argument\n -h to see possible ones\n");
            continue;
	}*/
		gets(itxt);
		if (!strncmp(itxt, "-q",2))
            break;
		else if (!strncmp(itxt, "-h",2))
	    help_screen();
		else if (!strncmp(itxt, "-p",2))
            get_all_tasks();
		else if (!strncmp(itxt, "-d",2))
        {
	    long id;
	    id = delete_screen();
	    if(id == -1)
		continue;
            delete_task(id);
	    get_all_tasks();
	}
		else if (!strncmp(itxt, "-t",2)){
	    
            char *todo = NULL;
            int todo_size = add_task_todo_screen(&todo);
	    
	    tsk= create_task(todo,todo_size);
	    insert_task(*tsk);
	    printf("Added :) \n");
        }
    }
    free(tsk);
    printf("Cya soon :)\n");
}