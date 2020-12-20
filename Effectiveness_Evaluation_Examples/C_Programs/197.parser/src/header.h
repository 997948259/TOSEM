 /***************************************************************************/
 /*                                                                         */
 /* This link grammar system is copyright (C) 1991-1997 by Daniel Sleator   */
 /* (sleator@cs.cmu.edu) and Davy Temperley.  This is work in progress.     */
 /* See http://www.cs.cmu.edu/~sleator for announcements of the latest      */
 /* version, detailed documentation, and rules for commercial use.          */
 /*                                                                         */
 /***************************************************************************/

#define FOR_RELEASE
   /* Defining this symbol comments out certain parts of the program.     */
   /* This is mostly stuff for improving the compiler diagnostics, and    */
   /* printing debugging and timing information.  In other words,         */
   /* defining this makes the program more portable.                      */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#if ! defined FOR_RELEASE
#include <sys/time.h>       /* Functions for computing timing info       */
#include <sys/resource.h>   /* ditto                                     */
#endif

int strncasecmp(const char *s1, const char *s2, size_t);
void mark_allocation_point(void);
void reset_allocation_point(void);
void initialize_memory(void);

/*
 Global variable descriptions

 N_words:
    The number of words in the current sentence.  Computed by
    separate_sentence().

 N_links:
    The number of links in the current linkage.  Computed by
    extract_linkage().

 sentence[].string:
    Contains a slightly modified form of the words typed by the user.
    Computed by separate_sentence().

 sentence[].x:
    Contains, for each word, a pointer to a list of expressions from the
    dictionary that match the word in sentence[].string.
    Computed by build_sentence_expressions().

 sentence[].d
    Contains for each word, a pointer to a list of disjuncts for this word.
    Computed by: parepare_to_parse(), but modified by pruning and power
    pruning.
 
 link_array[]
    This is an array of links.  These links define the current linkage.
    It is computed by extract_links().  It is used by analyze_linkage() to
    compute pp_linkage[].  It may contain fat links.

 pp_link_array[]
    Another array of links.  Here all fat links have been expunged.
    It is computed by analyze_linkage(), and used by post_process() and by
    print_links();

 chosen_disjuncts[]
    This is an array pointers to disjuncts, one for each word, that is
    computed by extract_links().  It represents the chosen disjuncts for the
    current linkage.  It is used to compute the cost of the linkage, and
    also by compute_chosen_words() to compute the chosen_words[].

 chosen_words[]
    An array of pointers to strings.  These are the words to be displayed
    when printing the solution, the links, etc.  Computed as a function of
    chosen_disjuncts[] by compute_chosen_words().  This differs from
    sentence[].string because it contains the suffixes.  It differs from
    chosen_disjunct[].string in that the idiom symbols have been removed.

 has_fat_down[]
    An array of chars, one for each word.  TRUE if there is a fat link
    down from this word, FALSE otherwise.  (Only set if there is at least
    one fat link.)  Set by set_has_fat_down_array() and used by
    analyze_linkage() and is_canonical().

 is_conjunction[]
    An array of chars, one for each word.  TRUE if the word is a conjunction
    ("and", "or", "nor", or "but" at the moment).  False otherwise. */                                                         

#define TRUE  1
#define FALSE 0
#define OBS

#define assert(ex,string) {                                               \
    if (!(ex)) {							  \
	printf("Assertion failed: %s\n", string); 		          \
	exit(1);							  \
    }									  \
}

#define NEGATIVECOST -1000000
/* This is a hack that allows one to discard disjuncts containing
   connectors whose cost is greater than given a bound. This number plus
   the cost of any connectors on a disjunct must remain negative, and
   this number multiplied times the number of costly connectors on any
   disjunct must fit into an integer. */

#define NOCUTOFF 1000
/* no connector will have cost this high */

#ifndef MIN
#define MIN(X,Y)  ( ((X) < (Y)) ? (X) : (Y))
#endif
#ifndef MAX
#define MAX(X,Y)  ( ((X) > (Y)) ? (X) : (Y))
#endif

#define LEFT_WALL_DISPLAY  ("/////")   /* the string to use to show the wall */
#define LEFT_WALL_SUPPRESS ("xxxxxxx") /* If this connector is used on the wall, */
				  /* then suppress the display of the wall  */
                                  /* bogus name to prevent ever suppressing */
