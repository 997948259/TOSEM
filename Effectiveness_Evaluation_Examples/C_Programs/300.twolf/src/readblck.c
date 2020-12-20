#include "standard.h"
extern FILE *fpo ;
int *nofeed ;
double *relativeLen ;

readblck( fp )
FILE *fp ;

{

int test , block , class , height , row ;
double relLen ;
char input[32] ;

block = 0 ;

while( fscanf( fp , " %s " , input ) == 1 ) {

    if( strcmp( input , "block") == 0 ) {
	block++ ;
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "height") == 0 ) {
	    test = fscanf( fp , " %d " , &height ) ;
	    if( test != 1 ) {
		fprintf( fpo,"Failed to input height of a block\n");
		fprintf( fpo,"at position height\n");
		exit(TW_FAIL);
	    }
	} else {
	    fprintf(fpo,"unexpected keyword in the .blk file\n");
	    fprintf( fpo, "at position height\n");
	    fprintf( fpo, "current block: %d\n", block );
	    exit(TW_FAIL);
	}
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "class") == 0 ) {
	    test = fscanf( fp , " %d " , &class ) ;
	    if( test != 1 ) {
		fprintf( fpo, "Failed to input class of a block\n");
		fprintf( fpo, "current block: %d\n", block );
		exit(TW_FAIL);
	    }
	} else {
	    fprintf( fpo, "unexpected keyword in the .blk file\n");
	    fprintf( fpo, "at position class\n");
	    fprintf( fpo, "current block: %d\n", block );
	    exit(TW_FAIL);
	}
    } else if( strcmp( input , "mirror") == 0 ) {
    } else if( strcmp( input , "nofeeds") == 0 ) {
    } else if( strcmp( input , "relative_length") == 0 ) {
	test = fscanf( fp , " %f " , &relLen ) ;
    } else {
	fprintf( fpo, "unexpected keyword in the .blk file\n");
	fprintf( fpo, "current block: %d\n", block );
	exit(TW_FAIL);
    }
}
numblock = block ;

rewind( fp ) ;

barray = (BBOXPTR *) safe_malloc( (numblock + 1) * sizeof( BBOXPTR ) ) ;
nofeed = (int *) safe_malloc( ( numblock + 2 ) * sizeof( int ) ) ;
for( row = 0 ; row <= numblock + 1 ; row++ ) {
    nofeed[row] = 0 ;
}

relativeLen = (double *) safe_malloc( (numblock + 1) * sizeof( double ) ) ;
for( block = 1 ; block <= numblock ; block++ ) {
    relativeLen[block] = 1.0 ;
}

for( block = 1 ; block <= numblock ; block++ ) {
    
    barray[ block ] = (BBOXPTR) safe_malloc( sizeof( BBOX ));
    barray[ block ]->bxcenter = 0 ;
    barray[ block ]->bycenter = 0 ;
    barray[ block ]->bleft    = 0 ;
    barray[ block ]->bright   = 0 ;
    barray[ block ]->bbottom  = 0 ;
    barray[ block ]->btop     = 0 ;
    barray[ block ]->bheight  = 0 ;
    barray[ block ]->blength  = 0 ;
    barray[ block ]->bclass   = 0 ;
    barray[ block ]->borient  = 0 ;
    barray[ block ]->desire   = 0 ;
    barray[ block ]->oldsize  = 0 ;
    barray[ block ]->newsize  = 0 ;
}

block = 0 ;

while( fscanf( fp , " %s " , input ) == 1 ) {

    if( strcmp( input , "block" ) == 0 ) {
	block++ ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %d " , &height ) ;
	barray[block]->btop    = height - height / 2 ;
	barray[block]->bbottom = - height / 2 ;
	barray[block]->bheight = height ;
	fscanf( fp , " %s " , input ) ;
	fscanf( fp , " %d " , &class ) ;
	barray[block]->bclass = class ;
	barray[block]->borient = 1 ;
    } else if( strcmp( input , "mirror" ) == 0 ) {
	barray[block]->borient = 2 ;
    } else if( strcmp( input , "nofeeds" ) == 0 ) {
	nofeed[block] = 1 ;
    } else if( strcmp( input , "relative_length" ) == 0 ) {
	fscanf( fp , " %f " , &relLen ) ;
	relativeLen[block] = relLen ;
    }
}
return ;
}
