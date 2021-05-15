//@ ltl invariant positive: []AP(low<=up);


int binary_search(int x);


struct DATA {
  int  key;
  int  value;
}  ;


	int cnt1;
 

struct DATA data[15] = { {1, 100},
	     {5,200},
	     {6, 300},
	     {7, 700},
	     {8, 900},
	     {9, 250},
	     {10, 400},
	     {11, 600},
	     {12, 800},
	     {13, 1500},
	     {14, 1200},
	     {15, 110},
	     {16, 140},
	     {17, 133},
	     {18, 10} };

int index;
int fvalue, mid, up, low,tmp;
int main(void)
{
	index=8;
	binary_search(index);
        return 0;
}

int binary_search(int x)
{
  
  int xy = 0;
  low = 0;
  up = 14;
  fvalue = -1 /* all data are positive */ ;
  while (low <= up) {
    mid = (low + up) >> 1;	
    if ( data[mid].key == x ) {  /*  found  */
      up = low - 1;
      fvalue = data[mid].value;

		printf("FOUND!!\n");

    }
    else  /* not found */
      if ( data[mid].key > x ) 	{
	up = mid - 1;

	printf("MID-1\n");

      }
      else   {
             	low = mid + 1;

	printf("MID+1\n");

      }

	cnt1++;

  }

	printf("Loop Count : %d\n", cnt1);
	tmp=10000000;
	while (tmp>0) {tmp=tmp-1;}
  return fvalue;
}
