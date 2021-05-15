#include <stdio.h>
/* #define TW_OK 1     --------only for VMS */
/* #define TW_FAIL 0   --------only for VMS */

#define TW_OK 0     /* -------- for Unix */
#define TW_FAIL 1   /* -------- for Unix */
#define RAND (Yacm_random() )

#define TOP 1
#define BOT 0
#define YES 1
#define NO 0
#define ABORT 1
#define NOABORT 0
#define twopen(a,b,c) (openFile(a,b,c))
#define twclose(a)    (fclose(a))
extern FILE *openFile() ;

#define DENSENULL ((DENSITYPTR)NULL)
#define GRDNULL ( ( CHANGRDPTR )NULL ) 
extern int numRows, numnets , maxterm ;
extern int randVar ;
int attlimit ;
extern FILE *fpo ;
extern char cktName[] ;


typedef struct netbox {
    struct netbox *nterm ;
    int terminal ;
    int extint   ;
    int xpos     ;
    int ypos     ;
    int newx     ;
    int newy     ;
    short int row  ;
    short int cell ;
    short int net ;
#ifdef HAVE_SIGNED_CHAR
    signed char pinloc   ;
#else
    char pinloc   ;
#endif /* HAVE_SIGNED_CHAR */
    char unequiv  ;
    char flag     ;
    char layer    ;
}
*NBOXPTR ,
NBOX ;

typedef struct changrdbox {
    NBOXPTR netptr ;
    short int tracks ;
    short int ntracks ;
    short int SegType ;
    short int nSegType ;
    struct changrdbox *prevgrd ;
    struct changrdbox *nprevgrd ;
    struct changrdbox *nextgrd ;
    struct changrdbox *nnextgrd ;
    struct densitybox *dptr ;
}
*CHANGRDPTR ,
CHANGRDBOX ;

typedef struct segbox {
    short int channel ;
    int pin1    ;
    int pin2    ;
    CHANGRDPTR pin1ptr    ;
    CHANGRDPTR pin2ptr    ;
}
*SEGBOXPTR ,
SEGBOX ;

typedef struct switchbox {
    int net ;
    char nflag ;
    char ncurrent ;
    char nswYorN ;
    char current ;
    char swYorN ;
    short int key ;
    short int nkey ;
    SEGBOXPTR ntop ;
    SEGBOXPTR nbot ;
    SEGBOXPTR top    ;
    SEGBOXPTR bot    ;
}
*SWITCHBOXPTR ,
SWITCHBOX ;


typedef struct tgridbox {
    CHANGRDPTR up ;
    CHANGRDPTR down ;
}
*TGRIDPTR ,
TGRIDBOX ;

typedef struct densitybox {
    CHANGRDPTR grdptr ;
    struct densitybox *next ;
    struct densitybox *nnext ;
    struct densitybox *back ;
    struct densitybox *nback ;
}
*DENSITYPTR ,
DENSITYBOX ;

extern NBOXPTR *tearray  ;

SWITCHBOX  *aNetSeg ;
CHANGRDPTR *Begin , *End ;
TGRIDPTR *Tgrid ;
DENSITYPTR **Densebox , **DboxHead ;
int *anet , *netchgs , *fixnetseg ;

int numChans , numSegs , numSwSegs , tracks ;
int *maxTrack , *nmaxTrack , max_tdensity ;
extern int *fixarray ;
extern int stage ;
extern unsigned randomSeed2 ;


