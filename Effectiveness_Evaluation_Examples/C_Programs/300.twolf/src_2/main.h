/* main.h - insert file for main.c */

/* global variables defined for main */
#ifdef MAIN_VARS
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN FILE *fpo ;
EXTERN unsigned randomSeed  ;
EXTERN unsigned randomSeed2 ;
EXTERN char cktName[128] ;
EXTERN int connection_machine ;
EXTERN int estimate_feeds ;
EXTERN int tw_fast ;
EXTERN int gate_array_special ;
EXTERN int pin_layers_given ;
EXTERN int no_feeds_side_nets ;
EXTERN int no_net_normalize ;
EXTERN int route2act ;    /* added for placement adjusted for routing */
EXTERN int routeGrid ;    /* used only if global routing is performed */
EXTERN int gridCell ;    /* used only if global routing is performed */
EXTERN int feedLayer ;
EXTERN int resume_run ;
EXTERN int attmax ;
EXTERN int maxCellO ;
EXTERN int iteration ;
EXTERN int iwire ;
EXTERN int iwirex ;
EXTERN int iwirey ;
EXTERN int fwire ;
EXTERN int fwirex ;
EXTERN int fwirey ;
EXTERN int blkxspan ;
EXTERN int blkyspan ;
EXTERN int ffeeds ;
EXTERN int addFeeds ;
EXTERN int fdWidth ;
EXTERN int lrtxspan ;
EXTERN int lrtyspan ;
EXTERN int **pairArray ;
EXTERN int attprcel ;
EXTERN int doglobal ; 
EXTERN int cswaps ;
EXTERN int costonly ;
EXTERN int restart  ;
EXTERN int ifrange ;
EXTERN int *fixarray ;
EXTERN int tw_fast ;
EXTERN int tw_slow ;
EXTERN double T ;
EXTERN double Tzero ;
EXTERN double *desired_accept ;
EXTERN double imprange ;
EXTERN double binpenCon ;
EXTERN double indent ;
EXTERN double rowSep ;
EXTERN double roLenCon ;
EXTERN double stopdeg ;
EXTERN double macspace[16] ;
EXTERN double cost_scale_factor ;

#undef EXTERN

extern int tracks ;
extern int numChans ;
extern int *maxTrack ;
extern int rowHeight ;
extern int maxterm ;
extern int fdthrus ;
extern int numSegs ;
extern int impcount ;
extern int *nofeed ;
extern int stage ;
extern int *pinlist ;
extern int one_pin_feedthru ;
