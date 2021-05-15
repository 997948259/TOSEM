#include "standard.h"
#include "groute.h"
#define T   2 
#define R   3 
extern char **pinnames ;
extern int rowHeight ;
extern int *pinlist ;



outpins()
{

char filename[64] ;
FILE *fp ;
NBOXPTR netptr ;
SEGBOXPTR sptr ;
int net , b , e , seg , x , y , pin , pinloc , chan , xx ;
int chan1, chan2 ;
int r_core_edge , l_core_edge , l_end , r_end , cell , blk ;
int pin2_1 , pin2_2 ;


sprintf( filename , "%s.pin" , cktName ) ;
fp = twopen ( filename , "w", ABORT ) ;

r_core_edge = 0 ;
l_core_edge = 32000 ;
for( blk = 1 ; blk <= numblock ; blk++ ) {
    cell = pairArray[blk][ pairArray[blk][0] ] ;
    r_end = carray[cell]->cxcenter + carray[cell]->tileptr->right ;
    cell = pairArray[blk][1] ;
    l_end = carray[cell]->cxcenter + carray[cell]->tileptr->left ;
    if( r_end > r_core_edge ) {
	r_core_edge = r_end ;
    }
    if( l_end < l_core_edge ) {
	l_core_edge = l_end ;
    }
}

for( net = 1 ; net <= numnets ; net++ ) {
    netptr = netarray[net]->netptr ;
    for( ; netptr != NETNULL ; netptr = netptr->nterm ) {
	pin = netptr->terminal ;
	if( pinlist[pin] == 0 ) {
	    continue ;
	}
	pinloc = - netptr->pinloc ;
	x = netptr->xpos ;
	y = netptr->ypos ;

	b = anet[net] ;
	e = anet[net + 1] - 1 ;
	    
	chan1 = -10 ;
	chan2 = -10 ;
	for( seg = b ; seg <= e ; seg++ ) {
	    if( aNetSeg[seg].current == 0 ) {
		sptr = aNetSeg[seg].top ;
	    } else {
		sptr = aNetSeg[seg].bot ;
	    }
	    if( pin == sptr->pin1 || pin == sptr->pin2 ) {
		chan = sptr->channel ;
		if( chan1 < 0 ) {
		    chan1 = chan ;
		    if( pin == sptr->pin1 ) {
			pin2_1 = sptr->pin2 ;
		    } else {
			pin2_1 = sptr->pin1 ;
		    }
		} else if( chan1 == chan ) {
		    continue ;
		} else if( chan2 < 0 ) {
		    chan2 = chan ;
		    if( pin == sptr->pin1 ) {
			pin2_2 = sptr->pin2 ;
		    } else {
			pin2_2 = sptr->pin1 ;
		    }
		    break ;
		}
	    }
	}

	if( (netptr->cell <= numcells && pinloc != 0) ||
			(netptr->cell > numcells &&
			(carray[netptr->cell]->padside == T ||
			 carray[netptr->cell]->padside == B ||
			 carray[netptr->cell]->padside == MTT ||
			 carray[netptr->cell]->padside == MBB)) ) {
	    if( netptr->cell > numcells ) {
		if( carray[netptr->cell]->padside == T ||
			carray[netptr->cell]->padside == MTT ) {
		    fprintf(fp,"%s %d %s %s %d %d %d %d 0\n", 
				netarray[net]->name, pinlist[pin], 
				carray[netptr->cell]->cname,
				pinnames[pin], x, y, chan1 , 1 ) ;
		} else if( carray[netptr->cell]->padside == B || 
			carray[netptr->cell]->padside == MBB ) {
		    fprintf(fp,"%s %d %s %s %d %d %d %d 0\n", 
				netarray[net]->name, pinlist[pin], 
				carray[netptr->cell]->cname,
				pinnames[pin], x, y, chan1 , -1 ) ;
		}
	    } else {
		fprintf(fp,"%s %d %s %s %d %d %d %d 0\n", 
			    netarray[net]->name, pinlist[pin], 
			    carray[netptr->cell]->cname,
			    pinnames[pin], x, y, chan1 , pinloc ) ;
	    }
	} else if( netptr->cell > numcells ) {
	    if( carray[netptr->cell]->padside == L   ||
		carray[netptr->cell]->padside == MUL ||
		carray[netptr->cell]->padside == ML  ||
		carray[netptr->cell]->padside == MLL ){

		fprintf(fp,"%s %d %s %s %d %d %d %d 0\n", 
				netarray[net]->name, pinlist[pin], 
				carray[netptr->cell]->cname,
				pinnames[pin], x, y, -1 , 1 ) ;

		if( carray[tearray[pin2_1]->cell]->padside != L   &&
		    carray[tearray[pin2_1]->cell]->padside != MUL &&
		    carray[tearray[pin2_1]->cell]->padside != ML  &&
		    carray[tearray[pin2_1]->cell]->padside != MLL ){

		    if( carray[netptr->cell]->padside == L ) {
			xx = l_core_edge ;
		    } else {
			xx = min_l_chan_edge( chan1 ) ;
			if( tearray[pin2_1]->xpos < xx ) {
			    xx = x ; 
			}
		    }
		    if( netptr->row == chan1 ) {
			y = barray[netptr->row]->bycenter -
						rowHeight ;
		    } else {
			y = barray[netptr->row]->bycenter +
						rowHeight ;
		    }
		    fprintf(fp," %s %d %s %s %d %d %d %d 0\n", 
			netarray[net]->name, pinlist[pin], 
			"PSEUDO_CELL",
			"PSEUDO_PIN", xx, y, chan1, -2 ) ;
		    fprintf(fp," %s %d %s %s %d %d %d %d 0\n", 
			netarray[net]->name, pinlist[pin], 
			"PSEUDO_CELL",
			"PSEUDO_PIN", xx, y, -1, -1 ) ;

		    if( chan2 > 0 ) {
			if( carray[tearray[pin2_2]->cell]->padside
							!= L   &&
			    carray[tearray[pin2_2]->cell]->padside
							!= MUL &&
			    carray[tearray[pin2_2]->cell]->padside
							!= ML  &&
			    carray[tearray[pin2_2]->cell]->padside
							!= MLL ){

			    if( carray[netptr->cell]->padside==L){
				xx = l_core_edge ;
			    } else {
				xx = min_l_chan_edge( chan2 ) ;
				if( tearray[pin2_2]->xpos < xx ) {
				    xx = x ; 
				}
			    }
			    if( netptr->row == chan2 ) {
				y = barray[netptr->row]->bycenter -
							rowHeight ;
			    } else {
				y = barray[netptr->row]->bycenter +
							rowHeight ;
			    }
			    fprintf(fp,
				" %s %d %s %s %d %d %d %d 0\n", 
				netarray[net]->name, pinlist[pin], 
				"PSEUDO_CELL",
				"PSEUDO_PIN", xx, y, chan2, -2 ) ;
			    fprintf(fp,
				" %s %d %s %s %d %d %d %d 0\n", 
				netarray[net]->name, pinlist[pin], 
				"PSEUDO_CELL",
				"PSEUDO_PIN", xx, y, -1, -1 ) ;
			}
		    }
		}
	    } else if( carray[netptr->cell]->padside == R    ||
		       carray[netptr->cell]->padside == MUR  ||
		       carray[netptr->cell]->padside == MR   ||
		       carray[netptr->cell]->padside == MLR  ){

		fprintf(fp,"%s %d %s %s %d %d %d %d 0\n", 
				netarray[net]->name, pinlist[pin], 
				carray[netptr->cell]->cname,
				pinnames[pin], x, y, -2 , 1 ) ;
		if( carray[tearray[pin2_1]->cell]->padside != R   &&
		    carray[tearray[pin2_1]->cell]->padside != MUR &&
		    carray[tearray[pin2_1]->cell]->padside != MR  &&
		    carray[tearray[pin2_1]->cell]->padside != MLR ){

		    if( carray[netptr->cell]->padside == R ) {
			xx = r_core_edge ;
		    } else {
			xx = min_r_chan_edge( chan1 ) ;
			if( tearray[pin2_1]->xpos > xx ) {
			    xx = x ; 
			}
		    }
		    if( netptr->row == chan1 ) {
			y = barray[netptr->row]->bycenter -
						rowHeight ;
		    } else {
			y = barray[netptr->row]->bycenter +
						rowHeight ;
		    }
		    fprintf(fp," %s %d %s %s %d %d %d %d 0\n", 
			netarray[net]->name, pinlist[pin], 
			"PSEUDO_CELL",
			"PSEUDO_PIN", xx, y, chan1, 2 ) ;
		    fprintf(fp," %s %d %s %s %d %d %d %d 0\n", 
			netarray[net]->name, pinlist[pin], 
			"PSEUDO_CELL",
			"PSEUDO_PIN", xx, y, -2, -1 ) ;

		    if( chan2 > 0 ) {
			if( carray[tearray[pin2_2]->cell]->padside
							!= R   &&
			    carray[tearray[pin2_2]->cell]->padside
							!= MUR &&
			    carray[tearray[pin2_2]->cell]->padside
							!= MR  &&
			    carray[tearray[pin2_2]->cell]->padside
							!= MLR ){
			    if( carray[netptr->cell]->padside==R){
				xx = r_core_edge ;
			    } else {
				xx = min_r_chan_edge( chan2 ) ;
				if( tearray[pin2_2]->xpos > xx ) {
				    xx = x ; 
				}
			    }
			    if( netptr->row == chan2 ) {
				y = barray[netptr->row]->bycenter -
							rowHeight ;
			    } else {
				y = barray[netptr->row]->bycenter +
							rowHeight ;
			    }
			    fprintf(fp,
				" %s %d %s %s %d %d %d %d 0\n", 
				netarray[net]->name, pinlist[pin], 
				"PSEUDO_CELL",
				"PSEUDO_PIN", xx, y, chan2, 2 ) ;
			    fprintf(fp,
				" %s %d %s %s %d %d %d %d 0\n", 
				netarray[net]->name, pinlist[pin], 
				"PSEUDO_CELL",
				"PSEUDO_PIN", xx, y, -2, -1 ) ;
			}
		    }
		}
	    }
	} else {   /* pinloc == 0, pin on a cell */
	    if( chan1 == netptr->row ) {
		fprintf(fp,
		     "%s %d %s %s %d %d %d %d 0\n", 
		    netarray[net]->name, 
		    pinlist[pin], 
		    carray[netptr->cell]->cname,
		    pinnames[pin], x, y, chan1 , 1 ) ;
	    } else {
		fprintf(fp,
		     "%s %d %s %s %d %d %d %d 0\n", 
		    netarray[net]->name, 
		    pinlist[pin], 
		    carray[netptr->cell]->cname,
		    pinnames[pin], x, y, chan1 , -1 ) ;
	    }
	    if( chan2 > 0 ) {
		if( chan2 == netptr->row ) {
		    fprintf(fp,
			 "%s %d %s %s %d %d %d %d 0\n", 
			netarray[net]->name, 
			pinlist[pin], 
			carray[netptr->cell]->cname,
			pinnames[pin], x, y, chan2 , 1 ) ;
		} else {
		    fprintf(fp,
			 "%s %d %s %s %d %d %d %d 0\n", 
			netarray[net]->name, 
			pinlist[pin], 
			carray[netptr->cell]->cname,
			pinnames[pin], x, y, chan2 , -1 ) ;
		}
	    }
	}
    }
}
twclose(fp);
return ;
}






