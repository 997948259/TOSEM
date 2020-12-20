 /***************************************************************************/
 /*                                                                         */
 /* This link grammar system is copyright (C) 1991-1997 by Daniel Sleator   */
 /* (sleator@cs.cmu.edu) and Davy Temperley.  This is work in progress.     */
 /* See http://www.cs.cmu.edu/~sleator for announcements of the latest      */
 /* version, detailed documentation, and rules for commercial use.          */
 /*                                                                         */
 /***************************************************************************/

#include "header.h"
#define INFINITY 1000

/* This file contains the exhaustive search algorithm. */

/* Important functions, and what they do.  Cost here always refers to the
   number of null-links used.

   int truecount(int lw, int rw, Connector *le, Connector *re);
       Returns the number of ways to parse the given region with the
       given connector lists.  It fills in the table with these
       counts as it computes them.  This is the same as count() in the
       old version of the parser.  No null links.

   int strictparse(void);
       Just like the old parse().  Returns the number of ways to parse
       the sentence by calling truecount().  No null links.

   int cost(int lw, int rw, Connector *le, Connector *re);
       Returns the cost of the minimum cost way of parsing the given region
       with the given connector lists.  Here cost is defined to be the number
       of null-links required.  It calls cost() recursively.
  
   int count(int lw, int rw, Connector *le, Connector *re);
       This returns the number of linkages for the given region whose cost
       is equal to the minimum cost.  It assumes (unnecessarily) that
       cost() has already been called for that region (and the cost values
       are already in the hash table).

   int calc_min_cost(void);
       This is the wrapper around cost() that computes the minimum cost way
       of parsing the sentence.

   int parse(int mincost);
       Returns the number of ways the sentence can be parsed with cost mincost.

*/

#define NO_ISLANDS TRUE

/* If this is FALSE, then linkages in which an island of words appear
   that are separate from the rest of the sentence are allowed.  If it
   is TRUE, then these are not allwed.  The current post processing
   system eliminates all linkages with islands, so for efficiency sake
   it makes sense to leave this set to TRUE.  */

int match(Connector *a, Connector *b) {
  /* 
     Returns TRUE if s and t match according to the connector matching
     rules.  The connector strings must be properly formed, starting with
     zero or more upper case letters, followed by some other letters, and
     The algorithm is symmetric with respect to a and b.
     
     It works as follows:  The labels must match.  The priorities must be
     compatible (both THIN_priority, or one UP_priority and one DOWN_priority).
     The sequence of upper case letters must match exactly.  After these comes
     a sequence of lower case letters "*"s or "^"s.  The matching algorithm
     is different depending on which of the two priority cases is being
     considered.  See the comments below.  */
    char *s, *t;
    int x, y;
    if (a->label != b->label) return FALSE;
    x = a->priority;
    y = b->priority;
    
    s = a->string;
    t = b->string;
    
    while(isupper(*s) || isupper(*t)) {
	if (*s != *t) return FALSE;
	s++;
	t++;
    }
    
    if ((x==THIN_priority) && (y==THIN_priority)) {
	/*
	   Remember that "*" matches anything, and "^" matches nothing
	   (except "*").  Otherwise two characters match if and only if
	   they're equal.  ("^" can be used in the dictionary just like
	   any other connector.)
	   */
	while ((*s!='\0') && (*t!='\0')) {
	    if ((*s == '*') || (*t == '*') ||
		((*s == *t) && (*s != '^'))) {
		s++;
		t++;
	    } else return FALSE;
	}
	return TRUE;
    } else if ((x==UP_priority) && (y==DOWN_priority)) {
	/*
	   As you go up (namely from x to y) the set of strings that
	   match (in the normal THIN sense above) should get no larger.
	   Read the comment in and.c to understand this.
	   In other words, the y string (t) must be weaker (or at least
	   no stronger) that the x string (s).
	   
	   This code is only correct if the strings are the same
	   length.  This is currently true, but perhaps for safty
	   this assumption should be removed.
	   */
	while ((*s!='\0') && (*t!='\0')) {
	    if ((*s == *t) || (*s == '*') || (*t == '^')) {
		s++;
		t++;
	    } else return FALSE;
	}
	return TRUE;
    } else if ((y==UP_priority) && (x==DOWN_priority)) {
	while ((*s!='\0') && (*t!='\0')) {
	    if ((*s == *t) || (*t == '*') || (*s == '^')) {
		s++;
		t++;
	    } else return FALSE;
	}
	return TRUE;
    } else return FALSE;
}

