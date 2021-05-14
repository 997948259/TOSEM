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

int main() {
	struct myStringStruct array[60];
	int i;
	int count = 5;
	int tmp;

	strcpy(array[0].qstring, "1");
	strcpy(array[1].qstring, "2");
	strcpy(array[2].qstring, "3");
	strcpy(array[3].qstring, "4");
	strcpy(array[4].qstring, "5");

	printf("\nSorting %d elements.\n\n", count);
	qsort(array, 5, 128, compare);

	for (i = 0; i < count; i++)
	{
		printf("%s\n", array[i].qstring);
	}
	tmp=10000000;
	while (tmp>0) {tmp=tmp-1;}
	return 0;
}

