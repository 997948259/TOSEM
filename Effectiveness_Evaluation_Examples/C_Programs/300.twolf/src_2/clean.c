#include "ucxxglb.h"

new_old( c )
int c ;
{

int old , new ;

if( ablock != bblock ) {
    barray[ablock]->newsize = barray[ablock]->oldsize + c ;
    barray[bblock]->newsize = barray[bblock]->oldsize - c ;
    old  = ABS(barray[ablock]->oldsize - barray[ablock]->desire) +
	   ABS(barray[bblock]->oldsize - barray[bblock]->desire) ;
    new  = ABS(barray[ablock]->newsize - barray[ablock]->desire) +
	   ABS(barray[bblock]->newsize - barray[bblock]->desire) ;
    newrowpenal += (new - old) ;
}
}


old_assgnto_new1( alobin , ahibin , anewlobin , anewhibin )
int alobin , ahibin , anewlobin , anewhibin ;
{

int bin , lobin , hibin ;

if( ablock == bblock ) {
    lobin = ( alobin <= anewlobin ) ? alobin : anewlobin ;
    hibin = ( ahibin >= anewhibin ) ? ahibin : anewhibin ;
    for( bin = lobin ; bin <= hibin ; bin++ ) {
	binptr[ablock][bin]->nupenalty = 
			 binptr[ablock][bin]->penalty ;
    } 
} else {
    for( bin = alobin ; bin <= ahibin ; bin++ ) {
	binptr[ablock][bin]->nupenalty = 
			 binptr[ablock][bin]->penalty ;
    }
    for( bin = anewlobin ; bin <= anewhibin ; bin++ ) {
	binptr[bblock][bin]->nupenalty = 
			 binptr[bblock][bin]->penalty ;
    }
} 
}
    

new_assgnto_old1( alobin , ahibin , anewlobin , anewhibin )
int alobin , ahibin , anewlobin , anewhibin ;
{

int bin , lobin , hibin ;

if( ablock == bblock ) {
    lobin = ( alobin <= anewlobin ) ? alobin : anewlobin ;
    hibin = ( ahibin >= anewhibin ) ? ahibin : anewhibin ;
    for( bin = lobin ; bin <= hibin ; bin++ ) {
	binptr[ablock][bin]->penalty = 
			 binptr[ablock][bin]->nupenalty ;
    } 
} else {
    for( bin = alobin ; bin <= ahibin ; bin++ ) {
	binptr[ablock][bin]->penalty = 
			 binptr[ablock][bin]->nupenalty ;
    }
    for( bin = anewlobin ; bin <= anewhibin ; bin++ ) {
	binptr[bblock][bin]->penalty = 
			 binptr[bblock][bin]->nupenalty ;
    }
} 
}

old_assgnto_new2( a1lobin , a1hibin , a2lobin , a2hibin ,
		  b1lobin , b1hibin , b2lobin , b2hibin )
int a1lobin , a1hibin , a2lobin , a2hibin ;
int b1lobin , b1hibin , b2lobin , b2hibin ;
{

int clobin , chibin , dlobin , dhibin ;
int lobin , hibin , bin ;

clobin = ( a1lobin <= b2lobin ) ? a1lobin : b2lobin ;
chibin = ( a1hibin >= b2hibin ) ? a1hibin : b2hibin ;
dlobin = ( a2lobin <= b1lobin ) ? a2lobin : b1lobin ;
dhibin = ( a2hibin >= b1hibin ) ? a2hibin : b1hibin ;
if( ablock == bblock ) {
    lobin = ( clobin <= dlobin ) ? clobin : dlobin ;
    hibin = ( chibin >= dhibin ) ? chibin : dhibin ;
    for( bin = lobin ; bin <= hibin ; bin++ ) {
	binptr[ablock][bin]->nupenalty = 
		     binptr[ablock][bin]->penalty ;
    }
} else {
    for( bin = clobin ; bin <= chibin ; bin++ ) {
	binptr[ablock][bin]->nupenalty = 
		     binptr[ablock][bin]->penalty ;
    }
    for( bin = dlobin ; bin <= dhibin ; bin++ ) {
	binptr[bblock][bin]->nupenalty = 
		     binptr[bblock][bin]->penalty ;
    }
}
}
	 