typedef struct Table_connector Table_connector;
struct Table_connector {
    short              lw, rw;
    Connector         *le, *re;
    short              cost;
    int                count;
    Table_connector   *next;
};

static int table_size;
static Table_connector ** table;

void init_table(void) {
    /* A piecewise exponential function determines the size of the hash table.      */
    /* Probably should make use of the actual number of disjuncts, rather than just */
    /* the number of words                                                          */
    int i;
    if (N_words >= 10) {
	table_size = (1<<16);
	/*  } else if (N_words >= 10) {
	    table_size = (1 << (((6*(N_words-10))/30) + 10)); */
    } else if (N_words >= 4) {
	table_size = (1 << (((6*(N_words-4))/6) + 4));
    } else {
	table_size = (1 << 4);
    }
    table = (Table_connector**) xalloc(table_size * sizeof(Table_connector*));
    for (i=0; i<table_size; i++) {
	table[i] = NULL;
    }
}

int hash(int lw, int rw, Connector *le, Connector *re, int cost) {
    int i;
    i = 0;
    
    i = i + (i<<1) + randtable[(lw + i) & (RTSIZE - 1)];
    i = i + (i<<1) + randtable[(rw + i) & (RTSIZE - 1)];
    i = i + (i<<1) + randtable[(((long) le + i) % (table_size+1)) & (RTSIZE - 1)];
    i = i + (i<<1) + randtable[(((long) re + i) % (table_size+1)) & (RTSIZE - 1)];
    i = i + (i<<1) + randtable[(cost+i) & (RTSIZE - 1)];
    return i & (table_size-1);
}

void free_table(void) {
    int i;
    Table_connector *t, *x;
    
    for (i=0; i<table_size; i++) {
	for(t = table[i]; t!= NULL; t=x) {
	    x = t->next;
	    xfree((void *) t, sizeof(Table_connector));
	}
    }
    xfree((void *) table, table_size * sizeof(Table_connector*));
}

Table_connector * table_pointer(int lw, int rw, Connector *le, Connector *re, int cost) {
    /* returns the pointer to this info, NULL if not there */
    Table_connector *t;
    N_hash_lookups++;
    work_in_hash_lookups++;
    t = table[hash(lw, rw, le, re, cost)];
    for (; t != NULL; t = t->next) {
	work_in_hash_lookups++;
	if ((t->lw == lw) && (t->rw == rw) && (t->le == le) && (t->re == re) && (t->cost == cost))  return t;
    }
    return NULL;
}

int table_lookup(int lw, int rw, Connector *le, Connector *re, int cost) {
    /* returns the count for this quintuple if there, -1 otherwise */    
    Table_connector *t = table_pointer(lw, rw, le, re, cost);

    if (t == NULL) return -1; else return t->count;
}

Table_connector * table_store(int lw, int rw, Connector *le, Connector *re, int cost, int count){
    /* Stores the value in the table.  Assumes it's not already there */
    Table_connector *t, *n;
    int h;
    N_in_table++;
    
    n = (Table_connector *) xalloc(sizeof(Table_connector));
    n->count = count; 
    n->lw = lw; n->rw = rw; n->le = le; n->re = re; n->cost = cost;
    h = hash(lw, rw, le, re, cost);
    t = table[h];
    n->next = t;
    table[h] = n;
    return n;
}

void table_update(int lw, int rw, Connector *le, Connector *re, int cost, int count) {
    /* Stores the value in the table.  Unlike table_store, it assumes it's already there */
    Table_connector *t = table_pointer(lw, rw, le, re, cost);
    
    assert(t != NULL, "This entry is supposed to be in the table.");
    t->count = count;
}


