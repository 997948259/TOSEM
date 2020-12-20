#include "standard.h"
#include "groute.h"

urcost( segment )
int segment ;
{

SEGBOXPTR asegptr , bsegptr ;
CHANGRDPTR aptr1 , aptr2 , bptr1 , bptr2 , bptr , fptr , ptr ;
CHANGRDPTR saptr , eaptr , sbptr , ebptr ;
DENSITYPTR denptr , headptr ;
int penalty , check ;
int x , achannel , bchannel , aMaxVal , bMaxVal ;
int maxaa , maxbb ;
int aoutside , binside ;
int ax1 , ax2 , bx1 , bx2 ;
int net , Flag , track ;

penalty = 0 ;
net = aNetSeg[segment].net ;
if( aNetSeg[segment].current == 0 ) {
    asegptr = aNetSeg[segment].top ;
    bsegptr = aNetSeg[segment].bot ;
} else {
    asegptr = aNetSeg[segment].bot ;
    bsegptr = aNetSeg[segment].top ;
}
achannel = asegptr->channel ;
bchannel = bsegptr->channel ;
aptr1 = asegptr->pin1ptr ;
aptr2 = asegptr->pin2ptr ;
bptr1 = bsegptr->pin1ptr ;
bptr2 = bsegptr->pin2ptr ;

aMaxVal = maxTrack[achannel] ;
bMaxVal = maxTrack[bchannel] ;
ax1 = aptr1->netptr->xpos ;
ax2 = aptr2->netptr->xpos ;
bx1 = bptr1->netptr->xpos ;
bx2 = bptr2->netptr->xpos ;
net = aNetSeg[segment].net ;
if( aptr1->SegType > 0 ) {   /* segment start from here */
    Flag = 0 ;
    bptr = aptr1 ;
    while( bptr->prevgrd != GRDNULL 
		&& bptr->prevgrd->netptr->xpos == ax1 ) {
	if( net == tearray[bptr->prevgrd->netptr->terminal]->net 
			    && bptr->prevgrd->SegType < 0 ) {
	    Flag = 1 ;
	    saptr = aptr1->nextgrd ;
	    while( saptr->netptr->xpos == ax1 ) {
		saptr = saptr->nextgrd ;
	    }
	    break ;
	} else {
	    bptr = bptr->prevgrd ;
	}
    }
    if( !Flag ) {
	saptr = aptr1->nextgrd ;
	while( saptr->netptr->xpos == ax1 ) {
	    if( net == tearray[saptr->netptr->terminal]->net 
				&& saptr->SegType < 0 ) {
		Flag = 1 ;
	    }
	    saptr = saptr->nextgrd ;
	}
    }
    if( !Flag ) {
	saptr = bptr ;
    }
} else {
    if( ax1 != gxstart ) {
	saptr = aptr1->nextgrd ;
	while( saptr->netptr->xpos == ax1 ) {
	    saptr = saptr->nextgrd ;
	}
    } else {
	saptr = aptr1 ;
    }
}

if( aptr2->SegType < 0 ) {   /* segment end here */
    Flag = 0 ;
    fptr = aptr2 ;
    while( fptr->nextgrd != GRDNULL 
		&& fptr->nextgrd->netptr->xpos == ax2 ) {
	if( net == tearray[fptr->nextgrd->netptr->terminal]->net
			    && fptr->nextgrd->SegType > 0 ) {
	    Flag = 1 ;
	    eaptr = aptr2->prevgrd ;
	    while( eaptr->netptr->xpos == ax2 ) {
		eaptr = eaptr->prevgrd ;
	    }
	    break ;
	} else {
	    fptr = fptr->nextgrd ;
	}
    }
    if( !Flag ) {
	eaptr = aptr2->prevgrd ;
	while( eaptr->netptr->xpos == ax2 ) {
	    if( net == tearray[eaptr->netptr->terminal]->net 
				&& eaptr->SegType > 0 ) {
		Flag = 1 ;
	    }
	    eaptr = eaptr->prevgrd ;
	}
    }
    if( !Flag ) {
	eaptr = fptr ;
    }
} else {
    if( ax2 != gxstop ) {
	eaptr = aptr2->prevgrd ;
	while( eaptr->netptr->xpos == ax2 ) {
	    eaptr = eaptr->prevgrd ;
	}
    } else {
	eaptr = aptr2 ;
    }
}

if( bptr1->SegType >= 0 ) { /* no segment ended here */
    Flag = 0 ;
    bptr = bptr1 ;
    while( bptr->prevgrd != GRDNULL 
		&& bptr->prevgrd->netptr->xpos == bx1 ) {
	if( net == tearray[bptr->prevgrd->netptr->terminal]->net 
			    && bptr->prevgrd->SegType < 0 ) {
	    Flag = 1 ;
	    sbptr = bptr1->nextgrd ;
	    while( sbptr->netptr->xpos == bx1 ) {
		sbptr = sbptr->nextgrd ;
	    }
	    break ;
	} else {
	    bptr = bptr->prevgrd ;
	}
    }
    if( !Flag ) {
	sbptr = bptr1->nextgrd ;
	while( sbptr->netptr->xpos == bx1 ) {
	    if( net == tearray[sbptr->netptr->terminal]->net 
				&& sbptr->SegType < 0 ) {
		Flag = 1 ;
	    }
	    sbptr = sbptr->nextgrd ;
	}
    }
    if( !Flag ) {
	sbptr = bptr ;
    }
} else {    /* segment ended here */
    sbptr = bptr1->nextgrd ;
    while( sbptr->netptr->xpos == bx1 ) {
	sbptr = sbptr->nextgrd ;
    }
}

if( bptr2->SegType <= 0 ) {  /* no segment start from here */
    Flag = 0 ;
    fptr = bptr2 ;
    while( fptr->nextgrd != GRDNULL 
		&& fptr->nextgrd->netptr->xpos == bx2 ) {
	if( net == tearray[fptr->nextgrd->netptr->terminal]->net
			    && fptr->nextgrd->SegType > 0 ) {
	    Flag = 1 ;
	    ebptr = bptr2->prevgrd ;
	    while( ebptr->netptr->xpos == bx2 ) {
		ebptr = ebptr->prevgrd ;
	    }
	    break ;
	} else {
	    fptr = fptr->nextgrd ;
	}
    }
    if( !Flag ) {
	ebptr = bptr2->prevgrd ;
	while( ebptr->netptr->xpos == bx2 ) {
	    if( net == tearray[ebptr->netptr->terminal]->net 
				&& ebptr->SegType > 0 ) {
		Flag = 1 ;
	    }
	    ebptr = ebptr->prevgrd ;
	}
    }
    if( !Flag ) {
	ebptr = fptr ;
    }
} else {
    ebptr = bptr2->prevgrd ;
    while( ebptr->netptr->xpos == bx2 ) {
	ebptr = ebptr->prevgrd ;
    }
}

aoutside = 0 ;
ax1 = saptr->netptr->xpos ;
ax2 = eaptr->netptr->xpos ;
denptr = DboxHead[ achannel ][ aMaxVal ]->next ;
for( ; denptr != DENSENULL ; denptr = denptr->next ) {
    x = denptr->grdptr->netptr->xpos ;
    if( !( ax1 <= x && ax2 >= x ) ) {
	aoutside = 1 ;
	break ;
    }
}
if( aoutside == 0 ) {
    penalty-- ;
}

binside  = 0 ;
bx1 = sbptr->netptr->xpos ;
bx2 = ebptr->netptr->xpos ;
denptr = DboxHead[ bchannel ][ bMaxVal ]->next ;
for( ; denptr != DENSENULL ; denptr = denptr->next ) {
    x = denptr->grdptr->netptr->xpos ;
    if( bx1 <= x && bx2 >= x ) {
	binside = 1 ;
	break ;
    }
}
if( binside == 1 ) {
    penalty++ ;
}

eaptr = eaptr->nextgrd ;
ebptr = ebptr->nextgrd ;
if( penalty == 0 ) {
    if( binside == 1 && aoutside == 0 ) {
	/* check = (aMaxVal - 1) - (bMaxVal + 1) ; */
	check = bMaxVal - aMaxVal + 2 ;
    } else {
	maxaa = 0 ;
	maxbb = 0 ;
	for( ptr = saptr ; ptr != eaptr ; ptr = ptr->nextgrd ) {
	    if( ptr->tracks > maxaa ) {
		maxaa = ptr->tracks ;
	    }
	}
	for( ptr = sbptr ; ptr != ebptr ; ptr = ptr->nextgrd ) {
	    if( ptr->tracks > maxbb ) {
		maxbb = ptr->tracks ;
	    }
	}
	maxaa = aMaxVal  - maxaa + 1 ;
	maxbb = bMaxVal  - maxbb - 1 ;
	check = maxaa - maxbb ;
    }
} else {
    check = penalty ;
}

if( check <= 0 ) {
    if( asegptr->pin1 <= maxterm ) {
	aptr1->SegType -= RIGHT ;
    }
    if( asegptr->pin2 <= maxterm ) {
	aptr2->SegType -= LEFT  ;
    }
    if( bsegptr->pin1 <= maxterm ) {
	bptr1->SegType += RIGHT ;
    }
    if( bsegptr->pin2 <= maxterm ) {
	bptr2->SegType += LEFT  ;
    }
    for( ptr = saptr ; ptr != eaptr ; ptr = ptr->nextgrd ) {
	denptr = ptr->dptr ;
	if( denptr->next != DENSENULL ) {
	    denptr->next->back = denptr->back ;
	}
	denptr->back->next = denptr->next ;
	track = --(ptr->tracks) ;

	headptr = DboxHead[ achannel ][ track ]->next ;
	if( headptr != DENSENULL ) {
	    DboxHead[ achannel ][ track ]->next = denptr ;
	    denptr->next  = headptr ;
	    headptr->back = denptr  ;
	    denptr->back  = DboxHead[ achannel ][ track ] ;
	} else {
	    DboxHead[ achannel ][ track ]->next = denptr ;
	    denptr->next = DENSENULL ;
	    denptr->back = DboxHead[ achannel ][ track ];
	}
    }
    if( aoutside == 0 ) {
	maxTrack[achannel]-- ;
    }
    for( ptr = sbptr ; ptr != ebptr ; ptr = ptr->nextgrd ) {
	denptr = ptr->dptr ;
	if( denptr->next != DENSENULL ) {
	    denptr->next->back = denptr->back ;
	}
	denptr->back->next = denptr->next ;
	track = ++(ptr->tracks) ;

	headptr = DboxHead[ bchannel ][ track ]->next ;
	if( headptr != DENSENULL ) {
	    DboxHead[ bchannel ][ track ]->next = denptr ;
	    denptr->next  = headptr ;
	    headptr->back = denptr  ;
	    denptr->back  = DboxHead[ bchannel ][ track ] ;
	} else {
	    DboxHead[ bchannel ][ track ]->next = denptr ;
	    denptr->next = DENSENULL ;
	    denptr->back = DboxHead[ bchannel ][ track ];
	}
    }
    if( binside == 1 ) {
	maxTrack[bchannel]++ ;
    }
    if( aNetSeg[segment].current == 1 ) {
	aNetSeg[segment].current = 0 ;
    } else {
	aNetSeg[segment].current = 1 ;
    }

    tracks += penalty ;
    return (1) ;
} else {
    return (0) ;
}
}
