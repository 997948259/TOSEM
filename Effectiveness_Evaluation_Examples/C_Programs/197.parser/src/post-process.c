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
   This file does the post-processing.  The input is a global array
   called "pp_link_array" whose length is the global "N_links".
   The main routine is "post_process()".  It uses the link names only,
   and not the connectors.  (Since this is now taking a significant
   fraction of total parsing time, it should be rewritten to use hashing
   instead of linear search (in the arrays of pointers to strings, see
   below).)
   
   A domain is a set of links.  Each domain has a defining link.
   Only certain types of links serve to define a domain.  These
   parameters are set by the lists of link names below.

   The domains are nested: given two domains, either they're disjoint,
   or one contains the other, i.e. they're tree structured.  The set of links
   in a domain (but in no smaller domain) are called the "group" of the
   domain.  Data structures are built to store all this stuff.
   The tree structured property is not mathematically guaranteed by
   the domain construction algorithm.  Davy simply claims that because
   of how he built the dictionary, the domains will always be so
   structured.  The program checks this and gives an error message
   if it's violated.

   Define the "root word" of a link (or domain) to be the word at the
   left end of the link.  The other end of the defining link is called
   the "right word".
   
   The domain corresponding to a link is defined to be the set of links
   reachable by starting from the right word, following links and never
   using the root word or any word to its left.

   There are some minor exceptions to this.  The "restricted_link" lists
   those connectors that, even if they point back before the root word,
   are included in the domain.  Some of the starting links are included
   in their domain, these are listed in the "domain_contains_links" list.

   Such was the way it was.  Now Davy tells me there should be another type
   of domain that's quite different.  Let's call these "urfl" domains.
   Certain type of connectors start urfl domains.  They're listed below.
   In a urfl domain, the search includes the root word.  It does a separate
   search to find urfl domains.

   Restricted links should work just as they do with ordinary domains. If they
   come out of the right word, or anything to the right of it (that's
   in the domain), they should be included but should not be traced
   further. If they come out of the root word, they should not be
   included.
*/   

/*
   I also, unfortunately, want to propose a new type of domain. These
   would include everything that can be reached from the root word of the
   link, to the right, that is closer than the right word of the link.
   (They would not include the link itself.)

   In the following sentence, then, the "Urfl_Only Domain" of the G link
   would include only the "O" link:

      +-----G----+    
      +---O--+   +-AI+
      |      |   |   |
   hitting dogs is fun.a 

   In the following sentence it would include the "O", the "TT", the "I",
   the second "O", and the "A".

      +----------------G---------------+    
      +-----TT-----+  +-----O-----+    |    
      +---O---+    +-I+    +---A--+    +-AI+
      |       |    |  |    |      |    |   |
   telling people to do stupid things is fun.a 

   This would allow us to judge the following:

           kicking dogs bores me
           *kicking dogs kicks dogs
           explaining the program is easy
           *explaining the program is running

   (These are distinctions that I thought we would never be able to make,
   so I told myself they were semantic rather than syntactic. But with
   domains, they should be easy.)

*/
static char * domain_starter_links[] =
               {"W", "Ce", "Cs", "Ca", "Cc", "Ci", "R*", "Re", "RSe", 
		"Mr", "QI#d", "Mv", "Jr", "Mj", "Qd", 
                "TOn", "TOi", "Mg", "MVi", 
                "Ss#d", "Bsd", "ER", "Z", 
                "Ma", "SIs#g", 
		"BIqx", "MX#p", "MX#a", "MX#r", "MX#j", "MV#o", "MV#p",
		"Eq", "COq", "CP", "AFd", "PFc",
		NULL};
  /* these links start a domain */
  /* each of these must be given a name in CDNP below */
  

static char * urfl_domain_starter_links[] = {"TOo", "I#j", 
                "Pa##j", NULL};
  /* these start a urfl domain.  These are also included in the domain */

static char * urfl_only_domain_starter_links[] = {"SFsx", "Ss#g",
"COp", NULL};
  /* these start a urfl_only domain.  They are not included in the domain */

typedef struct connector_domain_name_pair_struct CDNP;
struct connector_domain_name_pair_struct {char * string; int n;};

/* the strings below are viewes as connector names for purposes of pp matching */
/* not as post-processing symbols */
CDNP CDNP_array[] = {{"Ce", 'e'}, {"R", 'r'}, {"Re", 'r'}, {"W", 'm'},
		       {"RSe", 'e'}, {"Cs", 's'}, {"Ca", 's'},  {"Jr", 'e'},
		       {"Mr", 'r'}, {"Cc", 's'},
                       {"Mv", 'e'}, {"QI#d", 's'}, {"BIqx", 's'},
		       {"TOn", 'e'}, {"TOi", 'e'}, 
                       {"MVi", 'e'}, {"MV#o", 's'}, {"MV#p", 's'}, 
		       {"AFd", 's'}, {"PFc", 's'},
		       {"Mg", 'e'}, {"Mj", 'j'}, {"Qd", 'm'},
		       {"MX#j", 'j'}, {"TOo", 'x'}, {"I#j", 'x'}, 
		       {"Pa##j", 'x'}, {"COp", 'd'}, 
		       {"SFsx", 'd'}, {"Ss#g", 'd'}, {"SIs#g", 's'}, 
		       {"Ss#d", 's'}, 
                       {"Bsd", 's'}, {"ER", 's'}, {"Z", 's'},
                       {"Ma", 'e'}, {"MX#p", 'e'}, {"Ci", 'e'}, {"MX#a", 'e'},
		       {"Eq", 'e'}, {"COq", 'e'}, {"CP", 'd'},
		       {"MX#r", 'r'}, 
       		       {NULL, 0}};

