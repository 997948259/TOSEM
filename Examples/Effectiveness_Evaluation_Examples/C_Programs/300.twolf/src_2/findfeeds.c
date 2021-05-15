#include "standard.h"
extern int *length_of_row ;
extern int *add_to_row ;
int *act_feeds_in_row ;
int pad_line ;
int last_feed ;
extern int gate_array_special ;
extern int addFeeds ;
extern int *nofeed ;
extern char **pinnames ;
extern int ffeeds ;
extern int maxterm ;
extern int feedLayer ;
extern int *blkToRow ;
typedef struct ipbox {
    struct ipbox *npin ;
    int ixpos ;
    int iypos ;
    int layer ;
    char *ipname ;
} IPBOX , *IPBOXPTR ;

typedef struct ibox {
    struct ibox *niptr ;
    int iactive ;
    int aveXpos ;
    int icell ;
    IPBOXPTR iptr ;
} IBOX , *IBOXPTR ;
extern IBOXPTR siptr ;

int impcount ;
#define R 3

int *feed_location ;


findfeeds( flag )
int flag ;
{

NBOXPTR netptr , saveptr ;
int check , a ;
int net , i , row , l , r , toprow , botrow ;
int orig_toprow , orig_botrow ;
int TOP_ROW_FOR_NET , position , max_row_length ;
int first_ok , second_ok , rowb , rowt , have_to_check ;

feeds = 0 ;

if( ! flag ) {
    prepglob(0) ;
    impcount = 0 ;
    act_feeds_in_row = (int *) safe_malloc( (1 + numRows) *
					    sizeof(int) ) ;
    for( row = 1 ; row <= numRows ; row++ ) {
	act_feeds_in_row[row] = 0 ;
    }
} else {
    pad_line = numcells + ffeeds + add_to_row[0] ;
    impfix() ;
}

feed_location = (int *) safe_malloc( (1 + numnets) * sizeof(int) );

for( net = 0 ; net <= numnets ; net++ ) {
    feed_location[net] = 0 ;
}

for( net = 1 ; net <= numnets ; net++ ) {
    if( netarray[net]->feedflag == 1 ) {
	continue ;
    }
    if( (netptr = netarray[net]->netptr) != NETNULL ) {
	for( i = 0 ; i <= numRows + 1 ; i++ ) {
	    ROW_STATS[ i ][ LEFT_MOST ] = BIG_NUMBER ;
	    ROW_STATS[ i ][ RITE_MOST ] = NO_PINS ;
	    ROW_STATS[ i ][ FEED_FLAG ] = NOT_DONE ;
	}
	for( ; netptr != NETNULL ; netptr = netptr->nterm ) {
	    if( (flag == 0 && netptr->cell > numcells) ||
		(flag == 1 && netptr->cell > pad_line) ){
		if( carray[netptr->cell]->padside == L || 
			    carray[netptr->cell]->padside == ML ||
			    carray[netptr->cell]->padside == MUL ||
			    carray[netptr->cell]->padside == MLL ||
			    carray[netptr->cell]->padside == R ||
			    carray[netptr->cell]->padside == MR ||
			    carray[netptr->cell]->padside == MUR ||
			    carray[netptr->cell]->padside == MLR ) {
		    continue ;
		} else if( netptr->nterm != NULL ) {
		    if( netptr->nterm->extint == netptr->extint ) {
			for( ; ; ) {
			    if( netptr->nterm->extint == netptr->extint ){
				if( (netptr->row > numRows &&
					netptr->ypos <= netptr->nterm->ypos) ||
				    (netptr->row < 1 &&
					netptr->ypos >= netptr->nterm->ypos) ){

				    saveptr = netptr->nterm ;
				    netptr->nterm = saveptr->nterm ;
				    del_pin( saveptr->cell ,
							saveptr->terminal ) ;
				    safe_free( saveptr ) ;
				} else {
				    if( netptr == netarray[net]->netptr ) {
					netarray[net]->netptr = netptr->nterm;
					del_pin( netptr->cell ,
							netptr->terminal ) ;
					safe_free( netptr ) ;
					netptr = netarray[net]->netptr ;
				    } else {
					saveptr = netarray[net]->netptr ;
					for( ; ; ) {
					    if( saveptr->nterm == netptr ){
						break ;
					    } else {
						saveptr = saveptr->nterm ;
					    }
					}
					saveptr->nterm = netptr->nterm ;
					del_pin( netptr->cell ,
							netptr->terminal ) ;
					safe_free( netptr ) ;
					netptr = saveptr->nterm ;
				    }
				}
				if( netptr->nterm == NULL ) {
				    break ;
				}
			    } else {
				break ;
			    }
			}
		    }
		}
	    }
	    row = netptr->row ;
	    if( netptr->xpos > ROW_STATS[row][ RITE_MOST ] ) {
		ROW_STATS[ row ][ RITE_MOST ] = netptr->xpos ;
	    }
	    if( netptr->xpos < ROW_STATS[row][ LEFT_MOST] ) {
		ROW_STATS[ row ][ LEFT_MOST] = netptr->xpos ;
	    }
	    if( ROW_STATS[ row ][ FEED_FLAG ] == NOT_DONE ) {
		ROW_STATS[ row ][ FEED_FLAG ] = detfeed( flag , row , net ) ;
	    }
	}
	botrow = 0 ;
	toprow = numRows + 1 ;
	for( ; botrow <= numRows + 1 ; botrow++ ) {
	    if( ROW_STATS[ botrow ][ RITE_MOST ] != NO_PINS ) {
		break ;
	    }
	}
	for( ; toprow >= 0 ; toprow-- ) {
	    if( ROW_STATS[ toprow ][ RITE_MOST ] != NO_PINS ) {
		break ;
	    }
	}
	/* ******** MAXIMUM FEEDS *************************************** */
	orig_toprow = toprow ;
	orig_botrow = botrow ;
	netptr = netarray[net]->netptr ;
	for( ; netptr != NETNULL ; netptr = netptr->nterm ) {
	    if( (flag == 0 && netptr->cell <= numcells) ||
		(flag == 1 && netptr->cell <= pad_line) ){
		continue ;
	    }
	    if( carray[netptr->cell]->padside != L && 
			carray[netptr->cell]->padside != ML &&
			carray[netptr->cell]->padside != MUL &&
			carray[netptr->cell]->padside != MLL &&
			carray[netptr->cell]->padside != R &&
			carray[netptr->cell]->padside != MR &&
			carray[netptr->cell]->padside != MUR &&
			carray[netptr->cell]->padside != MLR ) {
		continue ;
	    }
	    if( netptr->nterm != NULL ) {
		if( netptr->nterm->extint == netptr->extint ) {
		    have_to_check = TRUE ;
		} else {
		    have_to_check = FALSE ;
		}
	    } else {
		have_to_check = FALSE ;
	    }
	    if( have_to_check ) {
		for( ; ; ) {
		    if( netptr->nterm->extint == netptr->extint ) {
			/*
			 *     Determine which of two equivs is more 
			 *     suitable.
			 */
			row = netptr->row ;
			if( row <= toprow && row >= botrow ) {
			    first_ok = 0 ;
			}
			if( row > toprow ) {
			    first_ok = row - toprow ;
			}
			if( row < botrow ) {
			    first_ok = botrow - row ;
			}
			row = netptr->nterm->row ;
			if( row <= toprow && row >= botrow ) {
			    second_ok = 0 ;
			}
			if( row > toprow ) {
			    second_ok = row - toprow ;
			}
			if( row < botrow ) {
			    second_ok = botrow - row ;
			}

			if( first_ok == second_ok ) {
			    first_ok = 1000000 ;
			    rowb = (netptr->row - 1 >= 0) ?
							netptr->row - 1 : 0 ;
			    rowt = (netptr->row + 1 <= numRows + 1) ?
						netptr->row + 1 : numRows + 1 ;
			    for( row = rowb ; row <= rowt ; row++ ) {
				if( ROW_STATS[row][ RITE_MOST ] == NO_PINS ) {
				    continue ;
				}
				if( netptr->xpos <=
					    ROW_STATS[row][ RITE_MOST ] &&
				    netptr->xpos >=
					    ROW_STATS[row][ LEFT_MOST ] ){
				    first_ok = 0 ;
				} else if( netptr->xpos > 
					    ROW_STATS[row][ RITE_MOST ] ) {
				    if( netptr->xpos - 
					    ROW_STATS[row][ RITE_MOST ] <
								first_ok){
					first_ok = netptr->xpos -
						ROW_STATS[row][ RITE_MOST ] ;
				    }
				} else {
				    if( ROW_STATS[row][ LEFT_MOST ] -
						    netptr->xpos < first_ok){
					first_ok = ROW_STATS[row][LEFT_MOST] -
								netptr->xpos ;
				    }
				}
			    }

			    second_ok = 1000000 ;
			    rowb = (netptr->nterm->row - 1 >= 0) ?
					    netptr->nterm->row - 1 : 0 ;
			    rowt = (netptr->nterm->row + 1 <= numRows + 1) ?
					    netptr->nterm->row + 1 :
					    numRows + 1 ;
			    for( row = rowb ; row <= rowt ; row++ ) {
				if( ROW_STATS[row][ RITE_MOST ] == NO_PINS ) {
				    continue ;
				}
				if( netptr->nterm->xpos <=
						ROW_STATS[row][ RITE_MOST ] &&
				    netptr->nterm->xpos >=
						ROW_STATS[row][ LEFT_MOST ] ){
				    second_ok = 0 ;
				} else if( netptr->nterm->xpos > 
						ROW_STATS[row][ RITE_MOST ] ) {
				    if( netptr->nterm->xpos - 
					    ROW_STATS[row][ RITE_MOST ] <
					    second_ok){
					second_ok = netptr->nterm->xpos -
						ROW_STATS[row][ RITE_MOST ] ;
				    }
				} else {
				    if( ROW_STATS[row][ LEFT_MOST ] -
					    netptr->nterm->xpos < second_ok){
					second_ok = ROW_STATS[row][LEFT_MOST] -
							netptr->nterm->xpos ;
				    }
				}
			    }
			}
			if( first_ok <= second_ok ) {
			    saveptr = netptr->nterm ;
			    netptr->nterm = saveptr->nterm ;
			    del_pin( saveptr->cell , saveptr->terminal ) ;
			    safe_free( saveptr ) ;
			} else {
			    if( netptr == netarray[net]->netptr ) {
				netarray[net]->netptr = netptr->nterm ;
				del_pin( netptr->cell , netptr->terminal ) ;
				safe_free( netptr ) ;
				netptr = netarray[net]->netptr ;
			    } else {
				saveptr = netarray[net]->netptr ;
				for( ; ; ) {
				    if( saveptr->nterm == netptr ) {
					break ;
				    } else {
					saveptr = saveptr->nterm ;
				    }
				}
				saveptr->nterm = netptr->nterm ;
				del_pin( netptr->cell , netptr->terminal ) ;
				safe_free( netptr ) ;
				netptr = saveptr->nterm ;
			    }
			}
			if( netptr->nterm == NULL ) {
			    break ;
			}
		    } else {
			break ;
		    }
		}
	    }
	    /* ************************** */
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
	    if( netptr->xpos > ROW_STATS[row][ RITE_MOST ] ) {
		ROW_STATS[ row ][ RITE_MOST ] = netptr->xpos ;
	    }
	    if( netptr->xpos < ROW_STATS[row][ LEFT_MOST] ) {
		ROW_STATS[ row ][ LEFT_MOST] = netptr->xpos ;
	    }
	    if( ROW_STATS[ row ][ FEED_FLAG ] == NOT_DONE ) {
		ROW_STATS[ row ][ FEED_FLAG ] = detfeed( flag , row , net ) ;
	    }
	}
	/* *********************************************************** */

	if( toprow != botrow ) {
	    row = toprow ;
	    TOP_ROW_FOR_NET = YES ;
	    for( row-- ; row >= botrow ; row-- ) {
		if( ROW_STATS[ row ][ RITE_MOST ] == NO_PINS ) {
		    continue ;
		}
		l = ( ROW_STATS[toprow][ LEFT_MOST] <= 
					ROW_STATS[row][ LEFT_MOST] ) ?
			ROW_STATS[toprow][ LEFT_MOST] : 
					ROW_STATS[row][ LEFT_MOST] ;
		r = ( ROW_STATS[toprow][ RITE_MOST ] >= 
					ROW_STATS[row][ RITE_MOST ] ) ? 
			ROW_STATS[toprow][ RITE_MOST ] : 
					ROW_STATS[row][ RITE_MOST ] ;

		position = (l + r) / 2 ;
		if( gate_array_special ) {
		    if( feed_location[net] == 0 ) {
			feed_location[net] = position ;
		    } else {
			position = feed_location[net];
		    }
		}

		if( TOP_ROW_FOR_NET == YES ) {
		    if( ROW_STATS[ toprow ][ FEED_FLAG ] == 1 || 
				ROW_STATS[ toprow ][ FEED_FLAG ] == 3 ) {
			if( ! nofeed[toprow] ) {
			    if( flag == 0 ) {
				if( implfeeds(toprow, position )){
				    impcount++ ;
				} else {
				    feeds++ ;
				    act_feeds_in_row[toprow]++ ;

				    if( gate_array_special == TRUE ) {
					build_feed_imp( feeds, 
					    position - fdWidth / 2 , 
							    toprow ) ;
				    }
				}
			    } else {
				if( implfeeds(toprow, position ) ) {
				    addimp( toprow , net ) ;
				} else {
				    addfeed( toprow, position, 
						++feeds, net ) ;

				    if( gate_array_special == TRUE ) {
					build_feed_imp( feeds, 
					    position - fdWidth / 2 , 
							    toprow ) ;

				    }
				}
			    }
			}
		    }
		}
		if( row > botrow ) {
		    if( ROW_STATS[row][ FEED_FLAG ] != 4 ) {
			if( ! nofeed[row] ) {
			    if( flag == 0 ) {
				if( implfeeds(row, position ) ){
				    impcount++ ;
				} else {
				    feeds++ ;
				    act_feeds_in_row[row]++ ;

				    if( gate_array_special == TRUE ) {
					build_feed_imp( feeds, 
					    position - fdWidth / 2 , 
								row ) ;
				    }
				}
			    } else {
				if( implfeeds(row, position ) ){
				    addimp( row , net ) ;
				} else {
				    addfeed( row, position , 
						++feeds, net ) ;

				    if( gate_array_special == TRUE ) {
					build_feed_imp( feeds, 
					    position - fdWidth / 2 , 
								row ) ;

				    }
				}
			    }
			}
		    }
		}
		if( row == botrow ) {
		    if( ROW_STATS[botrow][ FEED_FLAG ] == 2 || 
				 ROW_STATS[botrow][ FEED_FLAG ] == 3 ) {
			if( ! nofeed[botrow] ) {
			    if( flag == 0 ) {
				if( implfeeds(botrow, position ) ){
				    impcount++ ;
				} else {
				    feeds++ ;
				    act_feeds_in_row[botrow]++ ;

				    if( gate_array_special == TRUE ) {
					build_feed_imp( feeds, 
					    position - fdWidth / 2 , 
							    botrow ) ;
				    }
				}
			    } else {
				if( implfeeds(botrow, position ) ){
				    addimp( botrow , net ) ;
				} else {
				    addfeed( botrow, position , 
						++feeds, net ) ;

				    if( gate_array_special == TRUE ) {
					build_feed_imp( feeds, 
					    position - fdWidth / 2 , 
							    botrow ) ;
				    }
				}
			    }
			}
		    }
		}
		check = toprow - row - 1 ;
		if( check != 0 ) {
		    for( a = toprow - 1 ; a > row ; a--){
			if( ! nofeed[a] ) {
			    if( flag == 0 ) {
				if( implfeeds(a, position ) ){
				    impcount++ ;
				} else {
				    feeds++ ;
				    act_feeds_in_row[a]++ ;

				    if( gate_array_special == TRUE ) {
					build_feed_imp( feeds, 
					     position - fdWidth / 2 , a);
				    }
				}
			    } else {
				if( implfeeds(a, position ) ){
				    addimp( a , net ) ;
				} else {
				    addfeed( a, position , 
						++feeds, net ) ;

				    if( gate_array_special == TRUE ) {
					build_feed_imp( feeds, 
					     position - fdWidth / 2 , a);
				    }
				}
			    }
			}
		    }
		}
		toprow = row ;
		TOP_ROW_FOR_NET = NO ;
	    }
	} else {   /* toprow == botrow */
	    if( netarray[net]->feedflag == 0 ) {
		if( ROW_STATS[toprow][ FEED_FLAG ] == 3 ) {
		    if( ! nofeed[toprow] ) {

			l = ROW_STATS[toprow][ LEFT_MOST] ;
			r = ROW_STATS[toprow][ RITE_MOST ] ;
			position = (l + r) / 2 ;
			if( gate_array_special ) {
			    if( feed_location[net] == 0 ) {
				feed_location[net] = position ;
			    } else {
				position = feed_location[net];
			    }
			}

			if( flag == 0 ) {
			    if( implfeeds(toprow, position ) ) {
				impcount++ ;
			    } else {
				feeds++ ;
				act_feeds_in_row[toprow]++ ;

				if( gate_array_special == TRUE ) {
				    build_feed_imp( feeds, 
					    position - fdWidth / 2 , 
							    toprow ) ;
				}
			    }
			} else {

			    if( implfeeds( toprow, position ) ) {
				addimp( toprow , net ) ;
			    } else {
				addfeed( toprow, position, ++feeds, net);

				if( gate_array_special == TRUE ) {
				    build_feed_imp( feeds, 
					    position - fdWidth / 2 , 
							    toprow ) ;
				}
			    }
			}
		    }
		}
	    }
	}
    }
}
if( flag == 0 ) {
    ffeeds = feeds ;

    for( row = 1 ; row <= numRows ; row++ ) {
	length_of_row[row] += act_feeds_in_row[row] * fdWidth;
    }
    max_row_length = 0 ;
    for( row = 1 ; row <= numRows ; row++ ) {
	if( length_of_row[row] > max_row_length ) {
	    max_row_length = length_of_row[row] ;
	}
    }
    add_to_row[0] = 0 ;
    for( row = 1 ; row <= numRows ; row++ ) {
	add_to_row[row] = (max_row_length - length_of_row[row]) /
							    fdWidth ;
	add_to_row[0] += add_to_row[row] ;
    }
    safe_free( length_of_row ) ;

    if( addFeeds ) {
	prepglob(1) ;
    }
} else {
    impclobr() ;
    last_feed = feeds ;
}
safe_free( feed_location ) ;

return( feeds ) ;
}






