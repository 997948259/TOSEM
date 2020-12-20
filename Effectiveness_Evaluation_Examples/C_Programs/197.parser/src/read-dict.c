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
  The dictionary format:

  In what follows:
    Every "%" symbol and everything after it is ignored on every line. 
    Every newline or tab is replaced by a space.

  The dictionary file is a sequence of ENTRIES.  Each ENTRY is one or
  more WORDS (a sequence of upper or lower case letters) separated by
  spaces, followed by a ":", followed by an EXPRESSION followed by a
  ";".  An EXPRESSION is a lisp expression where the functions are "&"
  or "and" or "|" or "or", and there are three types of parentheses:
  "()", "{}", and "[]".  The terminal symbols of this grammar are the
  connectors, which are strings of letters or numbers or *s.  (This
  description applies to the prefix form of the dictionary.  the current
  dictionary is written in infix form.  If the defined constant
  INFIX_NOTATION is defined, then infix is used otherwise prefix is used.)

  The connector begins with an optinal @, which is followed by an upper
  case sequence of letters. Each subsequent *, lower case letter or
  number is a subscript. At the end is a + or - sign.  The "@" allows
  this connector to attach to one or more other connectors.

  Here is a sample dictionary entry (in infix form):

      gone:         T- & {@EV+};

  (See our paper for more about how to interpret the meaning of the
  dictionary expressions.)

  A previously defined word (such as "gone" above) may be used instead
  of a connector to specify the expression it was defined to be.  Of
  course, in this case, it must uniquely specify a word in the
  dictionary, and have been previously defined.

  If a word is of the form "/foo", then the file current-dir/foo
  is a so-called word file, and is read in as a list of words.
  A word file is just a list of words separted by blanks or newlines.

  A word that contains the character "_" defines an idiomatic use of
  the words separated by the "_".  For example "kind of" is an idiomatic
  expression, so a word "kind_of" is defined in the dictionary.
  Idomatic expressions of any number of words can be defined in this way.
  When the word "kind" is encountered, all the idiomatic uses of the word
  are considered.

  An expresion enclosed in "[..]" is give a cost of 1.  This means
  that if any of the connectors inside the square braces are used,
  a cost of 1 is incurred.  (This cost is the first element of the cost
  vector printed when a sentence is parsed.)  Of course if something is
  inside of 10 levels of "[..]" then using it incurs a cost of 10.
  These costs are called "disjunct costs".  The linkages are printed out
  in order of non-increasing disjunct cost.

  The expression "(A+ or ())" means that you can choose either "A+" or
  the empty expression "()", that is, that the connector "A+" is
  optional.  This is more compactly expressed as "{A+}".  In other words,
  curly braces indicate an optional expression.

  The expression "(A+ or [])" is the same as that above, but there is a
  cost of 1 incurred for choosing not to use "A+".  The expression
  "(EXP1 & [EXP2])" is exactly the same as "[EXP1 & EXP2]".  The difference
  between "({[A+]} & B+)" and "([{A+}] & B+)" is that the latter always
  incurrs a cost of 1, while the former only gets a cost of 1 if "A+" is
  used.  

  The dictionary writer is not allowed to use connectors that begin in
  "ID".  This is reserved for the connectors automatically
  generated for idioms.

*/

int N_dict = 0;               /* the size of the dictionary */
Dict_node * dict_root = NULL; /* the root of the dictionary tree */

static char token[MAX_TOKEN_LENGTH];
/* The global variable that stores the string representation of
   the current token. The empty string signifies end of file. */
static int is_special;
/* This tells if the token in "token[]" is one of the special
   ones for the syntax of the dictionary. */

int line_number = 1;

static FILE * dict_file;

void advance(void);

void error(char * s) {
    int i;
    printf("\nError in dictionary file: %s\n",s);
    printf("line %d, tokens = ",line_number);
    for (i=0; i<5 && token[0] != '\0' ; i++) {
	printf(" \"%s\"",token);
	(void) advance();
    }
    printf("\n");
    exit(1);
}

void warning(char * s) {
    printf("\nWarning: %s\n",s);
    printf("line %d, current token = \"%s\"\n",line_number, token);
}

