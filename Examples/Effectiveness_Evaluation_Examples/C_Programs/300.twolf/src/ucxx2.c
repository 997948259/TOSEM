#include "ucxxglb.h"

int axcenter , aycenter , bxcenter , bycenter ;
int anxcenter , bnxcenter ;
int aleft , aright , bleft , bright ;
int potential_errors , error_count , P_limit ;
double total_wire_chg ;
double sigma_wire_chg ;
double mean_wire_chg ;
int wire_chgs ;
extern int attempts ;

ucxx2( )
{

CBOXPTR acellptr , bcellptr ;
TIBOXPTR atileptr , btileptr ;
TEBOXPTR atermptr , btermptr ;
int error_light_is_on ;
int cost ;
int aorient , borient ;
int a1LoBin, a1HiBin, b1LoBin, b1HiBin ;
int a2LoBin, a2HiBin, b2LoBin, b2HiBin ;
int startxa1 , endxa1 , startxa2 , endxa2 ;
int startxb1 , endxb1 , startxb2 , endxb2 ;
int anbin , bnbin , i ;
int truth ;
double temp ;


acellptr = carray[ a ]    ; 
axcenter = acellptr->cxcenter ; 
aycenter = acellptr->cycenter ; 
aorient  = acellptr->corient  ; 
atileptr = acellptr->tileptr ; 
aleft    = atileptr->left    ; 
aright   = atileptr->right   ; 
atermptr = atileptr->termsptr ; 

bcellptr = carray[ b ]    ; 
bxcenter = bcellptr->cxcenter ; 
bycenter = bcellptr->cycenter ; 
borient  = bcellptr->corient  ; 
btileptr = bcellptr->tileptr ; 
bleft    = btileptr->left    ; 
bright   = btileptr->right   ; 
btermptr = btileptr->termsptr ; 

newbinpenal = binpenal ;
newrowpenal = rowpenal ;
newpenal    = penalty  ;

new_old( bright-bleft-aright+aleft ) ;

find_new_pos() ;

a1LoBin = SetBin( startxa1 = axcenter + aleft  ) ; 
a1HiBin = SetBin( endxa1   = axcenter + aright ) ; 
b1LoBin = SetBin( startxb1 = bxcenter + bleft  ) ; 
b1HiBin = SetBin( endxb1   = bxcenter + bright ) ; 
a2LoBin = SetBin( startxa2 = anxcenter + aleft  ) ; 
a2HiBin = SetBin( endxa2   = anxcenter + aright ) ; 
b2LoBin = SetBin( startxb2 = bnxcenter + bleft  ) ; 
b2HiBin = SetBin( endxb2   = bnxcenter + bright ) ; 

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
    term_newpos_a( atermptr , anxcenter , bycenter , aorient ) ; 
    term_newpos_b( btermptr , bnxcenter , aycenter , borient ) ; 
} else {
    term_newpos( atermptr , anxcenter , bycenter , aorient ) ; 
    term_newpos( btermptr , bnxcenter , aycenter , borient ) ; 
}

cost = funccost ; 

delta_vert_cost = 0 ;
if( ablock != bblock ) {
    new_dbox_a( atermptr , &cost ) ;
    new_dbox_a( btermptr , &cost ) ;
} else {
    new_dbox( atermptr , &cost ) ;
    new_dbox( btermptr , &cost ) ;
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
	dbox_pos_2( atermptr ) ;
	dbox_pos_2( btermptr ) ;
    } else {
	dbox_pos( atermptr ) ;
	dbox_pos( btermptr ) ;
    }
    anbin = SetBin( anxcenter ) ;
    bnbin = SetBin( bnxcenter ) ;
    if( cellaptr != cellbptr ) {
	remv_cell( cellaptr , Apost ) ;
	remv_cell( cellbptr , Bpost ) ;
	add_cell( &binptr[bblock][anbin]->cell , a ) ;
	add_cell( &binptr[ablock][bnbin]->cell , b ) ;
    } else {
	remv_cell( cellaptr , Apost ) ;
	for( i = 1 ; i <= *cellaptr ; i++ ) {
	    if( cellaptr[i] == b ) {
		break ;
	    }
	}
	remv_cell( cellaptr , i ) ;
	add_cell( &binptr[ablock][anbin]->cell , a ) ;
	add_cell( &binptr[ablock][bnbin]->cell , b ) ;
    }
    if( wire_chg < 0 ) {
	temp = (double) - wire_chg ;
	total_wire_chg += temp ;
	sigma_wire_chg += (temp - mean_wire_chg) * 
					(temp - mean_wire_chg) ;
	wire_chgs++ ;
    }
 
    acellptr->cblock   = bblock    ;
    acellptr->cxcenter = anxcenter ; 
    acellptr->cycenter = bycenter  ; 
    bcellptr->cblock   = ablock    ;
    bcellptr->cxcenter = bnxcenter ; 
    bcellptr->cycenter = aycenter  ; 

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


