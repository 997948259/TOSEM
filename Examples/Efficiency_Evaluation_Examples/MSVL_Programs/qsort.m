/*</
define p: count <= 5;
alw(p)
/>*/

</
define p: array[0].qstring[0] >= array[1].qstring[0];
som(alw(p))
/>

frame(array,i,count,tmp) and 
(
	struct myStringStruct {
	char qstring[128]
	};
	function compare(void* elem1, void* elem2,int RValue)
	{
		int result<==1 and skip;
		myStringStruct * e1 <== elem1 and skip;
		myStringStruct * e2 <== elem2 and skip;

		result := strcmp(e1->qstring, e2->qstring);
		if(result < 0)then
		{
			RValue:=1
		}
		else
		{
			if(result = 0) then
			{
				RValue:=0
			}
			else
			{
				RValue:=-1
			}
		}		
	};
	myStringStruct array[60] and skip;
	int i and skip;
	int count<==5 and skip;
	int tmp and skip;
	
	strcpy(array[0].qstring, "1") and skip;
	strcpy(array[1].qstring, "2") and skip;
	strcpy(array[2].qstring, "3") and skip;
	strcpy(array[3].qstring, "4") and skip;
	strcpy(array[4].qstring, "5") and skip;
	
	output("\nSorting ") and skip;
	output(count) and skip;
	output(" elements.\n\n") and skip;

	qsort(array,5,128,compare) and skip;
	i<==0 and skip;
	while(i<count)
	{
		output(array[i].qstring) and skip;
		output("\n") and skip;
		i:=i+1
	};
	tmp:=10000000;
	while(tmp>0)
	{
	  tmp:=tmp-1
	}
)