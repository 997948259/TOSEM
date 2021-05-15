#include "standard.h"
#define DELTA_B 1
#define PICK_INT(l,u) (((l)<(u)) ? ((RAND % ((u)-(l)+1))+(l)) : (l))
extern int tot_num_feeds ;
extern int tot_missing_rows ;
extern int est_fds ;
extern int total_feeds ;
extern int tw_fast ;
extern int tw_slow ;
extern int resume_run ;
extern int estimate_feeds ;
double partition() ;
double compute_and_combination() ;
double combination() ;
double expected_value() ;
double expected_svalue() ;
double finalRowControl ;
double initialRowControl ;
extern double *desired_accept ;
extern int randVar ;
extern BINBOX ***binptr ;
extern int totalR ;
extern int minxspan ;
extern int attmax ;
extern int blkxspan ;
extern int blkyspan ;
extern int rowHeight ;
extern int attprcel ;
extern int iteration ;
extern int penalty , binpenal , rowpenal ;
extern double binpenCon , roLenCon ;
extern double mean_width ;
extern int offset_limit ;
extern double cost_scale_factor ;
extern double T ;
extern double rowSep ;
int newpenal ;
int Apost , Bpost ;
int *cellaptr , *cellbptr ;
int earlyRej , Rej_error ;
extern int Trybin ;
int wire_chg , binpen_chg , rowpen_chg ;
int a , b , ablock , bblock ;
int attempts ;
extern int potential_errors , error_count , P_limit ;
extern double total_wire_chg ;
extern double sigma_wire_chg ;
extern double mean_wire_chg ;
extern int wire_chgs ;
extern int moveable_cells ;

