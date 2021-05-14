//#Safe
// ****************************************************
//
//     Making Prophecies with Decision Predicates
//
//              Byron Cook * Eric Koskinen
//                     July 2010
//
// ****************************************************

//@ ltl invariant positive: [](AP(a!= 0) ==> <>AP(r != 0));

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assume();
extern int __VERIFIER_nondet_int();

#define NTSTATUS int
#define STATUS_CANCELLED 2
#define STATUS_UNSUCCESSFUL 1
#define STATUS_SUCCESS 1
#define STATUS_TIMEOUT 3
#define SERIAL_TIMEOUTS int
#define PLIST_ENTRY int
#define PIRP int
#define KIRQL int
#define ULONG int
#define PIO_STACK_LOCATION int
#define BOOLEAN int
#define TRUE 1
#define FALSE 0

#include<stdio.h>

int a; int r;
int irql;
int csl;
NTSTATUS          status;
KIRQL             OldIrql;
SERIAL_TIMEOUTS   CurrentTimeouts;
int lock;
int k;
PLIST_ENTRY         ListElement;
PIRP                Irp;
PIO_STACK_LOCATION  IrpSp;
KIRQL               CancelIrql;
ULONG             BytesToMove;
ULONG             FirstHalf;
ULONG             SecondHalf;
KIRQL             CancelIrql;
BOOLEAN           LockHeld;
SERIAL_TIMEOUTS   CurrentTimeouts;
int tmp;


  a = r = 0; 
  status = STATUS_UNSUCCESSFUL; 
  CurrentTimeouts = 0;
  k = 6;

void KeAcquireSpinLock(int * lp, int * ip) {
  (*lp) = 1;
  (*ip) = irql;
}

void KeReleaseSpinLock(int * lp, int i) {
  (*lp) = 0;
  irql = i;
}


void IoAcquireCancelSpinLock(int * ip) {
  csl = 1;
  (*ip) = irql;
}

void IoReleaseCancelSpinLock(int ip) {
  csl = 0;
  irql = ip;
}


void main()
{

  a = 1; a = 0; 

  while (k>0) {

    ListElement = 0;
    Irp = 0;
    IrpSp = 0;
    CancelIrql = 0;

    k--;

    Irp= 0;

    IoAcquireCancelSpinLock(&CancelIrql);

    if (1) {

      IoReleaseCancelSpinLock(CancelIrql);
      continue;
    }

    IoReleaseCancelSpinLock(CancelIrql);
    r = 1;r = 0; 

      status=STATUS_UNSUCCESSFUL;
      Irp=NULL;
      LockHeld = TRUE;

      a = 1; a= 0; 

      if (1) {
		Irp=0;

		IrpSp=0;

		BytesToMove=6;
		if (1) {
		  FirstHalf=5;
		  SecondHalf=BytesToMove-FirstHalf;
		} 
		else {
		}
      }
      else
	{
	  if (1)
	    {
	      Irp = 0;
	      IoAcquireCancelSpinLock(&CancelIrql);
	      
		  if (1)
		{
		  IoReleaseCancelSpinLock(CancelIrql);
		  r = 1; r = 0; 
		  LockHeld = FALSE;
		}
	      else
		{
		  CurrentTimeouts = 0;

		  if(1)
		    {
		      IoReleaseCancelSpinLock(CancelIrql);
		      r = 1; r = 0;
		      LockHeld = FALSE;
		    }
		  else
		    {
		      IoReleaseCancelSpinLock(CancelIrql);
		      k--;
		    }
		}

	      Irp = NULL;
	    }

	}

      if (LockHeld == 1)
	{
	  r = 1; r = 0; 
	}

      if (Irp != 0) {
      }
    a=1; a=0; 
      }

  r=1; r=0; 

  tmp=10000000;
	while (tmp>0) {tmp=tmp-1;}
}
