#include "standard.h"
int minxspan ;
extern int totallen ;
extern int iwire ;
extern int iwirex ;
extern int iwirey ;
extern int max_blklength ;
extern int rowpenal , binpenal ;
extern double roLenCon ;
extern double binpenCon ;
double mean_width ;
int offset_limit ;
int blkleft , blkrite ;


findcost()
{
FILE *fp ;
TIBOXPTR tile , tileptr1 ;
CBOXPTR cellptr1 , ptr ;
DBOXPTR dimptr ;
NBOXPTR netptr , termptr ;
TEBOXPTR term  ;
BINPTR bptr ;
char filename[64] ;
int left , right , corient ;
int bin , LoBin , HiBin ;
int block , cell , net , blk ;
int startx , endx ;
int x , y , cost=0 ;
int temp , n , k , cbin ;
int net_pin_num[ 11 ] , *adjust_left ;
double deviation , factor ;

blkleft = 32000 ;
blkrite = 0      ;
adjust_left = (int *)safe_malloc( ( numblock + 1 ) * sizeof(int) ) ;
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
    adjust_left[ block ] = 32000 ;
}
binOffst = blkleft ;
max_blklength = blkrite - blkleft ;

deviation = 0 ;
temp = 0 ;
factor = 0.0 ;
for( cell = 1 ; cell <= numcells ; cell++ ) {
    temp += carray[ cell ]->clength ;
}
mean_width = temp / numcells ;

for( cell = 1 ; cell <= numcells ; cell++ ) {
    deviation += ( carray[ cell ]->clength - mean_width )
	       * ( carray[ cell ]->clength - mean_width ) ;
}
deviation = sqrt( deviation / numcells ) ;
binWidth  = ( int ) ( factor * deviation + mean_width ) + 1 ;

numBins = (int)( ( blkrite - binOffst ) / binWidth ) ;
if( ( blkrite - binOffst ) > ( numBins * binWidth ) ) {
    numBins++ ;
}
fprintf( fpo , "numBins automatically set to:%d\n", numBins);
fprintf( fpo , "binWidth = average_cell_width + %g sigma",factor);
fprintf( fpo , "= %d\n",binWidth ) ;
fprintf( fpo , "average_cell_width is:%g\n",mean_width ) ;
fprintf( fpo , "standard deviation of cell length is:%g\n",
		deviation ) ;
	     
minxspan = (int)(mean_width + 3.0 * deviation) ;
offset_limit = (int)(0.05 * mean_width * 
			(double) numcells / (double) numblock ) ;
/*********************************************************** */

sprintf( filename , "%s.res" , cktName ) ;
fp = twopen( filename , "r", NOABORT) ;
if( !(fp) ) {
    /* 
     *  Could not open the file cktName.res
     */
    if( resume_run == YES ) {
	fprintf(fpo,"Could not use resume file: %s  ", filename ) ;
	fprintf(fpo,"since it could not be found\n");
    } else {
	fprintf(fpo,"TimberWolfSC starting from the beginning\n");
    }
} else if( resume_run == NO ) {
    fprintf(fpo,"Use of resume file: %s was not requested\n", filename);
} else {
    fprintf( fpo, "Resuming TimberWolf from previous saved ");
    fprintf( fpo, "placement in %s\n", filename );
    TW_oldin( fp ) ;
    twclose( fp ) ;
}

