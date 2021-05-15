#include "standard.h"
#include "groute.h"
extern double stopdeg ;
extern int randVar ;
extern FILE *fpo ;
extern int *blkToRow ;
extern int moveable_cells ;

ugpair()
{

CBOXPTR acellptr, bcellptr ; 
BBOXPTR ablckptr ;
DENSITYPTR denptr ;
int a , b , ablock , lowValue ;
int flips , attempts , segment ;
int axcenter, bnxcenter, anxcenter ;
int aleft , aright , aorient ; 
int startx1, endx1 ;
int cellleft, cellrite ;
int x ;
int leftEdge, riteEdge ;
int aptr , chan1 , chan2 , found ;
int breakpoint , stoppoint ;
double r ;

lowValue = tracks ;
Shuffle = ( CHANGRDPTR * )safe_malloc( 251 * sizeof( CHANGRDPTR ) ) ;
for( segment = 1 ; segment <= numSegs ; segment++ ) {
    fixnetseg[segment] = aNetSeg[segment].current ;
}

flips = 0 ;
attempts = 0 ;
breakpoint = 0 ;
stoppoint = moveable_cells * stopdeg ;
while( breakpoint < stoppoint ) {
    do {
	ablock = (int) ( (double) numblock * ( (double) RAND / 
		      (double) 0x7fffffff ) ) + 1 ;
    } while( ablock == numblock + 1 ) ;
    if( pairArray[ablock][0] <= 1 ) {
	continue ;
    }
    chan1 = blkToRow[ablock] + 1 ; /* channel above the row */
    chan2 = blkToRow[ablock] ; /* channel below the row */

    for( found = 0 ; found == 0 ; ) {
	do {
	    aptr = (int) ( (double) pairArray[ablock][0] * 
			( (double) RAND / (double) 0x7fffffff ) ) + 1 ;
	} while( aptr == pairArray[ablock][0] + 1 ) ;
	
	a = pairArray[ablock][aptr] ;
	acellptr = carray[a] ;
	aorient = acellptr->corient ;

	axcenter = acellptr->cxcenter ;

	aleft = acellptr->tileptr->left ;
	aright = acellptr->tileptr->right ;
	startx1 = axcenter + aleft ; 
	endx1   = axcenter + aright ; 

	for( denptr = DboxHead[ chan1 ][ maxTrack[chan1] ]->next ;
		   denptr != DENSENULL ; denptr = denptr->next ) {
	    x = denptr->grdptr->netptr->newx ;
	    if( startx1 <= x && endx1 >= x ) {
		found = 1 ;
		break ;
	    }
	}
	if( found == 0 ) {
	    for( denptr = DboxHead[ chan2 ][ maxTrack[chan2] ]->next
		    ; denptr != DENSENULL ; denptr = denptr->next ) {
		x = denptr->grdptr->netptr->newx ;
		if( startx1 <= x && endx1 >= x ) {
		    found = 1 ;
		    break ;
		}
	    }
	}
    }
    ablckptr = barray[ ablock ] ;

    if( aptr > 1 ) {
	cellleft = pairArray[ablock][aptr - 1] ;
    } else {
	cellleft = 0 ;
    }
    if( aptr < pairArray[ablock][0] ) {
	cellrite = pairArray[ablock][aptr + 1] ;
    } else {
	cellrite = 0 ;
    }

    if( cellleft != 0 && cellrite != 0 && 
			carray[cellleft]->cclass != -1 &&
			acellptr->cclass != -1 &&
			carray[cellrite]->cclass != -1 ) {
	r = (double) RAND / (double) 0x7fffffff ;
	if( r >= 0.5 ) {
	    /*
	     *   Take the left neighbor first.
	     */
	    b = cellleft ;
	    bcellptr = carray[b] ;
	    leftEdge = bcellptr->cxcenter + bcellptr->tileptr->left ;
	    anxcenter = leftEdge - aleft ;
	    bnxcenter = endx1 - bcellptr->tileptr->right ;
	    if( ucgxp( a, b, anxcenter, bnxcenter ) ) {
		flips++ ;
		attempts++ ;
		if( attempts % 50 == 0 ) {
		    fprintf(fpo,"current iteration:%d\n",
						attempts ) ;
		    fflush(fpo);
		}
		if( attempts % 150 == 0 ) {
		    savewolf(3) ;
		}
		if( tracks < lowValue ) {
		    lowValue = tracks ;
		    fprintf(fpo,"Routing tracks reduced ");
		    fprintf(fpo,"to: %d  on iteration:%d\n",
					tracks, attempts ) ;	
		    fflush(fpo);
		} else {
		    breakpoint++ ;
		}
		if( !uneven_cell_height ) {
		    pairArray[ablock][aptr] = b ;
		    pairArray[ablock][aptr - 1] = a ;
		}
	    } else {
		breakpoint++ ;
		attempts++ ;
		if( attempts % 50 == 0 ) {
		    fprintf(fpo,"current iteration:%d\n",
						attempts ) ;
		    fflush(fpo);
		}
		if( attempts % 150 == 0 ) {
		    savewolf(3) ;
		}
		b = cellrite ;
		bcellptr = carray[b] ;
		riteEdge = bcellptr->cxcenter 
			    + bcellptr->tileptr->right ;
		anxcenter = riteEdge - aright ;
		bnxcenter = startx1 - bcellptr->tileptr->left ;
		if( ucgxp( a, b, anxcenter, bnxcenter ) ) {
		    flips++ ;
		    if( tracks < lowValue ) {
			lowValue = tracks ;
			fprintf(fpo,"Routing tracks reduced ");
			fprintf(fpo,"to: %d  on iteration:%d\n",
					tracks , (attempts +1) );
			fflush(fpo);
		    } else {
			breakpoint++ ;
		    }
		    if( !uneven_cell_height ) {
			pairArray[ablock][aptr] = b ;
			pairArray[ablock][aptr + 1] = a ;
		    }
		} else {
		    breakpoint++ ;
		}
		attempts++ ;
		if( attempts % 50 == 0 ) {
		    fprintf(fpo,"current iteration:%d\n",
						attempts ) ;
		    fflush(fpo);
		}
		if( attempts % 150 == 0 ) {
		    savewolf(3) ;
		}
	    }
	} else {
	    b = cellrite ;
	    bcellptr = carray[b] ;
	    riteEdge = bcellptr->cxcenter + bcellptr->tileptr->right ;
	    anxcenter = riteEdge - aright ;
	    bnxcenter = startx1 - bcellptr->tileptr->left ;
	    if( ucgxp( a, b, anxcenter, bnxcenter ) ) {
		flips++ ;
		attempts++ ;
		if( attempts % 50 == 0 ) {
		    fprintf(fpo,"current iteration:%d\n",
						attempts ) ;
		    fflush(fpo);
		}
		if( attempts % 150 == 0 ) {
		    savewolf(3) ;
		}
		if( tracks < lowValue ) {
		    lowValue = tracks ;
		    fprintf(fpo,"Routing tracks reduced ");
		    fprintf(fpo,"to: %d  on iteration:%d\n",
					    tracks, attempts );
		    fflush(fpo);
		} else {
		    breakpoint++ ;
		}
		if( !uneven_cell_height ) {
		    pairArray[ablock][aptr] = b ;
		    pairArray[ablock][aptr + 1] = a ;
		}
	    } else {
		attempts++ ;
		if( attempts % 50 == 0 ) {
		    fprintf(fpo,"current iteration:%d\n",
						attempts ) ;
		    fflush(fpo);
		}
		if( attempts % 150 == 0 ) {
		    savewolf(3) ;
		}
		breakpoint++ ;
		b = cellleft ;
		bcellptr = carray[b] ;
		leftEdge = bcellptr->cxcenter + bcellptr->tileptr->left;
		anxcenter = leftEdge - aleft ;
		bnxcenter = endx1 - bcellptr->tileptr->right ;
		if( ucgxp( a, b, anxcenter, bnxcenter ) ) {
		    flips++ ;
		    if( tracks < lowValue ) {
			lowValue = tracks ;
			fprintf(fpo,"Routing tracks reduced ");
			fprintf(fpo,"to: %d  on iteration:%d\n",
					tracks, (attempts + 1) );
			fflush(fpo);
		    } else {
			breakpoint++ ;
		    }
		    if( !uneven_cell_height ) {
			pairArray[ablock][aptr] = b ;
			pairArray[ablock][aptr - 1] = a ;
		    }
		} else {
		    breakpoint++ ;
		}
		attempts++ ;
		if( attempts % 50 == 0 ) {
		    fprintf(fpo,"current iteration:%d\n",
						attempts ) ;
		    fflush(fpo);
		}
		if( attempts % 150 == 0 ) {
		    savewolf(3) ;
		}
	    }
	}
    } else {
	if( cellleft != 0 && 
		    carray[cellleft]->cclass != -1 &&
		    acellptr->cclass != -1 ) {
	    b = cellleft ;
	    bcellptr = carray[b] ;
	    leftEdge = bcellptr->cxcenter + bcellptr->tileptr->left ;
	    anxcenter = leftEdge - aleft ;
	    bnxcenter = endx1 - bcellptr->tileptr->right ;
	    if( ucgxp( a, b, anxcenter, bnxcenter ) ) {
		flips++ ;
		if( tracks < lowValue ) {
		    lowValue = tracks ;
		    fprintf(fpo,"Routing tracks reduced ");
		    fprintf(fpo,"to: %d  on iteration:%d\n",
					    tracks, (attempts + 1) );
		    fflush(fpo);
		} else {
		    breakpoint++ ;
		}
		if( !uneven_cell_height ) {
		    pairArray[ablock][aptr] = b ;
		    pairArray[ablock][aptr - 1] = a ;
		}
	    } else {
		breakpoint++ ;
	    }
	    attempts++ ;
	    if( attempts % 50 == 0 ) {
		fprintf(fpo,"current iteration:%d\n",
					    attempts ) ;
		fflush(fpo);
	    }
	    if( attempts % 150 == 0 ) {
		savewolf(3) ;
	    }
	} else if( cellrite != 0 && 
		    carray[cellrite]->cclass != -1 &&
		    acellptr->cclass != -1 ) {
	    b = cellrite ;
	    bcellptr = carray[b] ;
	    riteEdge = bcellptr->cxcenter + bcellptr->tileptr->right ;
	    anxcenter = riteEdge - aright ;
	    bnxcenter = startx1 - bcellptr->tileptr->left ;
	    if( ucgxp( a, b, anxcenter, bnxcenter ) ) {
		flips++ ;
		if( tracks < lowValue ) {
		    lowValue = tracks ;
		    fprintf(fpo,"Routing tracks reduced ");
		    fprintf(fpo,"to: %d  on iteration:%d\n",
					    tracks, (attempts +1) );
		    fflush(fpo);
		} else {
		    breakpoint++ ;
		}
		if( !uneven_cell_height ) {
		    pairArray[ablock][aptr] = b ;
		    pairArray[ablock][aptr + 1] = a ;
		}
	    } else {
		breakpoint++ ;
	    }
	    attempts++ ;
	    if( attempts % 50 == 0 ) {
		fprintf(fpo,"current iteration:%d\n",
					    attempts ) ;
		fflush(fpo);
	    }
	    if( attempts % 150 == 0 ) {
		savewolf(3) ;
	    }
	}
    }
    switch( ablckptr->borient ) {
	case  1 : 
	    if( acellptr->orflag != 0 ) {
		if( ucg0( a , (aorient == 0) ? 2 : 0 ) ) {
		    if( tracks < lowValue ) {
			lowValue = tracks ;
			fprintf(fpo,"Routing tracks reduced ");
			fprintf(fpo,"to: %d  on iteration:%d\n",
						    tracks, attempts );
			fprintf(fpo,"  ----by an orientation change\n");
			fflush(fpo);
		    }
		}
	    }
	    break ;
	case  2 : 
	    if( acellptr->orflag != 0 ) {
		if( ucg0( a , (aorient == 1) ? 3 : 1 ) ) {
		    if( tracks < lowValue ) {
			lowValue = tracks ;
			fprintf(fpo,"Routing tracks reduced ");
			fprintf(fpo,"to: %d  on iteration:%d\n",
						    tracks, attempts );
			fprintf(fpo,"  ----by an orientation change\n");
			fflush(fpo);
		    }
		}
	    }
	    break ;
    }
}
if( attempts != 0 ) {
    fprintf( fpo, "    no. of accepted gflips: %d --->%d%s\n",
			    flips , (int)( 100.0 * (double)(flips) /
				    (double)(attempts) ) , "%" ) ;
    fflush(fpo);
}
safe_free( Shuffle ) ;
return;
}
