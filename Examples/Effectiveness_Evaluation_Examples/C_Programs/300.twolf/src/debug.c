#include "standard.h"
#include "groute.h"

cellbox_data( first_cell , last_cell )
int first_cell , last_cell ;
{

FILE *fp ;
CBOXPTR ptr ;
int cell ;

fp = twopen( "debug.cellbox" , "a", ABORT ) ;

fprintf(fp," cell xcenter ycenter corient padside left right\n" ) ;
for( cell = first_cell ; cell <= last_cell ; cell++ ) {
    ptr = carray[ cell ] ;
    fprintf( fp , "%5d  %6d  %6d      %2d      %2d %4d  %4d\n" ,
	cell , ptr->cxcenter , ptr->cycenter , ptr->corient ,
	ptr->padside , ptr->tileptr->left , ptr->tileptr->right ) ;
}

twclose( fp ) ;

}


cellterm_data( first_cell , last_cell )
int first_cell , last_cell ;
{

FILE *fp ;
CBOXPTR ptr ;
TEBOXPTR termptr ;
NBOXPTR ttermptr ;
int cell , corient ;

fp = twopen( "debug.cellterm" , "a", ABORT ) ;

for( cell = first_cell ; cell <= last_cell ; cell++ ) {
    fprintf(fp,"\n cell xcenter ycenter corient padside left right\n");
    ptr = carray[ cell ] ;
    corient = ptr->corient ;
    fprintf( fp , "%5d  %6d  %6d      %2d      %2d %4d  %4d\n" ,
	cell , ptr->cxcenter , ptr->cycenter , corient ,
	ptr->padside , ptr->tileptr->left , ptr->tileptr->right ) ;
    fprintf(fp,"   pin  net   tx   ty   xpos   ypos   newx   newy ") ;
    fprintf(fp,"loc ue flag\n" ) ;
    if( cell <= numcells ) {
	for( termptr = ptr->tileptr->termsptr ; termptr != TERMNULL ;
					termptr = termptr->nextterm ) {
	    ttermptr = tearray[termptr->cellterm] ;
	    fprintf(fp," %5d %4d %4d %4d %6d %6d %6d %6d %3d %2d  %2d\n"
		, termptr->cellterm , ttermptr->net , 
		termptr->txpos[ corient/2 ] ,
		termptr->typos[ corient%2 ] , ttermptr->xpos ,
		ttermptr->ypos , ttermptr->newx , ttermptr->newy ,
		ttermptr->pinloc , ttermptr->unequiv , ttermptr->flag );
	}
    } else {
	for( termptr = ptr->tileptr->termsptr ; termptr != TERMNULL ;
					termptr = termptr->nextterm ) {
	    ttermptr = tearray[termptr->cellterm] ;
	    fprintf(fp," %5d %4d %4d %4d %6d %6d %6d %6d %3d %2d  %2d\n"
		, termptr->cellterm , ttermptr->net ,termptr->txpos[ 1 ]
		, termptr->typos[ 1 ] , ttermptr->xpos ,
		ttermptr->ypos , ttermptr->newx , ttermptr->newy ,
		ttermptr->pinloc , ttermptr->unequiv , ttermptr->flag );
	}
    }
}
    
twclose( fp ) ;
}


terminal( first_net , last_net )
int first_net , last_net ;
{

FILE *fp ;
NBOXPTR netptr ;
int net ;

fp = twopen( "debug.terminal" , "a", ABORT ) ;

for( net = first_net ; net <= last_net ; net++ ) {
    fprintf(fp,"net %d\n" , net ) ;
    fprintf(fp," terminal  xpos  ypos  newx  newy  cell loc ue flag extint\n");
    for( netptr = netarray[net]->netptr ; netptr != NETNULL ;
					netptr = netptr->nterm ) {
	fprintf(fp,"    %5d %5d %5d %5d %5d %5d %3d %2d    %1d %6d\n" ,
	    netptr->terminal , netptr->xpos , netptr->ypos ,
	    netptr->newx , netptr->newy , netptr->cell , netptr->pinloc,
	    netptr->unequiv , netptr->flag , netptr->extint ) ;
    }
}
    
twclose( fp ) ;
}


