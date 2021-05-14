//#Safe
// ****************************************************
//
//     Making Prophecies with Decision Predicates
//
//              Byron Cook * Eric Koskinen
//                     July 2010
//
// ****************************************************

//@ ltl invariant positive: <>[]AP(polling == 1);

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assume();
extern int __VERIFIER_nondet_int();

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
int WarmPollPeriod;
int status;
int polling;
int PowerStateIsAC;
int Count;
LARGE_INTEGER   timeOut1;
UCHAR           deviceStatus;
PCHAR           devId;
BOOLEAN         requestRescan;
int tmp;
   WarmPollPeriod = 0;
   status = 2;
   polling = 0;
   PowerStateIsAC = 0;
   Count = 10;
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
           if (1) {
               if(1) {
					LARGE_INTEGER   timeOut1;
                   NTSTATUS        status;
                   UCHAR           deviceStatus;
                   PCHAR           devId;
                   BOOLEAN         requestRescan;
                   Count = 6;
                   do {
                       if( PowerStateIsAC ) {
                       } else {
                       }
                       status = -1;
                       if( 0 ) {
                           break;
                       }
                       if( !PowerStateIsAC ) {
                       }
                       if( STATUS_TIMEOUT == status ) {
                           if( 1 ) {
                               // try to acquire port
                               if( 1 ) {
                                   requestRescan = FALSE;
                                   // check for something connected
                                   deviceStatus = 0;
                                   if( 1) {
                                   } else {
                                       // we might have something connected
                                       // try a device ID to confirm
                                       devId = 1;
                                       if( devId ) {
                                           PCHAR  mfg, mdl, cls, des, aid, cid;
                                           // RawIeee1284 string includes 2 bytes of length data at beginning
                                           
                                           if( mfg && mdl ) {
                                               requestRescan = TRUE;
                                           }
                                       } else {
                                       }
                                       if( requestRescan ) {
                                       } else {
                                           if(1 ) {
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
		   mylabl: { int ddd; ddd = ddd; }
                   } while( --Count>0 );
//---------------------------------------------
               } else {
                   // error
               }
           } else {
           }
   }
   // Failsafe
   polling = 1;
   tmp=10000000;
	while (tmp>0) {tmp=tmp-1;}
   }
}