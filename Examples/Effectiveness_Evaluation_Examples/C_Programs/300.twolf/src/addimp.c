#include "standard.h"
extern int gate_array_special ;
extern int maxCellO ;
typedef struct ipbox {
    struct ipbox *npin ;
    int ixpos ;
    int iypos ;
    int layer ;
    char *ipname ;
} IPBOX , *IPBOXPTR ;

typedef struct ibox {
    struct ibox *niptr ;
    int iactive ;
    int aveXpos ;
    int icell ;
    IPBOXPTR iptr ;
} IBOX , *IBOXPTR ;

extern IBOXPTR siptr ;
extern int maxterm ;
extern int ffeeds ;
extern char **pinnames ;


addimp( row, net )
int row , net ;
{

CBOXPTR ptr ;
TEBOXPTR termptr ;
IPBOXPTR ipptr , tipptr , bipptr ;
NBOXPTR nptr , n1ptr , n2ptr ;
int pin , orient , realcell ;

realcell = siptr->icell ;
ptr = carray[ realcell ] ;
ptr->numterms += 2 ;

for( ipptr = siptr->iptr ; ; ipptr = ipptr->npin ) {
    if( ipptr->iypos > 0 ) {
	break ;
    }
}
tipptr = ipptr ;

for( ipptr = siptr->iptr ; ; ipptr = ipptr->npin ) {
    if( ipptr->iypos < 0 ) {
	break ;
    }
}
bipptr = ipptr ;

termptr = ptr->tileptr->termsptr ;
if( termptr != TERMNULL ) {
    while( termptr->nextterm != TERMNULL ) {
	termptr = termptr->nextterm ;
    }
    termptr = termptr->nextterm = (TEBOXPTR) safe_malloc(sizeof(TEBOX));
} else {
    termptr = ptr->tileptr->termsptr =(TEBOXPTR)
					safe_malloc(sizeof(TEBOX));
}
termptr->cellterm = ++maxterm ;
pinnames[maxterm] = (char *) safe_malloc( (strlen(tipptr->ipname) + 1) *
						sizeof( char ) ) ;
sprintf( pinnames[maxterm] , "%s" , tipptr->ipname ) ;
termptr->ei = maxterm ;
termptr->ue = 0 ;
tearray[maxterm] = ( NBOXPTR )safe_malloc( sizeof( NBOX ) ) ;

termptr->nextterm = (TEBOXPTR) safe_malloc(sizeof(TEBOX));
termptr->nextterm->nextterm = TERMNULL  ;
termptr->nextterm->ei = maxterm ;
termptr->nextterm->ue = 0 ;
termptr->nextterm->cellterm = ++maxterm ;
pinnames[maxterm] = (char *) safe_malloc( (strlen(bipptr->ipname) + 1) * 
						sizeof( char ) ) ;
sprintf( pinnames[maxterm] , "%s" , bipptr->ipname ) ;
tearray[maxterm] = ( NBOXPTR )safe_malloc( sizeof( NBOX ) ) ;


termptr->txpos[0] = tipptr->ixpos ;
termptr->typos[0] = tipptr->iypos ;
termptr->txpos[1] = -termptr->txpos[0] ;
termptr->typos[1] = -termptr->typos[0] ;
if( ptr->clength % 2 != 0 ) {
    termptr->txpos[1]++  ;
}
if( ptr->cheight % 2 != 0 ) {
    termptr->typos[1]++ ;
}
/*
if( gate_array_special && orient > 1 ) {
    tmptr->txpos = find_imp_x( ptr->cname , tmptr0->txpos ) ;
}
*/
pin = termptr->cellterm ;
nptr = netarray[net]->netptr ;
for( ; nptr->nterm != NETNULL ; nptr = nptr->nterm ) ;
nptr = nptr->nterm = (NBOXPTR) safe_malloc( sizeof(NBOX) ) ;
tearray[pin] = nptr ;
nptr->terminal = pin  ;
nptr->flag     = 0    ;
nptr->row      = row  ;
nptr->cell     = realcell ;
nptr->net      = net ;
nptr->extint   = termptr->ei ;
nptr->unequiv  = termptr->ue ;
nptr->layer    = tipptr->layer ;
n1ptr = nptr ;


/*  now for the second feed thru pin */
termptr = termptr->nextterm ;
termptr->txpos[0] =  bipptr->ixpos ;
termptr->typos[0] =  bipptr->iypos ;
termptr->txpos[1] = -termptr->txpos[0] ;
termptr->typos[1] = -termptr->typos[0] ;
if( ptr->clength % 2 != 0 ) {
    termptr->txpos[1]++  ;
}
if( ptr->cheight % 2 != 0 ) {
    termptr->typos[1]++ ;
}
pin = termptr->cellterm ;
nptr = nptr->nterm = (NBOXPTR) safe_malloc( sizeof(NBOX) ) ;
tearray[pin] = nptr ;
nptr->nterm = NETNULL ;
nptr->terminal = pin  ;
nptr->flag     = 0    ;
nptr->row      = row  ;
nptr->cell     = realcell ;
nptr->net      = net ;
nptr->extint   = termptr->ei ;
nptr->unequiv  = termptr->ue ;
nptr->layer    = bipptr->layer ;
n2ptr = nptr ;


/* 
 *   And now its time to worry about the other orientations
 *   which have to be generated.  Also, hopefully patch things
 *   up for the case in which fixed order groups are present.
 */

/*
 *   Now set pinloc based on the current cell orientation ---
 */
orient = ptr->corient ;
if( orient == 0 || orient == 2 ) {
    n1ptr->pinloc = 1 ;
    n2ptr->pinloc = -1 ;
} else {
    n1ptr->pinloc = -1 ;
    n2ptr->pinloc = 1 ;
}
return ;
}
