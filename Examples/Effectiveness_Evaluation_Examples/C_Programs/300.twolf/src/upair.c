#include "standard.h"
#define PICK_INT(l,u) (((l)<(u)) ? ((RAND % ((u)-(l)+1))+(l)) : (l))
extern int attmax ;
extern int iteration ;
extern double T ;
extern FILE *fpo ;
extern int **pairArray ;

upair()
{

CBOXPTR acellptr, bcellptr ; 
BBOXPTR ablckptr ;
int a , b , ablock , aorient ;
int flips , attempts ;
int axcenter,anxcenter, bnxcenter ;
int aleft , aright ; 
int startx1, endx1;
int cellleft, cellrite;
int leftEdge, riteEdge;
int aptr ;

flips = 0 ;
attempts = 0 ;

while( attempts < attmax ) {
    ablock = PICK_INT( 1 , numblock ) ;
    if( pairArray[ablock][0] <= 1 ) {
	continue ;
    }
    aptr = PICK_INT( 1 , pairArray[ablock][0] ) ;

    a = pairArray[ablock][aptr] ;
    acellptr = carray[ a ]  ;
    if( acellptr->cclass == -1 ) {
	continue ;
    }
    aorient = acellptr->corient ;

    ablckptr = barray[ ablock ] ;
    axcenter = acellptr->cxcenter ;

    aleft = acellptr->tileptr->left ;
    aright = acellptr->tileptr->right ;
    startx1 = axcenter + aleft    ; 
    endx1   = axcenter + aright   ; 
    if( aptr > 1 ) {
	cellleft = pairArray[ablock][aptr - 1] ;
	if( carray[cellleft]->cclass == -1 ) {
	    cellleft = 0 ;
	}
    } else {
	cellleft = 0 ;
    }
    if( aptr < pairArray[ablock][0] ) {
	cellrite = pairArray[ablock][aptr + 1] ;
	if( carray[cellrite]->cclass == -1 ) {
	    cellrite = 0 ;
	}
    } else {
	cellrite = 0 ;
    }
    if( cellleft == 0 && cellrite == 0 ) {
	continue ;
    }

    if( cellleft != 0 && cellrite != 0 ) {
	if( PICK_INT(1 , 2) == 1 ){
	    /*
	     *   Take the left neighbor first.
	     */
	    b = cellleft ;
	    bcellptr = carray[b] ;
	    leftEdge = bcellptr->cxcenter + bcellptr->tileptr->left ;
	    anxcenter = leftEdge - aleft ;
	    bnxcenter = endx1 - bcellptr->tileptr->right ;
	    if( ucxxp( a, b, anxcenter, bnxcenter ) ) {
		flips++ ;
		attempts++ ;
		pairArray[ablock][aptr] = b ;
		pairArray[ablock][aptr - 1] = a ;
	    } else {
		attempts++ ;
		b = cellrite ;
		bcellptr = carray[b] ;
		riteEdge = bcellptr->cxcenter 
				+ bcellptr->tileptr->right ;
		anxcenter = riteEdge - aright ;
		bnxcenter = startx1 - bcellptr->tileptr->left ;
		if( ucxxp( a, b, anxcenter, bnxcenter ) ) {
		    flips++ ;
		    pairArray[ablock][aptr] = b ;
		    pairArray[ablock][aptr + 1] = a ;
		} 
		attempts++ ;
	    }
	} else {
	    b = cellrite ;
	    bcellptr = carray[b] ;
	    riteEdge = bcellptr->cxcenter + bcellptr->tileptr->right ;
	    anxcenter = riteEdge - aright ;
	    bnxcenter = startx1 - bcellptr->tileptr->left ;
	    if( ucxxp( a, b, anxcenter, bnxcenter ) ) {
		flips++ ;
		attempts++ ;
		pairArray[ablock][aptr] = b ;
		pairArray[ablock][aptr + 1] = a ;
	    } else {
		attempts++ ;
		b = cellleft ;
		bcellptr = carray[b] ;
		leftEdge = bcellptr->cxcenter + bcellptr->tileptr->left;
		anxcenter = leftEdge - aleft ;
		bnxcenter = endx1 - bcellptr->tileptr->right ;
		if( ucxxp( a, b, anxcenter, bnxcenter ) ) {
		    flips++ ;
		    pairArray[ablock][aptr] = b ;
		    pairArray[ablock][aptr - 1] = a ;
		} 
		attempts++ ;
	    }
	}
    } else {
	if( cellleft ) {
	    b = cellleft ;
	    bcellptr = carray[b] ;
	    leftEdge = bcellptr->cxcenter + bcellptr->tileptr->left ;
	    anxcenter = leftEdge - aleft ;
	    bnxcenter = endx1 - bcellptr->tileptr->right ;
	    if( ucxxp( a, b, anxcenter, bnxcenter ) ) {
		flips++ ;
		pairArray[ablock][aptr] = b ;
		pairArray[ablock][aptr - 1] = a ;
	    } 
	    attempts++ ;
	} else if( cellrite != 0 && 
		    carray[cellrite]->cclass != -1 &&
		    acellptr->cclass != -1 ) {
	    b = cellrite ;
	    bcellptr = carray[b] ;
	    riteEdge = bcellptr->cxcenter + bcellptr->tileptr->right ;
	    anxcenter = riteEdge - aright ;
	    bnxcenter = startx1 - bcellptr->tileptr->left ;
	    if( ucxxp( a, b, anxcenter, bnxcenter ) ) {
		flips++ ;
		pairArray[ablock][aptr] = b ;
		pairArray[ablock][aptr + 1] = a ;
	    } 
	    attempts++ ;
	}
    }
    if( ablckptr->borient == 1 ) {
	if( acellptr->orflag != 0 ) {
	    uc0( a , (aorient == 0) ? 2 : 0 ) ;
	}
    } else {
	if( acellptr->orflag != 0 ) {
	    uc0( a , (aorient == 1) ? 3 : 1 ) ;
	}
    }
}
fprintf( fpo, " %3d %6.3f %9d  %3d%s\n", iteration+1 , T , funccost ,
	(int)( 100.0 * (double)(flips) / (double)(attmax) ) , "%" ) ;
fflush( fpo ) ;
return;
}
