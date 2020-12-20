 /***************************************************************************/
 /*                                                                         */
 /* This link grammar system is copyright (C) 1991-1997 by Daniel Sleator   */
 /* (sleator@cs.cmu.edu) and Davy Temperley.  This is work in progress.     */
 /* See http://www.cs.cmu.edu/~sleator for announcements of the latest      */
 /* version, detailed documentation, and rules for commercial use.          */
 /*                                                                         */
 /***************************************************************************/

#include "header.h"
#include <stdarg.h>

/* 
 The functions in this file do several things: () take a linkage
 involving fat links and expand it into a sequence of linkages
 (involving a subset of the given words), one for each way of
 eliminating the conjunctions.  () determine if a linkage involving
 fat links has a structural violation.  () make sure each of the expanded
 linkages has a consistent post-processing behavior.  () compute the
 cost of the linkage.
*/

Link pp_link_array[MAX_LINKS];

typedef struct DIS_node_struct DIS_node;
typedef struct CON_node_struct CON_node;
typedef struct CON_list_struct CON_list;
typedef struct DIS_list_struct DIS_list;
typedef struct Links_to_patch_struct Links_to_patch;
typedef void (*void_returning_function)();

struct DIS_node_struct {
    CON_list * cl;     /* the list of children */
    List_o_links * lol;/* the links that comprise this region of the graph */
    int word;          /* the word defining this node */
};

struct CON_node_struct {
    DIS_list * dl;     /* the list of children */
    DIS_list * current;/* defines the current child */
    int word;          /* the word defining this node */
};

struct DIS_list_struct {
    DIS_list * next;
    DIS_node * dn;
};

struct CON_list_struct {
    CON_list * next;
    CON_node * cn;
};

struct Links_to_patch_struct {
    Links_to_patch * next;
    int link;
    char dir;   /* this is 'r' or 'l' depending on which end of the link
		   is to be patched. */
    int new;    /* the new value of the end to be patched */
};

static List_o_links * word_links[MAX_SENTENCE];
  /* a pointer to the list of links out of this word */

void build_digraph(void) {
/* Constructs a graph in the word_links array based on the contents of    */
/* the global link_array.  Makes the word_links array point to a list of  */
/* words neighboring each word (actually a list of links).  This is a     */
/* directed graph, constructed for dealing with "and".  For a link in     */
/* which the priorities are UP or DOWN_priority, the edge goes from the   */
/* one labeled DOWN to the one labeled UP.                                */
/* Don't generate links edges for the bogus comma connectors              */
    int i, link, N_fat;
    Link * lp;
    List_o_links * lol;
    N_fat = 0;
    for (i=0; i<N_words; i++) {
	word_links[i] = NULL;
    }
    for (link=0; link<N_links; link++) {
	lp = &link_array[link];
	i = lp->lc->label;
	if (i < NORMAL_LABEL) {   /* one of those special links for either-or, etc */
	    continue;  
	}
	lol = (List_o_links *) xalloc(sizeof(List_o_links));
	lol->next = word_links[lp->l];
	word_links[lp->l] = lol;
	lol->link = link;
	lol->word = lp->r;
	i = lp->lc->priority;
	if (i == THIN_priority) {
	    lol->dir = 0;
	} else if (i == DOWN_priority) {
	    lol->dir = 1;
	} else {
	    lol->dir = -1;
	}
	lol = (List_o_links *) xalloc(sizeof(List_o_links));
	lol->next = word_links[lp->r];
	word_links[lp->r] = lol;
	lol->link = link;
	lol->word = lp->l;
	i = lp->rc->priority;
	if (i == THIN_priority) {
	    lol->dir = 0;
	} else if (i == DOWN_priority) {
	    lol->dir = 1;
	} else {
	    lol->dir = -1;
	}
    }
}

static int structure_violation;
static int dfs_root_word[MAX_SENTENCE];
/* for the depth-first search */

int is_CON_word(int w) {
/* Returns TRUE if there is at least one fat link pointing out of this word. */
    List_o_links * lol;
    for (lol = word_links[w]; lol!=NULL; lol = lol->next) {
	if (lol->dir == 1) {
	    return TRUE;
	}
    }
    return FALSE;
}

DIS_node * build_DIS_node(int);
CON_list * c_dfs(int, DIS_node *, CON_list *);