int get_character(int quote_mode) {
/* This gets the next character from the input, eliminating comments.
   If we're in quote mode, it does not consider the % character for
   comments */
    
    int c;
    
    c = fgetc(dict_file);
    if (c == '%' && !quote_mode) {
	while((c != EOF) && (c != '\n')) c = fgetc(dict_file);
    }
    if (c == '\n') line_number ++;
    return c;
}


/*
   This set of 10 characters are the ones defining the syntax of the dictionary.
*/
#define SPECIAL "(){};[]&|:"

void advance(void) {
   /* this reads the next token from the input into token */
    int c, i;
    static int already_got_it = '\0';
    int quote_mode;

    is_special = FALSE;

    if (already_got_it != '\0') {
	is_special = (strchr(SPECIAL, already_got_it) != NULL);
	if (already_got_it == EOF) {
	    token[0] = '\0';
	} else {
	    token[0] = already_got_it;
	    token[1] = '\0';
	}
	already_got_it = '\0';
	return;
    }

    do c=get_character(FALSE); while (isspace(c));

    quote_mode = FALSE;

    i = 0;
    for (;;) {
	if (i > MAX_TOKEN_LENGTH-1) {
	    error("Token too long");
	    return;
	}
	if (quote_mode) {
	    if (c == '\"') {
		quote_mode = FALSE;
		token[i] = '\0';
		return;
	    }
	    if (isspace(c)) {
		error("White space inside of token");
		return;
	    }	     
	    token[i] = c;
	    i++;
	} else {
	    if (strchr(SPECIAL, c) != NULL) {
		if (i==0) {
		    token[0] = c;
		    token[1] = '\0';
		    is_special = TRUE;
		    return;
		}
		token[i] = '\0';
		already_got_it = c;
		return;
	    }
	    if (c==EOF) {
		if (i==0) {
		    token[0] = '\0';
		    return;
		}
		token[i] = '\0';
		already_got_it = c;
		return;
	    }
	    if (isspace(c)) {
		token[i] = '\0';
		return;
	    }
	    if (c == '\"') {
		quote_mode = TRUE;
	    } else {
		token[i] = c;
		i++;
	    }
	}
	c = get_character(quote_mode);
    }
}

int is_equal(int c) {
/* returns TRUE if this token is a special token and it is equal to c */
    return (is_special && c==token[0] && token[1] == '\0');
}

char * copy_string(char * str) {
    char * s;
    s = (char *) xalloc(strlen(str)+1);
    strcpy(s, str);
    return s;
}

void check_connector(char * s) {
    /* makes sure the string s is a valid connector */
    int i;
    i = strlen(s);
    if (i < 1) {
	error("Expecting a connector.");
    }
    i = s[i-1];  /* the last character of the token */
    if ((i!='+') && (i!='-')) {
	error("A connector must end in a \"+\" or \"-\".");
    }
    if (*s == '@') s++;
    if (!isupper(*s)) {
	error("The first letter of a connector must be in [A--Z].");
    }
    if ((*s=='I') && (*(s+1)=='D')) {
	error("Connectors beginning with \"ID\" are forbidden");
    }
    while (*(s+1)) {
	if ((!isalnum(*s)) && (*s != '*') && (*s != '^')) {
	    error("All letters of a connector must be alpha-numeric.");
	}
	s++;
    }
}

Exp * make_unary_node(Exp * e);

Exp * connector(void) {
/* the current token is a connector (or a dictionary word)           */
/* make a node for it                                                */   
 
    Exp * n;
    Dict_node * dn;
    int i;

    i = strlen(token)-1;  /* this must be + or - if a connector */
    if ((token[i] != '+') && (token[i] != '-')) {
	dn = abridged_lookup(token);
	while((dn != NULL) && (strcmp(dn->string, token) != 0)) {
	    dn = dn->right;
	}
	if (dn == NULL) {
	    printf("\nPerhaps missing + or - in a connector.\n");
	    printf("Or perhaps you forgot the suffix on a word.\n");
	    error ("Or perhaps a word is used before it is defined\n");
	}
	n = make_unary_node(dn->exp);
    } else {
	check_connector(token);
	n = (Exp *) xalloc(sizeof(Exp));
	n->dir = token[i];
	token[i] = '\0';                   /* get rid of the + or - */
	if (token[0] == '@') {
	    n->u.string = copy_string(token+1);
	    n->multi = TRUE;
	} else {
	    n->u.string = copy_string(token);
	    n->multi = FALSE;
	}
	n->type = CONNECTOR_type;		
	n->cost = 0;
    }
    advance();
    return n;
}

