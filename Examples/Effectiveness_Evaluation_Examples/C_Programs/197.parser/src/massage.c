 /***************************************************************************/
 /*                                                                         */
 /* This link grammar system is copyright (C) 1991-1997 by Daniel Sleator   */
 /* (sleator@cs.cmu.edu) and Davy Temperley.  This is work in progress.     */
 /* See http://www.cs.cmu.edu/~sleator for announcements of the latest      */
 /* version, detailed documentation, and rules for commercial use.          */
 /*                                                                         */
 /***************************************************************************/

#include "header.h"

/* This file contains the functions for massaging disjuncts of the  */
/* sentence.                                                        */

#define COMMA_LABEL   (-2) /* to hook the comma to the following "and" */
#define EITHER_LABEL  (-3) /* to connect the "either" to the following "or" */
#define NEITHER_LABEL (-4) /* to connect the "neither" to the following "nor"*/
#define NOT_LABEL     (-5) /* to connect the "not" to the following "but"*/
#define NOTONLY_LABEL (-6) /* to connect the "not" to the following "only"*/
#define BOTH_LABEL    (-7) /* to connect the "both" to the following "and"*/

/* There's a problem with installing "...but...", "not only...but...", and
   "not...but...", which is that the current comma mechanism will allow
   a list separated by commas.  "Not only John, Mary but Jim came"
   The best way to prevent this is to make it impossible for the comma
   to attach to the "but", via some sort of additional subscript on commas.
   
   I can't think of a good way to prevent this.
*/

/* The following functions all do slightly different variants of the
   following thing:

   Catenate to the disjunct list pointed to by d, a new disjunct list.
   The new list is formed by copying the old list, and adding the new
   connector somewhere in the old disjunct, for disjuncts that satisfy
   certain conditions
*/

Disjunct * glom_comma_connector(Disjunct * d) {
/* In this case the connector is to connect to the comma to the
   left of an "and" or an "or".  Only gets added next to a fat link
*/
    Disjunct * d_list, * d1, * d2;
    Connector * c, * c1;
    d_list = NULL;
    for (d1 = d; d1!=NULL; d1=d1->next) {
	if (d1->left == NULL) continue; 
	for (c = d1->left; c->next != NULL; c = c->next)
	  ;
	if (c->label < 0) continue;   /* last one must be a fat link */

	d2 = copy_disjunct(d1);
	d2->next = d_list;
	d_list = d2;

	c1 = (Connector *) xalloc(sizeof(Connector));
	c1->string="";
	c1->label = COMMA_LABEL;
	c1->priority = THIN_priority;
	c1->multi=FALSE;	
	c1->next = NULL;

	c->next = c1;
    }
    return catenate_disjuncts(d, d_list);
}

Disjunct * glom_aux_connector(Disjunct * d, int label, int necessary) {
/* In this case the connector is to connect to the "either", "neither",
   "not", or some auxilliary d to the current which is a conjunction.
   Only gets added next to a fat link, but before it (not after it)
   In the case of "nor", we don't create new disjuncts, we merely modify
   existing ones.  This forces the fat link uses of "nor" to
   use a neither.  (Not the case with "or".)  If necessary=FALSE, then
   duplication is done, otherwise it isn't
*/
    Disjunct * d_list, * d1, * d2;
    Connector * c, * c1, *c2;
    d_list = NULL;
    for (d1 = d; d1!=NULL; d1=d1->next) {
	if (d1->left == NULL) continue; 
	for (c = d1->left; c->next != NULL; c = c->next)
	  ;
	if (c->label < 0) continue;   /* last one must be a fat link */

	if (!necessary) {
	    d2 = copy_disjunct(d1);
	    d2->next = d_list;
	    d_list = d2;
	}

	c1 = (Connector *) xalloc(sizeof(Connector));
	c1->string="";
	c1->label = label;
	c1->priority = THIN_priority;
	c1->multi=FALSE;
	c1->next = c;

	if (d1->left == c) {
	    d1->left = c1;
	} else {
	    for (c2 = d1->left; c2->next != c; c2 = c2->next)
	      ;
	    c2->next = c1;
	}
    }
    return catenate_disjuncts(d, d_list);
}

Disjunct * add_one_connector(int label, int dir, char *cs, Disjunct * d) {
/* This adds one connector onto the beginning of the left (or right)
   connector list of d.  The label and string of the connector are
   specified
*/
    Connector * c;

    c = (Connector *) xalloc(sizeof(Connector));
    c->string= cs;
    c->label = label;
    c->priority = THIN_priority;
    c->multi=FALSE;
    c->next = NULL;

    if (dir == '+') {
	c->next = d->right;
	d->right = c;
    } else {
	c->next = d->left;
	d->left = c;
    }
    return d;
}    