uloop()
{

CBOXPTR acellptr, bcellptr ; 
BBOXPTR ablckptr , bblckptr ;
DBOXPTR dimptr ;
int botblk , topblk ;
int flips , rejects ;
int axcenter , bxcenter , bycenter ; 
int aorient , borient ;
int bleft , bright ; 
int blk , pairflips ;
int i , r , l , t ;
int abin , bbin ;
int firstTry , fds , net , cost ;
double target_row_penalty ;
double target_bin_penalty ;
double temp , accept_deviation , fp_ratio , percent_error ;
double factor , total_feed_length , target_feed_length ;
static double avg_VW ;

attempts  = 0 ;
flips     = 0 ;
rejects   = 0 ;
pairflips = 0 ;
earlyRej  = 0 ;
Rej_error = 0 ;

potential_errors = 0 ;
error_count = 0 ;
if( iteration == 0 || resume_run == 1 ) {
    P_limit = (int) ( 10.0 * mean_width ) ;
} else {
    if( wire_chgs > 0 ) {
	mean_wire_chg = total_wire_chg / (double) wire_chgs ;
	if( iteration > 1 ) {
	    sigma_wire_chg = sqrt( sigma_wire_chg / (double) wire_chgs);
	} else {
	    sigma_wire_chg = 3.0 * mean_wire_chg ;
	}
    } else {
	mean_wire_chg  = 0.0 ;
	sigma_wire_chg = 0.0 ;
    }
    /* 80% */
    P_limit = mean_wire_chg + 1.3 * sigma_wire_chg +
					    T / cost_scale_factor;
}

sigma_wire_chg = 0.0 ;
total_wire_chg = 0.0 ;
wire_chgs = 0 ;
windx = minxspan ;

attmax = ((int)((double)(iteration) /
	      121.0 * (double)(2 * attprcel - attprcel / 2) ) +
	      (double)(attprcel / 2) ) * moveable_cells ;
if( tw_fast ){
  attmax /= tw_fast ;
}
if( tw_slow ){
  attmax *= tw_slow ;
}

fds = 0 ;
if( iteration >= 4 ) {
    fds = controlf() ;
    if( iteration <= 105 ) {
	total_feed_length = (double) est_fds ;
	target_feed_length = 0.7 * (double) implicit_feed_count - 
		    ((0.5 * (double) implicit_feed_count  / 105.0 ) *
					((double)iteration));
	if( implicit_feed_count > 0 ) {
	    factor = (double)(total_feed_length - target_feed_length) / 
				((double) implicit_feed_count) ;
	} else {
	    factor = 0.0 ;
	}
	cost = 0 ;
	for( net = 1 ; net <= numnets ; net++ ) {
	    dimptr = netarray[net] ;
	    if( dimptr->Vweight <= 1.0 ) {
		dimptr->Vweight *= 1.0 + factor ;
		if( dimptr->Vweight < 0.5 ) {
		    dimptr->Vweight = 0.5 ;
		} else if( dimptr->Vweight > 1.0 ) {
		    dimptr->Vweight = 1.0 ;
		}
	    }
	    avg_VW += dimptr->Vweight ;
	    cost += ((int)( dimptr->Hweight *
		    (double)( dimptr->xmax - dimptr->xmin))) +
		    ((int)( dimptr->Vweight *
		    (double)( dimptr->ymax - dimptr->ymin)));
	}
	avg_VW /= (double) numnets ;
	funccost = cost ;
    }
} else {
    avg_VW = 0.0 ;
}

while( attempts < attmax ) {

    a = PICK_INT( 1 , numcells ) ;

    acellptr = carray[ a ]  ;
    if( acellptr->cclass == -1 ) {
	continue ;
    }
    ablock   = acellptr->cblock ;
    ablckptr = barray[ ablock ] ;
    axcenter = acellptr->cxcenter ;
    aorient = acellptr->corient ;
    abin = SetBin( axcenter ) ;
    cellaptr = binptr[ablock][abin]->cell ;
    for( i = 1 ; i <= *cellaptr ; i++ ) {
	if( cellaptr[i] == a ) {
	     Apost = i ;
	     break ;
	}
    }


    /* 
     *  select block for cell a to be placed in 
     */
    bblock = 0 ;
    firstTry = 0 ;

    if( (botblk = ablock - DELTA_B) < 1) {
	botblk = 1 ;
    }
    if( (topblk = ablock + DELTA_B) > numblock ) {
	 topblk = numblock ;
    }
    for( i = 1 ; ; i++ ) {
	do {
	    blk = XPICK_INT( botblk , topblk , firstTry ) ; 
	    bblckptr = barray[ blk ] ;

	} while( ablckptr->bclass != bblckptr->bclass ) ;
	
	bleft = bblckptr->bxcenter + bblckptr->bleft ;
	bright = bblckptr->bxcenter + bblckptr->bright ;
	l = (bleft >= axcenter - windx) ? bleft : (axcenter-windx);
	r = (bright <= axcenter + windx) ? bright : (axcenter+windx);
	if( l > r ) {
	    if( i == 1 ) {
		firstTry = blk ;
		continue ;
	    } else if( i == 3 ) {
		if( r < bleft ) {
		    l = r = bleft ;
		} else {
		    l = r = bright ;
		}
	    } else {
		firstTry = - ablock ;
		continue ;
	    }
	} 
	bblock = blk ;
	bycenter = bblckptr->bycenter ;

	if( bblock == ablock ) {
	    bxcenter = XPICK_INT( l, r, axcenter ) ;
	} else {
	    bxcenter = XPICK_INT( l, r, 0 ) ;
	}
	break ;
    }
    bbin = SetBin( bxcenter ) ;
    cellbptr = binptr[bblock][bbin]->cell ;

    if( *cellbptr == 0 ) {

	if( ablckptr->borient == 1 ) {
	    if( bblckptr->borient == 1 ) {
		if( ucxx1( bxcenter, bycenter)){
		    flips++ ;
		} else {
		    rejects++ ;
		    if( rejects % 6 == 0 && acellptr->orflag != 0){
			uc0( a , (aorient == 0) ? 2 : 0 );
		    }
		}
	    } else {  /* bblckptr->borient == 2 */
		if( ucxxo1( bxcenter,bycenter,(aorient == 0) ? 1 : 3 )){
		    flips++ ;
		} else {
		    rejects++ ;
		    if( rejects % 6 == 0 && acellptr->orflag != 0){
			uc0( a , (aorient == 0) ? 2 : 0 );
		    }
		}
	    }
	} else {  /* ablockptr->borient == 2 */	
	    if( bblckptr->borient == 1 ) {
		if( ucxxo1( bxcenter, bycenter,
			    (aorient == 1) ? 0 : 2)){
		    flips++ ;
		} else {
		    rejects++ ;
		    if( rejects % 6 == 0 && acellptr->orflag != 0){
			uc0( a , (aorient == 1) ? 3 : 1 );
		    }
		}
	    } else {  /*  bblckptr->borient == 2 */
		if( ucxx1( bxcenter, bycenter) ){
		    flips++ ;
		} else {
		    rejects++ ;
		    if( rejects % 6 == 0 && acellptr->orflag != 0){
			uc0( a , (aorient == 1) ? 3 : 1 );
		    }
		}
	    }
	}
    } else { /*   *cellbptr >= 1   */

	Bpost = PICK_INT( 1 , *cellbptr ) ;
	b = cellbptr[ Bpost ] ;
	bcellptr  = carray[b] ;
	bblock    = bcellptr->cblock   ;
	bblckptr = barray[ bblock ] ;

	if( acellptr->cclass != bcellptr->cclass || a == b ) {
	    continue ;
	}
	
	borient   = bcellptr->corient  ;
	if( ablckptr->borient == 1 ) {
	    if( bblckptr->borient == 1 ) {
		t = ucxx2( ) ;
		if( t == -1 ) {
		    rejects++ ;
		    if( rejects % 6 == 0 && acellptr->orflag != 0){
			uc0( a , (aorient == 0) ? 2 : 0 );
		    }
		    attempts++ ;
		    continue ;
		} else if( t == 1 ) {
		    pairflips++ ;
		} else { 
		    rejects++ ;
		    if( rejects % 6 == 0 && acellptr->orflag != 0){
			uc0( a , (aorient == 0) ? 2 : 0 );
		    }
		}
	    } else {  /* bblock->orient == 2 */
		t = ucxxo2( (aorient == 0) ? 1:3, (borient == 1)
							 ? 0:2 ) ;
		if( t == -1 ) {
		    rejects++ ;
		    if( rejects % 6 == 0 && acellptr->orflag != 0){
			uc0( a , (aorient == 0) ? 2 : 0 );
		    }
		    attempts++ ;
		    continue ;
		} else if( t == 1 ) {
		    pairflips++ ;
		} else {
		    rejects++ ;
		    if( rejects % 6 == 0 && acellptr->orflag != 0){
			uc0( a , (aorient == 0) ? 2 : 0 );
		    }
		}
	    }
	} else { /* ablock->borient == 2 */
	    if( bblckptr->borient == 1 ) {
		t = ucxxo2( (aorient == 1) ? 0:2, (borient == 0)
							    ? 1:3) ;
		if( t == -1 ) {
		    rejects++ ;
		    if( rejects % 6 == 0 && acellptr->orflag != 0){
			uc0( a , (aorient == 1) ? 3 : 1 );
		    }
		    attempts++ ;
		    continue ;
		} else if( t == 1 ) {
		    pairflips++ ;
		} else {
		    rejects++ ;
		    if( rejects % 6 == 0 && acellptr->orflag != 0){
			uc0( a , (aorient == 1) ? 3 : 1 );
		    }
		}
	    } else { /* bblock->borient == 2 */  
		t = ucxx2( ) ;
		if( t == -1 ) {
		    rejects++ ;
		    if( rejects % 6 == 0 && acellptr->orflag != 0){
			uc0( a , (aorient == 1) ? 3 : 1 );
		    }
		    attempts++ ;
		    continue ;
		} else if( t == 1 ) {
		    pairflips++ ;
		} else {
		    rejects++ ;
		    if( rejects % 6 == 0 && acellptr->orflag != 0){
			uc0( a , (aorient == 1) ? 3 : 1 );
		    }
		}
	    }
	}
    }
    attempts++ ;
}


if( potential_errors > 0 ) {
    percent_error = (double) error_count / (double) potential_errors ;
} else {
    percent_error = 0.0 ;
}
percent_error *= 100.0 ;


temp = 100.0 * (double)(pairflips + flips) / (double)(attmax) ;
if( pairflips > 0.0001 ) {
    fp_ratio = 100.0 * (double)flips/(double)pairflips ;
} else {
    fp_ratio = 100.0 ;
}

vert_statistics() ;

fprintf(fpo,"%3d %3d %4d %8d %7d %5d %4.1f %4.1f %4.1f %4.1f %4.1f",
	iteration+1, (int)T, fds , funccost, penalty, P_limit,
	percent_error,binpenCon, roLenCon, temp, fp_ratio);
fprintf(fpo," %4.1f %5d %6d\n", 100.0*(double)earlyRej/(double)attmax,
			tot_num_feeds , ABS(tot_missing_rows) );
/* check_row_values() ; */
fflush( fpo ) ;


if( iteration < 1 || resume_run == 1 ) {
    if( iteration < 1 ) {
	cost_scale_factor = 1.0 ;
    }
    rowcon() ;
    resume_run = 0 ;
} else if( iteration < 100 ) {
    accept_deviation = (temp - desired_accept[iteration]) / 40.0 ;
    cost_scale_factor *= 1.0 + accept_deviation ;
}

/*  A Negative-Feedback Approach */
if( iteration <= 104 ) {
    target_bin_penalty = (1.40 - ((1.15/105.0)*((double)iteration+1.0))) *
						(double) totalR ;
    binpenCon += ((double) binpenal - target_bin_penalty) / 
					    (double) totalR ;
    binpenCon = (binpenCon > 0.5) ? binpenCon : 0.5 ;


    target_row_penalty = (initialRowControl - 
		(((initialRowControl - finalRowControl) / 105.0 ) *
			    ((double)iteration+1.0))) * (double) totalR ;
    roLenCon += ((double) rowpenal - target_row_penalty) / 
					    target_row_penalty ;
					
    roLenCon = (roLenCon > 0.5) ? roLenCon : 0.5 ;

    penalty = (int)( binpenCon * (double) binpenal + 
				roLenCon * (double) rowpenal ) ;
}

return ;
}





