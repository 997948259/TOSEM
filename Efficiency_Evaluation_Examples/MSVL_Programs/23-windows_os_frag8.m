//#Safe
//@ ltl invariant positive: <>[]AP(polling == 1);
</
  define p: polling=1;
  som(alw(p))
/>

frame(WarmPollPeriod,
status,
polling,
PowerStateIsAC,
Count,
timeOut1,

deviceStatus,
devId,
requestRescan,
tmp,
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
int tmp and
int ddd and
int  mfg and 
int mdl and
int cls and 
int des and 
int aid and 
int cid and

int break_1<==0 and skip;
WarmPollPeriod :=0;
status := 2;
polling := 0; 
PowerStateIsAC := 0;
Count := 10;

main()

);
  
function main() {
   if( status>0  ) then{
       WarmPollPeriod := 3;
       if( WarmPollPeriod < 5 ) then
	   {
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
              if(1) then 
			  {        
                   Count :=6;
                   while(Count>0 AND !break_1)
				   {
                       if( PowerStateIsAC ) then
					   {
							skip
                       } 
					   else 
					   {
							skip
                       };
                       status := -1;
                       if(0) then
					   {
                           break_1:=1
                       };
					   if(!break_1)then
					   {
						   if( !PowerStateIsAC ) then 
						   {
								skip
						   };
						   if(  status= -1 ) then
						   {
							   if( 1 ) then
							   {
								   // try to acquire port
									if( 1 ) then
									{  
										requestRescan := 0;
									   // check for something connected
									   deviceStatus :=0;
									   if( 1) then
									   {
											skip
									   } 
									   else 
									   {
										   // we might have something connected
										   // try a device ID to confirm
											devId :=1;
										   if( devId )then
										   {                                          
											  // RawIeee1284 string includes 2 bytes of length data at beginning
											   
											   if( mfg AND mdl ) then
											   {
												   requestRescan := 1
											   }
										   } 
										   else 
										   {
												skip
										   };
										   if( requestRescan ) then 
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
									   };
									  
									   if( requestRescan ) then 
									   {
											skip
									   }
									   
									} 
									else 
									{
										skip
								   }
							   } 
							   else 
							   {
									skip
							   }
						   };
					   
		              ddd := ddd;
					  Count:=Count-1
					  }
                   }
               }
				else 
				{
                   skip
               }
           } 
		   else 
		   {
				skip
           }
   };
   // Failsafe
   polling := 1;
   tmp:=10000000;
    while(tmp>0)
    {
	  tmp:=tmp-1
    }
}