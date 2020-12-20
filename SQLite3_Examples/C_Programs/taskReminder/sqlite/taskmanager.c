#include "taskmanager.h"

#define CMP_IF_ZERO(A,B) A? A:B



task * create_task(const char *todo,size_t n){

    /*
      Return: pointer to the task created
     */
    
    task * p = (task*) malloc(sizeof(task));
    p->todo= (char*) malloc(sizeof(char)*n);
    strcpy(p->todo,todo);
    return p;

}