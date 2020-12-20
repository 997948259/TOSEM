#include "standard.h"
extern int no_feeds_side_nets ;
extern int *blkToRow ;
#define T   2 
#define R   3 


assignro()
{
TEBOXPTR pinptr ;
NBOXPTR tmptr ;
int row , cell , pad ;
int yc , yb , blk ;

rowgrid = ( short int ** ) safe_malloc( (numRows + 2) * 
					    sizeof(short int *));
for( row = 0 ; row <= numRows + 1 ; row++ ) {
    rowgrid[row] = (short int *) safe_malloc( 3 * sizeof( short int ) );
}

for( cell = 1 ; cell <= numcells ; cell++ ) {
    pinptr = carray[cell]->tileptr->termsptr ;
    row = blkToRow[ carray[cell]->cblock ] ;
    for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
	tmptr = tearray[pinptr->cellterm] ;
	tmptr->row = row ;
    }
}
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == T || carray[pad]->padside == MTT ) {
	row = numRows + 1 ;
	pinptr = carray[pad]->tileptr->termsptr ;
	for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
	    tmptr = tearray[pinptr->cellterm] ;
	    tmptr->row = row ;
	}
    } else if(carray[pad]->padside == B || carray[pad]->padside == MBB){
	row = 0 ;
	pinptr = carray[pad]->tileptr->termsptr ;
	for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
	    tmptr = tearray[pinptr->cellterm] ;
	    tmptr->row = row ;
	}
    } else {  /* side pad or internal macro block */
	pinptr = carray[pad]->tileptr->termsptr ;
	for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
	    tmptr = tearray[pinptr->cellterm] ;
	    if( no_feeds_side_nets == 1 ) {
		if( carray[pad]->padside == L || 
				    carray[pad]->padside == R ) {
		    netarray[ tmptr->net ]->feedflag = 1 ;
		}
	    }
	    yc = carray[pad]->cycenter + pinptr->typos[1] ;
	    for( blk = 1 ; blk <= numRows ; blk++ ) {
		if( rowArray[blk].ypos >= yc ) {
		    break ;
		}
	    }
	    if( blk == 1 ) {
		row = 1 ;
	    } else if( blk > numRows ) {
		row = numRows ;
	    } else {
		yb = rowArray[blk].ypos ;
		if( yb - yc < yc - rowArray[blk - 1].ypos ) {
		    row = blk ;
		} else {
		    row = blk - 1 ;
		}
	    }
	    tmptr->row = row ;
	}
    }
}
return ;
}
reassign()
{

TEBOXPTR pinptr ;
NBOXPTR tmptr ;
int row , cell , pad ;
int yc , yb , blk ;

for( cell = 1 ; cell <= numcells ; cell++ ) {
    pinptr = carray[cell]->tileptr->termsptr ;
    row = blkToRow[ carray[cell]->cblock ] ;
    for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
	tmptr = tearray[pinptr->cellterm] ;
	tmptr->row = row ;
    }
}
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == T || carray[pad]->padside == MTT ) {
	row = numRows + 1 ;
	pinptr = carray[pad]->tileptr->termsptr ;
	for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
	    tmptr = tearray[pinptr->cellterm] ;
	    tmptr->row = row ;
	}
    } else if(carray[pad]->padside == B || carray[pad]->padside == MBB){
	row = 0 ;
	pinptr = carray[pad]->tileptr->termsptr ;
	for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
	    tmptr = tearray[pinptr->cellterm] ;
	    tmptr->row = row ;
	}
    } else {  /* side pad or internal macro block */
	pinptr = carray[pad]->tileptr->termsptr ;
	for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
	    tmptr = tearray[pinptr->cellterm] ;
	    if( no_feeds_side_nets == 1 ) {
		if( carray[pad]->padside == L || 
				    carray[pad]->padside == R ) {
		    netarray[ tmptr->net ]->feedflag = 1 ;
		}
	    }
	    yc = carray[pad]->cycenter + pinptr->typos[1] ;
	    for( blk = 1 ; blk <= numRows ; blk++ ) {
		if( rowArray[blk].ypos >= yc ) {
		    break ;
		}
	    }
	    if( blk == 1 ) {
		row = 1 ;
	    } else if( blk > numRows ) {
		row = numRows ;
	    } else {
		yb = rowArray[blk].ypos ;
		if( yb - yc < yc - rowArray[blk - 1].ypos ) {
		    row = blk ;
		} else {
		    row = blk - 1 ;
		}
	    }
	    tmptr->row = row ;
	}
    }
}

return ;
}
