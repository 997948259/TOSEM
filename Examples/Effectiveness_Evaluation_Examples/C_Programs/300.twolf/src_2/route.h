typedef struct edgeBox {
    short int group1 ;
    short int group2 ;
    short int cost   ;
    short int marked ;
    short int poison ;
    short int done   ;
}
*edgeBptr, 
edgeBox ;

typedef struct chkBox {
    short int lowx  ;
    short int highx ;
    short int ming  ;
    short int maxg  ;
    short int chky  ;
}
*chkBptr, 
chkBox ;
 
typedef struct csPinBox {
    int pin  ; 
    short int xloc ; 
    short int yloc ; 
    short int top  ; 
}
*csPinPtr ,
csPinBox ;

typedef struct csGroup { 
    int extint  ; 
    int aveX    ; 
    int aveY    ; 
    short int poison  ;
    short int edge1   ;
    short int edge2   ;
    short int unequiv ;
    short int block   ; 
    short int check   ; 
    short int numPins ; 
    short int pinLimit ;
    short int flag    ; 
    csPinBox *pinArray ;
}
csGroup ;

extern csGroup *groupArray ;
extern chkBox *checkArray ;
extern int MPG ;
extern int ME  ;
extern edgeBox *edgeArray ;
