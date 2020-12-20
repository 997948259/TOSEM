#include "standard.h"
int delta_vert_cost ;   /* used outside this file */
int tot_num_feeds ;     /* used outside this file */
int tot_missing_rows ;  /* used outside this file */
extern int numRows ;
extern int rowHeight ;
extern int ablock ;
extern int bblock ;
int *num_feeds ;
int *tmp_num_feeds ;
int *missing_rows ;
int *tmp_missing_rows ;
static char **rows ;
char **tmp_rows ;
#define T 2
#define R 3



check_cost()
{

DBOXPTR  dimptr  ;
NBOXPTR  netptr  ;
TEBOXPTR termptr ;
int old_mean , oldx , net , initial_cost , total ;

initial_cost = 0 ;
for( net = 1 ; net <= numnets ; net++ ) {
    dimptr = netarray[net] ;
    total = 0 ;
    for( netptr = dimptr->netptr ; netptr ; netptr = netptr->nterm ) {
	total += netptr->xpos ;
    }
    old_mean = total / dimptr->numpins ;
    for( netptr = dimptr->netptr ; netptr ; netptr = netptr->nterm ) {
	oldx = netptr->xpos ;
	initial_cost += ABS( oldx - old_mean ) ;
    }
}
return( initial_cost ) ;
}



initialize_cost()
{

DBOXPTR  dimptr  ;
NBOXPTR  netptr  ;
TEBOXPTR termptr ;
int old_mean , oldx , net , initial_cost ;

initial_cost = 0 ;
for( net = 1 ; net <= numnets ; net++ ) {
    dimptr = netarray[net] ;
    dimptr->old_total = 0 ;
    for( netptr = dimptr->netptr ; netptr ; netptr = netptr->nterm ) {
	dimptr->old_total += netptr->xpos ;
    }
    old_mean = dimptr->old_total / dimptr->numpins ;
    for( netptr = dimptr->netptr ; netptr ; netptr = netptr->nterm ) {
	oldx = netptr->xpos ;
	initial_cost += ABS( oldx - old_mean ) ;
    }
}
return( initial_cost ) ;
}



new_dbox( antrmptr , costptr )
TEBOXPTR antrmptr ;
int *costptr ;
{

NBOXPTR  netptr  ;
DBOXPTR  dimptr  ;
TEBOXPTR termptr ;
int old_mean , new_mean , oldx , newx ;

for( termptr = antrmptr ; termptr ; termptr = termptr->nextterm ) {
    dimptr = netarray[ termptr->net ] ;
    if( dimptr->dflag == 0  ) { 
	continue ;
    }
    dimptr->dflag = 0 ;

    new_mean = dimptr->new_total / dimptr->numpins ;
    old_mean = dimptr->old_total / dimptr->numpins ;
    for( netptr = dimptr->netptr ; netptr ; netptr = netptr->nterm ) {
	oldx = netptr->xpos ;
	if( netptr->flag == 1 ) {
	    newx = netptr->newx ;
	    netptr->flag = 0 ;
	} else {
	    newx = oldx ;
	}
	*costptr += ABS( newx - new_mean ) - ABS( oldx - old_mean ) ;
    }
}
return ;
}


