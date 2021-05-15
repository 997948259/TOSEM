#include "standard.h"
#include "route.h"
#include "groute.h"
#define DEBUG
#define YES 1
#define NO 0
extern int *key_queue ;
extern csGroup *groupArray ;
extern edgeBox *edgeArray ;
extern int numRows ;

extern int numEdges, numGroups , numPins ;

uclosepns(net)
int net ;
{

int pin , pin1 , pin2 , minP1 , minP2 , minX , sepT , sepB , edge ;
int group1 , group2 , block1 , block2 , p1 , p2 ;
int Tleft , Tright , Bleft , Bright ;
int minTop  , minBottom , maxTpin , maxBpin , otherTpin ;
int otherBpin , maxTop , maxBottom , segIndex ;
int k_left , k_right , super_edge ;
int e1 , e2 , g1 , g2 , next_edge , next_g, save_count ;
int key_flag , key_count , fault_line ;
int channel , left , right ;
int ltop , rtop , lbot , rbot ;
csPinBox *pArray1 , *pArray2 , *pArray ;
SEGBOXPTR tmp_ptr ;


key_count = 0 ;
super_edge = 0 ;

segIndex = anet[net] - 1 ;
fault_line = anet[net + 1] ;

for( ; ; ) {
    if( key_count > 0 ) {
	edge = key_queue[ key_count-- ] ;
	group1 = edgeArray[edge].group1 ;
	k_left  = groupArray[group1].aveX ;
	k_right = k_left ;
	key_flag = save_count ;
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
    }

    segIndex++ ;
#ifdef DEBUG
    if( segIndex >= fault_line ) {
	printf("Serious fault detected in function: uclosepns():");
	printf("   Net:%d\n", net );
	fflush(stdout);
    }
#endif
    aNetSeg[segIndex].nflag = 1 ;
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
	save_count = segIndex ;
	edgeArray[edge].done = YES ;
	key_flag = save_count ;
	/*
	 *   Find the cumulative span
	 */
	e1 = edge ;
	g1 = edgeArray[e1].group1 ;
	for( ; ; ) {
	    if( groupArray[g1].poison == YES ) {
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
	    k_left  = groupArray[g1].aveX ;
	    k_right = groupArray[g2].aveX ;
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
	    k_left  = groupArray[g2].aveX ;
	    k_right = groupArray[g1].aveX ;
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
	    if( maxTpin != 0 && otherTpin != 0 &&
					    block1 < numChans ) {
		if( maxBpin != 0 && otherBpin != 0 && block1 > 0 ) {
				/* switchable net segment */
		    aNetSeg[segIndex].nswYorN = 1 ;
		    if( key_flag == 0 || key_flag == segIndex ) {
			aNetSeg[segIndex].nkey = 0 ;
		    } else {
			aNetSeg[segIndex].nkey = key_flag ;
		    }
		    aNetSeg[segIndex].ncurrent = 0 ;
		    if( maxTop <= minTop ) {
			Tleft  = maxTop ;
			Tright = minTop ;
			p1  = maxTpin ;
			p2  = otherTpin ;
		    } else {
			Tleft  = minTop ;
			Tright = maxTop ;
			p1  = otherTpin ;
			p2  = maxTpin ;
		    }
		    if( key_flag != NO ) {
			Tleft  = k_left ;
			Tright = k_right ;
		    }
		    aNetSeg[segIndex].ntop->channel = block1 + 1;
		    aNetSeg[segIndex].ntop->pin1 = p1 ;
		    aNetSeg[segIndex].ntop->pin2 = p2 ;

		    if( maxBottom <= minBottom ) {
			Bleft  = maxBottom ;
			Bright = minBottom ;
			p1  = maxBpin ;
			p2  = otherBpin ;
		    } else {
			Bleft  = minBottom ;
			Bright = maxBottom ;
			p1  = otherBpin ;
			p2  = maxBpin ;
		    }
		    if( key_flag != NO ) {
			Bleft  = k_left ;
			Bright = k_right ;
		    }
		    aNetSeg[segIndex].nbot->channel = block1 ;
		    aNetSeg[segIndex].nbot->pin1 = p1 ;
		    aNetSeg[segIndex].nbot->pin2 = p2 ;

		    if( Bleft == Bright || Tleft == Tright ) {
			aNetSeg[segIndex].nswYorN = 0 ;
			if( Bleft == Bright && Tleft != Tright ) {
			    tmp_ptr = aNetSeg[segIndex].ntop ;
			    aNetSeg[segIndex].ntop = 
					aNetSeg[segIndex].nbot ;
			    aNetSeg[segIndex].nbot = tmp_ptr ;
			}
		    }
		} else {  /* only a top segment here */
		    aNetSeg[segIndex].nswYorN = 0 ;
		    aNetSeg[segIndex].nkey    = 0 ;
		    aNetSeg[segIndex].ncurrent = 0 ;
		    if( maxTop <= minTop ) {
			p1  = maxTpin ;
			p2  = otherTpin ;
		    } else {
			p1  = otherTpin ;
			p2  = maxTpin ;
		    }
		    aNetSeg[segIndex].ntop->channel = block1 + 1;
		    aNetSeg[segIndex].ntop->pin1 = p1 ;
		    aNetSeg[segIndex].ntop->pin2 = p2 ;
		}
	    } else if( maxBpin != 0 && otherBpin != 0 ) {
		/* only a bottom segment here */
		aNetSeg[segIndex].nswYorN = 0 ;
		aNetSeg[segIndex].nkey    = 0 ;
		aNetSeg[segIndex].ncurrent = 0 ;
		if( maxBottom <= minBottom ) {
		    p1  = maxBpin ;
		    p2  = otherBpin ;
		} else {
		    p1  = otherBpin ;
		    p2  = maxBpin ;
		}
		aNetSeg[segIndex].ntop->channel = block1 ;
		aNetSeg[segIndex].ntop->pin1 = p1 ;
		aNetSeg[segIndex].ntop->pin2 = p2 ;
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
	    if( maxTpin != 0 && otherTpin != 0 &&
					    block1 < numChans ) {
		if( maxBpin != 0 && otherBpin != 0 && block1 > 0 ) {
				/* a switchable net segment */
		    aNetSeg[segIndex].nswYorN = 1 ;
		    if( key_flag == 0 || key_flag == segIndex ) {
			aNetSeg[segIndex].nkey = 0 ;
		    } else {
			aNetSeg[segIndex].nkey = key_flag ;
		    }
		    aNetSeg[segIndex].ncurrent = 0 ;
		    if( maxTop <= minTop ) {
			Tleft  = maxTop ;
			Tright = minTop ;
			p1  = maxTpin ;
			p2  = otherTpin ;
		    } else {
			Tleft  = minTop ;
			Tright = maxTop ;
			p1  = otherTpin ;
			p2  = maxTpin ;
		    }
		    if( key_flag != NO ) {
			Tleft  = k_left ;
			Tright = k_right ;
		    }
		    aNetSeg[segIndex].ntop->channel = block1 + 1;
		    aNetSeg[segIndex].ntop->pin1 = p1 ;
		    aNetSeg[segIndex].ntop->pin2 = p2 ;

		    if( maxBottom <= minBottom ) {
			Bleft  = maxBottom ;
			Bright = minBottom ;
			p1  = maxBpin ;
			p2  = otherBpin ;
		    } else {
			Bleft  = minBottom ;
			Bright = maxBottom ;
			p1  = otherBpin ;
			p2  = maxBpin ;
		    }
		    if( key_flag != NO ) {
			Bleft  = k_left ;
			Bright = k_right ;
		    }
		    aNetSeg[segIndex].nbot->channel = block1 ;
		    aNetSeg[segIndex].nbot->pin1 = p1 ;
		    aNetSeg[segIndex].nbot->pin2 = p2 ;

		    if( Bleft == Bright || Tleft == Tright ) {
			aNetSeg[segIndex].nswYorN = 0 ;
			if( Bleft == Bright && Tleft != Tright ) {
			    tmp_ptr = aNetSeg[segIndex].ntop ;
			    aNetSeg[segIndex].ntop = 
					aNetSeg[segIndex].nbot ;
			    aNetSeg[segIndex].nbot = tmp_ptr ;
			}
		    }
		} else {  /* only a top segment here */
		    aNetSeg[segIndex].nswYorN = 0 ;
		    aNetSeg[segIndex].nkey    = 0 ;
		    aNetSeg[segIndex].ncurrent = 0 ;
		    if( maxTop <= minTop ) {
			p1  = maxTpin ;
			p2  = otherTpin ;
		    } else {
			p1  = otherTpin ;
			p2  = maxTpin ;
		    }
		    aNetSeg[segIndex].ntop->channel = block1 + 1;
		    aNetSeg[segIndex].ntop->pin1 = p1 ;
		    aNetSeg[segIndex].ntop->pin2 = p2 ;
		}
	    } else if( maxBpin != 0 && otherBpin != 0 ) {
		  /* only a bottom segment here */
		aNetSeg[segIndex].nswYorN = 0 ;
		aNetSeg[segIndex].nkey    = 0 ;
		aNetSeg[segIndex].ncurrent = 0 ;
		if( maxBottom <= minBottom ) {
		    p1  = maxBpin ;
		    p2  = otherBpin ;
		} else {
		    p1  = otherBpin ;
		    p2  = maxBpin ;
		}
		aNetSeg[segIndex].ntop->channel = block1 ;
		aNetSeg[segIndex].ntop->pin1 = p1 ;
		aNetSeg[segIndex].ntop->pin2 = p2 ;
	    }
	}
	if( aNetSeg[segIndex].nswYorN == 1 || key_flag != NO ) {
	    channel = aNetSeg[segIndex].ntop->channel ;
	    if( key_flag == NO ) {
		pin1 = aNetSeg[segIndex].ntop->pin1 ;
		pin2 = aNetSeg[segIndex].ntop->pin2 ;
	    } else {
		if( k_right > k_left ) {
		    pin1 = ltop ;
		    pin2 = rtop ;
		} else {
		    pin1 = pin2 = aNetSeg[segIndex].ntop->pin1 ;
		}
	    }
	    aNetSeg[segIndex].ntop->pin1ptr = Tgrid[ pin1 ]->up ;
	    if( tearray[ pin1 ]->pinloc == 0 &&
		tearray[ pin1 ]->row == channel ) {
		aNetSeg[segIndex].ntop->pin1ptr = Tgrid[pin1]->down;
	    }
	    aNetSeg[segIndex].ntop->pin2ptr = Tgrid[ pin2 ]->up ;
	    if( tearray[ pin2 ]->pinloc == 0 &&
		tearray[ pin2 ]->row == channel ) {
		aNetSeg[segIndex].ntop->pin2ptr = Tgrid[pin2]->down;
	    }

	    channel = aNetSeg[segIndex].nbot->channel ;
	    if( key_flag == NO ) {
		pin1 = aNetSeg[segIndex].nbot->pin1 ;
		pin2 = aNetSeg[segIndex].nbot->pin2 ;
	    } else {
		if( k_right > k_left ) {
		    pin1 = lbot ;
		    pin2 = rbot ;
		} else {
		    pin1 = pin2 = aNetSeg[segIndex].nbot->pin1 ;
		}
	    }
	    aNetSeg[segIndex].nbot->pin1ptr = Tgrid[ pin1 ]->up ;
	    if( tearray[ pin1 ]->pinloc == 0 &&
		tearray[ pin1 ]->row == channel ) {
		aNetSeg[segIndex].nbot->pin1ptr = Tgrid[pin1]->down;
	    }
	    aNetSeg[segIndex].nbot->pin2ptr = Tgrid[ pin2 ]->up ;
	    if( tearray[ pin2 ]->pinloc == 0 &&
		tearray[ pin2 ]->row == channel ) {
		aNetSeg[segIndex].nbot->pin2ptr = Tgrid[pin2]->down;
	    }
	} else {
	    channel = aNetSeg[segIndex].ntop->channel ;
	    if( key_flag == NO ) {
		pin1 = aNetSeg[segIndex].ntop->pin1 ;
		pin2 = aNetSeg[segIndex].ntop->pin2 ;
	    } else {
		if( k_right > k_left ) {
		    pin1 = ltop ;
		    pin2 = rtop ;
		} else {
		    pin1 = pin2 = aNetSeg[segIndex].ntop->pin1 ;
		}
	    }
	    aNetSeg[segIndex].ntop->pin1ptr = Tgrid[ pin1 ]->up ;
	    if( tearray[ pin1 ]->pinloc == 0 &&
		tearray[ pin1 ]->row == channel ) {
		aNetSeg[segIndex].ntop->pin1ptr = Tgrid[pin1]->down;
	    }
	    aNetSeg[segIndex].ntop->pin2ptr = Tgrid[ pin2 ]->up ;
	    if( tearray[ pin2 ]->pinloc == 0 &&
		tearray[ pin2 ]->row == channel ) {
		aNetSeg[segIndex].ntop->pin2ptr = Tgrid[pin2]->down;
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
		aNetSeg[segIndex].nswYorN = 0 ;
		aNetSeg[segIndex].nkey    = 0 ;
		aNetSeg[segIndex].ncurrent = 0 ;
		if( left > right ) {
		    aNetSeg[segIndex].ntop->channel = block1 ;
		    aNetSeg[segIndex].ntop->pin1 = minP2 ;
		    aNetSeg[segIndex].ntop->pin2 = minP1 ;
		} else {
		    aNetSeg[segIndex].ntop->channel = block1 ;
		    aNetSeg[segIndex].ntop->pin1 = minP1 ;
		    aNetSeg[segIndex].ntop->pin2 = minP2 ;
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
		aNetSeg[segIndex].nswYorN = 0 ;
		aNetSeg[segIndex].nkey    = 0 ;
		aNetSeg[segIndex].ncurrent = 0 ;
		if( left > right ) {
		    aNetSeg[segIndex].ntop->channel = block2 ;
		    aNetSeg[segIndex].ntop->pin1 = minP2 ;
		    aNetSeg[segIndex].ntop->pin2 = minP1 ;
		} else {
		    aNetSeg[segIndex].ntop->channel = block2 ;
		    aNetSeg[segIndex].ntop->pin1 = minP1 ;
		    aNetSeg[segIndex].ntop->pin2 = minP2 ;
		}
	    }
	}
	channel = aNetSeg[segIndex].ntop->channel ;
	pin1 = aNetSeg[segIndex].ntop->pin1 ;
	pin2 = aNetSeg[segIndex].ntop->pin2 ;
	aNetSeg[segIndex].ntop->pin1ptr = Tgrid[ pin1 ]->up ;
	if( tearray[ pin1 ]->pinloc == 0 &&
	    tearray[ pin1 ]->row == channel ) {
	    aNetSeg[segIndex].ntop->pin1ptr = Tgrid[pin1]->down;
	}
	aNetSeg[segIndex].ntop->pin2ptr = Tgrid[ pin2 ]->up ;
	if( tearray[ pin2 ]->pinloc == 0 &&
	    tearray[ pin2 ]->row == channel ) {
	    aNetSeg[segIndex].ntop->pin2ptr = Tgrid[pin2]->down;
	}
    }
}
#ifdef DEBUG
if( segIndex != fault_line - 1 ) {
    printf("Serious FAULT detected in function: uclosepns():");
    printf("   Net:%d\n", net );
    fflush(stdout);
}
#endif
return ;
}
