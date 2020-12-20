#include "standard.h"
#include "groute.h"

findrchk()
{

SEGBOXPTR segptr ;
CHANGRDPTR ptr1 , ptr2 , bptr , fptr , sptr , eptr , ptr , gdptr ;
int chan , segment ;
int pin1 , pin2 , x1 , x2 ;
int net , Flag ;

for( chan = 1 ; chan <= numChans ; chan++ ) {
    for( gdptr = Begin[ chan ] ; gdptr != GRDNULL ;
				    gdptr = gdptr->nnextgrd ) {
	gdptr->ntracks = 0 ;
	gdptr->nSegType = 0 ;
    }
}
for( segment = 1 ; segment <= numSegs ; segment++ ) {
    if( aNetSeg[segment].key != 0 ) {
	aNetSeg[segment].current = 
		aNetSeg[ aNetSeg[segment].key ].current ;
    }
    if( aNetSeg[segment].current == 0 ) {
	segptr = aNetSeg[segment].top ;
    } else {
	segptr = aNetSeg[segment].bot ;
    }
    pin1 = segptr->pin1 ;
    pin2 = segptr->pin2 ;
    if( pin1 > maxterm && pin2 > maxterm ) {
	continue ;
    }
    ptr1 = segptr->pin1ptr ;
    ptr2 = segptr->pin2ptr ;
    x1 = ptr1->netptr->xpos ;
    x2 = ptr2->netptr->xpos ;
    if( x1 == x2 ) {
	continue ;
    }
    net = aNetSeg[segment].net ;
    if( ptr1->nSegType >= 0 ) {
	Flag = 0 ;
	bptr = ptr1 ;
	while( bptr->nprevgrd != GRDNULL 
		    && bptr->nprevgrd->netptr->xpos == x1 ) {
	    if( net == tearray[bptr->nprevgrd->netptr->terminal]->net 
				&& bptr->nprevgrd->nSegType < 0 ) {
		Flag = 1 ;
		sptr = ptr1->nnextgrd ;
		while( sptr->netptr->xpos == x1 ) {
		    sptr = sptr->nnextgrd ;
		}
		break ;
	    } else {
		bptr = bptr->nprevgrd ;
	    }
	}
	if( !Flag ) {
	    sptr = ptr1->nnextgrd ;
	    while( sptr->netptr->xpos == x1 ) {
		if( net == tearray[sptr->netptr->terminal]->net 
				    && sptr->nSegType < 0 ) {
		    Flag = 1 ;
		}
		sptr = sptr->nnextgrd ;
	    }
	}
	if( !Flag ) {
	    sptr = bptr ;
	}
    } else {
	sptr = ptr1->nnextgrd ;
	while( sptr->netptr->xpos == x1 ) {
	    sptr = sptr->nnextgrd ;
	}
    }

    if( ptr2->nSegType <= 0 ) {
	Flag = 0 ;
	fptr = ptr2 ;
	while( fptr->nnextgrd != GRDNULL 
		    && fptr->nnextgrd->netptr->xpos == x2 ) {
	    if( net == tearray[fptr->nnextgrd->netptr->terminal]->net
				&& fptr->nnextgrd->nSegType > 0 ) {
		Flag = 1 ;
		eptr = ptr2->nprevgrd ;
		while( eptr->netptr->xpos == x2 ) {
		    eptr = eptr->nprevgrd ;
		}
		break ;
	    } else {
		fptr = fptr->nnextgrd ;
	    }
	}
	if( !Flag ) {
	    eptr = ptr2->nprevgrd ;
	    while( eptr->netptr->xpos == x2 ) {
		if( net == tearray[eptr->netptr->terminal]->net 
				    && eptr->nSegType > 0 ) {
		    Flag = 1 ;
		}
		eptr = eptr->nprevgrd ;
	    }
	}
	if( !Flag ) {
	    eptr = fptr ;
	}
    } else {
	eptr = ptr2->nprevgrd ;
	while( eptr->netptr->xpos == x2 ) {
	    eptr = eptr->nprevgrd ;
	}
    }

    eptr = eptr->nnextgrd ;

    for( ptr = sptr ; ptr != eptr ; ptr = ptr->nnextgrd ) {
	(ptr->ntracks)++ ;
    }
    if( pin1 <= maxterm ) {
	ptr1->nSegType += RIGHT ;
    }
    if( pin2 <= maxterm ) {
	ptr2->nSegType += LEFT ;
    }
}
if( uneven_cell_height ) {
    reset_ntrack( ) ;
}

for( chan = 1 ; chan <= numChans ; chan++ ) {
    for( gdptr = Begin[ chan ] ; gdptr != GRDNULL ;
					gdptr = gdptr->nnextgrd ) {
	if( gdptr->tracks != gdptr->ntracks ) {
	    debug( chan , gdptr ) ;
	    return ;
	}
    }
}
}