CON_node * build_CON_node(int w) {
/* This word is a CON word (has fat links down).  Build the tree for it.  */
    List_o_links * lol;
    CON_node * a;
    DIS_list * d, *dx;
    d = NULL;
    for (lol = word_links[w]; lol!=NULL; lol = lol->next) {
	if (lol->dir == 1) {
	    dx = (DIS_list *) xalloc (sizeof (DIS_list));
	    dx->next = d;
	    d = dx;
	    d->dn = build_DIS_node(lol->word);
	}
    }
    a = (CON_node *) xalloc(sizeof (CON_node));
    a->dl = a->current = d;
    a->word = w;
    return a;
}

CON_list * c_dfs(int w, DIS_node * start_dn, CON_list * c) {
/* Does a depth-first-search starting from w.  Puts on the front of the
   list pointed to by c all of the CON nodes it finds, and returns the
   result.  Also construct the list of all edges reached as part of this
   DIS_node search and append it to the lol list of start_dn.
*/
    CON_list *cx;
    List_o_links * lol, *lolx;
    if (dfs_root_word[w] != -1) {
	if (dfs_root_word[w] != start_dn->word) {
	    structure_violation = TRUE;
	}
	return c;
    }
    dfs_root_word[w] = start_dn->word;
    for (lol=word_links[w]; lol != NULL; lol = lol->next) {
	if (lol->dir < 0) {  /* a backwards link */
	    if (dfs_root_word[lol->word] == -1) {
		structure_violation = TRUE;
	    }
	} else if (lol->dir == 0) {
	    lolx = (List_o_links *) xalloc(sizeof(List_o_links));
	    lolx->next = start_dn->lol;
	    lolx->link = lol->link;
	    start_dn->lol = lolx;
	    c = c_dfs(lol->word, start_dn, c);
	}
    }
    if (is_CON_word(w)) {  /* if the current node is CON, put it first */
	cx = (CON_list *) xalloc(sizeof(CON_list));
	cx->next = c;
	c = cx;
	c->cn = build_CON_node(w);
    }
    return c;
}    

DIS_node * build_DIS_node(int w) {
/* This node is connected to its parent via a fat link.  Search the
   region reachable via thin links, and put all reachable nodes with fat
   links out of them in its list of children.
*/
    DIS_node * dn;
    dn = (DIS_node *) xalloc(sizeof (DIS_node));
    dn->word = w;   /* must do this before dfs so it knows the start word */
    dn->lol = NULL;
    dn->cl = c_dfs(w, dn, NULL);
    return dn;
}

DIS_node * build_DIS_CON_tree(void) {
    int w;
    DIS_node * dnroot, * dn;
    CON_list * child, * xchild;
    List_o_links * lol, * xlol;
    for (w=0; w<N_words; w++) {
	dfs_root_word[w] = -1;
    }
    dnroot = NULL;
    for (w=0; w < N_words; w++) {
	if (dfs_root_word[w] == -1) {
	    dn = build_DIS_node(w);
	    if (dnroot == NULL) {
		dnroot = dn;
	    } else {
		for (child = dn->cl; child != NULL; child = xchild) {
		    xchild = child->next;
		    child->next = dnroot->cl;
		    dnroot->cl = child;
		}
		for (lol = dn->lol; lol != NULL; lol = xlol) {
		    xlol = lol->next;
		    lol->next = dnroot->lol;
		    dnroot->lol = lol;
		}
		xfree((void *) dn, sizeof(DIS_node));
	    }
	}
    }
    return dnroot;
}

int advance_CON(CON_node *);
int advance_DIS(DIS_node * dn) {
/* Cycically advance the current state of this DIS node.
   If it's now at the beginning of its cycle" return FALSE;
   Otherwise return TRUE;
*/
    CON_list * cl;
    for (cl = dn->cl; cl!=NULL; cl=cl->next) {
	if (advance_CON(cl->cn)) {
	    return TRUE;
	}
    }
    return FALSE;
}

int advance_CON(CON_node * cn) {
/* Cycically advance the current state of this CON node.
   If it's now at the beginning of its cycle return FALSE;
   Otherwise return TRUE;
*/
    if (advance_DIS(cn->current->dn)) {
	return TRUE;
    } else {
	if (cn->current->next == NULL) {
	    cn->current = cn->dl;
	    return FALSE;
	} else {
	    cn->current = cn->current->next;
	    return TRUE;
	}
    }
}