pairCheck( first_row , last_row )
int first_row , last_row ;
{

FILE *fp ;
CBOXPTR cellptr ;
TIBOXPTR tileptr ;
int row , i , j , bin_left_edge , *Aray , cell , bin ;
int most_left , most_rite ;

fp = twopen( "dbg.pairCheck" , "a", ABORT ) ;
fprintf(fp,"cedge_binwidth = %d num_edgebin = %d\n",
			cedge_binwidth, num_edgebin ) ;

for( row = first_row ; row <= last_row ; row++ ) {
    Aray = pairArray[row] ;
    fprintf(fp,"\nROW %d\n" , row ) ;
    fprintf(fp," total number of cells in this row = %d\n",Aray[0] ) ;
    cellptr = carray[ Aray[1] ] ;
    most_left = cellptr->cxcenter + cellptr->tileptr->left ;
    cellptr = carray[ Aray[Aray[0]] ] ;
    most_rite = cellptr->cxcenter + cellptr->tileptr->right ;
    fprintf(fp," most_left is at %d most_rite is at \n", 
				    most_left , most_rite ) ;
    fprintf(fp,"   i  cell  left right height   top bottom\n" ) ;
    for( i = 1 ; i <= Aray[0] ; i++ ) {
	cell = Aray[i] ;
	cellptr = carray[ cell ] ;
	tileptr = cellptr->tileptr ;
	fprintf(fp," %3d %5d %5d %5d %6d %5d %6d\n",
	    i , cell , tileptr->left + cellptr->cxcenter ,
	    tileptr->right + cellptr->cxcenter , cellptr->cheight , 
				tileptr->top , -tileptr->bottom ) ;
    }
    fprintf(fp," bin index cell bin_left_edge\n" ) ;
    bin_left_edge = most_left ;
    for( bin = 1 ; bin <= num_edgebin ; bin++ ) {
	j = cedgebin[row][bin] ;
	fprintf(fp," %3d %5d %4d        %5d\n" ,
	    bin , j , Aray[j] , bin_left_edge ) ;
	bin_left_edge += cedge_binwidth ;
    }
}
twclose( fp ) ;
}


trackdebug( status )
int status ;
{
char filename[64] ;
int i , row , fcell , cht , fht , newtrack ;
FILE *fp ;
CHANGRDPTR gdptr , startptr , endptr ;
NBOXPTR netptr ;


fp = twopen( "trackdbg" , "a", ABORT ) ;
fprintf(fp,"\n S nS tk nt Tk rs   pin  xpos  newx  cell  fcel cht fht\n");
for( gdptr = ULgrdptr ; gdptr != URgrdptr->nextgrd ; ) {
    netptr = gdptr->netptr ;
    fht = fcellheight( netptr->terminal , &fcell , status ) ;
    if( netptr->pinloc == 1 ) {
	cht = carray[ netptr->cell ]->tileptr->top ;
    } else if( netptr->pinloc == 0 ) {
	cht = 0 ;
    } else {
	cht = -carray[ netptr->cell ]->tileptr->bottom ;
    }
    if( status == OLD ) {
	newtrack = gdptr->tracks - ( cht + fht ) / track_spacing ;
    } else {
	newtrack = gdptr->ntracks - ( cht + fht ) / track_spacing ;
    }
    fprintf(fp ,"%2d %2d %2d %2d %2d %2d %5d %5d %5d %5d %5d %3d %3d\n"
    , gdptr->SegType , gdptr->nSegType , gdptr->tracks , gdptr->ntracks
    , newtrack , ( cht + fht ) / track_spacing ,
    netptr->terminal , netptr->xpos ,netptr->newx , netptr->cell ,
    fcell , cht , fht ) ;
    if( status == OLD ) {
	gdptr = gdptr->nextgrd ;
    } else {
	gdptr = gdptr->nnextgrd ;
    }
}
fprintf(fp,"\n S nS tk nt Tk rs   pin  xpos  newx  cell  fcel cht fht\n");
for( gdptr = LLgrdptr ; gdptr != LRgrdptr->nextgrd ; ) {
    netptr = gdptr->netptr ;
    fht = fcellheight( netptr->terminal , &fcell , status ) ;
    if( netptr->pinloc == 1 ) {
	cht = carray[ netptr->cell ]->tileptr->top ;
    } else if( netptr->pinloc == 0 ) {
	cht = 0 ;
    } else {
	cht = -carray[ netptr->cell ]->tileptr->bottom ;
    }
    if( status == OLD ) {
	newtrack = gdptr->tracks - ( cht + fht ) / track_spacing ;
    } else {
	newtrack = gdptr->ntracks - ( cht + fht ) / track_spacing ;
    }
    fprintf(fp ,"%2d %2d %2d %2d %2d %2d %5d %5d %5d %5d %5d %3d %3d\n"
    , gdptr->SegType , gdptr->nSegType , gdptr->tracks , gdptr->ntracks
    , newtrack , ( cht + fht ) / track_spacing ,
    netptr->terminal , netptr->xpos ,netptr->newx , netptr->cell ,
    fcell , cht , fht ) ;
    if( status == OLD ) {
	gdptr = gdptr->nextgrd ;
    } else {
	gdptr = gdptr->nnextgrd ;
    }
}
twclose( fp ) ;
}


