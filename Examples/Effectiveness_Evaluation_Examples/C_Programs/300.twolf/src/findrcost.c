#include "standard.h"
#include "groute.h"

findrcost()
{

SEGBOXPTR segptr ;
CHANGRDPTR ptr1 , ptr2 , bptr , fptr , sptr , eptr , ptr , gdptr ;
DENSITYPTR denptr ;
int chan , segment ;
int track , max_trk ;
int pin1 , pin2 , x1 , x2 ;
int net , Flag ;

for( segment = 1 ; segment <= numSegs ; segment++ ) {
    if( aNetSeg[segment].current == 0 ) {
	segptr = aNetSeg[segment].top ;
    } else {
	segptr = aNetSeg[segment].bot ;
    }
    pin1 = segptr->pin1 ;
    pin2 = segptr->pin2 ;
    ptr1 = segptr->pin1ptr ;
    ptr2 = segptr->pin2ptr ;
    x1 = ptr1->netptr->xpos ;
    x2 = ptr2->netptr->xpos ;
    if( x1 == x2 ) {
	continue ;
    }
    net = aNetSeg[segment].net ;
    if( ptr1->SegType >= 0 ) {  /* no segment ended here */
	Flag = 0 ;
	bptr = ptr1 ;
	while( bptr->prevgrd != GRDNULL 
		    && bptr->prevgrd->netptr->xpos == x1 ) {
	    if( net == tearray[bptr->prevgrd->netptr->terminal]->net 
				&& bptr->prevgrd->SegType < 0 ) {
		Flag = 1 ;
		sptr = ptr1->nextgrd ;
		while( sptr->netptr->xpos == x1 ) {
		    sptr = sptr->nextgrd ;
		}
		break ;
	    } else {
		bptr = bptr->prevgrd ;
	    }
	}
	if( !Flag ) {
	    sptr = ptr1->nextgrd ;
	    while( sptr->netptr->xpos == x1 ) {
		if( net == tearray[sptr->netptr->terminal]->net 
				    && sptr->SegType < 0 ) {
		    Flag = 1 ;
		}
		sptr = sptr->nextgrd ;
	    }
	}
	if( !Flag ) {
	    sptr = bptr ;
	}
    } else {
	sptr = ptr1->nextgrd ;
	while( sptr->netptr->xpos == x1 ) {
	    sptr = sptr->nextgrd ;
	}
    }

    if( ptr2->SegType <= 0 ) {  /* no segment start here */
	Flag = 0 ;
	fptr = ptr2 ;
	while( fptr->nextgrd != GRDNULL 
		    && fptr->nextgrd->netptr->xpos == x2 ) {
	    if( net == tearray[fptr->nextgrd->netptr->terminal]->net
				&& fptr->nextgrd->SegType > 0 ) {
		Flag = 1 ;
		eptr = ptr2->prevgrd ;
		while( eptr->netptr->xpos == x2 ) {
		    eptr = eptr->prevgrd ;
		}
		break ;
	    } else {
		fptr = fptr->nextgrd ;
	    }
	}
	if( !Flag ) {
	    eptr = ptr2->prevgrd ;
	    while( eptr->netptr->xpos == x2 ) {
		if( net == tearray[eptr->netptr->terminal]->net 
				    && eptr->SegType > 0 ) {
		    Flag = 1 ;
		}
		eptr = eptr->prevgrd ;
	    }
	}
	if( !Flag ) {
	    eptr = fptr ;
	}
    } else {
	eptr = ptr2->prevgrd ;
	while( eptr->netptr->xpos == x2 ) {
	    eptr = eptr->prevgrd ;
	}
    }

    eptr = eptr->nextgrd ;

    for( ptr = sptr ; ptr != eptr ; ptr = ptr->nextgrd ) {
	(ptr->tracks)++ ;
    }
    if( pin1 <= maxterm ) {
	ptr1->SegType += RIGHT ;
    }
    if( pin2 <= maxterm ) {
	ptr2->SegType += LEFT ;
    }
}

DboxHead  = ( DENSITYPTR ** )safe_calloc( sizeof( DENSITYPTR * ) 
						, numChans + 1 ) ;
Densebox  = ( DENSITYPTR ** )safe_calloc( sizeof( DENSITYPTR * )
						, numChans + 1 ) ;
maxTrack  = (int *)safe_malloc( ( numChans + 1 ) * sizeof( int ) ) ;
nmaxTrack = (int *)safe_malloc( ( numChans + 1 ) * sizeof( int ) ) ;
max_tdensity = 0 ;
tracks   = 0 ;
if( uneven_cell_height ) {
    set_cedgebin( ) ;
    reset_track( ) ;
}
for( chan = 1 ; chan <= numChans ; chan++ ) {
    max_trk = 0 ;
    for( gdptr = Begin[ chan ] ; gdptr != GRDNULL ;
					gdptr = gdptr->nextgrd ) {
	if( gdptr->tracks > max_trk ) {
	    max_trk = gdptr->tracks ;
	}
    }
    maxTrack[ chan ]   = max_trk ;
    if( max_trk > max_tdensity ) {
	max_tdensity = max_trk ;
    }
    tracks += max_trk ;
}
for( chan = 1 ; chan <= numChans ; chan++ ) {
    DboxHead[ chan ]  = ( DENSITYPTR *)safe_calloc(
		sizeof( DENSITYPTR) , max_tdensity + 101 ) ;
    Densebox[ chan ]  = ( DENSITYPTR * )safe_calloc( 
		sizeof( DENSITYPTR) , max_tdensity + 101 ) ;
    for( track = 0 ; track <= max_tdensity + 100 ; track++ ) {
	DboxHead[ chan ][ track ] = ( DENSITYPTR )safe_calloc(
				    sizeof( DENSITYBOX ) , 1 ) ;
    }
    for( gdptr = Begin[ chan ] ; gdptr != GRDNULL ;
					gdptr = gdptr->nextgrd ) {
	track = gdptr->tracks ;
	if( DboxHead[ chan ][ track ]->next == NULL ) {
	    DboxHead[ chan ][ track ]->next = Densebox[ chan ][ track ]
	        = ( DENSITYPTR )safe_calloc( sizeof( DENSITYBOX ) , 1 );
	    Densebox[ chan ][ track ]->back = DboxHead[ chan ][ track ];
	    Densebox[ chan ][ track ]->grdptr = gdptr ;
	    gdptr->dptr = Densebox[ chan ][ track ] ;
	} else {
	    denptr = Densebox[ chan ][ track ]->next =  
		( DENSITYPTR )safe_calloc( sizeof( DENSITYBOX ) , 1 );
	    denptr->back = Densebox[ chan ][ track ] ;
	    denptr->grdptr = gdptr ;
	    gdptr->dptr = denptr ;
	    Densebox[ chan ][ track ] = denptr ;
	}
    }
}
}


