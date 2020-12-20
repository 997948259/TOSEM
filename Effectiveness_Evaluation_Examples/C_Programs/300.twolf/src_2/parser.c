#include "standard.h"
extern int pin_layers_given ;
int celllen ;
extern FILE *fpo ;
extern int maxterm ;
extern int numnets ;
int *fixLRBT ;
double *padspace ;

parser( fp )
FILE *fp ;
{

DBOXPTR nptr ;
int cell , test , layer ;
int block , left , right , bottom , top ;
int xpos , ypos , orient ;
int from , orderchk ;
int length , terms ;
int term , i , pinctr ;
double space ;
char input[1024] ;


celllen = 0 ; 
cell = 0 ;
terms = 0 ;
pinctr = 0 ;

maketabl() ;



while( fscanf( fp , " %s " , input ) == 1 ) {

    if( strcmp( input , "cell") == 0 ) {
	cell++ ;
	orderchk = 0 ;
	test = fscanf( fp , " %s " , input ) ;
	if( test != 1 ) {
	    fprintf( fpo, "Failed to input dummy cell number/name ");
	    fprintf( fpo, "in the .cel file\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL);
	}
	fscanf( fp , " %s " , input ) ;

    } else if( strcmp( input , "left") == 0 ) {
	test = fscanf( fp , " %d " , &left ) ;
	if( test != 1 ) {
	    fprintf( fpo, "Failed to input left ");
	    fprintf( fpo, "in the .cel file\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL);
	}
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "right") == 0 ) {
	    test = fscanf( fp , " %d " , &right ) ;
	    if( test != 1 ) {
		fprintf( fpo, "Failed to input right ");
		fprintf( fpo, "in the .cel file\n");
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	} else {
	    fprintf( fpo, "Failed to find keyword right ");
	    fprintf( fpo, "for a cell\n") ;
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "bottom") == 0 ) {
	    test = fscanf( fp , " %d " , &bottom ) ;
	    if( test != 1 ) {
		fprintf( fpo, "Failed to input bottom ");
		fprintf( fpo, "in the .cel file\n");
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	} else {
	    fprintf( fpo, "Failed to find keyword bottom ");
	    fprintf( fpo, "for a cell\n") ;
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "top") == 0 ) {
	    test = fscanf( fp , " %d " , &top ) ;
	    if( test != 1 ) {
		fprintf( fpo,"Failed to input top ");
		fprintf( fpo,"in the .cel file\n");
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	} else {
	    fprintf( fpo, "Failed to find keyword top ");
	    fprintf( fpo, "for a cell\n") ;
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	if( right + left != 0  &&  right + left != 1 || left > 0 ) {
	    fprintf( fpo, "The given center of the cell ");
	    fprintf( fpo, "is not (right + left) div 2\n");
	    fprintf( fpo, "Where the remainder is truncated\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	if( top + bottom != 0 && top + bottom != 1 || bottom > 0 ) {
	    fprintf( fpo, "The given center of the cell ");
	    fprintf( fpo, "is not (top + bottom) div 2\n");
	    fprintf( fpo, "Where the remainder is truncated\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	length = right - left ;
	celllen += length ;

    } else if( strcmp( input , "initially") == 0 ) {
	if( orderchk != 0 ) {
	    fprintf(fpo,"cannot preplace fixed sequence\n");
	    fprintf( fpo, "in the .cel file\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL);
	}
	orderchk = 1 ;
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "fixed") == 0 ) {
	} else if( strcmp( input , "nonfixed") == 0 ) {
	} else {
	    fprintf( fpo, "Failed to find fixed or nonfixed\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	test = fscanf( fp , " %d " , &from ) ;
	if( test != 1 ) {
	    fprintf(fpo,"Failed to input amount from following ");
	    fprintf(fpo,"(fixed,nonfixed) in the .cel file");
	    fprintf(fpo,"Current cell: %d\n", cell ) ;
	    exit(TW_FAIL);
	}
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "from") != 0 ) {
	    fprintf( fpo, "Failed to find keyword from ");
	    fprintf( fpo, "in the .cel file");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "left") == 0 ) {
	} else if( strcmp( input , "right") == 0 ) {
	} else {
	    fprintf( fpo, "Failed to find left or right\n");
	    fprintf( fpo, "following from in the .cel file");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "of") != 0 ) {
	    fprintf( fpo, "Failed to find keyword of ");
	    fprintf( fpo, "in the .cel file");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "block") != 0 ) {
	    fprintf( fpo, "Failed to find keyword block ");
	    fprintf( fpo, "in the .cel file");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	test = fscanf( fp , " %d " , &block ) ;
	if( test != 1 ) {
	    fprintf(fpo,"Failed to input amount from following ");
	    fprintf(fpo,"(fixed,nonfixed) in the .cel file");
	    fprintf(fpo,"Current cell: %d\n", cell ) ;
	    exit(TW_FAIL);
	}
	
    } else if( strcmp( input , "nomirror") == 0 ) {
    } else if( strcmp( input , "pin") == 0 ) {
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "name") != 0 ) {
	    fprintf( fpo, "Failed to find keyword name ");
	    fprintf( fpo, "for a pin\n") ;
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	test = fscanf( fp , " %s " , input ) ;
	if( test != 1 ) {
	    fprintf( fpo, "Failed to input pin name ");
	    fprintf( fpo, "in the .cel file\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL);
	}
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "signal") != 0 ) {
	    fprintf( fpo, "Failed to find keyword signal ");
	    fprintf( fpo, "for a pin\n") ;
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	test = fscanf( fp , " %s " , input ) ;
	if( test != 1 ) {
	    fprintf( fpo, "Failed to input signal name ");
	    fprintf( fpo, "in the .cel file\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL);
	}
	if( strcmp( input , "TW_PASS_THRU" ) != 0 ) {
	    addhash( input ) ;
	    pinctr++ ;
	}
	if( pin_layers_given != 0 ) {
	    fscanf( fp , " %s " , input ) ;
	    if( strcmp( input , "layer") != 0 ) {
		fprintf( fpo, "Failed to find keyword layer ");
		fprintf( fpo, "for a pin\n") ;
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL) ;
	    }
	    test = fscanf( fp , " %d " , &layer ) ;
	    if( test != 1 ) {
		fprintf( fpo, "Failed to input layer number ");
		fprintf( fpo, "in the .cel file\n");
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	    if( layer != 1 && layer != 2 && layer != 3 ) {
		fprintf( fpo, "Currently, a layer number ");
		fprintf( fpo, "in the .cel file must be either 1, 2,\n");
		fprintf( fpo, "or 3.   Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	}
	test = fscanf( fp , " %d %d " , &xpos , &ypos ) ;
	if( test != 2 ) {
	    fprintf( fpo, "Failed to input 2 items ");
	    fprintf( fpo, "for pin in the .cel file\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL);
	}

    } else if( strcmp( input , "equiv") == 0 ) {
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "name") != 0 ) {
	    fprintf( fpo, "Failed to find keyword name ");
	    fprintf( fpo, "for an equiv pin\n") ;
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	test = fscanf( fp , " %s " , input ) ;
	if( test != 1 ) {
	    fprintf( fpo, "Failed to input equiv pin name ");
	    fprintf( fpo, "in the .cel file\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL);
	}
	if( pin_layers_given != 0 ) {
	    fscanf( fp , " %s " , input ) ;
	    if( strcmp( input , "layer") != 0 ) {
		fprintf( fpo, "Failed to find keyword layer ");
		fprintf( fpo, "for an equiv pin\n") ;
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL) ;
	    }
	    test = fscanf( fp , " %d " , &layer ) ;
	    if( test != 1 ) {
		fprintf( fpo, "Failed to input layer number ");
		fprintf( fpo, "in the .cel file\n");
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	    if( layer != 1 && layer != 2 && layer != 3 ) {
		fprintf( fpo, "Currently, a layer number ");
		fprintf( fpo, "in the .cel file must be either 1, 2,\n");
		fprintf( fpo, "or 3.   Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	}
	test = fscanf( fp , " %d %d " , &xpos , &ypos ) ;
	if( test != 2 ) {
	    fprintf( fpo, "Failed to input 2 items ");
	    fprintf( fpo, "for equiv in the .cel file\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL);
	}
    } else if( strcmp( input , "unequiv") == 0 ) {
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "name") != 0 ) {
	    fprintf( fpo, "Failed to find keyword name ");
	    fprintf( fpo, "for an unequiv pin\n") ;
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	test = fscanf( fp , " %s " , input ) ;
	if( test != 1 ) {
	    fprintf( fpo, "Failed to input unequiv pin name ");
	    fprintf( fpo, "in the .cel file\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL);
	}
	if( pin_layers_given != 0 ) {
	    fscanf( fp , " %s " , input ) ;
	    if( strcmp( input , "layer") != 0 ) {
		fprintf( fpo, "Failed to find keyword layer ");
		fprintf( fpo, "for an unequiv pin\n") ;
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL) ;
	    }
	    test = fscanf( fp , " %d " , &layer ) ;
	    if( test != 1 ) {
		fprintf( fpo, "Failed to input layer number ");
		fprintf( fpo, "in the .cel file\n");
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	    if( layer != 1 && layer != 2 && layer != 3 ) {
		fprintf( fpo, "Currently, a layer number ");
		fprintf( fpo, "in the .cel file must be either 1, 2,\n");
		fprintf( fpo, "or 3.   Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	}
	test = fscanf( fp , " %d %d " , &xpos , &ypos ) ;
	if( test != 2 ) {
	    fprintf( fpo, "Failed to input 2 items ");
	    fprintf( fpo, "for unequiv in the .cel file\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL);
	}
    } else if( strcmp( input , "pad") == 0 ) {
	terms++ ;
	test = fscanf( fp , " %s " , input ) ;
	if( test != 1 ) {
	    fprintf( fpo, "Failed to input dummy pad number/name ");
	    fprintf( fpo, "in the .cel file\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL);
	}
	fscanf( fp , " %s " , input ) ;

	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "orient") == 0 ) {
	    test = fscanf( fp , " %d " , &orient ) ;
	    if( test != 1 ) {
		fprintf( fpo, "Failed to input orient ");
		fprintf( fpo, "in the .cel file\n");
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	} else {
	    fprintf( fpo, "Failed to find keyword orient ");
	    fprintf( fpo, "for a pad\n") ;
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}

	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "padside") == 0 ) {
	    test = fscanf( fp , " %s " , input ) ;
	    if( test != 1 ) {
		fprintf( fpo, "Failed to input padside ");
		fprintf( fpo, "in the .cel file\n");
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	} else {
	    fprintf( fpo, "Failed to find keyword padside ");
	    fprintf( fpo, "for a pad\n") ;
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "left") == 0 ) {
	    test = fscanf( fp , " %d " , &left ) ;
	    if( test != 1 ) {
		fprintf( fpo, "Failed to input left ");
		fprintf( fpo, "in the .cel file\n");
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	} else {
	    fprintf( fpo, "Failed to find keyword left ");
	    fprintf( fpo, "for a pad\n") ;
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "right") == 0 ) {
	    test = fscanf( fp , " %d " , &right ) ;
	    if( test != 1 ) {
		fprintf( fpo, "Failed to input right ");
		fprintf( fpo, "in the .cel file\n");
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	} else {
	    fprintf( fpo, "Failed to find keyword right ");
	    fprintf( fpo, "for a pad\n") ;
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	if( right + left != 0  &&  right + left != 1 ) {
	    fprintf( fpo, "The given center of the cell ");
	    fprintf( fpo, "is not (right + left) div 2\n");
	    fprintf( fpo, "Where the remainder is truncated\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "bottom") == 0 ) {
	    test = fscanf( fp , " %d " , &bottom ) ;
	    if( test != 1 ) {
		fprintf( fpo, "Failed to input bottom ");
		fprintf( fpo, "in the .cel file\n");
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	} else {
	    fprintf( fpo, "Failed to find keyword bottom ");
	    fprintf( fpo, "for a pad\n") ;
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "top") == 0 ) {
	    test = fscanf( fp , " %d " , &top ) ;
	    if( test != 1 ) {
		fprintf( fpo,"Failed to input top ");
		fprintf( fpo,"in the .cel file\n");
		fprintf( fpo, "Current cell: %d\n", cell ) ;
		exit(TW_FAIL);
	    }
	} else {
	    fprintf( fpo, "Failed to find keyword top ");
	    fprintf( fpo, "for a pad\n") ;
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
	if( top + bottom != 0  &&  top + bottom != 1 ) {
	    fprintf( fpo, "The given center of the cell ");
	    fprintf( fpo, "is not (top + bottom) div 2\n");
	    fprintf( fpo, "Where the remainder is truncated\n");
	    fprintf( fpo, "Current cell: %d\n", cell ) ;
	    exit(TW_FAIL) ;
	}
    } else if( strcmp( input , "sidespace") == 0 ) {
	test = fscanf( fp , " %lf " , &space ) ;
    } else {
	fprintf( fpo, "Found unparsable keyword in ");
	fprintf( fpo, "the .cel file\n");
	fprintf( fpo, "Current cell: %d\n", cell ) ;
	exit(TW_FAIL) ;
    }
}
rewind( fp ) ;

numcells = cell  ;
numterms = terms ;
padspace = (double *) safe_malloc( (numterms + 1) * sizeof(double) ) ;
for( i = 1 ; i <= numterms ; i++ ) {
    padspace[i] = 0.0 ;
}
fixLRBT  = (int *) safe_malloc( 4 * sizeof( int ) ) ;
fixLRBT[0] = 0 ;
fixLRBT[1] = 0 ;
fixLRBT[2] = 0 ;
fixLRBT[3] = 0 ;

netarray = (DBOXPTR *) safe_malloc( (netctr + 1) * sizeof( DBOXPTR ) ) ;

for( i = 1 ; i <= netctr ; i++ ) {

    nptr = netarray[ i ] = (DBOXPTR) safe_malloc( sizeof( DBOX ) ) ;

    nptr->netptr  = NETNULL ;
    nptr->name    = NULL    ;
    nptr->dflag   = 0       ;
    nptr->xmin    = 0       ;
    nptr->newxmin = 0       ;
    nptr->xmax    = 0       ;
    nptr->newxmax = 0       ;
    nptr->ymin    = 0       ;
    nptr->newymin = 0       ;
    nptr->ymax    = 0       ;
    nptr->newymax = 0       ;
    nptr->Hweight = 1.0     ;
    nptr->Vweight = 1.0     ;
    nptr->feedflag = 0      ;
    nptr->ignore   = 0      ;
}
numnets = netctr ;

tearray = (NBOXPTR *)safe_malloc( (pinctr + 1) * sizeof( NBOXPTR ) );
for( term = 1 ; term <= pinctr ; term++ ) {
    tearray[ term ] = NETNULL ;
}
maxterm = pinctr ;

return ;
}
