 /***************************************************************************/
 /*                                                                         */
 /* This link grammar system is copyright (C) 1991-1997 by Daniel Sleator   */
 /* (sleator@cs.cmu.edu) and Davy Temperley.  This is work in progress.     */
 /* See http://www.cs.cmu.edu/~sleator for announcements of the latest      */
 /* version, detailed documentation, and rules for commercial use.          */
 /*                                                                         */
 /***************************************************************************/

#include "header.h"

static int match_cost;

int left_disjunct_list_length(Disjunct * d) {
/* returns the number of disjuncts in the list that have non-null
   left connector lists */
    int i;
    for (i=0; d!=NULL; d=d->next) {
	if (d->left != NULL) i++;
    }
    return i;
}
int right_disjunct_list_length(Disjunct * d) {
    int i;
    for (i=0; d!=NULL; d=d->next) {
	if (d->right != NULL) i++;
    }
    return i;
}

static int l_table_size[MAX_SENTENCE];  /* the sizes of the hash tables */
static int r_table_size[MAX_SENTENCE];

static Match_node ** l_table[MAX_SENTENCE]; 
                 /* the beginnings of the hash tables */
static Match_node ** r_table[MAX_SENTENCE];

static Match_node * mn_free_list = NULL;
   /* I'll pedantically maintain my own list of these cells */

Match_node * get_match_node(void) {
/* return a match node to be used by the caller */
    Match_node * m;
    if (mn_free_list != NULL) {
	m = mn_free_list;
	mn_free_list = m->next;
    } else {
	m = (Match_node *) xalloc(sizeof(Match_node));
    }
    return m;
}

void put_match_list(Match_node *m) {
/* put these nodes back onto my free list */    
    Match_node * xm;
    for (; m != NULL; m = xm) {
	xm = m->next;
	m->next = mn_free_list;
	mn_free_list = m;
    }
}

void free_match_list(Match_node * t) {
    Match_node *xt;
    for (; t!=NULL; t=xt) {
	xt = t->next;
	xfree((char *)t, sizeof(Match_node));
    }
}

void free_fast_matcher() {
/* free all of the hash tables and Match_nodes */
    int w;
    int i;
    if (verbosity > 1) printf("%d Match cost\n", match_cost);
    for (w=0; w<N_words; w++) {
	for (i=0; i<l_table_size[w]; i++) {
	    free_match_list(l_table[w][i]);
	}
	xfree((char *)l_table[w], l_table_size[w] * sizeof (Match_node *));
	for (i=0; i<r_table_size[w]; i++) {
	    free_match_list(r_table[w][i]);
	}
	xfree((char *)r_table[w], r_table_size[w] * sizeof (Match_node *));
    }
    free_match_list(mn_free_list);
    mn_free_list = NULL;
}

int fast_match_hash(Connector * c) {
/* This hash function only looks at the leading upper case letters of
   the connector string, and the label fields.  This ensures that if two
   strings match (formally), then they must hash to the same place.
   The answer must be masked to the appropriate table size.
*/
    char *s;
    int i;
    i = randtable[c->label & (RTSIZE-1)];
    s = c->string;
    while(isupper(*s)) {
	i = i + (i<<1) + randtable[((*s) + i) & (RTSIZE-1)];
	s++;
    }
    return i;
}

Match_node * add_to_right_table_list(Match_node * m, Match_node * l) {
/* Adds the match node m to the sorted list of match nodes l.
   The parameter dir determines the order of the sorting to be used.
   Makes the list sorted from smallest to largest.
*/
    if (l==NULL) return m;
    if ((m->d->right->word) <= (l->d->right->word)) {
	m->next = l;
	return m;
    } else {
	l->next = add_to_right_table_list(m, l->next);
	return l;
    }
}

Match_node * add_to_left_table_list(Match_node * m, Match_node * l) {
/* Adds the match node m to the sorted list of match nodes l.
   The parameter dir determines the order of the sorting to be used.
   Makes the list sorted from largest to smallest
*/
    if (l==NULL) return m;
    if ((m->d->left->word) >= (l->d->left->word)) {
	m->next = l;
	return m;
    } else {
	l->next = add_to_left_table_list(m, l->next);
	return l;
    }
}