min_r_chan_edge( channel )
int channel ;
{

int cell , end , end2 ;

if( channel == 1 ) {
    cell = pairArray[1][ pairArray[1][0] ] ;
    end = carray[cell]->cxcenter + carray[cell]->tileptr->right ;
} else if( channel == numblock + 1 ) {
    cell = pairArray[numblock][ pairArray[numblock][0] ] ;
    end = carray[cell]->cxcenter + carray[cell]->tileptr->right ;
} else {
    cell = pairArray[channel - 1][ pairArray[channel - 1][0] ] ;
    end = carray[cell]->cxcenter + carray[cell]->tileptr->right ;
    cell = pairArray[channel][ pairArray[channel][0] ] ;
    end2 = carray[cell]->cxcenter + carray[cell]->tileptr->right ;
    end = (end < end2) ? end : end2 ;
}
return( end );
}



min_l_chan_edge( channel )
int channel ;
{

int cell , end , end2 ;

if( channel == 1 ) {
    cell = pairArray[1][1] ;
    end = carray[cell]->cxcenter + carray[cell]->tileptr->left ;
} else if( channel == numblock + 1 ) {
    cell = pairArray[numblock][1] ;
    end = carray[cell]->cxcenter + carray[cell]->tileptr->left ;
} else {
    cell = pairArray[channel - 1][1] ;
    end = carray[cell]->cxcenter + carray[cell]->tileptr->left ;
    cell = pairArray[channel][1] ;
    end2 = carray[cell]->cxcenter + carray[cell]->tileptr->left ;
    end = (end > end2) ? end : end2 ;
}
return( end );
}