int pseudocount(int lw, int rw, Connector *le, Connector *re, int cost) {
/* returns 0 if and only if this entry is in the hash table with a count value of 0 */
    int count;
    count = table_lookup(lw, rw, le, re, cost);
    if (count == 0) return 0; else return 1;
}

int count(int lw, int rw, Connector *le, Connector *re, int cost) {
    Disjunct * d;
    int total, pseudototal;
    int start_word, end_word, w;
    int leftcount, rightcount;
    int lcost, rcost, Lmatch, Rmatch;

    Match_node * m, *m1;
    Table_connector *t;

    if (cost < 0) return 0;  /* will we ever call it with cost<0 ? */

    t = table_pointer(lw, rw, le, re, cost);

    if (t == NULL) {
	t = table_store(lw, rw, le, re, cost, 0);  /* create the table entry with a tentative cost of 0 */
	                                           /* this cost must be updated before we return */
    } else {
	return t->count;
    }
    
    if (rw == 1+lw) {
	/* lw and rw are neighboring words */
	/* you can't have a linkage here with cost > 0 */
	if ((le == NULL) && (re == NULL) && (cost == 0)) {
	    t->count = 1;
	} else {
	    t->count = 0;
	}
	return t->count;
    }
    
    if ((le == NULL) && (re == NULL)) {
#if NO_ISLANDS
	/* if we don't allow islands (a set of words linked together but
	   separate from the rest of the sentence) then  the cost of skipping
	   n words is just n */
	if (cost == rw-lw-1) {
	    t->count = 1;
	} else {
	    t->count = 0;
	}
	return t->count;
#else
	if (cost == 0) {
	    /* there is no zero-cost solution in this case */
	    /* slight efficiency hack to separate this cost=0 case out */
	    /* but not necessary for correctness */
	    t->count = 0;
	} else {
	    total = 0;
	    w = lw+1;
	    for (d = sentence[w].d; d != NULL; d = d->next) {
		if (d->left == NULL) {
		    total += count(w, rw, d->right, NULL, cost-1);
		}
	    }
	    total += count(w, rw, NULL, NULL, cost-1);
	    t->count = total;
	}
	return t->count;
#endif	    
    }
    
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

    total = 0;
    
    for (w=start_word; w <= end_word; w++) {
	m1 = m = form_match_list(w, le, lw, re, rw); 
	for (; m!=NULL; m=m->next) {
	    d = m->d;
	    for (lcost = 0; lcost <= cost; lcost++) {
		rcost = cost-lcost;
		/* now lcost and rcost are the costs we're assigning to those parts respectively */


		/* Now, we determine if (based on table only) we can see that
		   the current range is not parsable. */

		Lmatch = (le != NULL) && (d->left != NULL) && match(le, d->left);
		Rmatch = (d->right != NULL) && (re != NULL) && match(d->right, re);

		rightcount = leftcount = 0;
		if (Lmatch) {
		    leftcount = pseudocount(lw, w, le->next, d->left->next, lcost);
		    if (le->multi) leftcount += pseudocount(lw, w, le, d->left->next, lcost);
		    if (d->left->multi) leftcount += pseudocount(lw, w, le->next, d->left, lcost);
		    if (le->multi && d->left->multi) leftcount += pseudocount(lw, w, le, d->left, lcost);
		}
		
		if (Rmatch) {
		    rightcount = pseudocount(w, rw, d->right->next, re->next, rcost);
		    if (d->right->multi) rightcount += pseudocount(w,rw,d->right,re->next, rcost);
		    if (re->multi) rightcount += pseudocount(w, rw, d->right->next, re, rcost);
		    if (d->right->multi && re->multi) rightcount += pseudocount(w, rw, d->right, re, rcost);
		}

		pseudototal = leftcount*rightcount;  /* total number where links are used on both sides */

		if (leftcount > 0) {
		    /* evaluate using the left match, but not the right */
		    pseudototal += leftcount * pseudocount(w, rw, d->right, re, rcost);
		}
		if ((le == NULL) && (rightcount > 0)) {
		    /* evaluate using the right match, but not the left */
		    pseudototal += rightcount * pseudocount(lw, w, le, d->left, lcost);
		}

		/* now pseudototal is 0 implies that we know that the true total is 0 */
		if (pseudototal != 0) {
		    rightcount = leftcount = 0;
		    if (Lmatch) {
			leftcount = count(lw, w, le->next, d->left->next, lcost);
			if (le->multi) leftcount += count(lw, w, le, d->left->next, lcost);
			if (d->left->multi) leftcount += count(lw, w, le->next, d->left, lcost);
			if (le->multi && d->left->multi) leftcount += count(lw, w, le, d->left, lcost);
		    }

		    if (Rmatch) {
			rightcount = count(w, rw, d->right->next, re->next, rcost);
			if (d->right->multi) rightcount += count(w,rw,d->right,re->next, rcost);
			if (re->multi) rightcount += count(w, rw, d->right->next, re, rcost);
			if (d->right->multi && re->multi) rightcount += count(w, rw, d->right, re, rcost);
		    }

		    total += leftcount*rightcount;  /* total number where links are used on both sides */

		    if (leftcount > 0) {
			/* evaluate using the left match, but not the right */
			total += leftcount * count(w, rw, d->right, re, rcost);
		    }
		    if ((le == NULL) && (rightcount > 0)) {
			/* evaluate using the right match, but not the left */
			total += rightcount * count(lw, w, le, d->left, lcost);
		    }
		}
	    }
	}
	    
	put_match_list(m1);
    }
    t->count = total;
    return total;
}

