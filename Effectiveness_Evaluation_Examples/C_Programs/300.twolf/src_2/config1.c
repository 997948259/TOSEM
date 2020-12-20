#include "standard.h"
/*  
 *  Configure the rows of standard cells along with possibly
 *  one or more macro blocks;  The macro blocks may be 
 *  specified as: MUL,MUR,MLL,MLR, ML,MR,MB,MT, MM, MTT, or MBB
 */
#define MAXMACRO 50 

typedef struct macrobox {
    int mx ;
    int my ;
} MACROBOX ;

extern int celllen ;
extern double rowSep ;
extern double indent ;
int *blkToRow ;
extern FILE *fpo ;
int rowHeight ;
extern double macspace[] ;
extern double *padspace ;
extern double *relativeLen ;
extern int *fixLRBT ;

BBOXPTR boxptr , *oldbarray ;
CBOXPTR cellptr ;
MACROBOX *macroArray ;
int *filledTo , *endRow ;
int macNumber , row , totalR ;
int totalBlock , borient , empty , cell , middleRow ;
int extraSpace , pad , height , width , bot , top , trow ;
static int rows;
int brow , rite , left , coreHeight , coreWidth , count , macro ;
int maxHeight , space , separation , yshift , xshift , last ;
int coreTop , coreRite , block , maxWidth , *padArray , numMacro ;
int URmacro , Rmacro , edge ;
int k , blk , zxshift , zyshift ;
int mttshift , mbbshift ;
double dsum , ratio ;

config1() 
{

double totalF , modulation , constant ;
int M , r , topRowY , centerY ;
int count_mtt , count_mbb ;
CBOXPTR padptr ;

macroArray = (MACROBOX *) safe_malloc((MAXMACRO + 1) * sizeof(MACROBOX));
macNumber = 0 ;
numRows = numblock ;
rowArray = (ROWBOX *) safe_malloc( (numRows + 1) * sizeof( ROWBOX ) ) ;
for( row = 1 ; row <= numRows ; row++ ) {
    rowArray[row].endx1   = -1 ;
    rowArray[row].startx2 = -1 ;
}

/*
    Total cell length = totalRowLength = totalR ;
    numRows is entered by the user ;
    rowSep is also entered by the user ;
    row center-to-center spacing = (rowSep + 1) * rowHeight ;
*/
totalR = celllen ;
rowHeight = 0 ;
for( row = 1 ; row <= numRows ; row++ ) {
    rowHeight += barray[row]->btop - barray[row]->bbottom ;
}
rowHeight /= numRows ;

/* Let bottom = 0 and 
	    top = (numRows - 1) * (rowSep + 1) * rowHeight + 
						rowHeight / 2 ;

    Position of each row n is as follows:
       starts at x = 0 ;
       y = (n - 1) * (rowSep + 1) * rowHeight + rowHeight / 2 ;
*/
for( row = 1 ; row <= numRows ; row++ ) {
    rowArray[row].startx = 0 ;
    rowArray[row].ypos = (row - 1) * (rowSep + 1) * rowHeight +
						rowHeight / 2 ;
}

if( numRows > 1 ) {
    totalF = 0.0 ;
    for( r = 1 ; r <= numRows ; r++ ) {
	totalF += relativeLen[r] ;
    }
    topRowY = rowArray[numRows].ypos ;
    centerY = (topRowY + rowArray[1].ypos) / 2 ;
    M = (int) ( (double) totalR / totalF ) ;

    dsum = 0.0 ;
    for( r = 1 ; r <= numRows ; r++ ) {
	dsum += relativeLen[r] * 
			    (double)(ABS(rowArray[r].ypos - centerY));
    }
    dsum /= totalF ;
    dsum *= 1.0 / (double)( topRowY - centerY ) ;

    constant = 1.0 + (1.0 - indent) * (1.0 - dsum) ;
    for( r = 1 ; r <= numRows ; r++ ) {
	rowArray[r].endx = (int)((double) M * 
				    constant * relativeLen[r]);
	modulation = 1.0 + (1.0 - indent) * ( 
			  ((double)(ABS(rowArray[r].ypos - centerY)) / 
			   (double)(topRowY - centerY)) - dsum);
	rowArray[r].desiredL = (int) ( 
		    (double) M * relativeLen[r] * modulation ) + 1 ;
    }
} else {
    rowArray[1].endx = totalR ;
    rowArray[1].desiredL = rowArray[1].endx ;
}

/*
    Define extra space = rowSep * rowHeight
*/
extraSpace = rowSep * rowHeight ;
for( k = 1 ; k <= 15 ; k++ ) {
    if( macspace[k] < 0.0 ) {
	macspace[k] = extraSpace ;
    } else {
	macspace[k] *= rowHeight ;
    }
}
middleRow = numRows / 2 ;

/*
    Now its time to add in a macro block.  Suppose we have such
    a macro block with a location specification as:
    MUL,MUR,MLL,MLR, ML,MR,MB,MT, or MM
    ---macro is height units tall and width units wide.
*/
padArray = (int *) safe_malloc( (numterms + 1) * sizeof( int ) ) ;
for( pad = 1 ; pad <= numterms ; pad++ ) {
    padArray[pad] = 0 ;
}
numMacro = 0 ;
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == MUL || carray[pad]->padside == ML ||
				    carray[pad]->padside == MLL ) {
	padArray[++numMacro] = pad ;
    }
}
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == MT || carray[pad]->padside == MM ||
				    carray[pad]->padside == MB ) {
	padArray[++numMacro] = pad ;
    }
}
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == MUR ) {
	padArray[++numMacro] = pad ;
	URmacro = numMacro ;
    }
}
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == MR ) {
	padArray[++numMacro] = pad ;
	Rmacro = numMacro ;
    }
}
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    if( carray[pad]->padside == MLR ) {
	padArray[++numMacro] = pad ;
    }
}