Exp * make_unary_node(Exp * e) {
/* This creates a node with one child (namely e).  Initializes  */
/* the cost to zero                                      */
    Exp * n;
    n = (Exp *) xalloc(sizeof(Exp));
    n->type = AND_type;  /* these must be AND types */
    n->cost = 0;
    n->u.l = (E_list *) xalloc(sizeof(E_list));
    n->u.l->next = NULL;
    n->u.l->e = e;
    return n;
}

Exp * make_zeroary_node(void) {
/* This creates a node with zero children.  Initializes  */
/* the cost to zero                                      */
    Exp * n;
    n = (Exp *) xalloc(sizeof(Exp));
    n->type = AND_type;  /* these must be AND types */
    n->cost = 0;
    n->u.l = NULL;
    return n;
}

Exp * make_optional_node(Exp * e) {
/* This creates an OR node with two children, one the given node,
   and the other as zeroary node.  This has the effect of creating
   what used to be called an optional node.
*/
    Exp * n;
    E_list *el, *elx;
    n = (Exp *) xalloc(sizeof(Exp));
    n->type = OR_type; 
    n->cost = 0;
    n->u.l = el = (E_list *) xalloc(sizeof(E_list));
    el->e = make_zeroary_node();
    el->next = elx = (E_list *) xalloc(sizeof(E_list));
    elx->next = NULL;
    elx->e = e;
    return n;
}

Exp * expression(void);

#if ! defined INFIX_NOTATION

Exp * operator_exp(int type) {
/* We're looking at the first of the stuff after an "and" or "or".     */
/* Build a Exp node for this expression.  Set the cost and optional    */
/* fields to the default values.  Set the type field according to type */
    Exp * n;
    E_list first;
    E_list * elist;
    n = (Exp *) xalloc(sizeof(Exp));
    n->type = type;
    n->cost = 0;
    elist = &first;
    while((!is_equal(')')) && (!is_equal(']')) && (!is_equal('}'))) {
	elist->next = (E_list *) xalloc(sizeof(E_list));
	elist = elist->next;
	elist->e = expression();
    }
    if (elist == &first) error("An \"or\" or \"and\" of nothing");
    n->u.l = first.next;
    return n;
}

Exp * in_parens(void) {
/* looks for the stuff that is allowed to be inside of parentheses */
/* either & or | followed by a list, or a terminal symbol          */    
    if (is_equal('&') || (strcmp(token, "and")==0)) {
	advance();
	return operator_exp(AND_type);
    } else if (is_equal('|') || (strcmp(token, "or")==0)) {
	advance();
	return operator_exp(OR_type);
    } else {
	return expression();
    }
}

Exp * expression(void) {
/* Build (and return the root of) the tree for the expression beginning     */
/* with the current token.  At the end, the token is the first one not part */
/* of this expression.                                                      */

    Exp * n;
    if (is_equal('(')) {
	advance();
	n = in_parens();
	if (!is_equal(')')) error("Expecting a \")\".");
	advance();
    } else if (is_equal('{')) {
	advance();
	n = in_parens();
	if (!is_equal('}')) error("Expecting a \"}\".");
	advance();
	n = make_optional_node(n);
    } else if (is_equal('[')) {
	advance();
	n = in_parens();
	if (!is_equal(']')) error("Expecting a \"]\".");
	advance();
	n->cost += 1;
    } else if (!is_special) {
	n = connector();
    } else if (is_equal(')') || is_equal(']')) {    /* allows "()" or "[]" */
        n = make_zeroary_node();
    } else {
    	error("Connector, \"(\", \"[\", or \"{\" expected.");
    }
    return n;
}

#else

/* This is for infix notation */

Exp * restricted_expression(int and_ok, int or_ok);

Exp * expression(void) {
/* Build (and return the root of) the tree for the expression beginning  */
/* with the current token.  At the end, the token is the first one not   */
/* part of this expression.                                              */
    return restricted_expression(TRUE,TRUE);
}

