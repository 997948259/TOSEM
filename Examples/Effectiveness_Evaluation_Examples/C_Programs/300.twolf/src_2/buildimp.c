#include "standard.h"
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

IPBOXPTR xipptr ;
extern int *blkToRow ;
extern IBOXPTR *impFeeds ;


buildimp( icell, xrel , yrel , pname , flag , layer )
int icell , xrel , yrel , flag , layer ;
char pname[] ;
{

CBOXPTR ptr ;
IBOXPTR iptr ;
int row ;

if( flag == 1 ) {
    ptr = carray[ icell ] ;
    row = blkToRow[ ptr->cblock ] ;
    iptr = impFeeds[row] ;
    if( iptr != (IBOXPTR) NULL ) {
	while( iptr->niptr != (IBOXPTR) NULL ) {
	    iptr = iptr->niptr ;
	}
	iptr->niptr = (IBOXPTR) safe_malloc( sizeof( IBOX ) ) ;
	iptr = iptr->niptr ;
    } else {
	impFeeds[row] = (IBOXPTR) safe_malloc( sizeof( IBOX ) ) ;
	iptr = impFeeds[row] ;
    }
    iptr->icell = icell ;
    iptr->iactive = 0 ;
    iptr->aveXpos = ptr->cxcenter + xrel ;
    iptr->niptr = (IBOXPTR) NULL ;
    iptr->iptr = (IPBOXPTR) safe_malloc( sizeof( IPBOX ) ) ;
    xipptr = iptr->iptr ;
    xipptr->ixpos = xrel ;
    xipptr->iypos = yrel ;
    xipptr->layer = layer ;
    xipptr->ipname = (char *)safe_malloc((strlen(pname) + 1) * sizeof(char));
    sprintf( xipptr->ipname , "%s" , pname ) ;
    xipptr->npin = (IPBOXPTR) NULL ;

} else {  /* equiv pass thru pin */
    xipptr->npin = (IPBOXPTR) safe_malloc( sizeof( IPBOX ) ) ;
    xipptr = xipptr->npin ;
    xipptr->ixpos = xrel ;
    xipptr->iypos = yrel ;
    xipptr->layer = layer ;
    xipptr->ipname = (char *)safe_malloc((strlen(pname) + 1) * sizeof(char));
    sprintf( xipptr->ipname , "%s" , pname ) ;
    xipptr->npin = (IPBOXPTR) NULL ;
}
return ;
}



build_feed_imp( feed , x , row )
int feed , x , row ;
{

IBOXPTR iptr ;
char pname[128] ;

iptr = impFeeds[row] ;
if( iptr != (IBOXPTR) NULL ) {
    while( iptr->niptr != (IBOXPTR) NULL ) {
	iptr = iptr->niptr ;
    }
    iptr->niptr = (IBOXPTR) safe_malloc( sizeof( IBOX ) ) ;
    iptr = iptr->niptr ;
} else {
    impFeeds[row] = (IBOXPTR) safe_malloc( sizeof( IBOX ) ) ;
    iptr = impFeeds[row] ;
}
iptr->icell = numcells + feed ;
iptr->iactive = -1 ;
iptr->aveXpos = x - fdWidth / 2 ;
iptr->niptr = (IBOXPTR) NULL ;
iptr->iptr = (IPBOXPTR) safe_malloc( sizeof( IPBOX ) ) ;
xipptr = iptr->iptr ;
xipptr->ixpos = - fdWidth / 2 ;
xipptr->iypos = barray[1]->bheight - barray[1]->bheight / 2 ;
xipptr->layer = 0 ;
sprintf( pname , "%s.%d" , "twfeed" , feed ) ;
xipptr->ipname = (char *)safe_malloc((strlen(pname) + 1) * sizeof(char));
sprintf( xipptr->ipname , "%s" , pname ) ;

xipptr = xipptr->npin = (IPBOXPTR) safe_malloc( sizeof( IPBOX ) ) ;
xipptr->ixpos = - fdWidth / 2 ;
xipptr->iypos = - barray[1]->bheight / 2 ;
xipptr->layer = 0 ;
xipptr->ipname = (char *)safe_malloc((strlen(pname) + 1) * sizeof(char));
sprintf( xipptr->ipname , "%s" , pname ) ;
xipptr->npin = (IPBOXPTR) NULL ;

return ;
}
