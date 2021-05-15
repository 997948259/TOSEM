#include "standard.h"
#include "route.h"
#include "groute.h"
extern int **pairArray ;
extern double rowSep ;
extern int rowHeight ;

#define NEWPOS 1
#define OLDPOS 0
 
#define ROWCOLOR "aquamarine"
#define NEWNETCOLOR "red"
#define PADCOLOR "aquamarine"
#define OLDNETCOLOR "green"
#define NEWPINCOLOR "white"
#define OLDPINCOLOR "black"
#define EQUIVCOLOR  "orange"
#define UNEQUIVCOLOR "blue"    
#define OLDGROUPCOLOR "blue"
#define NEWGROUPCOLOR "red"


globedbg(lowerNet,upperNet)
int lowerNet ;
int upperNet ;
{

int block, left, rite, bot, top , cell , b , e , pin1 , pin2 ;
int net , seg, term1, curExtint, separation, factor ;
int llx, lly, urx, ury ;
void checkPos();

SEGBOXPTR sptr ;
CBOXPTR cellptr ;
NBOXPTR curTerm;
FILE *fp , *fpp ;

fp = twopen( "cell.file","w", ABORT ) ;


for( block = 1 ; block <= numblock ; block++ ) {

    left = barray[block]->bxcenter + barray[block]->bleft ;
    bot  = barray[block]->bycenter + barray[block]->bbottom ;
    top  = barray[block]->bycenter + barray[block]->btop ;

    if( pairArray[block][0] > 0 ) {
	cell = pairArray[block][ pairArray[block][0] ] ;
	rite = carray[cell]->cxcenter + carray[cell]->tileptr->right;
    } else {
	rite = barray[block]->bxcenter + barray[block]->bright ;
    }

    fprintf(fp,"%d, %d, %d, %d, color: %s, label: row:%d\n",
		left,bot,rite,top, ROWCOLOR, block ) ;
}
/* initialize variables */
llx = INT_MAX ;
lly = INT_MAX ;
urx = INT_MIN ;
ury = INT_MIN ;

for( cell = numcells + 1 ; cell <= numcells + numterms ; cell++ ) { 
    cellptr = carray[cell] ;
    left = cellptr->cxcenter + cellptr->tileptr->left ;
    rite = cellptr->cxcenter + cellptr->tileptr->right ;
    bot  = cellptr->cycenter + cellptr->tileptr->bottom ;
    top  = cellptr->cycenter + cellptr->tileptr->top ;
    fprintf(fp,"%d, %d, %d, %d, color: %s, label: pad:%s\n",
	left,bot,rite,top, PADCOLOR, cellptr->cname ) ;
    /* find bounding box of pads */
    if( left < llx ){
	llx = left ;
    }
    if( rite > urx ){
	urx = rite ;
    }
    if( bot <  lly ){
	lly = bot  ;
    }
    if( top  > ury ){
	ury = top  ;
    }

}
twclose(fp);

fp  = twopen( "net.file","w", ABORT ) ;
fpp = twopen("pin.file","w", ABORT );

/* calculate channel separation for bending lines */
separation = (int) rowSep * rowHeight / 3;

/* process all nets */
for( net = lowerNet ; net <= upperNet ; net++ ) {
    b = anet[net] ;
    e = anet[net + 1] - 1 ;
    for( seg = b ; seg <= e ; seg++ ) {
	if( aNetSeg[seg].nflag == 0 ) {
	    /* we have not moved pin to a new pin position */
	    /* but use new colors anyway */
	    if( aNetSeg[seg].current == 0 ) {
		sptr = aNetSeg[seg].top ;
	    } else {
		sptr = aNetSeg[seg].bot ;
	    }
	    pin1 = sptr->pin1 ;
	    pin2 = sptr->pin2 ;
	    checkPos(tearray[pin1],NEWPOS,llx,lly,urx,ury) ;
	    checkPos(tearray[pin2],NEWPOS,llx,lly,urx,ury) ;
	    if (tearray[pin1]->ypos != tearray[pin2]->ypos){  /* no need to bend */
		fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n", 
			net,
			tearray[pin1]->xpos ,
			tearray[pin1]->ypos ,
			tearray[pin2]->xpos ,
			tearray[pin2]->ypos ,
			NEWNETCOLOR) ;
	    } else { /* we need to bend the net */
		if ( (int) tearray[pin1]->pinloc == -1){ 
		    factor = -1;  /* bend downwards */
		} else {
		    factor = 1;   /* bend upwards */
		}
		fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n", 
			net,
			tearray[pin1]->xpos ,
			tearray[pin1]->ypos ,
			(tearray[pin1]->xpos + tearray[pin2]->xpos)/2 ,
			tearray[pin2]->ypos + factor * separation ,
			NEWNETCOLOR) ;
		fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n", 
			net,
			(tearray[pin1]->xpos + tearray[pin2]->xpos)/2 ,
			tearray[pin2]->ypos + factor * separation ,
			tearray[pin2]->xpos ,
			tearray[pin2]->ypos ,
			NEWNETCOLOR) ;
	    }

	    /* now process the equiv / unequivs */  
  	    term1 = tearray[pin1]->terminal ;
	    curExtint = tearray[pin1]->extint ;  
	    for (curTerm=netarray[net]->netptr;curTerm;curTerm= curTerm->nterm){ 
		if (curTerm->extint == curExtint && curTerm->terminal != term1){
		    if (curTerm->unequiv){ /* its an unequiv */
			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    tearray[pin1]->xpos,
			    tearray[pin1]->ypos,
			    curTerm->xpos,
			    curTerm->ypos,
			    UNEQUIVCOLOR) ;
		    } else {  /* its an equiv */

			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    tearray[pin1]->xpos,
			    tearray[pin1]->ypos,
			    curTerm->xpos,
			    curTerm->ypos,
			    EQUIVCOLOR) ;
		    }
	   	}
	    }

	    /* now output pin2 equivs */
  	    term1 = tearray[pin2]->terminal ;
	    curExtint = tearray[pin2]->extint ;  
	    for (curTerm=netarray[net]->netptr;curTerm;curTerm= curTerm->nterm){ 
		if (curTerm->extint == curExtint && curTerm->terminal != term1){
		    if (curTerm->unequiv){ /* its an unequiv */
			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    tearray[pin2]->xpos,
			    tearray[pin2]->ypos,
			    curTerm->xpos,
			    curTerm->ypos,
			    UNEQUIVCOLOR) ;
		    } else {  /* its an equiv */

			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    tearray[pin2]->xpos,
			    tearray[pin2]->ypos,
			    curTerm->xpos,
			    curTerm->ypos,
			    EQUIVCOLOR) ;
		    }
	   	}
	    }

	    fprintf(fpp,"%d, %d, %d, %d, %d, color: %s, label: %d\n", 
			net,
			tearray[pin1]->xpos - 1,
			tearray[pin1]->ypos - 1,
			tearray[pin1]->xpos + 1,
			tearray[pin1]->ypos + 1,
			NEWPINCOLOR,
			pin1 ) ;
	    fprintf(fpp,"%d, %d, %d, %d, %d, color: %s, label: %d\n", 
			net,
			tearray[pin2]->xpos - 1,
			tearray[pin2]->ypos - 1,
			tearray[pin2]->xpos + 1,
			tearray[pin2]->ypos + 1, 
			NEWPINCOLOR,
			pin2 ) ;
	} else {  /* we moved a pin output old and new positions */
	    if( aNetSeg[seg].current == 0 ) {
		sptr = aNetSeg[seg].top ;
	    } else {
		sptr = aNetSeg[seg].bot ;
	    }
	    pin1 = sptr->pin1 ;
	    pin2 = sptr->pin2 ;
	     
	    checkPos(tearray[pin1],NEWPOS,llx,lly,urx,ury) ;
	    checkPos(tearray[pin2],NEWPOS,llx,lly,urx,ury) ;
	    checkPos(tearray[pin1],OLDPOS,llx,lly,urx,ury) ;
	    checkPos(tearray[pin2],OLDPOS,llx,lly,urx,ury) ;

	    if (tearray[pin1]->newy != tearray[pin2]->newy){  /* bend so you can see */
		fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n", 
			net,
			tearray[pin1]->newx ,
			tearray[pin1]->newy ,
			tearray[pin1]->newx  - 2 ,
			(tearray[pin1]->newy + tearray[pin2]->newy) / 2,
			OLDNETCOLOR) ;
		fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n", 
			net,
			tearray[pin1]->newx  - 2,
			(tearray[pin1]->newy + tearray[pin2]->newy) /2 ,
			tearray[pin2]->newx ,
			tearray[pin2]->newy ,
			OLDNETCOLOR) ;
	    } else { /* we need to bend the net */
		if ( (int) tearray[pin1]->pinloc == -1 ){ /* if current then bottom seg */
		    factor = -1;  /* bend downwards */
		} else {
		    factor = 1;   /* bend upwards */
		}
		fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n", 
			net,
			tearray[pin1]->newx ,
			tearray[pin1]->newy ,
			(tearray[pin1]->newx + tearray[pin2]->newx)/2 ,
			tearray[pin2]->newy + factor * separation * 3 / 4 ,
			OLDNETCOLOR) ;
		fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n", 
			net,
			(tearray[pin1]->newx + tearray[pin2]->newx)/2 ,
			tearray[pin2]->newy + factor * separation * 3 / 4,
			tearray[pin2]->newx ,
			tearray[pin2]->newy ,
			OLDNETCOLOR) ;
	    }

	    /* now process the equiv / unequivs */  
  	    term1 = tearray[pin1]->terminal ;
	    curExtint = tearray[pin1]->extint ;  
	    for (curTerm=netarray[net]->netptr;curTerm;curTerm= curTerm->nterm){ 
		if (curTerm->extint == curExtint && curTerm->terminal != term1){
		    if (curTerm->unequiv){ /* its an unequiv */
			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    tearray[pin1]->newx ,
			    tearray[pin1]->newy ,
			    curTerm->newx - 2,
			    (curTerm->newy + tearray[pin1]->newy)/2,
			    UNEQUIVCOLOR) ;
			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    curTerm->newx ,
			    curTerm->newy ,
			    curTerm->newx - 2,
			    (curTerm->newy + tearray[pin1]->newy)/2,
			    UNEQUIVCOLOR) ;
		    } else {  /* its an equiv */

			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    tearray[pin1]->newx ,
			    tearray[pin1]->newy ,
			    curTerm->newx - 2,
			    (curTerm->newy + tearray[pin1]->newy)/2,
			    EQUIVCOLOR) ;

			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    curTerm->newx ,
			    curTerm->newy ,
			    curTerm->newx - 2,
			    (curTerm->newy + tearray[pin1]->newy)/2,
			    EQUIVCOLOR) ;
		    }
	   	}
	    }

	    /* now output pin2 equivs */
  	    term1 = tearray[pin2]->terminal ;
	    curExtint = tearray[pin2]->extint ;  
	    for (curTerm=netarray[net]->netptr;curTerm;curTerm= curTerm->nterm){ 
		if (curTerm->extint == curExtint && curTerm->terminal != term1){
		    if (curTerm->unequiv){ /* its an unequiv */
			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    tearray[pin2]->newx ,
			    tearray[pin2]->newy ,
			    curTerm->newx - 2,
			    (curTerm->newy + tearray[pin2]->newy)/2,
			    UNEQUIVCOLOR) ;
			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    curTerm->newx ,
			    curTerm->newy ,
			    curTerm->newx - 2,
			    (curTerm->newy + tearray[pin2]->newy)/2,
			    UNEQUIVCOLOR) ;
		    } else {  /* its an equiv */

			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    tearray[pin2]->newx ,
			    tearray[pin2]->newy ,
			    curTerm->newx - 2,
			    (curTerm->newy + tearray[pin2]->newy)/2,
			    EQUIVCOLOR) ;
			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    curTerm->newx ,
			    curTerm->newy ,
			    curTerm->newx - 2,
			    (curTerm->newy + tearray[pin2]->newy)/2,
			    EQUIVCOLOR) ;
		    }
	   	}
	    }

	    fprintf(fpp,"%d, %d, %d, %d, %d, color: %s, label: %d\n",
			net,
			tearray[pin1]->newx - 2,
			tearray[pin1]->newy - 2,
			tearray[pin1]->newx + 2,
			tearray[pin1]->newy + 2, 
			OLDPINCOLOR,
			pin1 ) ;
	    fprintf(fpp,"%d, %d, %d, %d, %d, color: %s, label: %d\n",
			net,
			tearray[pin2]->newx - 2,
			tearray[pin2]->newy - 2,
			tearray[pin2]->newx + 2,
			tearray[pin2]->newy + 2, 
			OLDPINCOLOR,
			pin2 ) ;

	    if( aNetSeg[seg].ncurrent == 0 ) {
		sptr = aNetSeg[seg].ntop ;
	    } else {
		sptr = aNetSeg[seg].nbot ;
	    }
	    pin1 = sptr->pin1 ;
	    pin2 = sptr->pin2 ;
	    if (tearray[pin1]->ypos != tearray[pin2]->ypos){  /* no need to bend */
		fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n", 
			net,
			tearray[pin1]->xpos ,
			tearray[pin1]->ypos ,
			tearray[pin2]->xpos ,
			tearray[pin2]->ypos ,
			NEWNETCOLOR) ;
	    } else { /* we need to bend the net */
		if( (int) tearray[pin1]->pinloc == -1 ){
		    factor = -1;  /* bend downwards */
		} else {
		    factor = 1;   /* bend upwards */
		}
		fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n", 
			net,
			tearray[pin1]->xpos ,
			tearray[pin1]->ypos ,
			(tearray[pin1]->xpos + tearray[pin2]->xpos)/2 ,
			tearray[pin2]->ypos + factor * separation ,
			NEWNETCOLOR) ;
		fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n", 
			net,
			(tearray[pin1]->xpos + tearray[pin2]->xpos)/2 ,
			tearray[pin2]->ypos + factor * separation ,
			tearray[pin2]->xpos ,
			tearray[pin2]->ypos ,
			NEWNETCOLOR) ;
	    }

  	    term1 = tearray[pin1]->terminal ;
	    curExtint = tearray[pin1]->extint ;  
	    for (curTerm=netarray[net]->netptr;curTerm;curTerm= curTerm->nterm){ 
		if (curTerm->extint == curExtint && curTerm->terminal != term1){
		    if (curTerm->unequiv){ /* its an unequiv */
			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    tearray[pin1]->xpos,
			    tearray[pin1]->ypos,
			    curTerm->xpos,
			    curTerm->ypos,
			    UNEQUIVCOLOR) ;
		    } else {  /* its an equiv */

			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    tearray[pin1]->xpos,
			    tearray[pin1]->ypos,
			    curTerm->xpos,
			    curTerm->ypos,
			    EQUIVCOLOR) ;
		    }
	   	}
	    }

	    /* now output pin2 equivs */
  	    term1 = tearray[pin2]->terminal ;
	    curExtint = tearray[pin2]->extint ;  
	    for (curTerm=netarray[net]->netptr;curTerm;curTerm= curTerm->nterm){ 
		if (curTerm->extint == curExtint && curTerm->terminal != term1){
		    if (curTerm->unequiv){ /* its an unequiv */
			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    tearray[pin2]->xpos,
			    tearray[pin2]->ypos,
			    curTerm->xpos,
			    curTerm->ypos,
			    UNEQUIVCOLOR) ;
		    } else {  /* its an equiv */

			fprintf(fp,"%d, %d, %d, %d, %d, color: %s\n",
			    net,
			    tearray[pin2]->xpos,
			    tearray[pin2]->ypos,
			    curTerm->xpos,
			    curTerm->ypos,
			    EQUIVCOLOR) ;
		    }
	   	}
	    }

	    fprintf(fpp,"%d, %d, %d, %d, %d, color: %s, label: %d\n", 
			net,
			tearray[pin1]->xpos - 1,
			tearray[pin1]->ypos - 1,
			tearray[pin1]->xpos + 1,
			tearray[pin1]->ypos + 1, 
			NEWPINCOLOR ,
			pin1) ;
	    fprintf(fpp,"%d, %d, %d, %d, %d, color: %s, label: %d\n", 
			net,
			tearray[pin2]->xpos - 1,
			tearray[pin2]->ypos - 1,
			tearray[pin2]->xpos + 1,
			tearray[pin2]->ypos + 1, 
			NEWPINCOLOR,
			pin2) ;
	}
    }
}
twclose(fp);
twclose(fpp);
return ;
}

