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
phi_nSUC_ret,phi_io_compl,
pc,
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

int keA and int keR and int ioA and int ioR and

int phi_nSUC_ret and int phi_io_compl and
 unsigned int pc and

 keA <== 0 and
  keR <== 0 and
  ioA<==0  and
  ioR<==0 and 
  phi_nSUC_ret <== 0 and
  phi_io_compl <== 0 and
  skip;
  main()
);

function KeAcquireSpinLock(int * lp, int * ip) { 
   keA := 1; keA := 0;
   (*lp) := 1;
   (*ip) := irql
};

function KeReleaseSpinLock(int * lp, int i) { 
  keR := 1; keR := 0;
   (*lp) := 0;
   irql := i
};

function IoAcquireCancelSpinLock(int * ip) 
{ ioA := 1; ioA := 0;
   csl := 1;
   (*ip) := irql
};

function IoReleaseCancelSpinLock(int ip) 
{ ioR := 1; ioR := 0;
   csl := 0;
   irql := ip
};

//int t1394_IsochCleanup(int a) { }
//int ExAllocatePool(int a, int b) { }
//int t1394Diag_PnpStopDevice(int a,int b) { }
//int t1394_SubmitIrpSynch(int a, int b) { }
//int IoFreeIrp(int a) { }
//int IoSetDeviceInterfaceState() { }
//int RtlZeroMemory(int a, int b) { }
//int KeCancelTimer() { }
//int IoAllocateIrp(int a, int b) { }
//int IoFreeMdl() { }
//int IoSetCancelRoutine(int a) { }
//int ExFreePool0() { }
//int ExFreePool1(int a) { }
//int ExFreePool2(int a, int b) { }
function IoCompleteRequest(int a) {phi_io_compl := 1 };

function main() {
 /*  if (__VERIFIER_nondet_int()) {

       // haven't stopped yet, lets do so
       ntStatus = t1394Diag_PnpStopDevice(DeviceObject, Irp);
   }*/

   (ntStatus := 2 or ntStatus := 3);//IoSetDeviceInterfaceState();

    
   // lets free up any crom data structs we've allocated...
   KeAcquireSpinLock(&lock3, &Irql);

   k1 :=5;// __VERIFIER_nondet_int();
   while (k1>0) {

       CromData :=1;// __VERIFIER_nondet_int();

       // get struct off list
       k1:=k1-1;

       // need to free up everything associated with this allocate...
       if (CromData)then
       {
           /*if (__VERIFIER_nondet_int())
               ExFreePool0();

           if (__VERIFIER_nondet_int())
               IoFreeMdl();*/

           // we already checked CromData
           //ExFreePool1(CromData);
		   skip
       }
   };

   KeReleaseSpinLock(&lock3, Irql);

   KeAcquireSpinLock(&lock1, &Irql);

   k2 := 5;//__VERIFIER_nondet_int();
   while (k2>0) {

     AsyncAddressData := 0;//__VERIFIER_nondet_int();

       // get struct off list
       AsyncAddressData :=1;// __VERIFIER_nondet_int();
       k2:=k2-1

       // need to free up everything associated with this allocate...
       /*if (__VERIFIER_nondet_int())
           IoFreeMdl();

       if (__VERIFIER_nondet_int())
           ExFreePool0();

       if (__VERIFIER_nondet_int())
           ExFreePool0();

       if (AsyncAddressData)
           ExFreePool0();*/
   };

   KeReleaseSpinLock(&lock1, Irql);

   // free up any attached isoch buffers
   if (!break_1) then 
   {

       KeAcquireSpinLock(&lock4, &Irql);

       (k3 := 1 or k3:=0);//__VERIFIER_nondet_int();   //可能是这行有问题。应该放到while的前边wangmeng
       if (k3>0) then
	   {

	       IsochDetachData := 0;//__VERIFIER_nondet_int();
	       i :=1;// __VERIFIER_nondet_int();

           IsochDetachData :=1;// __VERIFIER_nondet_int();
           k3:=k3-1;


           //KeCancelTimer();
           keR := 1; keR := 0; KeReleaseSpinLock(&lock4, Irql)


           //t1394_IsochCleanup(IsochDetachData);
       }
       else 
	   {

           KeReleaseSpinLock(&lock4, Irql);
           break_1:=1
       }
   };

   // remove any isoch resource data

   k4 :=5; //__VERIFIER_nondet_int();
   if (!break_2) then {

       KeAcquireSpinLock(&lock5, &Irql);
       if (k4>0)then {

           (IsochResourceData := 1 or IsochResourceData := 0);//__VERIFIER_nondet_int();
           k4:=k4-1;

           KeReleaseSpinLock(&lock5, Irql);


           if (IsochResourceData) then{

	       pIrb := 0;//__VERIFIER_nondet_int();
               ResourceIrp :=0;// __VERIFIER_nondet_int();
               StackSize := 0;//__VERIFIER_nondet_int();
               (ResourceIrp :=0 or ResourceIrp:=1); //IoAllocateIrp(StackSize, 0);

               if (ResourceIrp=0) then{
			   skip

               }
               else {
                   
				   (pIrb:=1 or pIrb :=0); //ExAllocatePool(1, sizeof(int));

                   if (!pIrb)then
				   {
                       skip
					   //IoFreeIrp(ResourceIrp);
                   }
                   else {

                      // RtlZeroMemory (pIrb, sizeof (int));

                       // ntStatus = t1394_SubmitIrpSynch(ResourceIrp, pIrb);
                       (ntStatus:=2 or ntStatus:=3)

                       //ExFreePool1(pIrb);
                       //IoFreeIrp(ResourceIrp);
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

   k5 :=5;// __VERIFIER_nondet_int();
   while (k5>0) {

       prevCancel := 0;

       // get the irp off of the list
       BusResetIrp := 0;//__VERIFIER_nondet_int();
       k5:=k5-1;


       // make this irp non-cancelable...
       prevCancel := 1;//IoSetCancelRoutine(NULL);


       // and complete it...
       IoCompleteRequest(2)

       //ExFreePool1(BusResetIrp);
   };

  KeReleaseSpinLock(&lock6, Irql);

  if(ntStatus != 2) then{ 
     phi_nSUC_ret := 1
   }
}
