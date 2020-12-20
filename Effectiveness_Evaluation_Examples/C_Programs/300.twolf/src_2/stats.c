#include "standard.h"

#ifndef VMS
#include <sys/types.h>
#endif

print_stats(fp)
FILE *fp;
{
    fprintf(fp, "Usage statistics not available\n");
}


double cpu_time()
{
    return 0.0;
}
