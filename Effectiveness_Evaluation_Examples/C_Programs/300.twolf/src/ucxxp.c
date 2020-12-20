#include "ucxxglb.h"

ucxxp( a , b , anxcenter , bnxcenter )
int a , b , anxcenter , bnxcenter ;
{

CBOXPTR acellptr , bcellptr ;
TIBOXPTR atileptr , btileptr ;
TEBOXPTR atermptr , btermptr ;

int cost ;
int aorient , borient ;
int aycenter , bycenter ;
int truth ;

acellptr = carray[ a ]    ; 
aycenter = acellptr->cycenter ; 
aorient  = acellptr->corient  ; 
atileptr = acellptr->tileptr ;
atermptr = atileptr->termsptr ; 

bcellptr = carray[ b ]    ; 
bycenter = bcellptr->cycenter ; 
borient  = bcellptr->corient  ; 
btileptr = bcellptr->tileptr ;
btermptr = btileptr->termsptr ; 

term_newpos( atermptr , anxcenter , bycenter , aorient ) ; 
term_newpos( btermptr , bnxcenter , aycenter , borient ) ; 

cost = funccost ; 

new_dbox( atermptr , &cost ) ;
new_dbox( btermptr , &cost ) ;

truth = acceptt( funccost - cost ) ;

if( truth == 1 ) {

    dbox_pos( atermptr ) ;
    dbox_pos( btermptr ) ;

    acellptr->cxcenter = anxcenter ; 
    acellptr->cycenter = bycenter ; 
    bcellptr->cxcenter = bnxcenter ; 
    bcellptr->cycenter = aycenter ; 

    funccost = cost ; 
    return( 1 ) ;
} else {
    return( 0 ) ;
}
}