new_dbox_a( antrmptr , costptr )
TEBOXPTR antrmptr ;
int *costptr ;
{

DBOXPTR  dimptr  ;
NBOXPTR  netptr  ;
TEBOXPTR termptr ;
int old_mean , new_mean , oldx , newx ;
int f , m , min , max , row , net ;
char *rowsptr ;

for( termptr = antrmptr ; termptr ; termptr = termptr->nextterm ) {
    net = termptr->net ;
    dimptr = netarray[ net ] ;
    if( dimptr->dflag == 0  ) { 
	continue ;
    }
    dimptr->dflag = 0 ;

    new_mean = dimptr->new_total / dimptr->numpins ;
    old_mean = dimptr->old_total / dimptr->numpins ;
    for( netptr = dimptr->netptr ; netptr ; netptr = netptr->nterm ) {
	oldx = netptr->xpos ;
	if( netptr->flag == 1 ) {
	    newx = netptr->newx ;
	    netptr->flag = 0 ;
	} else {
	    newx = oldx ;
	}
	*costptr += ABS( newx - new_mean ) - ABS( oldx - old_mean ) ;
    }

    f = 0 ;
    m = 0 ;
    rowsptr = tmp_rows[net] ;
    for( row = 0 ; rowsptr[row] == 0 ; row++ ) ;
    min = row ;
    for( row = numRows+1; rowsptr[row] == 0;row--);
    max = row ;
    for( row = min ; row <= max ; row++ ) {
	if( rowsptr[row] == 0 ) {
	    f++ ;
	} else {
	    m++ ;
	}
    }
    tmp_num_feeds[net] = f ;
    if( min < max ) {
	m += 2 ;
    } else if( min == max ) {
	m += 1 ;
    } else {
	m = 0 ;
    }
    tmp_missing_rows[net] = -m ;

    delta_vert_cost += ((tmp_num_feeds[net] - num_feeds[net]) +
		   (tmp_missing_rows[net] - missing_rows[net])) *
		   2 * rowHeight ;
}
return ;
}



term_newpos( antrmptr , xcenter , ycenter , newaor )
TEBOXPTR antrmptr ;
int xcenter , ycenter , newaor ;
{

TEBOXPTR termptr ;
NBOXPTR ttermptr ;
DBOXPTR dimptr ;

for( termptr = antrmptr ; termptr ; termptr = termptr->nextterm ) {
    ttermptr = termptr->termptr ;
    ttermptr->flag = 1 ;
    ttermptr->newx = termptr->txpos[ newaor/2 ] + xcenter ;

    dimptr = netarray[ termptr->net ] ;
    if( dimptr->dflag == 0 ) {
	dimptr->dflag = 1 ;
	dimptr->new_total = dimptr->old_total +
				ttermptr->newx - ttermptr->xpos ;
    } else {
	dimptr->new_total += ttermptr->newx - ttermptr->xpos ;
    }
}
return ;
}



term_newpos_a( antrmptr , xcenter , ycenter , newaor )
TEBOXPTR antrmptr ;
int xcenter , ycenter , newaor ;
{

TEBOXPTR termptr ;
NBOXPTR ttermptr ;
DBOXPTR dimptr ;
char *rowsptr1 , *rowsptr2 ;
int net , row ;

for( termptr = antrmptr ; termptr ; termptr = termptr->nextterm ) {
    ttermptr = termptr->termptr ;
    ttermptr->flag = 1 ;
    ttermptr->newx = termptr->txpos[ newaor/2 ] + xcenter ;

    net = termptr->net ;
    dimptr = netarray[ net ] ;

    rowsptr2 = tmp_rows[net] ;
    if( dimptr->dflag == 0 ) {
	dimptr->dflag = 1 ;

	rowsptr1 = rows[net] ;
	for( row = 0 ; row <= numRows + 1 ; row++ ) {
	    rowsptr2[row] = rowsptr1[row] ;
	}
	rowsptr2[ablock]-- ;
	rowsptr2[bblock]++ ;

	dimptr->new_total = dimptr->old_total +
				ttermptr->newx - ttermptr->xpos ;
    } else {
	rowsptr2[ablock]-- ;
	rowsptr2[bblock]++ ;
	dimptr->new_total += ttermptr->newx - ttermptr->xpos ;
    }
}
return ;
}



