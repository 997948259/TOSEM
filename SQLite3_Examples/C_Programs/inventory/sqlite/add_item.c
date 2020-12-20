#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "add_item.h"

static int callback1(void *data, int argc, char **argv, char **azColName){};

/* ADD ITEM INTO DATABASE */
void addItem() {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   char choice;
   char itemname[BUFSIZ];
   char price[BUFSIZ];

   rc = sqlite3_open("inventory.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }
   
   inputitem:
   /*system("cls");
   printf("Item Name: ");
   fgets(itemname, BUFSIZ, stdin);
   itemname[strlen(itemname) - 1] = '\0';
   if (itemname[0] == '\0') {
     goto inputitem;
   } 
   
   inputprice: 
   printf("Price: ");
   if(fgets( price,BUFSIZ,stdin)!=NULL){
      char *chk;
      double tmp = strtod( price, &chk );
      price[strlen(price) - 1] = '\0';
      if (price[0] == '\0') {
         printf("Please input a valid price\n");
         goto inputprice;
      } 
      if ( isspace( *chk ) || *chk == 0 ) {
         goto query;
      } else {
        fprintf( stderr, "%s is not a valid valid price\n", price );
        goto inputprice;
      }
    } */
  
query:
   strcpy(itemname, "book");
   strcpy(price, "1");
   rc = sqlite3_exec(db, "create table STOCK_ITEM (ITEM_NAME CHAR(512),PRICE CHAR(512))", NULL, 0, &zErrMsg);
   sql = sqlite3_mprintf("INSERT INTO STOCK_ITEM (ITEM_NAME,PRICE) values ('%s','%s');", itemname,price);
   rc = sqlite3_exec(db, sql, callback1, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "ITEM SUCCESSFULLY ADDED!");
   }
   
   display:
   printf("\n\nWould you like to add another item? (Y/N) ");
   //scanf(" %c", &choice);
   choice = 'n';
   if(choice == 'y' || choice == 'Y') {
     goto inputitem;
   } else if (choice == 'n' || choice == 'N') {
     main();
   } else {
     system("cls");
     goto display;
   }
   
}