Disjunct * special_disjunct(int label, int dir, char *cs, char * ds) {
/* Builds a new disjunct with one connector pointing in direction dir
   (which is '+' or '-').  The label and string of the connector
   are specified, as well as the string of the disjunct.
   The next pointer of the new disjunct set to NULL, so it can be
   regarded as a list.
*/
    Disjunct * d1;
    Connector * c;
    d1 = (Disjunct *) xalloc(sizeof(Disjunct));
    d1->cost = 0;
    d1->string = ds;
    d1->next = NULL;

    c = (Connector *) xalloc(sizeof(Connector));
    c->string= cs;
    c->label = label;
    c->priority = THIN_priority;
    c->multi=FALSE;
    c->next = NULL;

    if (dir == '+') {
	d1->left = NULL;
	d1->right = c;
    } else {
	d1->right = NULL;
	d1->left = c;
    }
    return d1;
}

void construct_comma(void) {
/* Finds all places in the sentence where a comma is followed by
   a conjunction ("and", "or", "but", or "nor").  It modifies these comma
   disjuncts, and those of the following word, to allow the following
   word to absorb the comma (if used as a conjunction).
*/
    int w;
    for (w=0; w<N_words-1; w++) {
	if ((strcmp(sentence[w].string, ",")==0) &&
  	            is_conjunction[w+1]) {
	    sentence[w].d = catenate_disjuncts(
		   special_disjunct(COMMA_LABEL,'+',"", ","),
		   sentence[w].d);
	    sentence[w+1].d = glom_comma_connector(sentence[w+1].d);
	}
    }
}

/* The functions below put the special connectors on certain auxilliary
   words to be used with conjunctions.  Examples: either, neither, 
   both...and..., not only...but...
*/
void construct_either(void) {
    int w;
    if (!sentence_contains("either")) return;
    for (w=0; w<N_words; w++) {
	if (strcmp(sentence[w].string, "either") != 0) continue;
	sentence[w].d = catenate_disjuncts(
                   special_disjunct(EITHER_LABEL,'+',"", "either"),
                   sentence[w].d);
    }

    for (w=0; w<N_words; w++) {
	if (strcmp(sentence[w].string, "or") != 0) continue;
	sentence[w].d = glom_aux_connector
	                  (sentence[w].d, EITHER_LABEL, FALSE);
    }
}

void construct_neither(void) {
    int w;
    if (!sentence_contains("neither")) {
	for (w=0; w<N_words; w++) {
	    if (strcmp(sentence[w].string, "nor") != 0) continue;
	    free_disjuncts(sentence[w].d);
	    sentence[w].d = NULL;  /* a nor with no neither is dead */
	}
	return;
    }
    for (w=0; w<N_words; w++) {
	if (strcmp(sentence[w].string, "neither") != 0) continue;
	sentence[w].d = catenate_disjuncts(
		   special_disjunct(NEITHER_LABEL,'+',"", "neither"),
		   sentence[w].d);
    }

    for (w=0; w<N_words; w++) {
	if (strcmp(sentence[w].string, "nor") != 0) continue;
	sentence[w].d = glom_aux_connector
	                  (sentence[w].d, NEITHER_LABEL, TRUE);
    }
}

void construct_notonlybut(void) {
    int w;
    Disjunct *d;
    if (!sentence_contains("not")) {
	return;
    }
    for (w=0; w<N_words; w++) {
	if (strcmp(sentence[w].string, "not") != 0) continue;
	sentence[w].d = catenate_disjuncts(
	     special_disjunct(NOT_LABEL,'+',"", "not"),
	     sentence[w].d);
	if (w<N_words-1 &&  strcmp(sentence[w+1].string, "only")==0) {
	    sentence[w+1].d = catenate_disjuncts(
                          special_disjunct(NOTONLY_LABEL, '-',"","only"),
                          sentence[w+1].d);
	    d = special_disjunct(NOTONLY_LABEL, '+', "","not");
	    d = add_one_connector(NOT_LABEL,'+',"", d);
	    sentence[w].d = catenate_disjuncts(d, sentence[w].d);
	}
    }
    for (w=0; w<N_words; w++) {
	if (strcmp(sentence[w].string, "but") != 0) continue;
	sentence[w].d = glom_aux_connector
	                  (sentence[w].d, NOT_LABEL, TRUE);
    }
    
}

void construct_both(void) {
    int w;
    if (!sentence_contains("both")) return;
    for (w=0; w<N_words; w++) {
	if (strcmp(sentence[w].string, "both") != 0) continue;
	sentence[w].d = catenate_disjuncts(
                   special_disjunct(BOTH_LABEL,'+',"", "both"),
                   sentence[w].d);
    }

    for (w=0; w<N_words; w++) {
	if (strcmp(sentence[w].string, "and") != 0) continue;
	sentence[w].d = glom_aux_connector
	                  (sentence[w].d, BOTH_LABEL, FALSE);
    }
}