for( macro = 1 ; macro <= numMacro ; macro++ ) {
    pad = padArray[macro] ;
    padptr = carray[pad] ;
    height = padptr->tileptr->top - padptr->tileptr->bottom ;
    width  = padptr->tileptr->right - padptr->tileptr->left ;

    macNumber++ ;

    switch( padptr->padside ) {
      case MUL : for( row = numRows ; row >= 1 ; row-- ) {
		    if( rowArray[row].ypos + 
				rowSep * rowHeight * 0.33 <= 
				rowArray[numRows].ypos - height ) {
			break ;
		    }
		}
		/*  shorten the rows between row + 1 and numRows by:
		    width + macspace[MUL] ;
		    Number of "rows" affected is: numRows - row ;
		    Add to all "rows" by the amount:
			(rows * (width + macspace[MUL]) ) / numRows ;
		*/
		rows = numRows - row ;
		for( row++ ; row <= numRows ; row++ ) {
		    rowArray[row].startx = width + macspace[MUL] ;
		    rowArray[row].desiredL -= width + macspace[MUL] ;
		}
		for( row = 1 ; row <= numRows ; row++ ) {
		    rowArray[row].endx += (rows * 
				(width + macspace[MUL]) ) / numRows ;
		    rowArray[row].desiredL += (rows * 
				(width + macspace[MUL]) ) / numRows ;
		}
		macroArray[macNumber].mx = width / 2 ;
		macroArray[macNumber].my =
			(rowArray[numRows].ypos + rowHeight / 2) -
							height / 2 ;
		break ;
      case MUR : for( row = numRows ; row >= 1 ; row-- ) {
		    if( rowArray[row].ypos + 
				 rowSep * rowHeight * 0.33 <= 
				 rowArray[numRows].ypos - height ) {
			break ;
		    }
		}
		/*  shorten the rows between row + 1 and numRows by:
		    width + macspace[MUR] ;
		    Number of "rows" affected is: numRows - row ;
		    Add to all "rows" by the amount:
			(rows * (width + macspace[MUR]) ) / numRows ;
		*/
		rows = numRows - row ;
		for( row++ ; row <= numRows ; row++ ) {
		    rowArray[row].endx -= width + macspace[MUR] ;
		    rowArray[row].desiredL -= width + macspace[MUR] ;
		}
		for( row = 1 ; row <= numRows ; row++ ) {
		    rowArray[row].endx += (rows * 
				(width + macspace[MUR]) ) / numRows ;
		    rowArray[row].desiredL += (rows * 
				(width + macspace[MUR]) ) / numRows ;
		}
		macroArray[macNumber].mx = rowArray[numRows].endx +
					   macspace[MUR] + width / 2 ;
		macroArray[macNumber].my =
			(rowArray[numRows].ypos + rowHeight / 2) -
							height / 2 ;
		break ;
      case MLL : for( row = 1 ; row <= numRows ; row++ ) {
		    if( rowArray[row].ypos - 
					rowSep * rowHeight * 0.33 >= 
					rowArray[1].ypos + height ) {
			break ;
		    }
		}
		/*  shorten the rows between 1 and row - 1 by:
		    width + macspace[MLL] ;
		    Number of "rows" affected is: row - 1 ;
		    Add to all "rows" by the amount:
			(rows * (width + macspace[MLL]) ) / numRows ;
		*/
		rows = row - 1 ;
		for( row-- ; row >= 1 ; row-- ) {
		    rowArray[row].startx = width + macspace[MLL] ;
		    rowArray[row].desiredL -= width + macspace[MLL] ;
		}
		for( row = 1 ; row <= numRows ; row++ ) {
		    rowArray[row].endx += (rows * 
				(width + macspace[MLL]) ) / numRows ;
		    rowArray[row].desiredL += (rows * 
				(width + macspace[MLL]) ) / numRows ;
		}
		macroArray[macNumber].mx = width / 2 ;
		macroArray[macNumber].my =
			(rowArray[1].ypos - rowHeight / 2) +
							height / 2 ;
		break ;
      case MLR : for( row = 1 ; row <= numRows ; row++ ) {
		    if( rowArray[row].ypos - 
					rowSep * rowHeight * 0.33 >= 
					rowArray[1].ypos + height ) {
			break ;
		    }
		}
		/*  shorten the rows between 1 and row - 1 by:
		    width + macspace[MLR] ;
		    Number of "rows" affected is: row - 1 ;
		    Add to all "rows" by the amount:
			(rows * (width + macspace[MLR]) ) / numRows ;
		*/
		rows = row - 1 ;
		for( row-- ; row >= 1 ; row-- ) {
		    rowArray[row].endx -= width + macspace[MLR] ;
		    rowArray[row].desiredL -= width + macspace[MLR] ;
		}
		for( row = 1 ; row <= numRows ; row++ ) {
		    rowArray[row].endx += (rows * 
				(width + macspace[MLR]) ) / numRows ;
		    rowArray[row].desiredL += (rows * 
				(width + macspace[MLR]) ) / numRows ;
		}
		if( URmacro != 0 ) {
		    macroArray[URmacro].mx += (rows *
			    (width + macspace[MLR]) ) / numRows ;
		}
		if( Rmacro != 0 ) {
		    macroArray[Rmacro].mx += (rows *
			    (width + macspace[MLR]) ) / numRows ;
		}
		macroArray[macNumber].mx = rowArray[1].endx +
					   macspace[MLR] + width / 2 ;
		macroArray[macNumber].my =
			(rowArray[1].ypos - rowHeight / 2) +
							height / 2 ;
		break ;
      case ML  : bot = rowArray[middleRow].ypos - height / 2 ;
		top = bot + height ;
		for( row = 1 ; row <= numRows ; row++ ) {
		    if( rowArray[row].ypos - rowHeight / 2 - 
			    rowSep * rowHeight * 0.33 >= top ) {
			break ;
		    }
		}
		trow = row ;
		for( row = numRows ; row >= 1 ; row-- ) {
		    if( rowArray[row].ypos + rowHeight / 2 + 
				    rowSep * rowHeight * 0.33 <= bot ) {
			break ;
		    }
		}
		brow = row ;
		/*  shorten the rows between brow and trow by:
		    width + macspace[ML] ;
		    Number of "rows" affected is: trow - brow - 1 ;
		    Add to all "rows" by the amount:
			(rows * (width + macspace[ML]) ) / numRows ;
		*/
		rows = trow - brow - 1 ;
		for( row = brow + 1 ; row < trow ; row++ ) {
		    rowArray[row].startx = width + macspace[ML] ;
		    rowArray[row].desiredL -= width + macspace[ML] ;
		}
		for( row = 1 ; row <= numRows ; row++ ) {
		    rowArray[row].endx += (rows * 
				(width + macspace[ML]) ) / numRows ;
		    rowArray[row].desiredL += (rows * 
				(width + macspace[ML]) ) / numRows ;
		}
		macroArray[macNumber].mx = width / 2 ;
		macroArray[macNumber].my = rowArray[middleRow].ypos;
		break ;
      case MR  : bot = rowArray[middleRow].ypos - height / 2 ;
		top = bot + height ;
		for( row = 1 ; row <= numRows ; row++ ) {
		    if( rowArray[row].ypos - rowHeight / 2 -
				    rowSep * rowHeight * 0.33 >= top ) {
			break ;
		    }
		}
		trow = row ;
		for( row = numRows ; row >= 1 ; row-- ) {
		    if( rowArray[row].ypos + rowHeight / 2 +
				    rowSep * rowHeight * 0.33 <= bot ) {
			break ;
		    }
		}
		brow = row ;
		/*  shorten the rows between brow and trow by:
		    width + macspace[MR] ;
		    Number of "rows" affected is: trow - brow - 1 ;
		    Add to all "rows" by the amount:
			(rows * (width + macspace[MR]) ) / numRows ;
		*/
		rows = trow - brow - 1 ;
		for( row = brow + 1 ; row < trow ; row++ ) {
		    rowArray[row].endx -= width + macspace[MR] ;
		    rowArray[row].desiredL -= width + macspace[MR] ;
		}
		for( row = 1 ; row <= numRows ; row++ ) {
		    rowArray[row].endx += (rows * 
				(width + macspace[MR]) ) / numRows ;
		    rowArray[row].desiredL += (rows * 
				(width + macspace[MR]) ) / numRows ;
		}
		if( URmacro != 0 ) {
		    macroArray[URmacro].mx += (rows *
				(width + macspace[MR]) ) / numRows ;
		}
		macroArray[macNumber].mx = 
				    rowArray[middleRow].endx +
				    macspace[MR] + width / 2 ;
		macroArray[macNumber].my = rowArray[middleRow].ypos;
		break ;
      case MM  : bot = rowArray[middleRow].ypos - height / 2 ;
		top = bot + height ;
		/*
		left = (rowArray[middleRow].startx + 
			rowArray[middleRow].endx ) / 2 - width / 2 ;
		*/
		left = (rowArray[middleRow].startx + 
			rowArray[middleRow].endx ) / 2 ;
		rite = left + width ;
		for( row = 1 ; row <= numRows ; row++ ) {
		    if( rowArray[row].ypos - rowHeight / 2 -
				    rowSep * rowHeight * 0.67 >= top ) {
			break ;
		    }
		}
		trow = row ;
		for( row = numRows ; row >= 1 ; row-- ) {
		    if( rowArray[row].ypos + rowHeight / 2 +
				    rowSep * rowHeight * 0.67 <= bot ) {
			break ;
		    }
		}
		brow = row ;
		/*  split the rows between brow and trow by:
		    width + 2 * macspace[MM] ;
		    Number of "rows" affected is: trow - brow - 1 ;
		    Add to all "rows" by the amount:
		      (rows * (width + 2 * macspace[MM]) ) / numRows ;
		*/
		rows = trow - brow - 1 ;
		for( row = brow + 1 ; row < trow ; row++ ) {
		    rowArray[row].endx1   = left - macspace[MM] ;
		    rowArray[row].startx2 = rite + macspace[MM] ;
		   rowArray[row].desiredL -= width + 2 * macspace[MM];
		}
		for( row = 1 ; row <= numRows ; row++ ) {
		    rowArray[row].endx += (rows * 
			      (width + 2 * macspace[MM]) ) / numRows ;
		    rowArray[row].desiredL += (rows * 
			      (width + 2 * macspace[MM]) ) / numRows ;
		}
		macroArray[macNumber].mx = (left + rite) / 2 ;
		macroArray[macNumber].my = (bot + top) / 2 ;
		break ;
      case MB  : bot = rowArray[1].ypos - rowHeight / 2 ;
		top = bot + height ;
		left = (rowArray[1].startx + 
				rowArray[1].endx ) / 2 - width / 2 ;
		rite = left + width ;
		for( row = 1 ; row <= numRows ; row++ ) {
		    if( rowArray[row].ypos - rowHeight / 2 -
				    rowSep * rowHeight * 0.67 >= top ) {
			break ;
		    }
		}
		trow = row ;
		brow = 0 ;
		/*  split the rows between brow and trow by:
		    width + 2 * macspace[MB] ;
		    Number of "rows" affected is: trow - brow - 1 ;
		    Add to all "rows" by the amount:
		      (rows * (width + 2 * macspace[MB]) ) / numRows ;
		*/
		rows = trow - brow - 1 ;
		for( row = brow + 1 ; row < trow ; row++ ) {
		    rowArray[row].endx1   = left - macspace[MB] ;
		    rowArray[row].startx2 = rite + macspace[MB] ;
		   rowArray[row].desiredL -= width + 2 * macspace[MB];
		}
		for( row = 1 ; row <= numRows ; row++ ) {
		    rowArray[row].endx += (rows * 
			(width + 2 * macspace[MB]) ) / numRows ;
		    rowArray[row].desiredL += (rows * 
			(width + 2 * macspace[MB]) ) / numRows ;
		}
		macroArray[macNumber].mx = (left + rite) / 2 ;
		macroArray[macNumber].my = (bot + top) / 2 ;
		break ;
      case MT  : top = rowArray[numRows].ypos + rowHeight / 2 ;
		bot = top - height ;
		left = (rowArray[numRows].startx + 
			rowArray[numRows].endx ) / 2 - width / 2 ;
		rite = left + width ;
		trow = numRows + 1 ;
		for( row = numRows ; row >= 1 ; row-- ) {
		    if( rowArray[row].ypos + rowHeight / 2 +
				    rowSep * rowHeight * 0.67 <= bot ) {
			break ;
		    }
		}
		brow = row ;
		/*  split the rows between brow and trow by:
		    width + 2 * macspace[MT] ;
		    Number of "rows" affected is: trow - brow - 1 ;
		    Add to all "rows" by the amount:
		      (rows * (width + 2 * macspace[MT]) ) / numRows ;
		*/
		rows = trow - brow - 1 ;
		for( row = brow + 1 ; row < trow ; row++ ) {
		    rowArray[row].endx1   = left - macspace[MT] ;
		    rowArray[row].startx2 = rite + macspace[MT] ;
		   rowArray[row].desiredL -= width + 2 * macspace[MT];
		}
		for( row = 1 ; row <= numRows ; row++ ) {
		    rowArray[row].endx += (rows * 
			     (width + 2 * macspace[MT]) ) / numRows ;
		    rowArray[row].desiredL += (rows * 
			     (width + 2 * macspace[MT]) ) / numRows ;
		}
		macroArray[macNumber].mx = (left + rite) / 2 ;
		macroArray[macNumber].my = (bot + top) / 2 ;
		break ;
	default: fprintf(fpo,"screwup in finding padside\n");
		 exit(TW_FAIL);
		 break ;
    }
}