/* the set_cedgebin() , reset_track , facing_cellheight() function
    would be used only when the cells are in uneven height */

set_cedgebin()
{

CBOXPTR cellptr ;
int channel , row , bin , bin_rite_edge , cleft , crite ;
int most_left , most_rite , rite , i ;

cedgebin = (int **)safe_malloc( ( numChans + 1 ) * sizeof(int *) ) ;
cedge_binwidth = (int)( 2.0 * mean_width ) ;
cellptr = carray[ pairArray[1][ pairArray[1][0] ] ] ;
most_rite = cellptr->cxcenter + cellptr->tileptr->right ;
for( row = 2 ; row <= numRows ; row++ ) {
    cellptr = carray[ pairArray[row][ pairArray[row][0] ] ] ;
    rite = cellptr->cxcenter + cellptr->tileptr->right ;
    if( rite > most_rite ) {
	most_rite = rite ;
    }
}
num_edgebin = ( most_rite - blkleft ) / cedge_binwidth + 1 ;
for( channel = 1 ; channel <= numChans ; channel++ ) {
    cedgebin[ channel ] = (int *)safe_malloc(
		( num_edgebin + 1 ) * sizeof( int ) ) ;
}


for( row = 1 ; row <= numRows ; row++ ) {
    cellptr = carray[ pairArray[row][1] ] ;
    most_left = cellptr->cxcenter + cellptr->tileptr->left ;
    bin_rite_edge = most_left + cedge_binwidth ;
    cedgebin[row][1] = 1 ;
    bin = 1 ;
    for( i = 1 ; i <= pairArray[row][0] ; i++ ) {
	cellptr = carray[ pairArray[row][i] ] ; 
	crite = cellptr->cxcenter + cellptr->tileptr->right ;
	if( bin_rite_edge < crite ) {
	    while( bin_rite_edge <= crite ) {
		cedgebin[row][++bin] = i ;
		bin_rite_edge += cedge_binwidth ;
	    }
	}
    }
    for( ++bin ; bin <= num_edgebin ; bin++ ) {
	cedgebin[row][bin] = 0 ;
    }
}
}


