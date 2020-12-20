#include "standard.h"


uc0( a , newaor )
int a , newaor ;
{

CBOXPTR acellptr ;
TEBOXPTR antrmptr ;
int cost , truth ;


acellptr = carray[ a ]    ;
antrmptr = acellptr->tileptr->termsptr ;

term_newpos( antrmptr, acellptr->cxcenter, acellptr->cycenter, newaor );

cost = funccost ;

new_dbox( antrmptr , &cost ) ;

truth =  acceptt( funccost - cost ) ; 
if( truth == 1 ) {

    dbox_pos( antrmptr ) ;
    acellptr->corient = newaor ;
    funccost = cost ;
}
return ;
}
