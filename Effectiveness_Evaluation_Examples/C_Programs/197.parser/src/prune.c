 /***************************************************************************/
 /*                                                                         */
 /* This link grammar system is copyright (C) 1991-1997 by Daniel Sleator   */
 /* (sleator@cs.cmu.edu) and Davy Temperley.  This is work in progress.     */
 /* See http://www.cs.cmu.edu/~sleator for announcements of the latest      */
 /* version, detailed documentation, and rules for commercial use.          */
 /*                                                                         */
 /***************************************************************************/

#include "header.h"

/*

  The algorithms in this file prune disjuncts from the disjunct list
  of the sentence that can be elimininated by a simple checks.  The first
  check works as follows:

  A series of passes are made through the sentence, alternating
  left-to-right and right-to-left.  Consier the left-to-right pass (the
  other is symmetric).  A set S of connectors is maintained (initialized
  to be empty).  Now the disjuncts of the current word are processed.
  If a given disjunct's left pointing connectors have the property that
  at least one of them has no connector in S to which it can be matched,
  then that disjunct is deleted. Now the set S is augmented by the right
  connectors of the remaining disjuncts of that word.  This completes
  one word.  The process continues through the words from left to right.
  Alternate passes are made until no disjunct is deleted.

  It worries me a little that if there are some really huge disjuncts lists,
  then this process will probably do nothing.  (This fear turns out to be 
  unfounded.)

  Notes:  Power pruning will not work if applied before generating the
  "and" disjuncts.  This is because certain of it's tricks don't work.
  Think about this, and finish this note later....
  Also, currently I use the standard connector match procedure instead
  of the pruning one, since I know power pruning will not be used before 
  and generation.  Replace this to allow power pruning to work before
  generating and disjuncts.

  Currently it seems that normal pruning, power pruning, and generation,
  pruning, and power pruning (after "and" generation) and parsing take
  about the same amount of time.  This is why doing power pruning before
  "and" generation might be a very good idea.

  New idea:  Suppose all the disjuncts of a word have a connector of type
  c pointing to the right.  And further, suppose that there is exactly one
  word to its right containing that type of connector pointing to the left.
  Then all the other disjuncts on the latter word can be deleted.
  (This situation is created by the processing of "either...or", and by
  the extra disjuncts added to a "," neighboring a conjunction.)

*/


