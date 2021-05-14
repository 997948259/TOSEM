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
tmp
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
int continue_1<==0 and skip;
int tmp and skip;
a :=0; r := 0;
  status := 1;
  CurrentTimeouts := 0; 
  k := 6 ;

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

function main()
{

  a := 1; a := 0; 
  while (k>0) {

    ListElement := 0;
    Irp :=0; 
    IrpSp :=0;
    CancelIrql := 0;

    k:=k-1;

    Irp:= 0;

    IoAcquireCancelSpinLock(&CancelIrql);

    if (1) then
	{
      IoReleaseCancelSpinLock(CancelIrql);
      continue_1:=1  
    };
	
	if(!continue_1) then
	{
		IoReleaseCancelSpinLock(CancelIrql);
		r := 1;r := 0; 

      status:=1;
      Irp:=0;
      LockHeld := 1;

      a := 1; a:= 0; 

      if (1) then{
	     Irp:=0;

	     IrpSp:=0;

	     BytesToMove:=6;
			if (1) then {
				FirstHalf:=5;
				SecondHalf:=BytesToMove-FirstHalf
				}
			 else {
				skip
	         }	 
      }
      else 
	 {
	   if (1) then
	    {
	       
		 Irp :=0;
	       IoAcquireCancelSpinLock(&CancelIrql);
	       if (1) then
		   {
				 IoReleaseCancelSpinLock(CancelIrql);
		          r := 1; r := 0;
		          LockHeld := 0
		   }
	       else
		   {
		       CurrentTimeouts := 0;

		        if(1) then
		        {
		            IoReleaseCancelSpinLock(CancelIrql);
		             r := 1; r := 0; 
		             LockHeld := 0
		        }
		       else
		        {
		           IoReleaseCancelSpinLock(CancelIrql);
		           k:=k-1
		        }
		   };
	      Irp := 0
	    }
	  };

      if (LockHeld = 1)then
	  {
	     r := 1; r := 0 
	  };

      if (Irp != 0)then {
        skip
      };
      a:=1; a:=0 
	}
  };

  r:=1; r:=0;
  	tmp:=10000000;
    while(tmp>0)
    {
	  tmp:=tmp-1
    }
}
