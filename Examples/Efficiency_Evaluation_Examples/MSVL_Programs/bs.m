/*</
define p: low<=up;
alw(p)
/>*/

</
define p1: index>=5;
define p2: index<=18;
define p3: fvalue>=200;
define p4: fvalue<=1500;
alw((p1 and p2)-> som(p3 and p4))
/>
frame(data,cnt1,low,up,fvalue,index,mid,tmp) and
(
	struct DATA {
	int key and 
	int value
	};
	int cnt1 and skip;
	DATA data[15]<== [ [1, 100],
		[5,200],
	    [6, 300],
	    [7, 700],
	    [8, 900],
	    [9, 250],
	    [10, 400],
	    [11, 600],
	    [12, 800],
	    [13, 1500],
	    [14, 1200],
	    [15, 110],
	    [16, 140],
	    [17, 133],
	    [18, 10]] and skip;
	int index and skip;
	int fvalue and skip;
	int mid and skip;
	int up and skip;
	int low and skip;
	int tmp and skip;
	
	function main_1()
	{
		index:=8;
		binary_search(index)
	};
	function binary_search(int x,int RValue)
	{
		int xy<==0 and skip;
		low<==0 and skip;
		up<==14 and skip;
		fvalue<==-1 and skip;
		while(low<=up)
		{
			mid:=(low + up) >> 1;
			if ( data[mid].key = x ) then
			{ 
				up := low - 1;
				fvalue := data[mid].value
				output("FOUND!!\n") and skip
			}
			else
			{
				if(data[mid].key > x )then
				{
					up:=mid-1
					output("MID-1\n") and skip
				}
				else
				{
					low := mid + 1
					output("MID+1\n") and skip
				}
			};
			cnt1:=cnt1+1
		};
		output("Loop Count : ") and skip;
		output(cnt1) and skip;
		output("\n") and skip;
		tmp:=10000000;
		while(tmp>0)
		{
		  tmp:=tmp-1
		};
		RValue:=fvalue
	};
	main_1()
)