static char * domain_contains_links[] = {"Mg", "Mx", "Bsd", 
"MX#a", "Ma", "Mv", "MX#r", 
"Ss#d", "CP", "Ws", "Wq", "Qd", "Mj", "Wj", "Wi",
"MX#j", "AFd", "PFc", "Jr", "Wd", NULL};
  /* these links start a domain and they're also part of the domain */
  /* this must be a sublist of the domain_starter_list */

static char * ignore_these_links[] = {"Xca", NULL};
  /* These links are not put in the word/link graph.  */
  /* They also cannot be the starter links for a domain */
  /* Apparently this isn't needed - yes it is! (4/94) */

static char * must_be_connected_without[] = {"R*", 
"Re", "TOt", "EXx", "HA",  "SFsic", "Jr", NULL};
  /* the linkage must still be connected when these links are deleted */

static char * restricted_links[] = {"B#*", 
"D##w", "B#w", "B#d", "AFh",
     "MVt", "Xx", "HL", "SFsic", "AFd", "Bc", "CX", "CP",
     "EAh", "H", "HA", "PFc", "B#j", "Wd", "PF", "Z", NULL};
  /* these links are not traced further if they point back 
     before the root word */

int ppmatch(char *s, char *t) {
/* string comparison in postprocessing */
/* The first parameter is a post-processing symbol  */
/* The second one is a connector name from a link */
/* The upper case parts must match */
/* we imaging that the first arg is padded with an infinit sequence of "#" */
/* and that the 2nd one is padded with "*".  */
/* "#" matches anything, but "*" is just like an ordinary char for matching purposes. */
    char c;
    while(isupper(*s) || isupper(*t)) {
	if (*s != *t) return FALSE;
	s++;
	t++;
    }

    while (*s != '\0') {
	if (*s != '#') {
	    if (*t == '\0') c = '*'; else c = *t;
	    if (*s != c) return FALSE;
	}
	s++;
	t++;
    }
    return TRUE;
}

int find_domain_name(char * string) {
/* return the name of the domain used for this string */
/* return 0 if not in the list */
    int i;
    for (i=0; CDNP_array[i].string != NULL; i++) {
	if (ppmatch(CDNP_array[i].string, string)) {
	    return CDNP_array[i].n;
	}
    }
    return 0;
}

typedef struct d_tree_leaf_struct D_tree_leaf;
typedef struct domain_struct Domain;
struct domain_struct{
    char * string;
    int size;
    List_o_links * lol;
    int start_link;  /* the link that started this domain */
    int type;        /* one letter name */
    D_tree_leaf * child; 
    Domain * parent;
};

struct d_tree_leaf_struct{
    Domain * parent;
    int link;
    D_tree_leaf * next;
};

static Domain domain_array[MAX_LINKS];
/* the domains, sorted by size. */
static int N_domains;       /* the number of domains */
static int N_domain_trees;  /* the number of domain trees */


static List_o_links * word_links[MAX_SENTENCE];
  /* a pointer to the list of links out of this word */


void print_domain(int d) {
    List_o_links * lol;
    for (lol=domain_array[d].lol; lol != NULL; lol = lol->next) {
	print_a_link(stdout, lol->link);
    }
    printf("\n");
}

void print_domains(void) {
    int d;
    for (d=0; d<N_domains; d++)  {
	printf("domain %d \"%s\"\n", d, domain_array[d].string);
	print_domain(d);
    }
}

int post_process_match(char * s, char * t) {
/*
   The same as match() when the connectors are of THIN_priority, except
   that matching is tested for strings instead of connectors.  
*/
    while(isupper(*s) || isupper(*t)) {
	if (*s != *t) return FALSE;
	s++;
	t++;
    }

    while ((*s!='\0') && (*t!='\0')) {
	if ((*s == '*') || (*t == '*') ||
	    ((*s == *t) && (*s != '^'))) {
	    s++;
	    t++;
	} else return FALSE;
    }
    return TRUE;
}

int match_in_list(char * s, char * a[]) {
/* returns FALSE if the string s does not match anything the
   the array a, o.w. TRUE */
    int i;
    for (i=0; a[i] != NULL; i++) {
	if (post_process_match(s,a[i])) {
	    return TRUE;
	}
    }
    return FALSE;
}

int string_in_list(char * s, char * a[]) {
/* returns FALSE if the string s does not match equal anything the
   the array.  The array elements are post-processing symbols */
    int i;
    for (i=0; a[i] != NULL; i++) {
	if (ppmatch(a[i], s)) {
	    return TRUE;
	}
    }
    return FALSE;
}

void build_graph(void) {
/* fill in the word_links array with a list of words neighboring each
   word (actually a list of links).  The dir fields are not set, since this
   (after fat-link-extraction) is an undirected graph.
*/
    int i, link;
    List_o_links * lol;
    for (i=0; i<N_words; i++) {
	word_links[i] = NULL;
    }
    for (link=0; link<N_links; link++) {
	if (pp_link_array[link].l == -1) continue;
	if (string_in_list(pp_link_array[link].name, ignore_these_links)) {
	    continue;
	}
	lol = (List_o_links *) xalloc(sizeof(List_o_links));
	lol->next = word_links[pp_link_array[link].l];
	word_links[pp_link_array[link].l] = lol;
	lol->link = link;
	lol->word = pp_link_array[link].r;

	lol = (List_o_links *) xalloc(sizeof(List_o_links));
	lol->next = word_links[pp_link_array[link].r];
	word_links[pp_link_array[link].r] = lol;
	lol->link = link;
	lol->word = pp_link_array[link].l;
    }
}