void   checkPos(pin,pos,llx,lly,urx,ury) 
NBOXPTR pin ;
int pos ;
int llx ;
int lly ;
int urx ;
int ury ;
{

if( pos == NEWPOS){
    if( pin->xpos > urx ){
	printf("ERROR:pin xpos > urx ; set to urx ;");
	pin->xpos = urx ;
    }

    if( pin->xpos < llx ){
	printf("ERROR:pin xpos < llx ; set to llx ;");
	pin->xpos = llx ;
    }

    if( pin->ypos > ury ){
	printf("ERROR:pin ypos > ury ; set to ury ;");
	pin->ypos =ury ;
    }
    if( pin->ypos < lly ){
	printf("ERROR:pin ypos < lly ; set to lly ;");
	pin->ypos =ury ;
    }
} else {
    if( pin->newx > urx ){
	printf("ERROR:pin newx > urx ; set to urx ;");
	pin->newx = urx ;
    }

    if( pin->newx < llx ){
	printf("ERROR:pin newx < llx ; set to llx ;");
	pin->newx = llx ;
    }

    if( pin->newy > ury ){
	printf("ERROR:pin newy > ury ; set to ury ;");
	pin->newy =ury ;
    }
    if( pin->newy < lly ){
	printf("ERROR:pin newy < lly ; set to lly ;");
	pin->newy =ury ;
    }
}

} 


