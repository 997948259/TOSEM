#include <stdio.h> 
#include <math.h>

#define ABS(value)   ( (value)>=0 ? (value) : -(value) ) 
#define LEFT  -1
#define RIGHT 1
#define OLD 0
#define NEW 1

typedef struct tgridbox {
    CHANGRDPTR up ;
    CHANGRDPTR down ;
}
*TGRIDPTR ,
TGRIDBOX ;

typedef struct densitybox {
    CHANGRDPTR grdptr ;
    struct densitybox *next ;
    struct densitybox *nnext ;
    struct densitybox *back ;
    struct densitybox *nback ;
}
*DENSITYPTR ,
DENSITYBOX ;

typedef struct segbox {
    short int channel ;
    int pin1    ;
    int pin2    ;
    CHANGRDPTR pin1ptr    ;
    CHANGRDPTR pin2ptr   ;
}
*SEGBOXPTR ,
SEGBOX ;

typedef struct switchbox {
    int net ;
    char nflag ;
    char ncurrent ;
    char nswYorN ;
    char current ;
    char swYorN ;
    short int key ;
    short int nkey ;
    SEGBOXPTR ntop ;
    SEGBOXPTR nbot ;
    SEGBOXPTR top ;
    SEGBOXPTR bot ;
}
*SWITCHBOXPTR ,
SWITCHBOX ;


#define GRDNULL ( ( CHANGRDPTR ) NULL ) 
#define DENSENULL ( ( DENSITYPTR ) NULL ) 

extern SWITCHBOX  *aNetSeg ;
extern CHANGRDPTR *Begin , *End ;
extern DENSITYPTR **Densebox , **DboxHead ;
extern TGRIDPTR *Tgrid ;
extern double mean_width ;
extern int *anet ;
extern int *netchgs ;
extern int *fixnetseg ;
extern int **pairArray ;
extern int numChans , maxterm , numnets ;
extern int numSegs , numSwSegs ;
extern int tracks ;
extern int *maxTrack , *nmaxTrack ;
extern int max_tdensity ;
extern int gxstart , gxstop ;
extern int **cedgebin , cedge_binwidth , num_edgebin ;
extern int blkleft , blkrite ;
extern int Left_bound , Rite_bound ;
extern int gtopChan , gbotChan ;
extern int uneven_cell_height ;
extern int ffeeds , track_spacing ;
extern CHANGRDPTR ULgrdptr , URgrdptr , LLgrdptr , LRgrdptr , *Shuffle ;
