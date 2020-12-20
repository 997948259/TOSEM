//@ ltl invariant positive: <>[](array[0].qstring[0] >= array[1].qstring[0]);



struct myStringStruct {
  char qstring[128];
};

int compare(const void *elem1, const void *elem2)
{
  int result;
  
  result = strcmp((*((struct myStringStruct *)elem1)).qstring, (*((struct myStringStruct *)elem2)).qstring);

  return (result < 0) ? 1 : ((result == 0) ? 0 : -1);
}

int count;
int
main() {
  struct myStringStruct array[5];
  //FILE *fp;
  int i;
  count=0;
  char qstringChar1;
  char qstringChar2;
  

/*fp = fopen("F:\\input_small.dat","r");

while((count < 60) && (fscanf(fp, "%s", &array[count].qstring) == 1)) {
  count++;
}*/
//array[0].qstring="a";
//array[1].qstring="b";
//array[2].qstring="c";
//array[3].qstring="d";
//array[4].qstring="e";

  //qsort(array,count,sizeof(struct myStringStruct),compare);

  qstringChar1=array[0].qstring[0];
  qstringChar2=array[1].qstring[0];
  
  return 0;
}