Exp * restricted_expression(int and_ok, int or_ok) {
    Exp * nl=NULL, * nr, * n;
    E_list *ell, *elr;
    if (is_equal('(')) {
	advance();
	nl = expression();
	if (!is_equal(')')) error("Expecting a \")\".");
	advance();
    } else if (is_equal('{')) {
	advance();
	nl = expression();
	if (!is_equal('}')) error("Expecting a \"}\".");
	advance();
	nl = make_optional_node(nl);
    } else if (is_equal('[')) {
	advance();
	nl = expression();
	if (!is_equal(']')) error("Expecting a \"]\".");
	advance();
	nl->cost += 1;
    } else if (!is_special) {
	nl = connector();
    } else if (is_equal(')') || is_equal(']')) {    /* allows "()" or "[]" */
        nl = make_zeroary_node();
    } else {
    	error("Connector, \"(\", \"[\", or \"{\" expected.");
    }
    
    if (is_equal('&') || (strcmp(token, "and")==0)) {
	if (!and_ok) {
	    warning("\"and\" and \"or\" at the same level in an expression");
	}
	advance();
	nr = restricted_expression(TRUE,FALSE);
	n = (Exp *) xalloc(sizeof(Exp));
	n->u.l = ell = (E_list *) xalloc(sizeof(E_list));
	ell->next = elr = (E_list *) xalloc(sizeof(E_list));
	elr->next = NULL;
	
	ell->e = nl;
	elr->e = nr;
	n->type = AND_type;
	n->cost = 0;
    } else if (is_equal('|') || (strcmp(token, "or")==0)) {
	if (!or_ok) {
	    warning("\"and\" and \"or\" at the same level in an expression");
	}
	advance();
	nr = restricted_expression(FALSE,TRUE);
	n = (Exp *) xalloc(sizeof(Exp));
	n->u.l = ell = (E_list *) xalloc(sizeof(E_list));
	ell->next = elr = (E_list *) xalloc(sizeof(E_list));
	elr->next = NULL;

	ell->e = nl;
	elr->e = nr;
	n->type = OR_type;
	n->cost = 0;
    } else return nl;
    return n;
}

#endif

/* The data structure storing the dictionary is simply a binary tree.  */
/* There is one catch however.  The ordering of the words is not       */
/* exactly the order given by strcmp.  It was necessary to             */
/* modify the order to make it so that "make" < "make.n" < "make-up"   */
/* The problem is that if some other string could  lie between '\0'    */
/* and '.' (such as '-' which strcmp would give) then it makes it much */
/* harder to return all the strings that match a given word.           */
/* For example, if "make-up" was inserted, then "make" was inserted    */
/* the a search was done for "make.n", the obvious algorithm would     */
/* not find the match.                                                 */

/* verbose version */
/*
int dict_compare(char *s, char *t) {
    int ss, tt;
    while (*s != '\0' && *s == *t) {
	s++;
	t++;
    }
    if (*s == '.') {
	ss = 1;
    } else {
	ss = (*s)<<1;
    }
    if (*t == '.') {
	tt = 1;
    } else {
	tt = (*t)<<1;
    }
    return (ss - tt);
}
*/

/* terse version */
int dict_compare(char *s, char *t) {
    while (*s != '\0' && *s == *t) {s++; t++;}
    return (((*s == '.')?(1):((*s)<<1))  -  ((*t == '.')?(1):((*t)<<1)));
}
    
Dict_node * insert_dict(Dict_node * n, Dict_node * new) {
/* Insert the new node into the dictionary below node n                  */
/* give error message if the new element's string is already there       */
/* assumes that the "n" field of new is already set, and the left        */
/* and right fields of it are NULL                                       */
    int comp;
    
    if (n == NULL) return new;
    comp = dict_compare(new->string, n->string);
    if (comp < 0) {
        n->left = insert_dict(n->left, new);
    } else if (comp > 0) {
        n->right = insert_dict(n->right, new);
    } else {
        printf("\"%s\"\n", new->string);
        error("The word shown above has been multiply defined");
    }
    return n;
}

