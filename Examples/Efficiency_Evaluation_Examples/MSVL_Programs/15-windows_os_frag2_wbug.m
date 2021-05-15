//#unSafe
//@ ltl invariant positive: <>[]AP(polling==1);

</
define p: polling=1;
alw(som(p))
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
mfg, mdl, cls, des, aid, cid,tmp
)
and
(
int WarmPollPeriod and
int status and
int polling and
int PowerStateIsAC and
int tmp and 
int   timeOut1 and
int   deviceStatus and
int   devId and
int   requestRescan and
int   pollingFailureThreshold and
int break_1<==0 and
int loc_continue<==0 and
int ddd and
int  mfg, mdl, cls, des, aid, cid and skip;

WarmPollPeriod :=0;
status := 2;
polling := 0; 
PowerStateIsAC:=1;
main()
);


function main() {
   if( status>0  ) then{
       WarmPollPeriod := 3;
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
           if (1) then
		   {
				polling:= 1;
				if(1) then
				{
                   pollingFailureThreshold := 10; //pick an arbitrary but reasonable number
                   tmp:=10;
				   while( tmp>0 AND !break_1 ) then
				   {
                       if( PowerStateIsAC ) then { 
							skip
                       } 
					   else {
							skip
                       };
						if(0) then
						{
							break_1:=1
						};
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
						 if(1) then
						 {
							 polling := 0
						 };
                           if( 1 ) then
						   {
                              if( 1 ) then {
                                   requestRescan := 0;
                                   // check for something connected
                                   deviceStatus := 0;
                                   if( 0) then 
								   {
									skip
                                   } 
								   else 
								   {
									   devId:=1;
                                       if( devId )then {                                           
                                           // RawIeee1284 string includes 2 bytes of length data at beginning
										   mfg:=1;
										   mdl:=1;
                                           if( mfg AND mdl )then {
                                               requestRescan := 1
                                           }
                                       } 
									   else 
									   {
									      skip
                                       }
                                       if( requestRescan )then 
									   {
											skip
                                       } 
									   else 
									   {
                                           if(1) then 
										   {
											skip
                                           }
                                       }
                                   }
                                   if( requestRescan ) then
								   {
                                       skip
                                   }
                               } else 
									{
										skip
									}
                           } 
						   else {
							skip
                           }  
                       }					   
					   };
		               ddd := ddd
		              };
					  tmp:=tmp-1
                   }
               }
                   polling := 0
               } 
			   else 
			   {
                   polling := 0  
               }
           } else {
           }
   };
   polling := 0;
    tmp:=10000000;
    while(tmp>0)
    {
	  tmp:=tmp-1
    }
}