find_new_pos()
{

int newA_l , newA_r , newB_l , newB_r ;
int oldA_l , oldA_r , oldB_l , oldB_r ;
int span , target , target_l , target_r , blkLeft , blkRite ;
int dist1 , dist2 ;


newA_l = bxcenter + aleft  ;
newA_r = bxcenter + aright ;
newB_l = axcenter + bleft  ;
newB_r = axcenter + bright ;
if( (ablock == bblock) && (!( (newA_l >= newB_r) || (newB_l >= newA_r)))){
    /*  
     *   Then some overlapping will exist in the new positions
     */
    oldA_l = axcenter + aleft  ;
    oldA_r = axcenter + aright ;
    oldB_l = bxcenter + bleft  ;
    oldB_r = bxcenter + bright ;
    if( !( (oldA_l >= oldB_r) || (oldB_l >= oldA_r) ) ) {
	/*  
	 *    There was also initial overlap; therefore
	 *    move cells apart.  Find the minimum distance
	 *    necessary to pull them apart.
	 */
	span = aright - aleft + bright - bleft ;
	target = ( ((oldA_l <= oldB_l) ? oldA_l : oldB_l) +
		   ((oldA_r >= oldB_r) ? oldA_r : oldB_r) ) / 2 ;
	target_l = target - span / 2 ;
	target_r = target_l + span ;
	blkLeft = barray[ablock]->bxcenter + barray[ablock]->bleft ;
	blkRite = blkLeft + barray[ablock]->desire  ;
	if( target_l < blkLeft ) {
	    target_l += blkLeft - target_l ;
	    target_r += blkLeft - target_l ;
	} else if( target_r > blkRite ) {
	    target_l -= target_r - blkRite ;
	    target_r -= target_r - blkRite ;
	}
	dist1 = newA_r - newB_l ;
	dist2 = newB_r - newA_l ;
	if( dist1 <= dist2 ) {
	    anxcenter = target_l - aleft  ;
	    bnxcenter = target_r - bright ;
	} else {
	    anxcenter = target_r - aright ;
	    bnxcenter = target_l - bleft  ;
	}
    } else {
	/*  
	 *    No initial overlap, but some would be created
	 *    as it stands now.  Eliminate the possibility of
	 *    overlap by maintaining the original left
	 *    bound and the original right bound.
	 */
	if( oldA_l <= oldB_l ) {
	    bnxcenter = oldA_l - bleft  ;
	    anxcenter = oldB_r - aright ;
	} else {
	    anxcenter = oldB_l - aleft  ;
	    bnxcenter = oldA_r - bright ;
	}
    }
} else {
    anxcenter = bxcenter ;
    bnxcenter = axcenter ;

}
return ;
}
 

add_cell( cellptr , c ) 
int **cellptr , c ;
{

int k ;

if( (k = ++(**cellptr)) % 10 == 0 ) {
    *cellptr = (int *) safe_realloc( *cellptr, (k + 10) * sizeof(int));

}
(*cellptr)[k] = c ;

return ;
}




/*
remv_cell( cellptr , post )
int *cellptr , post ;
{

if( *cellptr != post ) {
    cellptr[ post ] = cellptr[ *cellptr ] ;
}
(*cellptr)-- ;
}
*/
