#include "standard.h"
#define T 2
#define R 3
int old_feed_length = 0 ;

configuref( feed_length )
int feed_length ;
{

CBOXPTR padptr ;
int core_left , core_right , core_span , row , pad , right ;
int shift_amount ;

shift_amount = (feed_length / numRows) - (old_feed_length / numRows) ;
if( shift_amount == 0 ) {
    for( row = 1 ; row <= numRows ; row++ ) {
	barray[row]->oldsize  = 0 ;
    }
    return ;
}

core_right = 0 ;
core_left  = 10000000 ;
for( row = 1 ; row <= numRows ; row++ ) {
    barray[row]->bright  += shift_amount ;
    barray[row]->blength += shift_amount ;
    barray[row]->desire  += shift_amount ;
    barray[row]->oldsize  = 0 ;
    rowArray[row].endx   += shift_amount ;
    if( rowArray[row].startx < core_left ) {
	core_left = rowArray[row].startx ;
    }
    if( rowArray[row].endx > core_right ) {
	core_right = rowArray[row].endx ;
    }
}
core_span = core_right - core_left ;

for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    padptr = carray[pad] ;
    if( padptr->padside == R || padptr->padside == MR ||
		padptr->padside == MUR || padptr->padside == MLR ) {
	padptr->cxcenter += shift_amount ;
    } else if( padptr->padside == T || padptr->padside == B ||
		padptr->padside == MTT || padptr->padside == MBB ) {
	right = padptr->cxcenter + padptr->tileptr->right - core_left;
	padptr->cxcenter += (int)(
		((double)right / (double) core_span) *
		((double) shift_amount) ) ;
    }
}

old_feed_length = feed_length ;

return ;
}
