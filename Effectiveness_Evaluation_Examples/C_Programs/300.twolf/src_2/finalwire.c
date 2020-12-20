#include "standard.h"
extern FILE *fpo ;
extern int numnets ;
extern int iwire ;
extern int iwirex ;
extern int iwirey ;
extern int fwire ;
extern int fwirex ;
extern int fwirey ;

finalwire( )
{

DBOXPTR dimptr ;
NBOXPTR netptr ;
int x , y , net , cost=0 ;

fwirex = 0 ;
fwirey = 0 ;

for( net = 1 ; net <= numnets ; net++ ) {
    dimptr =  netarray[ net ] ;
    if( (netptr = dimptr->netptr) != NETNULL ) {
	dimptr->xmin = dimptr->xmax = netptr->xpos ;
	dimptr->ymin = dimptr->ymax = netptr->ypos ;
	netptr = netptr->nterm ;
    }
    for( ; netptr != NETNULL ; netptr = netptr->nterm ) {
	x = netptr->xpos ;
	y = netptr->ypos ;
	if( x < dimptr->xmin ) {
	    dimptr->xmin = x ;
	} else if( x > dimptr->xmax ) {
	    dimptr->xmax = x ;
	}
	if( y < dimptr->ymin ) {
	    dimptr->ymin = y ;
	} else if( y > dimptr->ymax ) {
	    dimptr->ymax = y ;
	}
    }
    cost += ((int)( dimptr->Hweight *
	    (double)( dimptr->xmax - dimptr->xmin))) +
	    ((int)( dimptr->Vweight *
	    (double)( dimptr->ymax - dimptr->ymin)));
    fwirex += dimptr->xmax - dimptr->xmin ;
    fwirey += dimptr->ymax - dimptr->ymin ;
}
fwire = cost ;
fprintf( fpo,"\nInitial Wiring Cost: %d   Final Wiring Cost: %d\n",
						iwire , fwire ) ;
if( iwire != 0 ) {
   fprintf(fpo,"############## Percent Wire Cost Reduction: %d\n\n",
	    100 - (int)( (double)fwire / (double)iwire * 100.0 ) ) ;
}
fprintf( fpo,"\nInitial Wire Length: %d   Final Wire Length: %d\n",
	    (iwirex + iwirey) , (fwirex + fwirey) ) ;
if( iwirex + iwirey != 0 ) {
 fprintf(fpo,"************** Percent Wire Length Reduction: %d\n\n",
    100 - (int)( (double)(fwirex + fwirey) / 
		 (double)(iwirex + iwirey) * 100.0 ) ) ;
}
fprintf( fpo,"\nInitial Horiz. Wire: %d   Final Horiz. Wire: %d\n",
					    iwirex , fwirex ) ;
if( iwirex != 0 ) {
  fprintf(fpo,"$$$$$$$$$$$ Percent H-Wire Length Reduction: %d\n\n",
    100 - (int)( (double)fwirex / (double)iwirex * 100.0 ) ) ;
}
fprintf( fpo,"\nInitial Vert. Wire: %d   Final Vert. Wire: %d\n",
					    iwirey , fwirey ) ;
if( iwirey != 0 ) {
  fprintf(fpo,"@@@@@@@@@@@ Percent V-Wire Length Reduction: %d\n\n",
    100 - (int)( (double)fwirey / (double)iwirey * 100.0 ) ) ;
}
}
