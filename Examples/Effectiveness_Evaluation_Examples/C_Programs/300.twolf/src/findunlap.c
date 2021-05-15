#include "standard.h"
int *add_to_row ;
int *length_of_row ;

findunlap( before_feeds )
int before_feeds ;
{

CBOXPTR cellptr , ptr ;
TIBOXPTR tileptr ;
TEBOXPTR term ;
DBOXPTR dimptr ;
NBOXPTR termptr , netptr ;
int cost , corient ;
int block , cell , bin ;
int i , n ;
int bigblkx ;
int net , x , y , *blklen , row ;

blklen = (int *) safe_malloc( (numblock + 1) * sizeof( int ) ) ;
for( i = 0 ; i <= numblock ; i++ ) {
    blklen[i]  = 0 ;
}

if( before_feeds == 1 ) {
    unlap(1) ;
} else if( before_feeds == 0 ) {
    unlap(0) ;
}

if( before_feeds == 1 ) {
    for( block = 1 ; block <= numblock ; block++ ) {
	for( bin = 0 ; bin <= numBins ; bin++ ) {
	    safe_free( binptr[ block ][ bin ]->cell ) ;
	    safe_free( binptr[ block ][ bin ] ) ;
	}
	safe_free( binptr[ block ] ) ;
    }
    safe_free( binptr ) ;
}

for( cell = 1 ; cell <= numcells ; cell++ ) {
    ptr = carray[ cell ] ;
    corient = ptr->corient ;
    for( term = ptr->tileptr->termsptr ; term != TERMNULL ;
				  term = term->nextterm ) {
	termptr = tearray[ term->cellterm ] ;
        termptr->xpos = term->txpos[ corient/2 ] + ptr->cxcenter;
        termptr->ypos = term->typos[ corient%2 ] + ptr->cycenter;
    }
}
for( cell = numcells + 1 ; cell <= numcells + numterms ; cell++ ) {
    ptr = carray[ cell ] ;
    for( term = ptr->tileptr->termsptr ; term != TERMNULL ;
				  term = term->nextterm ) {
	termptr = tearray[ term->cellterm ] ;
        termptr->xpos = term->txpos[ 1 ] + ptr->cxcenter;
        termptr->ypos = term->typos[ 1 ] + ptr->cycenter;
    }
}

cost  = 0 ;
for( net = 1 ; net <= numnets ; net++ ) {
    dimptr =  netarray[ net ] ;
    if( (netptr = dimptr->netptr) != NETNULL ) {
	dimptr->xmin = dimptr->xmax = netptr->xpos ;
	dimptr->ymin = dimptr->ymax = netptr->ypos ;
	dimptr->Lnum = dimptr->Rnum = 1 ;
	dimptr->Bnum = dimptr->Tnum = 1 ;
	netptr = netptr->nterm ;
    }
    n = 1 ;
    for( ; netptr != NETNULL ; netptr = netptr->nterm ) {
	x = netptr->xpos ;
	y = netptr->ypos ;
	if( x < dimptr->xmin ) {
	    dimptr->xmin = x ;
	    dimptr->Lnum = 1 ;
	} else if( x == dimptr->xmin ) {
	    dimptr->Lnum++ ;
	    if( x == dimptr->xmax ) {
		dimptr->Rnum++ ;
	    }
	} else if( x > dimptr->xmax ) {
	    dimptr->xmax = x ;
	    dimptr->Rnum = 1 ;
	} else if( x == dimptr->xmax ) {
	    dimptr->Rnum++ ;
	}
	if( y < dimptr->ymin ) {
	    dimptr->ymin = y ;
	    dimptr->Bnum = 1  ;
	} else if( y == dimptr->ymin ) { 
	    dimptr->Bnum++ ;
	    if( y == dimptr->ymax ) {
		dimptr->Tnum++ ;
	    }
	} else if( y > dimptr->ymax ) {
	    dimptr->ymax = y ;
	    dimptr->Tnum = 1  ;
	} else if( y == dimptr->ymax ) {
	    dimptr->Tnum++ ;
	}
	n++ ;
    }
    dimptr->numpins = n ;
    cost += ((int)( dimptr->Hweight *
	    (double)( dimptr->xmax - dimptr->xmin))) +
	    ((int)( dimptr->Vweight *
	    (double)( dimptr->ymax - dimptr->ymin)));
}
funccost = cost ;


for( cell = 1 ; cell <= numcells ; cell++ ) {
    cellptr = carray[ cell ] ;
    tileptr = cellptr->tileptr ;
    block    = cellptr->cblock ;
    blklen[ block ] += tileptr->right - tileptr->left  ;
}

if( before_feeds == 1 ) {
    length_of_row = (int *) safe_malloc( (numRows+1) * sizeof(int) );
    add_to_row = (int *) safe_malloc( (numRows+1) * sizeof(int) );
    for( row = 1 ; row <= numRows ; row++ ) {
	length_of_row[row] = blklen[row] ; 
	add_to_row[row] = 0 ;
    }
}

if( before_feeds >= 0 ) {
    bigblkx = 0 ;
    if( before_feeds == 1 ) {
	fprintf(fpo,"Before Feeds are Added:\n");
    }
    fprintf(fpo,"BLOCK      TOTAL CELL LENGTHS      OVER/UNDER TARGET\n");
    for( i = 1 ; i <= numblock ; i++ ) {
	if( blklen[i] > blklen[ bigblkx ] ) {
	    bigblkx = i ;
	}
	fprintf( fpo, "%3d            %7d                %6d\n", i,
			blklen[i] ,  (blklen[i] - barray[i]->desire) );
    }
    fprintf( fpo, "\nLONGEST Block is:%d   Its length is:%d\n",
				bigblkx , blklen[ bigblkx ] ) ;
}
safe_free( blklen ) ;
return ;
}
