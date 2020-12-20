//#Safe
// Based on the small program from section 2 of the paper "Cook, Koskinen: Making Prophecies with Decision Predicates"
// manually translated by DD

//@ ltl invariant positive: <>[]AP(x==1);
</
  define p: x=1;
  som(alw(p))
/>
frame(x,y) and
( 
	int x<==1 and int y<==0 and skip; 
	if(!y) then
	{
		y:=1 or y:=0
	};

	x:=0;
	x:=1
)