void insert_list(Dict_node * p, int l) {
/* p points to a list of dict_nodes connected by their left pointers   */
/* l is the length of this list (the last ptr may not be NULL)         */
/* It inserts the list into the dictionary.                            */
/* It does the middle one first, then the left half, then the right.   */

    Dict_node * dn, *dnx, *dn_second_half;
    int k, i; /* length of first half */

    if (l == 0) return;

    k = (l-1)/2;
    dn = p;
    for (i=0; i<k; i++) {
	dn = dn->left;
    }
    /* dn now points to the middle element */
    dn_second_half = dn->left;
    dn->left = dn->right = NULL;
    if (contains_underbar(dn->string)) {
	insert_idiom(dn);
    } else if (is_idiom_word(dn->string)) {
    printf("*** Word \"%s\" found near line %d.\n", dn->string, line_number);
    printf("    Words ending \".Ix\" (x a number) are reserved for idioms.\n");
	printf("    This word will be ignored.\n");
    } else if ((dnx = abridged_lookup(dn->string))!= NULL) {
	printf("*** The word \"%s\"", dn->string);
	printf(" found near line %d matches the following words:\n",
	       line_number);
	for (;dnx != NULL; dnx = dnx->right) {
	    printf(" %s", dnx->string);
	}
	printf("\n    This word will be ignored.\n");
    } else {
	dict_root = insert_dict(dict_root, dn);
	N_dict++;
    }

    insert_list(p, k);
    insert_list(dn_second_half, l-k-1);
}

void read_entry(void) {
/* Starting with the current token parse one dictionary entry.         */
/* Add these words to the dictionary                                   */
    Exp *n;
    int i;

    Dict_node  *dn_new, *dnx, *dn = NULL;

    for (; !is_equal(':') ; advance()) {
	  if (is_special) {
	      error("I expected a word but didn\'t get it.");
	  }
	  if (token[0] == '/') {
	      /* it's a word-file name */
	      dn = read_word_file(dn, token);
	  } else {
	      dn_new = (Dict_node *) xalloc(sizeof(Dict_node));
	      dn_new->left = dn;
	      dn = dn_new;
	      dn->file = NULL;
	      dn->string = copy_string(token);
	  }
    }
    advance();  /* pass the : */
    n = expression();
    if (!is_equal(';')) error("Expecting \";\" at the end of an entry.");
    advance();  /* pass the ; */

    /* at this point, dn points to a list of Dict_nodes connected by      */
    /* their left pointers.  These are to be inserted into the dictionary */
    i = 0;
    for (dnx = dn; dnx != NULL; dnx = dnx->left) {
	dnx->exp = n;
	i++;
    }
    insert_list(dn,i);
}

void print_expression(Exp * n) {
    E_list * el; int i;
    if (n == NULL) {
	printf("NULL expression");
	return;
    }
    if (n->type == CONNECTOR_type) {
	for (i=0; i<n->cost; i++) printf("[");
	printf("%s%c",n->u.string, n->dir);
	for (i=0; i<n->cost; i++) printf("] ");
    } else {
	for (i=0; i<n->cost; i++) printf("[");
	if (n->cost == 0) printf("(");
	if (n->type == AND_type) printf("& ");
	if (n->type == OR_type) printf("or ");
	for (el = n->u.l; el != NULL; el = el->next) {
	    print_expression(el->e);
	}
	for (i=0; i<n->cost; i++) printf("] ");
	if (n->cost == 0) printf(") ");
    }
}

void rprint_dictionary_data(Dict_node * n) {
	if (n==NULL) return;
	rprint_dictionary_data(n->left);
	printf("%s: ", n->string);
	print_expression(n->exp);
	printf("\n");
	rprint_dictionary_data(n->right);
}

void print_dictionary_data(void) {
    rprint_dictionary_data(dict_root);
}


void read_dictionary(void) {
    advance();
    while(token[0] != '\0') {
    	read_entry();
    }
}

#if 0
OBS static int where_in_line;   /* global variable showing how far we've printed */
OBS 
OBS void rprint_dictionary_words(Dict_node * dn) {
OBS     if (dn == NULL) return;
OBS     rprint_dictionary_words(dn->left);
OBS     if (where_in_line+strlen(dn->string) > 70) {
OBS 	where_in_line = 0;
OBS 	printf("\n    ");
OBS     }
OBS     where_in_line += strlen(dn->string) + 1;
OBS     printf("%s ", dn->string);
OBS     rprint_dictionary_words(dn->right);
OBS }
OBS 
OBS void print_dictionary_words(void) {
OBS     where_in_line = 1000;
OBS     rprint_dictionary_words(dict_root);
OBS     printf("\n\n");
OBS     printf("There are %d words in the dictionary.\n",N_dict);
OBS }
#endif