void add_link_to_domain(int link) {
    List_o_links *lol;
    lol = (List_o_links *) xalloc(sizeof(List_o_links));
    lol->next = domain_array[N_domains].lol;
    domain_array[N_domains].lol = lol;
    domain_array[N_domains].size++;
    lol->link = link;
}

static int visited[MAX_SENTENCE];
/* for the depth-first search */

void depth_first_search(int w, int root, int start_link) {
    List_o_links * lol;
    visited[w] = TRUE;
    for (lol = word_links[w]; lol != NULL; lol = lol->next) {
	if (lol->word < w && lol->link != start_link) {
	    add_link_to_domain(lol->link);
	}
    }
    for (lol = word_links[w]; lol != NULL; lol = lol->next) {
	if (!visited[lol->word] && (lol->word != root) &&
	    !(lol->word < root && lol->word < w &&
	    string_in_list(pp_link_array[lol->link].name, restricted_links))) {
	    depth_first_search(lol->word, root, start_link);
	}
    }
}

void bad_depth_first_search(int w, int root, int start_link) {
    List_o_links * lol;
    visited[w] = TRUE;
    for (lol = word_links[w]; lol != NULL; lol = lol->next) {
	if ((lol->word < w)  && (lol->link != start_link) && (w != root)) {
	    add_link_to_domain(lol->link);
	}
    }
    for (lol = word_links[w]; lol != NULL; lol = lol->next) {
	if ((!visited[lol->word]) && !(w == root && lol->word < w) &&
	    !(lol->word < root && lol->word < w &&
	    string_in_list(pp_link_array[lol->link].name, restricted_links))) {
	    bad_depth_first_search(lol->word, root, start_link);
	}
    }
}

void d_depth_first_search(int w, int root, int right, int start_link) {
    List_o_links * lol;
    visited[w] = TRUE;
    for (lol = word_links[w]; lol != NULL; lol = lol->next) {
	if ((lol->word < w) && (lol->link != start_link) && (w != root)) {
	    add_link_to_domain(lol->link);
	}
    }
    for (lol = word_links[w]; lol != NULL; lol = lol->next) {
	if (!visited[lol->word] && !(w == root && lol->word >= right) &&
            !(w == root && lol->word < root) &&
	    !(lol->word < root && lol->word < w &&
	    string_in_list(pp_link_array[lol->link].name, restricted_links))) {
	    d_depth_first_search(lol->word, root, right, start_link);
	}
    }
}

int domain_compare(Domain * d1, Domain * d2) {
/* for sorting the domains by size */
    return (d1->size - d2->size) ;
}

void build_domains(void) {
    int link, i, d;
    char * s;

    N_domains = 0;
    for (link = 0; link<N_links; link++) {
	if (pp_link_array[link].l == -1) continue;
	if (string_in_list(pp_link_array[link].name, ignore_these_links)) {
	    continue;
	}
	s = pp_link_array[link].name;
	if (string_in_list(s, domain_starter_links)) {
	    for (i=0; i<N_words; i++) {
		visited[i] = FALSE;
	    }
	    domain_array[N_domains].string = s;
	    domain_array[N_domains].lol = NULL;
	    domain_array[N_domains].size = 0;
	    domain_array[N_domains].start_link = link;
	    if (string_in_list(s, domain_contains_links)) {
		add_link_to_domain(link);
	    }
	    depth_first_search(pp_link_array[link].r, pp_link_array[link].l, link);
	    N_domains++;
	} else if (string_in_list(s, urfl_domain_starter_links)) {
	    for (i=0; i<N_words; i++) {
		visited[i] = FALSE;
	    }
	    domain_array[N_domains].string = s;
	    domain_array[N_domains].lol = NULL;
	    domain_array[N_domains].size = 0;
	    domain_array[N_domains].start_link = link;
	    add_link_to_domain(link);
                 /* always add the starter link to its urfl domain */
	    bad_depth_first_search(pp_link_array[link].r,pp_link_array[link].l,link);
	    N_domains++;
	} else if (string_in_list(s, urfl_only_domain_starter_links)) {
	    for (i=0; i<N_words; i++) {
		visited[i] = FALSE;
	    }
	    domain_array[N_domains].string = s;
	    domain_array[N_domains].lol = NULL;
	    domain_array[N_domains].size = 0;
	    domain_array[N_domains].start_link = link;
                 /* do not add the starter link to its urfl_only domain */
	    d_depth_first_search(
	       pp_link_array[link].l,pp_link_array[link].l,pp_link_array[link].r,link);
	    N_domains++;
	}
    }
    qsort((void *)domain_array, N_domains, sizeof(Domain),
	  (int (*)(const void *, const void *))domain_compare);
    /* sort the domains by size */

    for (d=0; d<N_domains; d++) {
	i = find_domain_name(domain_array[d].string);
	if (i==0) {
	    printf("something wrong with domain name %s\n",
		    domain_array[d].string);
	    exit(1);
	}
	domain_array[d].type = i;
    }
}

int contained_in(Domain * d1, Domain * d2) {
/* returns TRUE if domain d1 is contained in domain d2 */
    char mark[MAX_LINKS];
    List_o_links * lol;
    int i;
    for (i=0; i<N_links; i++) {
	mark[i] = FALSE;
    }
    for (lol=d2->lol; lol != NULL; lol = lol->next) {
	mark[lol->link] = TRUE;
    }
    for (lol=d1->lol; lol != NULL; lol = lol->next) {
	if (!mark[lol->link]) return FALSE;
    }
    return TRUE;
}

