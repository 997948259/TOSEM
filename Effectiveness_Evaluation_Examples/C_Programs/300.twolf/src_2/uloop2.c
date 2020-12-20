#include "standard.h"
#define DELTA_B 1
#define PICK_INT(l,u) (((l)<(u)) ? ((RAND % ((u)-(l)+1))+(l)) : (l))
extern int estimate_feeds ;
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
extern int newpenal ;
extern int Apost , Bpost ;
extern int *cellaptr , *cellbptr ;
extern int earlyRej , Rej_error ;
extern int wire_chg , binpen_chg , rowpen_chg ;
extern int a , b , ablock , bblock ;
extern int attempts ;
extern int potential_errors , error_count , P_limit ;
extern double total_wire_chg ;
extern double sigma_wire_chg ;
extern double mean_wire_chg ;
extern int wire_chgs ;

uloop2()
{

CBOXPTR acellptr, bcellptr ; 
BBOXPTR ablckptr , bblckptr ;
int botblk , topblk ;
int flips ;
int axcenter , bxcenter , bycenter ; 
int aorient , borient ;
int bleft , bright ; 
int blk , pairflips ;
int i , r , l , t ;
int abin , bbin ;
int firstTry , fds ;
double temp , fp_ratio , percent_error ;


attempts  = 0 ;
flips     = 0 ;
pairflips = 0 ;
earlyRej  = 0 ;

P_limit = -1 ;
windx = minxspan ;

attmax = 2 * attprcel * numcells ;
binpenCon = 0.0 ;

fds = 0 ;
if( estimate_feeds ) {
    fds = controlf( 1 ) ;
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

	} while( ablock == blk || 
			ablckptr->bclass != bblckptr->bclass ) ;
	
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
		}
	    } else {  /* bblckptr->borient == 2 */
		if( ucxxo1( bxcenter,bycenter,(aorient == 0) ? 1 : 3 )){
		    flips++ ;
		}
	    }
	} else {  /* ablockptr->borient == 2 */	
	    if( bblckptr->borient == 1 ) {
		if( ucxxo1( bxcenter, bycenter,
			    (aorient == 1) ? 0 : 2)){
		    flips++ ;
		}
	    } else {  /*  bblckptr->borient == 2 */
		if( ucxx1( bxcenter, bycenter) ){
		    flips++ ;
		}
	    }
	}
    } else { /*   *cellbptr >= 1   */

	Bpost = PICK_INT( 1 , *cellbptr ) ;
	b = cellbptr[ Bpost ] ;
	bcellptr  = carray[b] ;
	bblock    = bcellptr->cblock   ;
	bblckptr = barray[ bblock ] ;

	if( bcellptr->cclass == -1 || a == b ) {
	    continue ;
	}
	
	borient   = bcellptr->corient  ;
	if( ablckptr->borient == 1 ) {
	    if( bblckptr->borient == 1 ) {
		t = ucxx2( ) ;
		if( t == 1 ) {
		    pairflips++ ;
		}
	    } else {  /* bblock->orient == 2 */
		t = ucxxo2( (aorient == 0) ? 1:3, (borient == 1)
							 ? 0:2 ) ;
		if( t == 1 ) {
		    pairflips++ ;
		}
	    }
	} else { /* ablock->borient == 2 */
	    if( bblckptr->borient == 1 ) {
		t = ucxxo2( (aorient == 1) ? 0:2, (borient == 0)
							    ? 1:3) ;
		if( t == 1 ) {
		    pairflips++ ;
		}
	    } else { /* bblock->borient == 2 */  
		t = ucxx2( ) ;
		if( t == 1 ) {
		    pairflips++ ;
		}
	    }
	}
    }
    attempts++ ;
}


temp = 100.0 * (double)(pairflips + flips) / (double)(attmax) ;
if( pairflips > 0.0001 ) {
    fp_ratio = 100.0 * (double)flips/(double)pairflips ;
} else {
    fp_ratio = 100.0 ;
}

fprintf(fpo,"%3d %3d %4d %8d %7d %5d 0.0 %4.1f %4.1f %4.1f %4.1f",
	iteration+1, (int)T, fds , funccost, penalty, P_limit,
	binpenCon, roLenCon, temp, fp_ratio);
fprintf(fpo," %4.1f\n", 100.0*(double)earlyRej/(double)attmax );
fflush( fpo ) ;

return ;
}