int dict_match(char * s, char * t) {
/* assuming that s is a pointer to a dictionary string, and that
   t is a pointer to a search string, this returns 0 if they
   match, >0 if s>t, and <0 if s<t.
   
   The matching is done as follows.  Walk down the strings until
   you come to the end of one of them, or until you find unequal
   characters.  A "*" matches anything.  Otherwise, replace "."
   by "\0", and take the difference.  This behavior matches that
   of the function dict_compare().
*/
    while((*s != '\0') && (*s == *t)) {s++; t++;}
    if ((*s == '*') || (*t == '*')) return 0;
    return (((*s == '.')?('\0'):(*s))  -  ((*t == '.')?('\0'):(*t)));
}

/* We need to prune out the lists thus generated.               */
/* A sub string will only be considered a subscript if it       */
/* followes the last "." in the word, and it does not begin     */
/* with a digit.                                                */

int true_dict_match(char * s, char * t) {
    char *ds, *dt;
    ds = strrchr(s, '.');
    dt = strrchr(t, '.');

    /* a dot at the end or a dot followed by a number is NOT considered a subscript */
    if ((dt != NULL) && ((*(dt+1) == '\0') || (isdigit(*(dt+1))))) dt = NULL;
    if ((ds != NULL) && ((*(ds+1) == '\0') || (isdigit(*(ds+1))))) ds = NULL;

    if (dt == NULL && ds != NULL) {
	if (((int)strlen(t)) > (ds-s)) return FALSE;   /* we need to do this to ensure that */
	return (strncmp(s, t, ds-s) == 0);      /*"i.e." does not match "i.e" */
    } else if (dt != NULL && ds == NULL) {
	if (((int)strlen(s)) > (dt-t)) return FALSE;   
	return (strncmp(s, t, dt-t) == 0);
    } else {
	return (strcmp(s, t) == 0);	
    }
}

static Dict_node * lookup_list = NULL;
          /* a pointer to the temporary lookup list */

void prune_lookup_list(char * s) {
    Dict_node *dn, *dnx, *dn_new;
    dn_new = NULL;
    for (dn = lookup_list; dn!=NULL; dn = dnx) {
	dnx = dn->right;
	/* now put dn onto the answer list, or free it */
	if (true_dict_match(dn->string, s)) {
	    dn->right = dn_new;
	    dn_new = dn;
	} else {
	    xfree((char *)dn, sizeof(Dict_node));	    
	}
    }
    /* now reverse the list back */
    lookup_list = NULL;
    for (dn = dn_new; dn!=NULL; dn = dnx) {
	dnx = dn->right;
	dn->right = lookup_list;
	lookup_list = dn;
    }
}

void free_lookup_list(void) {
    Dict_node * n;
    while(lookup_list != NULL) {
	n = lookup_list->right;
	xfree((char *)lookup_list, sizeof(Dict_node));
	lookup_list = n;
    }
}

void rdictionary_lookup(Dict_node * dn, char * s) {
/* see comment in dictionary_lookup below */
    int m;
    Dict_node * dn_new;
    if (dn == NULL) return;
    m = dict_match(s, dn->string);
    if (m >= 0) {
        rdictionary_lookup(dn->right, s);
    }
    if (m == 0) {
        dn_new = (Dict_node*) xalloc(sizeof(Dict_node));
	*dn_new = *dn;
        dn_new->right = lookup_list;
        lookup_list = dn_new;
    }
    if (m <= 0) {
        rdictionary_lookup(dn->left, s);
    }
}

Dict_node * dictionary_lookup(char *s) {
/* Returns a pointer to a lookup list of the words in the dictionary.
   This list is made up of Dict_nodes, linked by their right pointers.
   The node, file and string fields are copied from the dictionary.
   
   Freeing this list elsewhere is unnecessary, as long as the rest of 
   the program merely examines the list (doesn't change it) */

   free_lookup_list();
   rdictionary_lookup(dict_root, s);
   prune_lookup_list(s);
   return lookup_list;
}

