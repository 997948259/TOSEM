#include "standard.h"
#define TRUE 1
#define FALSE 0
int first_time_in_unlap = 1 ;
extern int **pairArray ;
extern int *add_to_row ;
extern int ffeeds ;
int noPairs ;

unlap( flag )
int flag ;
{

CBOXPTR cellptr ;
int *num , i , cell_count , space ;
int cell , block ;
int cell_left , left_edge , right_edge ;
int fixed , unfixed ;
int *left_queue , *right_queue , *center_queue ;
int max_cell_in_blk ;
int min_right_fixed_cell ;
int max_left_fixed_cell ;
int pair_array_index , total_cells ;

num = (int *) safe_malloc( ( numblock + 1 ) * sizeof(int) ) ;
for( block = 0 ; block <= numblock ; block++ ) {
    num[block] = 0 ;
}

if( flag == -2 ) {
    total_cells = numcells + ffeeds ;
} else {
    total_cells = numcells ;
}

for( cell = 1 ; cell <= total_cells ; cell++ ) {
    num[ carray[ cell ]->cblock ]++ ;
}

if( ! first_time_in_unlap ) {
    for( block = 1 ; block <= numblock ; block++ ) {
	safe_free( pairArray[ block ] ) ;
    }
    safe_free( pairArray ) ;
} else {
    first_time_in_unlap = 0 ;
}

pairArray = (int **) safe_malloc( ( numblock + 1 ) *
						sizeof(int *) ) ;
max_cell_in_blk = 0 ;
for( block = 1 ; block <= numblock ; block++ ) {
    pairArray[ block ] = (int *) safe_malloc( ( num[block] + 1 ) 
					    * sizeof( int ) ) ;
    pairArray[block][0] = num[block] ;

    if( num[block] > max_cell_in_blk ) {
	max_cell_in_blk = num[block] ;
    }
}
left_queue = (int *) safe_malloc((max_cell_in_blk + 1) * sizeof(int));
right_queue = (int *) safe_malloc((max_cell_in_blk + 1) * sizeof(int));
center_queue = (int *) safe_malloc((max_cell_in_blk + 1) * sizeof(int));

for( cell = 1 ; cell <= total_cells ; cell++ ) {
    block = carray[ cell ]->cblock ;
    pairArray[block][ num[block]-- ] = cell ;
}
for( block = 1 ; block <= numblock ; block++ ) {
    qsortx( (char *) ( pairArray[block] + 1 ) , 
		    pairArray[block][0] , sizeof( int ) ) ;
}

/* ------- Guarantees fixed-cell orderings now ------- */

for( block = 1 ; block <= numblock ; block++ ) {
    left_edge  = barray[block]->bxcenter + barray[block]->bleft ;
    right_edge = barray[block]->bxcenter + barray[block]->bright ;
    if( ( cell_count = pairArray[ block ][0] ) > 1 ) {
	noPairs = 0 ;
    }
    fixed   = FALSE ;
    unfixed = FALSE ;

    for( i = 1 ; i <= cell_count ; i++ ) {
	if( carray[pairArray[block][i]]->cclass == -1 ) {
	    fixed = TRUE ;
	} else {
	    unfixed = TRUE ;
	}
    }
    if( fixed == TRUE && unfixed == TRUE ) {
	for( i = 0 ; i <= max_cell_in_blk ; i++ ) {
	    left_queue[i]   = 0 ;
	    right_queue[i]  = 0 ;
	    center_queue[i] = 0 ;
	}
	max_left_fixed_cell = 0 ;
	for( i = 1 ; i <= cell_count ; i++ ) {
	    cellptr = carray[ pairArray[block][i] ] ;
	    if( cellptr->cclass == -1 ) {   /* fixed left */
		if( left_edge == cellptr->cxcenter +
		      cellptr->tileptr->left ) {
		    left_edge += cellptr->clength ;
		    left_queue[++(*left_queue)] = pairArray[block][i];
		    max_left_fixed_cell = i ;
		} else {
		    break ;
		}
	    }
	}
	min_right_fixed_cell = cell_count + 1 ;
	for( i = cell_count ; i >= 1 ; i-- ) {
	    cellptr = carray[ pairArray[block][i] ] ;
	    if( cellptr->cclass == -1 ) {   /* fixed right */
		if( right_edge == cellptr->cxcenter +
		      cellptr->tileptr->right ) {
		    right_edge -= cellptr->clength ;
		    right_queue[++(*right_queue)] = pairArray[block][i];
		    min_right_fixed_cell = i ;
		} else {
		    break ;
		}
	    }
	}
	for( i = 1 ; i <= cell_count ; i++ ) {
	    cellptr = carray[ pairArray[block][i] ] ;
	    if( (cellptr->cclass != -1) ||        /* unfixed */
		    (cellptr->cclass == -1 && i > max_left_fixed_cell &&
			i < min_right_fixed_cell)) { /* center-fixed */

		center_queue[++(*center_queue)] = pairArray[block][i];
	    }
	}
	pair_array_index = 0 ;
	for( i = 1 ; i <= *left_queue ; i++ ) {
	    pairArray[block][++pair_array_index] = left_queue[i] ;
	}
	for( i = 1 ; i <= *center_queue ; i++ ) {
	    pairArray[block][++pair_array_index] = center_queue[i] ;
	}
	for( i = *right_queue ; i >= 1 ; i-- ) {
	    pairArray[block][++pair_array_index] = right_queue[i] ;
	}
    }
    left_edge  = barray[block]->bxcenter + barray[block]->bleft ;
    if( flag == 1 ) {
	space = (int)( (double)(feeds_in_row[block] * binWidth) /
					(double)(cell_count - 1) ) ;
    } else {
	space = 0 ;
    }
    for( i = 1 ; i <= cell_count ; i++ ) {
	cellptr = carray[ pairArray[block][i] ] ;
        cell_left = cellptr->tileptr->left ;
        cellptr->cxcenter = left_edge - cell_left ;
	left_edge += cellptr->tileptr->right - cell_left + space ;
    }
}
safe_free(num);
safe_free(left_queue) ;
safe_free(right_queue) ;
safe_free(center_queue) ;

if( flag >= 0 ) {
    xcompact() ;
}

return ;
}
