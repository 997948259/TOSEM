

#include "standard.h"
#include "groute.h"
#include "utils.h"

extern NBOXPTR *tearray  ;
extern int numRows ;
extern FILE *fpo ;

readseg( fp )
FILE *fp ;
{

int segment , net , net1 , net2 , key_flag ;
int channel , pin1 , pin2 ;
int ltop , rtop , lbot , rbot ;
int Tleft , Tright , Bleft , Bright ;
char input[16] ;
SEGBOXPTR tmp_ptr ;

segment   = 0 ;
numSwSegs = 0 ;
numSegs   = 0 ;

while( fscanf( fp , " %s " , input ) == 1 ) {
    if( strcmp( input , "net") == 0 ) {
	fscanf( fp , " %d " , &net ) ;
    } else if( strcmp( input , "segment") == 0 ) {
	numSegs++ ;
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "channel") == 0 ) {
	    fscanf( fp , "%d" , &channel ) ;
	    fscanf( fp , " %s " , input )  ;
	    fscanf( fp , "%d" , &pin1 )    ;
	    fscanf( fp , " %s " , input )  ;
	    fscanf( fp , "%d" , &pin2 )    ;
	    fscanf( fp , "%d" , &ltop )    ;
	    fscanf( fp , "%d" , &rtop )    ;
	} else { /* input a switchable segment */
	    numSwSegs++ ;
	    fscanf( fp , "%d" , &key_flag ) ;
	    fscanf( fp , " %s " , input )  ; /*  "top"     */
	    fscanf( fp , " %s " , input )  ; /*  "channel" */
	    fscanf( fp , "%d" , &channel ) ;
	    fscanf( fp , " %s " , input )  ;
	    fscanf( fp , "%d" , &pin1 )    ;
	    fscanf( fp , " %s " , input )  ;
	    fscanf( fp , "%d" , &pin2 )    ;
	    fscanf( fp , "%d" , &ltop )    ;
	    fscanf( fp , "%d" , &rtop )    ;
	    fscanf( fp , " %s " , input )  ; /*  "bot"    */
	    fscanf( fp , " %s " , input )  ; /* "channel" */
	    fscanf( fp , "%d" , &channel ) ;
	    fscanf( fp , " %s " , input )  ;
	    fscanf( fp , "%d" , &pin1 )    ;
	    fscanf( fp , " %s " , input )  ;
	    fscanf( fp , "%d" , &pin2 )    ;
	    fscanf( fp , "%d" , &lbot )    ;
	    fscanf( fp , "%d" , &rbot )    ;
	}
    }
}
fprintf(fpo,"\nTotal Number of Net Segments: %d\n", numSegs ) ;
fprintf(fpo,"Number of Switchable Net Segments: %d\n\n", numSwSegs ) ;
fprintf(fpo,"Number of channels: %d\n\n", numChans ) ;
rewind( fp ) ;


aNetSeg = ( SWITCHBOXPTR ) safe_malloc((numSegs + 1) 
					* sizeof( SWITCHBOX ) );
fixnetseg = ( int * ) safe_malloc((numSegs + 1) * sizeof( int ) );
anet = (int *) safe_malloc( (numnets + 2) * sizeof( int ) ) ;
for( net = 0 ; net <= numnets + 1 ; net++ ) {
    anet[net] = 0 ;
}
netchgs = (int *) safe_malloc( (numnets + 1) * sizeof( int ) ) ;

