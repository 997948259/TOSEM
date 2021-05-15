#include "standard.h"
int *top_row_for_this_net ;
int *bot_row_for_this_net ;
extern int pin_layers_given ;
extern FILE *fpo ;
char **pinnames ;
extern int fdthrus ;
extern int maxterm ;
extern int numnets ;

gparser( fp )
FILE *fp ;
{


int cell , term , pinctr , i , layer ;
int block , left , right , bottom , top ;
int xpos , ypos , orient ;
int from ;
double space ;
char input[1024] ;
char netname[1024] ;
NBOXPTR nptr , zapptr ;
CBOXPTR ptr ;
TEBOXPTR cptr , koptr ;


cell = 0 ;
pinctr = 0 ;
netctr = 0 ;


maketabl() ;

while( fscanf( fp , " %s " , input ) == 1 ) {

    if( strcmp( input , "cell") == 0 ) {
	cell++ ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %d " , &block ) ;
    } else if( strcmp( input , "initially") == 0 ) {
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %d " , &from ) ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %d " , &block ) ;
    } else if( strcmp( input , "nomirror") == 0 ) {
    } else if( strcmp( input , "left") == 0 ) {
	fscanf( fp , " %d " , &left ) ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %d " , &right ) ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %d " , &bottom ) ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %d " , &top ) ;
    } else if( strcmp( input , "pin") == 0 ) {
	fscanf( fp , " %s " , input ) ; /* "name"   */
	fscanf( fp , " %s " , input ) ; /* pin name */
	fscanf( fp , " %s " , input ) ; /* signal   */
	fscanf( fp , " %s " , input ) ; /* signal name */
	strcpy( netname , input ) ;
	if( strcmp( input , "TW_PASS_THRU" ) != 0 ) {
	    pinctr++ ;
	    addhash( input ) ;
	}
	if( pin_layers_given != 0 ) {
	    fscanf( fp , " %s " , input ) ; /* layer   */
	    fscanf( fp , " %d " , &layer ) ; /* layer number */
	}
	fscanf( fp , " %d %d " , &xpos , &ypos ) ;
    } else if( strcmp( input , "equiv") == 0 ) {
	fscanf( fp , " %s " , input ) ; /* "name"   */
	fscanf( fp , " %s " , input ) ; /* pin name */
	if( pin_layers_given != 0 ) {
	    fscanf( fp , " %s " , input ) ; /* layer   */
	    fscanf( fp , " %d " , &layer ) ; /* layer number */
	}
	fscanf( fp , " %d %d " , &xpos , &ypos ) ;
	if( strcmp( netname , "TW_PASS_THRU" ) != 0 ) {
	    pinctr++ ;
	}
    } else if( strcmp( input , "unequiv") == 0 ) {
	fscanf( fp , " %s " , input ) ; /* "name"   */
	fscanf( fp , " %s " , input ) ; /* pin name */
	if( pin_layers_given != 0 ) {
	    fscanf( fp , " %s " , input ) ; /* layer   */
	    fscanf( fp , " %d " , &layer ) ; /* layer number */
	}
	fscanf( fp , " %d %d " , &xpos , &ypos ) ;
	pinctr++ ;
    } else if( strcmp( input , "pad") == 0 ) {
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %s " , input ) ;

	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %d " , &orient ) ;

	fscanf( fp , " %s " , input ) ;  /* keyword padside */
	fscanf( fp , " %d " , input ) ;  /* padside designation */
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %d " , &left ) ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %d " , &right ) ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %d " , &bottom ) ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %d " , &top ) ;
    } else if( strcmp( input , "sidespace") == 0 ) {
	fscanf( fp , " %lf " , &space ) ;
    } 
}


rewind( fp ) ;

top_row_for_this_net = (int *) safe_malloc(
			(numnets + 1) * sizeof(int) ) ;
bot_row_for_this_net = (int *) safe_malloc(
			(numnets + 1) * sizeof(int) ) ;
for( i = 1 ; i <= numnets ; i++ ) {
    top_row_for_this_net[i] = -1 ;
    bot_row_for_this_net[i] = 10000000 ;
}
insert_row(1) ;
for( i = 1 ; i <= numnets ; i++ ) {
    nptr = netarray[i]->netptr ;
    for( ; nptr ; nptr = nptr->nterm ) {
	if( nptr->row > top_row_for_this_net[i] ) {
	    top_row_for_this_net[i] = nptr->row ;
	}
	if( nptr->row < bot_row_for_this_net[i] ) {
	    bot_row_for_this_net[i] = nptr->row ;
	}
    }
}

for( i = 1 ; i <= numnets ; i++ ) {
    nptr = netarray[ i ]->netptr ; 
    netarray[i]->netptr = NETNULL ;
    if( nptr != NETNULL ) {
	zapptr = nptr ;
	while( nptr->nterm != NETNULL ) {
	    nptr = nptr->nterm ;
	    safe_free( zapptr ) ;
	    zapptr = nptr ;
	}
	safe_free( nptr ) ;
    }
}

safe_free( tearray ) ;

tearray = (NBOXPTR *) safe_malloc( (pinctr + 1 ) * sizeof( NBOXPTR ) );
for( term = 1 ; term <= pinctr ; term++ ) {
    tearray[ term ] = NETNULL ;
}
maxterm = pinctr ;
pinnames = (char **) safe_malloc( (pinctr + 1) * sizeof( char * ) ) ;

for( cell = 1 ; cell <= numcells + numterms ; cell++ ) {
    ptr = carray[cell] ;
    ptr->numterms = 0 ;
    cptr = ptr->tileptr->termsptr ;
    ptr->tileptr->termsptr = TERMNULL ;
    if( cptr != TERMNULL ) {
	koptr = cptr ;
	while( cptr->nextterm != TERMNULL ) {
	    cptr = cptr->nextterm ;
	    safe_free( koptr ) ;
	    koptr = cptr ;
	}
	safe_free( cptr ) ;
    }
}
return ;
}
