//#Safe
//@ ltl invariant positive: <>[]AP(polling==1);

</
define p: polling=1;
som(alw(p))
/>

frame(WarmPollPeriod,

polling,
PowerStateIsAC,

timeOut1,
status,
deviceStatus,
devId,
requestRescan,
pollingFailureThreshold,
break_1,
loc_continue,
ddd,
mfg, mdl, cls, des, aid, cid
)
and
(
int WarmPollPeriod and
//int status and
int polling and
int PowerStateIsAC and

int   timeOut1 and
int   status and
int   deviceStatus and
int   devId and
int   requestRescan and
int   pollingFailureThreshold and
int break_1<==0 and
int loc_continue<==0 and
int ddd and
int  mfg, mdl, cls, des, aid, cid and
//void ExAcquireFastMutex() {}
//void ExReleaseFastMutex() {}
//#define GetStatus __VERIFIER_nondet_int
//#define IoInvalidateDeviceRelations __VERIFIER_nondet_int
//#define KeWaitForSingleObject __VERIFIER_nondet_int
//#define P4ReadRawIeee1284DeviceId __VERIFIER_nondet_int
//#define HTPnpFindDeviceIdKeys __VERIFIER_nondet_int
//#define HtFreePort __VERIFIER_nondet_int
//#define HtRegGetDword __VERIFIER_nondet_int
//#define HtTryAllocatePort __VERIFIER_nondet_int
//#define SetFlags __VERIFIER_nondet_int

WarmPollPeriod <==0// __VERIFIER_nondet_int()
and
status <== 2//__VERIFIER_nondet_int()
and
polling <== 0 //__VERIFIER_nondet_int()
//and
//PowerStateIsAC = __VERIFIER_nondet_int()
and skip;
(PowerStateIsAC:=1 );
main()
);





function main() {
   if( status>0  ) then{
      // ExAcquireFastMutex();
       //SetFlags();
       //ExReleaseFastMutex();
       WarmPollPeriod := 3;//HtRegGetDword();
       if( WarmPollPeriod < 5 ) then{
           WarmPollPeriod := 5
       } 
	   else 
	   {
           if( WarmPollPeriod > 20 ) then
		   {
               WarmPollPeriod := 20
           }
       };
       //{
           //if (__VERIFIER_nondet_int()) 
		   //{
               // We've got it.  Now get a pointer to it.
             ((  polling:= 1;
              // if(__VERIFIER_nondet_int()) 
			  // {
//---------------------------------------------
              // {
               (
                   pollingFailureThreshold := 10; //pick an arbitrary but reasonable number
                   if( !break_1 ) then
				   {
                      /* if( PowerStateIsAC ) {
                       } else {
                       }*/
                       //status = KeWaitForSingleObject();
					   (status:=-1 or status:=0);
					   (break_1:=0 or break_1:=1);
                       /*if( __VERIFIER_nondet_int() ) {
                           break;
                       }*/
					   if(!break_1)then
					   {
                       if( !PowerStateIsAC ) then
					   {
                           loc_continue:=1
                       };
					   if(!loc_continue)then
					   {
                        if(  status= -1 )then
						{
                           //if( __VERIFIER_nondet_int() )
						   //{
                               // try to acquire port
                           (   //if( HtTryAllocatePort() ) {
                                   requestRescan := 0;
                                   // check for something connected
                                   deviceStatus := 0;//GetStatus();
                                   //if( __VERIFIER_nondet_int()) {
                                   //} else {
                                       // we might have something connected
                                       // try a device ID to confirm
                                  (  (  
 								       //devId = P4ReadRawIeee1284DeviceId();
									   (devId:=1 );
                                       if( devId )then {                                           
                                           // RawIeee1284 string includes 2 bytes of length data at beginning
                                           //HTPnpFindDeviceIdKeys();
										   (mfg:=1 or mfg:=0);
										   mdl:=1;
                                           if( mfg AND mdl )then {
                                               requestRescan := 1
                                           }
                                       } else {
									      skip
                                       }
                                       /*if( requestRescan )then {
                                       } else {
                                           if(__VERIFIER_nondet_int() ) {
                                           }
                                       }*/
									   ))
                                   //}
                                   //HtFreePort( );
                                   /*if( requestRescan ) {
                                       IoInvalidateDeviceRelations();
                                   }*/
                               //} else {
                               //}
							   )
                           //} else {
                           //}
						   
                       }					   
					   };
		               ddd := ddd
		              }
                   } ;
               //}
//---------------------------------------------
                   polling := 0
               )//} else {
                or   polling := 0
                   // error
               //}
           //} else {
           //}
		   ))
       //}
   };
   // Failsafe
   polling := 1
}