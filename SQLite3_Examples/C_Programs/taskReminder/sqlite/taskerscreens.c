#include "taskerscreens.h"


#define ESC 27
#define clear_screen() printf("\033[H\033[J")
/*
  This library handles screens processes and prints, just for more tidy code

 */

unsigned int read_line(char **text){
    int max = 100;
    int counter = 0;
    *text = (char*)  realloc(*text,sizeof(char)*max);
    char ch;
    while ( (ch = getchar() )!= '-')
    {
	*(*text+counter) = ch;
	counter ++;
	if(counter == max)
	{
	    max = max * 2;
	    *text = (char*)  realloc(*text,sizeof(char)*max);
	}
    }
    getchar(); // gets enter key from stdin to avoid wrong actions
    *(*text+counter)  = 0;
    return counter;
}

void welcome_screen(){
    clear_screen();
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
    size_t itxt_size =0;
    //getline(&itxt,&itxt_size,stdin);    
	gets(itxt);
    long id;
    if (!sscanf(itxt,"%ld",&id))
    {   
	printf("Surely I was waiting for a number\n");
        
	return -1;
    }
    clear_screen();
    return id;
}

unsigned int add_task_todo_screen(char **todo){
    clear_screen();
    printf("Make yourself home \n");
    printf("Write the Todo or Task you want to remember \n");
    printf("Press ESC then Enter to apply\n");
    printf("->");
    size_t txt_size=read_line(&*todo);    
    return txt_size;
}

void print_task_screen(char **cell_data)
{

    printf("---------------------------------------------------------\n");
    printf("Todo:\n");
    printf("--   %s\n\n",cell_data[TODO_COL]);
    printf("TASK ID %s\n", cell_data[ID_COL]);
    printf("---------------------------------------------------------\n");

}
