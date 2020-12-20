//#Safe
//@ ltl invariant positive: <>[]AP( Stored == 0 );
</
  define p: Stored=0;
  som(alw(p))
/>

frame(Stored,loop,break_1)
and
(
int Stored and
int loop and
int break_1<==0 and 
skip;
main()
);

function init() { Stored := 0 };
//void callback() {}
//void IoQueueWorkItem() {}
function main() 
{
    init();
    (loop:=1 or loop:=0);
    if(loop AND !break_1)then {
          /* if (__VERIFIER_nondet_int()) {
               //
               // We are safely at PASSIVE_LEVEL, call callback directly
               // to perform
               // this operation immediately.
               //
               //callback ();
           } else {*/
	       (skip or
		   //IoQueueWorkItem ();
               (Stored := 1;
               break_1:=1));
           //}
		   if(!break_1)then
		   {
		    (loop:=1 or loop:=0)
		   }
    };
    // Lower Irql and process
    if (Stored=1)then {
        //callback ();
        Stored := 0
    }
}