rowcon()
{

int C , R , p_first , totalCells , cellsPerRow , temp_R ;
int over, under ;
double states , value , expect , variance ; 
double expectedExtraRowLength , rowControl , x , minDev ;

totalCells = numcells ;
R = numRows ;

cellsPerRow = totalCells / R ;

temp_R = R - R / 3 ;
rowControl = 0.0 ;
do {
    rowControl += 0.001 ;
    C = (int)( rowControl * (double) totalCells / 2.0 ) ;
    if( 2.0 * (double)(C+1) - rowControl * totalCells <=
		    rowControl * totalCells - 2.0 * (double) C ) {
	C++ ;
    }
} while( 2 * C < temp_R ) ;

p_first = C / R ;
if( p_first * R < C ) {
    p_first++ ;
}
R -= R / 3 ;

under = 0 ;
over  = 0 ;
for( ; ; ) {
    value = expected_value( C , 0 , p_first , R ) ;
    states = combination( C+R-1, C ) ;
    expect = value / states ;
    expectedExtraRowLength = 100.0 * expect / (double) cellsPerRow ;
    value = expected_svalue( C , 0 , p_first , R ) ;
    variance = value / states - (expect * expect) ;
    x = 100.0 * sqrt( variance ) / (double) cellsPerRow ; 
    minDev = 100.0 / (double) cellsPerRow ;
    value = x+expectedExtraRowLength - minDev ;

    /*
    fprintf(fpo,"\n");
    fprintf(fpo,"rowControl:%6.3f     ", rowControl ) ;
    fprintf(fpo,"expected deviation above minimum:%6.2f\n", value ) ;
    fprintf(fpo,"\n");
    fflush(fpo);
    */
    if( value > 2.7 && value < 3.3 ) {
	break ;
    } else if( value <= 2.7 ) {
	rowControl += 0.001 ;
	if( !over ) {
	    under = 1 ;
	} else {
	    break ;
	}
    } else if( value >= 3.3 ) {
	if( !under ) {
	    rowControl -= 0.001 ;
	    over = 1 ;
	} else {
	    break ;
	}
    }
    C = (int)( rowControl * (double) totalCells / 2.0 ) ;
    if( 2.0 * (double)(C+1) - rowControl * totalCells <=
		    rowControl * totalCells - 2.0 * (double) C ) {
	C++ ;
    }
    p_first = C / R ;
    if( p_first * R < C ) {
	p_first++ ;
    }
}

initialRowControl =  5.5 * rowControl ;
finalRowControl   =  rowControl ;

return ;
}