int prune_match(Connector *a, Connector *b) {
/* This is almost identical to match().  Its reason for existance
   is the rather subtle fact that with "and" can transform a "Ss"
   connector into "Sp".  This means that in order for pruning to
   work, we must allow a "Ss" connector on word match an "Sp" connector
   on a word to its right.  This is what this version of match allows.
   we assume that a is on a word to the left of b.
*/
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
#if defined PLURALIZATION	
/*
        if ((*(a->string)=='S') && ((*s=='s') || (*s=='p')) &&  (*t=='p')) {
	    return TRUE;
	}
*/
/*
   The above is a kludge to stop pruning from killing off disjuncts
   which (because of pluralization in and) might become valid later.
   Recall that "and" converts a singular subject into a plural one.
   The (*s=='p') part is so that "he and I are good" doesn't get killed off.
   The above hack is subsumed by the following one:
*/
	if ((*(a->string)=='S') && ((*s=='s') || (*s=='p')) &&
	    ((*t=='p') || (*t=='s')) &&
	    ((s-1 == a->string) || ((s-2 == a->string) && (*(s-1) == 'I')))){
	    return TRUE;
	}
/*
   This change is to accommodate "nor".  In particular we need to
   prevent "neither John nor I likes dogs" from being killed off.
   We want to allow this to apply to "are neither a dog nor a cat here"
   and "is neither a dog nor a cat here".  This uses the "SI" connector.
   The third line above ensures that the connector is either "S" or "SI".
*/
#endif	
	while ((*s!='\0') && (*t!='\0')) {
	    if ((*s == '*') || (*t == '*') ||
		((*s == *t) && (*s != '^'))) {
              /* this last case here is rather obscure.  It prevents
                 '^' from matching '^'.....Is this necessary?
		     ......yes, I think it is.   */
		s++;
		t++;
	    } else return FALSE;
	}
	return TRUE;
    } else if ((x==UP_priority) && (y==DOWN_priority)) {
	while ((*s!='\0') && (*t!='\0')) {
	    if ((*s == *t) || (*s == '*') || (*t == '^')) {
                /* that '^' should match on the DOWN_priority
		   node is subtle, but correct */
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

static int s_table_size;
static Connector ** table;

void free_S(void) {
/* This function removes all connectors from the set S */
    int i;
    for (i=0; i<s_table_size; i++) {
	if (table[i] == NULL) continue; /* a prehaps stupid optimization */
	free_connectors(table[i]);
	table[i] = NULL;
    }
}

int hash_S(Connector * c) {
/* This hash function only looks at the leading upper case letters of
   the connector string, and the label fields.  This ensures that if two
   strings match (formally), then they must hash to the same place.
*/
    char *s;
    int i;
    i = c->label;
    s = c->string;
    while(isupper(*s)) {
	i = i + (i<<1) + randtable[(*s + i) & (RTSIZE-1)];
	s++;
    }
    return (i & (s_table_size-1));
}

void insert_S(Connector * c) {
/* this function puts a copy of c into S if one like it isn't already there */
    int h;
    Connector * e;

    h = hash_S(c);

    for (e = table[h]; e != NULL; e = e->next) {
	if ((strcmp(c->string, e->string) == 0) &&
	    (c->label == e->label) && (c->priority == e->priority)) {
	    return;
	}
    }
    e = (Connector *) xalloc(sizeof(Connector)) ;
    *e = *c;
    e->next = table[h];
    table[h] = e;
}


void zero_S(void) {
    int i;
    for (i=0; i<s_table_size; i++) {
	table[i] = NULL;
    }
}

void init_S(Connector * c) {
/* put a copy of the the connector list c into S.  Assumes S is empty */
    int h;
    Connector *c1;
    for (; c!=NULL; c = c->next) {
	h = hash_S(c);
	c1 = (Connector *) xalloc(sizeof(Connector)) ;
	*c1 = *c;
	c1->next = table[h];
	table[h] = c1;
    }
}

int matches_S(Connector * c, int dir) {
/* returns TRUE if c can match anything in the set S */
/* because of the horrible kludge, prune match is assymetric, and   */
/* direction is '-' if this is an l->r pass, and '+' if an r->l pass.   */

    int h;
    Connector * e;

    h = hash_S(c);
    if (dir=='-') {
	for (e = table[h]; e != NULL; e = e->next) {
	    if (prune_match(e, c)) return TRUE;
	}
    } else {
	for (e = table[h]; e != NULL; e = e->next) {
	    if (prune_match(c, e)) return TRUE;
	}
    }
    return FALSE;
}

void clean_up(int w) {
/* This removes the disjuncts that are empty from the list corresponding
   to word w of the sentence.
*/
    Disjunct head_disjunct, *d, *d1;

    d = &head_disjunct;

    d->next = sentence[w].d;

    while(d->next != NULL) {
	if ((d->next->left == NULL) && (d->next->right == NULL)) {
	    d1 = d->next;
	    d->next = d1->next;
	    xfree((char *)d1, sizeof(Disjunct));
	} else {
	    d = d->next;
	}
    }
    sentence[w].d = head_disjunct.next;
}

int count_disjuncts(Disjunct * d) {
/* returns the number of disjuncts in the list pointed to by d */
    int count = 0;
    for (; d!=NULL; d=d->next) {
	count++;
    }
    return count;
}

int count_disjuncts_in_sentence(void) {
/* returns the total number of disjuncts in the sentence */
    int w, count;
    count = 0;
    for (w=0; w<N_words; w++) {
	count += count_disjuncts(sentence[w].d);
    }
    return count;
}

void prune(void) {
    int N_deleted;
    Disjunct *d;
    Connector *e;
    int w;

    s_table_size = next_power_of_two_up(count_disjuncts_in_sentence());
    table = (Connector **) xalloc(s_table_size * sizeof (Connector *));
/* You know, I don't think this makes much sense.  This is probably much  */
/* too big.  There are many fewer connectors than disjuncts.              */

    zero_S();
    N_deleted = 1;  /* a lie to make it always do at least 2 passes */

    for (;;) {
	/* left-to-right pass */

	for (w = 0; w < N_words; w++) {
	    for (d = sentence[w].d; d != NULL; d = d->next) {
		for (e = d->left; e != NULL; e = e->next) {
		    if (!matches_S(e, '-')) break;
		}
		if (e != NULL) {
		    /* we know this disjunct is dead */
		    N_deleted ++;
		    free_connectors(d->left);
		    free_connectors(d->right);
		    d->left = d->right = NULL;
		}
	    }
	    clean_up(w);
	    for (d = sentence[w].d; d != NULL; d = d->next) {
		for (e = d->right; e != NULL; e = e->next) {
		    insert_S(e);
		}
	    }
	}

	if (verbosity > 2) {
	    printf("l->r pass removed %d\n",N_deleted);
	    print_disjunct_counts();
	}
	free_S();
	if (N_deleted == 0) break;

	/* right-to-left pass */
	N_deleted = 0;
	for (w = N_words-1; w >= 0; w--) {
	    for (d = sentence[w].d; d != NULL; d = d->next) {
		for (e = d->right; e != NULL; e = e->next) {
		    if (!matches_S(e,'+')) break;
		}
		if (e != NULL) {
		    /* we know this disjunct is dead */
		    N_deleted ++;
		    free_connectors(d->left);
		    free_connectors(d->right);
		    d->left = d->right = NULL;
		}
	    }
	    clean_up(w);
	    for (d = sentence[w].d; d != NULL; d = d->next) {
		for (e = d->left; e != NULL; e = e->next) {
		    insert_S(e);
		}
	    }
	}
	if (verbosity > 2) {
	    printf("r->l pass removed %d\n",N_deleted);
	    print_disjunct_counts();
	}
	free_S();
	if (N_deleted == 0) break;
	N_deleted = 0;
    }
    xfree((char *)table, s_table_size * sizeof (Connector *));
}

/*
   The second algorithm eliminates disjuncts that are dominated by 
   another.  It works by hashing them all, and checking for domination.
*/

static int dup_table_size;
static Disjunct ** dup_table;

int string_hash(char * s, int i) {
/* hash function that takes a string and a seed value i */
    for(;*s != '\0';s++) i = i + (i<<1) + randtable[(*s + i) & (RTSIZE-1)];
    return (i & (dup_table_size-1));
}

#if FALSE

/*
  Consider the idea of deleting a disjunct if it is dominated (in terms of
  what it can match) by some other disjunct on the same word.  This has
  been implemented below.  There are three problems with it:

  (1) It is almost never the case that any disjuncts are eliminated.
      (The code below has works correctly with fat links, but because
      all of the fat connectors on a fat disjunct have the same matching
      string, the only time a disjuct will die is if it is the same
      as another one.  This is captured by the simplistic version below.

  (2) connector_matches_alam may not be exactly correct.  I don't
      think it does the fat link matches properly.   (See the comment
      in and.c for more information about matching fat links.)  This is
      irrelevant because of (1).
      
  (3) The linkage that is eliminated by this, might just be the one that
      passes post-processing, as the following example shows.
      This is pretty silly, and should probably be changed.

> telling John how our program works would be stupid 
Accepted (2 linkages, 1 with no P.P. violations)
  Linkage 1, cost vector = (0, 0, 7)

    +------------------G-----------------+          
    +-----R-----+----CL----+             |          
    +---O---+   |   +---D--+---S---+     +--I-+-AI-+
    |       |   |   |      |       |     |    |    |
telling.g John how our program.n works would be stupid 

               /////          CLg     <---CLg--->  CL        telling.g
 (g)           telling.g      G       <---G----->  G         would
 (g) (d)       telling.g      R       <---R----->  R         how
 (g) (d)       telling.g      O       <---O----->  O         John
 (g) (d)       how            CLe     <---CLe--->  CL        program.n
 (g) (d) (e)   our            D       <---Ds---->  Ds        program.n
 (g) (d) (e)   program.n      Ss      <---Ss---->  Ss        works
 (g)           would          I       <---Ix---->  Ix        be
 (g)           be             AI      <---AIi--->  AIi       stupid

(press return for another)
> 
  Linkage 2 (bad), cost vector = (0, 0, 7)

    +------------------G-----------------+          
    +-----R-----+----CL----+             |          
    +---O---+   |   +---D--+---S---+     +--I-+-AI-+
    |       |   |   |      |       |     |    |    |
telling.g John how our program.n works would be stupid 

               /////          CLg     <---CLg--->  CL        telling.g
 (g)           telling.g      G       <---G----->  G         would
 (g) (d)       telling.g      R       <---R----->  R         how
 (g) (d)       telling.g      O       <---O----->  O         John
 (g) (d)       how            CLe     <---CLe--->  CL        program.n
 (g) (d) (e)   our            D       <---Ds---->  Ds        program.n
 (g) (d) (e)   program.n      Ss      <---Ss---->  Ss        works
 (g)           would          I       <---Ix---->  Ix        be
 (g)           be             AI      <---AI---->  AI        stupid

P.P. violations:
        Special subject rule violated
*/

int connector_matches_alam(Connector * a, Connector * b) {
/* This returns true if the connector a matches everything that b
   matches, and possibly more.  (alam=at least as much)

   TRUE for equal connectors.
   remains TRUE if multi-match added to the first.
   remains TRUE if subsrcripts deleted from the first.

*/
    char * s, * t, *u;
    if (((!a->multi) && b->multi) ||
	(a->label != b->label) ||
	(a->priority != b->priority))  return FALSE;
    s = a->string;
    t = b->string;
    while(isupper(*s) || isupper(*t)) {
	if (*s == *t) {
	    s++;
	    t++;
	} else return FALSE;
    }
    if (a->priority == DOWN_priority) {
	u = s;
	s = t;
	t = u;
    }
    while((*s != '\0') && (*t != '\0')) {
	if ((*s == *t) || (*s == '*') || (*t == '^')) {
	    s++;
	    t++;
	} else return FALSE;
    }
    while ((*s != '\0') && (*s == '*')) s++;
    return (*s == '\0');
}

int connector_hash(Connector * c, int i) {
/* This hash function that takes a connector and a seed value i.
   It only looks at the leading upper case letters of
   the string, and the label.  This ensures that if two connectors
   match, then they must hash to the same place. 
*/
    char * s;
    s = c->string;

    i = i + (i<<1) + randtable[(c->label + i) & (RTSIZE-1)];
    while(isupper(*s)) {
	i = i + (i<<1) + randtable[(*s + i) & (RTSIZE-1)];
	s++;
    }
    return (i & (dup_table_size-1));
}

int hash_disjunct(Disjunct * d) {
/* This is a hash function for disjuncts */
    int i;
    Connector *e;
    i = 0;
    for (e = d->left ; e != NULL; e = e->next) {
	i = connector_hash(e, i);
    }
    for (e = d->right ; e != NULL; e = e->next) {
	i = connector_hash(e, i);
    }
    return string_hash(d->string, i);
}

int disjunct_matches_alam(Disjunct * d1, Disjunct * d2) {
/* returns TRUE if disjunct d1 can match anything that d2 can       */
/* if this happens, it constitutes a proof that there is absolutely */
/* no use for d2. */    
    Connector *e1, *e2;
    if (d1->cost > d2->cost) return FALSE;
    e1 = d1->left;
    e2 = d2->left;
    while((e1!=NULL) && (e2!=NULL)) {
	if (!connector_matches_alam(e1,e2)) break;
	e1 = e1->next;
	e2 = e2->next;
    }
    if ((e1!=NULL) || (e2!=NULL)) return FALSE;
    e1 = d1->right;
    e2 = d2->right;
    while((e1!=NULL) && (e2!=NULL)) {
	if (!connector_matches_alam(e1,e2)) break;
	e1 = e1->next;
	e2 = e2->next;
    }
    if ((e1!=NULL) || (e2!=NULL)) return FALSE;
    return (strcmp(d1->string, d2->string) == 0);
}

Disjunct * eliminate_duplicate_disjuncts(Disjunct * d) {
/* Takes the list of disjuncts pointed to by d, eliminates all
   duplicates, and returns a pointer to a new list.
   It frees the disjuncts that are eliminated.
*/
    int i, h, count;
    Disjunct *dn, *dx, *dxn, *front;
    count = 0;
    dup_table_size = next_power_of_two_up(2 * count_disjuncts(d));
    dup_table = (Disjunct **) xalloc(dup_table_size * sizeof(Disjunct *));
    for (i=0; i<dup_table_size; i++) dup_table[i] = NULL;
    for (;d!=NULL; d = dn) {
	dn = d->next;
	h = hash_disjunct(d);

	front = NULL;
	for (dx = dup_table[h]; dx!=NULL; dx=dxn) {
	    dxn = dx->next;
	    if (disjunct_matches_alam(dx,d)) {
		/* we know that d should be killed */
		d->next = NULL;
		free_disjuncts(d);
		count++;
		front = catenate_disjuncts(front, dx);
		break;
	    } else if (disjunct_matches_alam(d,dx)) {
		/* we know that dx should be killed off */
		dx->next = NULL;
		free_disjuncts(dx);
		count++;
	    } else {
		/* neither should be killed off */
		dx->next = front;
		front = dx;
	    }
	}
	if (dx == NULL) {
	    /* we put d in the table */
	    d->next = front;
	    front = d;
	}
	dup_table[h] = front;
    }
    /* d is now NULL */
    for (i=0; i<dup_table_size; i++) {
	for (dx = dup_table[i]; dx != NULL; dx = dxn) {
	    dxn = dx->next;
	    dx->next = d;
	    d = dx;
	}
    }
    xfree((char *) dup_table, dup_table_size * sizeof(Disjunct *));
    if ((verbosity > 2)&&(count != 0)) printf("killed %d duplicates\n",count);
    return d;
}

#endif

/*
   Here is the old version that doesn't check for domination, just
   equality.
*/

int old_hash_disjunct(Disjunct * d) {
/* This is a hash function for disjuncts */
    int i;
    Connector *e;
    i = 0;
    for (e = d->left ; e != NULL; e = e->next) {
	i = string_hash(e->string, i);
    }
    for (e = d->right ; e != NULL; e = e->next) {
	i = string_hash(e->string, i);
    }
    return string_hash(d->string, i);
}

int connectors_equal_prune(Connector *c1, Connector *c2) {
/* The connectors must be exactly equal.  A similar function
   is connectors_equal_AND(), but that ignores priorities,
   this does not.
*/
    return (c1->label == c2->label) &&
	   (c1->multi == c2->multi) &&
	   (c1->priority == c2->priority) &&
           (strcmp(c1->string, c2->string) == 0);
}

int disjuncts_equal(Disjunct * d1, Disjunct * d2) {
/* returns TRUE if the disjuncts are exactly the same */
    Connector *e1, *e2;
    e1 = d1->left;
    e2 = d2->left;
    while((e1!=NULL) && (e2!=NULL)) {
	if (!connectors_equal_prune(e1,e2)) break;
	e1 = e1->next;
	e2 = e2->next;
    }
    if ((e1!=NULL) || (e2!=NULL)) return FALSE;
    e1 = d1->right;
    e2 = d2->right;
    while((e1!=NULL) && (e2!=NULL)) {
	if (!connectors_equal_prune(e1,e2)) break;
	e1 = e1->next;
	e2 = e2->next;
    }
    if ((e1!=NULL) || (e2!=NULL)) return FALSE;
    return (strcmp(d1->string, d2->string) == 0);
}

Disjunct * eliminate_duplicate_disjuncts(Disjunct * d) {
/* Takes the list of disjuncts pointed to by d, eliminates all
   duplicates, and returns a pointer to a new list.
   It frees the disjuncts that are eliminated.
*/
    int i, h, count;
    Disjunct *dn, *dx;
    count = 0;
    dup_table_size = next_power_of_two_up(2 * count_disjuncts(d));
    dup_table = (Disjunct **) xalloc(dup_table_size * sizeof(Disjunct *));
    for (i=0; i<dup_table_size; i++) dup_table[i] = NULL;
    while (d!=NULL) {
	dn = d->next;
	h = old_hash_disjunct(d);

	for (dx = dup_table[h]; dx!=NULL; dx=dx->next) {
	    if (disjuncts_equal(dx, d)) break;
	}
	if (dx==NULL) {
	    d->next = dup_table[h];
	    dup_table[h] = d;
	} else {
	    d->next = NULL;  /* to prevent it from freeing the whole list */
	    if (d->cost < dx->cost) dx->cost = d->cost;
	    free_disjuncts(d);
	    count++;
	}
	d = dn;
    }
    /* d is already null */
    for (i=0; i<dup_table_size; i++) {
	for (dn = dup_table[i]; dn != NULL; dn = dx) {
	    dx = dn->next;
	    dn->next = d;
	    d = dn;
	}
    }
    xfree((char *) dup_table, dup_table_size * sizeof(Disjunct *));
    if ((verbosity > 2)&&(count != 0)) printf("killed %d duplicates\n",count);
    return d;
}


/* Here is expression pruning.  This is done even before the expressions
   are turned into lists of disjuncts.

   This uses many of the same data structures and functions that are used
   by prune.
*/

int size_of_sentence_expressions(void) {
/* Computes and returns the number of connectors in all of the expressions 
   of the sentence.
*/
    X_node * x;
    int w, size;
    size = 0;
    for (w=0; w<N_words; w++) {
	for (x=sentence[w].x; x!=NULL; x = x->next) {
	    size += size_of_expression(x->exp);
	}
    }
    return size;
}

/* The purge operations remove all irrelevant stuff from the expression,    */
/* and free the purged stuff.  A connector is deemed irrelevant if its      */
/* string pointer has been set to NULL.  The passes through the sentence    */
/* have the job of doing this.                                              */

/* If an OR or AND type expression node has one child, we can replace it by */
/* its child.  This, of course, is not really necessary                     */

int and_purge_E_list(E_list * l);
E_list * or_purge_E_list(E_list * l);

Exp* purge_Exp(Exp *e) {
/* Must be called with a non-null expression                                */
/* Return NULL iff the expression has no disjuncts.                         */
/*  Exp * ne; */

    if (e->type == CONNECTOR_type) {
	if (e->u.string == NULL) {
	    xfree((char *)e, sizeof(Exp));
	    return NULL;
	} else {
	    return e;
	}
    }
    if (e->type == AND_type) {
	if (and_purge_E_list(e->u.l) == 0) {
	    xfree((char *)e, sizeof(Exp));
	    return NULL;
	}
    } else {
	e->u.l = or_purge_E_list(e->u.l);
	if (e->u.l == NULL) {
	    xfree((char *)e, sizeof(Exp));
	    return NULL;
	}
    }

/* This code makes it kill off nodes that have just one child
   (1) It's going to give an insignificant speed-up
   (2) Costs have not been handled correctly here.
   The code is excised for these reasons.
*/
/*  
    if ((e->u.l != NULL) && (e->u.l->next == NULL)) { 
	ne = e->u.l->e;
	xfree((char *) e->u.l, sizeof(E_list));
	xfree((char *) e, sizeof(Exp));
	return ne;
    }
*/    
    return e;
}

int and_purge_E_list(E_list * l) {
/* Returns 0 iff the length of the disjunct list is 0.          */
/* If this is the case, it frees the structure rooted at l.     */
    if (l == NULL) return 1;
    if ((l->e = purge_Exp(l->e)) == NULL) {
	free_E_list(l->next);
	xfree((char *)l, sizeof(E_list));
	return 0;
    }
    if (and_purge_E_list(l->next) == 0) {
	free_Exp(l->e);
	xfree((char *)l, sizeof(E_list));
	return 0;
    }
    return 1;
}

E_list * or_purge_E_list(E_list * l) {
/* get rid of the elements with null expressions */
    E_list * el;
    if (l == NULL) return NULL;
    if ((l->e = purge_Exp(l->e)) == NULL) {
	el = or_purge_E_list(l->next);
	xfree((char *)l, sizeof(E_list));
	return el;
    }
    l->next = or_purge_E_list(l->next);
    return l;
}

int mark_dead_connectors(Exp * e, int dir) {
/* Mark as dead all of the dir-pointing connectors
   in e that are not matched by anything in the current set.
   Returns the number of connectors so marked.
*/
    Connector dummy;
    int count;
    E_list *l;
    dummy.label = NORMAL_LABEL;
    dummy.priority = THIN_priority;
    count = 0;
    if (e->type == CONNECTOR_type) {
	if (e->dir == dir) {
	    dummy.string = e->u.string;
	    if (!matches_S(&dummy,dir)) {
		e->u.string = NULL;
		count++;
	    }
	}
    } else {
	for (l=e->u.l; l!=NULL; l=l->next) {
	    count += mark_dead_connectors(l->e, dir);
	}
    }
    return count;
}

void insert_connectors(Exp * e, int dir) {
/* Put into the set S all of the dir-pointing connectors still in e.    */
    Connector dummy;
    E_list *l;
    dummy.label = NORMAL_LABEL;
    dummy.priority = THIN_priority;
    if (e->type == CONNECTOR_type) {
	if (e->dir == dir) {
	    dummy.string = e->u.string;
	    insert_S(&dummy);
	}
    } else {
	for (l=e->u.l; l!=NULL; l=l->next) {
	    insert_connectors(l->e, dir);
	}
    }
}

void clean_up_expressions(int w) {
/* This removes the expressions that are empty from the list corresponding
   to word w of the sentence.
*/
    X_node head_node, *d, *d1;
    d = &head_node;
    d->next = sentence[w].x;
    while(d->next != NULL) {
	if (d->next->exp == NULL) {
	    d1 = d->next;
	    d->next = d1->next;
	    xfree((char *)d1, sizeof(X_node));
	} else {
	    d = d->next;
	}
    }
    sentence[w].x = head_node.next;
}

void expression_prune(void){
    int N_deleted;
    X_node * x;
    int w;

    s_table_size = next_power_of_two_up(size_of_sentence_expressions());
    table = (Connector **) xalloc(s_table_size * sizeof (Connector *));

    zero_S();
    N_deleted = 1;  /* a lie to make it always do at least 2 passes */

    for (;;) {
	/* left-to-right pass */
	for (w = 0; w < N_words; w++) {
	    for (x = sentence[w].x; x != NULL; x = x->next) {
/*     printf("before marking: "); print_expression(x->exp); printf("\n"); */
		N_deleted += mark_dead_connectors(x->exp, '-');
/*     printf("after marking marking: "); print_expression(x->exp); printf("\n"); */
	    }
	    for (x = sentence[w].x; x != NULL; x = x->next) {
/*     printf("before purging: "); print_expression(x->exp); printf("\n"); */
		x->exp = purge_Exp(x->exp);
/*     printf("after purging: "); print_expression(x->exp); printf("\n"); */
	    }
	    clean_up_expressions(w);  /* gets rid of X_nodes with NULL exp */
	    for (x = sentence[w].x; x != NULL; x = x->next) {
		insert_connectors(x->exp,'+');
	    }
	}

	if (verbosity > 2) {
	    printf("l->r pass removed %d\n",N_deleted);
	    print_expression_sizes();
	}

	free_S();
	if (N_deleted == 0) break;

	/* right-to-left pass */
	N_deleted = 0;
	for (w = N_words-1; w >= 0; w--) {
	    for (x = sentence[w].x; x != NULL; x = x->next) {
/*     printf("before marking: "); print_expression(x->exp); printf("\n"); */
		N_deleted += mark_dead_connectors(x->exp, '+');
/*     printf("after marking: "); print_expression(x->exp); printf("\n"); */
	    }
	    for (x = sentence[w].x; x != NULL; x = x->next) {
/*     printf("before perging: "); print_expression(x->exp); printf("\n"); */
		x->exp = purge_Exp(x->exp);
/*     printf("after perging: "); print_expression(x->exp); printf("\n"); */
	    }
	    clean_up_expressions(w);  /* gets rid of X_nodes with NULL exp */
	    for (x = sentence[w].x; x != NULL; x = x->next) {
		insert_connectors(x->exp, '-');
	    }
	}

	if (verbosity > 2) {
	    printf("r->l pass removed %d\n",N_deleted);
	    print_expression_sizes();
	}
	free_S();
	if (N_deleted == 0) break;
	N_deleted = 0;
    }
    xfree((char *)table, s_table_size * sizeof (Connector *));
}



/*
  Here is what you've been waiting for: POWER-PRUNE

  The kinds of constraints it checks for are the following:

    1) successive connectors on the same disjunct have to go to
       nearer and nearer words.

    2) two deep connectors cannot attach to eachother
       (A connectors is deep if it is not the first in its list, it
       is shallow if it is the first in its list, it is deepest if it
       is the last on its list.)

    3) on two adjacent words, a pair of connectors can be used
       only if they're the deepest ones on their disjuncts

    4) on two non-adjacent words, a pair of connectors can be used only
       if not [both of them are the deepest].

   The data structure consists of a pair of hash tables on every word.
   Each bucket of a hash table has a list of pointers to connectors.
   These nodes also store if the chosen connector is shallow.
*/
typedef struct c_list_struct C_list;
struct c_list_struct {
    Connector * c;
    int shallow;
    C_list * next;
};
/*
   As with normal pruning, we make alternate left->right and right->left
   passes.  In the R->L pass, when we're on a word w, we make use of
   all the left-pointing hash tables on the words to the right of w.
   After the pruning on this word, we build the left-pointing hash table
   this word.  This guarantees idempotence of the pass -- after doing an
   L->R, doing another would change nothing.

   Each connector has an integer c_word field.  This refers to the closest
   word that it could be connected to.  These are initially determined by
   how deep the connector is.  For example, a deepest connector can connect
   to the neighboring word, so its c_word field is w+1 (w-1 if this is a left
   pointing connector).  It's neighboring shallow connector has a c_word
   value of w+2, etc.

   The pruning process adjusts these c_word values as it goes along,
   accumulating information about any way of linking this sentence.
   The pruning process stops only after no disjunct is deleted and no
   c_word values change.
*/

static int power_cost;
static int power_prune_mode;  /* either GENTLE or RUTHLESS */
                              /* obviates excessive paramater passing */

int left_connector_count(Disjunct * d) {
/* returns the number of connectors in the left lists of the disjuncts. */
    Connector *c;
    int i=0;
    for (;d!=NULL; d=d->next) {
	for (c = d->left; c!=NULL; c = c->next) i++;
    }
    return i;
}
int right_connector_count(Disjunct * d) {
    Connector *c;
    int i=0;
    for (;d!=NULL; d=d->next) {
      for (c = d->right; c!=NULL; c = c->next) i++;
    }
    return i;
}

#define BAD_WORD (MAX_SENTENCE+1)
   /* the indiction in a word field that this connector cannot
      be used -- is obsolete.
   */

static int l_table_size[MAX_SENTENCE];  /* the sizes of the hash tables */
static int r_table_size[MAX_SENTENCE];

static C_list ** l_table[MAX_SENTENCE];
                 /* the beginnings of the hash tables */
static C_list ** r_table[MAX_SENTENCE];

void free_C_list(C_list * t) {
    C_list *xt;
    for (; t!=NULL; t=xt) {
	xt = t->next;
	xfree((char *)t, sizeof(C_list));
    }
}

void free_power_tables(void) {
/* free all of the hash tables and C_lists */
    int w;
    int i;
    for (w=0; w<N_words; w++) {
	for (i=0; i<l_table_size[w]; i++) {
	    free_C_list(l_table[w][i]);
	}
	xfree((char *)l_table[w], l_table_size[w] * sizeof (C_list *));
	for (i=0; i<r_table_size[w]; i++) {
	    free_C_list(r_table[w][i]);
	}
	xfree((char *)r_table[w], r_table_size[w] * sizeof (C_list *));
    }
}

int power_hash(Connector * c) {
/* This hash function only looks at the leading upper case letters of
   the connector string, and the label fields.  This ensures that if two
   strings match (formally), then they must hash to the same place.
   The answer must be masked to the appropriate table size.

   This is exactly the same hash function used in fast-match.
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

void put_into_power_table(int size, C_list ** t, Connector * c, int shal ) {
/* The disjunct d (whose left or right pointer points to c) is put
   into the appropriate hash table
*/
    int h;
    C_list * m;
    h = power_hash(c) & (size-1);
    m = (C_list *) xalloc (sizeof(C_list));
    m->next = t[h];
    t[h] = m;
    m->c = c;
    m->shallow = shal;
}

int set_dist_fields(Connector * c, int w, int delta) {
    int i;
    if (c==NULL) return w;
    i = set_dist_fields(c->next, w, delta) + delta;
    c->word = i;
    return i;
}

void init_power(void) {
/* allocates and builds the initial power hash tables */
    int w, len, size, i;
    C_list ** t;
    Disjunct * d, * xd, * head;
    Connector * c;
   /* first we initialize the word fields of the connectors, and
      eliminate those disjuncts with illegal connectors */
    for (w=0; w<N_words; w++) {
      head = NULL;
      for (d=sentence[w].d; d!=NULL; d=xd) {
          xd = d->next;
          if ((set_dist_fields(d->left, w, -1) < 0) ||
              (set_dist_fields(d->right, w, 1) >= N_words)) {
              d->next = NULL;
              free_disjuncts(d);
          } else {
              d->next = head;
              head = d;
          }
      }
      sentence[w].d = head;
    }

    for (w=0; w<N_words; w++) {
	len = left_connector_count(sentence[w].d);
	size = next_power_of_two_up(len);
	l_table_size[w] = size;
	t = l_table[w] = (C_list **) xalloc(size * sizeof(C_list *));
	for (i=0; i<size; i++) t[i] = NULL;

	for (d=sentence[w].d; d!=NULL; d=d->next) {
	    c = d->left;
	    if (c != NULL) {
		put_into_power_table(size, t, c, TRUE);
		for (c=c->next; c!=NULL; c=c->next){
		    put_into_power_table(size, t, c, FALSE);
		}
	    }
	}

	len = right_connector_count(sentence[w].d);
	size = next_power_of_two_up(len);
	r_table_size[w] = size;
	t = r_table[w] = (C_list **) xalloc(size * sizeof(C_list *));
	for (i=0; i<size; i++) t[i] = NULL;

	for (d=sentence[w].d; d!=NULL; d=d->next) {
	    c = d->right;
	    if (c != NULL) {
		put_into_power_table(size, t, c, TRUE);
		for (c=c->next; c!=NULL; c=c->next){
		    put_into_power_table(size, t, c, FALSE);
		}
	    }
	}
    }
}

void clean_table(int size, C_list ** t) {
/* This runs through all the connectors in this table, and eliminates those
   who are obsolete.  The word fields of an obsolete one has been set to
   BAD_WORD.
*/
    int i;
    C_list * m, * xm, * head;
    for (i=0; i<size; i++) {
	head = NULL;
	for (m=t[i]; m!=NULL; m=xm) {
	    xm = m->next;
	    if (m->c->word != BAD_WORD) {
		m->next = head;
		head = m;
	    } else {
		xfree((char *) m, sizeof(C_list));
	    }
	}
	t[i] = head;
    }
}

int possible_connection(Connector *lc, Connector *rc,
                      int lshallow, int rshallow,
                      int lword, int rword) {
/* this takes two connectors (and whether these are shallow or not)
   (and the two words that these came from) and returns TRUE if it is
   possible for these two to match based on local considerations.
*/
    if ((!lshallow) && (!rshallow)) return FALSE;
      /* two deep connectors can't work */
    if ((lc->word > rword) || (rc->word < lword)) return FALSE;
      /* word range constraints */
    if (power_prune_mode == RUTHLESS) {
	if (lword == rword-1) {
	    if (!((lc->next == NULL) && (rc->next == NULL))) return FALSE;
	} else {
	    if ((!null_links) &&
		(lc->next == NULL) && (rc->next == NULL) && (!lc->multi) && (!rc->multi)) {
		return FALSE;
	    }
	}
	return match(lc, rc);
    } else {
	if (lword == rword-1) {
	    if (!((lc->next == NULL) && (rc->next == NULL))) return FALSE;
	} else {
	    if ((!null_links) &&
		(lc->next == NULL) && (rc->next == NULL) && (!lc->multi) && (!rc->multi) &&
		!deletable[lword][rword]) {
		return FALSE;
	    }
	}
	return prune_match(lc, rc);
    }
}


int right_table_search(int w, Connector *c, int shallow, int word_c) {
/* this returns TRUE if the right table of word w contains
   a connector that can match to c.  shallow tells if c is shallow
*/
    int size, h;
    C_list *cl;
    size = r_table_size[w];
    h = power_hash(c) & (size-1);
    for (cl = r_table[w][h]; cl!=NULL; cl = cl->next) {
        if (possible_connection(cl->c, c, cl->shallow, shallow, w, word_c)) {
            return TRUE;
        }
    }
    return FALSE;
}

int left_table_search(int w, Connector *c, int shallow, int word_c) {
/* this returns TRUE if the right table of word w contains
   a connector that can match to c.  shallows tells if c is shallow
*/
    int size, h;
    C_list *cl;
    size = l_table_size[w];
    h = power_hash(c) & (size-1);
    for (cl = l_table[w][h]; cl!=NULL; cl = cl->next) {
      if (possible_connection(c, cl->c, shallow, cl->shallow, word_c, w)) {
          return TRUE;
      }
    }
    return FALSE;
}

static int N_changed;   /* counts the number of changes
			   of c->word fields in a pass */

int ok_cwords(Connector *c){
    for (; c != NULL; c=c->next) {
	if (c->word == BAD_WORD) return FALSE;
	if (c->word >= N_words) return FALSE;
    }
    return TRUE;
}

int left_connector_list_update(Connector *c, int word_c, int w, int shallow) {
/* take this connector list, and try to match it with the words
   w-1, w-2, w-3...Returns the word to which the first connector of the
   list could possibly be matched.  If c is NULL, returns w.  If there
   is no way to match this list, it returns a negative number.
   If it does find a way to match it, it updates the c->word fields
   correctly.
*/
    int n;
    int foundmatch;

    if (c==NULL) return w;
    n = left_connector_list_update(c->next, word_c, w, FALSE) - 1;
    if (((int) c->word) < n) n = c->word;

    /* n is now the rightmost word we need to check */
    foundmatch = FALSE;
    for (; (n >= 0) && ((w-n) <= maxlinklength); n--) {
	power_cost++;
	if (right_table_search(n, c, shallow, word_c)) {
	    foundmatch = TRUE;
	    break;
	}
    }
    if (n < ((int) c->word)) {
	c->word = n;
	N_changed++;
    }
    return (foundmatch ? n : -1);
}

int right_connector_list_update(Connector *c, int word_c, int w, int shallow) {
/* take this connector list, and try to match it with the words
   w+1, w+2, w+3...Returns the word to which the first connector of the
   list could possibly be matched.  If c is NULL, returns w.  If there
   is no way to match this list, it returns a number greater than N_words-1
   If it does find a way to match it, it updates the c->word fields
   correctly.
*/
    int n;
    int foundmatch;

    if (c==NULL) return w;
    n = right_connector_list_update(c->next, word_c, w, FALSE) + 1;
    if (c->word > n) n = c->word;

    /* n is now the leftmost word we need to check */
    foundmatch = FALSE;
    for (; (n < N_words) && ((n-w) <= maxlinklength); n++) {
	power_cost++;
	if (left_table_search(n, c, shallow, word_c)) {
	    foundmatch = TRUE;
	    break;
	}
    }
    if (n > c->word) {
	c->word = n;
	N_changed++;
    }
    return (foundmatch ? n : N_words);
}

void power_prune(int mode) {
    Disjunct *d, *free_later, *dx, *nd;
    Connector *c;
    int w, N_deleted;

    power_prune_mode = mode; /* this global variable avoids lots of
				parameter passing */
    init_power();
    power_cost = 0;
    free_later = NULL;
    N_changed = 1;  /* forces it always to make at least two passes */
    N_deleted = 0;

    for (;;) {
	/* left-to-right pass */
	
	for (w = 0; w < N_words; w++) {
	    for (d = sentence[w].d; d != NULL; d = d->next) {
		if (d->left == NULL) continue;
		if (left_connector_list_update(d->left, w, w, TRUE) < 0) {
		    for (c=d->left  ;c!=NULL; c = c->next) c->word = BAD_WORD;
		    for (c=d->right ;c!=NULL; c = c->next) c->word = BAD_WORD;
		    N_deleted++;
		}
	    }
	    
	    clean_table(r_table_size[w], r_table[w]);
	    nd = NULL;
	    for (d = sentence[w].d; d != NULL; d = dx) {
		dx = d->next;
		if ((d->left != NULL) && (d->left->word == BAD_WORD)) {
		    d->next = free_later;
		    free_later = d;
		} else {
		    d->next = nd;
		    nd = d;
		}
	    }
	    sentence[w].d = nd;
	}
	if (verbosity > 2) {
	   printf("l->r pass changed %d and deleted %d\n",N_changed,N_deleted);
	}

	if (N_changed == 0) break;
	
	N_changed = N_deleted = 0;
	/* right-to-left pass */
	
	for (w = N_words-1; w >= 0; w--) {
	    for (d = sentence[w].d; d != NULL; d = d->next) {
		if (d->right == NULL) continue;
		if (right_connector_list_update(d->right,w,w,TRUE) >= N_words){
		    for (c=d->right;c!=NULL; c = c->next) c->word = BAD_WORD;
		    for (c=d->left ;c!=NULL; c = c->next) c->word = BAD_WORD;
		    N_deleted++;
		}
	    }
	    clean_table(l_table_size[w], l_table[w]);
	    nd = NULL;
	    for (d = sentence[w].d; d != NULL; d = dx) {
		dx = d->next;
		if ((d->right != NULL) && (d->right->word == BAD_WORD)) {
		    d->next = free_later;
		    free_later = d;
		} else {
		    d->next = nd;
		    nd = d;
		}
	    }
	    sentence[w].d = nd;
	}
	
	if (verbosity > 2) {
	   printf("r->l pass changed %d and deleted %d\n",N_changed,N_deleted);
	}

	if (N_changed == 0) break;
	N_changed = N_deleted = 0;
    }
    free_disjuncts(free_later);
    free_power_tables();
    if (verbosity > 2) printf("%d power prune cost:\n", power_cost);
}
