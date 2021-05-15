/* utils.h - utility routine insert file */

#ifndef UTILS_H
#define UTILS_H
#endif
 
#define LRECL 255

#ifdef HAVE_LIMITS_H
#include <limits.h>
#else 

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

#ifndef INT_MIN
#define INT_MIN (-INT_MAX - 1)
#endif

#endif /* HAVE_LIMITS_H */


extern FILE *fpo ;
extern initProgram() ;
extern char *getProgName() ;
extern char *strclone() ;
extern void *safe_malloc(long bytes) ;
extern void *safe_calloc(long num_entries, long bytes) ;
extern void *safe_realloc(void *ptr,long bytes) ;
