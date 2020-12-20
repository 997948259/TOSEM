#include "standard.h"

outcm()
{

char filename[64] ;
FILE *fp ;
NBOXPTR netptr ;
int net , x , local_pin_count , pin_count ;
int cell , row , length , xstart ;


sprintf( filename , "%s.cm" , cktName ) ;
fp = twopen ( filename , "w", ABORT ) ;

pin_count = 0 ;
for( net = 1 ; net <= numnets ; net++ ) {
    local_pin_count = 0 ;
    for( netptr = netarray[net]->netptr; netptr; netptr = netptr->nterm){
	if( netptr->cell <= numcells ) {
	    local_pin_count++ ;
	}
    }
    if( local_pin_count > 1 ) {
	pin_count += local_pin_count ;
    }
}
fprintf(fp,"%d\n", pin_count ) ;

for( net = 1 ; net <= numnets ; net++ ) {
    local_pin_count = 0 ;
    for( netptr = netarray[net]->netptr; netptr; netptr = netptr->nterm){
	if( netptr->cell <= numcells ) {
	    local_pin_count++ ;
	}
    }
    if( local_pin_count <= 1 ) {
	continue ;
    }
    for( netptr = netarray[net]->netptr; netptr; netptr = netptr->nterm){
	if( netptr->cell > numcells ) {
	    continue ;
	}
	cell = netptr->cell ;
	row  = carray[cell]->cblock ;
	x    = netptr->xpos ;
	length = carray[cell]->tileptr->right - 
					carray[cell]->tileptr->left ;
	xstart = carray[cell]->cxcenter + carray[cell]->tileptr->left ;

	fprintf(fp,"%8d %8d %8d %8d %8d %8d\n", row, cell, net,
						 x, length, xstart );
    }
}
fclose(fp);

return ;
}
