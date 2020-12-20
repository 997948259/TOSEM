#include "standard.h"
/*  
 *  Configure the rows of standard cells along with possibly
 *  one or more macro blocks;  The macro blocks may be 
 *  specified as: MUL,MUR,MLL,MLR, ML,MR,MB,MT, MM, MTT, or MBB
 */
#define MAXMACRO 50 
#define T 2
#define R 3

typedef struct macrobox {
    int mx ;
    int my ;
} MACROBOX ;

extern int celllen ;
extern double rowSep ;
extern double indent ;
extern int *blkToRow ;
extern int rowHeight ;
extern double macspace[] ;
extern double *padspace ;
extern int *fixLRBT ;

extern BBOXPTR boxptr , *oldbarray ;
extern CBOXPTR cellptr ;
extern MACROBOX *macroArray ;
extern int *filledTo , *endRow ;
extern int macNumber , row , totalR ;
extern int totalBlock , borient , empty , cell , middleRow ;
extern int extraSpace , pad , height , width , bot , top , trow ;
extern int brow , rite , left , coreHeight , coreWidth , count , macro ;
extern int maxHeight , space , separation , yshift , xshift , last ;
extern int coreTop, coreRite , block , maxWidth , *padArray , numMacro ;
extern int URmacro , Rmacro , edge ;
extern int k , blk , zxshift , zyshift ;
extern int mttshift , mbbshift ;
extern double dsum , ratio ;
double ckt_size_factor ;



configure() 
{


config1() ;

xshift = 0 ;
yshift = 0 ;
zxshift = 0 ;
zyshift = 0 ;
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == B ) {
	count = 1 ;
	height = carray[pad]->tileptr->top -
		 carray[pad]->tileptr->bottom ;
	width = carray[pad]->tileptr->right -
		  carray[pad]->tileptr->left ;
	for( pad++ ; pad <= numcells + numterms ; pad++ ) {
	    if( carray[pad]->padside != B ) {
		break ;
	    }
	    count++ ;
	    if( carray[pad]->tileptr->top -
		carray[pad]->tileptr->bottom > height ) {
		height = carray[pad]->tileptr->top
		   - carray[pad]->tileptr->bottom ;
	    }
	    width += carray[pad]->tileptr->right -
		      carray[pad]->tileptr->left ;
	}
	maxHeight = height ;
	if( fixLRBT[2] == 0 ) {
	    space = coreWidth - width ;
	    separation = space / (count + 1) ;
	    if( separation < 0 ) {
		separation = 0 ;
		zxshift = ABS( space ) ;
	    }
	} else {
	    space = ( coreWidth >= width ) ? coreWidth : width ;
	}
	/*
	 *   Shift all rows up by maxHeight + extraSpace
	 */
	yshift = maxHeight + extraSpace ;
	for( row = 1 ; row <= numRows ; row++ ) {
	    rowArray[row].ypos += yshift ;
	}

	for( pad = numcells + 1; pad <= numcells + numterms; pad++){
	    if( carray[pad]->padside == B ) {
		height = carray[pad]->tileptr->top -
			 carray[pad]->tileptr->bottom ;
		width =  carray[pad]->tileptr->right -
			  carray[pad]->tileptr->left ;
		if( fixLRBT[2] == 0 ) {
		    carray[pad]->cxcenter = separation + width / 2 ;
		} else {
		    carray[pad]->cxcenter = padspace[ pad - numcells ]
							    * space ;
		}
		carray[pad]->cycenter = maxHeight - height / 2 - 1 ;
		last = separation + width ;

		for( pad++ ; pad <= numcells + numterms ; pad++ ) {
		    if( carray[pad]->padside != B ) {
			break ;
		    }
		    height = carray[pad]->tileptr->top -
			     carray[pad]->tileptr->bottom ;
		    width =  carray[pad]->tileptr->right -
			      carray[pad]->tileptr->left ;
		    if( fixLRBT[2] == 0 ) {
			carray[pad]->cxcenter = last + separation + 
						    width / 2 ;
		    } else {
			carray[pad]->cxcenter = 
				    padspace[ pad - numcells ] * space ;
		    }
		    carray[pad]->cycenter = maxHeight - 
						    height / 2 - 1 ;
		    last += separation + width ;
		}
	    }
	}
    }
}

