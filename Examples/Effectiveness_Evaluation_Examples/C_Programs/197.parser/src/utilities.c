 /***************************************************************************/
 /*                                                                         */
 /* This link grammar system is copyright (C) 1991-1997 by Daniel Sleator   */
 /* (sleator@cs.cmu.edu) and Davy Temperley.  This is work in progress.     */
 /* See http://www.cs.cmu.edu/~sleator for announcements of the latest      */
 /* version, detailed documentation, and rules for commercial use.          */
 /*                                                                         */
 /***************************************************************************/

#include "header.h"

/* This file contains certain general utilities. */

void free_connectors(Connector *e) {
/* free the list of connectors pointed to by e
   (does not free any strings) 
*/
    Connector * n;
    for(;e != NULL; e = n) {
	n = e->next;
	xfree((char *)e, sizeof(Connector));
    }
}

void free_disjuncts(Disjunct *c) {
/* free the list of disjuncts pointed to by c
   (does not free any strings) 
*/
    Disjunct *c1;
    for (;c != NULL; c = c1) {
	c1 = c->next;
	free_connectors(c->left);
	free_connectors(c->right);
	xfree((char *)c, sizeof(Disjunct));
    }
}

void free_X_nodes(X_node * x) {
/* frees the list of X_nodes pointed to by x, and all of the expressions */
    X_node * y;
    for (; x!= NULL; x = y) {
	y = x->next;
	free_Exp(x->exp);
	xfree((char *)x, sizeof(X_node));
    }
}

void free_E_list(E_list *);
void free_Exp(Exp * e) {
    if (e->type != CONNECTOR_type) {
	free_E_list(e->u.l);
    }
    xfree((char *)e, sizeof(Exp));
}

void free_E_list(E_list * l) {
    if (l == NULL) return;
    free_E_list(l->next);
    free_Exp(l->e);
    xfree((char *)l, sizeof(E_list));
}

int size_of_expression(Exp * e) {
/* Returns the number of connectors in the expression e */
    int size;
    E_list * l;
    if (e->type == CONNECTOR_type) return 1;
    size = 0;
    for (l=e->u.l; l!=NULL; l=l->next) {
	size += size_of_expression(l->e);
    }
    return size;
}

unsigned int randtable[RTSIZE];

/* There is a legitimate question of whether having the hash function    */
/* depend on a large array is a good idea.  It might not be fastest on   */
/* a machine that depends on caching for its efficiency.  On the other   */
/* hand, Phong Vo's hash (and probably other linear-congruential) is     */
/* pretty bad.  So, mine is a "competitive" hash function -- you can't   */
/* make it perform horribly.                                             */

#if ! defined FOR_RELEASE
void init_randtable(void) {
    int i;
    srandom(10);
    for (i=0; i<RTSIZE; i++) {
	randtable[i] = random();
    }
}
#else
void init_randtable(void) {
    int i;
    srand(10);
    for (i=0; i<RTSIZE; i++) {
	randtable[i] = rand();
    }
}
#endif

/* Build a copy of the given expression (don't copy strings, of course) */
E_list * copy_E_list(E_list * l);
Exp * copy_Exp(Exp * e) {
    Exp * n;
    if (e == NULL) return NULL;
    n = (Exp *) xalloc(sizeof(Exp));
    *n = *e;
    if (e->type != CONNECTOR_type) {
	n->u.l = copy_E_list(e->u.l);
    }
    return n;
}

E_list * copy_E_list(E_list * l) {
    E_list * nl;
    if (l == NULL) return NULL;
    nl = (E_list *) xalloc(sizeof(E_list));
    *nl = *l;    /* not necessary -- both fields will be built below */
    nl->next = copy_E_list(l->next);
    nl->e = copy_Exp(l->e);
    return nl;
}

Connector * copy_connectors(Connector * c) {
/* This builds a new copy of the connector list pointed to by c.
   Strings, as usual, are not copied.
*/
    Connector *c1;
    if (c == NULL) return NULL;
    c1 = (Connector *) xalloc(sizeof(Connector));
    *c1 = *c;
    c1->next = copy_connectors(c->next);
    return c1;
}

Disjunct * copy_disjunct(Disjunct * d) {
/* This builds a new copy of the disjunct pointed to by d (except for the
   next field which is set to NULL).  Strings, as usual,
   are not copied.
*/
    Disjunct * d1;
    if (d == NULL) return NULL;
    d1 = (Disjunct *) xalloc(sizeof(Disjunct));
    *d1 = *d;
    d1->next = NULL;
    d1->left = copy_connectors(d->left);
    d1->right = copy_connectors(d->right);
    return d1;
}

typedef struct string_node_struct String_node;
struct string_node_struct {
    char * string;
    int size;
    String_node * next;
};

static String_node * string_list = NULL;

void free_this_string_later(char * s, int size) {
    String_node * sn;
    sn = (String_node *) xalloc(sizeof(String_node));
    sn->next = string_list;
    string_list = sn;
    sn->string = s;
    sn->size = size;
}

void free_strings(void) {
    String_node * sn;
    for (; string_list != NULL; string_list = sn) {
	sn = string_list->next;
	xfree((char *) string_list->string, string_list->size);
	xfree((char *) string_list, sizeof(String_node));
    }
}

Disjunct * catenate_disjuncts(Disjunct *d1, Disjunct *d2) {
/* Destructively catenates the two disjunct lists d1 followed by d2. */
/* Doesn't change the contents of the disjuncts */
/* Traverses the first list, but not the second */    
    Disjunct * dis = d1;

    if (d1 == NULL) return d2;
    if (d2 == NULL) return d1;
    while (dis->next != NULL) dis = dis->next;
    dis->next = d2;
    return d1;
}

X_node * catenate_X_nodes(X_node *d1, X_node *d2) {
/* Destructively catenates the two disjunct lists d1 followed by d2. */
/* Doesn't change the contents of the disjuncts */
/* Traverses the first list, but not the second */    
    X_node * dis = d1;

    if (d1 == NULL) return d2;
    if (d2 == NULL) return d1;
    while (dis->next != NULL) dis = dis->next;
    dis->next = d2;
    return d1;
}

int next_power_of_two_up(int i) {
/* Returns the smallest power of two that is at least i and at least 1 */
    int j=1;
    while(j<i) j = j<<1;
    return j;
}

int upper_case_match(char *s, char *t) {
/* returns TRUE if the initial upper case letters of s and t match */
    while(isupper(*s) || isupper(*t)) {
	if (*s != *t) return FALSE;
	s++;
	t++;
    }
    return (!isupper(*s) && !isupper(*t));
}

void left_print_string(FILE * fp, char * s, char * t) {
/* prints s then prints the last |t|-|s| characters of t.
   if s is longer than t, it truncates s.
*/
    int i, j, k;
    j = strlen(t);
    k = strlen(s);
    for (i=0; i<j; i++) {
	if (i<k) {
	    fprintf(fp, "%c", s[i]);
	} else {
	    fprintf(fp, "%c", t[i]);
	}
    }
}
