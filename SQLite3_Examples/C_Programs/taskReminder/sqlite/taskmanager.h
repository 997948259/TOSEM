#ifndef __TASKMANAGER__
#define __TASKMANAGER__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <ctype.h>

#define NOT_ARCHIVE 0
#define ARCHIVE 1



typedef struct task{
   
    long id;
    char *todo;
    
}task;

task * create_task(const char *todo,size_t n);

#endif