for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == T ) {
	count = 1 ;
	width = carray[pad]->tileptr->right -
		  carray[pad]->tileptr->left ;
	for( pad++ ; pad <= numcells + numterms ; pad++ ) {
	    if( carray[pad]->padside != T ) {
		break ;
	    }
	    count++ ;
	    width += carray[pad]->tileptr->right -
		      carray[pad]->tileptr->left ;
	}
	if( fixLRBT[3] == 0 ) {
	    space = coreWidth - width ;
	    separation = space / (count + 1) ;
	    if( separation < 0 ) {
		separation = 0 ;
		if( ABS( space ) > zxshift ) {
		    zxshift = ABS( space ) ;
		}
	    }
	} else {
	    space = (coreWidth >= width ) ? coreWidth : width ;
	}
	/*
	 *   Keep all pads above rowArray[numRows].ypos +
	 *   rowHeight/2 + extraSpace + mttshift
	 */
	coreTop = rowArray[numRows].ypos + rowHeight / 2 + extraSpace +
							 mttshift ;

	for( pad = numcells + 1; pad <= numcells + numterms; pad++){
	    if( carray[pad]->padside == T ) {
		height = carray[pad]->tileptr->top -
			 carray[pad]->tileptr->bottom ;
		width =  carray[pad]->tileptr->right -
			  carray[pad]->tileptr->left ;
		if( fixLRBT[3] == 0 ) {
		    carray[pad]->cxcenter = separation + width / 2 ;
		} else {
		    carray[pad]->cxcenter = padspace[ pad - numcells ]
							    * space ;
		}
		carray[pad]->cycenter = coreTop + height / 2 ;
		last = separation + width ;

		for( pad++ ; pad <= numcells + numterms ; pad++ ) {
		    if( carray[pad]->padside != T ) {
			break ;
		    }
		    height = carray[pad]->tileptr->top -
			     carray[pad]->tileptr->bottom ;
		    width =  carray[pad]->tileptr->right -
			      carray[pad]->tileptr->left ;
		    if( fixLRBT[3] == 0 ) {
			carray[pad]->cxcenter = last + separation + 
							    width / 2 ;
		    } else {
			carray[pad]->cxcenter = 
				    padspace[ pad - numcells ] * space ;
		    }
		    carray[pad]->cycenter = coreTop + height / 2 ;
		    last += separation + width ;
		}
	    }
	}
    }
}

