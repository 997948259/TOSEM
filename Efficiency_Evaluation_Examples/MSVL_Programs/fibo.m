/*</
define p: i<=n+1;
alw(p)
/>*/
</
define p: temp=Fnew;
define q: Fold=temp;
alw(p->som(q))
/>
frame(i,Fnew,Fold,temp,ans,n) and
(
	int i, Fnew, Fold, temp, ans and skip;
	int n<==30 and skip;
	Fnew<==1 and skip;
	Fold<==0 and skip;
	i<==2 and skip;
	while(i<=n)
	{
		temp:=Fnew;
		Fnew:=Fnew+Fold;
		Fold:=temp;
		i:=i+1
	};
	ans:=Fnew;
	output(ans) and skip;
	output("\n") and skip
)