#include <stdio.h>

#ifndef UTILS_H
#include "utils.h"
#endif
 
#include "main.h"
#include "standard.h"

static char programName[LRECL];
static char progVersion[LRECL];
static char progDate[LRECL];

initProgram(name,version) 
char *name ;
char *version ;
{
    char    message[LRECL] ,
	    *date ,
	    *getCompileDate() ;

    int     i ;

    sprintf(programName,"%s",name);
    sprintf(progVersion,"%s",version);
     
    if ( date = getCompileDate() ){
	sprintf(progDate,"%s",date);
    } else {
	sprintf(progDate,"unknown") ;
    }

    fprintf(fpo,"\n%s version:%s date:%s\n",programName,progVersion,progDate) ;
    fprintf(fpo,"Standard Cell Placement and Global Routing Program\n");
    fprintf(fpo,"Authors: Carl Sechen, Bill Swartz\n");
    fprintf(fpo,"          Yale University\n");

    printf("\n%s version:%s date:%s\n",programName,progVersion,progDate) ;
    printf("Standard Cell Placement and Global Routing Program\n");
    printf("Authors: Carl Sechen, Bill Swartz\n");
    printf("         Yale University\n");

    safe_free(date) ;

    /* inialize variables */
#if 0
    randomSeed  = time(0) ;
#endif
    randomSeed  = 123456789 ;

    fixarray = (int *) NULL ;
    ffeeds = 0 ;
    for( i = 1 ; i <= 15 ; i++ ) {
	macspace[i] = -1.0 ;
    }
    costonly = 0 ;
    fdthrus = 0 ;
    doglobal = 0 ;
    cswaps = 0 ;

    imprange = -1.0 ;
    attprcel = 0 ;

    addFeeds = 0 ;
    fdWidth  = -1 ;
    rowSep = -1.0 ;
    indent = 1.0 ;
    numSegs = 0 ;
    resume_run = NO ;
    pin_layers_given = 0 ;
    no_feeds_side_nets = 0 ;
    no_net_normalize = 0 ;
    cost_scale_factor = 1.0 ;
    feedLayer = 0 ;
    tw_fast = 0 ;
    estimate_feeds = 1 ;
    connection_machine = 0 ;

    gate_array_special = FALSE ;
#if 0
    randomSeed  = time(0) ;
#endif
    randomSeed2 = 987654321;

} /* end initProgram */
 
    
char *getProgName()
{
 
    return(strclone(programName));
}

/* strclone - clone a string - user must free memory when done */
char *strclone(str)
char *str ;
{
    char *copy ;

    if( str ){  /* first check for null pointer */
	if( *str ){  /* first check allow dereference */
	    copy = (char *) safe_malloc(strlen(str)+1) ;
	    sprintf(copy,"%s",str) ;
	    return(copy) ;
	}
    }
    return(NULL) ;

} /* end strclone */

FILE *openFile(filename,readwrite,abort)
char *filename ;
char *readwrite ;
int  abort ;
{

    FILE *fileptr ;

    fileptr = fopen( filename, readwrite );

    if( !(fileptr) && abort ){
	printf("could not open file %s\n",filename ) ;
	exit(TW_FAIL) ;
    }
    return( fileptr ) ;

} /* end openFile */