int link_in_domain(int link, Domain * d) {
/* returns the predicate "the given link is in the given domain" */    
    List_o_links * lol;
    for (lol = d->lol; lol != NULL; lol = lol->next) {
	if (lol->link == link) return TRUE;
    }
    return FALSE;
}

int check_domain_nesting() {
/* returns TRUE if the domains actually form a properly nested structure */
    Domain * d1, * d2;
    int counts[4];
    char mark[MAX_LINKS];
    List_o_links * lol;
    int i;
    for (d1=domain_array; d1 < domain_array + N_domains; d1++) {
	for (d2=d1+1; d2 < domain_array + N_domains; d2++) {
	    for (i=0; i<N_links; i++) {
		mark[i] = 0;
	    }
	    for (lol=d2->lol; lol != NULL; lol = lol->next) {
		mark[lol->link] = 1;
	    }
	    for (lol=d1->lol; lol != NULL; lol = lol->next) {
		mark[lol->link] += 2;
	    }
	    counts[0] = counts[1] = counts[2] = counts[3] = 0;
	    for (i=0; i<N_links; i++) counts[(int) mark[i]]++;
	    if ((counts[1] > 0) && (counts[2] > 0) && (counts[3] > 0)) {
		return FALSE;
	    }
	}
    }
    return TRUE;
}
    
void build_domain_forest() {
    int d, d1, link;
    D_tree_leaf * dtl;
    if (N_domains > 0) {
	domain_array[N_domains-1].parent = NULL;
    }
    N_domain_trees = 1;
    for (d=0; d < N_domains-1; d++) {
	for (d1 = d+1; d1 < N_domains; d1++) {
	    if (contained_in(&domain_array[d], &domain_array[d1])) {
		domain_array[d].parent = &domain_array[d1];
		break;
	    }
	}
	if (d1 == N_domains) {
          /* we know this domain is a root of a new tree */
	    domain_array[d].parent = NULL;
	    N_domain_trees++;
	 /* It's now ok for this to happen.  It used to do:
            printf("I can't find a parent domain for this domain\n");
	    print_domain(d);
	    exit(1); */
	}
    }
    /* the parent links of domain nodes have been established.
       now do the leaves */
    for (d=0; d < N_domains; d++) {
	domain_array[d].child = NULL;
    }
    for (link=0; link < N_links; link++) {
	if (pp_link_array[link].l == -1) continue; /* probably not necessary */
	for (d=0; d<N_domains; d++) {
	    if (link_in_domain(link, &domain_array[d])) {
		dtl = (D_tree_leaf *) xalloc(sizeof(D_tree_leaf));
		dtl->link = link;
		dtl->parent = &domain_array[d];
		dtl->next = domain_array[d].child;
		domain_array[d].child = dtl;
		break;
	    }
	}
    }
}

void free_list_o_links(List_o_links *lol) {
/* free the list of links pointed to by lol
   (does not free any strings) 
*/
    List_o_links * xlol;
    while(lol != NULL) {
	xlol = lol->next;
	xfree((char *)lol, sizeof(List_o_links));
	lol = xlol;
    }
}

void free_D_tree_leaves(D_tree_leaf *dtl) {
    D_tree_leaf * xdtl;
    while(dtl != NULL) {
	xdtl = dtl->next;
	xfree((char *)dtl, sizeof(D_tree_leaf));
	dtl = xdtl;
    }
}

void free_post_processing_structures(void) {
    int w, d;
    for (w=0; w<N_words; w++) {
	free_list_o_links(word_links[w]);
    }
    for (d=0; d<N_domains; d++) {
	free_list_o_links(domain_array[d].lol);
	free_D_tree_leaves(domain_array[d].child);
    }
}

void print_domain_tree() {
    int d;
    D_tree_leaf * dtl;
    printf("Domain     It's parent \n");
    for (d=0; d<N_domains-1; d++) {
	printf(" %3d        %3d\n", d, (int) (domain_array[d].parent - domain_array));
    }
    for (d=0; d<N_domains; d++) {
	printf("Link children of domain %d:\n", d);
	for (dtl=domain_array[d].child; dtl != NULL; dtl = dtl->next) {
	    print_a_link(stdout, dtl->link);
	}
    }
}

int CCG_rule() {
/* The parent of every c domain is a c or g domain */

    int d, t;
    for (d=0; d<N_domains; d++) {
	if ((domain_array[d].type == 'c') && (domain_array[d].parent!=NULL)) {
	    t = domain_array[d].parent->type;
	    if ((t != 'g') && (t != 'c')) return FALSE;
	}
    }
    return TRUE;
}

int domain_bounded(int d_type) {
/* Checks to see that all domains with this name have the property that
   all of the words that touch a link in the domain are not to the left
   of the root word of the domain.
*/
    int d, lw;
    List_o_links * lol;

    for (d=0; d<N_domains; d++) {
	if (domain_array[d].type != d_type) continue;
	lw = pp_link_array[domain_array[d].start_link].l;
	for (lol = domain_array[d].lol; lol != NULL; lol = lol->next) {
	    if (pp_link_array[lol->link].l < lw) return FALSE;
	}
    }
    return TRUE;
}

int link_inhabits(char * link_name, int d_type){
/* Checks to see that every connector of the given name is member of
   the group of a domain of the specified type
*/
    int d;
    D_tree_leaf * c; 

    for (d=0; d<N_domains; d++) {
	for (c = domain_array[d].child; c != NULL; c = c->next) {
	    if (ppmatch(link_name, pp_link_array[c->link].name)) {
		if (domain_array[d].type != d_type) return FALSE;
	    }
	}
    }
    return TRUE;
}

