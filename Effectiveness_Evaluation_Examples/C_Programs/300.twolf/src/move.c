#include <stdio.h>
#include "mt.h"

static MT *mt = (MT *) NULL ;



point( x , y )
short int *x , *y ;

{
    int xx , yy ;

    if( mt == (MT *) NULL ) {

        return;
    }

    xx = *x ;
    yy = *y ;

    MTPoint( mt , &xx , &yy ) ;

    *x = xx ;
    *y = yy ;

    return ;
}



rect( l , b , r , t )
short int *l , *b , *r , *t ;
{

    short int temp ;

    point( l , b ) ;
    point( r , t ) ;

    if( *l > *r ) {

        temp = *l   ;
        *l   = *r   ;
        *r   = temp ; 
    }

    if( *b > *t ) {

        temp = *b   ;
        *b   = *t   ;
        *t   = temp ; 
    }

    return ;
}



move( moveType )
int moveType ;

{

    if( mt == (MT *) NULL ) {

    	mt = MTBegin() ;
    }

    MTIdenti( mt ) ;

    switch( moveType ) {

        case 0 :

            return ;


        case 1 :

            MTMY( mt ) ; 
    	    return     ;


        case 2 :

            MTMX( mt ) ; 
	    return     ;


        case 3 :

            MTRotate( mt , -1 , 0 ) ; 
	    return ; 


        case 4 :

            MTMX( mt ) ; 
	    MTRotate( mt , 0 , 1 ) ; 
	    return ;


        case 5 :

            MTMX( mt ) ; 
	    MTRotate( mt , 0 , -1 ) ; 
	    return ;


        case 6 :

            MTRotate( mt , 0 , 1 ) ; 
	    return ;


        case 7 :

            MTRotate( mt , 0 , -1 ) ; 
	    return ;

    }
}
