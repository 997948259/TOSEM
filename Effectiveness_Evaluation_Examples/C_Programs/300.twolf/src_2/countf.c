#include "standard.h"
#define T 2
#define R 3
int *xfeeds_in_row ;
int est_fds ;
short int **row_map ;
short int num_calls = 0 ;

countf()
{

NBOXPTR netptr ;
CBOXPTR cellptr ;
int check , a , value ;
int net , i , row , toprow , botrow ;
int TOP_ROW_FOR_NET ;
int orig_toprow , orig_botrow ;


if( num_calls == 0 ) {
    num_calls = 1 ;
    prep_feed_count_1() ;
    row_map = ( short int ** ) safe_malloc( (numRows + 2) * 
					    sizeof(short int *));
    for( row = 0 ; row <= numRows + 1 ; row++ ) {
	row_map[row] = (short int *) safe_malloc( 3 *
				    sizeof( short int ) );
    }
    insert_row( 0 ) ;
} else {
    prep_feed_count() ;
    insert_row( 1 ) ;
}


for( net = 1 ; net <= numnets ; net++ ) {
    if( (netptr = netarray[net]->netptr) == NETNULL ) {
	continue ;
    }
    for( i = 0 ; i <= numRows + 1 ; i++ ) {
	row_map[ i ][ RITE_MOST ] = NO_PINS ;
	row_map[ i ][ FEED_FLAG ] = NOT_DONE ;
    }
    for( ; netptr != NETNULL ; netptr = netptr->nterm ) {
	cellptr = carray[netptr->cell] ;
	if( netptr->cell > numcells &&
		       (cellptr->padside == L || 
			cellptr->padside == ML ||
			cellptr->padside == MUL ||
			cellptr->padside == MLL ||
			cellptr->padside == R ||
			cellptr->padside == MR ||
			cellptr->padside == MUR ||
			cellptr->padside == MLR) ) {
	    continue ;
	}
	row = netptr->row ;
	row_map[ row ][ RITE_MOST ] = netptr->xpos ;
	if( row_map[ row ][ FEED_FLAG ] == NOT_DONE ) {
	    row_map[ row ][ FEED_FLAG ] = 
				feed_situation( row , net ) ;
	}
    }
    botrow = 0 ;
    toprow = numRows + 1 ;
    for( ; botrow <= numRows + 1 ; botrow++ ) {
	if( row_map[ botrow ][ RITE_MOST ] != NO_PINS ) {
	    break ;
	}
    }
    for( ; toprow >= 0 ; toprow-- ) {
	if( row_map[ toprow ][ RITE_MOST ] != NO_PINS ) {
	    break ;
	}
    }

    orig_toprow = toprow ;
    orig_botrow = botrow ;
    netptr = netarray[net]->netptr ;
    for( ; netptr != NETNULL ; netptr = netptr->nterm ) {
	if( netptr->cell <= numcells ) {
	    continue ;
	}
	cellptr = carray[netptr->cell] ;
	if( cellptr->padside != L && 
		    cellptr->padside != ML &&
		    cellptr->padside != MUL &&
		    cellptr->padside != MLL &&
		    cellptr->padside != R &&
		    cellptr->padside != MR &&
		    cellptr->padside != MUR &&
		    cellptr->padside != MLR ) {
	    continue ;
	}
	row = netptr->row ;
	if( row <= orig_toprow && row >= orig_botrow ) {
	    continue ;
	}
	if( row > toprow ) {
	    toprow = row ;
	}
	if( row < botrow ) {
	    botrow = row ;
	}
	row_map[ row ][ RITE_MOST ] = netptr->xpos ;
	if( row_map[ row ][ FEED_FLAG ] == NOT_DONE ) {
	    row_map[ row ][ FEED_FLAG ] = feed_situation( row , net ) ;
	}
    }

    if( toprow != botrow ) {
	row = toprow ;
	TOP_ROW_FOR_NET = YES ;
	for( row-- ; row >= botrow ; row-- ) {
	    if( row_map[ row ][ RITE_MOST ] == NO_PINS ) {
		continue ;
	    }

	    if( TOP_ROW_FOR_NET == YES ) {
		if( row_map[ toprow ][ FEED_FLAG ] == 1 || 
			    row_map[ toprow ][ FEED_FLAG ] == 3 ) {
		    feeds_in_row[toprow]++ ;
		    xfeeds_in_row[toprow]++ ;
		}
	    }
	    if( row > botrow ) {
		if( row_map[row][ FEED_FLAG ] != 4 ) {
		    feeds_in_row[row]++ ;
		    xfeeds_in_row[row]++ ;
		}
	    }
	    if( row == botrow ) {
		if( row_map[botrow][ FEED_FLAG ] == 2 || 
			     row_map[botrow][ FEED_FLAG ] == 3 ) {
		    feeds_in_row[botrow]++ ;
		    xfeeds_in_row[botrow]++ ;
		}
	    }
	    check = toprow - row - 1 ;
	    if( check != 0 ) {
		for( a = toprow - 1 ; a > row ; a--){
		    feeds_in_row[a]++ ;
		    xfeeds_in_row[a]++ ;
		}
	    }
	    toprow = row ;
	    TOP_ROW_FOR_NET = NO ;
	}
    } else {   /* toprow == botrow */
	if( row_map[toprow][ FEED_FLAG ] == 3 ) {
	    feeds_in_row[toprow]++ ;
	    xfeeds_in_row[toprow]++ ;
	}
    }
}

est_fds = 0 ;
for( row = 1 ; row <= numRows ; row++ ) {
    if( xfeeds_in_row[row] > 0 ) {
	est_fds += xfeeds_in_row[row] ;
    }
    value = (feeds_in_row[row] * fdWidth) / binWidth ;
    if( feeds_in_row[row] > 0 ) {
	feeds_in_row[row] = 1 + value ;
    } else {
	feeds_in_row[row] = 0 ;
    }
}
value = 0 ;
for( row = 1 ; row <= numRows ; row++ ) {
    value += feeds_in_row[row] ;
}
return( value * binWidth ) ;
}



