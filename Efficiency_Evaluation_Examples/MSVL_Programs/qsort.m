/*</
define p: count <= 60;
alw(p)
/>*/

</
define p: array[0].qstring[0] >= array[1].qstring[0];
som(alw(p))
/>

frame(array,fp,i,count) and 
(
	struct myStringStruct {
	char qstring[128]
	};
	function compare(void* elem1, void* elem2,int RValue)
	{
		int result<==1 and skip;
		myStringStruct * e1 <== elem1 and skip;
		myStringStruct * e2 <== elem2 and skip;
		//output(e1->qstring) and skip;
		//output(e2->qstring) and skip;

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
	FILE *fp and skip;
	int i and skip;
	int count<==0 and skip;
	fp<== fopen("F:\\input_small.dat","r") and skip;
	while( (fscanf(fp, "%s", &array[count].qstring) = 1) AND (count < 60)) {
	 count:=count+1
    };
	output("\nSorting ") and skip;
	output(count) and skip;
	output(" elements.\n\n") and skip;

	qsort(array,count,128,compare) and skip;
	i<==0 and skip;
	while(i<count)
	{
		output(array[i].qstring) and skip;
		output("\n") and skip;
		i:=i+1
	}
)