#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_quantity.h"
#include "sqlite3.h"

int getStockQty(int itemno) {
	
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int con;
    int con2;
    int stock;
    char* str1;
    char str2[BUFSIZ];
    char *zErrMsg = 0;
    int num = itemno;
    str1 = "SELECT QTY FROM STOCK_ITEM WHERE ITEM_NO =";
    _itoa(num, str2, 10);
    char * sql = (char *) malloc(1 + strlen(str1)+ strlen(str2) );
    strcpy(sql, str1);
    strcat(sql, str2);
      
    con = sqlite3_open("inventory.db", &db);
    if (con != SQLITE_OK) {fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));sqlite3_close(db);return 1;}
    
    con = sqlite3_prepare_v2(db,sql, -1, &stmt, 0);    
    if (con != SQLITE_OK) {fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));sqlite3_close(db);return 1;}    
    
    con = sqlite3_step(stmt);
    
    if (con == SQLITE_ROW) {
        stock = sqlite3_column_int (stmt, 0);
    }
    sqlite3_finalize(stmt);
    //sqlite3_close(db);
    return(stock);
}