typedef struct patch_element_struct Patch_element;
struct patch_element_struct {
    char used;   /* TRUE if this link is used, else FALSE  */
    char changed;/* TRUE if this link changed, else FALSE  */
    int newl;    /* the new value of the left end          */
    int newr;    /* the new value of the right end         */
};

static Patch_element patch_array[MAX_LINKS];

void fill_patch_array_CON(CON_node *, Links_to_patch *);

void fill_patch_array_DIS(DIS_node * dn, Links_to_patch * ltp) {
/* Patches up appropriate links in the patch_array for this DIS_node     */
/* and this patch list.                                                  */
    CON_list * cl;
    List_o_links * lol;
    Links_to_patch * ltpx;
    for (lol=dn->lol; lol != NULL; lol=lol->next) {
	patch_array[lol->link].used = TRUE;
    }
    if ((dn->cl == NULL) || (dn->cl->cn->word != dn->word)) {
	for (; ltp != NULL; ltp = ltpx) {
	    ltpx = ltp->next;
	    patch_array[ltp->link].changed = TRUE;
	    if (ltp->dir == 'l') {
		patch_array[ltp->link].newl = dn->word;
	    } else {
		patch_array[ltp->link].newr = dn->word;
	    }
	    xfree((void *) ltp, sizeof(Links_to_patch));
	}
    }
    /* ltp != NULL at this point means that dn has child which is a cn
       which is the same word */
    for (cl=dn->cl; cl!=NULL; cl=cl->next) {
	fill_patch_array_CON(cl->cn, ltp);
	ltp = NULL;
    }
}

void fill_patch_array_CON(CON_node * cn, Links_to_patch * ltp) {
    List_o_links * lol;
    Links_to_patch *ltpx;
    for (lol=word_links[cn->word]; lol != NULL; lol = lol->next) {
	if (lol->dir == 0) {
	    ltpx = (Links_to_patch *) xalloc(sizeof(Links_to_patch));
	    ltpx->next = ltp;
	    ltp = ltpx;
	    ltp->new = cn->word;
	    ltp->link = lol->link;
	    if (lol->word > cn->word) {
		ltp->dir = 'l';
	    } else {
		ltp->dir = 'r';
	    }
	}
    }
    fill_patch_array_DIS(cn->current->dn, ltp);
}

void free_digraph(void) {
    List_o_links * lol, *lolx;
    int i;
    for (i=0; i<N_words; i++) {
	for (lol=word_links[i]; lol!=NULL; lol=lolx) {
	    lolx = lol->next;
	    xfree((void *) lol, sizeof(List_o_links));
	}
    }
}

void free_CON_tree(CON_node *);
void free_DIS_tree(DIS_node * dn) {
    List_o_links * lol, *lolx;
    CON_list *cl, *clx;
    for (lol=dn->lol; lol!=NULL; lol=lolx) {
	lolx = lol->next;
	xfree((void *) lol, sizeof(List_o_links));
    }
    for (cl = dn->cl; cl!=NULL; cl=clx) {
	clx = cl->next;
	free_CON_tree(cl->cn);
	xfree((void *) cl, sizeof(CON_list));
    }
    xfree((void *) dn, sizeof(DIS_node));
}

void free_CON_tree(CON_node * cn) {
    DIS_list *dl, *dlx;
    for (dl = cn->dl; dl!=NULL; dl=dlx) {
	dlx = dl->next;
	free_DIS_tree(dl->dn);
	xfree((void *) dl, sizeof(DIS_list));
    }
    xfree((void *) cn, sizeof(CON_node));
}

void print_a_link(FILE *fp, int link) {
    int j;
    if (pp_link_array[link].l == 0 && left_wall_defined) {
	left_print_string(fp, LEFT_WALL_DISPLAY,"               ");
    } else if (pp_link_array[link].l == N_words-1 && right_wall_defined) {
	left_print_string(fp, RIGHT_WALL_DISPLAY,"               ");	
    } else {
	left_print_string(fp, chosen_words[pp_link_array[link].l], "               ");
    }
    left_print_string(fp, pp_link_array[link].lc->string, "     ");
    j = pp_link_array[link].lc->label;
    if (j<0) fprintf(fp, "   "); else fprintf(fp, "%3d",j);
    fprintf(fp, "<---");
    left_print_string(fp, pp_link_array[link].name, "-----");
    fprintf(fp, "->  "); 
    left_print_string(fp, pp_link_array[link].rc->string, "     ");
    j = pp_link_array[link].rc->label;
    if (j<0) fprintf(fp, "   "); else fprintf(fp, "%3d",j);
    fprintf(fp, "  %s", chosen_words[pp_link_array[link].r]);
    fprintf(fp, "\n");
}

