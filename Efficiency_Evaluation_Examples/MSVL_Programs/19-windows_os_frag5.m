//#Safe
//@ ltl invariant positive: []( AP(lock == 1) ==> <>AP( lock == 0));

</
define p: lock=1;
define q: lock=0;
alw(p->som(q))
/>

frame(
lock,
CancelIrql,
irql,
csl,
CurrentWaitIrp,
NewMask,
CancelIrp,
Mask,
length,
NewTimeouts,
SerialStatus,
pBaudRate,
pLineControl,
LData,
LStop,
LParity,
keA,
keR,
DeviceObject,
Irp,
status,
OldIrql) and (

int lock and
int CancelIrql and
int irql and
int csl and
int CurrentWaitIrp<==0 and

int NewMask and
int CancelIrp and

int Mask and
int length and

int NewTimeouts and
int SerialStatus and 
int pBaudRate and 
int pLineControl and 
int LData and

int LStop and
int LParity and
//int Mask and
int keA and
int keR and
 int DeviceObject and 
 int Irp and 
 int status and
 int OldIrql and skip;
 main()
 );
 
/*
void KeAcquireSpinLock(int * lp, int * ip) {
   (*lp) = 1;
   (*ip) = irql;
}
*/
/*
void KeReleaseSpinLock(int * lp, int i) {
   (*lp) = 0;
   irql = i;
}
*/

 function IoAcquireCancelSpinLock ( int *ip )
 {
     csl:=1;
     (* ip):=irql
     
 };
 
 function IoReleaseCancelSpinLock ( int ip )
 {
     csl:=0;
     irql:=ip
     
 };
 
//void IoMarkIrpPending(int x) {}

// This could be modelled in more detail
//void RemoveReferenceAndCompleteRequest(int x,int y) {}

// This could be modelled in more detail
//void RemoveReferenceForDispatch(int x) {}


// This could be modelled in more detail
//void ProcessConnectionStateChange(int x) {}

