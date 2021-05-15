#include "ucxxglb.h"
extern int potential_errors , error_count ;
extern int attempts ;
extern int P_limit ;
extern double total_wire_chg ;
extern double sigma_wire_chg ;
extern double mean_wire_chg ;
extern int wire_chgs ;

ucxxo2( newaor , newbor )
int newaor , newbor ;
{

CBOXPTR acellptr , bcellptr ;
TIBOXPTR atileptr , btileptr ;
TEBOXPTR antrmptr , bntrmptr ;
double temp ;
int cost , error_light_is_on ;
int axcenter , aycenter , bxcenter , bycenter ;
int aleft , aright ;
int bleft , bright ;
int a1LoBin, a2LoBin, b1LoBin, b2LoBin ;
int a1HiBin, a2HiBin, b1HiBin, b2HiBin ;
int startxa1 , endxa1 , startxa2 , endxa2 ;
int startxb1 , endxb1 , startxb2 , endxb2 ;
int truth ;

acellptr = carray[ a ]    ;
axcenter = acellptr->cxcenter ;
aycenter = acellptr->cycenter ;
atileptr = acellptr->tileptr ;
aleft    = atileptr->left    ;
aright   = atileptr->right   ;
antrmptr = atileptr->termsptr ;

bcellptr = carray[ b ]        ;
bxcenter = bcellptr->cxcenter ;
bycenter = bcellptr->cycenter ;
btileptr = bcellptr->tileptr  ;
bleft    = btileptr->left     ;
bright   = btileptr->right    ;
bntrmptr = btileptr->termsptr ;

newbinpenal = binpenal ;
newrowpenal = rowpenal ;
newpenal    = penalty ;

new_old( bright - bleft - aright + aleft ) ;

a1LoBin = SetBin( startxa1 = axcenter + aleft    ) ;
a1HiBin = SetBin( endxa1   = axcenter + aright   ) ; 
b1LoBin = SetBin( startxb1 = bxcenter + bleft    ) ; 
b1HiBin = SetBin( endxb1   = bxcenter + bright   ) ; 
a2LoBin = SetBin( startxa2 = bxcenter + aleft    ) ;
a2HiBin = SetBin( endxa2   = bxcenter + aright   ) ; 
b2LoBin = SetBin( startxb2 = axcenter + bleft    ) ; 
b2HiBin = SetBin( endxb2   = axcenter + bright   ) ; 

old_assgnto_new2( a1LoBin , a1HiBin , b1LoBin , b1HiBin , 
		  a2LoBin , a2HiBin , b2LoBin , b2HiBin ) ;
sub_penal( startxa1 , endxa1 , ablock , a1LoBin , a1HiBin ) ;
sub_penal( startxb1 , endxb1 , bblock , b1LoBin , b1HiBin ) ;
add_penal( startxa2 , endxa2 , bblock , a2LoBin , a2HiBin ) ;
add_penal( startxb2 , endxb2 , ablock , b2LoBin , b2HiBin ) ;

binpen_chg = newbinpenal - binpenal ;
rowpen_chg = newrowpenal - rowpenal ;
newpenal = (int)( roLenCon * (double) newrowpenal + 
				binpenCon * (double) newbinpenal ) ;

error_light_is_on = 0 ;
if( newpenal - penalty > P_limit ) {
    if( potential_errors < 100 ) {
	++potential_errors ;
	error_light_is_on = 1 ;
    } else {
	earlyRej++ ;
	return( -1 ) ;
    }
}

if( ablock != bblock ) {
    term_newpos_a( antrmptr , bxcenter , bycenter , newaor ) ;
    term_newpos_b( bntrmptr , axcenter , aycenter , newbor ) ;
} else {
    term_newpos( antrmptr , bxcenter , bycenter , newaor ) ;
    term_newpos( bntrmptr , axcenter , aycenter , newbor ) ;
}

cost = funccost ;

delta_vert_cost = 0 ;
if( ablock != bblock ) {
    new_dbox_a( antrmptr , &cost ) ;
    new_dbox_a( bntrmptr , &cost ) ;
} else {
    new_dbox( antrmptr , &cost ) ;
    new_dbox( bntrmptr , &cost ) ;
}

wire_chg = cost - funccost ;

truth = acceptt(funccost + penalty - cost - newpenal - delta_vert_cost);

if( truth == 1 ) {

    if( error_light_is_on ) {
	error_count++ ;
    }

    new_assgnto_old2( a1LoBin , a1HiBin , b1LoBin , b1HiBin , 
		      a2LoBin , a2HiBin , b2LoBin , b2HiBin ) ;
    if( ablock != bblock ) {
	dbox_pos_2( antrmptr ) ;
	dbox_pos_2( bntrmptr ) ;   
    } else {
	dbox_pos( antrmptr ) ;
	dbox_pos( bntrmptr ) ;   
    }
    if( cellaptr != cellbptr ) {
	remv_cell( cellaptr , Apost ) ;
	remv_cell( cellbptr , Bpost ) ;
	add_cell( &cellbptr , a ) ;
	add_cell( &cellaptr , b ) ;
    }
    if( wire_chg < 0 ) {
	temp = (double) - wire_chg ;
	total_wire_chg += temp ;
	sigma_wire_chg += (temp - mean_wire_chg) * 
					(temp - mean_wire_chg) ;
	wire_chgs++ ;
    }
    /*
    if( wire_chg < max_wire_chg ) {
	max_wire_chg = wire_chg ;
    }
    */

    acellptr->cblock   = bblock   ;
    acellptr->cxcenter = bxcenter ;
    acellptr->cycenter = bycenter ;
    bcellptr->cblock   = ablock   ;
    bcellptr->cxcenter = axcenter ;
    bcellptr->cycenter = aycenter ;

    acellptr->corient = newaor ;
    bcellptr->corient = newbor ;

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