term_newpos_b( antrmptr , xcenter , ycenter , newaor )
TEBOXPTR antrmptr ;
int xcenter , ycenter , newaor ;
{

TEBOXPTR termptr ;
NBOXPTR ttermptr ;
DBOXPTR dimptr ;
char *rowsptr1 , *rowsptr2 ;
int net , row ;

for( termptr = antrmptr ; termptr ; termptr = termptr->nextterm ) {
    ttermptr = termptr->termptr ;
    ttermptr->flag = 1 ;
    ttermptr->newx = termptr->txpos[ newaor/2 ] + xcenter ;

    net = termptr->net ;
    dimptr = netarray[ net ] ;

    rowsptr2 = tmp_rows[net] ;
    if( dimptr->dflag == 0 ) {
	dimptr->dflag = 1 ;

	rowsptr1 = rows[net] ;
	for( row = 0 ; row <= numRows + 1 ; row++ ) {
	    rowsptr2[row] = rowsptr1[row] ;
	}
	rowsptr2[bblock]-- ;
	rowsptr2[ablock]++ ;

	dimptr->new_total = dimptr->old_total +
				ttermptr->newx - ttermptr->xpos ;
    } else {
	rowsptr2[bblock]-- ;
	rowsptr2[ablock]++ ;
	dimptr->new_total += ttermptr->newx - ttermptr->xpos ;
    }
}
return ;
}



dbox_pos( antrmptr ) 
TEBOXPTR antrmptr ;
{

DBOXPTR dimptr ;
TEBOXPTR termptr ;

for( termptr = antrmptr ; termptr ; termptr = termptr->nextterm ) {
    dimptr = netarray[ termptr->net ] ;
    dimptr->old_total = dimptr->new_total ;

    termptr->termptr->xpos = termptr->termptr->newx ;
}
return ;
}



dbox_pos_2( antrmptr ) 
TEBOXPTR antrmptr ;
{

NBOXPTR netptr ;
DBOXPTR dimptr ;
TEBOXPTR termptr ;
int x , net , row ;
register char *rowsptr1 , *rowsptr2 ;

for( termptr = antrmptr ; termptr ; termptr = termptr->nextterm ) {
    net = termptr->net ;
    dimptr = netarray[ net ] ;
    dimptr->old_total = dimptr->new_total ;

    termptr->termptr->xpos = termptr->termptr->newx ;

    missing_rows[net] = tmp_missing_rows[net] ;
    num_feeds[net] = tmp_num_feeds[net] ;

    rowsptr1 = rows[net] ;
    rowsptr2 = tmp_rows[net] ;
    for( row = 0 ; row <= numRows + 1 ; row++ ) {
	rowsptr1[row] = rowsptr2[row] ;
    }
}
return ;
}



initialize_rows()
{

TEBOXPTR termptr ;
int net , row , cell , min , max , f , m ;
char *rowsptr ;

num_feeds = (int *) safe_malloc( (1 + numnets) * sizeof(int) ) ;
tmp_num_feeds = (int *) safe_malloc( (1 + numnets) * sizeof(int) ) ;
missing_rows = (int *) safe_malloc( (1 + numnets) * sizeof(int) ) ;
tmp_missing_rows = (int *) safe_malloc( (1 + numnets) * sizeof(int) ) ;
rows = (char **) safe_malloc( (1 + numnets) * sizeof(char *) ) ;
tmp_rows = (char **) safe_malloc( (1 + numnets) * sizeof(char *) ) ;
for( net = 1 ; net <= numnets ; net++ ) {
    rows[net] = (char *) safe_malloc( (2 + numRows) * sizeof(char) ) ;
    tmp_rows[net] = (char *) safe_malloc( (2 + numRows) * sizeof(char));
    for( row = 0 ; row <= numRows + 1 ; row++ ) {
	rows[net][row] = 0 ;
	tmp_rows[net][row] = 0 ;
    }
    missing_rows[net] = 0 ;
    tmp_missing_rows[net] = 0 ;
    num_feeds[net] = 0 ;
    tmp_num_feeds[net] = 0 ;
}

for( cell = 1 ; cell <= numcells + numterms ; cell++ ) {
    if( cell > numcells ) {
	if( carray[cell]->padside != T && 
				carray[cell]->padside != B &&
				carray[cell]->padside != MTT &&
				carray[cell]->padside != MBB ) {
	    continue ;
	} else if( carray[cell]->padside == T ||
				carray[cell]->padside == MTT ) {
	    carray[cell]->cblock = row = numRows + 1 ;
	} else {
	    carray[cell]->cblock = row = 0 ;
	}
    } else {
	row = carray[cell]->cblock ;
    }
    for( termptr = carray[cell]->tileptr->termsptr ;
		termptr != TERMNULL ; termptr = termptr->nextterm ) {
	rows[ termptr->net ][ row ]++ ;
    }
}

for( net = 1 ; net <= numnets ; net++ ) {
    f = 0 ;
    m = 0 ;
    rowsptr = rows[net] ;
    for( row = 0 ; rowsptr[row] == 0 ; row++ ) ;
    min = row ;
    for( row = numRows + 1 ; rowsptr[row] == 0 ; row-- ) ;
    max = row ;
    for( row = min ; row <= max ; row++ ) {
	if( rowsptr[row] == 0 ) {
	    f++ ;
	} else {
	    m++ ;
	}
    }
    num_feeds[net] = f ;
    if( min < max ) {
	m += 2 ;
    } else if( min == max ) {
	m += 1 ;
    } else {
	m = 0 ;
    }
    missing_rows[net] = -m ;
}

return ;
}



