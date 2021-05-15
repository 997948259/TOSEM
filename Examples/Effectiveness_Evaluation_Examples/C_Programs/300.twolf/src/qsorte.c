#include "route.h"
extern int top_row ;

#define		THRESH		4	/* threshold for insertion */
#define		MTHRESH		6	/* threshold for median */

int	qsz;			/* size of each record */
int	thresh;			/* THRESHold in chars */
int	mthresh;		/* MTHRESHold in chars */


qsorte(base, n, size)
	char	*base;
	int	n;
	int	size;
{
	register char c, *i, *j, *lo, *hi;
	char *min, *max;

	if (n <= 1)
		return;
	qsz = size;
	thresh = qsz * THRESH;
	mthresh = qsz * MTHRESH;
	max = base + n * qsz;
	if (n >= THRESH) {
		qste(base, max);
		hi = base + thresh;
	} else {
		hi = max;
	}
	for (j = lo = base; (lo += qsz) < hi; )
		if (comparee(j, lo) > 0)
			j = lo;
	if (j != base) {
		/* swap j into place */
		for (i = base, hi = base + qsz; i < hi; ) {
			c = *j;
			*j++ = *i;
			*i++ = c;
		}
	}
	for (min = base; (hi = min += qsz) < max; ) {
		while (comparee(hi -= qsz, min) > 0)
			/* void */;
		if ((hi += qsz) != min) {
			for (lo = min + qsz; --lo >= min; ) {
				c = *lo;
				for (i = j = lo; (j -= qsz) >= hi; i = j)
					*i = *j;
				*i = c;
			}
		}
	}
}


qste(base, max)
	char *base, *max;
{
	register char c, *i, *j, *jj;
	register int ii;
	char *mid, *tmp;
	int lo, hi;

	lo = max - base;		/* number of elements as chars */
	do	{
		mid = i = base + qsz * ((lo / qsz) >> 1);
		if (lo >= mthresh) {
			j = (comparee((jj = base), i) > 0 ? jj : i);
			if (comparee(j, (tmp = max - qsz)) > 0) {
				/* switch to first loser */
				j = (j == jj ? i : jj);
				if (comparee(j, tmp) < 0)
					j = tmp;
			}
			if (j != i) {
				ii = qsz;
				do	{
					c = *i;
					*i++ = *j;
					*j++ = c;
				} while (--ii);
			}
		}
		/*
		 * Semi-standard quicksort partitioning/swapping
		 */
		for (i = base, j = max - qsz; ; ) {
			while (i < mid && comparee(i, mid) <= 0)
				i += qsz;
			while (j > mid) {
				if (comparee(mid, j) <= 0) {
					j -= qsz;
					continue;
				}
				tmp = i + qsz;	/* value of i after swap */
				if (i == mid) {
					/* j <-> mid, new mid is j */
					mid = jj = j;
				} else {
					/* i <-> j */
					jj = j;
					j -= qsz;
				}
				goto swap;
			}
			if (i == mid) {
				break;
			} else {
				/* i <-> mid, new mid is i */
				jj = mid;
				tmp = mid = i;	/* value of i after swap */
				j -= qsz;
			}
		swap:
			ii = qsz;
			do	{
				c = *i;
				*i++ = *jj;
				*jj++ = c;
			} while (--ii);
			i = tmp;
		}
		i = (j = mid) + qsz;
		if ((lo = j - base) <= (hi = max - i)) {
			if (lo >= thresh)
				qste(base, j);
			base = i;
			lo = hi;
		} else {
			if (hi >= thresh)
				qste(i, max);
			max = j;
		}
	} while (lo >= thresh);
}



comparee( a , b )
edgeBptr a , b ;
{

return( a->cost - b->cost ) ;

}
