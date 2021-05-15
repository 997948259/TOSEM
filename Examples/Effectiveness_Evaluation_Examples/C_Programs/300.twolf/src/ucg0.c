#include "standard.h"
#include "groute.h"

ucg0( a , newaor )
int a , newaor ;
{

CBOXPTR acellptr ;
NBOXPTR tmptr ;
TIBOXPTR antilptr ;
TEBOXPTR termptr , antrmptr ;
SEGBOXPTR segptr ;
DENSITYPTR denptr ;
CHANGRDPTR gdptr , endgrd ;

int x , y , oldtracks , track ;
int axcenter , aycenter ;
int i , b , e , seg , chan , net ;
int UpperLeft , UpperRight , LowerLeft , LowerRight ;
int ULpin , URpin , LLpin , LRpin ;
int leftx , ritex , topchan , botchan ;

acellptr = carray[ a ]    ;
axcenter = acellptr->cxcenter ;
aycenter = acellptr->cycenter ;

antilptr = acellptr->tileptr ;
antrmptr = antilptr->termsptr ;

UpperLeft  = LowerLeft  = gxstop ;
UpperRight = LowerRight = gxstart ;
ULpin = URpin = LLpin = LRpin = 0 ;
netchgs[0] = 0 ;
for( termptr = antrmptr ; termptr != TERMNULL ; termptr =
					    termptr->nextterm ) {
    x = termptr->txpos[ newaor / 2 ] + axcenter ;
    y = termptr->typos[ newaor % 2 ] + aycenter ;

    tmptr = tearray[termptr->cellterm] ;
    if( tmptr->pinloc == 1 ) {
	if( tmptr->newx < UpperLeft ) {
	    UpperLeft = tmptr->newx ;
	    ULpin = termptr->cellterm ;
	}
	if( tmptr->newx > UpperRight ) {
	    UpperRight = tmptr->newx ;
	    URpin = termptr->cellterm ;
	}
    } else { /* pinloc == -1 , pin is on the bottom side of the cell */
	if( tmptr->newx < LowerLeft ) {
	    LowerLeft = tmptr->newx ;
	    LLpin = termptr->cellterm ;
	}
	if( tmptr->newx > LowerRight ) {
	    LowerRight = tmptr->newx ;
	    LRpin = termptr->cellterm ;
	}
    }
    tmptr->xpos = x ;
    tmptr->ypos = y ;
    for( i = 1 ; i <= netchgs[0] ; i++ ) {
	if( tmptr->net == netchgs[i] ) {
	    break ;
	}
    }
    if( i > netchgs[0] ) {
	netchgs[ ++netchgs[0] ] = tmptr->net ;
    }
}
if( netchgs[0] == 0 ) {
    return(0) ;
}

leftx = axcenter + antilptr->left ;
ritex = axcenter + antilptr->right ;

if( ULpin != 0 ) {
    ULgrdptr = Tgrid[ ULpin ]->up->prevgrd ;
    while( ULgrdptr->netptr->newx >= leftx ) {
	ULgrdptr = ULgrdptr->prevgrd ;
    }
    URgrdptr = Tgrid[ URpin ]->up->nextgrd ;
    while( URgrdptr->netptr->newx <= ritex ) {
	URgrdptr = URgrdptr->nextgrd ;
    }
} else {
    ULgrdptr = GRDNULL ;
}

if( LLpin != 0 ) {
    LLgrdptr = Tgrid[ LLpin ]->down->prevgrd ;
    while( LLgrdptr->netptr->newx >= leftx ) {
	LLgrdptr = LLgrdptr->prevgrd ;
    }
    LRgrdptr = Tgrid[ LRpin ]->down->nextgrd ;
    while( LRgrdptr->netptr->newx <= ritex ) {
	LRgrdptr = LRgrdptr->nextgrd ;
    }
} else {
    LLgrdptr = GRDNULL ;
}

Left_bound = leftx - ( ritex - leftx ) ;
Rite_bound = ritex + ( ritex - leftx ) ;
if( uneven_cell_height ) {
    sub_reset1( a ) ;
}

oldtracks = tracks ;
uglobe() ;
topchan = gtopChan + 1 ; 
botchan = gbotChan - 1 ;
if( topchan > numChans ) {
    topchan = numChans ;
}
if( botchan < 1 ) {
    botchan = 1 ;
}

if( tracks < oldtracks ) {
    for( i = 1 ; i <= netchgs[0] ; i++ ) {
	net = netchgs[i] ;
	b = anet[net] ;
	e = anet[net + 1] - 1 ;
	for( seg = b ; seg <= e ; seg++ ) {
	    aNetSeg[seg].current = aNetSeg[seg].ncurrent ;
	    aNetSeg[seg].swYorN  = aNetSeg[seg].nswYorN ;
	    aNetSeg[seg].key     = aNetSeg[seg].nkey ;
	    aNetSeg[seg].nflag   = 0 ;
	    segptr               = aNetSeg[seg].top ;
	    aNetSeg[seg].top     = aNetSeg[seg].ntop ;
	    aNetSeg[seg].ntop    = segptr ;
	    segptr               = aNetSeg[seg].bot ;
	    aNetSeg[seg].bot     = aNetSeg[seg].nbot ;
	    aNetSeg[seg].nbot    = segptr ;
	}
    }
    for( termptr = antrmptr ; termptr != TERMNULL ; termptr =
					    termptr->nextterm ) {
	tmptr = tearray[termptr->cellterm] ;
	tmptr->newx = tmptr->xpos ;
	tmptr->newy = tmptr->ypos ;
    }
    for( seg = 1 ; seg <= numSegs ; seg++ ) {
	fixnetseg[seg] = aNetSeg[seg].current ;
    }
    for( chan = botchan ; chan <= topchan ; chan++ ) {
	for( gdptr = Begin[chan] ; gdptr != GRDNULL ; 
			    gdptr = gdptr->nnextgrd ) {
	    gdptr->tracks  = gdptr->ntracks ;
	    gdptr->SegType = gdptr->nSegType ;
	}
	for( track = 0 ; track <= max_tdensity+30 ; track++ ) {
	    for( denptr = DboxHead[ chan ][ track ] ;
		denptr != DENSENULL ; denptr = denptr->nnext ) {
		denptr->next = denptr->nnext ;
		denptr->back = denptr->nback ;
	    }
	}
	maxTrack[ chan ] = nmaxTrack[ chan ] ;
    }
    if( ULgrdptr != GRDNULL ) {
	endgrd = URgrdptr->nnextgrd ;
	for( gdptr = ULgrdptr ; gdptr != endgrd ;
			      gdptr = gdptr->nnextgrd ) {
	    gdptr->nextgrd = gdptr->nnextgrd ;
	    gdptr->prevgrd = gdptr->nprevgrd ;
	}
    }
    if( LLgrdptr != GRDNULL ) {
	endgrd = LRgrdptr->nnextgrd ;
	for( gdptr = LLgrdptr ; gdptr != endgrd ;
			      gdptr = gdptr->nnextgrd ) {
	    gdptr->nextgrd = gdptr->nnextgrd ;
	    gdptr->prevgrd = gdptr->nprevgrd ;
	}
    }

    acellptr->corient = newaor ;
    return(1);
} else {
    for( termptr = antrmptr ; termptr != TERMNULL ; termptr =
					    termptr->nextterm ) {
	tmptr = tearray[termptr->cellterm] ;
	tmptr->xpos = tmptr->newx ;
	tmptr->ypos = tmptr->newy ;
    }
    for( i = 1 ; i <= netchgs[0] ; i++ ) {
	net = netchgs[i] ;
	b = anet[net] ;
	e = anet[net + 1] - 1 ;
	for( seg = b ; seg <= e ; seg++ ) {
	    aNetSeg[seg].nflag  = 0 ;
	}
    }
    for( seg = 1 ; seg <= numSegs ; seg++ ) {
	aNetSeg[seg].current = fixnetseg[seg] ;
    }
    for( chan = botchan ; chan <= topchan ; chan++ ) {
	for( gdptr = Begin[chan] ; gdptr != GRDNULL ; 
			       gdptr = gdptr->nextgrd ) {
	    gdptr->ntracks  = gdptr->tracks ;
	    gdptr->nSegType = gdptr->SegType ;
	}
	for( track = 0 ; track <= max_tdensity+30 ; track++ ) {
	    for( denptr = DboxHead[ chan ][ track ] ;
		denptr != DENSENULL ; denptr = denptr->next ) {
		denptr->nnext = denptr->next ;
		denptr->nback = denptr->back ;
	    }
	}
	nmaxTrack[ chan ] = maxTrack[ chan ] ;
    }
    if( ULgrdptr != GRDNULL ) {
	endgrd = URgrdptr->nextgrd ;
	for( gdptr = ULgrdptr ; gdptr != endgrd ;
			      gdptr = gdptr->nextgrd ) {
	    gdptr->nnextgrd = gdptr->nextgrd ;
	    gdptr->nprevgrd = gdptr->prevgrd ;
	}
    }
    if( LLgrdptr != GRDNULL ) {
	endgrd = LRgrdptr->nextgrd ;
	for( gdptr = LLgrdptr ; gdptr != endgrd ;
			      gdptr = gdptr->nextgrd ) {
	    gdptr->nnextgrd = gdptr->nextgrd ;
	    gdptr->nprevgrd = gdptr->prevgrd ;
	}
    }

    tracks = oldtracks ;
    return(0);
}
}


