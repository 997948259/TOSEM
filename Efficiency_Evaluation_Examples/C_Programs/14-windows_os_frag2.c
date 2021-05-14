//#Safe
// ****************************************************
//
//     Making Prophecies with Decision Predicates
//
//              Byron Cook * Eric Koskinen
//                     July 2010
//
// ****************************************************

//@ ltl invariant positive: <>[]AP(polling==1);

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assume();
extern int __VERIFIER_nondet_int();

int WarmPollPeriod;
int status;
int polling;
int PowerStateIsAC;
int tmp;
#define NT_SUCCESS(s) s>0
#define STATUS_SUCCESS 1
#define STATUS_UNSUCCESSFUL 0
#define STATUS_TIMEOUT (-1)
#define LARGE_INTEGER int
#define NTSTATUS int
#define UCHAR int
#define PCHAR int
#define BOOLEAN int
#define ULONG int
#define NULL 0
#define FALSE 0
#define TRUE 1
WarmPollPeriod = 0;
status = 2;
polling = 0;
PowerStateIsAC = 1;


int main() {
   if( NT_SUCCESS( status ) ) {
       WarmPollPeriod = 3;
       if( WarmPollPeriod < 5 ) {
           WarmPollPeriod = 5;
       } else {
           if( WarmPollPeriod > 20 ) {
               WarmPollPeriod = 20;
           }
       }
       {
           if (1) {
               polling = 1;
               if(1) {
//---------------------------------------------
                   LARGE_INTEGER   timeOut1;
                   NTSTATUS        status;
                   UCHAR           deviceStatus;
                   PCHAR           devId;
                   BOOLEAN         requestRescan;
                   const ULONG     pollingFailureThreshold = 10; //pick an arbitrary but reasonable number
                   tmp=10;
				   do {
                       if( PowerStateIsAC ) {
                       } else {
                       }
                       if( 0 ) {
                           break;
                       }
                       if( !PowerStateIsAC ) {
                           goto loc_continue;
                       }
                       if( STATUS_TIMEOUT == status ) {
                           if( 1 ) {
                               if( 1 ) {
                                   requestRescan = FALSE;
                                   // check for something connected
                                   deviceStatus = 0;
                                   if(0) {
                                   } else {
                                       // we might have something connected
                                       // try a device ID to confirm
                                       devId = 1;
                                       if( devId ) {
                                           PCHAR  mfg, mdl, cls, des, aid, cid;
                                           // RawIeee1284 string includes 2 bytes of length data at beginning
                                           if( mfg=1 && mdl=1 ) {
                                               requestRescan = TRUE;
                                           }
                                       } else {
                                       }
                                       if( requestRescan ) {
                                       } else {
                                           if(1) {
                                           }
                                       }
                                   }
                                   if( requestRescan ) {
                                       
                                   }
                               } else {
                               }
                           } else {
                           }
                       }
		   loc_continue: { int ddd; ddd = ddd; }
                   tmp--;
				   } while( tmp>0 );
               
//---------------------------------------------
                   polling = 0;
               } else {
                   polling = 0;
               }
           } else {
           }
       }
   }
   polling = 1;
  tmp=10000000;
	while (tmp>0) {tmp=tmp-1;}
}