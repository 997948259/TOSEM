#include "standard.h"
extern int pin_layers_given ;
extern int maxCellO ;
int totallen ;
int maxterm ;
int move()  ;
int rect()  ;
int point() ;
extern int celllen ;
extern FILE *fpo ;
extern double macspace[] ;
extern double *padspace ;
extern int *fixLRBT ;


readcell( fp )
FILE *fp ;
{

int cell , orient  , layer ;
int block , left , right , bottom , top ;
int xpos , ypos , from ;
int terms , pinctr , netx ;
int tot , totx , toty ;
char input[1024] ;
char netname[1024] ;
double space ;
CBOXPTR ptr ;
TIBOXPTR tile , tptr ;
TEBOXPTR term , tmptr ;
NBOXPTR netptr , saveptr ;


parser( fp ) ;  


carray = (CBOXPTR *) safe_malloc( ( 1 + numcells + 
			       numterms) * sizeof( CBOXPTR ) ) ;

for( cell = 1 ; cell <= numcells + numterms ; cell++ ) {

    ptr = carray[ cell ] = (CBOXPTR) safe_malloc( sizeof(CBOX) ) ;

    ptr->cxcenter    = 0 ;
    ptr->cycenter    = 0 ;
    ptr->cheight     = 0 ;
    ptr->clength     = 0 ;
    ptr->cblock      = 0 ;
    ptr->cclass      = 0 ;
    ptr->corient     = 0 ;
    ptr->orflag      = 1 ;
    ptr->numterms    = 0 ;
    ptr->padside     = 0 ;
    ptr->tileptr     = TILENULL ;
}

implicit_feed_count = 0 ;
cell  = 0 ;
terms = 0 ;
pinctr = 0 ;

while( fscanf( fp , " %s " , input ) == 1 ) {

    if( strcmp( input , "cell") == 0 ) {
	    
	cell++ ;
	ptr = carray[ cell ] ;
	ptr->corient  = 0       ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %s " , input ) ;
	ptr->cname = (char *) safe_malloc( (strlen( input ) + 1 ) *
					    sizeof( char ) ) ;
	sprintf( ptr->cname , "%s" , input ) ;

    } else if( strcmp( input , "nomirror") == 0 ) {
	ptr->orflag = 0 ;

    } else if( strcmp( input , "initially") == 0 ) {
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "fixed" ) == 0 ) {
	    ptr->cclass = -1 ;
	    ptr->orflag = 0 ;
	} else if( strcmp( input , "nonfixed" ) == 0 ) {
	    ptr->cclass = 0 ;
	}
	fscanf( fp , " %d " , &from ) ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "left" ) == 0 ) {
	    ptr->cxcenter = from ;
	    ptr->cycenter = 1 ;
	} else if( strcmp( input , "right" ) == 0 ) {
	    ptr->cxcenter = -from ;
	    ptr->cycenter = -1 ;
	}
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %d " , &block ) ;
	ptr->cblock = block ;

    } else if( strcmp( input , "left") == 0 ) {

	tile = ptr->tileptr = (TIBOXPTR) safe_malloc( sizeof(TIBOX) ) ;
	tile->termsptr = TERMNULL ;

	fscanf( fp , " %d " , &left ) ;
	tile->left = left ;

    } else if( strcmp( input , "right") == 0 ) {

	fscanf( fp , " %d " , &right ) ;
	tile->right = right ;

    } else if( strcmp( input , "bottom") == 0 ) {

	fscanf( fp , " %d " , &bottom ) ;
	tile->bottom = bottom ;

    } else if( strcmp( input , "top") == 0 ) {

	fscanf( fp , " %d " , &top ) ;
	tile->top = top ;
	ptr->cheight = top - bottom ;
	ptr->clength = right - left ;

    } else if( strcmp( input , "pin") == 0 ) {

	fscanf( fp , " %s " , input ) ; /* "name" */
	fscanf( fp , " %s " , input ) ; /* pin name */
	fscanf( fp , " %s " , input ) ; /* "signal" */
	fscanf( fp , " %s " , input ) ; /* signal name */
	strcpy( netname , input ) ;
	if( strcmp( input , "TW_PASS_THRU" ) != 0 ) {
	    netx = hashfind( input ) ;
	    if( netarray[netx]->name == NULL ) {
		netarray[netx]->name = (char *) safe_malloc( 
			     (strlen( input ) + 1) * sizeof( char ) ) ;
		sprintf( netarray[netx]->name , "%s" , input ) ;
	    }
	    tot = 1 ;

	    ptr->numterms++ ;

	    if( ptr->numterms == 1 ) {
		term = ptr->tileptr->termsptr = (TEBOXPTR) 
					safe_malloc( sizeof( TEBOX ) ) ;
	    } else {
		term = term->nextterm = (TEBOXPTR) safe_malloc( 
						   sizeof( TEBOX ) ) ;
	    }
	    term->nextterm = TERMNULL ;
	    term->cellterm = ++pinctr ;
	    term->ue = 0 ;

	    saveptr = netarray[ netx ]->netptr ;
	    netptr = netarray[ netx ]->netptr = (NBOXPTR) 
				     safe_malloc( sizeof( NBOX ) ) ;
	    netptr->nterm    = saveptr ;
	    netptr->terminal = pinctr ;
	    netptr->net      = netx ;
	    netptr->xpos     = 0    ;
	    netptr->ypos     = 0    ;
	    netptr->newx     = 0    ;
	    netptr->newy     = 0    ;
	    netptr->flag     = 0    ;
	    netptr->cell     = cell + terms ;

	    if( pin_layers_given != 0 ) {
		fscanf( fp , " %s " , input ) ; /* "layer" */
		fscanf( fp , " %d " , &layer ) ; /* layer number */
	    }
	    fscanf( fp , " %d %d " , &xpos , &ypos ) ;
	    totx = xpos ;
	    toty = ypos ;
	    term->txpos[0] = xpos ;
	    term->typos[0] = ypos ;
	} else {
	    implicit_feed_count++ ;
	    if( pin_layers_given != 0 ) {
		fscanf( fp , " %s " , input ) ; /* "layer" */
		fscanf( fp , " %d " , &layer ) ; /* layer number */
	    }
	    fscanf( fp , " %d %d " , &xpos , &ypos ) ;
	}

    } else if( strcmp( input , "equiv") == 0 ) {

	fscanf( fp , " %s " , input ) ; /* "name" */
	fscanf( fp , " %s " , input ) ; /* pin name */
	if( pin_layers_given != 0 ) {
	    fscanf( fp , " %s " , input ) ; /* "layer" */
	    fscanf( fp , " %d " , &layer ) ; /* layer number */
	}
	fscanf( fp , " %d %d " , &xpos , &ypos ) ;
	if( strcmp( netname , "TW_PASS_THRU" ) != 0 ) {
	    tot++ ;
	    totx += xpos ;
	    toty += ypos ;
	    term->txpos[0] = totx / tot ;
	    if( terms == 0 ) {
		term->typos[0] = 0 ;
	    } else {
		term->typos[0] = toty / tot ;
	    }
	}

    } else if( strcmp( input , "unequiv") == 0 ) {

	fscanf( fp , " %s " , input ) ; /* "name" */
	fscanf( fp , " %s " , input ) ; /* pin name */
	if( pin_layers_given != 0 ) {
	    fscanf( fp , " %s " , input ) ; /* "layer" */
	    fscanf( fp , " %d " , &layer ) ; /* layer number */
	}
	fscanf( fp , " %d %d " , &xpos , &ypos ) ;
	tot++ ;
	totx += xpos ;
	term->txpos[0] = totx / tot ;
	term->typos[0] = 0 ;
	term->ue = 1 ;

    } else if( strcmp( input , "pad") == 0 ) {

	terms++ ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %s " , input ) ;
	ptr = carray[ numcells + terms ] ;
	ptr->cname = (char *) safe_malloc( (strlen( input ) + 1 ) *
					    sizeof( char ) ) ;
	sprintf( ptr->cname , "%s" , input ) ;
	ptr->cclass = 0 ;
	ptr->orflag = 0 ;

    } else if( strcmp( input , "orient") == 0 ) {

	fscanf( fp , " %d " , &orient ) ;
	ptr->corient = orient ;

    } else if( strcmp( input , "padside") == 0 ) {

	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "L" ) == 0 ) {
	    ptr->padside = 1 ;
	} else if( strcmp( input , "T" ) == 0 ) {
	    ptr->padside = 2 ;
	} else if( strcmp( input , "R" ) == 0 ) {
	    ptr->padside = 3 ;
	} else if( strcmp( input , "B" ) == 0 ) {
	    ptr->padside = 4 ;
	} else if( strcmp( input , "MUL" ) == 0 ) {
	    ptr->padside = 5 ;
	} else if( strcmp( input , "MUR" ) == 0 ) {
	    ptr->padside = 6 ;
	} else if( strcmp( input , "MLL" ) == 0 ) {
	    ptr->padside = 7 ;
	} else if( strcmp( input , "MLR" ) == 0 ) {
	    ptr->padside = 8 ;
	} else if( strcmp( input , "ML" ) == 0 ) {
	    ptr->padside = 9 ;
	} else if( strcmp( input , "MR" ) == 0 ) {
	    ptr->padside = 10 ;
	} else if( strcmp( input , "MB" ) == 0 ) {
	    printf("macro at position MB is no longer supported -- sorry!\n");
	    exit( TW_FAIL ) ;
	    ptr->padside = 11 ;
	} else if( strcmp( input , "MT" ) == 0 ) {
	    printf("macro at position MT is no longer supported -- sorry!\n");
	    exit( TW_FAIL ) ;
	    ptr->padside = 12 ;
	} else if( strcmp( input , "MM" ) == 0 ) {
	    printf("macro at position MM is no longer supported -- sorry!\n");
	    exit( TW_FAIL ) ;
	    ptr->padside = 13 ;
	} else if( strcmp( input , "MTT" ) == 0 ) {
	    ptr->padside = 14 ;
	} else if( strcmp( input , "MBB" ) == 0 ) {
	    ptr->padside = 15 ;
	} else {
	    fprintf(fpo,"padside not specified properly for ");
	    fprintf(fpo,"pad: %s\n", ptr->cname ) ;
	    exit(TW_FAIL);
	}
    } else if( strcmp( input , "sidespace") == 0 ) {
	fscanf( fp , " %lf " , &space ) ;
	if( ptr->padside == 1 ) {
	    fixLRBT[0] = 1 ;	
	    padspace[ terms ] = space ;
	} else if( ptr->padside == 3 ) {
	    fixLRBT[1] = 1 ;	
	    padspace[ terms ] = space ;
	} else if( ptr->padside == 4 ) {
	    fixLRBT[2] = 1 ;	
	    padspace[ terms ] = space ;
	} else if( ptr->padside == 2 ) {
	    fixLRBT[3] = 1 ;	
	    padspace[ terms ] = space ;
	} else {
	    macspace[ ptr->padside ] = space ;
	}
    }
}



