//#Safe
// Based on the small program from section 2 of the paper "Cook, Koskinen: Making Prophecies with Decision Predicates"
// manually translated by DD

//@ ltl invariant positive: <>[]AP(x==1);
</
  define p: x=1;
  som(alw(p))
/>
frame(x,tmp) and
( 
	int x<==1 and skip;
	int tmp<==10 and skip; 
	while(tmp>0) then
	{
		tmp:=tmp-1
	};
	x:=0;
	x:=1;
	tmp:=10000000;
	while(tmp>0)
	{
		tmp:=tmp-1
	}
)

