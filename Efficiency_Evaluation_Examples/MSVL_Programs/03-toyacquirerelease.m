//#Safe
//@ ltl invariant positive: [](AP(a != 0) ==> <> AP(r!= 0));
</
 define p: a!=0;
 define q: r!=0;
 
 alw(p->som(q))
/>

frame(a,r,n,x,tmp) and
(
  int a<==0 and int x<==0 and 
  int r<==0 and int tmp<==1 and
  int n and skip;  
  if(tmp) then 
  {
    a <== 1 and skip;
    a <== 0 and skip;
    n <== 0 and skip;
    while(n>0) 
	{
      n:=n-1
    };
    r <== 1 and skip;
    r <== 0 and skip;
	(tmp:=1 or tmp:=0)
  }
)