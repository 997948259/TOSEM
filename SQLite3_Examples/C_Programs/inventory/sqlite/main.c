#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sqlite3.h"
#include "date.h"
#include "add_item.h"
#include "get_quantity.h"
#include "stockin.h"
#include "stockout.h"
#include "viewstock.h"
#include "get_item.h"

int validate ( char *a ){
  unsigned x;
  for ( x = 0; x < strlen ( a ); x++ )
    if ( !isdigit ( a[x] ) ) return 1;
  return 0;
}


int main(int argc, char* argv[]) {
  
  int i;
  char buffer[BUFSIZ];
  menu:
  system("cls");
  printf(" ---------------------------------- \n");
  printf("|                                  |\n");
  printf("|             INVENTORY            |\n");
  printf("|              SYSTEM              |\n");
  printf("|                                  |\n");
  printf(" ---------------------------------- \n\n\n");
  printf("[1] Item Entry\n");
  printf("[2] View Stocks\n");
  printf("[3] Stock-in\n");
  printf("[4] Stock-out\n");
  printf("[5] View Report\n");
  printf("[0] Exit Program\n\n");
  printf("Enter Choice: ");
    
  /*if ( fgets ( buffer, sizeof buffer, stdin ) != NULL ) {
    buffer[strlen ( buffer ) - 1] = '\0';
    if ( validate ( buffer ) == 0 ) {
      i = atoi ( buffer );
    } else {
    	goto menu;
	} 
  } else {
  	goto menu;
  }*/
  i = 1;
    
  switch (i) {
    case 1 :
      addItem();
      break;
    case 2 :
      viewStocks();
      break;
    case 3 :
      stockIn();
      break;
    case 4 :
      stockOut();
      break;
    case 5 :
      viewReport();
      break;
    case 0 :
      exit(0);
      break;
  default:
      goto menu;
  }
 
}