double partition( C_initial , k_initial , p_initial , R_initial )
int C_initial , k_initial , p_initial , R_initial ;
{

int R , C , k , p , k_limit , p_limit ;
double states , equivs ;

states = 0.0 ;
R = k_limit = R_initial - k_initial ;
C = C_initial - p_initial * k_initial ;

for( k = 1 ; k <= k_limit ; k++ ) {
    equivs = combination( R , k ) ;
    p_limit = C / k ;
    for( p = p_initial ; p <= p_limit ; p++ ) {
	if( C - (p-1)*R > k ) { ;
	    continue ;
	}
	states += equivs * (compute_and_combination( C , k , p , R ) -
					partition( C , k , p , R ) ) ;
	continue ;
    }
}

return( states ) ;
}


double expected_value( C_initial , k_initial , p_initial , R_initial )
int C_initial , k_initial , p_initial , R_initial ;
{

int R , C , k , p , k_limit , p_limit ;
double value , equivs ;

value = 0.0 ;
R = k_limit = R_initial - k_initial ;
C = C_initial - p_initial * k_initial ;

for( k = 1 ; k <= k_limit ; k++ ) {
    equivs = combination( R , k ) ;
    p_limit = C / k ;
    for( p = p_initial ; p <= p_limit ; p++ ) {
	if( C - (p-1)*R > k ) { ;
	    continue ;
	}
	value += (double) p * equivs *
			(compute_and_combination( C , k , p , R ) -
				    partition( C , k , p , R ) ) ;
    }
}

return( value ) ;
}


