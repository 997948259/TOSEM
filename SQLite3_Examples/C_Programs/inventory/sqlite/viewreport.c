#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "viewstock.h"

/* VIEW LIST OF ITEM STOCKS */

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
     printf("%s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}


void viewReport() {
   system("cls");
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data=NULL;
   char choice;
   
   rc = sqlite3_open("inventory.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr," -----------------\n");
      fprintf(stderr,"| LIST OF STOCKS  |\n");
      fprintf(stderr," -----------------\n");
   }

   sql = sqlite3_mprintf("SELECT * FROM STOCK_LOGS"); 
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   sqlite3_close(db);
   
   printf("------------------------\n");
   display:
   printf("[1] Back to main menu\n");
   printf("[0] Exit Program: ");
   scanf(" %c", &choice);
   switch (choice) {
    case '1' :
      main();
      break;
    case '0' :
      exit(0);
      break;
  default:
      printf("Invalid Input\n");
      goto display;
   }
}