check_row_values()
{

TEBOXPTR termptr ;
int net , row , cell , min , max , f , m , fds, mrs ;
char *rowsptr , **check_rows ;
int *check_feeds ;

check_feeds = (int *) safe_malloc( (1 + numnets) * sizeof(int) ) ;
check_rows = (char **) safe_malloc( (1 + numnets) * sizeof(char *) ) ;
for( net = 1 ; net <= numnets ; net++ ) {
    check_rows[net] = (char *) safe_malloc((2+numRows) * sizeof(char));
    for( row = 0 ; row <= numRows + 1 ; row++ ) {
	check_rows[net][row] = 0 ;
    }
    check_feeds[net] = 0 ;
}

for( cell = 1 ; cell <= numcells + numterms ; cell++ ) {
    if( cell > numcells ) {
	if( carray[cell]->padside != T && 
				carray[cell]->padside != B &&
				carray[cell]->padside != MTT &&
				carray[cell]->padside != MBB ) {
	    continue ;
	} else if( carray[cell]->padside == T ||
				carray[cell]->padside == MTT ) {
	    carray[cell]->cblock = row = numRows + 1 ;
	} else {
	    carray[cell]->cblock = row = 0 ;
	}
    } else {
	row = carray[cell]->cblock ;
    }
    for( termptr = carray[cell]->tileptr->termsptr ;
		termptr != TERMNULL ; termptr = termptr->nextterm ) {
	check_rows[ termptr->net ][ row ]++ ;
    }
}

fds = 0 ;
mrs = 0 ;
for( net = 1 ; net <= numnets ; net++ ) {
    f = 0 ;
    m = 0 ;
    rowsptr = check_rows[net] ;
    for( row = 0 ; rowsptr[row] == 0 ; row++ ) ;
    min = row ;
    for( row = numRows + 1 ; rowsptr[row] == 0 ; row-- ) ;
    max = row ;
    for( row = min ; row <= max ; row++ ) {
	if( rowsptr[row] == 0 ) {
	    f++ ;
	} else {
	    m++ ;
	}
    }
    fds += f ;
    if( min < max ) {
	m += 2 ;
    } else if( min == max ) {
	m += 1 ;
    } else {
	m = 0 ;
    }
    mrs -= m ;
}

safe_free( check_feeds ) ;
for( net = 1 ; net <= numnets ; net++ ) {
    safe_free( check_rows[net] ) ;
}
safe_free( check_rows ) ;

fprintf(fpo,"FEEDS:%d     MRs:%d\n", fds , mrs ) ;
printf("FEEDS:%d     MRs:%d\n", fds , mrs ) ;
fflush(stdout);
fflush(fpo) ;

return ;
}





vert_statistics()
{

int net ;

tot_missing_rows = 0 ;
tot_num_feeds = 0 ;
for( net = 1 ; net <= numnets ; net++ ) {
    tot_missing_rows += missing_rows[net] ;
    tot_num_feeds += num_feeds[net] ;
}
return ;
}
