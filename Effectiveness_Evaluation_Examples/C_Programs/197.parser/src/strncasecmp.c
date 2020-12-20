#include <string.h>
#include <ctype.h>

#ifdef TEST
#include <stdio.h>
int strncasecmp(const char *s1, const char *s2, size_t n);

int main (int argc, char *argv[]) {
	if (argc != 4) {
		printf ("test [string1] [string2] [size]\n");
		exit (1);
	}
	printf ("'%s' cmp '%s' = %d\n", argv[1], argv[2], strncasecmp(argv[1], argv[2], atoi(argv[3])));
	return 0;
}
#endif

int strncasecmp(const char *s1, const char *s2, size_t n)
{

	const char *i, *j;
	char ui, uj;

	for (i = s1, j = s2 ; *i!=0 && *j!=0; i++, j++ ) {
		if (n-- == 0) return 0;
		ui = toupper(*i);
		uj = toupper(*j);
		if (ui < uj) {
			return -1;
		} else if (ui > uj) {
			return 1;
		}
	}
	if (*i) return -1;
	if (*j) return  1;
	return 0;
}


