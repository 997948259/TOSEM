//@ ltl invariant positive: <>([] (AP(a_0 < a_1) && AP(a_9 < a_10)));

int cnt1, cnt2;

 int  i,j, temp;
 int tmp;
   int a_0=0;
  int a_1=0;
  int a_9=0;
  int a_10=0;
int main()
{
 
  int a[11];

  a[0] = 0;   /* assume all data is positive */
  a[1] = 11; a[2]=10;a[3]=9; a[4]=8; a[5]=7; a[6]=6; a[7]=5;
  a[8] =4; a[9]=3; a[10]=2;
  i = 2;

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


      i++;
    }
    a_0=a[0];
    a_1=a[1];
    a_9=a[9];
    a_10=a[10];
	tmp=10000000;
	while (tmp>0) {tmp=tmp-1;}
    return 0;

}