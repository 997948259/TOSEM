#include "standard.h"
#include "groute.h"

#define YES 1
#define NO  0
extern int randVar ;
extern FILE *fpo ;

uglobrout()
{

int attperseg ;
int attlimit , attempts , swSeg ;
int stoppoint , breakpoint ;
int found , channel ;
int x , x1 , x2 ;
SEGBOXPTR segptr ;
DENSITYPTR denptr ;


attperseg = 5 ;

unetseg() ;

attlimit = attperseg * numSwSegs ;

attempts = 0 ;
breakpoint = 0 ;
stoppoint = 1.5 * numSwSegs ;

while( attempts < attlimit ) {
    for( ; ; ) {
	do {
	    swSeg = (int) ( (double) numSegs * ( (double) RAND / 
					  (double) 0x7fffffff ) ) + 1 ;
	} while( swSeg == numSegs + 1 ) ;
	if( aNetSeg[swSeg].nflag == 1 ) {
	    if( aNetSeg[swSeg].nswYorN == 1 && 
			    aNetSeg[swSeg].nkey == 0 ) {
		break ;
	    }
	} else {
	    if( aNetSeg[swSeg].swYorN == 1 && 
			    aNetSeg[swSeg].key == 0 ) {
		break ;
	    }
	}
    }

    if( aNetSeg[swSeg].nflag == 0 ) {
	if( aNetSeg[swSeg].current == 0 ) {
	    segptr = aNetSeg[swSeg].top ;
	} else {
	    segptr = aNetSeg[swSeg].bot ;
	}
    } else {
	if( aNetSeg[swSeg].ncurrent == 0 ) {
	    segptr = aNetSeg[swSeg].ntop ;
	} else {
	    segptr = aNetSeg[swSeg].nbot ;
	}
    }
    channel = segptr->channel ;
    x1  = segptr->pin1ptr->netptr->xpos ;
    x2  = segptr->pin2ptr->netptr->xpos ;
    if( ( channel > gtopChan ) || ( channel < gbotChan ) ||
	    ( x2 < Left_bound ) || ( x1 > Rite_bound ) ) {
	attempts++ ;
	continue ;
    }

    found = NO ;

    for( denptr = DboxHead[ channel ][ nmaxTrack[channel] ]->nnext ;
		    denptr != DENSENULL ; denptr = denptr->nnext ) {
	x = denptr->grdptr->netptr->xpos ;
	if( x1 <= x && x2 >= x ) {
	    found = YES ;
	    break ;
	}
    }
    if( !found ) {
	if( ++breakpoint > stoppoint ) {
	    break ;
	}
	attempts++ ;
	continue ;
    }

    if( purcost( swSeg ) ) {
	attempts++ ;
	breakpoint = 0 ;
    } else {
	if( ++breakpoint > stoppoint ) {
	    break ;
	}
	attempts++ ;
    }
}
return ;
}
