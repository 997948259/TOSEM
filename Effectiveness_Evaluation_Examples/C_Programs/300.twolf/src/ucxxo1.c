#include "ucxxglb.h"

ucxxo1( bxcenter , bycenter , newaor )
int bxcenter , bycenter , newaor ;
{

CBOXPTR acellptr ;
TIBOXPTR atileptr ;
TEBOXPTR antrmptr ;

int cost ;
int axcenter ;
int aleft , aright ;
int a1LoBin, a1HiBin, b1LoBin, b1HiBin ;
int startxa1 , endxa1 , startxb1 , endxb1 ;
int truth ;

acellptr = carray[ a ]    ; 
axcenter = acellptr->cxcenter ; 
atileptr = acellptr->tileptr ;
aleft    = atileptr->left ; 
aright   = atileptr->right ; 
antrmptr = atileptr->termsptr ; 
 
newbinpenal = binpenal ;
newrowpenal = rowpenal ;
newpenal    = penalty ;

new_old( aleft - aright ) ;

a1LoBin = SetBin( startxa1 = axcenter + aleft   ) ; 
a1HiBin = SetBin( endxa1   = axcenter + aright  ) ; 
b1LoBin = SetBin( startxb1 = bxcenter + aleft   ) ; 
b1HiBin = SetBin( endxb1   = bxcenter + aright  ) ; 

old_assgnto_new1( a1LoBin , a1HiBin , b1LoBin , b1HiBin ) ;

sub_penal( startxa1 , endxa1 , ablock , a1LoBin , a1HiBin ) ;
add_penal( startxb1 , endxb1 , bblock , b1LoBin , b1HiBin ) ; 

if( ablock != bblock ) {
    term_newpos_a( antrmptr , bxcenter , bycenter , newaor ) ;
} else {
    term_newpos( antrmptr , bxcenter , bycenter , newaor ) ;
}

cost = funccost ; 

delta_vert_cost = 0 ;
if( ablock != bblock ) {
    new_dbox_a( antrmptr , &cost ) ;
} else {
    new_dbox( antrmptr , &cost ) ;
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
	dbox_pos_2( antrmptr ) ;
    } else {
	dbox_pos( antrmptr ) ;
    }
    /* ****************************************************** */
    remv_cell( cellaptr , Apost ) ;
    add_cell( &cellbptr , a ) ;
    /* ****************************************************** */


    acellptr->cblock   = bblock   ;
    acellptr->cxcenter = bxcenter     ; 
    acellptr->cycenter = bycenter     ; 
    acellptr->corient  = newaor ; 

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
