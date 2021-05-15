#include	<stdio.h>
#include	<signal.h>

/* memory errors */
#define  heap_error_base   0x40060000
#define  heap_bad_block    (heap_error_base + 1)
#define  heap_no_mem       (heap_error_base + 2)

/* conditional compile for the memory manager */
/* if MEMORYMAN is not defined use system malloc calloc etc. */


/*
  *--------------------------------------------------------------
  * BEGIN NORMAL C MEMORY MANAGEMENT SYSTEM
  *--------------------------------------------------------------
*/

/* use standard calls to malloc, calloc, etc */

char *safe_malloc(size)
unsigned size;
{
    char *p;

    extern char *malloc() ;

    if ((p = malloc(size)) == (char *) 0) {
        cleanupHandler(heap_no_mem,"safe_malloc");
    }
    return p;
}


char *safe_realloc(obj, size)
char *obj;
unsigned size;
{
    char *p;

    extern char *realloc() ;

    if ((p = realloc(obj, size)) == (char *) 0) {
        cleanupHandler(heap_no_mem,"safe_realloc");
    }
    return p;
}


char *safe_calloc(size, num)
unsigned size, num;
{
    char *p;

    extern char *calloc() ;

    if ((p = calloc(size, num)) == (char *) 0) {
        cleanupHandler(heap_no_mem,"safe_calloc");
    }
    return p;
}
/* when not testing memory just call system free */
safe_free(ptr)
char *ptr;
{
    free(ptr);
    return;
}

safe_cfree(ptr)
char *ptr;
{
#ifndef SPEC_CPU2000
    cfree(ptr);
#endif
    return;
}
/*
  *--------------------------------------------------------------
  * END NORMAL C MEMORY MANAGEMENT SYSTEM
  *--------------------------------------------------------------
*/

int cleanup(sigNum)
int sigNum ;
{

    cleanupHandler(-sigNum,NULL) ;

}

int cleanupHandler(status,function)
int status ;
char *function ;
{

    exit(1) ;

}
