#include "standard.h"
#include "groute.h"
extern FILE *fpo ;

typedef struct tmpmerg {
    int value ;
    int next  ;
    int first ;
} 
TEMPMERG ;
TEMPMERG *tmp_pinlist ;


extern int maxterm ;
extern int numnets ;
extern int numRows ;
int *pinlist ;
int pinGroup ;
int *merge_array ;
int array_length ;



mergplist()
{

int segment , i , current_net ;
int chan , track , terminal ;
DENSITYPTR denptr , temptr ;

for( chan = 1 ; chan <= numChans ; chan++ ) {
    for( track = 0 ; track <= max_tdensity+100 ; track++ ) {
	denptr = DboxHead[ chan ][ track ]->next ;
	while( denptr != DENSENULL ) {
	    temptr = denptr->next ;
	    safe_free( denptr->grdptr ) ;
	    safe_cfree( denptr ) ;
	    denptr = temptr ;
	}
	safe_cfree( DboxHead[ chan ][ track ] ) ;
    }
    safe_cfree( DboxHead[ chan ] ) ;
}
safe_cfree( DboxHead ) ;
for( terminal = 1 ; terminal <= maxterm + 2*numChans ; terminal++ ) {
    safe_free( Tgrid[ terminal ] ) ;
}
safe_free( Tgrid ) ;

pinGroup = 0 ;

pinlist = (int *) safe_malloc( (maxterm + 1) * sizeof(int) );
for( i = 1 ; i <= maxterm ; i++ ) {
    pinlist[i] = 0 ;
}

merge_array = (int *) safe_malloc( 100 * sizeof(int) );
merge_array[0] = 0 ;
tmp_pinlist = (TEMPMERG *) safe_malloc( 100 * sizeof(TEMPMERG) );
for( i = 0 ; i < 100 ; i++ ) {
    tmp_pinlist[i].value = 0 ;
    tmp_pinlist[i].next  = 0 ;
    tmp_pinlist[i].first = i ;
}
array_length = 100 ;


current_net = aNetSeg[1].net ;
for( segment = 1 ; segment <= numSegs + 1 ; segment++ ) {
    if( segment <= numSegs ) {
	if( aNetSeg[segment].net != current_net ) {
	    assign_group_values() ;
	    initialize_pins() ;
	    current_net = aNetSeg[segment].net ;
	}
	merge_pins( segment ) ;
    } else {
	assign_group_values() ;
    }
}
return ;
}




initialize_pins()
{

int i ;

for( i = 1 ; i <= merge_array[0] ; i++ ) {
    tmp_pinlist[i].value = 0 ;
    tmp_pinlist[i].next  = 0 ;
    tmp_pinlist[i].first = i ;
}
merge_array[0] = 0 ;

return ;
}





add_pins( pin )
int pin ;
{

int i ;

for( i = 1 ; i <= merge_array[0] ; i++ ) {
    if( pin == merge_array[i] ) {
	return(i) ;
    }
}

if( ++merge_array[0] >= array_length ) {
    array_length += 100 ;
    merge_array = (int *) safe_realloc( merge_array ,
				(array_length) * sizeof(int) );
    tmp_pinlist = (TEMPMERG *) safe_realloc( tmp_pinlist ,
				(array_length) * sizeof(TEMPMERG) );
    for( i = merge_array[0] ; i < merge_array[0] + 100 ; i++ ) {
	tmp_pinlist[i].value = 0 ;
	tmp_pinlist[i].next  = 0 ;
	tmp_pinlist[i].first = i ;
    }
}

merge_array[ merge_array[0] ] = pin ;

return( merge_array[0] ) ;
}





assign_group_values()
{

int i ;

for( i = 1 ; i <= merge_array[0] ; i++ ) {
    pinlist[ merge_array[i] ] = tmp_pinlist[i].value ;
}

return ;
}




merge_pins( segment )
int segment ;
{

SEGBOXPTR boxptr ;

if( aNetSeg[segment].key != 0 ) {
    aNetSeg[segment].current = aNetSeg[ aNetSeg[segment].key ].current ;
}
if( aNetSeg[segment].current == 0 ) {
    boxptr = aNetSeg[segment].top ;
} else {
    boxptr = aNetSeg[segment].bot ;
}
if( (boxptr->pin1 != boxptr->pin2) &&
    ((pinlist[boxptr->pin1] != pinlist[boxptr->pin2]) ||
			    ((pinlist[boxptr->pin1] == 0) && 
			    (pinlist[boxptr->pin2] == 0)))) { 
    merge( add_pins(boxptr->pin1) , add_pins(boxptr->pin2) ) ;
}

return ;
}




merge( i , j ) 
int i , j ;
{

int newval , next , first , secfirst ;

newval = ++pinGroup ;

secfirst = tmp_pinlist[j].first ;
first = tmp_pinlist[i].first ;

next = secfirst ;
do {
    tmp_pinlist[next].value = newval ;
    tmp_pinlist[next].first = first  ;
    next = tmp_pinlist[next].next ;
} while( next != 0 ) ;

next = first ;
for( ; ; ) {
    tmp_pinlist[next].value = newval ;
    if( tmp_pinlist[next].next != 0 ) {
	next = tmp_pinlist[next].next ;
    } else {
	tmp_pinlist[next].next = secfirst ;
	break ;
    }
}
return ;
}
