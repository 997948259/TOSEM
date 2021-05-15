#include "standard.h"

maketabl()
{
    int i ;

    hashtab = ( HASHPTR * ) safe_malloc( 3001 * sizeof( HASHPTR ) ) ;
    for( i = 0 ; i < 3001 ; i++ ) {
	hashtab[i] = ( HASHPTR ) NULL ;
    }
    return ;
}

delHtab()
{
    int i ;
    HASHPTR hptr , zapptr ;

    for( i = 0 ; i < 3001 ; i++ ) {
	hptr = hashtab[i] ;
	if( hptr != (HASHPTR) NULL ) {
	    zapptr = hptr ;
	    while( hptr->hnext != (HASHPTR) NULL ) {
		hptr = hptr->hnext ;
		safe_free( zapptr ) ;
		zapptr = hptr ;
	    }
	    safe_free( hptr ) ;
	}
    }
    safe_free( hashtab ) ;
    return ;
}

addhash( hname )
char hname[] ;
{
    int i ;
    HASHPTR hptr ;
    unsigned int hsum = 0 ;

    for( i = 0 ; i < strlen( hname ) ; i++ ) {
	hsum += ( unsigned int ) hname[i] ;
    }
    hsum %= 3001 ;
    if( (hptr = hashtab[hsum]) == (HASHPTR) NULL ) {
	hptr = hashtab[hsum] = (HASHPTR) safe_malloc( sizeof( HASHBOX ) ) ;
	hptr->hnext = (HASHPTR) NULL ;
	hptr->hnum = ++netctr ;
	hptr->hname = (char *) safe_malloc( (strlen( hname ) + 1) * 
						sizeof( char ) ) ;
	sprintf( hptr->hname , "%s" , hname ) ;
	return(1) ;
    } else {
	for( ; ; ) {
	    if( strcmp( hname , hptr->hname ) == 0 ) {
		return(0) ;
	    }
	    if( hptr->hnext == (HASHPTR) NULL ) {
		hptr = hptr->hnext = (HASHPTR) safe_malloc( sizeof(HASHBOX));
		hptr->hnext = (HASHPTR) NULL ;
		hptr->hnum = ++netctr ;
		hptr->hname = (char *) safe_malloc( (strlen( hname ) + 1) * 
						sizeof( char ) ) ;
		sprintf( hptr->hname , "%s" , hname ) ;
		return(1) ;
	    } else {
		hptr = hptr->hnext ;
	    }
	}
    }
}

hashfind( hname )
char hname[] ;
{
    int i ;
    HASHPTR hptr ;
    unsigned int hsum = 0 ;

    for( i = 0 ; i < strlen( hname ) ; i++ ) {
	hsum += ( unsigned int ) hname[i] ;
    }
    hsum %= 3001 ;
    if( (hptr = hashtab[hsum]) == (HASHPTR) NULL ) {
	return(0) ;
    } else {
	for( ; ; ) {
	    if( strcmp( hname , hptr->hname ) == 0 ) {
		return( hptr->hnum ) ;
	    }
	    if( hptr->hnext == (HASHPTR) NULL ) {
		return(0) ;
	    } else {
		hptr = hptr->hnext ;
	    }
	}
    }
}