del_pin( cell , pin )
int cell , pin ;
{

TEBOXPTR tptr , sptr ;

carray[cell]->numterms-- ;
tptr = carray[cell]->tileptr->termsptr ;
if( tptr->cellterm == pin ) {
    sptr = carray[cell]->tileptr->termsptr ;
    carray[cell]->tileptr->termsptr = tptr->nextterm ;
    safe_free( sptr ) ;
} else {
    for( ; ; ) {
	if( tptr->nextterm->cellterm == pin ) {
	    break ;
	} else {
	    tptr = tptr->nextterm ;
	}
    }
    sptr = tptr->nextterm ;
    tptr->nextterm = sptr->nextterm ;
    safe_free( sptr ) ;
}
return ;
}


fixwolf( nfeed )
int nfeed ;
{

CBOXPTR *newarray , ptr ;
int i , j , n ;

n = numcells ;
newarray = (CBOXPTR *) safe_malloc( (1 + numcells + numterms +
		    2 * numblock + nfeed) * sizeof(CBOXPTR) );

tearray = ( NBOXPTR * ) safe_realloc( tearray , 
	    (2 * (nfeed + impcount + numblock + 1) + maxterm + 1) * sizeof(NBOXPTR) ); 
pinnames = (char **) safe_realloc( pinnames, 
	    (1 + maxterm + 2 * (nfeed + impcount)) * sizeof( char * ) );
for( i = 1 ; i <= n ; i++ ) {
    newarray[i] = carray[i] ;
}
for( j = n + 1 ; j <= n + nfeed ; j++ ) {
    newarray[j] = ptr = (CBOXPTR) safe_malloc( sizeof( CBOX ) ) ;
    ptr->corient = 0 ;
    ptr->cclass  = 0 ;
    if( gate_array_special ) {
	ptr->orflag  = 1 ;
    } else {
	ptr->orflag  = 0 ;
    }
    ptr->numterms = 2 ;
    ptr->tileptr = (TIBOXPTR) safe_malloc( sizeof( TIBOX ) ) ;
    ptr->tileptr->termsptr = (TEBOXPTR) safe_malloc(sizeof(TEBOX));
    ptr->tileptr->termsptr->cellterm = ++maxterm ;
    pinnames[maxterm] = (char *) safe_malloc( 16 * sizeof( char ) ) ;
    sprintf( pinnames[maxterm] , "twfeed%d" , maxterm ) ;
    ptr->tileptr->termsptr->ei = maxterm ;
    ptr->tileptr->termsptr->ue = 0 ;
    /*  now for the second feed through pin */
    ptr->tileptr->termsptr->nextterm = (TEBOXPTR) 
					    safe_malloc(sizeof(TEBOX));
    ptr->tileptr->termsptr->nextterm->nextterm = TERMNULL  ;
    ptr->tileptr->termsptr->nextterm->ei = maxterm ;
    ptr->tileptr->termsptr->nextterm->ue = 0 ;
    ptr->tileptr->termsptr->nextterm->cellterm = ++maxterm ;
    pinnames[maxterm] = (char *) safe_malloc( 16 * sizeof( char ) ) ;
    sprintf( pinnames[maxterm] , "twfeed%d" , maxterm ) ;
}
for( ; i <= numcells + numterms ; i++ , j++ ) {
    newarray[j] = carray[i] ;
}
safe_free( carray ) ;
carray = (CBOXPTR *)safe_realloc( newarray, (1 + numcells + numterms + 
		    2 * numblock + nfeed) * sizeof(CBOXPTR) );
return ;
}