void print_links(FILE *fp) {
    int link;
    for (link=0; link<N_links; link++) {
	if (pp_link_array[link].l == -1) continue;
	fprintf(fp, "       ");
	print_a_link(fp, link);
    }
    fprintf(fp, "\n");
}

void print_links_and_domains(FILE *fp, PP_node * pp) {
/* To the left of each link, print the sequence of domains it is in. */
/* Printing a domain means printing its type                         */
/* Takes info from pp_link_array and pp and chosen_words.            */    
    int link, longest, j;
    D_type_list * d;
    Violation_list * v;
    longest = 0;
    for (link=0; link<N_links; link++) {
	if (pp_link_array[link].l == -1) continue;
	j = 0;
	for (d = pp->d_type_array[link]; d!=NULL; d=d->next) j++;
	if (j>longest) longest = j;
    }
    for (link=0; link<N_links; link++) {
	if (pp_link_array[link].l == -1) continue;
	j = 0;
	for (d = pp->d_type_array[link]; d!=NULL; d=d->next) {
	    fprintf(fp, " (%c)", d->type);
	    j++;
	}
	for (;j<longest; j++) {
	    fprintf(fp, "    ");
	}
	fprintf(fp, "   ");
	print_a_link(fp, link);
    }
    fprintf(fp, "\n");
    if (pp->v != NULL) fprintf(fp, "P.P. violations:\n");
    for (v=pp->v; v!=NULL; v=v->next) {
	fprintf(fp, "        %s\n", v->string);
    }
}

/* The following three functions are all for computing the cost of   */
/* the and lists.                                                    */

static int visited[MAX_SENTENCE];
static int and_element_sizes[MAX_SENTENCE];
static int N_and_elements;

void and_dfs_full(int w) {
/* scope out this and element */
    List_o_links *lol;
    if (visited[w]) return;
    visited[w] = TRUE;
    and_element_sizes[N_and_elements]++;
    for (lol = word_links[w]; lol != NULL; lol = lol->next) {
	if (lol->dir >= 0) {
	    and_dfs_full(lol->word);
	}
    }
}

void and_dfs_commas(int w) {
/* get down the tree past all the commas */
    List_o_links *lol;
    if (visited[w]) return;
    visited[w] = TRUE;
    for (lol = word_links[w]; lol != NULL; lol = lol->next) {
	if (lol->dir == 1) {
             /* we only consider UP or DOWN priority links here */

	    if (strcmp(sentence[lol->word].string, ",")==0) {
		    /* pointing to a comma */
		and_dfs_commas(lol->word);
	    } else {
		and_dfs_full(lol->word);
		N_and_elements++;
	    }
	}
    }
}

int and_cost(void) {
/* Computes the imbalance in the and lists.  Assumes the graph has already */
/* been constructed.                                                       */
    int w, i, min, max, j, cost;
    char * s;
    cost = 0;
    for(w = 0; w<N_words; w++) {
	s = sentence[w].string;
	if (is_conjunction[w]) {
	    N_and_elements = 0;
	    for(i=0; i<N_words; i++) {
		visited[i] = FALSE;
		and_element_sizes[i] = 0;
	    }
	    if (left_wall_defined) visited[0] = TRUE;  /* this prevents the wall  */
                       /* from being erroniously put in an and list count*/
                       /* it also introduces and violation in "walk and run"*/
	    and_dfs_commas(w);
	    if (N_and_elements > 0) {
		min=MAX_SENTENCE;
		max=0;
		for (i=0; i<N_and_elements; i++) {
		    j = and_element_sizes[i];
		    if (j < min) min=j;
		    if (j > max) max=j;
		}
		cost += max-min;   /* is this the right function? */
	    }
	}
    }
    return cost;
}

int cost_for_length(int length) {
/* this function defines the cost of a link as a function of its length */
      return length-1;
}

