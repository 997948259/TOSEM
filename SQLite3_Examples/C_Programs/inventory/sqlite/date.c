#include "date.h"
#include <time.h>
#include <stdio.h>
char* getDate (){
  static char buffer[26];
  time_t timer;
  struct tm* tm_info;
  time(&timer);
  tm_info = localtime(&timer);
  strftime(buffer, 26, "%m/%d/%Y %H:%M:%S", tm_info);
  char *y;
  y = (char*) &buffer;
  return y;
} 