addfeed( row , pos , feednum , net ) 
int row , pos , feednum , net ;
{
CBOXPTR cellptr ;
TIBOXPTR tileptr ;
NBOXPTR nptr ;
TEBOXPTR termptr ;
int pin , blk , corient ;

blk = rowToBlk( row , pos ) ;
cellptr = carray[ numcells + feednum ] ;
cellptr->padside = 0 ;
cellptr->cxcenter = pos ;
cellptr->cycenter = barray[blk]->bycenter ;
cellptr->cheight  = barray[blk]->bheight  ;
cellptr->clength  = fdWidth ;
if( barray[blk]->borient == 2 ) {
    cellptr->corient = 1 ;
}
tileptr = cellptr->tileptr ;
cellptr->cname = (char *) safe_malloc( 16 * sizeof( char ) ) ;
if( gate_array_special ) {
    sprintf( cellptr->cname , "twfeed" ) ;
} else {
#ifdef FEED_INSTANCES
    sprintf( cellptr->cname , "twfeed%d", feednum ) ;
#else
    sprintf( cellptr->cname , "twfeed" ) ;
#endif
}
cellptr->cblock = blk ;
tileptr->left   = -fdWidth / 2 ;
tileptr->right  = fdWidth + tileptr->left ;
tileptr->bottom = -barray[blk]->bheight / 2 ;
tileptr->top    = barray[blk]->bheight + tileptr->bottom ;
termptr = tileptr->termsptr ;
termptr->txpos[0] = 0 ;
termptr->txpos[1] = 0 ;
corient = cellptr->corient ;
if( corient == 0 ) {
    termptr->typos[0] = tileptr->top ;
    termptr->typos[1] = tileptr->bottom ;
} else {
    termptr->typos[0] = tileptr->bottom ;
    termptr->typos[1] = tileptr->top ;
}
termptr = termptr->nextterm ;
termptr->txpos[0] = 0 ;
termptr->txpos[1] = 0 ;
if( corient == 0 ) {
    termptr->typos[0] = tileptr->bottom ;
    termptr->typos[1] = tileptr->top ;
} else {
    termptr->typos[0] = tileptr->top ;
    termptr->typos[1] = tileptr->bottom ;
}

pin = tileptr->termsptr->cellterm ;
nptr = netarray[net]->netptr ;
if( nptr == NETNULL ) {
    fprintf(fpo,"no pins in net to be ");
    fprintf(fpo,"connected to feed thru\n");
    exit(TW_FAIL);
}
for( ; nptr->nterm != NETNULL ; nptr = nptr->nterm ) ;
nptr = nptr->nterm = (NBOXPTR) safe_malloc( sizeof(NBOX) ) ;
tearray[pin] = nptr ;
nptr->terminal = pin  ;
nptr->flag     = 0    ;
nptr->row      = row  ;
nptr->cell     = numcells + feednum ;
nptr->net      = net ;
nptr->extint   = tileptr->termsptr->ei ;
nptr->unequiv  = tileptr->termsptr->ue ;
nptr->layer    = feedLayer ;
nptr->pinloc = 1 ;


/*  now for the second feed thru pin */
pin = tileptr->termsptr->nextterm->cellterm ;
nptr = nptr->nterm = (NBOXPTR) safe_malloc( sizeof(NBOX) ) ;
tearray[pin] = nptr ;
nptr->nterm = NETNULL ;
nptr->terminal = pin  ;
nptr->flag     = 0    ;
nptr->row      = row  ;
nptr->cell     = numcells + feednum ;
nptr->net      = net ;
nptr->extint   = tileptr->termsptr->nextterm->ei ;
nptr->unequiv  = tileptr->termsptr->nextterm->ue ;
nptr->layer    = feedLayer ;
nptr->pinloc = -1 ;

return ;
}

