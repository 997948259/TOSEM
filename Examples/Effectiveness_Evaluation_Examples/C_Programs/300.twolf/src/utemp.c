#include "standard.h"
extern int last_feed ;
extern int *add_to_row ;
extern int connection_machine ;
extern int rowHeight ;
extern int estimate_feeds ;
extern int tw_fast ;
extern double cost_scale_factor ;
extern unsigned randomSeed ;
extern int *nofeed ;
extern char cktName[] ;
extern int attprcel ;
extern int attmax ;
extern FILE *fpo ;
extern double T ;
extern int iteration ;
double table1[1024] , table2[1024] , table3[1024] ;
extern int addFeeds ;
extern int **pairArray ;
extern int numChans ;
extern int *maxTrack ;
extern int tracks ;
extern int doglobal ;
extern int cswaps ;
extern int stage ;
extern int noPairs ;
extern int numRows ;
extern double ckt_size_factor ;
extern double Tzero ;
extern int last_level ;
extern double finalRowControl ;
extern double initialRowControl ;
int moveable_cells ;
int fdthrus ;
extern int randVar ;

utemp()
{

double TloRange , Tfactor ;
int pairtest , check ;
unsigned i2 ;
double **tempfile ;
char filename[64] ;
int t , i , row , freeze , cell , changes ;
FILE *fp ;


last_level = -1 ;

if( stage >= 2 ) {
    pairtest = 1 ;
} else {
    pairtest = 0 ;
}
initialRowControl = 0.0 ;
finalRowControl = 0.0 ;
check = 0 ;
freeze = 10000000 ;
randVar = randomSeed ; 
fprintf( fpo, "\nThe rand generator seed was at utemp() : %d\n\n\n", 
						    randVar ) ;
 
table1[0] = 1.0 ;
table2[0] = 1.0 ;
table3[0] = 1.0 ;
for( i2 = 1 ; i2 <= 1023 ; i2++ ) {
    table1[ i2 ] = exp( -(double) i2 / 8.0 ) ;
    table2[ i2 ] = exp( -(double) i2 / 8192.0 ) ;
    table3[ i2 ] = exp( -(double) i2 / 8388608.0 ) ;
}


moveable_cells = 0 ;
for( cell = 1 ; cell <= numcells ; cell++ ) {
    if( carray[cell]->cclass < 0 ) {
        continue ;
    }
    moveable_cells++ ;
}


if( moveable_cells <= 500 ) {
    attprcel = 25 ;
} else {
    /*  n to the 4/3 power  */
    attprcel = (int)(25.0 * 
		pow( (double) moveable_cells / 500.0, 1.0 / 3.0 ) ) ;
}
if( tw_fast ) {
    attprcel /= 5 ;
}

tempfile = (double **) safe_malloc( 4 * sizeof( double * ) ) ;
for( t = 0 ; t <= 3 ; t++ ) {
    tempfile[t] = (double *) safe_malloc( 2 * sizeof( double ) ) ;
}
tempfile[0][0] = 0.9825 ;
tempfile[0][1] = 90.0 ;
fprintf(fpo,"  tempfile[0][0] = %f    ", tempfile[0][0] ); 
fprintf(fpo,  "tempfile[0][1] = %f\n  ", tempfile[0][1] ); 
tempfile[1][0] = 0.915 ;
tempfile[1][1] = 20.0 ;
fprintf(fpo,"tempfile[1][0] = %f    ", tempfile[1][0] ); 
fprintf(fpo,"tempfile[1][1] = %f\n  ", tempfile[1][1] ); 
tempfile[2][0] = 0.70 ;
tempfile[2][1] = 10.0 ;
fprintf(fpo,"tempfile[2][0] = %f    ", tempfile[2][0] ); 
fprintf(fpo,"tempfile[2][1] = %f\n  ", tempfile[2][1] ); 
tempfile[3][0] = 0.10 ;
tempfile[3][1] = 0.0 ;
fprintf(fpo,"tempfile[3][0] = %f    ", tempfile[3][0] ); 
fprintf(fpo,"tempfile[3][1] = %f\n\n", tempfile[3][1] ); 


TloRange = 10000000000.0 ;
t = -1 ;

fprintf(fpo , "  I   T  fds     Wire Penalty P_lim Epct " ) ;
fprintf(fpo , "binC rowC  acc  s/p early  FDs    MRs\n" ) ;
for( ; ; ) {
    while( T < TloRange ) { 
	t++ ;
	if( t > 3 ) {
	    fprintf( fpo, "exceeded tempfile array in ");
	    fprintf( fpo, "utemp.c \n");
	    exit(TW_FAIL);
	}
	Tfactor  = tempfile[t][0] ;
	TloRange = tempfile[t][1] ;
    }

    if( pairtest == 0 ) {
	uloop() ;
	if( T < Tzero ) {
	    pairtest = 1 ;
	}
	savewolf(1) ; 
    } else {
	if( check == 0 ) {
	    check = 1 ;
	    if( stage == 1 ) {
		uloop2() ;
		++iteration ;
	    }
	    last_level = -1 ;
	    savewolf(1) ;
	    freeze = iteration ;

	    if( connection_machine ) {
		unlap(-1) ;
		findunlap(-1) ;
		outcm() ;
	    }

	    countf() ;
	    if( doglobal ) {
		sprintf( filename , "%s.cel" , cktName ) ;
		fp = twopen (filename , "r", ABORT ) ;
		finalwire() ;
		grdcell( fp ) ;
		twclose( fp ) ;
	    }
	    reassign() ;
	    if( doglobal ) {
		if( addFeeds == 0 ) {
		    for( row = 1 ; row <= numblock ; row++ ) {
			nofeed[row] = 1 ;
		    }
		}
		findunlap(1) ;

		fdthrus = findfeeds(0) ;
		fdthrus += add_to_row[0] ;
		fixwolf( fdthrus ) ;
		findfeeds(1) ;

		unlap(-2) ;
		add_dummy_feeds( last_feed ) ;

		numcells += fdthrus ;
		moveable_cells += fdthrus ;
		if( stage >= 2 ) {
		    sprintf( filename , "%s.rs2" , cktName ) ;
		    if( fp = twopen ( filename , "r", NOABORT )) {
			fixfdpos(fp) ;
			twclose(fp) ;
		    }
		}
	    }
	    sortpin() ;
	    findunlap(0) ;
	    penalty = 0 ;
	    initialize_cost() ;  /* New Cost Function */
	    /*
	     *  This computes new wire costs for the compacted
	     *  placement (and feed insertion).  It calls unlap()
	     *  which sorts and places the cells end-to-end
	     */

	    fprintf(fpo,"Added: %d  feed-through cells\n\n",fdthrus);
	    fprintf(fpo,"Removed the cell overlaps --- ");
	    fprintf(fpo,"Will do neighbor interchanges only now\n");
	    fprintf( fpo, "\nTOTAL INTERCONNECT LENGTH: %d\n",funccost);
	    fprintf(fpo,"OVERLAP PENALTY: %d\n\n", penalty );
	    fprintf(fpo,"initialRowControl:%8.3f\n", initialRowControl);
	    fprintf(fpo,"finalRowControl:%8.3f\n", finalRowControl);
	    fflush(fpo);

	    attmax = 5 * moveable_cells ;

	    if( stage != 3 ) {
		if( noPairs == 0 ) {
		    T = 0.001 ;
		    fprintf( fpo, "iter      T      Wire accept\n" ) ;
		    upair() ;
		    savewolf(2) ;
		}
	    }
	} else {
	    if( noPairs == 0 ) {
		T = 0.001 ;
		upair() ;
		savewolf(2) ;
	    }
	}
    }

    if( stage != 3 ) {
	printf("%3d ", ++iteration );
	if( iteration % 15 == 0 ) {
	    printf("\n");
	}
	fflush( stdout ) ;
    }

    if( iteration >= freeze + 3 || stage == 3 ) {
	/*
	    * WE ARE FINISHED *
	*/

	/* Now align the feeds */
	for( i = 1 ; i <= 8 ; i++ ) {
	    align_init() ;
	    changes = alignfeed() ;
	    fprintf(fpo,"Total Feed-Alignment Movement (Pass %d): %d\n",
						    i, changes );
	}
	align_init() ;
	/* recompute the wire costs */
	findunlap(-1) ;

	if( doglobal ) {
	    globe() ;
	    globroute() ;
	    if( cswaps ) {
		if( noPairs == 0 ) {
		    ugpair() ;
		}
	    }
	    findrchk() ;
	    fprintf(fpo,"\nFINAL NUMBER OF ROUTING TRACKS: %d\n\n", 
							    tracks ) ;
	    for( i = 1 ; i <= numChans ; i++ ) {
		fprintf(fpo,"MAX OF CHANNEL:%3d  is: %3d\n",i
						,maxTrack[i]);
	    }
	    mergplist() ;
	    outpins() ;
	    output() ; 
	} else {
	    output() ; 
	}
	fprintf(fpo,"FINAL TOTAL INTERCONNECT LENGTH: %d\n",funccost);
	fprintf(fpo,"FINAL OVERLAP PENALTY: %d    ", penalty );
	fprintf(fpo, "FINAL VALUE OF TOTAL COST IS: %d\n", 
					    funccost + penalty ) ;
	fprintf(fpo,"MAX NUMBER OF ATTEMPTED FLIPS PER T:%8d\n",attmax);
	break ;
    } else {
	T = Tfactor * T ;
    }
}
fprintf(fpo,"\n\ncost_scale_factor:%g\n\n", cost_scale_factor ) ;

return ;
}