void put_into_match_table(int size, Match_node ** t,
			  Disjunct * d, Connector * c, int dir ) {
/* The disjunct d (whose left or right pointer points to c) is put
   into the appropriate hash table
   dir =  1, we're putting this into a right table.
   dir = -1, we're putting this into a left table.
*/
    int h;
    Match_node * m;
    h = fast_match_hash(c) & (size-1);
    m = (Match_node *) xalloc (sizeof(Match_node));
    m->next = NULL;
    m->d = d;
    if (dir == 1) {
	t[h] = add_to_right_table_list(m, t[h]);
    } else {
	t[h] = add_to_left_table_list(m, t[h]);
    }
}

void init_fast_matcher() {
    int w, len, size, i;
    Match_node ** t;
    Disjunct * d;
    match_cost = 0;
    for (w=0; w<N_words; w++) {
	len = left_disjunct_list_length(sentence[w].d);
	size = next_power_of_two_up(len);
	l_table_size[w] = size;
	t = l_table[w] = (Match_node **) xalloc(size * sizeof(Match_node *));
	for (i=0; i<size; i++) t[i] = NULL;

	for (d=sentence[w].d; d!=NULL; d=d->next) {
	    if (d->left != NULL) {
		put_into_match_table(size, t, d, d->left, -1);
	    }
	}

	len = right_disjunct_list_length(sentence[w].d);
	size = next_power_of_two_up(len);
	r_table_size[w] = size;
	t = r_table[w] = (Match_node **) xalloc(size * sizeof(Match_node *));
	for (i=0; i<size; i++) t[i] = NULL;

	for (d=sentence[w].d; d!=NULL; d=d->next) {
	    if (d->right != NULL) {
		put_into_match_table(size, t, d, d->right, 1);
	    }
	}
    }
}

Match_node * form_match_list
      (int w, Connector *lc, int lw, Connector *rc, int rw) {
/* Forms and returns a list of disjuncts that might match lc or rc or both.
   lw and rw are the words from which lc and rc came respectively.
   The list is formed by the link pointers of Match_nodes.
   The list contains no duplicates.  A quadratic algorithm is used to
   eliminate duplicates.  In practice the match_cost is less than the
   parse_cost (and the loop is tiny), so there's no reason to bother
   to fix this.
*/
    Match_node *ml, *mr, *mx, *my, * mz, *front, *free_later;

    if (lc!=NULL) {
	ml = l_table[w][fast_match_hash(lc) & (l_table_size[w]-1)];
    } else {
	ml = NULL;
    }
    if (rc!=NULL) {
	mr = r_table[w][fast_match_hash(rc) & (r_table_size[w]-1)];
    } else {
	mr = NULL;
    }

    front = NULL;
    for (mx = ml; mx!=NULL; mx=mx->next) {
	if (mx->d->left->word < lw) break;
	my = get_match_node();
	my->d = mx->d;
	my->next = front;
	front = my;
    }
    ml = front;   /* ml is now the list of things that could match the left */

    front = NULL;
    for (mx = mr; mx!=NULL; mx=mx->next) {
	if (mx->d->right->word > rw) break;
	my = get_match_node();
	my->d = mx->d;
	my->next = front;
	front = my;
    }
    mr = front;   /* mr is now the list of things that could match the right */

    /* now we want to eliminate duplicates from the lists */

    free_later = NULL;
    front = NULL;
    for(mx = mr; mx != NULL; mx=mz) {
	/* see if mx in first list, put it in if its not */
	mz = mx->next;
	match_cost++;
	for (my=ml; my!=NULL; my=my->next) {
	    match_cost++;
	    if (mx->d == my->d) break;
	}
	if (my != NULL) { /* mx was in the l list */
	    mx->next = free_later;
	    free_later = mx;
	}
	if (my==NULL) {  /* it was not there */
	    mx->next = front;
	    front = mx;
	}
    }
    mr = front;  /* mr is now the abbreviated right list */
    put_match_list(free_later);

    /* now catenate the two lists */
    if (mr == NULL) return ml;
    for (mx = mr; mx->next != NULL; mx = mx->next)
      ;
    mx->next = ml;
    return mr;
}
