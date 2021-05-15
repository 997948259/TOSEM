#include <stdio.h> 
#include <math.h>
#include <string.h>
#include "utils.h"

#ifdef VMS
#define TW_OK 1
#define TW_FAIL 0
#else
#define TW_OK 0
#define TW_FAIL 1
#endif

#define FEED_INSTANCES  /* ---selection of this keyword will cause  */
/*                            each feed-through cell to have        */
/*                            a distinct (instance) name            */


/* I/O macros */
#define twopen(a,b,c) (openFile(a,b,c))
#define twclose(a)    (fclose(a))



/* ***********LEAVE THE BELOW UNCHANGED *************************** */

#ifndef MAXINT
#define MAXINT 0x7FFFFFFF
#endif /* MAXINT */

#define RAND (Yacm_random() )

/* for ignore field in NETBOX */

#define ZERO 0
#define ALLOC(type)    (  (type *) safe_malloc ( sizeof(type) )  )
#define LINE printf(" file : %s  line # %d\n", __FILE__,__LINE__);
#define ABS(value)   ( (value)>=0 ? (value) : -(value) ) 
#define make_string(s) strcpy(safe_malloc(strlen(s)+1), s)
#define SetBin(x) (( (Trybin=((x)-binOffst)/binWidth)<0 ) ? 0 : \
                  ((Trybin>numBins) ? numBins : Trybin )) 

#define CULLNULL (CBOXPTR) NULL
#define NETNULL (NBOXPTR) NULL
#define DIMNULL (DBOXPTR) NULL
#define TILENULL (TIBOXPTR) NULL
#define TERMNULL (TEBOXPTR) NULL
#define TNETNULL (TNETSPTR) NULL
#define L   1 
#define B   4 
#define MUL 5 
#define MUR 6 
#define MLL 7 
#define MLR 8 
#define ML  9 
#define MR  10
#define MB  11 
#define MT  12 
#define MM  13 
#define MTT 14 
#define MBB 15 
#define TRUE 1
#define FALSE 0
#define LEFT_MOST 0
#define RITE_MOST 1
#define FEED_FLAG 2
#define NOT_DONE -2
#define NO_PINS -1000
#define BIG_NUMBER 32000
#define ROW_STATS rowgrid
#define YES 1
#define NO 0
#define ABORT 1
#define NOABORT 0

typedef struct blockbox {
    int bxcenter  ;
    int bycenter  ;
    short int bleft     ;
    short int bright    ;
    short int bbottom   ;
    short int btop      ;
    short int bheight   ;
    short int blength   ;
    short int desire    ;
    short int oldsize   ;
    short int newsize   ;
    short int bclass    ;
    short int borient   ;
} *BBOXPTR, BBOX ;

typedef struct netbox {
    struct netbox *nterm ;
    int terminal ;
    int extint   ;
    int xpos     ;
    int ypos     ;
    int newx     ;
    int newy     ;
    short int row  ;
    short int cell ;
    short int net ;
#ifdef HAVE_SIGNED_CHAR
    signed char pinloc   ;
#else
    char pinloc   ;
#endif /* HAVE_SIGNED_CHAR */
    char unequiv  ;
    char flag     ;
    char layer    ;
} *NBOXPTR, NBOX ;

typedef struct termbox { 
    struct termbox *nextterm ;
    NBOXPTR  termptr;
    int cellterm    ;
    int ei          ;
    short int net   ;
    short int txpos[2] ;
    short int typos[2] ;
    short int ue    ;
} *TEBOXPTR, TEBOX ;

typedef struct tilebox { 
    short int left     ;
    short int right    ;
    short int bottom   ;
    short int top      ;
    TEBOXPTR termsptr ;
}
*TIBOXPTR ,
TIBOX ;

typedef struct cellbox { 
    char *cname           ;
    char corient          ;
    char orflag           ;
    int cxcenter          ;
    int cycenter          ;
    short int cclass      ;
    short int cheight     ;
    short int clength     ;
    short int border      ;
    short int cblock      ;
    short int numterms    ;
    short int padside     ;
    TIBOXPTR tileptr ;
}
*CBOXPTR ,
CBOX ;

typedef struct dimbox {
    NBOXPTR netptr ;
    char *name   ;
    char dflag    ;
    char feedflag ;
    char ignore   ;
    int old_total ;
    int new_total ;
    int xmin     ;
    int newxmin  ;
    int xmax     ;
    int newxmax  ;
    int ymin     ;
    int newymin  ;
    int ymax     ;
    int newymax  ;
    short int Lnum     ;
    short int newLnum  ;
    short int Rnum     ;
    short int newRnum  ;
    short int Bnum     ;
    short int newBnum  ;
    short int Tnum     ;
    short int newTnum  ;
    short int numpins  ;
    double Vweight ;
    double Hweight ;
}
*DBOXPTR ,
DBOX ;


typedef struct hash {
    char *hname ;
    int hnum ;
    struct hash *hnext ;
}
HASHBOX , 
*HASHPTR ;

typedef struct rowbox {
    int startx  ;
    int endx    ;
    int endx1   ;
    int startx2 ;
    int ypos    ;
    int desiredL ;
} ROWBOX ;

typedef struct binbox {
    int left ;
    int right ;
    int *cell ;
    int penalty ;
    int nupenalty ;
} BINBOX ,
*BINPTR ;

typedef struct changrdbox {
    NBOXPTR netptr ;
    short int tracks ;
    short int ntracks ;
    short int SegType ;
    short int nSegType ;
    struct changrdbox *prevgrd ;
    struct changrdbox *nprevgrd ;
    struct changrdbox *nextgrd ;
    struct changrdbox *nnextgrd ;
    struct densitybox *dptr ;
}
*CHANGRDPTR ,
CHANGRDBOX ;


#ifdef MAIN_VARS
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN HASHPTR *hashtab ;

EXTERN int netctr ;

EXTERN CBOXPTR  *carray  ;
EXTERN DBOXPTR   *netarray   ;
EXTERN NBOXPTR *tearray  ;
EXTERN BBOXPTR *barray ;
EXTERN ROWBOX *rowArray ;
EXTERN BINBOX ***binptr ;
EXTERN CHANGRDPTR ULgrdptr , URgrdptr , LLgrdptr , LRgrdptr , *Shuffle ;

EXTERN int bdxlen , bdylen ;

EXTERN int numblock ;
EXTERN int numcells ;
EXTERN int numterms ;
EXTERN int numnets ;
EXTERN int numRows ;

EXTERN int penalty  ;
EXTERN int funccost ;
EXTERN int Trybin   ;
EXTERN int binpenal ;
EXTERN int rowpenal ;
EXTERN int newrowpenal ;
EXTERN int newbinpenal ;
EXTERN int Left_bound, Rite_bound ;
EXTERN int **cedgebin, cedge_binwidth, num_edgebin ;
EXTERN int gtopChan , gbotChan ;
EXTERN int one_pin_feedthru ;


EXTERN int numBins  ;
EXTERN int binWidth ;
EXTERN int binOffst ;
EXTERN int fdWidth  ;

EXTERN int feeds ;
EXTERN short int **rowgrid ;
EXTERN int windx ;
EXTERN int randVar ;
EXTERN int max_blklength ;
EXTERN int desiredL ;
EXTERN int implicit_feed_count ;
EXTERN int *feeds_in_row ;
EXTERN int resume_run ;
EXTERN int uneven_cell_height ;
EXTERN int track_spacing ;
EXTERN char cktName[] ;
EXTERN FILE *fpo ;

#undef EXTERN

extern FILE *openFile() ;
