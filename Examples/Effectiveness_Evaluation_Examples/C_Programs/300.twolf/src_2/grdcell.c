#include "standard.h"
extern int one_pin_feedthru ;
extern int *top_row_for_this_net ;
extern int *bot_row_for_this_net ;
extern int gate_array_special ;
extern int pin_layers_given ;
extern char cktName[] ;
extern int fdthrus  ;
extern int maxterm ;
int move()  ;
int rect()  ;
int point() ;
extern char **pinnames ;

typedef struct ipbox {
    struct ipbox *npin ;
    int ixpos ;
    int iypos ;
    int layer ;
    char *ipname ;
} IPBOX , *IPBOXPTR ;

typedef struct ibox {
    struct ibox *niptr ;
    int iactive ;
    int aveXpos ;
    int icell ;
    IPBOXPTR iptr ;
} IBOX , *IBOXPTR ;
extern IBOXPTR *impFeeds ;

typedef struct impbox {
    int x ;
    struct impbox *next_pin ;
} IMPBOX ;

typedef struct celltype {
    struct celltype *next_cell ;
    char *name ;
    struct impbox *first_imp ;
} CELLTYPE ;

CELLTYPE *head_type , *active_cell_type ;
IMPBOX *pin_ptr ;
int active_type ;


grdcell( fp )
FILE *fp ;
{

int i , cell , orient , corient ;
int block , left , right , bottom , top ;
int xpos , ypos , pinctr , netx ;
int from , pick_top_pin , hack_off_a_pin ;
int terms , net ;
int extint , layer ;
char input[1024] ;
char netname[1024] ;
char pname[1024] ;
double space ;
CBOXPTR ptr ;
TIBOXPTR tile , tptr ;
TEBOXPTR term , tmptr ;
NBOXPTR netptr , termptr , saveptr ;



gparser( fp ) ;  

impFeeds = (IBOXPTR *) safe_malloc( (numRows + 1) * sizeof( IBOXPTR ) ) ;
for( i = 1 ; i <= numRows ; i++ ) {
    impFeeds[i] = (IBOXPTR) NULL ;
}

cell   = 0 ;
terms  = 0 ;
pinctr = 0 ;
extint = 0 ;

while( fscanf( fp , " %s " , input ) == 1 ) {

    if( strcmp( input , "cell") == 0 ) {
	    
	cell++ ;
	ptr = carray[ cell ] ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %s " , input ) ; /* The type of a GA cell */
	if( gate_array_special ) {
	    active_type = add_type( input ) ;
	}

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

	tile = ptr->tileptr ;
	fscanf( fp , " %d " , &left ) ;

    } else if( strcmp( input , "right") == 0 ) {

	fscanf( fp , " %d " , &right ) ;

    } else if( strcmp( input , "bottom") == 0 ) {

	fscanf( fp , " %d " , &bottom ) ;

    } else if( strcmp( input , "top") == 0 ) {

	fscanf( fp , " %d " , &top ) ;

    } else if( strcmp( input , "pin") == 0 ) {

	fscanf( fp , " %s " , input ) ; /* "name"   */
	fscanf( fp , " %s " , input ) ; /* pin name */
	strcpy( pname , input ) ;
	fscanf( fp , " %s " , input ) ; /* "signal" */
	fscanf( fp , " %s " , input ) ; /* signal name */
	strcpy( netname , input ) ;
	if( strcmp( netname , "TW_PASS_THRU" ) != 0 ) {
	    pinctr++ ;
	    extint++ ;
	    pinnames[pinctr] = (char *) safe_malloc(
			    (strlen( pname ) + 1) * sizeof( char ) ) ;
	    sprintf( pinnames[pinctr] , "%s" , pname ) ;
	    netx = hashfind( input ) ;

	    if( ++ptr->numterms == 1 ) {
		term = tile->termsptr = (TEBOXPTR) safe_malloc(
						sizeof( TEBOX ) ) ;
	    } else {
		term = term->nextterm = (TEBOXPTR) safe_malloc( 
						   sizeof( TEBOX ) ) ;
	    }
	    term->nextterm = TERMNULL ;
	    term->cellterm = pinctr ;
	    term->ei = extint ;
	    term->ue = 0 ;

	    saveptr = netarray[ netx ]->netptr ;
	    netptr = netarray[ netx ]->netptr = (NBOXPTR) 
					     safe_malloc( sizeof( NBOX ) ) ;
	    netptr->nterm    = saveptr ;
	    netptr->terminal = pinctr ;
	    if( terms == 0 ) {
		netptr->cell = cell ;
	    }
	    netptr->net      = netx ;
	    netptr->xpos     = 0    ;
	    netptr->ypos     = 0    ;
	    netptr->newx     = 0    ;
	    netptr->newy     = 0    ;
	    netptr->flag     = 0    ;
	    netptr->unequiv  = 0    ;
	    if( pin_layers_given != 0 ) {
		fscanf( fp , " %s " , input ) ; /* "layer" */
		fscanf( fp , " %d " , &layer ) ; /* layer number */
	    } else {
		layer = 1 ;
	    }
	    fscanf( fp , " %d %d " , &xpos , &ypos ) ;
	    netptr->layer = layer - 1 ;
	    term->txpos[0] = xpos ;
	    term->typos[0] = ypos ;
	} else {
	    if( pin_layers_given != 0 ) {
		fscanf( fp , " %s " , input ) ; /* "layer" */
		fscanf( fp , " %d " , &layer ) ; /* layer number */
	    } else {
		layer = 1 ;
	    }
	    fscanf( fp , " %d %d " , &xpos , &ypos ) ;
	    if( one_pin_feedthru ) {
		buildimp( cell , xpos , top    , pname , 1 , layer-1 ) ;
		buildimp( cell , xpos , bottom , pname , 0 , layer-1 ) ;
	    } else {
		buildimp( cell , xpos , ypos , pname , 1 , layer - 1 ) ;
	    }
	    if( gate_array_special && active_type ) {
		add_pin( xpos ) ;
	    }
	}

    } else if( strcmp( input , "equiv") == 0 ) {

	fscanf( fp , " %s " , input ) ; /* "name"   */
	fscanf( fp , " %s " , input ) ; /* pin name */
	strcpy( pname , input ) ;
	if( pin_layers_given != 0 ) {
	    fscanf( fp , " %s " , input ) ; /* "layer" */
	    fscanf( fp , " %d " , &layer ) ; /* layer number */
	} else {
	    layer = 1 ;
	}
	fscanf( fp , " %d %d " , &xpos , &ypos ) ;
	if( strcmp( netname , "TW_PASS_THRU" ) != 0 ) {
	    pinctr++ ;
	    pinnames[pinctr] = (char *) safe_malloc(
		    (strlen( pname ) + 1) * sizeof( char ) ) ;
	    sprintf( pinnames[pinctr] , "%s" , pname ) ;
	    ++ptr->numterms ;
	    term = term->nextterm = (TEBOXPTR) safe_malloc( 
						   sizeof( TEBOX ) ) ;
	    term->nextterm = TERMNULL ;
	    term->cellterm = pinctr ;
	    term->ei = extint ;
	    term->ue = 0 ;

	    saveptr = netarray[ netx ]->netptr ;
	    netptr = netarray[ netx ]->netptr = (NBOXPTR) 
					 safe_malloc( sizeof( NBOX ) ) ;
	    netptr->nterm    = saveptr ;
	    netptr->terminal = pinctr ;
	    netptr->net      = netx ;
	    if( terms == 0 ) {
		netptr->cell = cell ;
	    }
	    netptr->xpos     = 0    ;
	    netptr->ypos     = 0    ;
	    netptr->newx     = 0    ;
	    netptr->newy     = 0    ;
	    netptr->flag     = 0    ;
	    netptr->unequiv  = 0    ;
	    netptr->layer    = layer - 1 ;
	    term->txpos[0]   = xpos ;
	    term->typos[0]   = ypos ;
	} else {
	    buildimp( cell , xpos , ypos , pname , 0 , layer - 1 ) ;
	}

    } else if( strcmp( input , "unequiv") == 0 ) {

	fscanf( fp , " %s " , input ) ; /* "name"   */
	fscanf( fp , " %s " , input ) ; /* pin name */
	strcpy( pname , input ) ;
	if( pin_layers_given != 0 ) {
	    fscanf( fp , " %s " , input ) ; /* "layer" */
	    fscanf( fp , " %d " , &layer ) ; /* layer number */
	} else {
	    layer = 1 ;
	}
	fscanf( fp , " %d %d " , &xpos , &ypos ) ;

	hack_off_a_pin = NO ;
	if( netarray[netx]->numpins >= 10 ) {
	    hack_off_a_pin = YES ;
	    if( top_row_for_this_net[netx] % 2 == 0 ) {
		    /* pick bot pins for even rows, unless bot row */
		if( carray[cell]->cblock != 
				    bot_row_for_this_net[netx] ) {
		    if( carray[cell]->cblock % 2 == 0 ) {
			pick_top_pin = NO  ;
		    } else {
			pick_top_pin = YES ;
		    }
		} else {
		    pick_top_pin = YES ;
		}
	    } else {  /* pick bot pins for odd rows, unless bot row */
		if( carray[cell]->cblock != 
				    bot_row_for_this_net[netx] ) {
		    if( carray[cell]->cblock % 2 == 1 ) {
			pick_top_pin = NO  ;
		    } else {
			pick_top_pin = YES ;
		    }
		} else {
		    pick_top_pin = YES ;
		}
	    }
	    if( barray[ carray[cell]->cblock ]->borient == 2 ) {
		if( pick_top_pin == NO ) {
		    pick_top_pin = YES ;
		} else {
		    pick_top_pin = NO  ;
		}
	    }
	}
	if( hack_off_a_pin == NO ) { 
	    pinctr++ ;
	    pinnames[pinctr] = (char *) safe_malloc(
		    (strlen( pname ) + 1) * sizeof( char ) ) ;
	    sprintf( pinnames[pinctr] , "%s" , pname ) ;
	    ++ptr->numterms ;
	    term->ue = 1 ;
	    term = term->nextterm = (TEBOXPTR) safe_malloc( 
					   sizeof( TEBOX ) ) ;
	    term->nextterm = TERMNULL ;
	    term->cellterm = pinctr ;
	    term->ei = extint ;
	    term->ue = 1 ;

	    saveptr = netarray[ netx ]->netptr ;
	    saveptr->unequiv = 1 ;
	    netptr = netarray[ netx ]->netptr = (NBOXPTR) 
				 safe_malloc( sizeof( NBOX ) ) ;
	    netptr->nterm    = saveptr ;
	    netptr->terminal = pinctr ;
	    netptr->net      = netx   ;
	    if( terms == 0 ) {
		netptr->cell = cell ;
	    }
	    netptr->xpos     = 0    ;
	    netptr->ypos     = 0    ;
	    netptr->newx     = 0    ;
	    netptr->newy     = 0    ;
	    netptr->flag     = 0    ;
	    netptr->unequiv  = 1    ;
	    netptr->layer    = layer - 1 ;
	    term->txpos[0]   = xpos ;
	    term->typos[0]   = ypos ;
	} else {
	    if( ypos < -1 && pick_top_pin == YES ||
				ypos > 1 && pick_top_pin == NO ) {
		continue ;
	    } else {
		sprintf( pinnames[pinctr] , "%s" , pname ) ;
		term->txpos[0] = xpos ;
		term->typos[0] = ypos ;
	    }
	}

    } else if( strcmp( input , "pad") == 0 ) {

	terms++ ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %s " , input ) ;
	ptr = carray[ numcells + terms ] ;

    } else if( strcmp( input , "orient") == 0 ) {

	fscanf( fp , " %d " , &orient ) ;

    } else if( strcmp( input , "padside") == 0 ) {

	fscanf( fp , " %s " , input ) ;
    } else if( strcmp( input , "sidespace") == 0 ) {
	fscanf( fp , " %lf " , &space ) ;
    }
}


safe_free( top_row_for_this_net ) ;

delHtab() ;

for( net = 1 ; net <= numnets ; net++ ) {
    for( netptr = netarray[ net ]->netptr ; netptr != NETNULL ;
				    netptr = netptr->nterm ) {
	tearray[ netptr->terminal ] = netptr ;
    }
}


/*
    NOW WE HAVE TO LOAD IN THE OTHER CONFIGURATIONS
*/


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

    ptr = carray[cell] ;
    tptr = ptr->tileptr ;
    move( ptr->corient ) ;
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

for( cell = 1 ; cell <= numcells ; cell++ ) {
    ptr = carray[cell] ;
    tile = ptr->tileptr ;
    corient = ptr->corient ;
    for( term = tile->termsptr ; term != TERMNULL ; 
			    term = term->nextterm ) {
	termptr = tearray[ term->cellterm ] ;
	termptr->xpos = term->txpos[corient/2] + ptr->cxcenter ;
	termptr->ypos = term->typos[corient%2] + ptr->cycenter ;
    }
}
for( cell = numcells + 1  ; cell <= numcells + numterms ; cell++ ) {
    ptr = carray[cell] ;
    tile = ptr->tileptr ;
    for( term = tile->termsptr ; term != TERMNULL ; 
			    term = term->nextterm ) {
	termptr = tearray[ term->cellterm ] ;
	termptr->xpos = term->txpos[1] + ptr->cxcenter ;
	termptr->ypos = term->typos[1] + ptr->cycenter ;
    }
}


return ;
}


