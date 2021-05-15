#include "standard.h"
#include "main.h"

readParFile()
{
FILE *fp ;
char filename[64] , input[64] ;
int test ;
double f ;

sprintf( filename , "%s.par" , cktName ) ;
fp = twopen( filename , "r", ABORT ) ;
route2act = -1;
routeGrid = -1;
gridCell = -1; 

while( fscanf( fp , " %s " , input ) == 1 ) {

    if( strcmp( input , "implicit.feed.thru.range") == 0 ) {

	test = fscanf( fp , " %lf " , &imprange ) ;
	if( test != 1 ) {
	    fprintf( fpo,"The value of implicit.feed.thru.range");
	    fprintf( fpo," was not properly");
	    fprintf( fpo,"entered in the .par file\n");
	    exit(TW_FAIL);
	}

    } else if( strcmp( input , "fast") == 0 ) {
	test = fscanf( fp, " %d ", &tw_fast ) ;
	if( test != 1 ){
	  fprintf( fpo, "The value of fast was not ") ;
	  fprintf( fpo, "properly entered in the .par file\n" ) ;
	  exit(TW_FAIL) ;
	}

    } else if( strcmp( input , "slow") == 0 ) {
	test = fscanf( fp, " %d ", &tw_slow ) ;
	if( test != 1 ){
	  fprintf( fpo, "The value of fast was not ") ;
	  fprintf( fpo, "properly entered in the .par file\n" ) ;
	  exit(TW_FAIL) ;
	}

    } else if( strcmp( input , "pin_layers_given") == 0 ) {
	pin_layers_given = 1 ;

    } else if( strcmp( input , "gate_array_special") == 0 ) {
	gate_array_special = TRUE ;

    } else if( strcmp( input , "connection_machine") == 0 ) {
	connection_machine = 1 ;

    } else if( strcmp( input , "no_feeds_side_nets") == 0 ) {
	no_feeds_side_nets = 0 ;

    } else if( strcmp( input , "no_net_normalize") == 0 ) {
	no_net_normalize = 1 ;

    } else if( strcmp( input , "estimate_feeds" ) == 0 ) {
	estimate_feeds = 1 ;

    } else if( strcmp( input , "cost_only" ) == 0 ) {
	costonly = 1 ;

    } else if(strcmp(input,"do.global.route") == 0 ){
	doglobal = 1 ;

    } else if(strcmp(input,"do.global.route.cell.swaps") == 0){
	cswaps = 1 ;
	stopdeg = 0.3 ;

    } else if(strcmp(input,"full") == 0 ) {
	if( cswaps ) {
	    stopdeg = 0.5 ;
	}

    } else if( strcmp( input , "feedThruWidth") == 0 ) {
	test = fscanf( fp , " %d " , &fdWidth ) ;
	if( test != 1 ) {
	    fprintf( fpo,"The value of feedThruWidth was not ");
	    fprintf( fpo,"properly entered in the .par file\n");
	    exit(TW_FAIL);
	}

    } else if( strcmp( input , "layer") == 0 ) {
	test = fscanf( fp , " %d " , &feedLayer ) ;
	if( test != 1 ) {
	    fprintf( fpo,"The value of layer was not ");
	    fprintf( fpo,"properly entered in the .par file\n");
	    exit(TW_FAIL);
	}
	if( feedLayer != 1 && feedLayer != 2 && feedLayer != 3 ) {
	    fprintf( fpo,"The value of layer must currently be one of ");
	    fprintf( fpo,"1, 2, or 3 \n");
	    exit(TW_FAIL);
	} else {
	    feedLayer-- ;
	}

    } else if( strcmp( input , "addFeeds") == 0 ) {
	addFeeds = 1 ;

    } else if( strcmp( input , "indent") == 0 ) {
	test = fscanf( fp , " %lf " , &indent ) ;
	indent = 1.0 ;
	/*  indent should always be 1.0 now  */

    } else if( strcmp( input , "random.seed") == 0 ) {

	test = fscanf( fp , " %d " , &randomSeed ) ;

	if( test != 1 ) {
	    fprintf( fpo,"The value of random.seed was not ");
	    fprintf( fpo,"properly entered in the .par file\n");
	    exit(TW_FAIL);
	}

    } else if( strcmp( input , "random.seed2") == 0 ) {

	test = fscanf( fp , " %d " , &randomSeed2 ) ;

	if( test != 1 ) {
	    fprintf( fpo,"The value of random.seed2 was not ");
	    fprintf( fpo,"properly entered in the .par file\n");
	    exit(TW_FAIL);
	}

    } else if( strcmp( input , "rowSep") == 0 ) {

	test = fscanf( fp , " %lf " , &rowSep ) ;

	if( test != 1 ) {
	    fprintf( fpo,"The value of rowSep was not properly");
	    fprintf( fpo,"entered in the .par file\n");
	    exit(TW_FAIL);
	}

    } else if( strcmp( input , "restart") == 0 ) {
	resume_run = YES ;

    /* added following two keywords to allow the modification of
	placement positions to include routing area   */
    /* track_spacing is the routing grid in microns */
    /* route2act is the routing layer to active cell minimum spacing */
    /* these are only used if global routing is performed */
    /* see output routine - output.c  WPS 8-29-86 */

    } else if( strcmp( input , "track.spacing") == 0 ) {
	uneven_cell_height = 1 ;
	test = fscanf( fp , " %d " , &track_spacing ) ;
	if( test != 1 ) {
	    fprintf( fpo,"The value of trackSpacing was not properly");
	    fprintf( fpo,"entered in the .par file\n");
	    exit(TW_FAIL);
	}

    } else if( strcmp( input , "one.pin.feedthru") == 0 ) {
	one_pin_feedthru = 1 ;

    } else if( strcmp( input , "route2act") == 0 ) {
	test = fscanf( fp , " %d " , &route2act ) ;
	if( test != 1 ) {
	    fprintf( fpo,"The value of route2act was not properly");
	    fprintf( fpo,"entered in the .par file\n");
	    exit(TW_FAIL);
	}

    } else if( strcmp( input , "gridCell") == 0 ) {
	test = fscanf( fp , " %d " , &gridCell ) ;
	if( test != 1 ) {
	    fprintf( fpo,"The value of gridCell was not properly");
	    fprintf( fpo,"entered in the .par file\n");
	    exit(TW_FAIL);
	}

    } else if( strcmp( input , "routeGrid") == 0 ) {
	test = fscanf( fp , " %d " , &routeGrid ) ;
	if( test != 1 ) {
	    fprintf( fpo,"The value of routeGrid was not properly");
	    fprintf( fpo,"entered in the .par file\n");
	    exit(TW_FAIL);
	}

    } else {
	fprintf( fpo, "Unparsable keyword>>> %s\n", input );
	fprintf( fpo, "was found in the .par file\n");
	exit(TW_FAIL);
    }
}
twclose( fp ) ;

sprintf( filename , "%s.rs2" , cktName ) ;
if( (fp = twopen ( filename , "r", NOABORT)) && resume_run == YES ) {
    fscanf( fp , "%lf" , &f ) ;
    fscanf( fp , "%d" , &stage ) ;
    fscanf( fp , "%d" , &stage ) ;
    fscanf( fp , "%d" , &stage ) ;
    fprintf(fpo,"\n\nNOTE: Restart file .rs2 will be used \n\n");
    twclose(fp);
    restart = 1 ;
} else {
    stage = 1 ;
    fprintf(fpo,"\n\nNOTE: Restart file .rs2 not used\n\n");
    restart = 0 ;
}

if( cswaps != 0 ) {
    if( doglobal == 0 ) {
	fprintf(fpo,"user specified cell swaps ");
	fprintf(fpo,"without requesting do.global.route\n");
	exit(TW_FAIL);
    }
}
if( doglobal ) {
    fprintf(fpo,"TimberWolf will perform a global route step\n");
}
if( cswaps ) {
    fprintf(fpo,"TimberWolf will perform final cell placements\n");
    fprintf(fpo," by swapping cells based on minimization of\n");
    fprintf(fpo," the total number of routing tracks required\n");
}
if( addFeeds && imprange < 0.0 ) {
    fprintf( fpo, "implicit.feed.thru.range was ");
    fprintf( fpo, "not entered in the .par file\n");
    exit(TW_FAIL);
}
if( rowSep < 0.0 ) {
    fprintf( fpo, "rowSep was not entered in the .par file\n");
    exit(TW_FAIL);
} else {
    fprintf( fpo, "rowSep: %f\n" , rowSep ) ;
}
if( addFeeds == 1  &&  fdWidth == -1 ) {
    fprintf(fpo,"feedThruWidth was not entered in the .par file\n");
    exit(TW_FAIL);
} else {
    fprintf( fpo, "feedThruWidth: %d\n" , fdWidth ) ;
}
#ifdef TI
if( track_spacing < 0.0 ) {
    fprintf( fpo, "track.spacing was not entered in the .par file\n");
    exit(TW_FAIL);
} else {
    fprintf( fpo, "trackSpacing: %d\n" , track_spacing ) ;
}

if( route2act < 0.0 ) {
    fprintf( fpo, "route2act was not entered in the .par file\n");
    exit(TW_FAIL);
} else {
    fprintf( fpo, "route2act: %d\n" , route2act ) ;
}
if( gridCell < 0.0 ) {
    fprintf( fpo, "gridCell was not entered in the .par file\n" ) ;
    fprintf( fpo, "If the user wishes cell dimensions to be output\
    					in same scale as input,\n") ;
    fprintf( fpo, "gridCell should be set to the ICE characteristic\
							number.\n") ;
    exit(TW_FAIL);
} else {
    fprintf( fpo, "gridCell: %d\n" , gridCell ) ;
    fprintf( fpo, "Cells values will be output by multiplying\
				by gridCell: %d\n" , gridCell ) ;
}
#endif

return ;
}
