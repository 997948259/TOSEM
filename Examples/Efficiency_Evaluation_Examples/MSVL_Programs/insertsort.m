</
define p: i>=0;
define q: j>=0;
alw(p and q)
/>
/*</
define p1: a_0<a_1;
define p2: a_9<a_10;
som(alw(p1 and p2))
/>*/

frame(cnt1,cnt2,i,j,temp,tmp,a_0,a_1,a_9,a_10,a) and
(
	int cnt1 and skip;
	int cnt2 and skip;
	int i,j,temp and skip;
	int tmp;
	int a_0<==0 and skip;
	int a_1<==0 and skip;
	int a_9<==0 and skip;
	int a_10<==0 and skip;
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
	a_0:=a[0];
    a_1:=a[1];
    a_9:=a[9];
    a_10:=a[10];
	tmp:=10000000;
	while(tmp>0)
	{
	  tmp:=tmp-1
	}
)