int link_cost(void) {
/* computes the cost of the current parse of the current sentence */
/* due to the length of the links                                 */
    int lcost, i;
    lcost =  0;
    for (i=0; i<N_links; i++) {
	lcost += cost_for_length(link_array[i].r - link_array[i].l);
    }
    return lcost;
}

int N_null;
static int null_cost(void) {
    /* computes the number of null links in the linkage */
    return N_null;
}

int disjunct_cost(void) {
/* computes the cost of the current parse of the current sentence     */
/* due to the cost of the chosen disjuncts                            */
    int lcost, i;
    lcost =  0;
    for (i=0; i<N_words; i++) {
      if (chosen_disjuncts[i] != NULL)
	lcost += chosen_disjuncts[i]->cost;
    }
    return lcost;
}

int strictly_smaller_name(char * s, char * t) {
/*
   Returns TRUE if string s represents a strictly smaller match set
   than does t.  An almost identical function appears in and.c.
   The difference is that here we don't require s and t to be the
   same length.
*/
    int strictness, ss, tt;
    strictness = 0;
    while ((*s!='\0') || (*t!='\0')) {
	if (*s == '\0') {
	    ss = '*';
	} else {
	    ss = *s;
	    s++;
	}
	if (*t == '\0') {
	    tt = '*';
	} else {
	    tt = *t;
	    t++;
	}
	if (ss == tt) continue;
	if ((tt == '*') || (ss == '^')) {
	    strictness++;
	} else {
	    return FALSE;
	}
    }
    return (strictness > 0);  
}

void compute_link_names() {
/*
   The name of the link is set to be the GCD of the names of
   its two endpoints.
*/
    int i;
    for (i=0; i<N_links; i++) {
	link_array[i].name = intersect_strings(
	   link_array[i].lc->string, link_array[i].rc->string);
    }
}

void compute_pp_link_names() {
/*
   This fills in the pp_link_array[].name field.  We assume that
   link_array[].name have already been filled in.  As above, in the
   standard case, the name is just the GCD of the two end points.
   If pluralization has occurred, then we want to use the name
   already in link_array[].name.  We detect this in two ways.
   If the endpoints don't match, then we know pluralization
   has occured.  If they do, but the name in link_array[].name
   is *less* restrictive, then pluralization must have occured.
*/
    int i;
    char * s;
    for (i=0; i<N_links; i++) {
	if (pp_link_array[i].l == -1) continue;
	if (!match(pp_link_array[i].lc, pp_link_array[i].rc)) {
	    pp_link_array[i].name = link_array[i].name;
	} else {
	    s = intersect_strings(pp_link_array[i].lc->string,
				  pp_link_array[i].rc->string);
	    if (strictly_smaller_name(s, link_array[i].name)) {
		pp_link_array[i].name = link_array[i].name;
	    } else {
		pp_link_array[i].name = s;
	    }
	}
    }
}

