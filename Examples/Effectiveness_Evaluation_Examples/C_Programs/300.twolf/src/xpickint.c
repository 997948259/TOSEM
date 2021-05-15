#include <stdio.h>
#include <math.h>
#include "standard.h"
#define RAND (Yacm_random() )
#define PICK_INT(l,u) (((l)<(u)) ? ((RAND % ((u)-(l)+1))+(l)) : (l))
extern int randVar ;

XPICK_INT( l , u , c )
int l , u , c ;
{

    int d ;

    if ( c < 0 ) {
	return(-c) ;
    } else {
        do {
	    d = PICK_INT(l,u) ;
	} while ( d == c ) ;
	return(d) ;
    }
}