fcellheight( pin , fcell , status )
int pin , *fcell , status ;
{

CBOXPTR cellptr ;
int bin , i , *Aray , most_left , most_rite ;
int nrow , pin_x , crite , row , pinloc ;

row = tearray[pin]->row ;
pinloc = tearray[pin]->pinloc ;
if( 1 <= row  && row <= numRows ) {
    nrow = row + pinloc ;
    if( nrow == 0 || nrow == numChans || pinloc == 0 ) {
	*fcell = 0 ;
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
    *fcell = 0 ;
    return( 0 ) ;
}
bin = ( pin_x - most_left ) / cedge_binwidth + 1 ;
if( ( i = cedgebin[nrow][bin] ) == 0 ) {
    *fcell = 0 ;
    return( 0 ) ;
}
*fcell = Aray[i] ;
cellptr =  carray[ *fcell ] ;
crite = cellptr->tileptr->right + cellptr->cxcenter ;
while(  crite < pin_x && i < Aray[0] ) {
    *fcell = Aray[++i] ;
    cellptr = carray[ *fcell ] ;
    crite += cellptr->clength ;
}
if( crite == pin_x && i != Aray[0] ) {
    if( carray[ Aray[i+1] ]->cheight > cellptr->cheight ) {
	*fcell = Aray[i+1] ;
	cellptr = carray[ *fcell ] ;
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

chan_debug( start_chan , end_chan , status )
int start_chan , end_chan , status ;
{
char filename[64] ;
int i , row , fcell , cht , fht , chan , newtrack ;
FILE *fp ;
CHANGRDPTR gdptr ;
NBOXPTR netptr ;


fp = twopen( "chandbg" , "a", ABORT ) ;
for( chan = start_chan ; chan <= end_chan ; chan++ ) {
fprintf(fp,"\n channel = %d\n" , chan ) ;
fprintf(fp,"\n S nS tk nt Tk rs   pin  xpos  newx  cell  fcel cht fht\n");
if( status == OLD ) {
    gdptr = Begin[chan]->nextgrd ;
} else {
    gdptr = Begin[chan]->nnextgrd ;
}
for( ; gdptr != End[chan] ; ) {
    netptr = gdptr->netptr ;
    fht = fcellheight( netptr->terminal , &fcell , status ) ;
    if( netptr->pinloc == 1 ) {
	cht = carray[ netptr->cell ]->tileptr->top ;
    } else if( netptr->pinloc == 0 ) {
	cht = 0 ;
    } else {
	cht = -carray[ netptr->cell ]->tileptr->bottom ;
    }
    if( status == OLD ) {
	newtrack = gdptr->tracks - ( cht + fht ) / track_spacing ;
    } else {
	newtrack = gdptr->ntracks - ( cht + fht ) / track_spacing ;
    }
    fprintf(fp ,"%2d %2d %2d %2d %2d %2d %5d %5d %5d %5d %5d %3d %3d\n" 
    , gdptr->SegType , gdptr->nSegType , gdptr->tracks , gdptr->ntracks
    , newtrack , ( cht + fht ) / track_spacing ,
    netptr->terminal , netptr->xpos ,netptr->newx , netptr->cell ,
    fcell , cht , fht ) ;
    if( status == OLD ) {
	gdptr = gdptr->nextgrd ;
    } else {
	gdptr = gdptr->nnextgrd ;
    }
}
}
twclose( fp ) ;
}

negative()
{


NBOXPTR netptr ;
CHANGRDPTR gdptr ;
int channel ;

for( channel = 1 ; channel <= numChans ; channel++ ) {
    for( gdptr = Begin[ channel ]->nnextgrd ; gdptr != GRDNULL ;
					gdptr = gdptr->nnextgrd ) {
	netptr = gdptr->netptr ;
	if( gdptr->ntracks < 0 ) {
	    printf("channel   pin  xpos  newx  cell   net\n" ) ;
	    printf("    %3d %5d %5d %5d %5d %5d\n", channel ,
		netptr->terminal , netptr->xpos , netptr->newx ,
		netptr->cell , netptr->net ) ;
	}
    }
}
}