/*  
 *  Now its time to generate a pad placement around the
 *  periphery of the just defined core topology.
 *  First determine coreWidth and coreHeight.
 */
coreHeight = rowArray[numRows].ypos + rowHeight - rowHeight / 2 ;
coreWidth = 0 ;
for( row = 1 ; row <= numRows ; row++ ) {
    if( rowArray[row].endx > coreWidth ) {
	coreWidth = rowArray[row].endx ;
    }
}
for( macro = 1 ; macro <= numMacro ; macro++ ) {
    pad = padArray[macro] ;
    edge = macroArray[macro].mx + carray[pad]->tileptr->right ;
    if( edge > coreWidth ) {
	coreWidth = edge ;
    }
}

/*
 *  Add in the MTT and MBB macros, if there are any
 */
mbbshift = 0 ;
height   = 0 ;
width    = 0 ;
count_mbb = 0 ;
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    padptr = carray[pad] ;
    if( padptr->padside == MBB ) {
	if( padptr->tileptr->top - padptr->tileptr->bottom > height ){
	    height = padptr->tileptr->top - padptr->tileptr->bottom ;
	}
	width += padptr->tileptr->right - padptr->tileptr->left ;
	count_mbb++ ;
    }
}
if( count_mbb > 0 ) {
    mbbshift = height + rowSep * rowHeight ;
    /*
     *   Shift all rows up by height + rowSep * rowHeight
     */
    for( row = 1 ; row <= numRows ; row++ ) {
	rowArray[row].ypos += mbbshift ;
    }
    coreHeight += mbbshift ;
    if( width > coreWidth ) {
	coreWidth = width ;
    }
    space = coreWidth - width ;
    separation = space / (count_mbb + 1) ;
    if( separation < 0 ) {
	separation = 0 ;
    }

    maxHeight = height ;
    height    = 0 ;
    width     = 0 ;
    last      = separation ;
    for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
	padptr = carray[pad] ;
	if( padptr->padside == MBB ) {
	    height = padptr->tileptr->top - padptr->tileptr->bottom ;
	    width  = padptr->tileptr->right - padptr->tileptr->left ;

	    padptr->cxcenter = last + width / 2  ;
	    padptr->cycenter = maxHeight - height / 2 - 1 ;
	    last += separation + width ;
	}
    }
}