#define RIGHT_WALL_DISPLAY  ("/////")   /* the string to use to show the wall */
#define RIGHT_WALL_SUPPRESS ("RW") /* If this connector is used on the wall, */

/* The following define the names of the special strings in the dictionary. */
#define LEFT_WALL_WORD   ("LEFT-WALL")
#define RIGHT_WALL_WORD  ("RIGHT-WALL")
#define POSTPROCESS_WORD ("POSTPROCESS")
#define ANDABLE_CONNECTORS_WORD ("ANDABLE-CONNECTORS")

/*
OBS #define COMMA_WORD       ("COMMA")
OBS #define COLON_WORD       ("COLON")
OBS #define SEMICOLON_WORD   ("SEMI-COLON")
OBS #define PERCENT_WORD     ("PERCENT-SIGN")
OBS #define DOLLAR_WORD      ("DOLLAR-SIGN")
OBS #define LP_WORD          ("LEFT-PAREN")
OBS #define RP_WORD          ("RIGHT-PAREN")
OBS #define AMPERSAND_WORD   ("AMPERSAND")
*/

#define PROPER_WORD      ("CAPITALIZED-WORDS")
#define HYPHENATED_WORD  ("HYPHENATED-WORDS")
#define NUMBER_WORD      ("NUMBERS")
#define UNKNOWN_WORD     ("UNKNOWN-WORD")

/*      Some size definitions.  Reduce these for small machines */
#define MAX_WORD 60           /* maximum number of chars in a word */
#define MAX_LINE 1500         /* maximum number of chars in a sentence */
#define MAX_SENTENCE 250      /* maximum number of words in a sentence */
   /* This cannot be more than 254, because I use word MAX_SENTENCE+1 to
      indicate that nothing can connect to this connector, and this
      should fit in one byte (if the word field of a connector is an
      unsigned char) */
#define MAX_LINKS (2*MAX_SENTENCE-3) /* maximum number of links allowed */
#define MAX_TOKEN_LENGTH 50          /* maximum number of chars in a token */

/* conditional compiling flags */
#define PLURALIZATION
      /* If defined, Turns on the pluralization operation in        */
      /* "and", "or" and "nor" */
#define INFIX_NOTATION
      /* If defined, then we're using infix notation for the dictionary */
      /* otherwise we're using prefix notation */

#define DOWN_priority 2
#define UP_priority   1
#define THIN_priority 0

#define NORMAL_LABEL  (-1) /* used for normal connectors            */
                           /* the labels >= 0 are used by fat links */

typedef struct Connector_struct Connector;
struct Connector_struct{
    short label;
    short word;   /* The nearest word to my left (or right) that
                     this could connect to.  Computed by power pruning
		     could also be defined as an unsigned char*/
    char priority;/* one of the three priorities above */
    char multi;   /* TRUE if this is a multi-connector */
    Connector * next;
    char * string;
};

typedef struct Disjunct_struct Disjunct;
struct Disjunct_struct {
    Disjunct *next;
    short cost;
    char marked;
    char * string;
    Connector *left, *right;
};

typedef struct Link_struct Link;
struct Link_struct {
    int l, r;
    Connector * lc, * rc;
    char * name;
};

typedef struct Match_node_struct Match_node;
struct Match_node_struct {
    Match_node * next;
    Disjunct * d;
};

typedef struct Exp_struct Exp;
typedef struct X_node_struct X_node;
struct X_node_struct {
    char * string;  /* the word itself */
    Exp * exp;
    X_node *next;
};

typedef struct Word_struct Word;
struct Word_struct {
    char string[MAX_WORD];
    X_node * x;      /* sentence starts out with these */
    Disjunct * d;    /* eventually these get generated */
};

/* The E_list an Exp structures defined below comprise the expression      */
/* trees that are stored in the dictionary.  The expression has a type     */
/* (AND, OR or TERMINAL).  If it is not a terminal it has a list           */
/* (an E_list) of children.                                                */

typedef struct E_list_struct E_list;

struct Exp_struct {
    char type;            /* one of three types, see below */
    unsigned char cost;   /* The cost of using this expression.
			     Only used for non-terminals */
    char dir;   /* '-' means to the left, '+' means to right (for connector) */
    char multi; /* TRUE if a multi-connector (for connector)  */
    union {
	E_list * l;       /* only needed for non-terminals */
	char * string;    /* only needed if it's a connector */
    }u;
};

struct E_list_struct {
    E_list * next;
    Exp * e;
};