for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == L ) {
	count = 1 ;
	height = carray[pad]->tileptr->top -
		 carray[pad]->tileptr->bottom ;
	width = carray[pad]->tileptr->right -
		  carray[pad]->tileptr->left ;
	for( pad++ ; pad <= numcells + numterms ; pad++ ) {
	    if( carray[pad]->padside != L ) {
		break ;
	    }
	    count++ ;
	    if( carray[pad]->tileptr->right -
		carray[pad]->tileptr->left  > width ) {
		width = carray[pad]->tileptr->right -
			 carray[pad]->tileptr->left ;
	    }
	    height += carray[pad]->tileptr->top -
		      carray[pad]->tileptr->bottom ;
	}
	maxWidth = width ;
	if( fixLRBT[0] == 0 ) {
	    space = coreHeight - height ;
	    separation = space / (count + 1) ;
	    if( separation < 0 ) {
		separation = 0 ;
		zyshift = ABS( space ) ;
	    }
	} else {
	    space = (coreHeight >= height ) ? coreHeight : height ;
	}
	/*
	 *   Shift all rows rite by maxWidth + extraSpace
	 */
	xshift = maxWidth + extraSpace ;
	for( row = 1 ; row <= numRows ; row++ ) {
	    rowArray[row].startx += xshift ;
	    rowArray[row].endx   += xshift ;
	    if( rowArray[row].endx1 > 0 ) {
		rowArray[row].endx1   += xshift ;
		rowArray[row].startx2 += xshift ;
	    }
	}

	for( pad = numcells + 1; pad <= numcells + numterms; pad++){
	    if( carray[pad]->padside == L ) {
		height = carray[pad]->tileptr->top -
			 carray[pad]->tileptr->bottom ;
		width =  carray[pad]->tileptr->right -
			  carray[pad]->tileptr->left ;
		if( fixLRBT[0] == 0 ) {
		    carray[pad]->cycenter = rowArray[1].ypos - 
			    rowHeight / 2 + separation + 
			    height / 2 - mbbshift ;
		} else {
		    carray[pad]->cycenter = rowArray[1].ypos - 
			    rowHeight / 2 - mbbshift + 
			    padspace[ pad - numcells ] * space ;
		}
		carray[pad]->cxcenter = maxWidth - width / 2 - 1 ;
		last = rowArray[1].ypos - rowHeight / 2 + 
				separation + height - mbbshift ;

		for( pad++ ; pad <= numcells + numterms ; pad++ ) {
		    if( carray[pad]->padside != L ) {
			break ;
		    }
		    height = carray[pad]->tileptr->top -
			     carray[pad]->tileptr->bottom ;
		    width =  carray[pad]->tileptr->right -
			      carray[pad]->tileptr->left ;
		    if( fixLRBT[0] == 0 ) {
			carray[pad]->cycenter = last + separation + 
						    height / 2 ;
		    } else {
			carray[pad]->cycenter = rowArray[1].ypos - 
			    rowHeight / 2 - mbbshift + 
			    padspace[ pad - numcells ] * space ;
		    }
		    carray[pad]->cxcenter = maxWidth - 
						    width / 2 - 1 ;
		    last += separation + height ;
		}
	    }
	}
    }
}

for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == R ) {
	count = 1 ;
	height = carray[pad]->tileptr->top -
		 carray[pad]->tileptr->bottom ;

	for( pad++ ; pad <= numcells + numterms ; pad++ ) {
	    if( carray[pad]->padside != R ) {
		break ;
	    }
	    count++ ;
	    height += carray[pad]->tileptr->top -
		      carray[pad]->tileptr->bottom ;
	}
	if( fixLRBT[1] == 0 ) {
	    space = coreHeight - height ;
	    separation = space / (count + 1) ;
	    if( separation < 0 ) {
		separation = 0 ;
		if( ABS( space ) > zyshift ) {
		    zyshift = ABS( space ) ;
		}
	    }
	} else {
	    space = (coreHeight >= height) ? coreHeight : height ;
	}
	coreRite = coreWidth + xshift + extraSpace ;

	for( pad = numcells + 1; pad <= numcells + numterms; pad++){
	    if( carray[pad]->padside == R ) {
		height = carray[pad]->tileptr->top -
			 carray[pad]->tileptr->bottom ;
		width =  carray[pad]->tileptr->right -
			  carray[pad]->tileptr->left ;
		if( fixLRBT[1] == 0 ) {
		    carray[pad]->cycenter = rowArray[1].ypos - 
					rowHeight / 2 + separation + 
					height / 2 - mbbshift ;
		} else {
		    carray[pad]->cycenter = rowArray[1].ypos - 
				    rowHeight / 2 - mbbshift + 
				    padspace[ pad - numcells ] * space ;
		}
		carray[pad]->cxcenter = coreRite + width / 2 ;
		last = rowArray[1].ypos - rowHeight / 2 + 
			    separation + height - mbbshift ;

		for( pad++ ; pad <= numcells + numterms ; pad++ ) {
		    if( carray[pad]->padside != R ) {
			break ;
		    }
		    height = carray[pad]->tileptr->top -
			     carray[pad]->tileptr->bottom ;
		    width =  carray[pad]->tileptr->right -
			      carray[pad]->tileptr->left ;
		    if( fixLRBT[1] == 0 ) {
			carray[pad]->cycenter = last + separation + 
						    height / 2 ;
		    } else {
			carray[pad]->cycenter = rowArray[1].ypos - 
				    rowHeight / 2 - mbbshift + 
				    padspace[ pad - numcells ] * space ;
		    }
		    carray[pad]->cxcenter = coreRite + width / 2 ;
		    last += separation + height ;
		}
	    }
	}
    }
}