prep_feed_count_1()
{

TEBOXPTR pinptr  ;
int cell , corient , offset , row ;
double total_row_len ;

total_row_len = 0 ;
for( row = 1 ; row <= numRows ; row++ ) {
    total_row_len += (double) barray[row]->blength ;
}
feeds_in_row = (int *) safe_malloc( (1 + numRows) * sizeof(int) );
xfeeds_in_row = (int *) safe_malloc( (1 + numRows) * sizeof(int) );

offset = - (int)((double) implicit_feed_count * 0.90) ;
for( row = 1 ; row <= numRows ; row++ ) {
    feeds_in_row[row] = (int)( (double) offset *
	    ((double)(barray[row]->blength) / total_row_len) ) ;
    xfeeds_in_row[row] = 0 ;
    /*
    xfeeds_in_row[row] = (int)( (double) offset / 0.90 *
	    ((double)(barray[row]->blength) / total_row_len) ) ;
    */
}

for( cell = 1; cell <= numcells + numterms; cell++){
    if( cell <= numcells ) {
	pinptr = carray[cell]->tileptr->termsptr ;
	corient = carray[cell]->corient ;
	for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
	    tearray[pinptr->cellterm]->unequiv = pinptr->ue ;
	    tearray[pinptr->cellterm]->cell = cell ;
	    if( ABS( pinptr->typos[ corient%2 ]) > 1 ) {
		if( pinptr->typos[ corient%2 ] > 0 ) {
		    tearray[pinptr->cellterm]->pinloc = 1 ;
		} else {
		    tearray[pinptr->cellterm]->pinloc = -1 ;
		}
	    } else {
		tearray[pinptr->cellterm]->pinloc = 0 ;
	    }
	}
    } else if( cell > numcells ) {
	pinptr = carray[cell]->tileptr->termsptr ;
	for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
	    tearray[pinptr->cellterm]->unequiv = pinptr->ue ;
	    tearray[pinptr->cellterm]->cell = cell ;
	    tearray[pinptr->cellterm]->pinloc = 0 ;
	}
    }
}
return ;
}


