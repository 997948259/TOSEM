 /***************************************************************************/
 /*                                                                         */
 /* This link grammar system is copyright (C) 1991-1997 by Daniel Sleator   */
 /* (sleator@cs.cmu.edu) and Davy Temperley.  This is work in progress.     */
 /* See http://www.cs.cmu.edu/~sleator for announcements of the latest      */
 /* version, detailed documentation, and rules for commercial use.          */
 /*                                                                         */
 /***************************************************************************/

#include "header.h"
  
int contains_underbar(char * s) {
    /* Returns TRUE if the string contains an underbar character.
     */
    while(*s != '\0') {
	if (*s == '_') return TRUE;
	s++;
    }
    return FALSE;
}

int is_idiom_string(char * s) {
    /* Returns FALSE if it is not a correctly formed idiom string.
       correct such string:
       () contains no "."
       () non-empty strings separated by _
       */
    char * t;
    for (t=s; *t != '\0'; t++) {
	if (*t == '.') {
	    return FALSE;
	}
    }
    if ((s[0] == '_') || (s[strlen(s)-1] == '_')) {
	return FALSE;
    }
    for (t=s; *t != '\0'; t++) {
	if ((*t == '_') && (*(t+1) == '_')) {
	    return FALSE;
	}
    }
    return TRUE;
}    

int is_number(char *s) {
    /* return TRUE if the string s is a sequence of digits. */
    while(*s != '\0') {
	if (!isdigit(*s)) return FALSE;
	s++;
    }
    return TRUE;
}

int numberfy(char * s) {
    /* if the string contains a single ".", and ends in ".Ix" where
       x is a number, return x.  Return -1 if not of this form.
       */
    for (; (*s != '\0') && (*s != '.'); s++)
      ;
    if (*s++ != '.') return -1;
    if (*s++ != 'I') return -1;
    if (!is_number(s)) return -1;
    return atoi(s);
}

int max_postfix_found(Dict_node * d) {
    /* Look for words that end in ".Ix" where x is a number.
       Return the largest x found.
       */
    int i, j;
    i = 0;
    while(d != NULL) {
	j = numberfy(d->string);
	if (j > i) i = j;
	d = d->right;
    }
    return i;
}

char * build_idiom_word_name(char * s) {
    /* Allocates string space and returns a pointer to it.
       In this string is placed the idiomized name of the given string s.
       This is the same as s, but with a postfix of ".Ix", where x is an
       appropriate number.  x is the minimum number that distinguishes
       this word from others in the dictionary.
       */
    char * new_s, * x;
    int count;
    count = max_postfix_found(dictionary_lookup(s))+1;
    new_s = x = (char *) xalloc(strlen(s) + 10); /* fails if > 10**10 idioms */
    while((*s != '\0') && (*s != '.')) {
	*x = *s;
	x++;
	s++;
    }
    sprintf(x,".I%d",count);
    return new_s;
}

Dict_node * make_idiom_Dict_nodes(char * s) {
    /* Tear the idiom string apart.
       Destroys the string s, but does not free it.
       Put the parts into a list of Dict_nodes (connected by their right pointers)
       Sets the string fields of these Dict_nodes pointing to the
       fragments of the string s.  Later these will be replaced by
       correct names (with .Ix suffixes).
       The list is reversed from the way they occur in the string.
       A pointer to this list is returned.
       */
    Dict_node * dn, * dn_new;
    char * t;
    int more;
    dn = NULL;
    while (*s != '\0') {
	t = s;
    	while((*s != '\0') && (*s != '_')) s++;
	if (*s == '_') {
	    more = TRUE;
	    *s = '\0';
	} else {
	    more = FALSE;
	}
	dn_new = (Dict_node *) xalloc(sizeof (Dict_node));
	dn_new->right = dn;
	dn = dn_new;
	dn->string = t;
	dn->file = NULL;
	if (more) s++;
    }
    return dn;
}

static char current_name[] = "AAAAAAAA";
#define CN_size (sizeof(current_name)-1)

void increment_current_name(void) {
    int i, carry;
    i = CN_size-1;
    carry = 1;
    while (carry == 1) {
	current_name[i]++;
	if (current_name[i] == 'Z'+1) {
	    current_name[i] = 'A';
	    carry = 1;
	} else {
	    carry = 0;
	}
	i--;
    }
}

char * generate_id_connector(void) {
    /* generate a new connector name
       obtained from the current_name
       allocate string space for it.
       return a pointer to it.
     */
    unsigned int i;
    char * t, * s;
    
    for (i=0; current_name[i] == 'A'; i++)
      ;
    /* i is now the number of characters of current_name to skip */
    s = t = (char *) xalloc(CN_size - i + 2 + 1 + 1);
    *t++ = 'I';
    *t++ = 'D';
    for (; i < CN_size; i++ ) {
	*t++ = current_name[i] ;
    }
    *t++ = '\0';
    return s;
}