rowToBlk( row , pos )
int row , pos ;
{

int y , block , block1 , block2 , startx1 , endx1 , startx2 ;
int endx2 ;

y = rowArray[row].ypos ;
block1 = 0 ;
block2 = 0 ;
for( block = 1 ; block <= numblock ; block++ ) {
    if( barray[block]->bycenter == y ) {
	block1 = block ;
	break ;
    }
}
for( block++ ; block <= numblock ; block++ ) {
    if( barray[block]->bycenter == y ) {
	block2 = block ;
	break ;
    }
}
if( block1 == 0 ) {
    fprintf(fpo,"rowToBlk failed to find block corresponding\n");
    fprintf(fpo,"to row:%d\n", row ) ;
    exit(TW_FAIL) ;
}
if( block2 == 0 ) {
    block = block1 ;
} else {
    startx1 = barray[block1]->bxcenter + barray[block1]->bleft ;
    endx1 = barray[block1]->bxcenter + barray[block1]->bright ;
    startx2 = barray[block2]->bxcenter + barray[block2]->bleft ;
    endx2 = barray[block2]->bxcenter + barray[block2]->bright ;
    if( pos >= startx1 && pos <= endx1 ) {
	block = block1 ;
    } else if( pos >= startx2 && pos <= endx2 ) {
	block = block2 ;
    } else {
	/*  Well, ok then, find the nearest block  */
	if( endx2 < startx1 ) {
	    if( pos - endx2 <= startx1 - pos ) {
		block = block2 ;
	    } else {
		block = block1 ;
	    }
	} else {
	    if( pos - endx1 <= startx2 - pos ) {
		block = block1 ;
	    } else {
		block = block2 ;
	    }
	}
    }
}
return(block) ;
}