function main()
{
  frame(main_1_2_ddd2,
  continue_1) and (
  int main_1_2_ddd2 and
  
  int continue_1<==0 
  and skip;
  
	keA := 0; 
	keR := 0;
	//DD: init lock with 0 to avoid trivial satisfaction
	lock := 0;
	
	CancelIrql := 0;//__VERIFIER_nondet_int();
	irql :=0;// __VERIFIER_nondet_int();
	csl :=0;// __VERIFIER_nondet_int();
	DeviceObject := 0;//__VERIFIER_nondet_int();
	
	Irp :=0;// __VERIFIER_nondet_int();
	status:=1;
	///OldIrql;
	status := 2;//__VERIFIER_nondet_int();
	keA := 0;
	keR := 0;
	length := 2;//__VERIFIER_nondet_int();
	
	NewTimeouts := 0;//__VERIFIER_nondet_int();
	
	SerialStatus:=0;//__VERIFIER_nondet_int();
	pBaudRate :=0;// __VERIFIER_nondet_int();
	pLineControl :=0;// __VERIFIER_nondet_int();
	
	LData := 0;
	
	LStop := 0;
	LParity := 0;
	Mask := 255;

	if(2!=status) then 
     {
         while(1)
         {
             main_1_2_ddd2:=main_1_2_ddd2
         }        
     }
     else 
     {
          skip 
     };
	
	if(1)then
	{
		//if(__VERIFIER_nondet_int()) 
		//{
		//	if (__VERIFIER_nondet_int()) 
		//	{
				(status := 4) or 
		//	}
		//}
		//else if(__VERIFIER_nondet_int())
		//{
		  ( 
		    CurrentWaitIrp:=0;
			NewMask := 0;//__VERIFIER_nondet_int();
			
			//if (__VERIFIER_nondet_int()) 
			//{
			(	status := 4 
			or
			//} 
			//else 
			//{
			(   keA := 1; 
			
			keA := 0; 
				lock := 1; 
				OldIrql := irql;
				
				NewMask := 0;//__VERIFIER_nondet_int();
				keR := 1; 
				
				keR := 0; 
				lock := 0; 
				
				irql := OldIrql;
				
				if (CurrentWaitIrp != 0) then
				{
					//RemoveReferenceAndCompleteRequest(CurrentWaitIrp, 2);
					skip
				}
			)
			 )
			//}
			) or
		//}
		//else if(__VERIFIER_nondet_int())
		//{
		(	
		    CurrentWaitIrp:=0;
			//if (__VERIFIER_nondet_int()) 
			//{
				(status := 4);
			//}
			keA := 1; 
			keA := 0; 
			lock := 1; 
			
			OldIrql := irql;
			CurrentWaitIrp:=0;//__VERIFIER_nondet_int();
			//if (__VERIFIER_nondet_int()) 
			//{
				(status:=1 
				or
			//} 
			//else 
			//{
				//IoMarkIrpPending(Irp);
				status:=7);
			//}
			keR := 1; 
			keR := 0; 
			lock := 0; 
			
			irql := OldIrql;
			if (CurrentWaitIrp != 0) then
			{
			    skip
				//RemoveReferenceAndCompleteRequest(CurrentWaitIrp, 2);
			}
		) or
		//}
		//else if(__VERIFIER_nondet_int())
		//{
		(	CancelIrp :=0; //__VERIFIER_nondet_int();
			(Mask:= 1 
			or Mask:=0); //__VERIFIER_nondet_int();
			//if (__VERIFIER_nondet_int()) 
			//{
				(status := 4 
				);
			//}
			//DD: Changed & to && to prevent LassoRanker error
			if (Mask)then 
			{
				keA := 1; 
				keA := 0; 
				lock := 1; 
				OldIrql := irql;
				
				length := 2;//__VERIFIER_nondet_int();
				if (length>0) then
				{
					length:=length-1;
					CancelIrp:=0;//__VERIFIER_nondet_int();
					IoAcquireCancelSpinLock(&CancelIrql);
					//if (__VERIFIER_nondet_int()) 
					//{
						((IoReleaseCancelSpinLock(CancelIrql);
						continue_1:=1));
					//}
					if(!continue_1)then
					{
					   IoReleaseCancelSpinLock(CancelIrql);
					   keR := 1; 
					   keR := 0; 
					   lock := 0; 
					   irql := OldIrql;
					//RemoveReferenceAndCompleteRequest(CancelIrp, 11);
					   keA := 1; 
					   keA := 0; 
					   lock := 1; 
					   OldIrql := irql
					}
               };
               CancelIrp:=0;
               //if (__VERIFIER_nondet_int())
               //{
					(CancelIrp:=0);//__VERIFIER_nondet_int();
              // }
               keR := 1; 
			   keR := 0; 
			   lock := 0; 
			   irql := OldIrql;
               if (CancelIrp != 0)then
			   {
			        skip
					//RemoveReferenceAndCompleteRequest(CancelIrp, 11);
               }
			}
		) 
		or
		//}
		//else if(__VERIFIER_nondet_int())
		//{
          // if (__VERIFIER_nondet_int()) 
		  // {
			//	status = 4;
          // }
		//}
		//else if(__VERIFIER_nondet_int())
		//{
		(	NewTimeouts := 0;//__VERIFIER_nondet_int();
			//if (__VERIFIER_nondet_int()) 
			//{
				(status := 4 
				or 
			//}
			//if (__VERIFIER_nondet_int()) 
			//{
				status := 15 
				);
			//}
			keA := 1; 
			keA := 0; 
			lock := 1; 
			OldIrql := irql;
			keR := 1; 
			keR := 0; 
			lock := 0; 
			irql := OldIrql
		) 
		or
		//}
		//else if(__VERIFIER_nondet_int())
		//{
		(	//if (__VERIFIER_nondet_int()) 
			//{
				(status := 4 
				);
			//}
			keA := 1; 
			keA := 0; 
			lock := 1; 
			
			OldIrql := irql;
			keR := 1; 
			keR := 0; 
			lock := 0; 
			irql := OldIrql
		) 
		or
		//}
		//else if(__VERIFIER_nondet_int()) 
		//{
		(	SerialStatus:=0;//__VERIFIER_nondet_int();
			//if (__VERIFIER_nondet_int()) 
			//{
				(status := 4 
				);
			//}
			keA := 1; 
			keA := 0; 
			
			lock := 1; 
			
			OldIrql := irql;
			keR := 1; 
			keR := 0; 
			lock := 0; 
			irql := OldIrql
		) 
		or
		//}
		//else if(__VERIFIER_nondet_int())
		//{
		 ( keA := 1; 
		 keA := 0; 
		   lock := 1; 
		   
		   OldIrql := irql;
		   /*if (__VERIFIER_nondet_int()) 
		   {
		   } 
		   else 
		   {
				if (__VERIFIER_nondet_int()) 
				{
				}
		   }*/
		   keR := 1; 
		   keR := 0; 
		   
		   lock := 0; 
		   irql := OldIrql
		   //ProcessConnectionStateChange(DeviceObject);
		  ) or
		//}
		//else if(__VERIFIER_nondet_int())
		//{
		//	if (__VERIFIER_nondet_int()) 
		//	{
		//		status = 4;
		//	}
		//}
		//else if(__VERIFIER_nondet_int())
		//{
		(	//if (__VERIFIER_nondet_int()) 
			//{
				(status := 4) 
				or
			//} 
			//else 
			//{
				(keA := 1; 
				keA := 0; 
				lock := 1; 
				OldIrql := irql;
				
				keR := 1; 
				keR := 0; 
				lock := 0; 
				irql := OldIrql)
			//}
		) 
		or 
		//}
		//else if(__VERIFIER_nondet_int()) 
		//{
		(   pBaudRate := 0;//__VERIFIER_nondet_int();
			//if (__VERIFIER_nondet_int()) 
			//{
				(status := 4) 
				or
			//} 
			//else 
			//{
				(keA := 1; 
				keA := 0; 
				lock := 1; 
				OldIrql := irql;
				
				keR := 1; 
				keR := 0; 
				lock := 0; 
				irql := OldIrql)
			//}
		) 
		or
		//}
		//else if(__VERIFIER_nondet_int())
		//{
		(	pLineControl := 0;//__VERIFIER_nondet_int();
			LData := 0;
			LStop := 0;
			LParity := 0;
			Mask := 255;//0xff;
			//if (__VERIFIER_nondet_int()) 
			//{
				(status := 4 
				
				);
			//}
			if(1) 
			then
			{ 
				//if(__VERIFIER_nondet_int()) /* case 5:*/ 
				//{
					(LData := 27;
					
					Mask := 31)
					or
				//}
				//else if(__VERIFIER_nondet_int()) /* case 6:*/ 
				//{
					(LData := 24;
					
					Mask := 63) 
					or
				//}
				//else if(__VERIFIER_nondet_int()) /* case 7:*/ 
				//{
					(LData := 25;
					
					Mask := 127) 
					or
				//}
				//else if(__VERIFIER_nondet_int()) /* case 8:*/ 
				//{
                   (LData := 26) 
				   or
				//}
				//else /*default:*/ 
				//{
                   (status := 15)
				//}
			};
			if (status != 2)
			then
			{
			   skip
			};
			if(1)
			then 
			{
				
				//{
					status := 15
				//}
			};
			if (status != 2)
			then
			{
               skip
			};
			if (1)
			then
			{
				//if(__VERIFIER_nondet_int()) 
				//{
					LStop := 32 or
				//}
				//else if(__VERIFIER_nondet_int()) 
				//{
					(if (LData != 27)
					then
					{
						status := 15
					};
					LStop := 37
					) 
					or
				//}
				//else if(__VERIFIER_nondet_int()) 
				//{
					(if (LData = 27) then
					{
						status := 15
					};
					LStop := 33
					)
					or
				//}
				//else 
				//{
					status := 15
				//}
			};
			if (status != 2)then
			{
                skip
			};
			keA := 1; 
			keA := 0; 
			
			lock := 1; 
			OldIrql := irql;
			
			keR := 1; 
			keR := 0; 
			lock := 0; 
			irql := OldIrql
		) or
		//}
		//else if(__VERIFIER_nondet_int())
		//{
		(	//if (__VERIFIER_nondet_int())  
			//{
				(status := 4 
				);
			//}
			keA := 1; 
		    keA := 0; 
			
			lock := 1; 
		 OldIrql := irql;
		 
			keR := 1; 
			keR := 0; 
			
			lock := 0; 
			irql := OldIrql
			
		) or
		//}
		//else if(__VERIFIER_nondet_int()) 
		//{
		//}
		//else 
		//{
			status:=41
		//}
	};
	if (status != 7)then
	{
		if (Irp != 0)then
		{
			skip//RemoveReferenceAndCompleteRequest(Irp, status);
		}
	}
	//RemoveReferenceForDispatch(DeviceObject);
	///while (1) 
	//{ int rrr; 
	//rrr = rrr; }
)
}