int group_type_contains(int d_type, char * link_name) {
/* every d_type group must contain a link_name link within it. */
    int d;
    D_tree_leaf * c;
    for (d=0; d<N_domains; d++) {
	if (domain_array[d].type != d_type) continue;
	for (c=domain_array[d].child; c != NULL; c = c->next) {
	    if (ppmatch(link_name, pp_link_array[c->link].name)) break;
	}
	if (c == NULL) return FALSE;
    }
    return TRUE;
}

int group_type_contains_all(int d_type, char * name_list[]) {
/* every d_type group must contain all of the specified links */
    int i;
    for (i=0; name_list[i] != NULL; i++) {
	if (!group_type_contains(d_type, name_list[i])) return FALSE;
    }
    return TRUE;
}

int group_type_contains_one(int d_type, char * name_list[]) {
/* Checks that every d_type group contains exactly one of the listed links */
    int d, i;
    int count;
    D_tree_leaf * c;
    for (d=0; d<N_domains; d++) {
	if (domain_array[d].type != d_type) continue;
	count = 0;
	for (i=0; name_list[i] != NULL; i++) {
	    for (c=domain_array[d].child; c != NULL; c = c->next) {
		if (ppmatch(name_list[i], pp_link_array[c->link].name)) count++;
	    }
	}
	if (count != 1) return FALSE;
    }
    return TRUE;
}

int contains_none(char * selector, char * incompat[]) {
/* returns TRUE if and only if:
     all groups containing the selector link do not contain anything
     from the incompat set.  Uses exact string matching.
*/
    D_tree_leaf * dtl;
    int d;
    for (d=0; d<N_domains; d++) {
	for (dtl = domain_array[d].child; dtl != NULL; dtl = dtl->next) {
	    if (ppmatch(selector, pp_link_array[dtl->link].name)) break;
	}
	if (dtl != NULL) {
	    for (dtl = domain_array[d].child; dtl != NULL; dtl = dtl->next) {
		if (string_in_list(pp_link_array[dtl->link].name, incompat)) {
		    return FALSE;
		}
	    }
	}
    }
    return TRUE;
}

int ordering_constraint(char * X, char * Y) {
/*
  Returns TRUE if for every X link and Y link in the same group
  the right word of Y is strictly to the right of the right word
  of the X.  FALSE otherwise.

  This uses exact string matching.  Supposedly this is obsolete.
*/
    D_tree_leaf * dtl;
    int d, leftmost_y, rightmost_x;
    for (d=0; d<N_domains; d++) {
	leftmost_y = N_words;
        rightmost_x = -1;
	for (dtl = domain_array[d].child; dtl != NULL; dtl = dtl->next) {
	    if ((strcmp(pp_link_array[dtl->link].name, Y) == 0)) {
		if (leftmost_y > pp_link_array[dtl->link].r) {
		    leftmost_y = pp_link_array[dtl->link].r;
		}
	    } else if ((strcmp(pp_link_array[dtl->link].name, X) == 0)) {
		if (rightmost_x < pp_link_array[dtl->link].r) {
		    rightmost_x = pp_link_array[dtl->link].r;
		}
	    }
	}
	if (leftmost_y <= rightmost_x) return FALSE;
    }
    return TRUE;
}

int contains_one(char * selector, char * required[]) {
/* returns TRUE if and only if:
     all groups containing the specified link contain at least
     one from the required list.  (as determined by exact
     string matching)
*/
    D_tree_leaf * dtl;
    int d, count;
    for (d=0; d<N_domains; d++) {
	for (dtl = domain_array[d].child; dtl != NULL; dtl = dtl->next) {
	    if (ppmatch(selector, pp_link_array[dtl->link].name)) break;
	}
	if (dtl != NULL) {
	    count = 0;
	    for (dtl = domain_array[d].child; dtl != NULL; dtl = dtl->next) {
		if (string_in_list(pp_link_array[dtl->link].name, required)) {
		    count++;
		}
	    }
	    if (count < 1) return FALSE;
	}
    }
    return TRUE;
}

void connectivity_dfs(int w, char * s[]){
    List_o_links *lol;
    visited[w] = TRUE;
    for (lol = word_links[w]; lol != NULL; lol = lol->next) {
	if (!visited[lol->word] &&
	    !string_in_list(pp_link_array[lol->link].name, s)) {
	    connectivity_dfs(lol->word, s);
	}
    }
}

void mark_reachable_words(int w){
    List_o_links *lol;
    if (visited[w]) return;
    visited[w] = TRUE;
    for (lol = word_links[w]; lol != NULL; lol = lol->next) {
	mark_reachable_words(lol->word);
    }
}

int is_connected_without(char * s[]) {
/* Returns true if the linkage is connected when ignoring the links
   whose names are in the given list of link names.

   Actually, what it does is this: it returns FALSE if the connectivity
   of the subgraph reachable from word 0 changes as a result of deleting
   these links.
*/
    int i;
    for (i=0; i<N_words; i++) {
	visited[i] = FALSE;
    }
    mark_reachable_words(0);
    for (i=0; i<N_words; i++) {
	visited[i] = !visited[i];
    }
    connectivity_dfs(0, s);
    for (i=0; i<N_words; i++) {
	if (visited[i] == FALSE) {
	    return FALSE;
	}
    }
    return TRUE;
}

