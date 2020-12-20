//#Safe
//@ ltl invariant positive: [](AP(a!= 0) ==> <>AP(r != 0));

</
  define p: a!=0;
  define q: r!=0;
  alw(p->som(q))
/>

frame(
a,r,
irql,
csl,
status,
OldIrql,
lock,
k,
ListElement,
Irp,
IrpSp,
BytesToMove,
FirstHalf,
SecondHalf,
CancelIrql,
LockHeld,
CurrentTimeouts,
ddd,
continue_1,
loop
)
and
(
int a and int r and 
int irql and 
int csl and 
int          status and 
int             OldIrql and 
//int   CurrentTimeouts and 
int lock and 
int k and 
int         ListElement and 
int                Irp and 
int  IrpSp and 
//int               CancelIrql and 
int             BytesToMove and 
int             FirstHalf and 
int             SecondHalf and 
int             CancelIrql and 
int           LockHeld and 
int   CurrentTimeouts and 
int ddd and 
int continue_1<==0 and
int loop<==1 and 
a <==0 and r <== 0 and
  status <== 1 and
  CurrentTimeouts <== 0//__VERIFIER_nondet_int() 
  and
  k <== 6 //__VERIFIER_nondet_int() //该值可以改wangmeng
  and skip;

  main()
);



function KeAcquireSpinLock(int * lp, int * ip) {
  (*lp) := 1;
  (*ip) := irql
};

function KeReleaseSpinLock(int * lp, int i) {
  (*lp) := 0;
  irql := i
};


function IoAcquireCancelSpinLock(int * ip) {
  csl := 1;
  (*ip) := irql
};

function IoReleaseCancelSpinLock(int ip) {
  csl := 0;
  irql := ip
};

//int IoGetCurrentIrpStackLocation(int a) {}

//void RemoveReferenceAndCompleteRequest(int a, int b) {}

function main()
{

  a := 1; a := 0; // KeAcquireSpinLock( &lock, &OldIrql);

  loop:=1;
  if (loop AND k>0) then{

    ListElement := 0;//__VERIFIER_nondet_int();
    Irp :=0; //__VERIFIER_nondet_int();
    IrpSp :=0;// __VERIFIER_nondet_int();
    CancelIrql := 0;//__VERIFIER_nondet_int();

    k:=k-1;

    Irp:= 0;//__VERIFIER_nondet_int();

    IoAcquireCancelSpinLock(&CancelIrql);

    //if (__VERIFIER_nondet_int()) {
      (IoReleaseCancelSpinLock(CancelIrql);

      continue_1:=1);
	  
    //}
	
	if(!continue_1) then
	{

    // IoSetCancelRoutine(Irp, NULL);
    IoReleaseCancelSpinLock(CancelIrql);
    r := 1;r := 0; // KeReleaseSpinLock(&lock, OldIrql);

    //CALL TO TryToSatisfyRead( deviceExtension);
   // {
      status:=1;
      Irp:=0;//NULL;
      LockHeld := 1;

      a := 1; a:= 0; //KeAcquireSpinLock(&lock,&OldIrql);

     // if (__VERIFIER_nondet_int() && __VERIFIER_nondet_int()) 
	 // then{
	    //
	    //  there is an IRP and there are characters waiting
	    //
	   ((  Irp:=0;//__VERIFIER_nondet_int();

	     IrpSp:=0;//IoGetCurrentIrpStackLocation(Irp);

	     BytesToMove:=6;//__VERIFIER_nondet_int();

	   // if (__VERIFIER_nondet_int()) {
	        ( FirstHalf:=5;//__VERIFIER_nondet_int();

	         SecondHalf:=BytesToMove-FirstHalf)
			 


	        // } else {
	        // }
			 )
      //}
      or //else
	 //{
	  ( //if (__VERIFIER_nondet_int())
	    //{
	     (  Irp :=0;// __VERIFIER_nondet_int();

	       IoAcquireCancelSpinLock(&CancelIrql);
	       //if (__VERIFIER_nondet_int())
		   //{
		     ( (    IoReleaseCancelSpinLock(CancelIrql);

		          r := 1; r := 0; // KeReleaseSpinLock( &lock, OldIrql);

		         // RemoveReferenceAndCompleteRequest(Irp,2);
		          LockHeld := 0)
		  // }
		   or 
	       //else
		  // {
		    (    CurrentTimeouts := 0;//__VERIFIER_nondet_int();

		       // if(__VERIFIER_nondet_int())
		        //{
		           (( IoReleaseCancelSpinLock(CancelIrql);

		             r := 1; r := 0; // KeReleaseSpinLock( &lock, OldIrql);

		             //RemoveReferenceAndCompleteRequest(Irp, 3);

		             LockHeld := 0)
		       // }
			     or
		       // else
		       // {
		           (IoReleaseCancelSpinLock(CancelIrql);
		           k:=k-1))
		       // }
				));
		   //}

	      Irp := 0) or skip
	    //}
       ));
	  //};

      if (LockHeld = 1)then
	  {
	     r := 1; r := 0 //KeReleaseSpinLock( &lock, OldIrql);
	  };

      if (Irp != 0)then {
	//
	//  if irp isn't null, then we handled one
	//
	//RemoveReferenceAndCompleteRequest(Irp, 1);
        skip
      };



     // }
     //-------------------------------------------------------------
      a:=1; a:=0 // KeAcquireSpinLock(&lock, &OldIrql)
	};
	(loop:=1 or loop:=0)
  };

  r:=1; r:=0
}