void insert_idiom(Dict_node * dn) {
    /* Takes as input a pointer to a Dict_node.
       The string of this Dict_node is an idiom string.
       This string is torn apart, and its components are inserted into the
       dictionary as special idiom words (ending in .I*, where * is a number).
       The expression of this Dict_node (its node field) has already been
       read and constructed.  This will be used to construct the special idiom
       expressions.
       The given dict node is freed.  The string is also freed.
       */
    Exp * nc, * no, * n1;
    E_list *ell, *elr;
    char * s;
    int s_length;
    Dict_node * dn_list, * xdn, * start_dn_list;
    
    no = dn->exp;
    s = dn->string;
    s_length = strlen(s);
    
    if (!is_idiom_string(s)) {
	printf("*** Word \"%s\" on line %d is not",s, line_number);
	printf(" a correctly formed idiom string.\n");
	printf("    This word will be ignored\n");
	xfree((char *)s, s_length+1);
	xfree((char *)dn, sizeof (Dict_node));
	return;
    }
    
    dn_list = start_dn_list = make_idiom_Dict_nodes(s);
    xfree((char *)dn, sizeof (Dict_node));
    
    if (dn_list->right == NULL) {
      error("Idiom string with only one connector -- should have been caught");
    }
    
    /* first make the nodes for the base word of the idiom (last word) */
    /* note that the last word of the idiom is first in our list */
    
    /* ----- this code just sets up the node fields of the dn_list ----*/
    nc = (Exp *) xalloc(sizeof(Exp));
    nc->u.string = generate_id_connector();
    nc->dir = '-';
    nc->multi = FALSE;
    nc->type = CONNECTOR_type;
    nc->cost = 0;
    
    n1 = (Exp *) xalloc(sizeof(Exp));
    n1->u.l = ell = (E_list *) xalloc(sizeof(E_list));
    ell->next = elr = (E_list *) xalloc(sizeof(E_list));
    elr->next = NULL;
    ell->e = nc;
    elr->e = no;
    n1->type = AND_type;
    n1->cost = 0;

    dn_list->exp = n1;
    
    dn_list = dn_list->right;
    
    while(dn_list->right != NULL) {
	/* generate the expression for a middle idiom word */
	
	n1 = (Exp *) xalloc(sizeof(Exp));
	n1->u.string = NULL;
	n1->type = AND_type;
	n1->cost = 0;
	n1->u.l = ell = (E_list *) xalloc(sizeof(E_list));
	ell->next = elr = (E_list *) xalloc(sizeof(E_list));
	elr->next = NULL;
	
	nc = (Exp *) xalloc(sizeof(Exp));
	nc->u.string = generate_id_connector();
	nc->dir = '+';
	nc->multi = FALSE;
	nc->type = CONNECTOR_type;
	nc->cost = 0;
	elr->e = nc;
	
	increment_current_name();
	
	nc = (Exp *) xalloc(sizeof(Exp));
	nc->u.string = generate_id_connector();
	nc->dir = '-';
	nc->multi = FALSE;
	nc->type = CONNECTOR_type;
	nc->cost = 0;

	ell->e = nc;
	
	dn_list->exp = n1;
	
	dn_list = dn_list->right;
    }
    /* now generate the last one */
    
    nc = (Exp *) xalloc(sizeof(Exp));
    nc->u.l = ell = (E_list *) xalloc(sizeof(E_list));
    ell->next = elr = (E_list *) xalloc(sizeof(E_list));
    elr->next = NULL;
    ell->e = elr->e = NULL;
    nc->u.string = generate_id_connector();
    nc->dir = '+';
    nc->multi = FALSE;
    nc->type = CONNECTOR_type;
    nc->cost = 0;
    
    dn_list->exp = nc;
    
    increment_current_name();
    
    /* ---- end of the code alluded to above ---- */
    
    /* now its time to insert them into the dictionary */
    
    dn_list = start_dn_list;
    
    while (dn_list != NULL) {
	xdn = dn_list->right;
	dn_list->left = dn_list->right = NULL;
        dn_list->string = build_idiom_word_name(dn_list->string);
	dict_root = insert_dict(dict_root, dn_list);
	N_dict++;
	dn_list = xdn;
    }
    xfree((char *)s, s_length+1);
}

int is_idiom_word(char * s) {
    /* returns TRUE if this is a word ending in ".Ix", where x is a number. */
    return (numberfy(s) != -1) ;
}

/*
  int only_idiom_words(Dict_node * dn) {
  returns TRUE if the list of words contains only words that are
  idiom words.  This is useful, because under this condition you want
   to be able to insert the word anyway, as long as it doesn't match
   exactly.

    while(dn != NULL) {
	if (!is_idiom_word(dn->string)) return FALSE;
	dn = dn->right;
    }
    return TRUE;
}
*/