/*  
 *  Now its time to shift the macro blocks by the same amount
 *  the rows were shifted above during pad placement
 */
for( macro = 1 ; macro <= numMacro ; macro++ ) {
    pad = padArray[macro] ;
    carray[pad]->cxcenter = macroArray[macro].mx + xshift ;
    carray[pad]->cycenter = macroArray[macro].my + yshift + 
						    mbbshift ;
}
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == B || carray[pad]->padside == T ) {
	carray[pad]->cxcenter += xshift ;

    } else if( carray[pad]->padside == MTT ||
				    carray[pad]->padside == MBB ) {
	carray[pad]->cxcenter += xshift ;
	carray[pad]->cycenter += yshift ;
    }
}

/*
 *   Shift all rows rite by zxshift / 2 ( center the core 
 *   for pad limited cases )
 */
for( row = 1 ; row <= numRows ; row++ ) {
    rowArray[row].startx += zxshift / 2 ;
    rowArray[row].endx   += zxshift / 2 ;
    if( rowArray[row].endx1 > 0 ) {
	rowArray[row].endx1   += zxshift / 2 ;
	rowArray[row].startx2 += zxshift / 2 ;
    }
}
for( macro = 1 ; macro <= numMacro ; macro++ ) {
    pad = padArray[macro] ;
    carray[pad]->cxcenter += zxshift / 2 ;
}
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == R ) {
	carray[pad]->cxcenter += zxshift ;

    } else if( carray[pad]->padside == MTT ||
				    carray[pad]->padside == MBB ) {
	carray[pad]->cxcenter += zxshift / 2 ;
    }
}
/*
 *   Shift all rows up by zyshift / 2 ( center the core for
 *   pad limited cases )
 */
yshift = maxHeight + rowHeight + extraSpace ;
for( row = 1 ; row <= numRows ; row++ ) {
    rowArray[row].ypos += zyshift / 2 ;
}
for( macro = 1 ; macro <= numMacro ; macro++ ) {
    pad = padArray[macro] ;
    carray[pad]->cycenter += zyshift / 2 ;
}
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == T ) {
	carray[pad]->cycenter += zyshift ;

    } else if( carray[pad]->padside == MTT ||
				    carray[pad]->padside == MBB ) {
	carray[pad]->cycenter += zyshift / 2 ;
    }
}

/* 
 *  Now its time to blast away the old barray and
 *  generate the new one.
 */

/*
 *  Find the number of blocks
 */
block = 0 ;
for( row = 1 ; row <= numRows ; row++ ) {
    block++ ;
    if( rowArray[row].endx1 > 0 ) {
	block++ ;
    }
}
totalBlock = block ;
oldbarray = barray ;

blkToRow = (int *) safe_malloc( (totalBlock + 1) * sizeof(int) ) ;
barray = (BBOXPTR *) safe_malloc( (totalBlock + 1) * sizeof(BBOXPTR) ) ;
for( block = 1 ; block <= totalBlock ; block++ ) {
    barray[block] = (BBOXPTR) safe_malloc( sizeof(BBOX) ) ;
}