#if 0
OBS Dict_node * dictionary_lookup(char *s) {
OBS /* this version no longer works consistently with the pruned lookup list
OBS    method described above.  Thus we use the slightly less efficient one
OBS    below */
OBS     int rboolean_dictionary_lookup(Dict_node * dn, char * s) {
OBS     int m;
OBS     if (dn == NULL) return FALSE;
OBS     m = dict_match(s, dn->string);
OBS     if (m < 0) {
OBS         return rboolean_dictionary_lookup(dn->left, s);
OBS     } else if (m == 0) {
OBS         return TRUE;
OBS     } else {
OBS         return rboolean_dictionary_lookup(dn->right, s);
OBS     }
OBS }
OBS 
OBS int boolean_dictionary_lookup(char *s) {
OBS /* returns true if in the dictionary, false otherwise */
OBS     return rboolean_dictionary_lookup(dict_root, s);
OBS }
#endif

int boolean_dictionary_lookup(char *s) {
    return (dictionary_lookup(s) != NULL);
}


/* the following routines are exactly the same as those above, 
   only they do not consider the idiom words
*/

void rabridged_lookup(Dict_node * dn, char * s) {
    int m;
    Dict_node * dn_new;
    if (dn == NULL) return;
    m = dict_match(s, dn->string);
    if (m >= 0) {
        rabridged_lookup(dn->right, s);
    }
    if ((m == 0) && (!is_idiom_word(dn->string))) {
        dn_new = (Dict_node*) xalloc(sizeof(Dict_node));
	*dn_new = *dn;
        dn_new->right = lookup_list;
        lookup_list = dn_new;
    }
    if (m <= 0) {
        rabridged_lookup(dn->left, s);
    }
}

Dict_node * abridged_lookup(char *s) {
   free_lookup_list();
   rabridged_lookup(dict_root, s);
   prune_lookup_list(s);
   return lookup_list;
}

int boolean_abridged_lookup(char *s) {
/* returns true if in the dictionary, false otherwise */
    return (abridged_lookup(s) != NULL);
}

/* the following functions are for handling deletion */

static Dict_node * parent;
static Dict_node * to_be_deleted;


int find_one_non_idiom_node(Dict_node * p, Dict_node * dn, char * s) {
/* Returns true if it finds a non-idiom dict_node in a file that matches
   the string s.

   ** note: this now DOES include non-file words in its search.

    Also sets parent and to_be_deleted appropriately.
*/
    int m;
    if (dn == NULL) return FALSE;
    m = dict_match(s, dn->string);
    if (m <= 0) {
	if (find_one_non_idiom_node(dn,dn->left, s)) return TRUE;
    }
/*    if ((m == 0) && (!is_idiom_word(dn->string)) && (dn->file != NULL)) { */
    if ((m == 0) && (!is_idiom_word(dn->string))) {
	to_be_deleted = dn;
	parent = p;
	return TRUE;
    }
    if (m >= 0) {
	if (find_one_non_idiom_node(dn,dn->right, s)) return TRUE;
    }
    return FALSE;
}

void set_parent_of_node(Dict_node *p, Dict_node * del, Dict_node * new) {
    if (p == NULL) {
	dict_root = new;
    } else {
	if (p->left == del) {
	    p->left = new;
	} else if (p->right == del) {
	    p->right = new;
	} else {
	    assert(FALSE, "Dictionary broken?");
	}
    }
}

int delete_dictionary_words(char * s) {
/* This deletes all the non-idiom words of the dictionary that match
   the given string.  Returns TRUE if some deleted, FALSE otherwise.
*/
    Dict_node *pred, *pred_parent;
    if (!find_one_non_idiom_node(NULL, dict_root, s)) return FALSE;
    for(;;) {
	/* now parent and to_be_deleted are set */
	if (to_be_deleted->file != NULL) {
	    to_be_deleted->file->changed = TRUE;
	}
	if (to_be_deleted->left == NULL) {
	    set_parent_of_node(parent, to_be_deleted, to_be_deleted->right);
	    xfree((char *)to_be_deleted, sizeof(Dict_node));
	} else {
	    pred_parent = to_be_deleted;
	    pred = to_be_deleted->left;
	    while(pred->right != NULL) {
		pred_parent = pred;
		pred = pred->right;
	    }
	    to_be_deleted->string = pred->string;
	    to_be_deleted->file = pred->file;
	    to_be_deleted->exp = pred->exp;
	    set_parent_of_node(pred_parent, pred, pred->left);
	    xfree((char *)pred, sizeof(Dict_node));
	}
	if (!find_one_non_idiom_node(NULL, dict_root, s)) return TRUE;
    }
}

void open_dictionary(char * s) {
    if ((dict_file = fopen(s, "r")) == NULL) {
	printf("Cannot open file %s\n", s);
	exit(1);
    }
}
