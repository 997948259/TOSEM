#include "standard.h"
extern int no_net_normalize ;

readnets( fp )
FILE *fp ;
{

int net , test , status ;
double Hweight , Vweight , beta , total_weight ;
NBOXPTR netptr ;
char input[1024] ;


fscanf( fp , " %s ", input ) ;
if( strcmp( input , "allnets") != 0 ) {
    fprintf( fpo, "The keyword allnets was ");
    fprintf( fpo, "not properly entered in the .net file\n");
    exit(TW_FAIL);
}
fscanf( fp , " %s ", input ) ;
if( strcmp( input , "HVweights") != 0 ) {
    fprintf( fpo, "The keyword HVweights was ");
    fprintf( fpo, "not properly entered in the .net file\n");
    exit(TW_FAIL);
}
test = fscanf( fp , "%lf %lf" , &Hweight , &Vweight ) ;
if( test != 2 ) {
    fprintf( fpo, "The net weights for allnets were ");
    fprintf( fpo, "not properly entered in the .net file\n");
    exit(TW_FAIL);
}
if( Hweight <= 0.0 || Vweight <= 0.0 ) {
    fprintf( fpo, "A global net weight was ");
    fprintf( fpo, "zero or negative in the \n");
    fprintf(fpo,".net file\n");
    fprintf(fpo,"This is not allowed; choose .0001 instead\n");
    exit(TW_FAIL);
}

if( Vweight < 1.0 ) {
    Vweight = 1.0 ;
}
for( net = 1 ; net <= numnets ; net++ ) {
    netarray[net]->Hweight = Hweight ;
    netarray[net]->Vweight = Vweight ;
}

while( fscanf( fp , " %s " , input ) == 1 ) {
    if( strcmp( input , "net") == 0 ) {
	fscanf( fp , " %s ", input ) ;
	status = hashfind( input ) ;
	if( status == 0 ) {
	    fprintf( fpo, "The net named: %s  in the .net file\n",
						    input );
	    fprintf( fpo, "was not encountered while reading\n");
	    fprintf( fpo, "the .cel file --- FATAL error\n");
	    exit(TW_FAIL);
	}
    } else if( strcmp( input , "HVweights") == 0 ) {
	test = fscanf( fp , "%lf %lf" , &Hweight , &Vweight ) ;
	if( test != 2 ) {
	    fprintf( fpo, "The critical net weights were ");
	    fprintf( fpo, "not properly entered\n");
	    fprintf(fpo,"in the .net file after net: %s\n",
							input);
	    exit(TW_FAIL);
	}
	if( Hweight <= 0.0 || Vweight <= 0.0 ) {
	    fprintf( fpo, "A critical net weight was ");
	    fprintf( fpo, "zero or negative in the \n");
	    fprintf(fpo,".net file after net: %s\n", input);
	    fprintf(fpo,"This is not allowed; choose .0001 instead\n");
	    exit(TW_FAIL);
	}
	netarray[status]->Hweight = Hweight ;
	netarray[status]->Vweight = Vweight ;
    } else if( strcmp( input , "nofeeds" ) == 0 ) {
	netarray[status]->feedflag = 1 ;
    } else if( strcmp( input , "ignore" ) == 0 ) {
	netarray[status]->ignore = 1 ;
    } else {
	fprintf( fpo, "unexpected keyword in the .net file\n");
	exit(TW_FAIL);
    }
}

delHtab() ;


if( ! no_net_normalize ) {
    total_weight = 0 ;
    for( net = 1 ; net <= numnets ; net++ ) {
	total_weight += netarray[net]->Hweight + netarray[net]->Vweight ;
    }
    beta = 2.0 * (double) numnets / total_weight ;

    for( net = 1 ; net <= numnets ; net++ ) {
	netarray[net]->Hweight *= beta ;
	netarray[net]->Vweight *= beta ;

    }
}


for( net = 1 ; net <= numnets ; net++ ) {
    for( netptr = netarray[ net ]->netptr ; netptr != NETNULL ;
				    netptr = netptr->nterm ) {
	tearray[ netptr->terminal ] = netptr ;
	tearray[ netptr->terminal ]->net = net ;
    }
}
return ;
}
