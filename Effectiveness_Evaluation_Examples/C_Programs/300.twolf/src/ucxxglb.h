#include "standard.h"
#define MASK 0x3ff 
#define remv_cell( cellptr , post ) (\
( *cellptr != post ) ? (cellptr[ post ] = cellptr[ *cellptr ],\
(*cellptr)-- ) : (*cellptr)-- )
/*
#define add_cell( cellptr , c ) ( cellptr[ ++(*cellptr) ] = c )
*/

extern double T ;
extern double table1[] , table2[] , table3[] ;
extern int wire_chg , binpen_chg , rowpen_chg ;
extern int newrowpenal , newbinpenal , newpenal ;
extern int rowpenal , binpenal , penalty ;
extern int ablock , bblock ;
extern int a , b ;
extern int Apost , Bpost ;
extern int *cellaptr , *cellbptr ;
extern int earlyRej , Rej_error ;
extern double binpenCon , roLenCon ;
extern int delta_vert_cost ;