debug( chan , gdptr )
int chan ;
CHANGRDPTR gdptr ;
{
FILE *fpb ;
char filename[64] ;
NBOXPTR netptr ;
int i ;


sprintf( filename , "%s.debug" , cktName ) ;
fpb = twopen ( filename , "w", ABORT) ;

fprintf(fpb ," channel = %2d nmaxTrack = %2d maxTrack = %2d\n"
		    , chan , nmaxTrack[chan] , maxTrack[chan]) ;
fprintf(fpb,"SegType nSegType track ntrack  pin xpos newx cell  net\n");
for( i = 5 ; i >= 0 ; i-- ) {
    if( gdptr->prevgrd != GRDNULL ) {
	gdptr = gdptr->prevgrd ;
    }
}
for( ; i <= 12 ; i++ ) {
    if( gdptr != GRDNULL ) {
	netptr = gdptr->netptr ;
	fprintf(fpb ,"%7d %8d %5d %6d %4d %4d %4d %4d %4d\n", 
	gdptr->SegType , gdptr->nSegType , gdptr->tracks , 
	gdptr->ntracks , netptr->terminal , netptr->xpos ,
	netptr->newx , netptr->cell , tearray[netptr->terminal]->net );
	gdptr = gdptr->nextgrd ;
    }
}
}

reset_ntrack()
{

CBOXPTR cellptr ;
TIBOXPTR tileptr ;
TEBOXPTR termptr ;
int cell , pin , pinloc , row , top , bottom ;

for( cell = 1 ; cell <= numcells ; cell++ ) {
    cellptr = carray[cell] ;
    tileptr = cellptr->tileptr ;
    top =  tileptr->top ;
    bottom = -tileptr->bottom ;
    row = cellptr->cblock ;
    for( termptr = tileptr->termsptr ;
	termptr != NULL ; termptr = termptr->nextterm ) {

	pin = termptr->cellterm ;
	pinloc = tearray[pin]->pinloc ;
	if( pinloc == 1 ) {
	    Tgrid[ pin ]->up->ntracks += ( top +
	    facing_cellheight( pin , row , 1 , NEW ) ) / track_spacing ;
	} else if( pinloc == -1 ) {
	    Tgrid[ pin ]->up->ntracks += ( bottom +
	    facing_cellheight( pin , row , -1 , NEW ) ) / track_spacing;
	} else {  /* pinloc == 0 */
	    Tgrid[ pin ]->up->ntracks += ( top +
	    facing_cellheight( pin , row , 1 , NEW ) ) / track_spacing ;
	    Tgrid[ pin ]->down->ntracks += ( bottom +
	    facing_cellheight( pin , row , -1 , NEW ) ) / track_spacing;
	}
    }
}
for( ; cell <= numcells + numterms ; cell++ ) {
    cellptr = carray[cell] ;
    tileptr = cellptr->tileptr ;
    for( termptr = tileptr->termsptr ; termptr != NULL ;
			    termptr = termptr->nextterm ) {
	pin = termptr->cellterm ;
	row = tearray[pin]->row ;
	Tgrid[ pin ]->up->ntracks += facing_cellheight(
		pin , row , 0 , NEW ) / track_spacing ;
    }
}
}