/*
    NOW WE HAVE TO LOAD IN THE OTHER CONFIGURATIONS
*/
for( cell = 1 ; cell <= numcells ; cell++ ) {
    if( carray[cell]->orflag == 1 ) {
	if( maxCellO == 0 ) {
	    maxCellO = 2 ;
	} else if( maxCellO == 1 ) {
	    maxCellO = 3 ;
	} 
	break ;
    }
}


for( cell = 1 ; cell <= numcells ; cell++ ) {

    ptr = carray[ cell ] ;
    tptr = ptr->tileptr ;

    for( tmptr = tptr->termsptr ; tmptr != TERMNULL ;
				    tmptr = tmptr->nextterm ) {
	if( ( ptr->clength %2 != 0 ) ) {
	    tmptr->txpos[1] = -tmptr->txpos[0] + 1 ;
	} else {
	    tmptr->txpos[1] = -tmptr->txpos[0] ;
	}
	if( ( ptr->cheight %2 != 0 ) ) {
	    tmptr->typos[1] = -tmptr->typos[0] + 1 ;
	} else {
	    tmptr->typos[1] = -tmptr->typos[0] ;
	}
    }

}

for( cell = numcells + 1 ; cell <= numcells + numterms ; cell++ ) {
    
    ptr = carray[ cell ] ;
    tptr = ptr->tileptr ;
    orient = ptr->corient ;
    move( orient ) ;
    rect( &tptr->left , &tptr->bottom , &tptr->right ,
						&tptr->top ) ;
    if( (ptr->cheight % 2 != 0 && (orient == 4 || orient == 6))||
	(ptr->clength % 2 != 0 && (orient == 2 || orient == 3))){
	tptr->left++ ;
	tptr->right++ ;
    }
    if( (ptr->cheight % 2 != 0 && (orient == 1 || orient == 3))||
	(ptr->clength % 2 != 0 && (orient == 4 || orient == 7))){
	tptr->bottom++ ;
	tptr->top++ ;
    }

    for( tmptr = tptr->termsptr ; tmptr != TERMNULL ;
				    tmptr = tmptr->nextterm ) {
	tmptr->txpos[1] = tmptr->txpos[0] ;
	tmptr->typos[1] = tmptr->typos[0] ;
	point( &tmptr->txpos[1] , &tmptr->typos[1] ) ;
	if( (ptr->cheight % 2 != 0 && (orient == 4 || orient == 6))||
	    (ptr->clength % 2 != 0 && (orient == 2 || orient == 3))){
	    tmptr->txpos[1]++ ; 
	}
	if( (ptr->cheight % 2 != 0 && (orient == 1 || orient == 3))||
	    (ptr->clength % 2 != 0 && (orient == 4 || orient == 7))){
	    tmptr->typos[1]++ ;
	}
    }
}

/* 
 *   Configure the blocks, place the macro blocks and pads.
 *   Also generate an initial placement of the standard cells
 */

configure() ;
carray = (CBOXPTR *) safe_realloc( carray, (1 + numcells + numterms) *
						sizeof( CBOXPTR ) ) ;

for( block = 1 ; block <= numblock ; block++ ) {
    totallen += barray[ block ]->blength ;
}
fprintf( fpo, "total cell length: %d\n", celllen ) ;
fprintf( fpo, "total block length: %d\n", totallen ) ;

return ;
}