int is_connected(void) {
/* Returns true if the linkage is connected, considering words
   that have at least one edge....this allows conjunctive sentences
   not to be thrown out. */
    int i;
    for (i=0; i<N_words; i++) visited[i] = (word_links[i] == NULL);
    mark_reachable_words(0);
    for (i=0; i<N_words; i++) if (!visited[i]) return FALSE;
    return TRUE;
}

static char * incompat_with_THi[] =  {"I*", "PP*", "TO*", "Pa*", "Pam", 
	  "S", "SI", "Pg*", "Pv*", "LE*", "AFd*", "MVta",
	  NULL};
static char * SFiSFIi[] =  {"SFsi", "SFIsi", "OXi", NULL};
static char * Necessary_for_SF[] =  {"TOi", "THi", "QIi",  
          "TSi", "O#i", "Ci", "THb", "COqi", "CPi", "Eqi", "AFdi", NULL};
static char * Necessary_for_MVt[] = {"Dm#m", "EAm", "EEm", "MVm", 
	  "Pam", "Pafm", "AFm", "EB#m", "MVb", "Om", "Mam", 
	  "Am", "Jm", "Ds*m", NULL};
static char * Nec_for_MVz[] = {"D##y", "EAy", "EEy", "MVy", 
	  "EB#y", NULL};
static char * Opt[] = {"Opt", "Omt", "O*t", "Bp#t", "B*#t", "Bc#t",
	  NULL};
static char * Ost[] = {"O*t", "Ost", "Omt", "Bs#t", "B*#t", "Bc#t", 
          NULL};
static char * Oxt[] = {"O#t", "B##t", NULL};
static char * Nec_for_BIh[] = {"Ss#b", "SIs#b", NULL};
static char * Nec_for_THb[] = {"S##t", "SI##t",  
	      "SFsi", "SFIsi", NULL};
static char * Nec_for_BIq[] = {"S##q", "SI##q", "SFsi",
              "Ss#b", "SFIsi", "SIs#b", NULL};
static char * Necessary_for_Thcom[] = {"TH", NULL};
static char * Necessary_for_Tvcom[] = {"TOi*", NULL};
static char * Necessary_for_Tocom[] = {"TO**", "TOf*", NULL};
static char * Necessary_for_Tvcom_Trans[] = {"TOt*", NULL};
static char * MVm[] = {"MVm", NULL};
static char * MV[] = {"MVa", "MVp", NULL};
static char * EBmm[] = {"EB#m", "EB#y", NULL};
static char * Pa_or_Paf[] = {"Pa*", "Paf*", NULL};
static char * Nec_for_MVto[] = {"D##m", "D##y", "Om", "Oy", "Jm", "Jy", 
	      "Am", NULL};
static char * Nec_for_MVtp[] = {"EEm", "MVb", "Dm#m", "EEy", "D##y",
     "MVm", "Om", "Oy", "Jm", "Jy", "Am", NULL};
static char * Nec_for_MVta[] = {"Pam", "Pafm", "EAm", "Ds*m", "EAy", "AFm", "Mam", "Am", NULL}; 
static char * Nec_for_Cc[] = {"EEm", "EEy", "MVm", "MVb", "MVy", NULL};
static char * Nec_for_Mc[] = {"Dm#m", NULL};
static char * Nec_for_Sp_com[] = {"Dmcm", "Dmcy", "Om", "Oy", 
     "Jm", "Jy", NULL};
static char * Nec_for_Ss_com[] = {"Dmum", "Dmuy", "Om", "Oy", 
     "Jm", "Jy", "Ds*y", NULL};
static char * Nec_for_S_com[] = {"Dm#m", "D##y", "Om", 
     "Oy", "Jm", "Jy", NULL};
static char * Nec_for_Inv[] = {"Wq", "Qd", "CQ", "PFc", NULL};
static char * Incompat_with_Ws[] = 
   {"B#m", "Ca", "BT", NULL};
static char * Nec_for_Ws_2[] = {"D##w", "S##w", "H", NULL};
static char * Nec_for_Wq[] = {"SI", "SFI", NULL};
static char * Nec_for_Ma[] = {"TO", "TOf", "TH", "MVp", "TOt", "QI", "OF", 
     "MVt", "MVz", "MVh", "Ytm", "Ya", NULL};
static char * Nec_for_Ia[] = {"B#m", "B#w", NULL};
static char * Jr[] = {"Jr", NULL};
static char * Nec_for_Jr[] = {"B#j", NULL};
static char * Nec_for_j[] = {"JQ", "Jw", NULL};
static char * Mj_or_Wj[] = {"Mj", "Wj", "MX#j", NULL};
static char * Nec_for_Qe[] = {"EEh", NULL};
static char * Nec_for_EAh[] = {"AF", "Bsm", "B*m", "Qe", "Ca", "AFm", 
     NULL}; 
static char * ZZ[] = {"ZZ", NULL};
static char * Nec_for_MVh[] = {"EExk", "EAxk", "D##k", 
     NULL};
static char * Incompat_with_MXsr[] = {"Sp#w", NULL};
static char * Incompat_with_MXpr[] = {"Ss#w", "S#iw", NULL};
static char * illegal_S_types[] = {"Spxi", "Spi*", "Spit", 
     "Spiq", "Spib", "Spiw", NULL};
static char * illegal_SI_types[] = {"SIpxi", "SIpi*", "SIpit", 
     "SIpiq", "SIpib", NULL};

/*
contains_none("xx", array_name)
  returns false if a domain containing xx has a link that matches
  something in the array.   Uses exact string matching (not smart matching)

contains_one("xx", array_name)
  return true if every domain containing xx has at least one occurrence
  of a thing in the array.  Uses exact string matching (not smart matching)
*/