sortpin() ;
for( cell = 1 ; cell <= numcells + numterms ; cell++ ) {
    ptr = carray[ cell ] ;
    corient = ptr->corient ;
    block   = ptr->cblock  ;
    tile    = ptr->tileptr ;
    if( cell <= numcells ) {
	ptr->cycenter = barray[block]->bycenter ;
	if( adjust_left[block] > ptr->cxcenter + tile->left ) {
	    adjust_left[block] = ptr->cxcenter + tile->left ;
	}
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
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */ 
/* @@@ calculate the initial wire cost of user's placement @@@ */
iwirex = 0 ;
iwirey = 0 ;
for( net = 1 ; net <= numnets ; net++ ) {
    dimptr =  netarray[ net ] ;
    if( (netptr = dimptr->netptr) != NETNULL ) {
	dimptr->xmin = dimptr->xmax = netptr->xpos ;
	dimptr->ymin = dimptr->ymax = netptr->ypos ;
    }
    for( netptr = netptr->nterm ; netptr != NETNULL ;
				  netptr = netptr->nterm ) {
	x = netptr->xpos ;
	y = netptr->ypos ;
	if( x < dimptr->xmin ) {
	    dimptr->xmin = x ;
	} else if( x > dimptr->xmax ) {
	    dimptr->xmax = x ;
	}
	if( y < dimptr->ymin ) {
	    dimptr->ymin = y ;
	} else if( y > dimptr->ymax ) {
	    dimptr->ymax = y ;
	}
    }
    cost += ((int)( dimptr->Hweight *
	    (double)( dimptr->xmax - dimptr->xmin))) +
	    ((int)( dimptr->Vweight *
	    (double)( dimptr->ymax - dimptr->ymin)));
    iwirex += dimptr->xmax - dimptr->xmin ;
    iwirey += dimptr->ymax - dimptr->ymin ;
}
fprintf( fpo, "\n\n\nTHIS IS THE ROUTE COST OF THE ");
fprintf( fpo, "ORIGINAL PLACEMENT: %d\n" , cost ) ;
/* @@@@@@@@@@@@@@@@@@@@@@ calculation end @@@@@@@@@@@@@@@@@@@@ */ 

/* $$$$$$$$$$$ move the cells in each block such that   $$$$$$$ */
/* $$$$$$$$$$$ they line up with the left edge of block $$$$$$$ */

if( resume_run == NO ) {

    for( cell = 1 ; cell <= numcells ; cell++ ) {
	ptr = carray[cell] ;
	corient = ptr->corient ;
	block   = ptr->cblock ;
	ptr->cxcenter -= adjust_left[block] - 
		 barray[block]->bxcenter - barray[block]->bleft ;
	for( term = ptr->tileptr->termsptr ; 
			term != TERMNULL ;  term = term->nextterm ) {
	    termptr = tearray[ term->cellterm ] ;
	    termptr->xpos = term->txpos[corient/2] + ptr->cxcenter;
	    termptr->ypos = term->typos[corient%2] + ptr->cycenter;
	}
    }
}
/* $$$$$$$$$$$$$$$$$$$$$$ adjustment end $$$$$$$$$$$$$$$$$$$$$$ */

cost = 0 ;
iwirex = 0 ;
iwirey = 0 ;

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
    iwirex += dimptr->xmax - dimptr->xmin ;
    iwirey += dimptr->ymax - dimptr->ymin ;
}
iwire = cost ;

for( n = 1 ; n <= 10 ; n++ ) {
    net_pin_num[ n ] = 0 ;
}
for( net = 1 ; net <= numnets ; net++ ) {
    dimptr =  netarray[ net ] ;
    if( dimptr->numpins >= 10 ) {
	net_pin_num[ 10 ]++ ;
    } else {
	net_pin_num[ dimptr->numpins ]++ ;
    }
}
for( n = 1 ; n <= 9 ; n++ ) {
    fprintf( fpo, "The number of nets with %d pin is %d\n",
             n , net_pin_num[ n ] ) ;
}
fprintf( fpo, "The number of nets with 10 pin or more is %d\n",
              net_pin_num[ 10 ] ) ;

binpenal = 0 ;
rowpenal = 0 ;
penalty = 0 ;

/* belows set up the initial bin-penalty */
binptr = ( BINPTR ** ) safe_malloc( (numblock + 1 ) *
			      sizeof( BINPTR * ) ) ;

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
    /* Bins to check are: 0 and LoBin thru HiBin */
    /* first check the latter range */

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
