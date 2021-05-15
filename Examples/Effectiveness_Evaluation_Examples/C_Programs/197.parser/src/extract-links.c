 /***************************************************************************/
 /*                                                                         */
 /* This link grammar system is copyright (C) 1991-1997 by Daniel Sleator   */
 /* (sleator@cs.cmu.edu) and Davy Temperley.  This is work in progress.     */
 /* See http://www.cs.cmu.edu/~sleator for announcements of the latest      */
 /* version, detailed documentation, and rules for commercial use.          */
 /*                                                                         */
 /***************************************************************************/

#include "header.h"

Link link_array[MAX_LINKS];
int N_links;

char forgiving;

/* should get rid of chosen_words eventually.  That info is in the
   chosen disjuncts */

Disjunct * chosen_disjuncts[MAX_SENTENCE];

void issue_link(Disjunct *ld, Disjunct * rd, int lw, int rw,
		Connector * lc, Connector * rc) {
    link_array[N_links].l = lw;
    link_array[N_links].r = rw;
    link_array[N_links].lc = lc;
    link_array[N_links].rc = rc;
    N_links++;

    chosen_disjuncts[lw] = ld;
    chosen_disjuncts[rw] = rd;
}

int magic(int lw, int rw, Connector *le, Connector *re, int cost) {
/* returns the count for this quadruple if there, 0 otherwise */
/* the only difference between this and table_lookup is that  */
/* the latter returns -1 when it's not there, this returns 0  */
/* This will fool list_links into working, even though the    */
/* search may be conducted in a different order.  If one of   */
/* these bogus answers is returned, even though it may be     */
/* wrong, we know that this entry in the table could not be   */
/* used in any of the correct parsings, so it's ok to give the*/
/* wrong answer.                                              */
    int count;

    if (cost < 0) return 0;
    
    count = table_lookup(lw, rw, le, re, cost);
    if (count < 0) return 0; else return count;
}

