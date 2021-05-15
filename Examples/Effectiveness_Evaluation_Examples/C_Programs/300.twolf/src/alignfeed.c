#include "standard.h"
extern int fdthrus ;
extern int **pairArray ;


alignfeed()
{

int row , last_up , last_dn , up , dn , cell_up , cell_dn ;
int net_up , net_dn , x_up , distance ;

distance = 0 ;
for( row = numRows - 1 ; row >= 1 ; row-- ) {
    last_up = pairArray[row+1][0] ;
    last_dn = pairArray[row][0] ;
    for( up = 1 ; up <= last_up ; up++ ) {
	cell_up = pairArray[row+1][up] ;
	if( cell_up >= numcells - fdthrus + 1 ) {
	    if( carray[cell_up]->tileptr->termsptr == TERMNULL ) {
		continue ;
	    }
	    net_up = tearray[ carray[cell_up]->tileptr->
					termsptr->cellterm ]->net ;
	    x_up   = carray[cell_up]->cxcenter ;
	    for( dn = 1 ; dn <= last_dn ; dn++ ) {
		cell_dn = pairArray[row][dn] ;
		if( cell_dn >= numcells - fdthrus + 1 ) {
		    if( carray[cell_dn]->tileptr->termsptr == 
							TERMNULL ) {
			continue ;
		    }
		    net_dn = tearray[ carray[cell_dn]->tileptr->
					termsptr->cellterm ]->net;
		    if( net_dn != net_up ) {
			continue ;
		    }
		    distance += re_place( pairArray[row] ,
					    cell_dn , dn , x_up ) ;
		    break ;
		}
	    }
	}
    }
}

return( distance ) ;
}



re_place( rowptr , cell , index , x_location )
int *rowptr , cell , index , x_location ;
{

int i , j , last , prev_x ;

last = rowptr[0] ;

if( carray[ rowptr[1] ]->cxcenter >= x_location ) {
    i = 0 ;
} else if( carray[ rowptr[last] ]->cxcenter <= x_location ) {
    i = last ;
} else {
    for( i = 1 ; i < last ; i++ ) {
	if( carray[ rowptr[i] ]->cxcenter <= x_location &&
		    carray[ rowptr[i+1] ]->cxcenter >= x_location ) {
	    break ;
	}
    }
}
prev_x = carray[cell]->cxcenter ;
if( index > i + 1 ) {
    for( j = index - 1 ; j >= i + 1 ; j-- ) {
	carray[ rowptr[j] ]->cxcenter += fdWidth ;
	rowptr[j+1] = rowptr[j] ;
    }
    rowptr[i+1] = cell ;

    carray[cell]->cxcenter = carray[ rowptr[i+2] ]->cxcenter +
	carray[ rowptr[i+2] ]->tileptr->left - (fdWidth - fdWidth / 2);
} else if( index < i ) {
    for( j = index + 1 ; j <= i ; j++ ) {
	carray[ rowptr[j] ]->cxcenter -= fdWidth ;
	rowptr[j-1] = rowptr[j] ;
    }
    rowptr[i] = cell ;
    carray[cell]->cxcenter = carray[ rowptr[i-1] ]->cxcenter +
	carray[ rowptr[i-1] ]->tileptr->right + fdWidth / 2 ;
}
return( ABS( carray[cell]->cxcenter - prev_x) ) ;
}



align_init()
{

int row , i , cell , *rowptr , j , last , width ;

for( row = 1 ; row <= numRows ; row++ ) {
    last = pairArray[row][0] ;
    for( i = 1 ; i <= last ; i++ ) {
	cell = pairArray[row][i] ;
	if( cell < numcells - fdthrus + 1 ) {
	    break ;
	}
    }
    if( i > 1 && i <= last ) {
	rowptr = pairArray[row] ;
	width = carray[cell]->tileptr->right -
				    carray[cell]->tileptr->left ;
	for( j = i - 1 ; j >= 1 ; j-- ) {
	    carray[ rowptr[j] ]->cxcenter += width ;
	    rowptr[j+1] = rowptr[j] ;
	}
	rowptr[1] = cell ;
	carray[cell]->cxcenter = carray[ rowptr[2] ]->cxcenter +
	    carray[ rowptr[2] ]->tileptr->left - (width - width / 2) ;
    }

    for( i = last ; i >= 1 ; i-- ) {
	cell = pairArray[row][i] ;
	if( cell < numcells - fdthrus + 1 ) {
	    break ;
	}
    }
    if( i < last && i >= 1 ) {
	rowptr = pairArray[row] ;
	width = carray[cell]->tileptr->right -
				    carray[cell]->tileptr->left ;
	for( j = i + 1 ; j <= last ; j++ ) {
	    carray[ rowptr[j] ]->cxcenter -= width ;
	    rowptr[j-1] = rowptr[j] ;
	}
	rowptr[last] = cell ;
	carray[cell]->cxcenter = carray[ rowptr[last-1] ]->cxcenter +
	    carray[ rowptr[last-1] ]->tileptr->right + width / 2 ;
    }
}
return ;
}
