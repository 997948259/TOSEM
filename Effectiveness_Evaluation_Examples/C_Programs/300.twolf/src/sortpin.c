#include "standard.h"

sortpin()

{

int j , n , cell ;
CBOXPTR ptr ;
TIBOXPTR tile ;
TEBOXPTR term , *xpptr ;
NBOXPTR termptr ;

xpptr = (TEBOXPTR *) safe_malloc( 300 * sizeof( TEBOXPTR ) ) ;
for( cell = 1 ; cell <= numcells + numterms ; cell++ ) {
    ptr = carray[ cell ] ;
    if( ( tile = ptr->tileptr ) == TILENULL ) {
	continue ;
    }
    n = 0 ;
    for( term = tile->termsptr ; term != TERMNULL ;
				  term = term->nextterm ) {
	termptr = tearray[ term->cellterm ] ;
	term->net = termptr->net ;
	term->termptr = termptr ;
	xpptr[ ++n ] = term ;
    }
    shellsort( xpptr , n ) ;
    xpptr[ n + 1 ] = TERMNULL ;
    ptr->tileptr->termsptr = xpptr[ 1 ] ;
    for( j = 1 ; j <= n ; j++ ) {
	xpptr[j]->nextterm = xpptr[j+1] ;
    }
}
safe_free( xpptr ) ;
}


shellsort( term , n )
TEBOXPTR *term ;
int n ;
{

TEBOXPTR ptr ;
int incr , i , j ;

for( incr = n / 2 ; incr > 0 ; incr /= 2 ) {
    for( i = incr + 1 ; i <= n ; i++ ) {
	for( j = i - incr ; j > 0 && 
	(term[j]->net > term[j+incr]->net) ; j -= incr ) {
	    ptr = term[j] ;
	    term[j] = term[j+incr] ;
	    term[j+incr] = ptr ;
	}
    }
}
}
