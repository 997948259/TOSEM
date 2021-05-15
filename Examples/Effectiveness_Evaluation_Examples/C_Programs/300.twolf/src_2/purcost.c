#include "standard.h"
#include "groute.h"
extern int maxterm ;

purcost( segment )
int segment ;
{

SEGBOXPTR top , bot , asegptr , bsegptr ;
CHANGRDPTR aptr1 , aptr2 , bptr1 , bptr2 , bptr , fptr , ptr ;
CHANGRDPTR saptr , eaptr , sbptr , ebptr ;
DENSITYPTR denptr , headptr ;
int penalty , current , check ;
int x , achannel , bchannel , aMaxVal , bMaxVal ;
int maxaa , maxbb ;
int aoutside , binside ;
int ax1 , ax2 , bx1 , bx2 ;
int net , Flag , track ;

penalty = 0 ;

if( aNetSeg[segment].nflag == 0 ) {
    top = aNetSeg[segment].top ;
    bot = aNetSeg[segment].bot ;
    current = aNetSeg[segment].current ;
} else {
    top = aNetSeg[segment].ntop ;
    bot = aNetSeg[segment].nbot ;
    current = aNetSeg[segment].ncurrent ;
}
if( current == 0 ) {
    asegptr = top ;
    bsegptr = bot ;
} else {
    asegptr = bot ;
    bsegptr = top ;
}
achannel = asegptr->channel ;
bchannel = bsegptr->channel ;
aptr1 = asegptr->pin1ptr ;
aptr2 = asegptr->pin2ptr ;
bptr1 = bsegptr->pin1ptr ;
bptr2 = bsegptr->pin2ptr ;

aMaxVal = nmaxTrack[achannel] ;
bMaxVal = nmaxTrack[bchannel] ;
ax1 = aptr1->netptr->xpos ;
ax2 = aptr2->netptr->xpos ;
bx1 = bptr1->netptr->xpos ;
bx2 = bptr2->netptr->xpos ;
net = aNetSeg[segment].net ;

if( aptr1->nSegType > 0 ) {  /* segment start from here */
    Flag = 0 ;
    bptr = aptr1 ;
    while( bptr->nprevgrd != GRDNULL 
		&& bptr->nprevgrd->netptr->xpos == ax1 ) {
	if( net == tearray[bptr->nprevgrd->netptr->terminal]->net 
			    && bptr->nprevgrd->nSegType < 0 ) {
	    Flag = 1 ;
	    saptr = aptr1->nnextgrd ;
	    while( saptr->netptr->xpos == ax1 ) {
		saptr = saptr->nnextgrd ;
	    }
	    break ;
	} else {
	    bptr = bptr->nprevgrd ;
	}
    }
    if( !Flag ) {
	saptr = aptr1->nnextgrd ;
	while( saptr->netptr->xpos == ax1 ) {
	    if( net == tearray[saptr->netptr->terminal]->net 
				&& saptr->nSegType < 0 ) {
		Flag = 1 ;
	    }
	    saptr = saptr->nnextgrd ;
	}
    }
    if( !Flag ) {
	saptr = bptr ;
    }
} else {
    if( ax1 != gxstart ) {
	saptr = aptr1->nnextgrd ;
	while( saptr->netptr->xpos == ax1 ) {
	    saptr = saptr->nnextgrd ;
	}
    } else {
	saptr = aptr1 ;
    }
}

if( aptr2->nSegType < 0 ) {  /* segment ended here */
    Flag = 0 ;
    fptr = aptr2 ;
    while( fptr->nnextgrd != GRDNULL 
		&& fptr->nnextgrd->netptr->xpos == ax2 ) {
	if( net == tearray[fptr->nnextgrd->netptr->terminal]->net
			    && fptr->nnextgrd->nSegType > 0 ) {
	    Flag = 1 ;
	    eaptr = aptr2->nprevgrd ;
	    while( eaptr->netptr->xpos == ax2 ) {
		eaptr = eaptr->nprevgrd ;
	    }
	    break ;
	} else {
	    fptr = fptr->nnextgrd ;
	}
    }
    if( !Flag ) {
	eaptr = aptr2->nprevgrd ;
	while( eaptr->netptr->xpos == ax2 ) {
	    if( net == tearray[eaptr->netptr->terminal]->net 
				&& eaptr->nSegType > 0 ) {
		Flag = 1 ;
	    }
	    eaptr = eaptr->nprevgrd ;
	}
    }
    if( !Flag ) {
	eaptr = fptr ;
    }
} else {
    if( ax2 != gxstop ) {
	eaptr = aptr2->nprevgrd ;
	while( eaptr->netptr->xpos == ax2 ) {
	    eaptr = eaptr->nprevgrd ;
	}
    } else {
	eaptr = aptr2 ;
    }
}

if( bptr1->nSegType >= 0 ) {  /* no segment ended here */
    Flag = 0 ;
    bptr = bptr1 ;
    while( bptr->nprevgrd != GRDNULL 
		&& bptr->nprevgrd->netptr->xpos == bx1 ) {
	if( net == tearray[bptr->nprevgrd->netptr->terminal]->net 
			    && bptr->nprevgrd->nSegType < 0 ) {
	    Flag = 1 ;
	    sbptr = bptr1->nnextgrd ;
	    while( sbptr->netptr->xpos == bx1 ) {
		sbptr = sbptr->nnextgrd ;
	    }
	    break ;
	} else {
	    bptr = bptr->nprevgrd ;
	}
    }
    if( !Flag ) {
	sbptr = bptr1->nnextgrd ;
	while( sbptr->netptr->xpos == bx1 ) {
	    if( net == tearray[sbptr->netptr->terminal]->net 
				&& sbptr->nSegType < 0 ) {
		Flag = 1 ;
	    }
	    sbptr = sbptr->nnextgrd ;
	}
    }
    if( !Flag ) {
	sbptr = bptr ;
    }
} else {
    sbptr = bptr1->nnextgrd ;
    while( sbptr->netptr->xpos == bx1 ) {
	sbptr = sbptr->nnextgrd ;
    }
}

if( bptr2->nSegType <= 0 ) {  /* no segments start from here */
    Flag = 0 ;
    fptr = bptr2 ;
    while( fptr->nnextgrd != GRDNULL 
		&& fptr->nnextgrd->netptr->xpos == bx2 ) {
	if( net == tearray[fptr->nnextgrd->netptr->terminal]->net
			    && fptr->nnextgrd->nSegType > 0 ) {
	    Flag = 1 ;
	    ebptr = bptr2->nprevgrd ;
	    while( ebptr->netptr->xpos == bx2 ) {
		ebptr = ebptr->nprevgrd ;
	    }
	    break ;
	} else {
	    fptr = fptr->nnextgrd ;
	}
    }
    if( !Flag ) {
	ebptr = bptr2->nprevgrd ;
	while( ebptr->netptr->xpos == bx2 ) {
	    if( net == tearray[ebptr->netptr->terminal]->net 
				&& ebptr->nSegType > 0 ) {
		Flag = 1 ;
	    }
	    ebptr = ebptr->nprevgrd ;
	}
    }
    if( !Flag ) {
	ebptr = fptr ;
    }
} else {
    ebptr = bptr2->nprevgrd ;
    while( ebptr->netptr->xpos == bx2 ) {
	ebptr = ebptr->nprevgrd ;
    }
}

aoutside = 0 ;
ax1 = saptr->netptr->xpos ;
ax2 = eaptr->netptr->xpos ;
denptr = DboxHead[ achannel ][ aMaxVal ]->nnext ;
for( ; denptr != DENSENULL ; denptr = denptr->nnext ) {
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
denptr = DboxHead[ bchannel ][ bMaxVal ]->nnext ;
for( ; denptr != DENSENULL ; denptr = denptr->nnext ) {
    x = denptr->grdptr->netptr->xpos ;
    if( bx1 <= x && bx2 >= x ) {
	binside = 1 ;
	break ;
    }
}
if( binside == 1 ) {
    penalty++ ;
}

eaptr = eaptr->nnextgrd ;
ebptr = ebptr->nnextgrd ;
if( penalty == 0 ) {
    if( binside == 1 && aoutside == 0 ) {
	/* check = (aMaxVal - 1) - (bMaxVal + 1) ; */
	check = bMaxVal - aMaxVal + 2 ;
    } else {
	maxaa = 0 ;
	maxbb = 0 ;
	for( ptr = saptr ; ptr != eaptr ; ptr = ptr->nnextgrd ) {
	    if( ptr->ntracks > maxaa ) {
		maxaa = ptr->ntracks ;
	    }
	}
	for( ptr = sbptr ; ptr != ebptr ; ptr = ptr->nnextgrd ) {
	    if( ptr->ntracks > maxbb ) {
		maxbb = ptr->ntracks ;
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
	aptr1->nSegType -= RIGHT ;
    }
    if( asegptr->pin2 <= maxterm ) {
	aptr2->nSegType -= LEFT  ;
    }
    if( bsegptr->pin1 <= maxterm ) {
	bptr1->nSegType += RIGHT ;
    }
    if( bsegptr->pin2 <= maxterm ) {
	bptr2->nSegType += LEFT  ;
    }
    for( ptr = saptr ; ptr != eaptr ; ptr = ptr->nnextgrd ) {
	denptr = ptr->dptr ;
	if( denptr->nnext != DENSENULL ) {
	    denptr->nnext->nback = denptr->nback ;
	}
	denptr->nback->nnext = denptr->nnext ;
	track = --(ptr->ntracks) ;

	headptr = DboxHead[ achannel ][ track ]->nnext ;
	if( headptr != DENSENULL ) {
	    DboxHead[ achannel ][ track ]->nnext = denptr ;
	    denptr->nnext  = headptr ;
	    headptr->nback = denptr  ;
	    denptr->nback  = DboxHead[ achannel ][ track ] ;
	} else {
	    DboxHead[ achannel ][ track ]->nnext = denptr ;
	    denptr->nnext = DENSENULL ;
	    denptr->nback = DboxHead[ achannel ][ track ];
	}
    }
    if( aoutside == 0 ) {
	--(nmaxTrack[achannel]) ;
    }
    for( ptr = sbptr ; ptr != ebptr ; ptr = ptr->nnextgrd ) {
	denptr = ptr->dptr ;
	if( denptr->nnext != DENSENULL ) {
	    denptr->nnext->nback = denptr->nback ;
	}
	denptr->nback->nnext = denptr->nnext ;
	track = ++(ptr->ntracks) ;

	headptr = DboxHead[ bchannel ][ track ]->nnext ;
	if( headptr != DENSENULL ) {
	    DboxHead[ bchannel ][ track ]->nnext = denptr ;
	    denptr->nnext  = headptr ;
	    headptr->nback = denptr  ;
	    denptr->nback  = DboxHead[ bchannel ][ track ] ;
	} else {
	    DboxHead[ bchannel ][ track ]->nnext = denptr ;
	    denptr->nnext = DENSENULL ;
	    denptr->nback = DboxHead[ bchannel ][ track ];
	}
    }
    if( binside == 1 ) {
	nmaxTrack[bchannel]++ ;
    }
    if( aNetSeg[segment].nflag == 0 ) {
	if( current == 1 ) {
	    aNetSeg[segment].current = 0 ;
	} else {
	    aNetSeg[segment].current = 1 ;
	}
    } else {
	if( current == 1 ) {
	    aNetSeg[segment].ncurrent = 0 ;
	} else {
	    aNetSeg[segment].ncurrent = 1 ;
	}
    }

    tracks += penalty ;
    return (1) ;
} else {
    return (0) ;
}
}