void free_PP_node(PP_node * p) {
    D_type_list * dtl, * dtlx;
    Violation_list * v, *vx;
    int i;
    for (i=0; i<N_links; i++){
	for (dtl = p->d_type_array[i]; dtl != NULL; dtl = dtlx) {
	    dtlx = dtl->next;
	    xfree((char *) dtl, sizeof(D_type_list));
	}
    }
    if (N_links > 0) xfree((char *) p->d_type_array, N_links * sizeof(D_type_list *));
    for (v = p->v; v!=NULL; v = vx) {
	vx = v->next;
	xfree((char *) v, sizeof(Violation_list));
    }
    xfree((char *) p, sizeof (PP_node));
}
     

D_type_list ** build_type_array(void) {
    D_type_list ** array, * dtl;
    int d, i;
    List_o_links * lol;

    array = NULL;  /* stop uninitialized variable compiler warnings */
    if (N_links > 0) array = (D_type_list **) xalloc(N_links * sizeof(D_type_list *));
    for (i=0; i<N_links; i++) {
	array[i] = NULL;
    }
    for (d=0; d<N_domains; d++) {
	for (lol=domain_array[d].lol; lol != NULL; lol = lol->next) {
	    dtl = (D_type_list *) xalloc(sizeof(D_type_list));
	    dtl->next = array[lol->link];
	    array[lol->link] = dtl;
	    dtl->type = domain_array[d].type;
	}
    }
    return array;
}

PP_node * bogus_pp_node(void) {
/* Construct and return a vacuus pp_node.
   This is for when post processing is turned off.
*/
    PP_node * pp_return;
    int link;
    pp_return = (PP_node *) xalloc(sizeof(PP_node));
    pp_return->d_type_array =
      (D_type_list **) xalloc(N_links * sizeof(D_type_list *));
    for (link=0; link<N_links; link++) {
	pp_return->d_type_array[link] = NULL;
    }
    pp_return->v = NULL;
    return pp_return;
}
 
Violation_list * issue_violation(Violation_list * v, char * string) {
    Violation_list * v1;
    v1 = (Violation_list *) xalloc(sizeof (Violation_list));
    v1->string = string;
    v1->next = v;
    return v1;
}

#define PP(condition,message) {                                 \
    if ((condition)) {                                          \
	v = issue_violation(v, (message));                      \
	goto done_checking;                                     \
    }                                                           \
}

/* The above goto could be avoided by using "elseif", but some compilers  */
/* have arbitrary limits on how many of these you can have.               */