/*
To: Danny Sleator <sleator@CS.cmu.edu>
From: John Lafferty <lafferty@CS.cmu.edu>
Subject: improved parse procedure
Mime-Version: 1.0
Content-Type: text/plain; charset=us-ascii
Date: Mon, 08 Jan 1996 19:13:23 -0500
Message-ID: <27437.821146403@HARROLD.IS.CS.CMU.EDU>
Sender: John_Lafferty@HARROLD.IS.CS.CMU.EDU


Danny,

Here's another, equivalent way of writing the "parse" procedure in your
version of the code with null links (e.g., the release version):

int parse(int cost) {
    return count(-1, N_words, NULL, NULL, cost+1);
}

I'm making pretty good progress on writing the inside/outside
training.  I have the basic routines written and working with 
dummy procedures for the probabilities (but these procedures 
are the hard part!).

John
*/

int parse(int cost) {
    /* Returns the number of ways the sentence can be parsed with the
       specified cost Assumes that the hash table has already been
       initialized, and is freed later.  */
    
    Disjunct * dis;
    int total=0;
    
    for (dis = sentence[0].d; dis != NULL; dis = dis->next) {
	if (dis->left == NULL) {
	    total += count(0, N_words, dis->right, NULL, cost);
	}
    }

    /* the following allows the possibility of a null link used on the leftmost word */
    total += count(0, N_words, NULL, NULL, cost);
    
    if (verbosity > 1) {
	printf("Total count with cost %d:   %d\n", cost, total);
    }
    return total;
}

/*
   
   CONJUNCTION PRUNING.
   
   The basic idea is this.  Before creating the fat disjuncts,
   we run a modified version of the exhaustive search procedure.
   Its purpose is to mark the disjuncts that can be used in any
   linkage.  It's just like the normal exhaustive search, except that
   if a subrange of words are deletable, then we treat them as though
   they were not even there.  So, if we call the function in the
   situation where the set of words between the left and right one
   are deletable, and the left and right connector pointers
   are NULL, then that range is considered to have a solution.
   
   There are actually two procedures to implement this.  One is
   mark_region() and the other is region_valid().  The latter just
   checks to see if the given region can be completed (within it).
   The former actually marks those disjuncts that can be used in
   any valid linkage of the given region.
   
   As in the standard search procedure, we make use of the fast-match
   data structure (which requires power pruning to have been done), and
   we also use a hash table.  The table is used differently in this case.
   The meaning of values stored in the table are as follows:
   
   -1  Nothing known (Actually, this is not stored.  It's returned
   by table_lookup when nothing is known.)
   0  This region can't be completed (marking is therefore irrelevant)
   1  This region can be completed, but it's not yet marked
   2  This region can be completed, and it's been marked.
   */  