prepglob(degree)
int degree ;
{

TEBOXPTR pinptr  ;
int cell , corient ;

if( degree == 0 ) {
    for( cell = 1; cell <= numcells + numterms; cell++){
	if( cell <= numcells ) {
	    pinptr = carray[cell]->tileptr->termsptr ;
	    corient = carray[cell]->corient ;
	    for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
		tearray[pinptr->cellterm]->extint = pinptr->ei;
		tearray[pinptr->cellterm]->unequiv= pinptr->ue;
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
		tearray[pinptr->cellterm]->cell = cell ;
		tearray[pinptr->cellterm]->extint = pinptr->ei;
		tearray[pinptr->cellterm]->unequiv = pinptr->ue;
		tearray[pinptr->cellterm]->pinloc = 0 ;
	    }
	}
    }
} else {
    for( cell = numcells + 1 ; cell <= numcells + numterms; cell++ ) {
	pinptr = carray[cell]->tileptr->termsptr ;
	for( ; pinptr != TERMNULL ; pinptr = pinptr->nextterm ) {
	    tearray[pinptr->cellterm]->cell = cell + ffeeds +
						add_to_row[0] ;
	}
    }
}
return ;
}

detfeed( flag , row , net )
int flag ;
int row  ;
int net  ;
{

CBOXPTR cellptr ;
NBOXPTR nptr , nptr2 ;
int pinup, pindown ;
int extint , pinloc ;

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
for( nptr = netarray[net]->netptr; nptr != NETNULL; nptr = nptr->nterm ){
    if( nptr->row != row || nptr->unequiv == 1 ) {
	continue ;
    }
    if( (flag == 0 && nptr->cell > numcells) ||
	    (flag == 1 && nptr->cell > pad_line) ){
	cellptr = carray[nptr->cell] ;
	if( cellptr->padside == L || 
			cellptr->padside == ML ||
			cellptr->padside == MUL ||
			cellptr->padside == MLL ||
			cellptr->padside == R ||
			cellptr->padside == MR ||
			cellptr->padside == MUR ||
			cellptr->padside == MLR ) {
	    continue ;
	}
    }
    extint = nptr->extint ;
    pinloc = nptr->pinloc ;
    if( pinloc == 0 ) {
	return(4) ;
    }
    if( pinloc > 0 ) {
	pinup = 1 ;
    } else {
	pindown = 1 ;
    }
    nptr2 = nptr->nterm ;
    for( ; nptr2 != NETNULL ; nptr2 = nptr2->nterm ) {
	if( nptr2->row != row || nptr2->unequiv == 1 ) {
	    continue ;
	}
	if( (flag == 0 && nptr2->cell > numcells) ||
		(flag == 1 && nptr2->cell > pad_line) ){
	    cellptr = carray[nptr2->cell] ;
	    if( cellptr->padside == L || 
			    cellptr->padside == ML ||
			    cellptr->padside == MUL ||
			    cellptr->padside == MLL ||
			    cellptr->padside == R ||
			    cellptr->padside == MR ||
			    cellptr->padside == MUR ||
			    cellptr->padside == MLR ) {
		continue ;
	    }
	}
	if( nptr2->pinloc == 0 ) {
	    return(4) ;
	}
	if( nptr2->extint == extint ) {
	    if( nptr2->pinloc != pinloc ) {
		return(4) ;
	    }
	} else {
	    if( nptr2->pinloc > 0 ) {
		pinup = 1 ;
	    } else {
		pindown = 1 ;
	    }
	}
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