PP_node * post_process(void){
/* Takes as input:
      N_words (to know how big to make the graph).
      N_links, pp_link_array[]  (of course also uses the connectors, etc.
           that are reachable from the pp_link_array).
      pp_link_array[i].l = -1 means that this connector is to be ignored.
   Returns:
      For each link, the domain structure of that link.
      A list of the violation strings.
*/      

    Violation_list * v;
    PP_node * pp_return;
    if(!postprocess_defined) return bogus_pp_node();
    pp_return = (PP_node *) xalloc(sizeof(PP_node));
    build_graph();
    build_domains();
    build_domain_forest();
    v = NULL;
#if ! defined FOR_RELEASE
    if(!check_domain_nesting()) {
	if (display_bad) {
	    printf("FYI: The domains are not nested.\n");
	}
    }
#endif
    PP(!is_connected_without(must_be_connected_without),
                                      "Connectivity violation");

    PP(!is_connected(), "Connectivity violation");  

    PP(!domain_bounded('s'), "Unbounded s domain");
    PP(!domain_bounded('r'), "Unbounded r domain");

    PP(!contains_one("SI#*", Nec_for_Inv),    "question inversion violated");
    PP(!contains_one("SI#i", Nec_for_Inv),    "question inversion violated");
    PP(!contains_one("SI#x", Nec_for_Inv),  "question inversion violated");
    PP(!contains_one("SFI##*", Nec_for_Inv), "question inversion violated");

    PP(!contains_none("Ws", Incompat_with_Ws), "question inversion violated");
    PP(!contains_one("Ws", Nec_for_Ws_2),   "question inversion violated");

    PP(!contains_one("I#a", Nec_for_Ia),"incorrect use of 'to'"); 

    PP(!contains_one("Wq", Nec_for_Wq),"question inversion violated");
    PP(!contains_one("Qd", Nec_for_Wq),"question inversion violated");
    PP(!contains_one("PFc", Nec_for_Wq),"question inversion violated");

    PP(!contains_one("Mj", Nec_for_j),"misuse of question word"); 
    PP(!contains_one("MX#j", Nec_for_j),"misuse of question word"); 
    PP(!contains_one("Wj", Nec_for_j),"misuse of question word"); 
    PP(!contains_one("JQ", Mj_or_Wj),"misuse of preposition");
    PP(!contains_one("Jw", Mj_or_Wj),"misuse of preposition");

    PP(!contains_one("B#j", Jr),"A B*j must have a Jr");
    PP(!contains_one("Jr", Nec_for_Jr),"A Jr must have an B*j");   

    PP(!contains_one("EAh", Nec_for_EAh),"Incorrect use of 'how'"); 

    PP(!contains_one("EEh", Nec_for_EAh),"Incorrect use of 'how'"); 

    PP(!contains_one("Qe", Nec_for_Qe), "Incorrect use of adverb");

    PP(!contains_one("THi", SFiSFIi),"THi rule 1 violated");
    PP(!contains_one("TSi", SFiSFIi),"TSi rule 1 violated");
    PP(!contains_one("QIi", SFiSFIi),"QIi rule 1 violated");
    PP(!contains_one("TOi", SFiSFIi),"TV rule 1 violated");
    PP(!contains_one("Ci", SFiSFIi),"Ci rule 1 violated");
    PP(!contains_one("COqi", SFiSFIi),"It rules violated");
    PP(!contains_one("CPi", SFiSFIi),"It rules violated");
    PP(!contains_one("Eqi", SFiSFIi),"It rules violated");
    PP(!contains_one("LEi", SFiSFIi),"THi rule 1 violated");
    PP(!contains_one("MVti", SFiSFIi),"THi rule 1 violated");
    PP(!contains_one("AFdi", SFiSFIi),"THi rule 1 violated");
    PP(!contains_one("O#i", SFiSFIi),"O#i rule 1 violated"); 

    PP(!contains_none("SF", incompat_with_THi),"There rule 1 violated");
    PP(!contains_none("SFI", incompat_with_THi),"There rule 1 violated");
    PP(!contains_none("OX", incompat_with_THi),"OXt rule 1 violated");

    PP(!contains_one("SFst", Ost),"There rule 2 violated");
    PP(!contains_one("SFIst", Ost),"There rule 2 violated");
    PP(!contains_one("SFp", Opt),"There rule 2 violated");
    PP(!contains_one("SFIp", Opt),"There rule 2 violated");
    PP(!contains_one("OXt", Oxt),"There rule 2 violated");
    PP(!contains_one("SFsi*", Necessary_for_SF),"It rule violated");
    PP(!contains_one("SFIsi", Necessary_for_SF),"It rule violated");

    PP(!contains_one("THb", Nec_for_THb),"be-that rule violated");
    PP(!contains_one("BIh", Nec_for_BIh),"be-complement rule violated");
    PP(!contains_one("BIq", Nec_for_BIq),"be-complement rule violated");
    PP(!contains_one("OXi", Necessary_for_SF),"SF rule violated");
    
    PP(!contains_one("MVt", Necessary_for_MVt),"Than rule violated");
    PP(!contains_one("MVz", Nec_for_MVz),"As rule violated");

    PP(!contains_one("MV#a", Nec_for_MVta),"bad use of comparative");
    PP(!contains_one("MV#i", Nec_for_MVta),"bad use of comparative");
    PP(!contains_one("MV#o", Nec_for_MVto),"bad use of comparative");
    PP(!contains_one("MV#p", Nec_for_MVtp),"bad use of comparative");

    PP(!contains_one("Pafc", EBmm),"Than-adj 1 violated");
    PP(!contains_one("Pafc", Pa_or_Paf),"Than-adj 2 violated");
    PP(!contains_one("MVat", MVm),"Than-adv 1 violated");
    PP(!contains_one("MVpt", MVm),"Than-prep 1 violated");
    PP(!contains_one("MVat", MV),"Than-adv 2 violated");
    PP(!contains_one("MVpt", MV),"Than-prep 2 violated");

    PP(!contains_one("U#t", Nec_for_MVto),"Than-obj 2 violated");

    PP(!contains_one("Cc", Nec_for_Cc),"Cc violated");

    PP(!contains_one("Mc", Nec_for_Mc),"Mc violated");
    PP(!contains_one("Sp#c", Nec_for_Sp_com),"Sp_com violated");
    PP(!contains_one("Ss#c", Nec_for_Ss_com),"Ss_com violated");
    PP(!contains_one("S*ic", Nec_for_Ss_com),"Ss_com violated");
    PP(!contains_one("S##c", Nec_for_S_com),"S_com violated");
    PP(!contains_one("THc", Necessary_for_Thcom),"That-comparative rule violated");
    PP(!contains_one("TOfc", Necessary_for_Tocom),"To-comparative rule violated");
    PP(!contains_one("TOic", Necessary_for_Tvcom),"To-comparative rule violated");
    PP(!contains_one("TOtc", Necessary_for_Tvcom_Trans),"To-comparative rule violated");

    PP(!contains_one("Ma*", Nec_for_Ma), "bad use of adjective");
    PP(!contains_one("Mam", Nec_for_Ma), "bad use of adjective");
    PP(!contains_one("MX#a", Nec_for_Ma), "bad use of adjective");
    PP(!contains_one("Ixd", ZZ),"Can't use \"do\" with that verb");
    PP(!contains_one("Oxn", ZZ),"Can't use a tag word after a pronoun");
/*    PP(!contains_one("Spxi", ZZ),"bad n-v agreement"); 
    PP(!contains_one("SIpxi", ZZ),"bad n-v agreement"); 
    PP(!contains_one("Spi*", ZZ),"bad n-v agreement"); 
    PP(!contains_one("Spit", ZZ),"bad n-v agreement"); 
    PP(!contains_one("Spiq", ZZ),"bad n-v agreement");
    PP(!contains_one("Spib", ZZ),"bad n-v agreement");
    PP(!contains_one("SIpi", ZZ),"bad n-v agreement");  */
    PP(!contains_none("S", illegal_S_types),"bad n-v agreement");  
    PP(!contains_none("SI", illegal_SI_types),"bad n-v agreement");  


    PP(!contains_one("MVh", Nec_for_MVh),"Incorrect use of that");

    PP(!contains_none("MXsr", Incompat_with_MXsr),"Bad n-v agreement");
    PP(!contains_none("MXpr", Incompat_with_MXpr),"Bad n-v agreement");

done_checking:

    pp_return->d_type_array = build_type_array();
    pp_return->v = v;
    free_post_processing_structures();
    return pp_return;
}
