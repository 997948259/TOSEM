#include "standard.h"
#include "route.h"
#include "groute.h"

#define T   2 
#define R   3 
#define GOING_UP 1
#define GOING_DN -1
#define GOING_UP_OR_DN 0
#define SAME_ROW 0
#define UP_ROW 1
#define DN_ROW -1
#define TOP_SIDE 1
#define BOT_SIDE -1
#define BOTH_SIDES 0
#define UNEQUIV_SIDES 2
#define SUCCESS 1
#define FAILURE 0

extern int *blkToRow ;

extern int **pseudoPins ;
extern int **pseudoEdge ;
extern int rowHeight ;
 
extern int *key_queue ;
extern int numEdges, numGroups , numPins ;
extern int top_row ;
 
uglobe() 
{

NBOXPTR netptr ;
CBOXPTR cellptr1 , cellptr2 ;
int group1 , group2 , edge , i , pin , net , group , cell1 , cell2 ;
int top , extint , block , locX , locY ;
int flag1 , flag2 , chgloop ;
int found, type1 ;
int unequiv , added_an_edge , ue_grp , g1 , g2 , ei1 , ei2 ;
int ei , done , edge2 , jj ;
int a1 , b1 , a2 , b2 , edge1 , ya , yb ;
int single_pin1 , single_pin2 , unequiv1 , unequiv2 ;

for(  i = 0 ; i <= MPG ; i++ ){
    groupArray[i].numPins = 0 ;
    groupArray[i].flag    = 0 ;
    groupArray[i].poison  = 0 ;
    groupArray[i].unequiv = 0 ;
    groupArray[i].extint  = 0 ;
    groupArray[i].edge1   = 0 ;
    groupArray[i].edge2   = 0 ;
    groupArray[i].check   = 0 ;
}
for(  i = 0 ; i <= ME ; i++ ){
    edgeArray[i].marked = 0 ;
    edgeArray[i].done   = 0 ;
    edgeArray[i].poison = 0 ;
}

for( chgloop = 1 ; chgloop <= netchgs[0] ; chgloop++ ) {
    net = netchgs[chgloop] ;
    numEdges = 0 ;
    top_row = -1 ;
    for( jj = 0 ; jj <= numRows + 1 ; jj++ ) {
	pseudoPins[jj][0] = 0 ;
	pseudoPins[jj][1] = 0 ;
	pseudoEdge[jj][0] = 0 ;
	pseudoEdge[jj][1] = 0 ;
    }
    netptr = netarray[net]->netptr ;
    for( ; netptr != NETNULL ; netptr = netptr->nterm ) {
	top    = netptr->pinloc   ;
	extint = netptr->extint   ;
	unequiv = netptr->unequiv ;
	block  = netptr->row      ;
	if( block > top_row ) {
	    if( netptr->cell <= numcells ) {
		top_row = block ;
	    } else if( carray[netptr->cell]->padside != L &&
		       carray[netptr->cell]->padside != R ) {
		top_row = block ;
	    }
	}
	locX   = netptr->xpos     ;
	locY   = netptr->ypos     ;
	pin    = netptr->terminal ;

	found = FAILURE ;
	group = 1 ;
	while( groupArray[ group ].numPins != 0 && found == FAILURE ){
	    if( groupArray[ group ].extint == extint && unequiv == NO ) {
		found = SUCCESS ;
	    } else {
		group++ ;
	    }
	}
	numPins = groupArray[ group ].numPins + 1 ;
	groupArray[ group ].numPins = numPins ;
	groupArray[ group ].pinArray[ numPins ].xloc = locX ;
	groupArray[ group ].pinArray[ numPins ].yloc = locY ;
	groupArray[ group ].pinArray[ numPins ].top = top ;
	groupArray[ group ].pinArray[ numPins ].pin = pin ;
	if( found == FAILURE ) {
	    groupArray[ group ].aveX   = locX   ;
	    groupArray[ group ].aveY   = locY   ;
	    groupArray[ group ].extint = extint ;
	    groupArray[ group ].unequiv = unequiv ;
	    groupArray[ group ].block  = block  ;
	} else {
	    /*
	     *    a pin with this extint already here 
	     *    the ave field currently houses a sum ---
 	     *    it will be converted later to an average 
	     */
	    groupArray[ group ].aveX += locX ;
	    groupArray[ group ].aveY += locY ;
	}
    }
    group = 1 ;
    for( group = 1; groupArray[ group ].numPins != 0 ; group++ ) {
	numPins = groupArray[ group ].numPins ;
	if( numPins > 1  ) {
	    groupArray[group].aveX /= numPins ;
	    groupArray[group].aveY /= numPins ;
	}
    }
    /*  
     *   And now it is time to construct the graph and
     *   find the MST  
     */
    numGroups = 0 ;
    while( groupArray[ numGroups + 1 ].numPins != 0 ) {
	numGroups++ ; 
    }
    if( numGroups == 2 ) {
	if( groupArray[1].unequiv == 1 && groupArray[2].unequiv == 1 ) {
	    for( i = 1 ; i <= numGroups ; i++ ) {
		groupArray[i].numPins = 0 ;
		groupArray[i].flag    = 0 ;
		groupArray[i].poison  = 0 ;
		groupArray[i].unequiv = 0 ;
		groupArray[i].extint  = 0 ;
		groupArray[i].edge1   = 0 ;
		groupArray[i].edge2   = 0 ;
		groupArray[i].check   = 0 ;
	    }
	    for( i = 1 ; i <= numEdges ; i++ ) {
		edgeArray[i].marked = 0 ;
		edgeArray[i].done   = 0 ;
		edgeArray[i].poison = 0 ;
	    }
	    continue ;
	}
    } else if( numGroups <= 1 ) {   /* forget it  */
	for( i = 1 ; i <= numGroups ; i++ ) {
	    groupArray[i].numPins = 0 ;
	    groupArray[i].flag    = 0 ;
	    groupArray[i].poison  = 0 ;
	    groupArray[i].unequiv = 0 ;
	    groupArray[i].extint  = 0 ;
	    groupArray[i].edge1   = 0 ;
	    groupArray[i].edge2   = 0 ;
	    groupArray[i].check   = 0 ;
	}
	for( i = 1 ; i <= numEdges ; i++ ) {
	    edgeArray[i].marked = 0 ;
	    edgeArray[i].done   = 0 ;
	    edgeArray[i].poison = 0 ;
	}
	continue ;
    }

    qsortg((char *)(groupArray + 1), numGroups,sizeof(csGroup));

    /* 
     *       step 2.  Form the graph which has the nodes
     *       representing the groups and an edge
     *       connects two nodes if a net segment
     *       could legally connect these two groups 
     */
    for( group = 1 ; group < numGroups ; group++ ) {
	block = groupArray[ group ].block ;
	type1 = detGroup( group ) ;
	searchG( group , type1 , block ) ;
    }

    /* 
     *     step 3.   Find the MST for the graph generated above.
     *               Employ Kruskal's algorithm  
     *               First, Sort the edges according to cost
     */
    for( edge1 = 1 ; edge1 <= numEdges ; edge1++ ) {
	a1 = edgeArray[edge1].group1 ;
	a2 = edgeArray[edge1].group2 ;
	if( groupArray[a1].block != groupArray[a2].block ) {
	    continue ;
	}
	for( edge2 = edge1 + 1 ; edge2 <= numEdges ; edge2++ ) {
	    b1 = edgeArray[edge2].group1 ; 
	    b2 = edgeArray[edge2].group2 ;
	    if( groupArray[b1].block != groupArray[b2].block ) {
		continue ;
	    }

	    if( (groupArray[a1].unequiv == 1 && 
					groupArray[b1].unequiv == 1 &&
		    groupArray[a1].extint == groupArray[b1].extint  &&
		    groupArray[a2].extint == groupArray[b2].extint) ||

		(groupArray[a2].unequiv == 1 && 
					groupArray[b2].unequiv == 1 &&
		    groupArray[a2].extint == groupArray[b2].extint  &&
		    groupArray[a1].extint == groupArray[b1].extint)  ) {



		ya = (groupArray[a1].aveY + groupArray[a2].aveY) / 2 ;
		yb = (groupArray[b1].aveY + groupArray[b2].aveY) / 2 ;

		if( groupArray[a1].block == top_row ) {
		    if( ya < yb ) {
			if( edgeArray[edge2].cost <=
					    edgeArray[edge1].cost ) {
			    edgeArray[edge2].cost = 
					    edgeArray[edge1].cost + 1 ;
			}
		    } else {
			if( edgeArray[edge2].cost >=
					    edgeArray[edge1].cost ) {
			    edgeArray[edge2].cost = 
					    edgeArray[edge1].cost - 1 ;
			}
		    }
		} else {
		    if( ya < yb ) {
			if( edgeArray[edge2].cost >=
					    edgeArray[edge1].cost ) {
			    edgeArray[edge2].cost = 
					    edgeArray[edge1].cost - 1 ;
			}
		    } else {
			if( edgeArray[edge2].cost <=
					    edgeArray[edge1].cost ) {
			    edgeArray[edge2].cost = 
					    edgeArray[edge1].cost + 1 ;
			}
		    }
		}
		break ;
	    }
	}
    }
    qsorte( (char *) (edgeArray + 1) , numEdges , sizeof( edgeBox ) ) ;

    for( group = 1 ; group <= numGroups ; group++ ) {
	groupArray[group].flag = group ;
    }
    for( edge = 1 ; edge <= numEdges ; edge++ ) {
	group1 = edgeArray[ edge ].group1 ;
	flag1  = groupArray[ group1 ].flag ;
	group2 = edgeArray[ edge ].group2 ;
	flag2  = groupArray[ group2 ].flag ;
	if( flag1 <= 0 || flag2 <= 0 || flag1 == flag2 ) {
	    continue ;
	}
	added_an_edge = NO ;
	edgeArray[ edge ].marked = 1 ;
	for( group = 1; group <= numGroups; group++ ) {
	    if( groupArray[ group ].flag == flag2 ) {
		groupArray[ group ].flag = flag1 ;
	    }
	}

	cell1 = tearray[ groupArray[group1].pinArray[1].pin ]->cell ;
	cell2 = tearray[ groupArray[group2].pinArray[1].pin ]->cell ;
	cellptr1 = carray[cell1] ;
	cellptr2 = carray[cell2] ;
	if( cell1 > numcells && cellptr1->padside != T &&
			        cellptr1->padside != MTT &&
			        cellptr1->padside != MBB &&
			        cellptr1->padside != B ) {
	    if( cell2 <= numcells ) {
		groupArray[group1].flag = 0 ;
	    }
	}
	if( cell2 > numcells && cellptr2->padside != T &&
			        cellptr2->padside != MTT &&
			        cellptr2->padside != MBB &&
			        cellptr2->padside != B ) {
	    if( cell1 <= numcells ) {
		groupArray[group2].flag = 0 ;
	    }
	}

	if( groupArray[group1].unequiv == 1 ) {
	    ei1 = groupArray[group1].extint ;
	    for( ue_grp = 1; ue_grp <= numGroups; ue_grp++ ) {
		if( ue_grp == group1 ) {
		    continue ;
		}
		if( groupArray[ue_grp].extint == ei1 ) {
		    break ;
		}
	    }
	    if( groupArray[ue_grp].flag > 0 ) {
		g1 = g2 = 0 ;
		groupArray[ue_grp].flag = -1 ;
		for( edge2 = edge + 1 ; edge2 <= numEdges ; edge2++ ) {
		    if( g2 == 0 ) {
			if( edgeArray[edge2].group1 == ue_grp ) {
			    g2 = edgeArray[edge2].group2 ;
			    if( groupArray[g2].flag < 0 ) {
				g2 = 0 ;
			    }
			    continue ;
			}
		    }
		    if( g1 == 0 ) {
			if( edgeArray[edge2].group2 == ue_grp ) {
			    g1 = edgeArray[edge2].group1 ;
			    if( groupArray[g1].flag < 0 ) {
				g1 = 0 ;
			    }
			}
		    }
		}
		if( g1 != 0 && g2 != 0 ) {
		    addEdge( g1, g2 ) ;
		    added_an_edge = YES ;
		}
	    }
	}
	if( groupArray[group2].unequiv == 1 ) {
	    ei2 = groupArray[group2].extint ;
	    for( ue_grp = 1; ue_grp <= numGroups; ue_grp++ ) {
		if( ue_grp == group2 ) {
		    continue ;
		}
		if( groupArray[ue_grp].extint == ei2 ) {
		    break ;
		}
	    }
	    if( groupArray[ue_grp].flag > 0 ) {
		g1 = g2 = 0 ;
		groupArray[ue_grp].flag = -1 ;
		for( edge2 = edge + 1 ; edge2 <= numEdges ; edge2++ ) {
		    if( g2 == 0 ) {
			if( edgeArray[edge2].group1 == ue_grp ) {
			    g2 = edgeArray[edge2].group2 ;
			    if( groupArray[g2].flag < 0 ) {
				g2 = 0 ;
			    }
			    continue ;
			}
		    }
		    if( g1 == 0 ) {
			if( edgeArray[edge2].group2 == ue_grp ) {
			    g1 = edgeArray[edge2].group1 ;
			    if( groupArray[g1].flag < 0 ) {
				g1 = 0 ;
			    }
			}
		    }
		}
		if( g1 != 0 && g2 != 0 ) {
		    addEdge( g1, g2 ) ;
		    added_an_edge = YES ;
		}
	    }
	}
	if( added_an_edge == YES ) {
	    for( edge1 = edge + 1 ; edge1 <= numEdges ; edge1++ ) {
		a1 = edgeArray[edge1].group1 ;
		a2 = edgeArray[edge1].group2 ;
		if( groupArray[a1].block != groupArray[a2].block ) {
		    continue ;
		}
		for( edge2 = edge1 + 1 ; edge2 <= numEdges ; edge2++ ) {
		    b1 = edgeArray[edge2].group1 ; 
		    b2 = edgeArray[edge2].group2 ;
		    if( groupArray[b1].block != groupArray[b2].block ) {
			continue ;
		    }


		    if( (groupArray[a1].unequiv == 1 && 
					groupArray[b1].unequiv == 1 &&
			    groupArray[a1].extint == 
					groupArray[b1].extint  &&
			    groupArray[a2].extint == 
					groupArray[b2].extint) ||

			(groupArray[a2].unequiv == 1 && 
					groupArray[b2].unequiv == 1 &&
			    groupArray[a2].extint == 
					groupArray[b2].extint  &&
			    groupArray[a1].extint == 
					groupArray[b1].extint)  ) {


			ya = (groupArray[a1].aveY + 
						groupArray[a2].aveY) / 2 ;
			yb = (groupArray[b1].aveY + 
						groupArray[b2].aveY) / 2 ;

			if( groupArray[a1].block == top_row ) {
			    if( ya < yb ) {
				if( edgeArray[edge2].cost <=
					    edgeArray[edge1].cost ) {
				    edgeArray[edge2].cost = 
					    edgeArray[edge1].cost + 1;
				}
			    } else {
				if( edgeArray[edge2].cost >=
					    edgeArray[edge1].cost ) {
				    edgeArray[edge2].cost = 
						edgeArray[edge1].cost - 1;
				}
			    }
			} else {
			    if( ya < yb ) {
				if( edgeArray[edge2].cost >=
					    edgeArray[edge1].cost ) {
				    edgeArray[edge2].cost = 
						edgeArray[edge1].cost - 1;
				}
			    } else {
				if( edgeArray[edge2].cost <=
					    edgeArray[edge1].cost ) {
				    edgeArray[edge2].cost = 
						edgeArray[edge1].cost + 1;
				}
			    }
			}
			break ;
		    }
		}
	    }
	    qsorte( (char *) (edgeArray + 1 + edge) , numEdges - edge , 
					   sizeof( edgeBox ) ) ;
	}
    }

    /*
     *  Check off one of every unequiv group
     */
    for( group = 1 ; group <= numGroups ; group++ ) {
	if( groupArray[group].flag < 0 ) {
	    continue ;
	}
	if( groupArray[group].unequiv != 1 ) {
	    continue ;
	}
	ei = groupArray[group].extint ;
	for( group2 = group + 1 ; group2 <= numGroups ; group2++ ) {
	    if( groupArray[group2].extint == ei ) {
		if( groupArray[group2].flag >= 0 ) {
		    groupArray[group2].flag = -1 ;
		}
		break ;
	    }
	}
    }

    /* 
     *      step 4.  Output the edges of the MST with their
     *               appropriate pins selected from the two
     *               groups.  The edges were marked "1"
     *               during the computation of the MST above 
     */


    done = NO ;
    while( done == NO ) {
	done = YES ;
	for( edge = 1 ; edge <= numEdges ; edge++ ) {
	    if( edgeArray[edge].marked == YES && edgeArray[edge].poison == NO){
		g1 = edgeArray[edge].group1 ;
		g2 = edgeArray[edge].group2 ;
		unequiv1 = groupArray[g1].unequiv ;
		if( unequiv1 == NO ) {
		    if( groupArray[g1].numPins == 1 &&
				groupArray[g1].pinArray[1].top != 0 ) {
			single_pin1 = YES ;
			unequiv1 = YES ;
		    }
		}
		unequiv2 = groupArray[g2].unequiv ;
		if( unequiv2 == NO ) {
		    if( groupArray[g2].numPins == 1 &&
				groupArray[g2].pinArray[1].top != 0 ) {
			single_pin2 = YES ;
			unequiv2 = YES ;
		    }
		}

		if( (groupArray[g1].poison == YES) ||
					(groupArray[g2].poison == YES) ){
		    done = NO ;
		    edgeArray[edge].poison = YES ;
		    if( unequiv1 == YES ) {
			groupArray[g1].poison = YES ;
		    }
		    if( unequiv2 == YES ) {
			groupArray[g2].poison = YES ;
		    }
		} else if( groupArray[g1].block != groupArray[g2].block ) {
		    done = NO ;
		    edgeArray[edge].poison = YES ;
		    if( unequiv1 == YES ) {
			groupArray[g1].poison = YES ;
		    }
		    if( unequiv2 == YES ) {
			groupArray[g2].poison = YES ;
		    }
		} else if( single_pin1 == YES || single_pin2 == YES ) {
		    done = NO ;
		    edgeArray[edge].poison = YES ;
		    if( unequiv1 == YES ) {
			groupArray[g1].poison = YES ;
		    }
		    if( unequiv2 == YES ) {
			groupArray[g2].poison = YES ;
		    }
		}
	    }
	}
    }
    for( edge = 1 ; edge <= numEdges ; edge++ ) {
	if( edgeArray[edge].marked == YES && edgeArray[edge].poison == NO){
		/* only such an edge could possibly be switchable */
	    g1 = edgeArray[edge].group1 ;
	    g2 = edgeArray[edge].group2 ;
	    if( groupArray[g1].unequiv == NO &&
					groupArray[g2].unequiv == NO ) {
		edgeArray[edge].poison = YES ;
	    }
	    if( groupArray[g1].unequiv == NO ) {
		groupArray[g1].poison = YES ;
	    }
	    if( groupArray[g2].unequiv == NO ) {
		groupArray[g2].poison = YES ;
	    }
	}
    }

    /* make equiv groups out of the unequivs */

    for( edge = 1 ; edge <= numEdges ; edge++ ) {
	if( edgeArray[edge].marked == YES && edgeArray[edge].poison == NO){
		/* only such an edge could possibly be switchable */
	    g1 = edgeArray[edge].group1 ;
	    g2 = edgeArray[edge].group2 ;
	    if( groupArray[g1].edge1 == 0 ) {
		groupArray[g1].edge1 = edge ;
	    } else {
		groupArray[g1].edge2 = edge ;
	    }
	    if( groupArray[g2].edge1 == 0 ) {
		groupArray[g2].edge1 = edge ;
	    } else {
		groupArray[g2].edge2 = edge ;
	    }
	    if( groupArray[g1].poison == NO ) {
		ei = groupArray[g1].extint ;
		for( group = 1 ; ; group++ ) {
		    if( (group == g1) || (groupArray[group].extint != ei) ) {
			continue ;
		    }
		    break ;
		}
		groupArray[g1].numPins = 2 ;
		groupArray[g1].pinArray[2].xloc = groupArray[group].pinArray[1].xloc ;
		groupArray[g1].pinArray[2].yloc = groupArray[group].pinArray[1].yloc ;
		groupArray[g1].pinArray[2].top = groupArray[group].pinArray[1].top ;
		groupArray[g1].pinArray[2].pin = groupArray[group].pinArray[1].pin ;
	    }

	    if( groupArray[g2].poison == NO ) {
		ei = groupArray[g2].extint ;
		for( group = 1 ; ; group++ ) {
		    if( (group == g2) || (groupArray[group].extint != ei) ) {
			continue ;
		    }
		    break ;
		}
		groupArray[g2].numPins = 2 ;
		groupArray[g2].pinArray[2].xloc = groupArray[group].pinArray[1].xloc ;
		groupArray[g2].pinArray[2].yloc = groupArray[group].pinArray[1].yloc ;
		groupArray[g2].pinArray[2].top = groupArray[group].pinArray[1].top ;
		groupArray[g2].pinArray[2].pin = groupArray[group].pinArray[1].pin ;
	    }
	}
    }
    for( edge = 1 ; edge <= numEdges ; edge++ ) {
	if( edgeArray[edge].marked == YES && edgeArray[edge].poison == NO ) {
		/* if edge cannot be expanded, its not unusual */
	    g1 = edgeArray[edge].group1 ;
	    g2 = edgeArray[edge].group2 ;
	    if( groupArray[g1].edge2 == 0 && groupArray[g2].edge2 == 0 ) {
		edgeArray[edge].poison = YES ;
	    }
	}
    }
    /*
     *  All remaining "poison-free" edges are combinable ---
     *  all but one of the combinable group of edges must be
     *  made to have zero length; the other one is to have length
     *  equal to the span of the whole group.
     */



    uclosepns(net) ;  /* This procedure does the above */

    /*  
     *    reset groupArray for the next net 
     */
    for( i = 1 ; i <= numGroups ; i++ ) {
	groupArray[i].numPins = 0 ;
	groupArray[i].flag    = 0 ;
	groupArray[i].poison  = 0 ;
	groupArray[i].unequiv = 0 ;
	groupArray[i].extint  = 0 ;
	groupArray[i].edge1   = 0 ;
	groupArray[i].edge2   = 0 ;
	groupArray[i].check   = 0 ;
    }
    for( i = 1 ; i <= numEdges ; i++ ) {
	edgeArray[i].marked = 0 ;
	edgeArray[i].done   = 0 ;
	edgeArray[i].poison = 0 ;
    }
}
uglobrout() ;

return ;
}