add_type( type )
char *type ;
{

CELLTYPE *cell_ptr ;

if( head_type == NULL ) {
    head_type = (CELLTYPE *) safe_malloc( sizeof( CELLTYPE ) ) ;
    head_type->next_cell = NULL ;
    head_type->first_imp = NULL ;

    head_type->name = (char *) safe_malloc(
			(strlen(type) + 1) * sizeof( char ) ) ;
    sprintf( head_type->name , "%s" , type ) ;
    pin_ptr = NULL ;
    active_cell_type = head_type ;
    return(1) ;
} else {
    cell_ptr = head_type ;
    for( ; ; ) {
	if( strcmp( cell_ptr->name, type ) == 0 ) {
	    return(0) ;
	}
	if( cell_ptr->next_cell != NULL ) {
	    cell_ptr = cell_ptr->next_cell ;
	} else {
	    cell_ptr->next_cell = (CELLTYPE *) 
				    safe_malloc(sizeof(CELLTYPE));
	    cell_ptr->next_cell->next_cell = NULL ;
	    cell_ptr->next_cell->first_imp = NULL ;
	    cell_ptr->next_cell->name = (char *) safe_malloc(
			(strlen(type) + 1) * sizeof( char ) ) ;
	    sprintf( cell_ptr->next_cell->name , "%s" , type ) ;
	    pin_ptr = NULL ;
	    active_cell_type = cell_ptr->next_cell ;
	    return(1) ;
	}
    }
}
}




