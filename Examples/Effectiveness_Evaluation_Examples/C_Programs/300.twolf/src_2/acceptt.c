#include <stdio.h>

#define RAND (Yacm_random() )
#define MASK 0x3ff
extern double table1[] , table2[] , table3[] , T ;
extern double cost_scale_factor ;
extern int randVar ;

int acceptt( delta_cost )
int delta_cost ;
{

int truth ;
double fred ;
register unsigned fract ;

fred =  ((double) delta_cost * cost_scale_factor ) / T ; 

if( fred >= 0.0 ) {
    truth = 1 ;
} else if( fred < -80.0 ) {
    truth = 0 ;
} else if( fred > -0.0001 ) {
    if( 1.0 + fred > ( (double) RAND / (double)0x7fffffff ) ) { 
	truth = 1 ;
    } else {
	truth = 0 ;
    }
} else {
    fract = (int)( -fred * 8388608.0 ) ;
    if( (table1[ (fract >> 20) & MASK ] * 
		    table2[ (fract >> 10) & MASK] * 
		    table3[ fract & MASK ]) > 
		    ( (double) RAND / (double)0x7fffffff ) ) {
	truth = 1 ;
    } else {
	truth = 0 ;
    }
}

return(truth) ; 
}