Linkage_info analyze_fat_linkage(int should_print) {
  /* This uses link_array.  It enumerates and post-processes
     all the linkages represented by this one.  We know this contains
     at least one fat link.
     */
    int i;
    int should_print_messages = TRUE;  /* could use this to turn off error message printing */
    Violation_list * v;
    Linkage_info li;
    DIS_node *d_root;
    PP_node * pp, * accum;
    D_type_list * dtl0, * dtl1;
    
    build_digraph();
    structure_violation = FALSE;
    d_root = build_DIS_CON_tree();
    li.N_violations = 0;
    li.disjunct_cost = disjunct_cost();
    li.null_cost = null_cost();
    li.link_cost = link_cost();
    
    if ((structure_violation && should_print && display_multiple) ||
	(should_print && display_fat)) {
	compute_link_names();
	for (i=0; i<N_links; i++) {
	    pp_link_array[i] = link_array[i];
	}
	print_links_graphically(stdout);
	if (display_links) print_links(stdout);
    }
    
    if (structure_violation) {
/*	if (should_print_messages && display_on) { */
	if (display_links && display_bad) {
	    fprintf(stdout, "And structure violation.\n");
	}
	li.N_violations ++;
	li.and_cost = 0;
    } else {
	li.and_cost = and_cost();
	compute_link_names();
	accum = (PP_node *) xalloc(sizeof(PP_node));
	accum->d_type_array = (D_type_list **) xalloc(N_links * sizeof(D_type_list *));
	accum->v = NULL;
	for (i=0; i<N_links; i++) accum->d_type_array[i] = NULL;
	for (;;) {
	    for (i=0; i<N_links; i++) {
		patch_array[i].used = patch_array[i].changed = FALSE;
		patch_array[i].newl = link_array[i].l;
		patch_array[i].newr = link_array[i].r;
		pp_link_array[i] = link_array[i];
	    }
	    fill_patch_array_DIS(d_root, NULL);
	    
	    /*
	       The original code here would not print null links, because
	       they are not reached in the searches.  To fix this, we note
	       that any link that connects to a word that was not reached
	       in the c_dfs must be a null link, and should be printed.
	       */
	    
	    for (i=0; i<N_links; i++) {
		if (patch_array[i].changed || patch_array[i].used) {
		    pp_link_array[i].l = patch_array[i].newl;
		    pp_link_array[i].r = patch_array[i].newr;
		} else if ((dfs_root_word[link_array[i].l] != -1) &&
			   (dfs_root_word[link_array[i].r] != -1)) {
		    pp_link_array[i].l = -1;
		}
	    }
	    
	    compute_pp_link_array_connectors();
	    compute_pp_link_names();
	    pp = post_process();
	    if (display_multiple && should_print) {
		/* I guess it will print the linkage even if there are inconsistent domain ancestries*/
		/* this is OK because this function should be called with printing turned off first */
		print_links_graphically(stdout);
	    }
	    if (pp->v == NULL) {
		/* the purpose of this stuff is to make sure the domain
		   ancestry for a link in each of its sentences is consistent.
		   I know of no way in the current system that this
		   violation can occur. */
		for (i=0; i<N_links; i++) {
		    if (pp_link_array[i].l == -1) continue;
		    if (accum->d_type_array[i] == NULL) {
			accum->d_type_array[i] = pp->d_type_array[i];
			pp->d_type_array[i] = NULL;
		    } else {
			dtl0 = pp->d_type_array[i];
			dtl1 = accum->d_type_array[i];
			while((dtl0 != NULL) && (dtl1 != NULL) &&
			      (dtl0->type == dtl1->type)) {
			    dtl0 = dtl0->next;
			    dtl1 = dtl1->next;
			}
			if ((dtl0 != NULL) || (dtl1 != NULL)) {
			    break;
			}
		    }
		}
		if (i != N_links) {
		    if (display_links && should_print_messages) {
			fprintf(stdout, "Incompatible domain ancestry\n");
			li.N_violations ++;
		    }
		    free_PP_node(pp);
		    break;
		}
	    } else {
		for (v=pp->v; v!=NULL; v=v->next) {
		    li.N_violations ++;
		}
	    }
	    free_PP_node(pp);
	    
	    /* previous code: if ((li.N_violations != 0) || (!advance_DIS(d_root))) break; 
	       Getting rid of N_violations test forces links to be displayed */
	    
	    if (!advance_DIS(d_root)) break; 
	}
	if (display_on && (li.N_violations != 0) && (verbosity > 1) && should_print_messages) {
	    fprintf(stdout, "P.P. violation in one part of conjunction.\n");
	}
	free_PP_node(accum);
    }
    free_digraph();
    free_DIS_tree(d_root);
    if (should_print) fflush(stdout);
    return li;
}

Linkage_info analyze_thin_linkage(int should_print) {
    /* This uses link_array.  It post-processes
       this linkage, and prints the appropriate thing.  There are no fat
       links in it.
       */
    int i;
    Violation_list * v;
    Linkage_info li;
    PP_node * pp;
    
    compute_link_names();
    for (i=0; i<N_links; i++) {
	pp_link_array[i] = link_array[i];
    }
    pp = post_process();
    if ((display_fat || display_multiple) && should_print) {
	print_links_graphically(stdout);
	if (display_links) print_links_and_domains(stdout, pp);
    }
    
    li.N_violations = 0;
    li.and_cost = 0;
    li.disjunct_cost = disjunct_cost();
    li.null_cost = null_cost();
    li.link_cost = link_cost();
    
    for (v=pp->v; v!=NULL; v=v->next) li.N_violations ++;
    free_PP_node(pp);
    if (should_print) fflush(stdout);
    return li;
}