double expected_svalue( C_initial , k_initial , p_initial , R_initial )
int C_initial , k_initial , p_initial , R_initial ;
{

int R , C , k , p , k_limit , p_limit ;
double value , equivs ;

value = 0.0 ;
R = k_limit = R_initial - k_initial ;
C = C_initial - p_initial * k_initial ;

for( k = 1 ; k <= k_limit ; k++ ) {
    equivs = combination( R , k ) ;
    p_limit = C / k ;
    for( p = p_initial ; p <= p_limit ; p++ ) {
	if( C - (p-1)*R > k ) { ;
	    continue ;
	}
	value += (double)(p * p) * equivs *
			(compute_and_combination( C , k , p , R ) -
				    partition( C , k , p , R ) ) ;
    }
}

return( value ) ;
}


double compute_and_combination( C , k , p , R )
int C , k , p , R ;
{

int numerator , denom1 , denom2 , temp ;
double states ;

states = 1.0  ;
numerator = C - k*p + R - k - 1 ;
denom1 = C - k*p ;
denom2 = R - k - 1 ;
if( denom1 > denom2 ) {
    temp = denom1 ;
    denom1 = denom2 ;
    denom2 = temp ;
}
for( ; numerator > denom2 ; numerator-- , denom1-- ) {
    states *= (double) numerator ;
    states /= (double) denom1 ;
}

return( states ) ;
}


double combination( numerator , denominator )
int numerator , denominator ;
{

double states ;
int temp , denom1 , denom2 ;

states = 1.0  ;

denom1 = denominator ;
denom2 = numerator - denominator ;
if( denom1 > denom2 ) {
    temp = denom1 ;
    denom1 = denom2 ;
    denom2 = temp ;
}
for( ; numerator > denom2 ; numerator-- , denom1-- ) {
    states *= (double) numerator ;
    states /= (double) denom1 ;
}

return( states ) ;
}
