//#UnSafe
//@ ltl invariant positive: <>AP(phi_io_compl == 1) || <>AP(phi_nSUC_ret == 1);
</
 define p: phi_io_compl=1;
 define q: phi_nSUC_ret=1;
 som(p) or som(q)
/>
frame(
 lock1,
 lock2,
 lock3,
 lock4,
 lock5,
 lock6,
 CancelIrql,
 irql,
 csl,
   DeviceObject,
             Irp,
            ntStatus,
deviceExtension,
Irql,
k1,
k2,
k3,
k4,
k5,
tmp,
CromData,
AsyncAddressData,
IsochResourceData,
IsochDetachData,
i,
pIrb,
ResourceIrp,
StackSize,
BusResetIrp,
prevCancel,
keA,keR,ioA,ioR,
phi_nSUC_ret,
phi_io_compl,
break_1,
break_2
)
and
(
int lock1 and
int lock2 and
int lock3 and
int lock4 and
int lock5 and
int lock6 and
int CancelIrql and
int irql and
int csl and
int   DeviceObject and
int             Irp and
int            ntStatus and
int   deviceExtension and
int               Irql and
int k1 and
int k2 and
int k3 and
int k4 and
int k5 and
int tmp and
int      CromData and
int     AsyncAddressData and
int    IsochResourceData and
int      IsochDetachData and
int                   i and
int                pIrb and
int                ResourceIrp and
int               StackSize and
int  BusResetIrp and
int  prevCancel and

int break_1<==0 and
int break_2<==0 and

int keA and 
int keR and 
int ioA and 
int ioR and
int phi_nSUC_ret and
int phi_io_compl and

 keA <== 0 and
  keR <== 0 and 
  ioA <== 0 and
  ioR <== 0 and 
  phi_nSUC_ret <== 0 and
  phi_io_compl <== 0 and 
  skip;
  main()
);

function KeAcquireSpinLock(int * lp, int * ip) { 
   keA := 1; 
   keA := 0;
   (*lp) := 1;
   (*ip) := irql
};

function KeReleaseSpinLock(int * lp, int i) { 
  keR := 1;
  keR := 0;
   (*lp) := 0;
   irql := i
};

function IoAcquireCancelSpinLock(int * ip) 
{ 
	ioA := 1; 
	ioA := 0;
   csl := 1;
   (*ip) := irql
};

function IoReleaseCancelSpinLock(int ip) 
{ 
	ioR := 1; 
	ioR := 0;
   csl := 0;
   irql := ip
};

function IoCompleteRequest(int a) 
{ 
	phi_io_compl := 1
};

function main() {
   if (1) then {
       ntStatus := 1
   };

   ntStatus := 2;
    
   // lets free up any crom data structs we've allocated...
   KeAcquireSpinLock(&lock3, &Irql);

   k1 :=5;
   while (k1>0) {

       CromData :=1;

       // get struct off list
       k1:=k1-1;

       // need to free up everything associated with this allocate... 
       if (CromData)then
       {
           if (1) then
		   {
				skip
		   };

           if (1) then
		   {
				skip
		   }
       }
   };

   KeReleaseSpinLock(&lock3, Irql);

   KeAcquireSpinLock(&lock1, &Irql);

   k2 := 5;
   while (k2>0) {

     AsyncAddressData := 0;

       // get struct off list
	   
       AsyncAddressData :=1;
       k2:=k2-1;

       // need to free up everything associated with this allocate...
	   
       if (1) then
	   {
			skip
	   };

	   if (1) then
	   {
			skip
	   };
	   
	   if (1) then
	   {
			skip
	   };

	   if (1) then
	   {
			skip
	   }
   };

   KeReleaseSpinLock(&lock1, Irql);

   // free up any attached isoch buffers
   while (!break_1) 
   {
	   KeAcquireSpinLock(&lock4, &Irql);

       k3 := 1;
       if (k3>0) then
	   {

	       IsochDetachData := 0;
	       i :=1;

           IsochDetachData :=1;
           k3:=k3-1;

		   KeReleaseSpinLock(&lock4, Irql)

       }
       else 
	   {
		   KeReleaseSpinLock(&lock4, Irql);
           break_1:=1
       }
   };

   // remove any isoch resource data

   k4 :=5;
   while (!break_2) {

	   KeAcquireSpinLock(&lock5, &Irql);
       if (k4>0)then {

           IsochResourceData := 1;
           k4:=k4-1;

		   KeReleaseSpinLock(&lock5, Irql);

           if (IsochResourceData) then{

				pIrb := 0;
               ResourceIrp :=0;
               StackSize := 0;
               ResourceIrp :=0;

               if (ResourceIrp=0) then{
					skip
               }
               else
			   {
				   pIrb :=0;
                   if (!pIrb)then
				   {
                       skip
                   }
                   else 
				   {
                       ntStatus:=2 
                   }
               }
           }
       }
       else {
		   KeReleaseSpinLock(&lock5, Irql);
           break_2:=1
       }
   };

   // get rid of any pending bus reset notify requests
   KeAcquireSpinLock(&lock6, &Irql);
   k5 :=5;
   while (k5>0) {
       prevCancel := 0;
       // get the irp off of the list
       BusResetIrp := 0;
       k5:=k5-1;

       // make this irp non-cancelable...
       prevCancel := 1;
	   IoCompleteRequest(2)
   };

   KeReleaseSpinLock(&lock6, Irql);
   if(ntStatus != 2) { 
     phi_nSUC_ret = 1;
   }

   tmp:=10000000;
    while(tmp>0)
    {
	  tmp:=tmp-1
    }
}
