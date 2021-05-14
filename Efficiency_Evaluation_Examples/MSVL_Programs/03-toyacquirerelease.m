//#Safe
//@ ltl invariant positive: [](AP(a != 0) ==> <> AP(r!= 0));
</
 define p: a!=0;
 define q: r!=0;
 
 alw(p->som(q))
/>

frame(a,r,n,tmp) and
(
  int a<==0 and int r<==0 and int n and int tmp and skip;  
  tmp:=10;
  while(tmp>0) 
  {
    a := 1;
    a := 0;
    n := 1;
    while(n>0) 
	{
      n:=n-1
    };
    r := 1;
    r := 0;
	tmp:=tmp-1
  };
  tmp:=10000000;
  while(tmp>0) 
  {
	tmp:=tmp-1
  }
)