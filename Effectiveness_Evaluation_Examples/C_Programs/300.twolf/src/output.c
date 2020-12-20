#include "standard.h"
int comparex() ;
extern int lrtxspan ;
extern int lrtyspan ;
extern int **pairArray ;
extern int costonly ;
extern int restart  ;

output()
{

FILE *fpp1 , *fpp2 ;
int locx , locy , height , width , k , Wwd ;
int xloc , i , cell , block , orient ;
int num ;
int xloc2 , yloc2 , yloc ;
int *array , desire ;
int left , right , bottom , top , end ;
char filename[64] ;
CBOXPTR cellptr ;


sprintf( filename , "%s.pl1" , cktName ) ;
fpp1 = twopen( filename , "w", ABORT ) ;

sprintf( filename , "%s.pl2" , cktName ) ;
fpp2 = twopen( filename , "w", ABORT ) ;

for( block = 1 ; block <= numblock ; block++ ) {

    left   = barray[block]->bxcenter + barray[block]->bleft   ;
    right  = barray[block]->bxcenter + barray[block]->bright  ;
    bottom = barray[block]->bycenter + barray[block]->bbottom ;
    top    = barray[block]->bycenter + barray[block]->btop    ;

    if( restart == 0 && costonly == 1 ) {
	desire = barray[block]->desire ;
    } else {
	if( pairArray[block][0] > 0 ) {
	    cell = pairArray[block][ pairArray[block][0] ] ;
	    end  = carray[cell]->cxcenter + carray[cell]->tileptr
			    ->right ;
	    desire = end - left ;
	} else {
	    desire = 0 ;
	}
    }

    if( barray[block]->borient > 0 ) {
	fprintf(fpp2,"%d %d %d  %d %d  0 0\n", block ,
			    left, bottom, left + desire, top ) ;
    } else {
	fprintf(fpp2,"%d %d %d  %d %d  0 0\n", block ,
			    left, bottom, right, bottom + desire ) ;
    }

    num = pairArray[block][0] ;
    if( num == 0 ) {
	continue ;
    }
    array = pairArray[block] + 1 ;

    for( i = 0 ; i < num ; i++ ) {
	cell = array[ i ] ;
	cellptr = carray[ cell ] ;
	orient = cellptr->corient ;

	xloc = cellptr->cxcenter + cellptr->tileptr->left ;
	yloc = cellptr->cycenter + cellptr->tileptr->bottom ;

	xloc2 = cellptr->tileptr->right - 
		cellptr->tileptr->left ; 
	yloc2 = cellptr->tileptr->top - 
		cellptr->tileptr->bottom ; 

	fprintf(fpp1,"%s %d %d  %d %d  %d %d\n", 
			    cellptr->cname , 
			    xloc, yloc, xloc + xloc2, 
			    yloc + yloc2, orient, block ) ;
    }
}


for( i = numcells + 1 ; i <= numcells + numterms ; i++ ) {
    cellptr = carray[ i ]  ;
    orient = cellptr->corient ;

    locx = cellptr->cxcenter + cellptr->tileptr->left ;
    locy = cellptr->cycenter + cellptr->tileptr->bottom;

    height = cellptr->tileptr->top - cellptr->tileptr->bottom ;
    width = cellptr->tileptr->right - cellptr->tileptr->left ;

    fprintf(fpp1,"%s %d %d  %d %d  %d 0\n", cellptr->cname , 
				    locx, locy, locx + width, 
				    locy + height, orient ) ;
    fprintf(fpp2,"%s %d %d  %d %d  %d 0\n", cellptr->cname , 
				    locx, locy, locx + width, 
				    locy + height, orient ) ;
}
twclose( fpp1 ) ;
twclose( fpp2 ) ;
return ;
}




comparex( a , b )
int *a , *b ;

{
    return( carray[ *a ]->cxcenter - carray[ *b ]->cxcenter ) ;
}