/* Here are the types */
#define OR_type 0
#define AND_type 1
#define CONNECTOR_type 2

/* The structure below stores a list of dictionary word files. */

typedef struct Word_file_struct Word_file;
struct Word_file_struct {
    char file[MAX_WORD];     /* the file name */
    int changed;             /* TRUE if this file has been changed */
    Word_file * next;
};

/* The dictionary is stored as a binary tree comprised of the following   */
/* nodes.  A list of these (via right pointers) is used to return         */
/* the result of a dictionary lookup.                                     */

typedef struct Dict_node_struct Dict_node;
struct Dict_node_struct {
    char * string;  /* the word itself */
    Word_file * file; /* the file the word came from (NULL if dict file) */
    Exp * exp;
    Dict_node *left, *right;
};

/* The following three structs comprise what is returned by post_process(). */
typedef struct Violation_list_struct Violation_list;
struct Violation_list_struct {
    Violation_list * next;
    char * string;
};

typedef struct D_type_list_struct D_type_list;
struct D_type_list_struct {
    D_type_list * next;
    int type;
};
 
typedef struct PP_node_struct PP_node;
struct PP_node_struct {
    D_type_list ** d_type_array;
    Violation_list * v;
};

/* This is for building the graphs of links in post-processing and          */
/* fat link extraction.                                                     */

typedef struct Linkage_info_struct Linkage_info;
struct Linkage_info_struct {
    int index;
    short N_violations, null_cost, disjunct_cost, and_cost, link_cost;
};

typedef struct List_o_links_struct List_o_links;
struct List_o_links_struct{
    int link;       /* the link number */
    int word;       /* the word at the other end of this link */
    int dir;        /* 0: undirected, 1: away from me, -1: toward me */
    List_o_links * next;
};

/* these are needed also in word-file.c  */
extern int N_dict;            /* the size of the dictionary  */
extern Dict_node * dict_root; /* the root of the dictionary tree */

extern int finished_cuts;        /* true if there are no more cuts to be made*/
extern Word sentence[];
extern int N_null;               /* the number of null links in the sentence */
extern int N_words;              /* the number of words in the sentence */
extern int left_wall_defined;         /* TRUE if the dictionary contains "LEFTR_WALL" */
extern int right_wall_defined;        /* TRUE if the dictionary contains "RIGHT_WALL" */
extern int postprocess_defined;  /* TRUE if the dict contains "POSTPROCESS */
extern int andable_defined; /* TRUE if the dict has the andable conn. list */
extern int unknown_word_defined; /* TRUE if the dict contains the generic unknown word */
extern int capitalized_word_defined;  /* TRUE if the dict contains the generic capitalized word */
extern int verbosity;            /* the verbosity level */
extern int maxlinklength;    /* don't consider links longer than this length */
extern int null_links;       /* tells the parsing algorithm that null-links are allowed */
extern int screen_width;     /* the width of the screen for display purposes */
extern int display_short;        /* abbreviate height of display */
extern int display_on;           /* turn the graphical display on */
extern int display_links;        /* display the links */
extern int display_postscript;   /* for postscript printing the sentence */
extern int display_word_subscripts;  /* display word subscripts, as in "dog.n" as opposed to "dog" */
extern int display_link_subscripts;  /* display link subscripts, as in "Ss" as opposed to "S" */
extern int display_bad; /* display even the linkages with P.P. violations */
extern int display_multiple;     /* display the component sentences  */
extern int display_fat;          /* display the fat linkage too */
extern int display_walls;        /* display the walls */
extern int echo_on;     /* true if we should echo the input sentence */
extern int www_mode;
extern int just_one;

/* The following variables are just used for keeping statistics */
extern int parse_cost;          /* counts iterations of inner parse loop */
extern int mark_cost;           /* estimate of the cost of the marking phase */
extern int N_in_table;          /* hashing statistics for parse */
extern int N_hash_lookups;      /* ditto */
extern int work_in_hash_lookups;/* ditto */
extern int space_in_use;        /* space requested but not yet freed during a parse */
extern int max_space_in_use;    /* maximum of the above for this parse */


extern Link link_array[];      /* extract_links ------> analyze_linkage  */
extern Link pp_link_array[];   /* analyze_linkage -----> post_process    */
extern int N_links;
extern char * chosen_words[];
extern Disjunct * chosen_disjuncts[];
extern char has_fat_down[];  /* TRUE if this word has a fat down link */
extern char is_conjunction[];   /* TRUE if this word is a conjunction */
extern char * deletable[];      /* see main.c for explanation */

