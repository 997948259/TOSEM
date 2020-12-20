//@ ltl invariant positive: [] (AP(i>=0) && AP(j>=0));

int cnt1, cnt2;

 int  i,j, temp;
int main()
{
 
  int a[11];

  a[0] = 0;   /* assume all data is positive */
  a[1] = 11; a[2]=10;a[3]=9; a[4]=8; a[5]=7; a[6]=6; a[7]=5;
  a[8] =4; a[9]=3; a[10]=2;
  i = 2;
  int a_0=0;
  int a_1=0;
  int a_9=0;
  int a_10=0;
  while(i <= 10){

      cnt1++;

      j = i;

	cnt2=0;

      while (a[j] < a[j-1]) 
      {

	cnt2++;

	temp = a[j];
	a[j] = a[j-1];
	a[j-1] = temp;
	j--;
      }

	printf("Inner Loop Counts: %d\n", cnt2);

      i++;
    }
    a_0=a[0];
    a_1=a[1];
    a_9=a[9];
    a_10=a[10];

    printf("Outer Loop : %d ,  Inner Loop : %d\n", cnt1, cnt2);
    return 0;

}

	
