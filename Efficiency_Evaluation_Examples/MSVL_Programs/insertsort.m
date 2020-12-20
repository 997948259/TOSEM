</
define p: i>=0;
define q: j>=0;
alw(p and q)
/>
/*</
define p1: a[0]<a[1];
define p2: a[9]<a[10];
som(alw(p1 and p2))
/>*/

frame(cnt1,cnt2,i,j,temp,a) and
(
	int i,j,temp and skip;
	int cnt1 and skip;
	int cnt2 and skip;
	int a[11] and skip;
	a[0]<==0 and skip;
	a[1]<== 11 and skip; 
	a[2]<==10 and skip;
	a[3]<==9 and skip; 
	a[4]<==8 and skip; 
	a[5]<==7 and skip; 
	a[6]<==6 and skip; 
	a[7]<==5 and skip;
	a[8] <==4 and skip; 
	a[9]<==3 and skip; 
	a[10]<==2 and skip;
	i:=2;
	while(i<=10)
	{
		cnt1:=cnt1+1;
		j:=i;
		cnt2:=0;
		while(a[j] < a[j-1])
		{
			cnt2:=cnt2+1;
			temp := a[j];
			a[j] := a[j-1];
			a[j-1] := temp;
			j:=j-1
		};
		i:=i+1
	};
	output("a[10]:") and skip;
	output(a[10]) and skip;
	output("a[9]:") and skip;
	output(a[9]) and skip
)