prep_feed_count()
{

TEBOXPTR pinptr  ;
int cell , corient , offset , row ;
double total_row_len ;

total_row_len = 0 ;
for( row = 1 ; row <= numRows ; row++ ) {
    total_row_len += (double) barray[row]->blength ;
}
offset = - (int)((double) implicit_feed_count * 0.90) ;
for( row = 1 ; row <= numRows ; row++ ) {
    feeds_in_row[row] = (int)( (double) offset *
	    ((double)(barray[row]->blength) / total_row_len) ) ;
    xfeeds_in_row[row] = 0 ;
    /*
    xfeeds_in_row[row] = (int)( (double) offset * 0.4 *
	    ((double)(barray[row]->blength) / total_row_len) ) ;
    */
}

for( cell = 1; cell <= numcells ; cell++){
    pinptr = carray[cell]->tileptr->termsptr ;
    corient = carray[cell]->corient ;
    for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
	if( ABS( pinptr->typos[ corient%2 ]) > 1 ) {
	    if( pinptr->typos[ corient%2 ] > 0 ) {
		tearray[pinptr->cellterm]->pinloc = 1 ;
	    } else {
		tearray[pinptr->cellterm]->pinloc = -1 ;
	    }
	} else {
	    tearray[pinptr->cellterm]->pinloc = 0 ;
	}
    }
}
return ;
}




insert_row( flag )
int flag ;
{

TEBOXPTR pinptr ;
int row , cell , pad ;
int yc , yb , blk ;


for( cell = 1 ; cell <= numcells ; cell++ ) {
    row = carray[cell]->cblock ;
    pinptr = carray[cell]->tileptr->termsptr ;
    for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
	tearray[pinptr->cellterm]->row = row ;
    }
}
if( flag == 0 ) {
    for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
	if( carray[pad]->padside == T || carray[pad]->padside == MTT ) {
	    row = numRows + 1 ;
	    pinptr = carray[pad]->tileptr->termsptr ;
	    for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
		tearray[pinptr->cellterm]->row = row ;
	    }
	} else if(carray[pad]->padside == B || 
					carray[pad]->padside == MBB){
	    row = 0 ;
	    pinptr = carray[pad]->tileptr->termsptr ;
	    for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
		tearray[pinptr->cellterm]->row = row ;
	    }
	} else {  /* side pad or internal macro block */
	    pinptr = carray[pad]->tileptr->termsptr ;
	    for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
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
		tearray[pinptr->cellterm]->row = row ;
	    }
	}
    }
}
return ;
}




feed_situation( row , net )
int row , net ;
{

NBOXPTR nptr ;
CBOXPTR cellptr ;
int pinup, pindown , pinloc ;

/*
 *   The following code is used for the return value:
 *
 *       pins top,bot but NOT truly equivalent:   0
 *       pins only on top of row for this net:    1
 *       pins only on bot of row for this net:    2
 *       pins top,bot but no passthru for net:    3
 *       passthru exists for this net:            4
 */
pinup   = 0 ;
pindown = 0 ;
nptr = netarray[net]->netptr;
for( ; nptr != NETNULL; nptr = nptr->nterm ) {
    if( nptr->row != row || nptr->unequiv == 1 ) {
	continue ;
    }
    cellptr = carray[nptr->cell] ;
    if( nptr->cell > numcells &&
		   (cellptr->padside == L || 
		    cellptr->padside == ML ||
		    cellptr->padside == MUL ||
		    cellptr->padside == MLL ||
		    cellptr->padside == R ||
		    cellptr->padside == MR ||
		    cellptr->padside == MUR ||
		    cellptr->padside == MLR) ) {
	continue ;
    }
    pinloc = nptr->pinloc ;
    if( pinloc == 0 ) {
	return(4) ;
    }
    if( pinloc > 0 ) {
	pinup = 1 ;
    } else {
	pindown = 1 ;
    }
}
if( pinup == 1 && pindown == 0 ) {
    return(1) ;
} else if( pinup == 0 && pindown == 1 ) {
    return(2) ;
} else if( pinup == 1 && pindown == 1 ) {
    return(3) ;
} else {
    return(0);
}
}
