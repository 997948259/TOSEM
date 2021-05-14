//@ ltl invariant positive: [] (AP(i<=(n+1)));

int  i, Fnew, Fold, temp,ans, n;
int tmp;
int main()
{
	
	n=30;
	Fnew = 1;  Fold = 0;
	i = 2;

    	while( i <= n ) 
	{
      		temp = Fnew;
		Fnew = Fnew + Fold;
      		Fold = temp;
      		i++;
    	}

    	ans = Fnew;
		tmp=10000000;
		while (tmp>0) {tmp=tmp-1;}
  	

	return 0;
}

/*RITHM-monitor-code*/
