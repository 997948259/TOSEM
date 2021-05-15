#include "standard.h"
#include "groute.h"

changrid( )
{

CHANGRDPTR **gdptr , grdptr , cgdptr , ngdptr ;
NBOXPTR netptr ;
int row , net , channel , terminal ;
int *numPins , *PinInChan ;
int count , i ;


numPins   = (int *)safe_calloc( sizeof( int ) , numChans+1 ) ;
PinInChan = (int *)safe_calloc( sizeof( int ) , numChans+1 ) ;
for( net = 1 ; net <= numnets ; net++ ) {
    for( netptr = netarray[net]->netptr ; netptr != NETNULL ;
					netptr = netptr->nterm ) {
	if( (int) netptr->pinloc == -1 ) {
	    numPins[ netptr->row ]++ ;
	} else if( netptr->pinloc == 1 ) {
	    numPins[ netptr->row + 1 ]++ ;
	} else {  /* pinloc == 0  pin on pads or macros */
	    if( netptr->row > 0 ) {
		numPins[ netptr->row ]++ ;
	    }
	    if( netptr->row < numChans ) {
		numPins[ netptr->row + 1 ]++ ;
	    }
	}
    }
}

gdptr = (CHANGRDPTR **)safe_malloc( (numChans+1) *
				sizeof( CHANGRDPTR *) ) ;
for( channel = 1 ; channel <= numChans ; channel++ ) {
    gdptr[channel] = ( CHANGRDPTR * )safe_malloc(
	( numPins[channel] + 1 ) * sizeof( CHANGRDPTR ) ) ;
}

Tgrid = ( TGRIDPTR * )safe_malloc( ( maxterm + 2*numChans + 1 )
					* sizeof( TGRIDPTR ) ) ;
for( terminal = 1 ; terminal <= maxterm + 2*numChans ; terminal++ ) {
    Tgrid[ terminal ] = ( TGRIDPTR )safe_malloc( sizeof(TGRIDBOX) ) ;
}
for( net = 1 ; net <= numnets ; net++ ) {
    for( netptr = netarray[net]->netptr ; netptr != NETNULL ;
					netptr = netptr->nterm ) {
	row = netptr->row ;
	terminal = netptr->terminal ;
	grdptr = ( CHANGRDPTR )safe_malloc( sizeof( CHANGRDBOX ) ) ;
	if( (int) netptr->pinloc == -1 ) {
	    channel = row ;
	    count = ++(PinInChan[ channel ]) ;
	    gdptr[ channel ][ count ] = grdptr ;
	    Tgrid[ terminal ]->up = grdptr ;
	    Tgrid[ terminal ]->down = grdptr ;
	    grdptr->netptr  = tearray[ terminal ] ;
	    grdptr->tracks  = 0 ;
	    grdptr->SegType = 0 ;
	} else if( netptr->pinloc == 1 ) {
	    channel = row + 1 ;
	    count = ++(PinInChan[ channel ]) ;
	    gdptr[ channel ][ count ] = grdptr ;
	    Tgrid[ terminal ]->up = grdptr ;
	    Tgrid[ terminal ]->down = grdptr ;
	    grdptr->netptr  = tearray[ terminal ] ;
	    grdptr->tracks  = 0 ;
	    grdptr->SegType = 0 ;
	} else {  /* pinloc == 0  pin on pads or macros */
	    if( 1 <= row && row <= numChans - 1 ) {
		channel = row ;
		count = ++(PinInChan[ channel ]) ;
		gdptr[ channel ][ count ] = grdptr ;
		Tgrid[ terminal ]->down   = grdptr ;
		grdptr->netptr  = tearray[ terminal ] ;
		grdptr->tracks  = 0 ;
		grdptr->SegType = 0 ;

		channel = row + 1 ;
		count = ++(PinInChan[ channel ]) ;
		grdptr = gdptr[ channel ][ count ] =
		 ( CHANGRDPTR )safe_malloc( sizeof( CHANGRDBOX ) ) ;
		Tgrid[ terminal ]->up = grdptr ;
		grdptr->netptr  = tearray[ terminal ] ;
		grdptr->tracks  = 0 ;
		grdptr->SegType = 0 ;
	    } else if( row == 0 ) {
		count = ++(PinInChan[ 1 ]) ;
		gdptr[ 1 ][ count ] = grdptr ;
		Tgrid[ terminal ]->up   = grdptr ;
		Tgrid[ terminal ]->down = grdptr ;
		grdptr->netptr  = tearray[ terminal ] ;
		grdptr->tracks  = 0 ;
		grdptr->SegType = 0 ;
	    } else {            /* row == numChans */
		count = ++(PinInChan[ numChans ]) ;
		gdptr[ numChans ][ count ] = grdptr ;
		Tgrid[ terminal ]->up   = grdptr ;
		Tgrid[ terminal ]->down = grdptr ;
		grdptr->netptr  = tearray[ terminal ] ;
		grdptr->tracks  = 0 ;
		grdptr->SegType = 0 ;
	    }
	}
    }
}

for( channel = 1 ; channel <= numChans ; channel++ ) {
    qsortgdx( (char *) ( gdptr[channel] + 1 ) , numPins[channel] ,
					    sizeof( CHANGRDPTR ) ) ;
}

Begin = ( CHANGRDPTR * )safe_malloc( (numChans+1)
				* sizeof( CHANGRDPTR ) ) ;
End   = ( CHANGRDPTR * )safe_malloc( (numChans+1) 
				* sizeof( CHANGRDPTR ) ) ;
for( channel = 1 ; channel <= numChans ; channel++ ) {
    Begin[channel] = ( CHANGRDPTR )safe_calloc( sizeof(CHANGRDBOX) ,1 );
    Begin[channel]->netptr = ( NBOXPTR )safe_calloc( sizeof(NBOX) , 1);
    Begin[channel]->netptr->xpos = gxstart - 1 ;
    Begin[channel]->netptr->terminal = maxterm + channel ;
    Begin[channel]->netptr->row = channel ;
    Begin[channel]->netptr->pinloc = -1 ;
    tearray[maxterm + channel] = Begin[channel]->netptr ;

    End[channel] = ( CHANGRDPTR )safe_calloc( sizeof(CHANGRDBOX) , 1 ) ;
    End[channel]->netptr = ( NBOXPTR )safe_calloc( sizeof(NBOX) , 1);
    End[channel]->netptr->xpos = gxstop + 1 ;
    End[channel]->netptr->terminal = maxterm + numChans + channel ;
    End[channel]->netptr->row = channel ;
    End[channel]->netptr->pinloc = -1 ;
    tearray[maxterm + numChans + channel] = End[channel]->netptr ;
}
for( channel = 1 ; channel <= numChans ; channel++ ) {
    Tgrid[ maxterm + channel ]->up   = Begin[ channel ] ;
    Tgrid[ maxterm + channel ]->down = Begin[ channel ] ;
    Tgrid[ maxterm + numChans + channel ]->up   = End[ channel ] ;
    Tgrid[ maxterm + numChans + channel ]->down = End[ channel ] ;
}

for( channel = 1 ; channel <= numChans ; channel++ ) {
    if( numPins[channel] == 0 ) {
	Begin[channel]->nextgrd = NULL ;
	End[channel]->prevgrd   = NULL ;
    } else if( numPins[channel] == 1 ) {
	Begin[channel]->nextgrd = gdptr[channel][1] ;
	gdptr[channel][1]->prevgrd  = Begin[channel] ;
	End[channel]->prevgrd   = gdptr[channel][1] ;
	gdptr[channel][1]->nextgrd  = End[channel] ;
    } else {
	Begin[channel]->nextgrd     = gdptr[channel][1] ;
	gdptr[channel][1]->prevgrd  = Begin[channel] ;
	for( i = 1 ; i <= numPins[channel]-1 ; i++ ) {
	    cgdptr = gdptr[channel][i]   ;
	    ngdptr = gdptr[channel][i+1] ;
	    cgdptr->nextgrd   = ngdptr ;
	    ngdptr->prevgrd   = cgdptr ;
	}
	ngdptr->nextgrd  = End[channel] ;
	End[channel]->prevgrd  = ngdptr ;
    }
}
for( channel = 1 ; channel <= numChans ; channel++ ) {
    safe_free( gdptr[ channel ] ) ;
}
safe_free( gdptr ) ;

safe_cfree( numPins ) ;
safe_cfree( PinInChan ) ;
}