new_assgnto_old2( a1lobin , a1hibin , a2lobin , a2hibin ,
		  b1lobin , b1hibin , b2lobin , b2hibin )
int a1lobin , a1hibin , a2lobin , a2hibin ;
int b1lobin , b1hibin , b2lobin , b2hibin ;
{

int clobin , chibin , dlobin , dhibin ;
int lobin , hibin , bin ;

clobin = ( a1lobin <= b2lobin ) ? a1lobin : b2lobin ;
chibin = ( a1hibin >= b2hibin ) ? a1hibin : b2hibin ;
dlobin = ( a2lobin <= b1lobin ) ? a2lobin : b1lobin ;
dhibin = ( a2hibin >= b1hibin ) ? a2hibin : b1hibin ;
if( ablock == bblock ) {
    lobin = ( clobin <= dlobin ) ? clobin : dlobin ;
    hibin = ( chibin >= dhibin ) ? chibin : dhibin ;
    for( bin = lobin ; bin <= hibin ; bin++ ) {
	binptr[ablock][bin]->penalty = 
		     binptr[ablock][bin]->nupenalty ;
    }
} else {
    for( bin = clobin ; bin <= chibin ; bin++ ) {
	binptr[ablock][bin]->penalty = 
		     binptr[ablock][bin]->nupenalty ;
    }
    for( bin = dlobin ; bin <= dhibin ; bin++ ) {
	binptr[bblock][bin]->penalty = 
		     binptr[bblock][bin]->nupenalty ;
    }
}
}


sub_penal( startx , endx , block , LoBin , HiBin )
int startx , endx , block , LoBin , HiBin ;
{

BINPTR bptr ;
int bin ;


if( LoBin == HiBin ) {
    bptr = binptr[block][LoBin] ;
    newbinpenal     -= ABS( bptr->nupenalty ) ; 
    bptr->nupenalty -= endx - startx          ;
    newbinpenal     += ABS( bptr->nupenalty ) ;
} else {
    for( bin = LoBin ; bin <= HiBin ; bin++ ) {
	bptr = binptr[block][bin] ;
	if( bin == LoBin ) {
	    newbinpenal     -= ABS( bptr->nupenalty ) ;
	    bptr->nupenalty -= bptr->right - startx   ;
	    newbinpenal     += ABS( bptr->nupenalty ) ;
        } else if( bin == HiBin ) {
	    newbinpenal     -= ABS( bptr->nupenalty ) ;
	    bptr->nupenalty -= endx - bptr->left      ;
	    newbinpenal     += ABS( bptr->nupenalty ) ;
        } else {
	    newbinpenal     -= ABS( bptr->nupenalty ) ;
	    bptr->nupenalty -= binWidth               ;
	    newbinpenal     += ABS( bptr->nupenalty ) ;
        }
    }
}
}

add_penal( startx , endx , block , LoBin , HiBin )
int startx , endx , block , LoBin , HiBin ;
{

BINPTR bptr ;
int bin ;

if( LoBin == HiBin ) {
    bptr = binptr[block][LoBin] ;
    newbinpenal     -= ABS( bptr->nupenalty ) ; 
    bptr->nupenalty += endx - startx          ;
    newbinpenal     += ABS( bptr->nupenalty ) ;
} else {
    for( bin = LoBin ; bin <= HiBin ; bin++ ) {
	bptr = binptr[block][bin] ;
	if( bin == LoBin ) {
	    newbinpenal     -= ABS( bptr->nupenalty ) ;
	    bptr->nupenalty += bptr->right - startx   ;
	    newbinpenal     += ABS( bptr->nupenalty ) ;
        } else if( bin == HiBin ) {
	    newbinpenal     -= ABS( bptr->nupenalty ) ;
	    bptr->nupenalty += endx - bptr->left      ;
	    newbinpenal     += ABS( bptr->nupenalty ) ;
        } else {
	    newbinpenal     -= ABS( bptr->nupenalty ) ;
	    bptr->nupenalty += binWidth               ;
	    newbinpenal     += ABS( bptr->nupenalty ) ;
        }
    }
}
}
