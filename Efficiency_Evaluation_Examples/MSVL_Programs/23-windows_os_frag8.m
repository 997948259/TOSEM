//#Safe
//@ ltl invariant positive: <>[]AP(polling == 1);
</
  define p: polling=1;
  som(alw(p))
/>


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
//#define CountLookup __VERIFIER_nondet_int

frame(WarmPollPeriod,
status,
polling,
PowerStateIsAC,
Count,
timeOut1,

deviceStatus,
devId,
requestRescan,
ddd,
mfg, mdl, cls, des, aid, cid,
break_1
)
and
(
int WarmPollPeriod and
int Count and
int polling and
int PowerStateIsAC and

int   timeOut1 and
int   status and
int   deviceStatus and
int   devId and
int   requestRescan and
int ddd and
int  mfg, 
mdl<==1,
 cls, 
 des, 
 aid, 
 cid 
 and

int break_1<==0 and

WarmPollPeriod <==0// __VERIFIER_nondet_int()
and
status <== 2//__VERIFIER_nondet_int()
and
polling <== 0 //__VERIFIER_nondet_int() 
and
Count <== 10 //__VERIFIER_nondet_int()
and
PowerStateIsAC <== 0 //__VERIFIER_nondet_int()
and skip;

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
           //if (__VERIFIER_nondet_int()) {
               // We've got it.  Now get a pointer to it.
             //  if(__VERIFIER_nondet_int()) {
//---------------------------------------------
             ( (// {             
                   Count :=6;// CountLookup();
                   if(Count>0 AND !break_1)then
				   {
                      /* if( PowerStateIsAC ) {
                       } else {
                       }*/
                       (status := -1 
					  ) ;//KeWaitForSingleObject();
                       /*if( __VERIFIER_nondet_int() ) {
                           break;
                       }*/
					   (break_1:=1 
					   );
					   if(!break_1)then
					   {
                      /* if( !PowerStateIsAC ) 
					  {
			 //goto mylabl;
                       }*/
                       if(  status= -1 ) then
					   {
                           //if( __VERIFIER_nondet_int() ) {
                               // try to acquire port
                              // if( HtTryAllocatePort() ) {
                              //  ((   
								requestRescan := 0;
                                   // check for something connected
                                   deviceStatus :=0;// GetStatus();
                                  // if( __VERIFIER_nondet_int()) {
                                  // } else {
                                       // we might have something connected
                                       // try a device ID to confirm
                             // (skip or 
        							//  (
							           (devId :=1 								   
									   or devId :=0);//P4ReadRawIeee1284DeviceId();
                                       if( devId )then
									   {                                          
                                          // RawIeee1284 string includes 2 bytes of length data at beginning
                                           //HTPnpFindDeviceIdKeys();
										   mfg:=1;
                                           if( mfg AND mdl ) then{
                                               requestRescan := 1
                                           }
                                       } else {
									    skip
                                       }
                                       //if( requestRescan ) {
                                       //} else {									   
                                         //  if(__VERIFIER_nondet_int() ) {
                                        //   }
                                      // }
									 //  ))
                                   //}
                                   //HtFreePort( );
								   
                                   //if( requestRescan ) {
								   
                                    //   IoInvalidateDeviceRelations();
                                   //}
								   
                             // ) or skip)// } else {
                              // }
                           //} else {
                           //}
                       };
					   
		              ddd := ddd;
					  Count:=Count-1
					  }
                   }
               //}
//---------------------------------------------
               ))
			   //} else {
                   // error
              // }
           //} else {
           //}
       //}
   };
   // Failsafe
   polling := 1
}