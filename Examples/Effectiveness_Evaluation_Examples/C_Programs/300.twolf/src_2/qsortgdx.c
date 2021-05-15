#include "standard.h"
#include "groute.h"

extern int top_row ;

#define		THRESH		4	/* threshold for insertion */
#define		MTHRESH		6	/* threshold for median */

extern int	qsz;			/* size of each record */
extern int	thresh;			/* THRESHold in chars */
extern int	mthresh;		/* MTHRESHold in chars */


qsortgdx(base, n, size)
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
		qstgdx(base, max);
		hi = base + thresh;
	} else {
		hi = max;
	}
	for (j = lo = base; (lo += qsz) < hi; )
		if (comparegdx(j, lo) > 0)
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
		while (comparegdx(hi -= qsz, min) > 0)
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


qstgdx(base, max)
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
			j = (comparegdx((jj = base), i) > 0 ? jj : i);
			if (comparegdx(j, (tmp = max - qsz)) > 0) {
				/* switch to first loser */
				j = (j == jj ? i : jj);
				if (comparegdx(j, tmp) < 0)
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
			while (i < mid && comparegdx(i, mid) <= 0)
				i += qsz;
			while (j > mid) {
				if (comparegdx(mid, j) <= 0) {
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
				qstgdx(base, j);
			base = i;
			lo = hi;
		} else {
			if (hi >= thresh)
				qstgdx(i, max);
			max = j;
		}
	} while (lo >= thresh);
}



comparegdx( a , b )
CHANGRDPTR *a , *b ;
{
return( (*a)->netptr->xpos - (*b)->netptr->xpos ) ;
}
