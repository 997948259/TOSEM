#include "standard.h"
#include "groute.h"
static int na_i , nb_i , start_i , end_i ;
static int startcbin , endcbin , rowleft ;
static int leftx , ritex ;
static int old_axcenter , old_bxcenter ;
static CBOXPTR acellptr , bcellptr ;

ucgxp( a , b , anxcenter , bnxcenter )
int a , b , anxcenter , bnxcenter ;
{

CBOXPTR cellptr ;
NBOXPTR tmptr ;
TIBOXPTR atileptr , btileptr ;
TEBOXPTR termptr , atermptr , btermptr ;
SEGBOXPTR segptr ;
DENSITYPTR denptr ;
CHANGRDPTR gdptr , endgrd ;

int oldtracks , track , x , row  ;
int aorient , borient , bin , bin_rite_edge , crite ;
int i , bb , e , seg , chan , net ;
int UpperLeft , UpperRight , LowerLeft , LowerRight ;
int ULpin , URpin , LLpin , LRpin ;
int topchan , botchan ;

acellptr = carray[ a ]    ; 
aorient  = acellptr->corient / 2 ; 
atileptr = acellptr->tileptr ;
atermptr = atileptr->termsptr ; 

bcellptr = carray[ b ]    ; 
borient  = bcellptr->corient / 2 ; 
btileptr = bcellptr->tileptr ;
btermptr = btileptr->termsptr ; 

UpperLeft  = LowerLeft  = gxstop ;
UpperRight = LowerRight = gxstart ;
ULpin = URpin = LLpin = LRpin = 0 ;
    
netchgs[0] = 0 ;
for( termptr = atermptr ; termptr != TERMNULL ; termptr = 
					termptr->nextterm ){
    x = termptr->txpos[ aorient ] + anxcenter ; 

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
    } else { 
	/* pinloc == -1 , pin is on the bottom side of the cell */
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
    for( i = 1 ; i <= netchgs[0] ; i++ ) {
	if( tmptr->net == netchgs[i] ) {
	    break ;
	}
    }
    if( i > netchgs[0] ) {
	netchgs[ ++netchgs[0] ] = tmptr->net ;
    }
} 
for( termptr = btermptr ; termptr != TERMNULL ; termptr = 
				    termptr->nextterm ) {
    x = termptr->txpos[ borient ] + bnxcenter ; 

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
    } else { 
	/* pinloc == -1 , pin is on the bottom side of the cell */
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

if( anxcenter < bnxcenter ) { /* originally b is to the left of a */
    leftx = anxcenter + atileptr->left ;
    ritex = bnxcenter + btileptr->right ;
} else {
    leftx = bnxcenter + btileptr->left ;
    ritex = anxcenter + atileptr->right ;
}

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
    sub_reset2( a , b , anxcenter , bnxcenter ) ;
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

if( tracks <= oldtracks ) {

    if( !uneven_cell_height ) {
	acellptr->cxcenter = anxcenter ;
	bcellptr->cxcenter = bnxcenter ;
    }
    for( termptr = atermptr ; termptr != TERMNULL ; termptr = 
					    termptr->nextterm ) {
	tmptr = tearray[termptr->cellterm] ;
	tmptr->newx = tmptr->xpos ;
    } 
    for( termptr = btermptr ; termptr != TERMNULL ; termptr = 
					    termptr->nextterm ) {
	tmptr = tearray[termptr->cellterm] ;
	tmptr->newx = tmptr->xpos ;
    }
    for( i = 1 ; i <= netchgs[0] ; i++ ) {
	net = netchgs[i] ;
	bb = anet[net] ;
	e = anet[net + 1] - 1 ;
	for( seg = bb ; seg <= e ; seg++ ) {
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
    return( 1 ) ;
} else {
    if( uneven_cell_height ) {
	acellptr->cxcenter = old_axcenter ;
	bcellptr->cxcenter = old_bxcenter ;
    }
    for( termptr = atermptr ; termptr != TERMNULL ; termptr = 
					    termptr->nextterm ) {
	tmptr = tearray[termptr->cellterm] ;
	tmptr->xpos = tmptr->newx ;
    } 
    for( termptr = btermptr ; termptr != TERMNULL ; termptr = 
					    termptr->nextterm ) {
	tmptr = tearray[termptr->cellterm] ;
	tmptr->xpos = tmptr->newx ;
    }
    for( i = 1 ; i <= netchgs[0] ; i++ ) {
	net = netchgs[i] ;
	bb = anet[net] ;
	e = anet[net + 1] - 1 ;
	for( seg = bb ; seg <= e ; seg++ ) {
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
    if( uneven_cell_height ) {
	row = carray[a]->cblock ;
	pairArray[row][nb_i] = a ;
	pairArray[row][na_i] = b ;
	bin = startcbin ;
	bin_rite_edge = rowleft + --bin * cedge_binwidth ;
	for( i = start_i ; i <= end_i ; i++ ) {
	    cellptr = carray[ pairArray[row][i] ] ;
	    crite = cellptr->cxcenter + cellptr->tileptr->right ;
	    while( bin_rite_edge < crite ) {
		cedgebin[ row ][ ++bin ] = i ;
		bin_rite_edge += cedge_binwidth ;
	    }
	}
    }
    return( 0 ) ;
}
}


sub_reset2( a , b , anxcenter , bnxcenter )
int a , b , anxcenter , bnxcenter ;
{

int row , bin , track , *Aray , i , cell ;
int bin_rite_edge , crite , pinloc , self_reset ;
NBOXPTR netptr ;
CBOXPTR cellptr ;
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
old_axcenter = acellptr->cxcenter ;
old_bxcenter = bcellptr->cxcenter ;
acellptr->cxcenter = anxcenter ;
bcellptr->cxcenter = bnxcenter ;
Aray  = pairArray[row] ;
rowleft  = carray[Aray[1]]->cxcenter + carray[Aray[1]]->tileptr->left ;
startcbin = ( leftx - rowleft ) / cedge_binwidth + 1 ;
endcbin   = ( ritex - rowleft ) / cedge_binwidth + 1 ;
start_i = cedgebin[row][startcbin] ;
end_i = cedgebin[row][endcbin]   ;
bin = startcbin ;
i = start_i ;
for( cell = Aray[ i ] ; cell != a ; cell = Aray[ ++i ] ) ;
if( anxcenter < bnxcenter ) {
    na_i = i - 1 ;
    nb_i = i ;
} else {
    na_i = i + 1 ;
    nb_i = i ;
}
Aray[na_i] = a ;
Aray[nb_i] = b ;
bin_rite_edge = rowleft + --bin * cedge_binwidth ;
for( i = start_i ; i <= end_i ; i++ ) {
    cellptr = carray[ Aray[i] ] ;
    crite = cellptr->cxcenter + cellptr->tileptr->right ;
    while( bin_rite_edge < crite ) {
	cedgebin[ row ][ ++bin ] = i ;
	bin_rite_edge += cedge_binwidth ;
    }
}
}