block = 0 ;
for( row = 1 ; row <= numRows ; row++ ) {
    boxptr = oldbarray[row] ;
    if( rowArray[row].endx1 > 0 ) {
	block++ ;
	blkToRow[block] = row ;
	barray[block]->bxcenter = (rowArray[row].startx +
				    rowArray[row].endx1 ) / 2 ;
	barray[block]->bycenter = rowArray[row].ypos ;
	barray[block]->bleft   = rowArray[row].startx -
				    barray[block]->bxcenter ;
	barray[block]->bright  = rowArray[row].endx1 -
				    barray[block]->bxcenter ;
	barray[block]->bbottom = boxptr->bbottom ;
	barray[block]->btop    = boxptr->btop ;
	barray[block]->bheight = boxptr->btop - boxptr->bbottom ;
	barray[block]->blength = rowArray[row].endx1 -
				    rowArray[row].startx ;
	barray[block]->bclass  = boxptr->bclass ;
	barray[block]->borient = boxptr->borient ;
	barray[block]->oldsize = 0 ;

	block++ ;
	blkToRow[block] = row ;
	barray[block]->bxcenter = (rowArray[row].startx2 +
				    rowArray[row].endx ) / 2 ;
	barray[block]->bycenter = rowArray[row].ypos ;
	barray[block]->bleft   = rowArray[row].startx2 -
				    barray[block]->bxcenter ;
	barray[block]->bright  = rowArray[row].endx -
				    barray[block]->bxcenter ;
	barray[block]->bbottom = boxptr->bbottom ;
	barray[block]->btop    = boxptr->btop ;
	barray[block]->bheight = boxptr->btop - boxptr->bbottom ;
	barray[block]->blength = rowArray[row].endx -
				    rowArray[row].startx2 ;
	barray[block]->bclass  = boxptr->bclass ;
	barray[block]->borient = boxptr->borient ;

	ratio = (double) barray[block - 1]->blength / (double) 
	     (barray[block - 1]->blength + barray[block]->blength) ;
	barray[block]->desire = 1 + (int)((1.0 - ratio) * 
				    rowArray[row].desiredL) ;
	barray[block - 1]->desire = 1 + (int)(ratio * 
				    rowArray[row].desiredL) ;
	barray[block]->oldsize = 0 ;
    } else {
	block++ ;
	blkToRow[block] = row ;
	barray[block]->bxcenter = (rowArray[row].startx +
				    rowArray[row].endx ) / 2 ;
	barray[block]->bycenter = rowArray[row].ypos ;
	barray[block]->bleft   = rowArray[row].startx -
				    barray[block]->bxcenter ;
	barray[block]->bright  = rowArray[row].endx -
				    barray[block]->bxcenter ;
	barray[block]->bbottom = boxptr->bbottom ;
	barray[block]->btop    = boxptr->btop ;
	barray[block]->bheight = boxptr->btop - boxptr->bbottom ;
	barray[block]->blength = rowArray[row].endx -
				    rowArray[row].startx ;
	barray[block]->bclass  = boxptr->bclass ;
	barray[block]->borient = boxptr->borient ;
	barray[block]->desire  = rowArray[row].desiredL ;
	barray[block]->oldsize = 0 ;
    }
}
/*
 *  Now blow array the old block array, rowArray, macroArray
 */
for( row = 1 ; row <= numblock ; row++ ) {
    safe_free( oldbarray[row] ) ;
}
safe_free( oldbarray ) ;
numblock = totalBlock ;


fprintf(fpo,"\n******************\nBLOCK DATA\n");
desiredL = 0 ;
for( block = 1 ; block <= numblock ; block++ ) {
    desiredL += barray[block]->desire ;
    fprintf(fpo,"block:%d desire:%d\n",block,barray[block]->desire);
    /*
    barray[block]->bright  += 0.10 * barray[block]->blength ;
    barray[block]->blength += 0.10 * barray[block]->blength ;
    */
}
fprintf(fpo,"Total Desired Length: %d\n", desiredL ) ;
ckt_size_factor = (double) desiredL ;

/*
 *  And now, folks, its time for cell placement, that is,
 *  real random cell placement
 */

filledTo = (int *) safe_malloc( (numblock + 1) * sizeof( int ) ) ;
endRow = (int *) safe_malloc( (numblock + 1) * sizeof( int ) ) ;
for( row = 1 ; row <= numblock ; row++ ) {
    filledTo[row] = barray[row]->bxcenter + barray[row]->bleft ;
    endRow[row]  = barray[row]->bxcenter + barray[row]->bright ;
}
/*
 *  On first pass, place the cells with specific block assignments
 */
