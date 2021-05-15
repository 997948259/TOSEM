#include "standard.h"

extern int max_blklength ;
extern int rowpenal , binpenal ;
extern double roLenCon ;
extern double binpenCon ;
extern int blkleft , blkrite ;


findcostf()
{
TIBOXPTR tile , tileptr1 ;
CBOXPTR cellptr1 , ptr ;
DBOXPTR dimptr ;
NBOXPTR netptr , termptr ;
TEBOXPTR term  ;
BINPTR bptr ;
int left , right , corient ;
int bin , LoBin , HiBin ;
int block , cell , net , blk ;
int startx , endx ;
int x , y , cost=0 ;
int n , k , cbin ;
int old_numBins ;

blkleft = 32000 ;
blkrite = 0      ;
for( block = 1 ; block <= numblock ; block++ ) {
    if( barray[ block ]->bxcenter + barray[ block ]->bleft <
						blkleft ) {
	blkleft = barray[ block ]->bxcenter +
					barray[ block ]->bleft ;
    } 
    if( barray[ block ]->bxcenter + 
			barray[ block ]->bright > blkrite ) {
	blkrite = barray[ block ]->bxcenter +
				    barray[ block ]->bright ;
    }
}
binOffst = blkleft ;
max_blklength = blkrite - blkleft ;

old_numBins = numBins ;
numBins = (int)( ( blkrite - binOffst ) / binWidth ) ;
if( ( blkrite - binOffst ) > ( numBins * binWidth ) ) {
    numBins++ ;
}

sortpin() ;
for( cell = 1 ; cell <= numcells + numterms ; cell++ ) {
    ptr = carray[ cell ] ;
    corient = ptr->corient ;
    block   = ptr->cblock  ;
    tile    = ptr->tileptr ;
    if( cell <= numcells ) {
	ptr->cycenter = barray[block]->bycenter ;
	for( term = tile->termsptr ; term != TERMNULL ;
				      term = term->nextterm ) {
	    termptr = tearray[ term->cellterm ] ;
	    termptr->xpos = term->txpos[corient/2] + ptr->cxcenter;
	    termptr->ypos = term->typos[corient%2] + ptr->cycenter;
	}
    } else {
	for( term = tile->termsptr ; term != TERMNULL ;
				      term = term->nextterm ) {
	    termptr = tearray[ term->cellterm ] ;
	    termptr->xpos = term->txpos[1] + ptr->cxcenter;
	    termptr->ypos = term->typos[1] + ptr->cycenter;
	}
    }
}

cost = 0 ;
for( net = 1 ; net <= numnets ; net++ ) {
    dimptr =  netarray[ net ] ;
    if( (netptr = dimptr->netptr) != NETNULL ) {
	dimptr->xmin = dimptr->xmax = netptr->xpos ;
	dimptr->ymin = dimptr->ymax = netptr->ypos ;
	dimptr->Lnum = dimptr->Rnum = 1 ;
	dimptr->Bnum = dimptr->Tnum = 1 ;
	netptr = netptr->nterm ;
    }
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
    }
    cost += ((int)( dimptr->Hweight *
	    (double)( dimptr->xmax - dimptr->xmin))) +
	    ((int)( dimptr->Vweight *
	    (double)( dimptr->ymax - dimptr->ymin)));
}


binpenal = 0 ;
rowpenal = 0 ;
penalty = 0 ;

for( block = 1 ; block <= numblock ; block++ ) {
    for( bin = 0 ; bin <= old_numBins ; bin++ ) {
	safe_free( binptr[block][bin]->cell ) ;
	safe_free( binptr[block][bin] ) ;
    }
    safe_free( binptr[block] ) ;
}

for( block = 1 ; block <= numblock ; block++ ) {

    binptr[block] = (BINPTR * ) safe_malloc( (numBins + 1) *
				      sizeof( BINPTR ) ) ;
    left  = barray[ block ]->bleft + barray[ block ]->bxcenter ;
    right = barray[ block ]->bleft + barray[ block ]->bxcenter 
				   + barray[ block ]->desire   ;
    LoBin = SetBin( left ) ;
    HiBin = SetBin( right ) ;
    
    for( bin = 0 ; bin <= numBins ; bin++ ) {
	binptr[block][bin] = (BINBOX *) safe_malloc( 
					    sizeof(BINBOX) ) ; 
	binptr[block][bin]->cell = (int *)safe_malloc( 
					    10 * sizeof(int) );
	bptr = binptr[block][bin] ;
	bptr->cell[0] = 0 ;
	bptr->right = binOffst + bin * binWidth ;
	bptr->left  = bptr->right - binWidth ;
	if( bin == LoBin ) {
	    bptr->penalty = left - bptr->right ;
	} else if( bin == HiBin ) {
	    bptr->penalty = bptr->left - right ;
	} else if( bin > HiBin || bin < LoBin ) {
	    bptr->penalty = 0 ;
	} else {
	    bptr->penalty = - binWidth ;
	}
    }
}

installf() ;

for( cell = 1 ; cell <= numcells ; cell++ ) {

    cellptr1 = carray[ cell ] ;
    tileptr1 = cellptr1->tileptr ;
    block = cellptr1->cblock ;

    startx = cellptr1->cxcenter + tileptr1->left  ;
    endx   = cellptr1->cxcenter + tileptr1->right ;

    barray[block]->oldsize += endx - startx ;

    cbin  = SetBin( cellptr1->cxcenter ) ;
    LoBin = SetBin( startx ) ;
    HiBin = SetBin( endx ) ;

    k = ++(binptr[block][cbin]->cell[0]) ;
    if( k % 10 == 0 ) {
	binptr[block][cbin]->cell = (int *) safe_realloc(
	      binptr[block][cbin]->cell, (k + 10) * sizeof( int ) ) ;
    }
    binptr[block][cbin]->cell[k] = cell ;
    if( LoBin == HiBin ) {
	binptr[block][LoBin]->penalty +=  ( endx - startx ) ;
    } else {
	bptr = binptr[block][LoBin] ;
	bptr->penalty += ( bptr->right - startx ) ;

	bptr = binptr[block][HiBin] ;
	bptr->penalty +=  ( endx - bptr->left ) ;

	if( LoBin + 1 < HiBin ) {
	    for( bin = LoBin + 1 ; bin <= HiBin - 1 ; bin++ ) {
		binptr[block][bin]->penalty += binWidth ;
	    }
	}
    }
}

for( block = 1 ; block <= numblock ; block++ ) {
    for( bin = 0 ; bin <= numBins ; bin++ ) {
	binpenal += ABS( binptr[block][bin]->penalty ) ;
    }
}

for( blk = 1 ; blk <= numblock ; blk++ ) {
    rowpenal += ABS(barray[blk]->oldsize - barray[blk]->desire) ;
}
penalty = (int)( binpenCon * (double) binpenal + 
				roLenCon * (double) rowpenal ) ;
return( cost ) ;
}




installf()
{

int row , n , left , length , sep , i , bin ;

for( row = 1 ; row <= numRows ; row++ ) {
    n = feeds_in_row[row] ;
    if( n < 1 ) {
	continue ;
    }
    left   = barray[row]->bxcenter + barray[row]->bleft ;
    length = barray[row]->bright   - barray[row]->bleft ;
    sep    = (length - n * binWidth ) / (n + 1) ;
    for( i = 1 ; i <= n ; i++ ) {
	bin = SetBin( left + sep * i + binWidth / 2 ) ;
	binptr[row][bin]->penalty += binWidth ;
	barray[row]->oldsize += binWidth ;
    }
}

return;
}
