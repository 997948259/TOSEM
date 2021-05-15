#include "ucxxglb.h"

ucxx1( bxcenter , bycenter )
int bxcenter , bycenter ;
{

CBOXPTR acellptr ;
TIBOXPTR atileptr ;
TEBOXPTR atermptr ;

int cost ;
int axcenter ;
int aleft , aright ;
int a1LoBin , a1HiBin , b1LoBin , b1HiBin ;
int startxa1 , endxa1 , startxb1 , endxb1 ;
int truth , aorient ;

acellptr = carray[ a ]    ; 
aorient  = acellptr->corient ;
axcenter = acellptr->cxcenter ; 
atileptr = acellptr->tileptr  ;
aleft    = atileptr->left    ; 
aright   = atileptr->right   ; 
atermptr = atileptr->termsptr ; 
 
newbinpenal = binpenal ;
newrowpenal = rowpenal ;
newpenal    = penalty ;

new_old( aleft-aright ) ;


a1LoBin = SetBin( startxa1 = axcenter + aleft  ) ; 
a1HiBin = SetBin( endxa1   = axcenter + aright ) ; 
b1LoBin = SetBin( startxb1 = bxcenter + aleft  ) ; 
b1HiBin = SetBin( endxb1   = bxcenter + aright ) ; 

old_assgnto_new1( a1LoBin , a1HiBin , b1LoBin , b1HiBin ) ;

sub_penal( startxa1 , endxa1 , ablock , a1LoBin , a1HiBin ) ; 
add_penal( startxb1 , endxb1 , bblock , b1LoBin , b1HiBin ) ; 

if( ablock != bblock ) {
    term_newpos_a( atermptr , bxcenter , bycenter , aorient ) ; 
} else {
    term_newpos( atermptr , bxcenter , bycenter , aorient ) ; 
}

cost = funccost ; 

delta_vert_cost = 0 ;
if( ablock != bblock ) {
    new_dbox_a( atermptr , &cost ) ;
} else {
    new_dbox( atermptr , &cost ) ;
}

wire_chg = cost - funccost ;
binpen_chg = newbinpenal - binpenal ;
rowpen_chg = newrowpenal - rowpenal ;

newpenal = (int)( roLenCon * (double) newrowpenal + 
				binpenCon * (double) newbinpenal ) ;
truth = acceptt(funccost + penalty - cost - newpenal - delta_vert_cost);
if( truth == 1 ) {
    new_assgnto_old1( a1LoBin , a1HiBin , b1LoBin , b1HiBin ) ;
    if( ablock != bblock ) {
	dbox_pos_2( atermptr ) ;
    } else {
	dbox_pos( atermptr ) ;
    }
    /* ****************************************************** */
    remv_cell( cellaptr , Apost ) ;
    add_cell( &cellbptr , a ) ;
    /* ****************************************************** */

    acellptr->cblock   = bblock   ;
    acellptr->cxcenter = bxcenter ; 
    acellptr->cycenter = bycenter ; 

    funccost = cost ; 
    binpenal = newbinpenal ;
    rowpenal = newrowpenal ;
    penalty  = newpenal ;

    if( ablock != bblock ) {
	barray[ablock]->oldsize = barray[ablock]->newsize ;
	barray[bblock]->oldsize = barray[bblock]->newsize ;
    }
    return( 1 ) ;
} else {
    return( 0 ) ;
}
}
