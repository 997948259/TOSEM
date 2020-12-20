#include "standard.h"
#include "groute.h"
int stage ;
extern int estimate_feeds ;
extern double T ;
extern int iteration ;
extern int impcount ;
extern int *fixarray ;
extern double binpenCon , roLenCon , cost_scale_factor ;
int last_level ;

savewolf( level )
int level ;
{

FILE *fp ;
int xcenter , ycenter ;
int cell , block , orient , seg ;
char filename[64] ;
char file1[1024], file2[1024];
CBOXPTR cellptr ;
double cpu_time();
double current_time;
static double last_time = 0.0;

#ifndef VMS
/* make sure another checkpoint is worthwhile !! */
current_time = cpu_time();
if ((current_time - last_time) < 600.0 && 
		level == last_level && level <= 1 ) {
    return;
}
last_time = current_time;
last_level = level;
#endif

#ifdef VMS
if( level == 1 ) {
    sprintf( filename , "%s.sav" , cktName ) ;
    fp = twopen( filename , "w", ABORT ) ;
    sprintf( filename , "%s.sav;-2" , cktName ) ;
    delete( filename ) ;
} else {
    sprintf( filename , "%s.sv2" , cktName ) ;
    fp = twopen( filename , "w", ABORT ) ;
    sprintf( filename , "%s.sv2;-2" , cktName ) ;
    delete( filename ) ;
}
#else
sprintf( filename , "%s.tmp" , cktName ) ;
fp = twopen( filename , "w", ABORT ) ;
#endif

fprintf( fp, "%f\n", T ) ;
fprintf( fp, "%d\n", iteration ) ;
fprintf( fp, "%d\n", ffeeds ) ;
fprintf( fp, "%d\n", level ) ;

fprintf( fp, "%f\n", binpenCon ) ;
fprintf( fp, "%f\n", roLenCon ) ;
fprintf( fp, "%f\n", cost_scale_factor ) ;
fprintf( fp, "%d\n", estimate_feeds ) ;


if( level == 3 ) {
    fprintf(fp,"%d\n", numSegs ) ;
    for( seg = 1 ; seg <= numSegs ; seg++ ) {
	fprintf(fp,"%d\n", aNetSeg[seg].current ) ;
    }
}

for( cell = 1 ; cell <= numcells + numterms ; cell++ ) {
    cellptr = carray[ cell ] ;
    orient  = cellptr->corient   ;
    block   = cellptr->cblock    ;
    xcenter = cellptr->cxcenter  ;
    ycenter = cellptr->cycenter  ;
    fprintf( fp , "%d %d %d %d %d\n", cell , block , 
			       orient , xcenter , ycenter ) ;
}
twclose( fp ) ;
#ifndef VMS
sprintf(file1, "%s.tmp", cktName);
if( level == 1 ) {
    sprintf(file2, "%s.sav", cktName);
} else {
    sprintf(file2, "%s.sv2", cktName);
}
unlink(file2);
rename(file1, file2);
#endif
return ;
}

TW_oldin( fp )
FILE *fp ;
{

int cell , orient , numfds ;
int block , xcenter , ycenter , dummy ;
CBOXPTR ptr ;
TEBOXPTR term ;
NBOXPTR termptr ;


fscanf( fp , "%lf" , &T ) ;
fscanf( fp , "%d" , &iteration ) ;
fscanf( fp , "%d" , &numfds ) ;
fscanf( fp , "%d" , &dummy ) ;

fscanf( fp , "%lf" , &binpenCon ) ;
fscanf( fp , "%lf" , &roLenCon ) ;
fscanf( fp , "%lf" , &cost_scale_factor ) ;
fscanf( fp , "%d" , &estimate_feeds ) ;

while( fscanf( fp , " %d %d %d %d %d ", &cell , &block , &orient , 
				    &xcenter , &ycenter ) == 5 ) {
    ptr = carray[ cell ] ;
    ptr->cblock   = block   ;
    ptr->corient  = orient  ;
    ptr->cxcenter = xcenter ;
    ptr->cycenter = ycenter ;
    if( cell <= numcells ) {
	for( term = ptr->tileptr->termsptr ; 
			term != TERMNULL ; term = term->nextterm ) {
	    termptr = tearray[term->cellterm] ;
	    termptr->xpos = term->txpos[ orient/2 ] + xcenter ;
	    termptr->ypos = term->typos[ orient%2 ] + ycenter ;
	}
    } else {
	for( term = ptr->tileptr->termsptr ; 
			term != TERMNULL ; term = term->nextterm ) {
	    termptr = tearray[term->cellterm] ;
	    termptr->xpos = term->txpos[ 1 ] + xcenter ;
	    termptr->ypos = term->typos[ 1 ] + ycenter ;
	}
    }
}
return ;
}


fixfdpos( fp )
FILE *fp ;
{

int cell , orient , numfds , dummy , number , seg , current ;
int block , xcenter , ycenter , junk ;
double d_dummy ;
CBOXPTR ptr ;


fscanf( fp , "%lf" , &T ) ;
fscanf( fp , "%d" , &iteration ) ;
fscanf( fp , "%d" , &numfds ) ;
fscanf( fp , "%d" , &dummy ) ;
fscanf( fp , "%lf" , &d_dummy ) ;
fscanf( fp , "%lf" , &d_dummy ) ;
fscanf( fp , "%lf" , &d_dummy ) ;
fscanf( fp , "%d" , &junk ) ;

if( dummy == 3 ) {
    fscanf(fp,"%d", &number ) ;
    fixarray = (int *) safe_malloc( (number + 1) * sizeof(int) ) ;
    for( seg = 1 ; seg <= number ; seg++ ) {
	fscanf(fp,"%d", &current ) ;
	fixarray[seg] = current ;
    }
}
while( fscanf( fp , " %d %d %d %d %d ", &cell , &block , &orient , 
				    &xcenter , &ycenter ) == 5 ) {
    ptr = carray[ cell ] ;
    ptr->cxcenter = xcenter ;
    ptr->cycenter = ycenter ;
    ptr->corient  = orient ;
}
return ;
}
