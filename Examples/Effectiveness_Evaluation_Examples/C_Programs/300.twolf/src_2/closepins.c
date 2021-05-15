#include "standard.h"
#include "route.h"
extern int maxterm ;
extern int numChans ;
extern int *key_queue ;
extern int numEdges, numGroups , numPins ;
extern csGroup *groupArray ;
extern edgeBox *edgeArray ;

closepins(tw , net )
FILE *tw ;
int net ;
{

int pin , pin1 , pin2 , minP1 , minP2 , minX , sepT , sepB , edge ;
int left , right , group1 , group2 , block1 , block2 , p1 , p2 ;
int minTop  , minBottom , maxTpin , maxBpin , otherTpin ;
int otherBpin , maxTop , maxBottom , key_count , key_flag ;
int segment_count , super_edge , next_edge ;
int e1 , e2 , g1 , g2 , next_g, save_count ;
int ltop , rtop , lbot , rbot ;
csPinBox *pArray1 , *pArray2 , *pArray ;


key_count = 0 ;
segment_count = 0 ;
super_edge = 0 ;

fprintf(tw,"net %d\n", net );
for( ; ; ) {
    if( key_count > 0 ) {
	edge = key_queue[ key_count-- ] ;
	group1 = edgeArray[edge].group1 ;
	key_flag = save_count ;
	ltop = lbot = rtop = rbot = -1 ;
	    /* pseudo zero length segment */
    } else {
	while( ++super_edge <= numEdges ) {
	    if( edgeArray[super_edge].marked == NO ) {
		continue ;
	    }
	    if( edgeArray[super_edge].done == NO ) {
		break ;
	    }
	}
	if( super_edge > numEdges ) {
	    break ;
	}
	edge = super_edge ;
	key_flag = 0 ;
	ltop = lbot = rtop = rbot = 0 ;
	    /* potentially normal segment */
    }

    segment_count++ ;

    maxTop  = -1000000000 ;
    maxBottom = -1000000000 ;
    maxTpin = 0 ;
    maxBpin = 0 ;
    group1  = edgeArray[edge].group1 ;
    pArray1 = groupArray[group1].pinArray ;
    block1  = groupArray[group1].block ;
    group2  = edgeArray[ edge ].group2 ;
    pArray2 = groupArray[group2].pinArray ;
    block2  = groupArray[group2].block ;

    if( edgeArray[edge].poison == NO && key_flag == NO) {
	save_count = segment_count ;
	edgeArray[edge].done = YES ;
	key_flag = save_count ;
	/*
	 *   Find the cumulative span
	 */
	e1 = edge ;
	g1 = edgeArray[e1].group1 ;
	for( ; ; ) {
	    if( groupArray[g1].poison == YES ) {
		/*
		 *   Only YES if an EQUIV group
		 */
		break ;
	    }
	    if( groupArray[g1].edge1 == e1 ) {
		next_edge = groupArray[g1].edge2 ;
	    } else {
		next_edge = groupArray[g1].edge1 ;
	    }
	    if( next_edge == 0 ) {
		break ;
	    }
	    next_g = edgeArray[next_edge].group1 ;
	    if( next_g == g1 ) {
		g1 = edgeArray[next_edge].group2 ;
	    } else {
		g1 = next_g ;
	    }
	    e1 = next_edge ;
	    edgeArray[e1].done = YES ;
	    key_queue[ ++key_count ] = e1 ;
	}
	e2 = edge ;
	g2 = edgeArray[e2].group2 ;
	for( ; ; ) {
	    if( groupArray[g2].poison == YES ) {
		break ;
	    }
	    if( groupArray[g2].edge1 == e2 ) {
		next_edge = groupArray[g2].edge2 ;
	    } else {
		next_edge = groupArray[g2].edge1 ;
	    }
	    if( next_edge == 0 ) {
		break ;
	    }
	    next_g = edgeArray[next_edge].group1 ;
	    if( next_g == g2 ) {
		g2 = edgeArray[next_edge].group2 ;
	    } else {
		g2 = next_g ;
	    }
	    e2 = next_edge ;
	    edgeArray[e2].done = YES ;
	    key_queue[ ++key_count ] = e2 ;
	}
	if( groupArray[g1].aveX <= groupArray[g2].aveX ) {
	    pArray = groupArray[g1].pinArray ;
	    for(pin = 1; pin <= groupArray[g1].numPins; pin++ ){
		if( pArray[pin].top == 1 || pArray[pin].top == 0){
		    ltop = pArray[pin].pin ;
		}
		if(pArray[pin].top == -1 || pArray[pin].top == 0){
		    lbot = pArray[pin].pin ;
		}
	    }
	    pArray = groupArray[g2].pinArray ;
	    for(pin = 1; pin <= groupArray[g2].numPins; pin++ ){
		if( pArray[pin].top == 1 || pArray[pin].top == 0){
		    rtop = pArray[pin].pin ;
		}
		if(pArray[pin].top == -1 || pArray[pin].top == 0){
		    rbot = pArray[pin].pin ;
		}
	    }
	} else {
	    pArray = groupArray[g2].pinArray ;
	    for(pin = 1; pin <= groupArray[g2].numPins; pin++ ){
		if( pArray[pin].top == 1 || pArray[pin].top == 0){
		    ltop = pArray[pin].pin ;
		}
		if(pArray[pin].top == -1 || pArray[pin].top == 0){
		    lbot = pArray[pin].pin ;
		}
	    }
	    pArray = groupArray[g1].pinArray ;
	    for(pin = 1; pin <= groupArray[g1].numPins; pin++ ){
		if( pArray[pin].top == 1 || pArray[pin].top == 0){
		    rtop = pArray[pin].pin ;
		}
		if(pArray[pin].top == -1 || pArray[pin].top == 0){
		    rbot = pArray[pin].pin ;
		}
	    }
	}
    }


    if( block1 == block2 ) {
	    /* potentially a switchable net segment */
	if( groupArray[group1].aveX <= groupArray[group2].aveX){
	    for(pin = 1; pin <= groupArray[group1].numPins; pin++ ){
		if( pArray1[pin].top == 1 || pArray1[pin].top == 0){
		    if( pArray1[ pin ].xloc > maxTop ) {
			maxTop = pArray1[ pin ].xloc ;
			maxTpin = pArray1[ pin ].pin ;
		    }
		}
		if(pArray1[pin].top == -1 || pArray1[pin].top == 0){
		    if( pArray1[ pin ].xloc > maxBottom ) {
			maxBottom = pArray1[ pin ].xloc ;
			maxBpin = pArray1[ pin ].pin ;
		    }
		}
	    }
	    sepT = 1000000000 ;
	    sepB = 1000000000 ;
	    otherTpin = 0 ;
	    otherBpin = 0 ;
	    for(pin = 1; pin <= groupArray[group2].numPins; pin++ ){
		if( pArray2[pin].top == 1 || pArray2[pin].top == 0){
		    if( ABS(pArray2[ pin ].xloc - maxTop) < sepT ) {
			otherTpin = pArray2[ pin ].pin ;
			minTop = pArray2[ pin ].xloc ;
			sepT = ABS( minTop - maxTop ) ;
		    }
		}
		if(pArray2[pin].top == -1 || pArray2[pin].top == 0){
		    if( ABS(pArray2[pin].xloc - maxBottom) < sepB ){
			otherBpin = pArray2[ pin ].pin ;
			minBottom = pArray2[ pin ].xloc ;
			sepB = ABS( minBottom - maxBottom );
		    }
		}
	    }
	    if( maxTpin != 0 && otherTpin != 0 && block1 < numChans && 
		    ( (!(maxBpin != 0 && otherBpin != 0)) ||
		      ( (maxBpin != 0 && otherBpin != 0)  &&
			maxBottom != minBottom)  )  ) {

		if( maxBpin != 0 && otherBpin != 0 && block1 > 0 &&
						maxTop != minTop ) {

		    /* a switchable net segment */

		    fprintf(tw,"segment switchable %d\n", key_flag );
		    fprintf(tw,"top channel %d\n", (block1 + 1) );
		    if( maxTop <= minTop ) {
			p1  = maxTpin ;
			p2  = otherTpin ;
		    } else {
			p1  = otherTpin ;
			p2  = maxTpin ;
		    }
		    fprintf(tw,"pin1 %d  pin2 %d %d %d\n"
		    , p1 , p2 , ltop , rtop ) ;

		    fprintf(tw,"bottom channel %d\n", block1 );
		    if( maxBottom <= minBottom ) {
			p1  = maxBpin ;
			p2  = otherBpin ;
		    } else {
			p1  = otherBpin ;
			p2  = maxBpin ;
		    }
		    fprintf(tw,"pin1 %d  pin2 %d %d %d\n"
		    , p1 , p2 , lbot , rbot ) ;
		} else {  /* only a top segment here */
		    fprintf(tw,"segment channel %d\n",(block1 + 1));
		    if( maxTop <= minTop ) {
			p1  = maxTpin ;
			p2  = otherTpin ;
		    } else {
			p1  = otherTpin ;
			p2  = maxTpin ;
		    }
		    fprintf(tw,"pin1 %d  pin2 %d %d %d\n"
		    , p1 , p2 , ltop , rtop ) ;
		}
	    } else if( maxBpin != 0 && otherBpin != 0 ) {
		/* only a bottom segment here */
		fprintf(tw,"segment channel %d\n", block1);
		if( maxBottom <= minBottom ) {
		    p1  = maxBpin ;
		    p2  = otherBpin ;
		} else {
		    p1  = otherBpin ;
		    p2  = maxBpin ;
		}
		fprintf(tw,"pin1 %d  pin2 %d %d %d\n"
		, p1 , p2 , lbot , rbot ) ;
	    }
	} else {
	    for(pin = 1; pin <= groupArray[group2].numPins ; pin++){
		if( pArray2[pin].top == 1 || pArray2[pin].top == 0){
		    if( pArray2[ pin ].xloc > maxTop ) {
			maxTop  = pArray2[ pin ].xloc ;
			maxTpin = pArray2[ pin ].pin ;
		    }
		}
		if(pArray2[pin].top == -1 || pArray2[pin].top == 0){
		    if( pArray2[ pin ].xloc > maxBottom ) {
			maxBottom = pArray2[ pin ].xloc ;
			maxBpin = pArray2[ pin ].pin ;
		    }
		}
	    }
	    sepT = 1000000000 ;
	    sepB = 1000000000 ;
	    otherTpin = 0 ;
	    otherBpin = 0 ;
	    for(pin = 1; pin <= groupArray[group1].numPins ; pin++){
		if( pArray1[pin].top == 1 || pArray1[pin].top == 0){
		    if( ABS(pArray1[ pin ].xloc - maxTop) < sepT ) {
			otherTpin = pArray1[ pin ].pin ;
			minTop = pArray1[ pin ].xloc ;
			sepT = ABS(minTop - maxTop ) ;
		    }
		}
		if(pArray1[pin].top == -1 || pArray1[pin].top == 0){
		    if( ABS(pArray1[pin].xloc - maxBottom) < sepB ){
		      otherBpin = pArray1[ pin ].pin ;
		      minBottom = pArray1[ pin ].xloc ;
		      sepB = ABS(minBottom - maxBottom) ;
		    }
		}
	    }
	    if( maxTpin != 0 && otherTpin != 0 && block1 < numChans &&
		    ( (!(maxBpin != 0 && otherBpin != 0)) ||
		      ( (maxBpin != 0 && otherBpin != 0)  &&
			maxBottom != minBottom)  )  ) {

		if( maxBpin != 0 && otherBpin != 0 && 
				    block1 > 0 && maxTop != minTop ) {

		    /* a switchable net segment */

		    fprintf(tw,"segment switchable %d\n", key_flag );
		    fprintf(tw,"top channel %d\n", (block1 + 1) );
		    if( maxTop <= minTop ) {
			p1  = maxTpin ;
			p2  = otherTpin ;
		    } else {
			p1  = otherTpin ;
			p2  = maxTpin ;
		    }
		    fprintf(tw,"pin1 %d  pin2 %d %d %d\n"
		    , p1 , p2 , ltop , rtop ) ;

		    fprintf(tw,"bottom channel %d\n", block1 );
		    if( maxBottom <= minBottom ) {
			p1  = maxBpin ;
			p2  = otherBpin ;
		    } else {
			p1  = otherBpin ;
			p2  = maxBpin ;
		    }
		    fprintf(tw,"pin1 %d  pin2 %d %d %d\n"
		    , p1 , p2 , lbot , rbot ) ;
		} else {  /* only a top segment here */
		    fprintf(tw,"segment channel %d\n",(block1 + 1));
		    if( maxTop <= minTop ) {
			p1  = maxTpin ;
			p2  = otherTpin ;
		    } else {
			p1  = otherTpin ;
			p2  = maxTpin ;
		    }
		    fprintf(tw,"pin1 %d  pin2 %d %d %d\n"
		    , p1 , p2 , ltop , rtop ) ;
		}
	    } else if( maxBpin != 0 && otherBpin != 0 ) {
		  /* only a bottom segment here */
		fprintf(tw,"segment channel %d\n", block1 );
		if( maxBottom <= minBottom ) {
		    p1  = maxBpin ;
		    p2  = otherBpin ;
		} else {
		    p1  = otherBpin ;
		    p2  = maxBpin ;
		}
		fprintf(tw,"pin1 %d  pin2 %d %d %d\n"
		, p1 , p2 , lbot , rbot ) ;
	    }
	}
    } else {  /* non-switchable from one block to another */
	minX = 1000000000 ;
	minP1 = 0 ;
	minP2 = 0 ;
	if( block1 > block2 ) { /* get top of group2.... */
	    for(pin1 = 1;pin1 <= groupArray[group1].numPins;pin1++){
		if( pArray1[pin1].top == -1 ||
					pArray1[pin1].top == 0 ) {
		    pin2 = 1 ;
		    for(;pin2 <= groupArray[group2].numPins;pin2++){
			if( pArray2[ pin2 ].top == 1 ||
					pArray2[pin2].top == 0 ) {
			    if( ABS( pArray1[ pin1 ].xloc -
				   pArray2[ pin2 ].xloc ) < minX ) {
				left  = pArray1[pin1].xloc;
				right = pArray2[pin2].xloc;
				minX  = ABS( left - right );
				minP1 = pArray1[pin1].pin;
				minP2 = pArray2[pin2].pin;
			    }
			}
		    }
		}
	    }
	    if( minP1 != 0 && minP2 != 0 ) {
		fprintf(tw,"segment channel %d\n", block1 );
		if( left > right ) {
		    fprintf(tw," pin1 %d  pin2 %d %d %d\n"
		    , minP2 , minP1 , ltop , rtop );
		} else {
		    fprintf(tw," pin1 %d  pin2 %d %d %d\n"
		    , minP1 , minP2 , ltop , rtop );
		}
	    }
	} else {   /* block1 < block2 */
	    pin1 = 1 ;
	    for(; pin1 <= groupArray[group1].numPins; pin1++ ) {
		if( pArray1[pin1].top == 1 ||
					pArray1[pin1].top == 0 ) {
		    pin2 = 1 ;
		    for(;pin2 <= groupArray[group2].numPins;pin2++){
			if( pArray2[ pin2 ].top == -1 ||
					pArray2[pin2].top == 0 ) {
			    if( ABS( pArray1[ pin1 ].xloc -
				   pArray2[ pin2 ].xloc ) < minX ) {
				left = pArray1[pin1].xloc;
				right = pArray2[pin2].xloc;
				minX = ABS( left - right ) ;
				minP1 = pArray1[pin1].pin;
				minP2 = pArray2[pin2].pin;
			    }
			}
		    }
		}
	    }
	    if( minP1 != 0 && minP2 != 0 ) {
		fprintf(tw,"segment channel %d\n", block2 );
		if( left > right ) {
		    fprintf(tw," pin1 %d  pin2 %d %d %d\n"
		    , minP2 , minP1 , ltop , rtop );
		} else {
		    fprintf(tw," pin1 %d  pin2 %d %d %d\n"
		    , minP1 , minP2 , ltop , rtop );
		}
	    }
	}
    }
}
return ;
}