while( fscanf( fp , " %s " , input ) == 1 ) {
    if( strcmp( input , "net") == 0 ) {
	fscanf( fp , " %d " , &net ) ;
	anet[net] = segment + 1 ;
    } else if( strcmp( input , "segment") == 0 ) {
	segment++ ;
	fscanf( fp , " %s " , input ) ;
	if( strcmp( input , "channel") == 0 ) {
	    fscanf( fp , "%d" , &channel ) ;
	    fscanf( fp , " %s " , input )  ;
	    fscanf( fp , "%d" , &pin1 )    ;
	    fscanf( fp , " %s " , input )  ;
	    fscanf( fp , "%d" , &pin2 )    ;
	    fscanf( fp , "%d" , &ltop )    ;
	    fscanf( fp , "%d" , &rtop )    ;
	    aNetSeg[segment].top = 
		    (SEGBOXPTR) safe_malloc( sizeof(SEGBOX) );
	    aNetSeg[segment].bot = 
		    (SEGBOXPTR) safe_malloc( sizeof(SEGBOX) );
	    aNetSeg[segment].ntop = 
		    (SEGBOXPTR) safe_malloc( sizeof(SEGBOX));
	    aNetSeg[segment].nbot = 
		    (SEGBOXPTR) safe_malloc( sizeof(SEGBOX));
	    aNetSeg[segment].net = net ;
	    aNetSeg[segment].nflag = 0 ;
	    aNetSeg[segment].current = 0 ;
	    aNetSeg[segment].swYorN = 0 ;
	    aNetSeg[segment].key = 0 ;
	    aNetSeg[segment].nkey = 0 ;
	    aNetSeg[segment].top->channel = channel ;
	    aNetSeg[segment].top->pin1    = pin1    ;
	    aNetSeg[segment].top->pin2    = pin2    ;
	    aNetSeg[segment].top->pin1ptr = Tgrid[ pin1 ]->up ;
	    if( tearray[ pin1 ]->pinloc == 0 &&
		tearray[ pin1 ]->row == channel ) {
		aNetSeg[segment].top->pin1ptr = Tgrid[ pin1 ]->down;
	    }
	    aNetSeg[segment].top->pin2ptr = Tgrid[ pin2 ]->up ;
	    if( tearray[ pin2 ]->pinloc == 0 &&
		tearray[ pin2 ]->row == channel ) {
		aNetSeg[segment].top->pin2ptr = Tgrid[ pin2 ]->down;
	    }
	} else { /* input a switchable segment */
	    fscanf( fp , "%d" , &key_flag ) ;
	    fscanf( fp , " %s " , input ) ; /* "top"     */
	    fscanf( fp , " %s " , input ) ; /* "channel" */
	    fscanf( fp , "%d" , &channel ) ;
	    fscanf( fp , " %s " , input ) ;
	    fscanf( fp , "%d" , &pin1 ) ;
	    fscanf( fp , " %s " , input ) ;
	    fscanf( fp , "%d" , &pin2 ) ;
	    fscanf( fp , "%d" , &ltop )    ;
	    fscanf( fp , "%d" , &rtop )    ;
	    aNetSeg[segment].top =
		    (SEGBOXPTR) safe_malloc( sizeof(SEGBOX) );
	    aNetSeg[segment].bot = 
		    (SEGBOXPTR) safe_malloc( sizeof(SEGBOX) );
	    aNetSeg[segment].ntop = 
		    (SEGBOXPTR) safe_malloc( sizeof(SEGBOX));
	    aNetSeg[segment].nbot = 
		    (SEGBOXPTR) safe_malloc( sizeof(SEGBOX));
	    aNetSeg[segment].net = net ;
	    aNetSeg[segment].nflag = 0 ;
	    aNetSeg[segment].current = 0 ;
	    aNetSeg[segment].swYorN = 1 ;
	    if( key_flag == 0 || 
			    ((anet[net] - 1 + key_flag) == segment) ) {
		aNetSeg[segment].key = 0 ;
	    } else {
		aNetSeg[segment].key = key_flag + anet[net] - 1 ;
	    }
	    aNetSeg[segment].nkey = 0 ;
	    aNetSeg[segment].top->channel = channel ;
	    aNetSeg[segment].top->pin1    = pin1    ;
	    aNetSeg[segment].top->pin2    = pin2    ;
	    if( ltop == -1 ) {
		pin1 = pin2 ;
	    } else if( ltop > 0 ) {
		pin1 = ltop ;
		pin2 = rtop ;
	    }
	    Tleft = tearray[ pin1 ]->xpos ;
	    aNetSeg[segment].top->pin1ptr = Tgrid[ pin1 ]->up ;
	    if( tearray[ pin1 ]->pinloc == 0 &&
		tearray[ pin1 ]->row == channel ) {
		aNetSeg[segment].top->pin1ptr = Tgrid[ pin1 ]->down;
	    }
	    Tright = tearray[ pin2 ]->xpos ;
	    aNetSeg[segment].top->pin2ptr = Tgrid[ pin2 ]->up ;
	    if( tearray[ pin2 ]->pinloc == 0 &&
		tearray[ pin2 ]->row == channel ) {
		aNetSeg[segment].top->pin2ptr = Tgrid[ pin2 ]->down;
	    }
	    fscanf( fp , " %s " , input ) ;
	    fscanf( fp , " %s " , input ) ;
	    fscanf( fp , "%d" , &channel ) ;
	    fscanf( fp , " %s " , input ) ;
	    fscanf( fp , "%d" , &pin1 ) ;
	    fscanf( fp , " %s " , input ) ;
	    fscanf( fp , "%d" , &pin2 ) ;
	    fscanf( fp , "%d" , &lbot )    ;
	    fscanf( fp , "%d" , &rbot )    ;
	    aNetSeg[segment].bot->channel = channel ;
	    aNetSeg[segment].bot->pin1    = pin1    ;
	    aNetSeg[segment].bot->pin2    = pin2    ;
	    if( lbot == -1 ) {
		pin1 = pin2 ;
	    } else if( lbot > 0 ) {
		pin1 = lbot ;
		pin2 = rbot ;
	    }
	    Bleft = tearray[ pin1 ]->xpos ;
	    aNetSeg[segment].bot->pin1ptr = Tgrid[ pin1 ]->up ;
	    if( tearray[ pin1 ]->pinloc == 0 &&
		tearray[ pin1 ]->row == channel ) {
		aNetSeg[segment].bot->pin1ptr = Tgrid[ pin1 ]->down;
	    }
	    Bright = tearray[ pin2 ]->xpos ;
	    aNetSeg[segment].bot->pin2ptr = Tgrid[ pin2 ]->up ;
	    if( tearray[ pin2 ]->pinloc == 0 &&
		tearray[ pin2 ]->row == channel ) {
		aNetSeg[segment].bot->pin2ptr = Tgrid[ pin2 ]->down;
	    }
	    if( Bleft == Bright || Tleft == Tright ) {
		aNetSeg[segment].swYorN = 0 ;
		if( Bleft == Bright && Tleft != Tright ) {
		    tmp_ptr = aNetSeg[segment].top ;
		    aNetSeg[segment].top = 
				aNetSeg[segment].bot ;
		    aNetSeg[segment].bot = tmp_ptr ;
		}
	    }
	}
    }
}
net2 = net + 1 ;
anet[net2] = segment + 1 ;
for( net = 1 ; net < net2 ; net++ ) {
    if( anet[net] == 0 ) {
	for( net1 = net + 1 ; net1 <= net2 ; net1++ ) {
	    if( anet[net1] != 0 ) {
		anet[net] = anet[net1] ;
		break ;
	    }
	}
    }
}

return ;
}
