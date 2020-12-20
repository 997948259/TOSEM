#include "standard.h"

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

#define INULL  (IBOXPTR) NULL
#define IPNULL (IPBOXPTR) NULL

IBOXPTR siptr ;
extern int ifrange ;
extern int numRows ;
IBOXPTR *impFeeds  ;


implfeeds( row , xc )
int row , xc ;
{

IBOXPTR iptr ;
int minspan ;

minspan = 32000 ;
siptr = INULL ;
for( iptr = impFeeds[row] ; iptr != INULL ; iptr = iptr->niptr ) {
    if( iptr->iactive <= 0 ) {
	if( ABS(iptr->aveXpos - xc) < minspan ) {
	    minspan = ABS(iptr->aveXpos - xc) ;
	    siptr = iptr ;
	}
    }
}
if( siptr != INULL && minspan <= ifrange ) {
    if( siptr->iactive == 0 ) {
	siptr->iactive = 1 ;
    } else {
	siptr->iactive = 2 ;
    }
    return(1);
} else {
    return(0);
}
}


impfix()
{

IBOXPTR iptr , niptr ;
IPBOXPTR ipptr , nipptr ;
int row ;

for( row = 1 ; row <= numRows ; row++ ) {
    iptr = impFeeds[row] ;
    if( iptr == INULL ) {
	continue ;
    }
    if( iptr->iactive != 1 ) {
	ipptr = iptr->iptr;
	while( ipptr != IPNULL ) {
	    nipptr = ipptr->npin ;
	    safe_free( ipptr ) ;
	    ipptr = nipptr ;
	}
	niptr = iptr->niptr ;
	safe_free( iptr ) ;
	iptr = niptr ;
	while( iptr != INULL ) {
	    if( iptr->iactive == 1 ) {
		break ;
	    } else {
		for( ipptr = iptr->iptr; ipptr != IPNULL ; ) {
		    nipptr = ipptr->npin ;
		    safe_free( ipptr ) ;
		    ipptr = nipptr ;
		}
		niptr = iptr->niptr ;
		safe_free( iptr ) ;
		iptr = niptr ;
	    }
	}
	impFeeds[row] = iptr ;
    }
    if( iptr != INULL ) {
	niptr = iptr->niptr ;
	while( niptr != INULL ) {
	    if( niptr->iactive != 1 ) {
		for( ipptr = niptr->iptr; ipptr != IPNULL ; ) {
		    nipptr = ipptr->npin ;
		    safe_free( ipptr ) ;
		    ipptr = nipptr ;
		}
		iptr->niptr = niptr->niptr ;
		safe_free( niptr ) ;
		niptr = iptr->niptr ;
	    } else {
		iptr = niptr ;
		niptr = iptr->niptr ;
	    }
	}
    }
}
for( row = 1 ; row <= numRows ; row++ ) {
    for( iptr = impFeeds[row] ; iptr != INULL ; iptr = iptr->niptr ) {
	iptr->iactive = 0 ;
    }
}

return ;
}



impclobr()
{

IBOXPTR iptr , niptr ;
IPBOXPTR ipptr , nipptr ;
int row ;

for( row = 1 ; row <= numRows ; row++ ) {
    iptr = impFeeds[row] ;
    while( iptr != INULL ) {
	niptr = iptr->niptr ;
	for( ipptr = iptr->iptr; ipptr != IPNULL ; ) {
	    nipptr = ipptr->npin ;
	    safe_free( ipptr ) ;
	    ipptr = nipptr ;
	}
	safe_free( iptr ) ;
	iptr = niptr ;
    }
}
safe_free( impFeeds ) ;

return ;
}