for( cell = 1 ; cell <= numcells ; cell++ ) {
    cellptr = carray[cell] ;
    row = cellptr->cblock ;
    if( row == 0 ) {
	continue ;
    }
    blk = RtoB( row , cellptr->cycenter ) ;

    borient = barray[blk]->borient ;
    cellptr->cblock = blk ;

    width = cellptr->tileptr->right - cellptr->tileptr->left ;
    if( cellptr->cycenter > 0 ) {
	carray[cell]->cxcenter = barray[blk]->bxcenter + 
				    barray[blk]->bleft + 
				    cellptr->cxcenter + width / 2 ;
	carray[cell]->cycenter = barray[blk]->bycenter ;
    } else {
	carray[cell]->cxcenter = barray[blk]->bxcenter + 
				    barray[blk]->bright + 
		    cellptr->cxcenter - (width - width / 2) ;
	carray[cell]->cycenter = barray[blk]->bycenter ;
    }

    if( borient == 2 ) {
	cellptr->corient = 1 ;
    } else {  /* borient was 1 */
	cellptr->corient = 0 ;
    }
}

/*
 *  Final pass, place all unassigned cells
 */
for( cell = 1 ; cell <= numcells ; cell++ ) {
    if( carray[cell]->cblock != 0 ) {
	continue ;
    }
    /*  
     *  cute strategy:  place cell in the most empty row
     */
    empty = -32000 ;
    for( row = 1 ; row <= numblock ; row++ ) {
	if( endRow[row] - filledTo[row] > empty ) {
	    empty = endRow[row] - filledTo[row] ;
	    block = row ;
	}
    }
    borient = barray[block]->borient ;
    width = carray[cell]->tileptr->right - carray[cell]->tileptr->left ;
    carray[cell]->cblock = block ;
    if( borient > 0 ) {
	carray[cell]->cxcenter = filledTo[block] + width / 2 ;
	carray[cell]->cycenter = barray[block]->bycenter ;
	if( borient == 2 ) {
	    carray[cell]->corient = 1 ;
	} else {  /* borient was 1 */
	    carray[cell]->corient = 0 ;
	}
    } else {
	carray[cell]->cycenter = filledTo[block] + width / 2 ;
	carray[cell]->cxcenter = barray[block]->bxcenter ;
	if( borient == -2 ) {
	    carray[cell]->corient = 4 ;
	} else {  /* borient was -1 */
	    carray[cell]->corient = 7 ;
	}
    }
    filledTo[block] += width ;
}

/*
 * Ah ha, done
 */
return ;
}

RtoB( row , from )
int row , from ;
{
    int y , block , block1 , block2 , endx1 , startx2 ;

    y = rowArray[row].ypos ;
    block1 = 0 ;
    block2 = 0 ;
    for( block = 1 ; block <= numblock ; block++ ) {
	if( barray[block]->bycenter == y ) {
	    block1 = block ;
	    break ;
	}
    }
    for( block++ ; block <= numblock ; block++ ) {
	if( barray[block]->bycenter == y ) {
	    block2 = block ;
	    break ;
	}
    }
    if( block1 == 0 ) {
	fprintf(fpo,"RtoB failed to find block corresponding");
	fprintf(fpo," to row:%d\n", row ) ;
	exit(TW_FAIL) ;
    }
    if( block2 == 0 ) {
	block = block1 ;
    } else {
	endx1 = barray[block1]->bxcenter + barray[block1]->bright ;
	startx2 = barray[block2]->bxcenter + barray[block2]->bleft ;
	if( from > 0 ) {
	    if( endx1 < startx2 ) {
		block = block1 ;
	    } else {
		block = block2 ;
	    }
	} else {
	    if( startx2 > endx1 ) {
		block = block2 ;
	    } else {
		block = block1 ;
	    }
	}
    }
    return(block) ;
}
