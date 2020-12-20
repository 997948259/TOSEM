#include "standard.h"
/* #define DEBUG */
extern FILE *fpo ;
int *blklist ;
extern int **pairArray ;
extern double rowSep ;
extern int rowHeight ;
typedef struct int2 {
    int sleft ;
    int srite ;
} INT2 ;
INT2 *blkshifts ;

#define L   1 
#define T   2 
#define R   3 
#define B   4 
#define MUL 5 
#define MUR 6 
#define MLL 7 
#define MLR 8 
#define ML  9 
#define MR  10
#define MB  11 
#define MT  12 
#define MM  13 
#define MTT 14 
#define MBB 15 
extern double macspace[] ;

xcompact()
{

int blk , pad , k , bot , top , rite , left , maxd , cell , end , mind ;
int padside ;
CBOXPTR padptr , cellptr ;

blklist = (int *) safe_malloc( (numblock + 1) * sizeof( int ) ) ;
blkshifts = (INT2 *) safe_malloc( (numblock + 1) * sizeof( INT2 ) ) ;
for( blk = 1 ; blk <= numblock ; blk++ ) {
    blkshifts[blk].sleft = -1000 ;
}

for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == MT || carray[pad]->padside == MM ||
				      carray[pad]->padside == MB ) {
	padptr  = carray[pad] ;
	padside = padptr->padside ;
	rite = padptr->cxcenter + padptr->tileptr->right ;
	left = padptr->cxcenter + padptr->tileptr->left ;
	bot = padptr->cycenter + padptr->tileptr->bottom 
				    - rowSep * rowHeight * 0.67;
	top = padptr->cycenter + padptr->tileptr->top 
				    + rowSep * rowHeight * 0.67 ;
	findblks( bot , top , rite , -1 ) ;
	maxd = 0 ;
	for( k = 1 ; k <= blklist[0] ; k++ ) {
	    blk = blklist[k] ;
	    cell = pairArray[blk][ pairArray[blk][0] ] ;
	    cellptr = carray[cell] ;
	    if( cellptr->cxcenter + cellptr->tileptr->right > maxd ) {
		maxd = cellptr->cxcenter + cellptr->tileptr->right  ;
	    }
	}
	for( k = 1 ; k <= blklist[0] ; k++ ) {
	    blk = blklist[k] ;
	    blkshifts[blk].srite = maxd ;
	    blkshifts[blk].sleft = barray[blk]->bxcenter +
						    barray[blk]->bleft ;
	}
	findblks( bot , top , rite , 1 ) ;
	carray[pad]->cxcenter += macspace[padside] - (left - maxd);
	for( k = 1 ; k <= blklist[0] ; k++ ) {
	    blk = blklist[k] ;
	    barray[blk]->bxcenter += macspace[padside] - 
						    (left - maxd) ;
	    for( k = 1 ; k <= pairArray[blk][0] ; k++ ) {
		cell = pairArray[blk][k] ;
		carray[cell]->cxcenter += macspace[padside] - 
						    (left - maxd) ;
	    }
	}
    }
}
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    padptr = carray[ pad ] ;
    if( padptr->padside == MUR || padptr->padside == MR ||
				      padptr->padside == MLR ) {
	padside = padptr->padside ;
	rite = padptr->cxcenter + padptr->tileptr->right ;
	left = padptr->cxcenter + padptr->tileptr->left ;
	bot = padptr->cycenter + padptr->tileptr->bottom 
					- rowSep * rowHeight * 0.33 ;
	top = padptr->cycenter + padptr->tileptr->top  
					+ rowSep * rowHeight * 0.33 ;
	findblks( bot , top , rite , -1 ) ;
	maxd = 0 ;
	for( k = 1 ; k <= blklist[0] ; k++ ) {
	    blk = blklist[k] ;
	    cell = pairArray[blk][ pairArray[blk][0] ] ;
	    cellptr = carray[cell] ;
	    if( cellptr->cxcenter + cellptr->tileptr->right > maxd ) {
		maxd = cellptr->cxcenter + cellptr->tileptr->right ;
	    }
	}
	for( k = 1 ; k <= blklist[0] ; k++ ) {
	    blk = blklist[k] ;
	    blkshifts[blk].srite = maxd ;
	    blkshifts[blk].sleft = barray[blk]->bxcenter +
						    barray[blk]->bleft ;
	}
	carray[pad]->cxcenter += macspace[padside] - (left - maxd);

    }
}
/*
 *  Find the rightmost pad with padside MUR, MR, MLR, MTT, or MBB
 *  or the rightmost blk 
 */
maxd = 0 ;
for( blk = 1 ; blk <= numblock ; blk++ ) {
    if( pairArray[blk][0] <= 0 ) {
	continue ;
    }
    cell = pairArray[blk][ pairArray[blk][0] ] ;
    end = carray[cell]->cxcenter + carray[cell]->tileptr->right ;
    if( end > maxd ) {
	maxd = end ;
    }
}
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    padptr = carray[pad] ;
    if( padptr->padside == MUR || padptr->padside == MR ||
        padptr->padside == MLR || padptr->padside == MTT ||
                                       padptr->padside == MBB ) {
	if( padptr->cxcenter + padptr->tileptr->right  > maxd ) {
	    maxd = padptr->cxcenter + padptr->tileptr->right ;
	}
    }
}
for( blk = 1 ; blk <= numblock ; blk++ ) {
    if( blkshifts[blk].sleft == -1000 ) {
	blkshifts[blk].srite = maxd ;
	blkshifts[blk].sleft = barray[blk]->bxcenter +
						    barray[blk]->bleft ;
    }
}
/*
 *  Find the innermost left edge of the R pads
 */
mind = 32000 ;
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    padptr = carray[pad] ;
    if( padptr->padside == R ) {
	if( padptr->cxcenter + padptr->tileptr->left < mind ) {
	    mind = padptr->cxcenter + padptr->tileptr->left ;
	}
    }
}
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == R ) {
	carray[pad]->cxcenter += rowSep * rowHeight - (mind - maxd);
    }
}
#ifdef DEBUG
for( blk = 1 ; blk <= numblock ; blk++ ) {
    fprintf(fpo,"blk:%d  sleft:%d  srite:%d\n",blk,blkshifts[blk].sleft,
					blkshifts[blk].srite ) ;
}
#endif

return ;
}

findblks( bot , top , rite , direction ) 
int bot , top , rite , direction ;
{

int blk ;

blklist[0] = 0 ;
for( blk = 1 ; blk <= numblock ; blk++ ) {
    if( barray[blk]->bycenter > bot && barray[blk]->bycenter < top ) {
	if( direction == -1 ) {
	    if( barray[blk]->bxcenter + barray[blk]->bright < rite ) {
		if( blkshifts[blk].sleft == -1000 ) {
		    blklist[ ++blklist[0] ] = blk ;
		}
	    }
	} else {
	    if( barray[blk]->bxcenter + barray[blk]->bleft > rite ) {
		blklist[ ++blklist[0] ] = blk ;
	    }
	}
    }
}

return ;
}
