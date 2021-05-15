
#define MAIN_VARS  

#include "standard.h"
extern int last_feed ;
extern int *add_to_row ;
extern int moveable_cells ;
extern int tot_num_feeds ;
extern int tot_missing_rows ;

#include "main.h"

#ifdef MEMORYMAN
#include <signal.h>
#endif



main( argc , argv )
int argc ;
char *argv[] ;
{


FILE *fp ;
char filename[64] ;
int block ;
int i , net , changes ;
char input[40] ;
int l , r , b , t , cx , cy , cl , cr , cb , ct , cell , row ;


/* 
    get a pointer to the parameters file
*/
if( argc != 2 ) {
    printf("circuit name not entered properly on command line\n");
    printf("Proper syntax: TimberwolfSC circuitName\n");
    exit(TW_FAIL);
}
sprintf( cktName , "%s" , argv[1] ) ;

sprintf( filename , "%s.out" , cktName ) ;
fpo = twopen( filename, "w" , ABORT ) ;

initProgram( "TimberWolfSC", "v4.3a" );

readParFile();

Yset_random_seed( randomSeed ) ;

/* 
    get a pointer to blockfile
*/
sprintf( filename , "%s.blk" , cktName ) ;
fp = twopen( filename , "r" , ABORT ) ;
readblck( fp ) ;
twclose( fp ) ;

maxCellO = 0 ;
for( block = 1 ; block <= numblock ; block++ ) {
    if( barray[block]->borient == 2 ) {
	maxCellO = 1 ;
	break ;
    }
}


sprintf( filename , "%s.cel" , cktName ) ;
fp = twopen( filename , "r" , ABORT ) ;
readcell( fp ) ;
twclose( fp ) ;

/* 
    get a pointer to the netlist input file 
*/
sprintf( filename , "%s.net" , cktName ) ;
fp = twopen( filename , "r", ABORT  ) ;
readnets( fp ) ;
twclose( fp ) ;

iteration = 0 ;
T = 500.0 ;

t = 0 ;
b = 32000 ;
r = 0 ;
l = 32000 ;
for( block = 1 ; block <= numblock ; block++ ) {
    cx = barray[block]->bxcenter ;
    cy = barray[block]->bycenter ;
    cl = barray[block]->bleft;
    cr = barray[block]->bright;
    cb = barray[block]->bbottom;
    ct = barray[block]->btop;
    if( cx + cr > r ) {
	r = cx + cr ;
    }
    if( cx + cl < l ) {
	l = cx + cl ;
    }
    if( cy + ct > t ) {
	t = cy + ct ;
    }
    if( cy + cb < b ) {
	b = cy + cb ;
    }
}
blkxspan = r - l ;
blkyspan = t - b ;
ifrange = blkxspan * imprange ;
fprintf(fpo,"block x-span:%d  block y-span:%d\n",blkxspan,blkyspan);
fprintf(fpo,"implicit feed thru range: %d\n", ifrange ) ;

for( cell = 1 ; cell <= numcells + numterms ; cell++ ) {
    cx = carray[ cell ]->cxcenter ;
    cy = carray[ cell ]->cycenter ;
    cl = carray[cell]->tileptr->left;
    cr = carray[cell]->tileptr->right;
    cb = carray[cell]->tileptr->bottom;
    ct = carray[cell]->tileptr->top;
    if( cx + cr > r ) {
	r = cx + cr ;
    }
    if( cx + cl < l ) {
	l = cx + cl ;
    }
    if( cy + ct > t ) {
	t = cy + ct ;
    }
    if( cy + cb < b ) {
	b = cy + cb ;
    }
}
bdxlen = r - l ;
bdylen = t - b ;

lrtxspan = r ;
lrtyspan = t ;


for( net = 1 ; net <= numnets ; net++ ) {
    netarray[net]->Vweight *= 2.0 / (rowSep + 1.0) ;
}

binpenCon = 4.0 * ((((double) numcells) / ((double) numblock) ) / 39.0) ;
binpenCon = (binpenCon > 4.0) ? binpenCon : 4.0 ;
binpenCon = 1.0 ;
roLenCon  = 3.0 ;
fprintf(fpo,"Using default value of bin.penalty.control:%f\n",
						binpenCon ) ;
funccost = findcost() ;

assignro() ;

initialize_rows() ;
fprintf(fpo,"\nNew Cost Function: Initial Horizontal Cost:%d\n",
					    initialize_cost() ) ;
vert_statistics() ;
fprintf(fpo,"New Cost Function: FEEDS:%d   MISSING_ROWS:%d\n\n",
			    tot_num_feeds , tot_missing_rows ) ;

fprintf( fpo , "bdxlen:%d  bdylen:%d\n", bdxlen , bdylen ) ;
fprintf( fpo , "l:%d  t:%d  r:%d  b:%d\n", l , t , r , b ) ;
			    
fprintf( fpo, "\n\n\nTHIS IS THE ROUTE COST OF THE ");
fprintf( fpo, "CURRENT PLACEMENT: %d\n" , funccost ) ;
fprintf( fpo, "\n\n\nTHIS IS THE PENALTY OF THE ") ;
fprintf( fpo , "CURRENT PLACEMENT: %d\n" , penalty ) ;
fflush( fpo ) ;

if( !costonly ) {
    Tzero = 0.1 ;
    desired_accept = (double *) safe_malloc( 117 * sizeof(double) ) ;
    for( i = 0 ; i <= 116 ; i++ ) {
	if( i < 7 ) {
	    desired_accept[i] = 50.0 ;
	} else {
	    desired_accept[i] = 50.5 - 
		    ( (50.0 / 110.0) * (double)(i - 6) ) ;
	}
    }
    utemp() ;

} else {
    if( connection_machine ) {
	unlap(-1) ;
	findunlap(-1) ;
	outcm() ;
    }
    if( doglobal ) {
	countf() ;
	sprintf( filename , "%s.cel" , cktName ) ;
	fp = twopen( filename , "r", ABORT  ) ;
	grdcell( fp ) ;
	twclose( fp ) ;
	reassign() ;
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
	if( stage >= 2 ) {
	    sprintf( filename , "%s.rs2" , cktName ) ;
	    fp = twopen( filename , "r", NOABORT  ) ;
	     
	    if( fp ){
		fixfdpos(fp) ;
		twclose(fp) ;
	    }
	}
	findunlap(0) ;
	/*
	 *  This computes new wire costs for the compacted
	 *  placement (and feed insertion).  It calls unlap()
	 *  which sorts and places the cells end-to-end
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

	moveable_cells = 0 ;
	for( cell = 1 ; cell <= numcells ; cell++ ) {
	    if( carray[cell]->cclass < 0 ) {
		continue ;
	    }
	    moveable_cells++ ;
	}

	globe() ;
	globroute() ;
	if( cswaps ) {
	    ugpair() ;
	}
	findrchk() ;
	fprintf(fpo,"\nFINAL NUMBER OF ROUTING TRACKS: %d\n\n", 
						    tracks);
	for( i = 1 ; i <= numChans ; i++ ) {
	    fprintf(fpo,"MAX OF CHANNEL:%3d  is: %3d\n", i 
					    , maxTrack[i]);
	}
	mergplist() ;
	outpins() ;
	output() ;
	safe_free( pinlist ) ;
    } else {
	reassign() ;
	findunlap(1) ;
	output() ;
    }
}

fprintf( fpo , "Number of Feed Thrus: %d\n", ffeeds ) ;
fprintf( fpo , "Number of Implicit Feed Thrus: %d\n", impcount ) ;

fprintf( fpo , "\nStatistics:\n");
fprintf( fpo , "Number of Standard Cells: %d\n", 
				    numcells - fdthrus );
fprintf( fpo , "Number of Pads: %d \n", numterms );
fprintf( fpo , "Number of Nets: %d \n", numnets ) ;
fprintf( fpo , "Number of Pins: %d \n", maxterm ) ;

print_stats(fpo);
twclose(fpo) ;
exit(TW_OK);
}