void dumpEdgeArray(net)
int net ;
  
{
int edge ;
FILE *fp , *fpp ;
int block, left, rite, bot, top , cell , g1 , g2 ;
int llx, lly, urx, ury ;
CBOXPTR cellptr ;
extern int numEdges ;

fp = twopen("cell.file","w",ABORT);


for( block = 1 ; block <= numblock ; block++ ) {

    left = barray[block]->bxcenter + barray[block]->bleft ;
    bot  = barray[block]->bycenter + barray[block]->bbottom ;
    top  = barray[block]->bycenter + barray[block]->btop ;

    if( pairArray[block][0] > 0 ) {
	cell = pairArray[block][ pairArray[block][0] ] ;
	rite = carray[cell]->cxcenter + carray[cell]->tileptr->right;
    } else {
	rite = barray[block]->bxcenter + barray[block]->bright ;
    }

    fprintf(fp,"%d, %d, %d, %d, color: %s, label: row:%d\n",
		left,bot,rite,top, ROWCOLOR, block ) ;
}
/* initialize variables */
llx = INT_MAX ;
lly = INT_MAX ;
urx = INT_MIN ;
ury = INT_MIN ;

for( cell = numcells + 1 ; cell <= numcells + numterms ; cell++ ) { 
    cellptr = carray[cell] ;
    left = cellptr->cxcenter + cellptr->tileptr->left ;
    rite = cellptr->cxcenter + cellptr->tileptr->right ;
    bot  = cellptr->cycenter + cellptr->tileptr->bottom ;
    top  = cellptr->cycenter + cellptr->tileptr->top ;
    fprintf(fp,"%d, %d, %d, %d, color: %s, label: pad:%s\n",
	left,bot,rite,top, PADCOLOR, cellptr->cname ) ;
    /* find bounding box of pads */
    if( left < llx ){
	llx = left ;
    }
    if( rite > urx ){
	urx = rite ;
    }
    if( bot <  lly ){
	lly = bot  ;
    }
    if( top  > ury ){
	ury = top  ;
    }

}
twclose(fp);

fp  = twopen("net.file","w",ABORT);
fpp = twopen("pin.file","w",ABORT);

for( edge = 1 ; edge <= numEdges  ; edge++ ) {
	
    g1 = edgeArray[edge].group1 ;
    g2 = edgeArray[edge].group2 ;

    if( edgeArray[edge].marked == YES ) { /* output in red */

	fprintf(fp,"%d, %d, %d, %d, %d, color: %s, label:%d\n", 
		net,
	        groupArray[g1].aveX,
	        groupArray[g1].aveY,
	        groupArray[g2].aveX,
	        groupArray[g2].aveY,
		NEWGROUPCOLOR,
		edge) ;
    
	fprintf(fpp,"%d, %d, %d, %d, %d, color: %s, label:G%d\n", 
		net,
	        groupArray[g1].aveX - 1,
	        groupArray[g1].aveY - 1,
	        groupArray[g1].aveX + 1,
	        groupArray[g1].aveY + 1,
		NEWPINCOLOR,
		g1) ;
	fprintf(fpp,"%d, %d, %d, %d, %d, color: %s, label:G%d\n", 
		net,
	        groupArray[g2].aveX - 1,
	        groupArray[g2].aveY - 1,
	        groupArray[g2].aveX + 1,
	        groupArray[g2].aveY + 1,
		NEWPINCOLOR,
		g2) ;
    } else {

	fprintf(fp,"%d, %d, %d, %d, %d, color: %s, label:%d\n", 
		net,
	        groupArray[g1].aveX,
	        groupArray[g1].aveY,
	        groupArray[g2].aveX,
	        groupArray[g2].aveY,
		OLDGROUPCOLOR,
		edge) ;
	fprintf(fpp,"%d, %d, %d, %d, %d, color: %s, label:G%d\n", 
		net,
	        groupArray[g1].aveX - 1,
	        groupArray[g1].aveY - 1,
	        groupArray[g1].aveX + 1,
	        groupArray[g1].aveY + 1,
		OLDPINCOLOR,
		g1) ;
	fprintf(fpp,"%d, %d, %d, %d, %d, color: %s, label:G%d\n", 
		net,
	        groupArray[g2].aveX - 1,
	        groupArray[g2].aveY - 1,
	        groupArray[g2].aveX + 1,
	        groupArray[g2].aveY + 1,
		OLDPINCOLOR,
		g2) ;
   }

}
twclose(fp);
twclose(fpp);
}