add_pin( x )
int x ;
{

if( pin_ptr == NULL ) {
    pin_ptr = active_cell_type->first_imp = 
			    (IMPBOX *) safe_malloc(sizeof(IMPBOX));
} else {
    pin_ptr = pin_ptr->next_pin = (IMPBOX *) safe_malloc(sizeof(IMPBOX));
}
pin_ptr->x = x ;
pin_ptr->next_pin = NULL ;

return ;
}



find_imp_x( name , x )
char *name ;
int x ;
{

if( strcmp( "twfeed" , name ) == 0 ) {
    if( x < 0 ) {
	return( 0 ) ;
    } else {
	return( - fdWidth / 2 ) ;
    }
}

active_cell_type = head_type ;
for( ; ; ) {
    if( active_cell_type == NULL ) {
	fprintf(fpo,"Failed to find implicit type\n");
	printf("Failed to find implicit type: <%s>\n", name);
	fflush(stdout);
	exit(TW_FAIL) ;
    }
    if( strcmp( active_cell_type->name , name ) == 0 ) {
	break ;
    }
    active_cell_type = active_cell_type->next_cell ;
}

pin_ptr = active_cell_type->first_imp ;
for( ; ; ) {
    if( pin_ptr == NULL ) {
	fprintf(fpo,"Failed to find implicit pin\n");
	printf("Failed to find implicit pin at x=<%d>\n", x);
	fflush(stdout);
	exit(TW_FAIL) ;
    }
    if( pin_ptr->x == x ) {
	break ;
    }
    pin_ptr = pin_ptr->next_pin ;
}

if( pin_ptr->next_pin == NULL ) {
    return( active_cell_type->first_imp->x ) ;
} else {
    return( - pin_ptr->next_pin->x ) ;
}
	
}