#define RTSIZE 256
/* size of random table for computing the
   hash functions.  must be a power of 2 */

extern unsigned int randtable[RTSIZE];   /* random table for hashing */
extern int line_number;     /* current line for reading in the dictionary */

#define GENTLE 1
#define RUTHLESS 0
/* These parameters tell power_pruning, to tell whether this is before or after
   generating and disjuncts.  GENTLE is before RUTHLESS is after. */

void read_dictionary(void);
void print_dictionary_data(void);
void print_dictionary_words(void);
void print_expression(Exp *);
X_node * build_word_expressions(char *);
int maxcost_of_sentence(void);
void build_sentence_disjuncts(int cost_cutoff);
Disjunct * build_disjuncts_for_dict_node(Dict_node *);
void open_dictionary(char *);
int boolean_dictionary_lookup(char *);
int boolean_abridged_lookup(char *);
Dict_node * dictionary_lookup(char *);    /* remember, this returns a list  */
                             /*      of Dict_nodes linked by right pointers */
Dict_node * abridged_lookup(char *);
int delete_dictionary_words(char *);
int table_lookup(int, int, Connector *, Connector *, int);
void print_disjunct_counts(void);
void print_links_graphically(FILE *fp);
void print_links(FILE *fp);
void extract_links(int index, int cost);
PP_node * post_process(void);
int match(Connector *, Connector *);
int count(int lw, int rw, Connector *le, Connector *re, int cost);
void * xalloc(int);
void xfree(char *, int);
void prune(void);
void power_prune(int);
int prune_match(Connector *, Connector *);
void free_disjuncts(Disjunct *);
void free_X_nodes(X_node *);
void free_connectors(Connector *);
void init_randtable(void);
void init_table(void);
void free_table(void);
Dict_node * read_word_file(Dict_node *, char *);
int files_need_saving(void);
void save_files(void);
Dict_node * insert_dict(Dict_node *, Dict_node *);
void error(char *); /* call when there is an error while reading in dict */
void insert_idiom(Dict_node *);
int contains_underbar(char *);
void print_disjunct_list(Disjunct *);
int is_idiom_word(char *);
Disjunct* eliminate_duplicate_disjuncts(Disjunct * );
void print_sentence(FILE *fp, int w);
void print_all_word_disjuncts(void);
Disjunct * copy_disjunct(Disjunct * );
Connector * copy_connectors(Connector *);
void free_strings(void);
void free_this_string_later(char *, int);
void free_lookup_list(void); /* really doesn't need to be called outside of
                                the dictionary lookup code.  */
void build_AND_tables(void);
Disjunct * build_AND_disjunct_list(char *);
void free_AND_tables(void);
Disjunct * catenate_disjuncts(Disjunct *, Disjunct *);
X_node * catenate_X_nodes(X_node *, X_node *);
Disjunct * build_COMMA_disjunct_list(void);
Disjunct * explode_disjunct_list(Disjunct *);
void print_AND_statistics(void);
void init_fast_matcher(void);
void free_fast_matcher(void);
/* Match_node * form_match_list(int, Connector *, Connector *); */
Match_node * form_match_list(int, Connector *, int, Connector *, int);
void put_match_list(Match_node *);
int next_power_of_two_up(int);
void init_andable_hash_table(void);
int upper_case_match(char *, char *);
void print_a_link(FILE *fp, int link);
char * intersect_strings(char *, char *);
void construct_comma(void);
void construct_either(void);
void construct_neither(void);
void construct_notonlybut(void);
void construct_both(void);
Disjunct * glom_wall_connector(Disjunct *);
void build_conjunction_tables(void);
int sentence_contains(char *);
int parse(int mincost);
void free_Exp(Exp *);
void free_E_list(E_list *);
Exp * copy_Exp(Exp *);
void expression_prune(void);
int size_of_expression(Exp *);
void construct_wall_expressions(void);
void print_expression_sizes(void);
Linkage_info analyze_fat_linkage(int);
Linkage_info analyze_thin_linkage(int);
void free_PP_node(PP_node *);
void compute_chosen_words(void);
int is_canonical_linkage(void);
void compute_pp_link_array_connectors(void);
int set_has_fat_down(void);
void left_print_string(FILE* fp, char *, char *);
void conjunction_prune(void);

/* int srandom(int);
int random(void); */