void list_links(Disjunct *ld, Disjunct * rd, int lw, int rw,
                Connector *le, Connector *re, int cost, int index) {
    Disjunct * d;
    int leftcount, rightcount, total;
    int i, x, delta;
    int lml=0, lmr=0, rml=0, rmr=0;
    int lc, rc, lindex, rindex;
    int lcost, rcost;
    int w, start_word, end_word;
    Match_node * m, *m1;

    if (rw == 1+lw) {
	assert((le == NULL) && (re == NULL) && (index == 0),
	       "Error encountered while extracting links.");
	return;
    }

    if (cost < 0) return;

    if ((le == NULL) && (re == NULL)) {
	total = 0;
	w = lw+1;
	for (d = sentence[w].d; d != NULL; d = d->next) {
	    if (d->left == NULL) {
		i = magic(w, rw, d->right, re, cost-1);
		total += i;
		if ((total-i <= index) && (total > index)) {
		    list_links(d, rd, w, rw, d->right, re, cost-1, index-total+i);
		}
	    }
	}
	i = magic(w, rw, NULL, NULL, cost-1);
	total += i;
	if ((total - i <= index) && (total > index)) {
	    list_links(NULL, rd, w, rw, NULL, re, cost-1, index-total+i);
	}
	return;
    }


    total = 0;
    if (le == NULL) {
	start_word = lw+1;
    } else {
	start_word = le->word;
    }
    if (re == NULL) {
	end_word = MIN(rw-1, lw+maxlinklength);
    } else {
	end_word = re->word;
    }

    for (w=start_word; w <= end_word; w++) {
	m1 = m = form_match_list(w, le, lw, re, rw); 
	for (; m!=NULL; m=m->next) {
	    d = m->d;
	    for (lcost = 0; lcost <= cost; lcost++) {
		rcost = cost-lcost;
		/* now lcost and rcost are the costs we're assigning to those parts respectively */
		if ((le != NULL) && (d->left != NULL) && match(le, d->left)) {
		    lml = le->multi;
		    lmr = d->left->multi;
		    leftcount = magic(lw, w, le->next, d->left->next, lcost);
		    if (lml) leftcount += magic(lw, w, le, d->left->next, lcost);
		    if (lmr) leftcount += magic(lw, w, le->next, d->left, lcost);
		    if (lml&&lmr) leftcount += magic(lw, w, le, d->left, lcost);
		} else {
		    leftcount = 0;
		}
		if ((d->right != NULL) && (re != NULL) && match(d->right, re)) {
		    rml = d->right->multi;
		    rmr = re->multi;
		    rightcount = magic(w, rw, d->right->next,re->next, rcost);
		    if (rml) rightcount+= magic(w, rw, d->right, re->next, rcost);
		    if (rmr) rightcount+= magic(w, rw, d->right->next, re, rcost);
		    if (rml&&rmr) rightcount+= magic(w, rw, d->right, re, rcost);
		} else {
		    rightcount = 0;
		}
		i = leftcount * rightcount;
		total += i;
		
		if ((total-i <= index) && (total > index)) {
		    x = index-total+i;  /* 0 <= x < i */
		    lindex = x / rightcount;
		    rindex = x % rightcount;
		    lc = 0;
		    delta = magic(lw, w, le->next, d->left->next, lcost);
		    lc += delta;
		    if (lc > lindex) {
			issue_link(ld, d, lw, w, le, d->left);
			list_links(ld, d, lw, w, le->next, d->left->next, lcost, lindex-lc+delta);
		    }
		    if (lml) delta = magic(lw, w, le, d->left->next, lcost);
		    else delta = 0;
		    lc += delta;
		    if ((lc-delta <= lindex) && (lc > lindex)) {
			issue_link(ld, d, lw, w, le, d->left);
			list_links(ld, d, lw, w, le, d->left->next, lcost, lindex-lc+delta);
		    }
		    if (lmr) delta = magic(lw, w, le->next, d->left, lcost);
		    else delta=0;
		    lc += delta;
		    if ((lc-delta <=lindex) && lc > lindex) {
			issue_link(ld, d, lw, w, le, d->left);
			list_links(ld, d, lw, w, le->next, d->left, lcost, lindex-lc+delta);
		    }
		    if (lml&&lmr) delta = magic(lw, w, le, d->left, lcost);
		    else delta = 0;
		    lc += delta;
		    if ((lc-delta <=lindex) && lc > lindex) {
			issue_link(ld, d, lw, w, le, d->left);
			list_links(ld, d, lw, w, le, d->left, lcost, lindex-lc+delta);
		    }
		    rc = 0;
		    delta = magic(w, rw, d->right->next,re->next, rcost);
		    rc += delta;
		    if (rc > rindex) {
			issue_link(d, rd, w, rw, d->right, re);
			list_links(d, rd, w, rw, d->right->next, re->next, rcost, rindex-rc+delta);
		    }
		    if (rml) delta = magic(w, rw, d->right, re->next, rcost);
		    else delta = 0;
		    rc += delta;
		    if ((rc-delta <= rindex) && rc > rindex) {
			issue_link(d, rd, w, rw, d->right, re);
			list_links(d, rd, w, rw, d->right, re->next, rcost, rindex-rc+delta);
		    }
		    if (rmr) delta = magic(w, rw, d->right->next, re, rcost);
		    else delta = 0;
		    rc += delta;
		    if ((rc-delta <= rindex) && rc > rindex) {
			issue_link(d, rd, w, rw, d->right, re);
			list_links(d, rd, w, rw, d->right->next, re, rcost, rindex-rc+delta);
		    }
		    if (rml&&rmr) delta = magic(w, rw, d->right, re, rcost);
		    else delta = 0;
		    rc += delta;
		    if ((rc-delta <= rindex) && rc > rindex) {
			issue_link(d, rd, w, rw, d->right, re);
			list_links(d, rd, w, rw, d->right, re, rcost, rindex-rc+delta);
		    }
		}
		
		if (leftcount > 0) {
		    i = leftcount * magic(w, rw, d->right, re, rcost);
		} else {
		    i = 0;
		}
		total += i;
		if ((total-i <= index) && (total > index)) {
		    x = index-total+i;  /* 0 <= x < i */
		    lindex = x % leftcount;
		    rindex = x / leftcount;

		    lc = 0;
		    delta = magic(lw, w, le->next, d->left->next, lcost);
		    lc += delta;
		    if (lc > lindex) {
			issue_link(ld, d, lw, w, le, d->left);
			list_links(ld, d, lw, w, le->next,d->left->next, lcost, lindex-lc+delta);
		    }
		    if (lml) delta = magic(lw, w, le, d->left->next, lcost);
		    else delta = 0;
		    lc += delta;
		    if ((lc-delta <= lindex) && (lc > lindex)) {
			issue_link(ld, d, lw, w, le, d->left);
			list_links(ld, d, lw, w, le, d->left->next, lcost, lindex-lc+delta);
		    }
		    if (lmr) delta = magic(lw, w, le->next, d->left, lcost);
		    else delta=0;
		    lc += delta;
		    if ((lc-delta <=lindex) && lc > lindex) {
			issue_link(ld, d, lw, w, le, d->left);
			list_links(ld, d, lw, w, le->next, d->left, lcost, lindex-lc+delta);
		    }
		    if (lml&&lmr) delta = magic(lw, w, le, d->left, lcost);
		    else delta = 0;
		    lc += delta;
		    if ((lc-delta <=lindex) && lc > lindex) {
			issue_link(ld, d, lw, w, le, d->left);
			list_links(ld, d, lw, w, le, d->left, lcost, lindex-lc+delta);
		    }
		    
		    list_links(d, rd, w, rw, d->right, re, rcost, rindex);
		}
		if ((le == NULL) && (rightcount > 0)) {
		    i = rightcount * magic(lw, w, le, d->left, lcost);
		} else {
		    i = 0;
		}
		total += i;
		if ((total-i <= index) && (total > index)) {
		    x = index-total+i;  /* 0 <= x < i */
		    rindex = x % rightcount;
		    lindex = x / rightcount;
		    
		    rc = 0;
		    delta = magic(w, rw, d->right->next,re->next, rcost);
		    rc += delta;
		    if (rc > rindex) {
			issue_link(d, rd, w, rw, d->right, re);
			list_links(d, rd, w, rw, d->right->next, re->next, rcost, rindex-rc+delta);
		    }
		    if (rml) delta = magic(w, rw, d->right, re->next, rcost);
		    else delta = 0;
		    rc += delta;
		    if ((rc-delta <= rindex) && rc > rindex) {
			issue_link(d, rd, w, rw, d->right, re);
			list_links(d, rd, w, rw, d->right, re->next, rcost, rindex-rc+delta);
		    }
		    if (rmr) delta = magic(w, rw, d->right->next, re, rcost);
		    else delta = 0;
		    rc += delta;
		    if ((rc-delta <= rindex) && rc > rindex) {
			issue_link(d, rd, w, rw, d->right, re);
			list_links(d, rd, w, rw, d->right->next, re, rcost, rindex-rc+delta);
		    }
		    if (rml&&rmr) delta = magic(w, rw, d->right, re, rcost);
		    else delta = 0;
		    rc += delta;
		    if ((rc-delta <= rindex) && rc > rindex) {
			issue_link(d, rd, w, rw, d->right, re);
			list_links(d, rd, w, rw, d->right, re, rcost, rindex-rc+delta);
		    }
		    list_links(ld, d, lw, w, le, d->left, lcost, lindex);
		}
	    }
	}
	put_match_list(m1);
    }
}

void initialize_links(void) {
    int i;
    for (i=0; i<N_words; ++i) {
	chosen_disjuncts[i] = NULL;
    }
}

void extract_links(int index, int cost) {
/* generate the list of all links of the indexth parsing of the sentence */
/* for this to work, the hash table must have already been built with a  */
/* call to count(cost).                                                  */
    
    Disjunct * dis;
    int total, c=0;
    N_links = 0;
    total = 0;

    initialize_links();

    for (dis = sentence[0].d; dis != NULL; dis = dis->next) {
	if (dis->left == NULL) {
	    c = magic(0, N_words, dis->right, NULL, cost);
	    total += c;
	    if (total > index) break;
	}	
    }
    if (total > index) {
	list_links(dis, NULL, 0, N_words, dis->right, NULL, cost, index-total+c);
    } else {
	c = magic(0, N_words, NULL, NULL, cost);
	total += c;
	list_links(NULL, NULL, 0, N_words, NULL, NULL, cost, index-total+c);
    }
}
