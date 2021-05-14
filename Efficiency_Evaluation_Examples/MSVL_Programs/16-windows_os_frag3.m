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
int tmp and
int break_1<==0 and 
skip;
main()
);

function init() { Stored := 0 };
function main() 
{
    init();
	tmp:=10;
    while(tmp>0 AND !break_1)then {
           if (1) then {
               skip
           } else {
               Stored := 1;
               break_1:=1
           };
		   if(!break_1)then
		   {
				tmp:=tmp-1 
		   }
    };
    // Lower Irql and process
    if (Stored=1)then {
        Stored := 0
    };
	 tmp:=10000000;
    while(tmp>0)
    {
	  tmp:=tmp-1
    }
}