globroute()
{

FILE *fp ;
char filename[64] ;
int attperseg ;
int swSeg , flips , attempts , seg ;
int breakpoint , stoppoint ;
int found ;
SEGBOXPTR segptr ;
DENSITYPTR denptr ;
CHANGRDPTR gdptr , ptr1 , ptr2 ;
int x , x1 , x2 , channel , track ;


attperseg = 40 ;
randVar = randomSeed2 ;
fprintf( fpo, "\nThe rand generator seed was at globroute() : %d\n\n", 
							    randVar ) ;

sprintf( filename , "%s.twf" , cktName ) ;
fp = twopen ( filename , "r", ABORT ) ;
changrid( ) ;
readseg( fp ) ;
twclose( fp ) ;

if( stage == 3 ) {
    for( seg = 1 ; seg <= numSegs ; seg++ ) {
	aNetSeg[seg].current = fixarray[seg] ;
    }
}

findrcost() ;

fprintf(fpo,"\n\nTHIS IS THE ORIGINAL NUMBER OF TRACKS: %d\n\n\n" , 
							tracks ) ;
fflush(fpo);

attlimit = attperseg * numSwSegs ;
attempts = 0 ;
flips = 0    ;
stoppoint = 10 * numSwSegs ;
breakpoint = 0 ;

while( attempts < attlimit ) {
    for( ; ; ) {
	do {
	    swSeg = (int) ( (double) numSegs * ( (double) RAND / 
					  (double) 0x7fffffff ) ) + 1 ;
	} while( swSeg == numSegs + 1 ) ;
	if( aNetSeg[swSeg].swYorN == 1 && aNetSeg[swSeg].key == 0 ) {
	    break ;
	}
    }
    if( aNetSeg[swSeg].current == 0 ) {
	segptr = aNetSeg[swSeg].top ;
    } else {
	segptr = aNetSeg[swSeg].bot ;
    }
    channel = segptr->channel ;
    ptr1 = segptr->pin1ptr ;
    ptr2 = segptr->pin2ptr ;
    x1 = ptr1->netptr->xpos ;
    x2 = ptr2->netptr->xpos ;

    found = NO ;
	
    for( denptr = DboxHead[ channel ][ maxTrack[channel] ]->next
		    ; denptr != DENSENULL ; denptr = denptr->next ) {
	x = denptr->grdptr->netptr->xpos ;
	if( x1 <= x && x2 >= x ) {
	    found = YES ;
	    break ;
	}
    }

    if( !found ) {
	if( ++breakpoint > stoppoint ) {
	    break ;
	}
	attempts++ ;
	continue ;
    }

    if( urcost( swSeg ) ) {
	flips++    ;
	attempts++ ;
	breakpoint = 0 ;
    } else {
	if( ++breakpoint > stoppoint ) {
	    break ;
	}
	attempts++ ;
    }
}
for( channel = 1 ; channel <= numChans ; channel++ ) {
    for( gdptr = Begin[channel] ; gdptr != GRDNULL ;
			    gdptr = gdptr->nextgrd ) {
	gdptr->ntracks  = gdptr->tracks ;
	gdptr->nSegType = gdptr->SegType ;
	gdptr->nnextgrd = gdptr->nextgrd ;
	gdptr->nprevgrd = gdptr->prevgrd ;
	gdptr->netptr->newx = gdptr->netptr->xpos ;
	gdptr->netptr->newy = gdptr->netptr->ypos ;
    }
    for( track = 0 ; track <= max_tdensity+100 ; track++ ) {
	for( denptr = DboxHead[channel][track] ;
		denptr != DENSENULL ; denptr = denptr->next ) {
	    denptr->nnext = denptr->next ;
	    denptr->nback = denptr->back ;
	}
    }
    nmaxTrack[channel] = maxTrack[channel] ;
}
fprintf(fpo,"no. of accepted flips: %d\n", flips ) ;
fprintf(fpo,"no. of attempted flips: %d\n", attempts ) ;
if( numSwSegs != 0 ) {
    fprintf(fpo,"no. of attempted flips / numSwSegs: %.1f\n", 
			    (double) attempts / (double) numSwSegs ) ;
}
fprintf(fpo,"THIS IS THE NUMBER OF TRACKS: %d\n\n\n" , tracks ) ;
fflush(fpo);

return ;
}
