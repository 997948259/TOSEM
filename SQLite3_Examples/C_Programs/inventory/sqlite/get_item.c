#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "get_item.h"

/* VIEW LIST OF ITEM STOCKS */

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
     printf("%s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}


void getItemDetails(int itemno) {
   system("cls");
   sqlite3 *db;
   char *zErrMsg = 0;
   int con;
   const char* data=NULL;
   char choice;
   char* str1;
   char str2[BUFSIZ];
   int num = itemno;
   str1 = "SELECT * FROM STOCK_ITEM WHERE ITEM_NO =";
   _itoa(num, str2, 10);
   char * sql = (char *) malloc(1 + strlen(str1)+ strlen(str2) );
   strcpy(sql, str1);
   strcat(sql, str2);
   
   con = sqlite3_open("inventory.db", &db);
   if( con ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr," -----------------\n");
      fprintf(stderr,"|   ITEM DETAILS  |\n");
      fprintf(stderr," -----------------\n");
   }

   con = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( con != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   //sqlite3_close(db);

}