mttshift = 0 ;
height   = 0 ;
width    = 0 ;
count_mtt = 0 ;
for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
    padptr = carray[pad] ;
    if( padptr->padside == MTT ) {
	if( padptr->tileptr->top - padptr->tileptr->bottom > height ){
	    height = padptr->tileptr->top - padptr->tileptr->bottom ;
	}
	width += padptr->tileptr->right - padptr->tileptr->left ;
	count_mtt++ ;

    }
}
if( count_mtt > 0 ) {
    mttshift = height + rowSep * rowHeight ;
    coreHeight += mttshift ;
    if( width > coreWidth ) {
	coreWidth = width ;
    }
    space = coreWidth - width ;
    separation = space / (count_mtt + 1) ;
    if( separation < 0 ) {
	separation = 0 ;
    }

    height    = 0 ;
    width     = 0 ;
    last      = separation ;
    for( pad = numcells + 1 ; pad <= numcells + numterms ; pad++ ) {
	padptr = carray[pad] ;
	if( padptr->padside == MTT ) {
	    height = padptr->tileptr->top - padptr->tileptr->bottom ;
	    width  = padptr->tileptr->right - padptr->tileptr->left ;

	    padptr->cxcenter = last + width / 2  ;
	    padptr->cycenter = coreHeight + rowSep * rowHeight + 
						    height / 2 ;
	    last += separation + width ;
	}
    }
}

return ;
}