reset_track()
{

CBOXPTR cellptr ;
TIBOXPTR tileptr ;
TEBOXPTR termptr ;
int cell , pin , pinloc , row , top , bottom ;

for( cell = 1 ; cell <= numcells ; cell++ ) {
    cellptr = carray[cell] ;
    tileptr = cellptr->tileptr ;
    row =  cellptr->cblock ;
    top =  tileptr->top ;
    bottom = -tileptr->bottom ;
    for( termptr = tileptr->termsptr ;
	termptr != TERMNULL ; termptr = termptr->nextterm ) {

	pin = termptr->cellterm ;
	pinloc = tearray[pin]->pinloc ;
	if( pinloc == 1 ) {
	    Tgrid[ pin ]->up->tracks += ( top +
	    facing_cellheight( pin , row , 1 , NEW ) ) / track_spacing ;
	} else if( pinloc == -1 ) {
	    Tgrid[ pin ]->up->tracks += ( bottom +
	    facing_cellheight( pin , row , -1 , NEW ) ) / track_spacing;
	} else {  /* pinloc == 0 */
	    Tgrid[ pin ]->up->tracks += ( top +
	    facing_cellheight( pin , row , 1 , NEW ) ) / track_spacing ;
	    Tgrid[ pin ]->down->tracks += ( bottom +
	    facing_cellheight( pin , row , -1 , NEW ) ) / track_spacing;
	}
    }
}
for( ; cell <= numcells + numterms ; cell++ ) {
    cellptr = carray[cell] ;
    tileptr = cellptr->tileptr ;
    for( termptr = tileptr->termsptr ; termptr != TERMNULL ;
			    termptr = termptr->nextterm ) {
	pin = termptr->cellterm ;
	row = tearray[ pin ]->row ;
	Tgrid[ pin ]->up->tracks += facing_cellheight(
		pin , row , 0 , NEW ) / track_spacing ;
    }
}
}


facing_cellheight( pin , row , pinloc , status )
int pin, row , pinloc , status ;
{

CBOXPTR cellptr ;
int bin , i , *Aray , most_left , most_rite ;
int nrow , pin_x , crite ;

if( 1 <= row  && row <= numRows ) {
    nrow = row + pinloc ;
    if( nrow == 0 || nrow == numChans || pinloc == 0 ) {
	return(0) ;
    }
} else if( row == 0 ) {
    nrow = 1 ;
} else {
    nrow = numRows ;
}

Aray  = pairArray[nrow] ;
if( status == OLD ) {
    pin_x = tearray[pin]->newx ;
} else {
    pin_x = tearray[pin]->xpos ;
}
cellptr   = carray[ Aray[1] ] ;
most_left = cellptr->cxcenter + cellptr->tileptr->left ;
cellptr   = carray[ Aray[Aray[0]] ] ;
most_rite = cellptr->cxcenter + cellptr->tileptr->right ;
if( pin_x < most_left || pin_x > most_rite ) {
    return( 0 ) ;
}
bin = ( pin_x - most_left ) / cedge_binwidth + 1 ;
if( ( i = cedgebin[nrow][bin] ) == 0 ) {
    return( 0 ) ;
}
cellptr =  carray[ Aray[i] ] ;
if( ( ( cellptr->tileptr->left + cellptr->cxcenter ) == pin_x )
					    && ( bin >= 2 ) ) {
    if( carray[ Aray[i-1] ]->cheight > cellptr->cheight ) {
	cellptr = carray[ Aray[--i] ] ;
    }
} else {
    crite = cellptr->tileptr->right + cellptr->cxcenter ;
    while(  crite < pin_x && i < Aray[0] ) {
	cellptr = carray[ Aray[++i] ] ;
	crite += cellptr->clength ;
    }
    if( crite == pin_x && i != Aray[0] ) {
	if( carray[ Aray[i+1] ]->cheight > cellptr->cheight ) {
	    cellptr = carray[ Aray[i+1] ] ;
	}
    }
}

if( 1 <= row  && row <= numRows ) {
    if( pinloc == 1 ) {
	return( -cellptr->tileptr->bottom ) ;
    } else {
	return( cellptr->tileptr->top ) ;
    }
} else if( row == 0 ) {
    return( -cellptr->tileptr->bottom ) ;
} else {
    return( cellptr->tileptr->top ) ;
}
}