int region_valid(int lw, int rw, Connector *le, Connector *re) {
    /* Returns 0 if this range cannot be successfully filled in with           */
    /* links.  Returns 1 if it can, and it's not been marked, and returns      */
    /* 2 if it can and it has been marked.                                     */
    
    Disjunct * d;
    int left_valid, right_valid, found;
    int i, start_word, end_word;
    int w;
    Match_node * m, *m1;
    
    i = table_lookup(lw, rw, le, re, 0);
    if (i >= 0) return i;
    
    if ((le == NULL) && (re == NULL) && deletable[lw][rw]) {
	table_store(lw, rw, le, re, 0, 1);
	return 1;
    }
    
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
    
    found = 0;
    
    for (w=start_word; w <= end_word; w++) {
	m1 = m = form_match_list(w, le, lw, re, rw); 
	for (; m!=NULL; m=m->next) {
	    d = m->d;
	    mark_cost++;
	    /* in the following expressions we use the fact that 0=FALSE. Could eliminate
	       by always saying "region_valid(...) != 0"  */
	    left_valid = (((le != NULL) && (d->left != NULL) && prune_match(le, d->left)) &&
			  ((region_valid(lw, w, le->next, d->left->next)) ||
			   ((le->multi) && region_valid(lw, w, le, d->left->next)) ||
			   ((d->left->multi) && region_valid(lw, w, le->next, d->left)) ||
			   ((le->multi && d->left->multi) && region_valid(lw, w, le, d->left))));
	    if (left_valid && region_valid(w, rw, d->right, re)) {
		found = 1;
		break;
	    }
	    right_valid = (((d->right != NULL) && (re != NULL) && prune_match(d->right, re)) &&
			   ((region_valid(w, rw, d->right->next,re->next))    ||
			    ((d->right->multi) && region_valid(w,rw,d->right,re->next))  ||
			    ((re->multi) && region_valid(w, rw, d->right->next, re))  ||
			    ((d->right->multi && re->multi) && region_valid(w, rw, d->right, re))));
	    if ((left_valid && right_valid) || (right_valid && region_valid(lw, w, le, d->left))) {
		found = 1;
		break;
	    }
	}
	put_match_list(m1);
	if (found != 0) break;
    }
    table_store(lw, rw, le, re, 0, found);
    return found;
}

