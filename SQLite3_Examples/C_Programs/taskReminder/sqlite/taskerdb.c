#include "taskerdb.h"
/*
  This library handles the database for tasker, it uses
sqlite 3 library, 

 */


sqlite3 *db;
char *err_msg = 0;

// Call back function pointer used with sql executions
static int (*callback) (void *, int , char **, char **);


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
int intialize_db(char *name, int (*callback_function) (void *, int , char **, char **)){
    callback = callback_function;
  int rc;
    rc = sqlite3_open(name,&db);
    if( rc )
        return -1;
    rc = intialize_tasks_table();
    if( rc != SQLITE_OK )
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
    int flag = PRINT_TASKS;
    rc = sqlite3_exec(db,sql,*callback,(void*)&flag,&err_msg);
    if( rc != SQLITE_OK )
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
    sql = (char*) malloc(sizeof(char)*40);
    sprintf(sql,"SELECT * FROM TASKS WHERE ID=%ld;",id);
    int flag = GET_TASK;
    rc = sqlite3_exec(db,sql,*callback,(void*)&flag,&err_msg);
    if( rc != SQLITE_OK )
      sqlite3_free(err_msg);
    else 
      return 0;
    return -1;
}

int insert_task(task tsk){
  char *sql;
  sql  = (char*) malloc(sizeof(char)*(300 + strlen(tsk.todo)));
  int rc;
   sprintf(sql ,"INSERT INTO TASKS (TODO) VALUES (\"%s\");",tsk.todo);
    rc = sqlite3_exec(db,sql,*callback,0,&err_msg);

    if( rc != SQLITE_OK )
      {
	printf("\n %s",err_msg);
	sqlite3_free(err_msg);
	printf("\n %s",err_msg);
      }
	else
      return 0;
    return -1;


}

int edit_task(task tsk){
char *sql;
  int rc;
  sql =(char*) malloc(sizeof(char)*100 + sizeof(char)*strlen(tsk.todo));
  sprintf(sql , "UPDATE TASKS set TODO =\"%s\" where ID=%ld;", tsk.todo,tsk.id);
      rc = sqlite3_exec(db,sql,*callback,0,&err_msg);
      if( rc != SQLITE_OK )
      {
	printf("%s",err_msg);
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
  sprintf(sql , "DELETE FROM TASKS WHERE ID = %ld ;",id);
    rc = sqlite3_exec(db,sql,*callback,0,&err_msg);
    if( rc != SQLITE_OK )
      {
	sqlite3_free(err_msg);}
    else
      return 0;
  return -1;
}
void close_db(){

    sqlite3_close(db);

}