sub_reset1( a )
int a ;
{

int row , track , pinloc , self_reset ;
NBOXPTR netptr ;
CHANGRDPTR grdptr ;
DENSITYPTR denptr , headptr ;

row = carray[a]->cblock ;
if( ULgrdptr != GRDNULL ) {
    for( grdptr = ULgrdptr ; grdptr != URgrdptr ;
				grdptr = grdptr->nextgrd ) {
	netptr = grdptr->netptr ;
	pinloc = netptr->pinloc ;
	if( pinloc == 1 ) {
	    self_reset = carray[ netptr->cell ]->tileptr->top ;
	} else if( pinloc == -1 ) {
	    self_reset = -carray[ netptr->cell ]->tileptr->bottom ;
	} else {
	    self_reset = 0 ;
	}
	grdptr->ntracks -= ( self_reset + facing_cellheight( 
		    netptr->terminal , netptr->row , pinloc , 
				    OLD ) ) / track_spacing ;
    }
}
if( LLgrdptr != GRDNULL ) {
    for( grdptr = LLgrdptr ; grdptr != LRgrdptr ;
				grdptr = grdptr->nextgrd ) {
	netptr = grdptr->netptr ;
	pinloc = netptr->pinloc ;
	if( pinloc == 1 ) {
	    self_reset = carray[ netptr->cell ]->tileptr->top ;
	} else if( pinloc == -1 ) {
	    self_reset = -carray[ netptr->cell ]->tileptr->bottom ;
	} else {
	    self_reset = 0 ;
	}
	grdptr->ntracks -= ( self_reset + facing_cellheight( 
		    netptr->terminal , netptr->row , pinloc , 
				    OLD ) ) / track_spacing ;
    }
}
}