void mark_region(int lw, int rw, Connector *le, Connector *re) {
    /* Mark as useful all disjuncts involved in some way to complete the structure  */
    /* within the current region.  Note that only disjuncts strictly between        */
    /* lw and rw will be marked.  If it so happens that this region itself is not   */
    /* valid, then this fact will be recorded in the table, and nothing else happens*/    
    
    Disjunct * d;
    int left_valid, right_valid, i;
    int start_word, end_word;
    int w;
    Match_node * m, *m1;
    
    i = region_valid(lw, rw, le, re);
    if ((i==0) || (i==2)) return;
    /* we only reach this point if it's a valid unmarked region, i=1 */
    table_update(lw, rw, le, re, 0, 2);
    
    if ((le == NULL) && (re == NULL) && (null_links) && (rw != 1+lw)) {
	w = lw+1;
	for (d = sentence[w].d; d != NULL; d = d->next) {
	    if ((d->left == NULL) && region_valid(w, rw, d->right, NULL)) {
		d->marked = TRUE;
		mark_region(w, rw, d->right, NULL);
	    }
	}
	mark_region(w, rw, NULL, NULL);
	return;
    }
    
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
	    mark_cost++;
	    left_valid = (((le != NULL) && (d->left != NULL) && prune_match(le, d->left)) &&
			  ((region_valid(lw, w, le->next, d->left->next)) ||
			   ((le->multi) && region_valid(lw, w, le, d->left->next)) ||
			   ((d->left->multi) && region_valid(lw, w, le->next, d->left)) ||
			   ((le->multi && d->left->multi) && region_valid(lw, w, le, d->left))));
	    right_valid = (((d->right != NULL) && (re != NULL) && prune_match(d->right, re)) &&
			   ((region_valid(w, rw, d->right->next,re->next)) ||
			    ((d->right->multi) && region_valid(w,rw,d->right,re->next))  ||
			    ((re->multi) && region_valid(w, rw, d->right->next, re)) ||
			    ((d->right->multi && re->multi) && region_valid(w, rw, d->right, re))));
	    
	    /* The following if statements could be restructured to avoid superfluous calls
	       to mark_region.  It didn't seem a high priority, so I didn't optimize this.
	       */
	    
	    if (left_valid && region_valid(w, rw, d->right, re)) {
		d->marked = TRUE;
		mark_region(w, rw, d->right, re);
		mark_region(lw, w, le->next, d->left->next);
		if (le->multi) mark_region(lw, w, le, d->left->next);
		if (d->left->multi) mark_region(lw, w, le->next, d->left);
		if (le->multi && d->left->multi) mark_region(lw, w, le, d->left);
	    }
	    
	    if (right_valid && region_valid(lw, w, le, d->left)) {
		d->marked = TRUE;
		mark_region(lw, w, le, d->left);
		mark_region(w, rw, d->right->next,re->next);
		if (d->right->multi) mark_region(w,rw,d->right,re->next);
		if (re->multi) mark_region(w, rw, d->right->next, re);
		if (d->right->multi && re->multi) mark_region(w, rw, d->right, re);
	    }
	    
	    if (left_valid && right_valid) {
		d->marked = TRUE;
		mark_region(lw, w, le->next, d->left->next);
		if (le->multi) mark_region(lw, w, le, d->left->next);
		if (d->left->multi) mark_region(lw, w, le->next, d->left);
		if (le->multi && d->left->multi) mark_region(lw, w, le, d->left);
		mark_region(w, rw, d->right->next,re->next);
		if (d->right->multi) mark_region(w,rw,d->right,re->next);
		if (re->multi) mark_region(w, rw, d->right->next, re);
		if (d->right->multi && re->multi) mark_region(w, rw, d->right, re);
	    }
	}
	put_match_list(m1);
    }
}

void conjunction_prune(void) {
    /*
       We've already built the sentence disjuncts, and we've pruned them
       and power_pruned(GENTLE) them also.  The sentence contains a
       conjunction.  deletable[][] has been initialized to indicate the
       ranges which may be deleted in the final linkage.
       
       This routine deletes irrelevant disjuncts.  It finds them by first
       marking them all as irrelevant, and then marking the ones that
       might be useable.  Finally, the unmarked ones are removed.
       
       */
    Disjunct * d, * d_head, * dx;
    int w;
    
    /* we begin by unmarking all disjuncts.  This would not be necessary if
       whenever we created a disjunct we cleared its marked field.
       I didn't want to search the program for all such places, so
       I did this way.
       */
    for (w=0; w<N_words; w++) {
	for (d=sentence[w].d; d != NULL; d=d->next) {
	    d->marked = FALSE;
	}
    }
    
    init_fast_matcher();
    init_table();
    
    for (d = sentence[0].d; d != NULL; d = d->next) {
	if ((d->left == NULL) && region_valid(0, N_words, d->right, NULL)) {
	    mark_region(0, N_words, d->right, NULL);
	    d->marked = TRUE;
	}
    }
    
    for (w=0; w<N_words; w++) {
	d_head = NULL;
	for (d=sentence[w].d; d != NULL; d=dx) {
	    dx = d->next;
	    if (d->marked) {
		d->next = d_head;
		d_head = d;
	    } else {
		d->next = NULL;
		free_disjuncts(d);
	    }
	}
	sentence[w].d = d_head;
    }
    
    free_fast_matcher();
    free_table();    
}
