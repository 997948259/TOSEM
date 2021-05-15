/* ----------------------------------------------------------------- 
FILE:	    rand.c                                       
DESCRIPTION:mimimum standard random number generator function.  This
	    random generator replaces the poor Berkeley 4.2 random
	    generator using generators discussed in the Communications
	    of the ACM.  See articles by L'Ecuyer and Park/Miller in
	    June 1988 and October 1988 resp.
CONTENTS:   
	    int Yacm_random()
	    Yset_random_seed(int)
DATE:	    Oct 27, 1988 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) rand.c (Yale) version 3.1 3/21/90" ;
#endif
#endif

static int randVarS ;               /* random number */

#define A_RAND 16807L               /* good generator multiplier */
#define M_RAND 2147483647L                /* 2 ** 31 - 1 */
#define Q_RAND 127773L                    /* m / a */
#define R_RAND 2836L                      /* m mod a */
#define ABS(value)   ( (value)>=0 ? (value) : -(value) ) 

/*  
  M_RANDD may have to be changed on different systems. On ultrix
  it is as below.
  #define M_RANDD (double) 1.0 / 2147483647.0  
*/
#define M_RANDD 4.65661287524579690000000000000000e-10

/* returns a random number in [0..2**31 - 1] */
int Yacm_random() 
{
    register int k_rand ;

    k_rand = randVarS / Q_RAND ;
    randVarS = A_RAND * (randVarS - k_rand * Q_RAND) - (k_rand * R_RAND) ;
    if( randVarS < 0 ){
	randVarS += M_RAND ;
    } 
    return( randVarS ) ;

} /* end acm_random */

Yset_random_seed( seed )
int seed ;
{
    seed = ABS(seed) ;
    if( seed == 0 ){
	seed++ ;
    }
    randVarS = seed ;
} /* end set_random_seed */