add_dummy_feeds( feednum ) 
int feednum ;
{
CBOXPTR cellptr ;
TIBOXPTR tileptr ;
int pin , corient , left , right ;
int pos , row , i , last_cell ;

for( row = 1 ; row <= numRows ; row++ ) {
    last_cell = pairArray[row][ pairArray[row][0] ] ;
    pos = carray[last_cell]->cxcenter +
			carray[last_cell]->tileptr->right - fdWidth ;
    for( i = 1 ; i <= add_to_row[row] ; i++ ) {
	pos += fdWidth ;
	cellptr = carray[ numcells + ++feednum ] ;
	cellptr->padside = 0 ;
	cellptr->cxcenter = pos ;
	cellptr->cycenter = barray[row]->bycenter ;
	cellptr->cheight  = barray[row]->bheight  ;
	cellptr->clength  = fdWidth ;
	if( barray[row]->borient == 2 ) {
	    cellptr->corient = 1 ;
	}
	tileptr = cellptr->tileptr ;
	cellptr->cname = (char *) safe_malloc( 16 * sizeof( char ) ) ;
#ifdef FEED_INSTANCES
	sprintf( cellptr->cname , "twfeed%d", feednum ) ;
#else
	sprintf( cellptr->cname , "twfeed" ) ;
#endif
	cellptr->cblock = row ;
	tileptr->left   = -fdWidth / 2 ;
	tileptr->right  = fdWidth + tileptr->left ;
	tileptr->bottom = -barray[row]->bheight / 2 ;
	tileptr->top    = barray[row]->bheight + tileptr->bottom ;
	safe_free( tileptr->termsptr->nextterm ) ;
	safe_free( tileptr->termsptr ) ;
	tileptr->termsptr = TERMNULL ;
    }
}
return ;
}
