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
  This file does the grungy job of chopping the user's input sentence
  into words, processing the special commands, and calling all the
  functions necessary to parse the input sentence.

  The following sequence of steps is used to parse:

     * Break the input line into appropriate words.
     * Construct the dictionary expressions for each of the words.
     * Apply expression pruning to these expressions.
     * Build the disjuncts for the expressions.
     * If the sentence contains a conjunction then:
          * Apply gentle power_pruning
          * Clear out further irrelevant disjuncts with conjunction-pruning.
          * Build the "and" tables and put fat disjuncts on all the words.
	  * Apply pruning to the resulting disjuncts.
     * Apply ruthless power pruning.
     * Exhaustively search for a valid linkage.
     * For each of these linkages:
          * If there is a conjunction, expand the sentence
	    into each of the sentences it represents. and apply
	    post-processing to each of these.  All must pass, or the
	    sentence is considered to have a violation.
	  * If there is not a conjunction, then just postprocess
	    the linkage.
	  * Compute the costs of each of the linkage.  (A p.p. violation
	    essentially has infinite cost.)
     * Sort all the linkages by cost.
     * Display the solutions one at a time, according to the whim of the
       user.

  Pruning is always applied before power pruning, because it saves more
  time in power-pruning than it uses.  Power-pruning is said to be
  "ruthless" in that doing it before generating the and disjuncts will
  not work -- it will remove too much stuff.  Pruning has been modified
  to be "gentile" -- it doesn't do as much as it might so that it avoids
  deleting things that are needed after and-disjunct generation.
  It might be effective to make a ruthless version of pruning, and install
  it where appropriate.
*/

/*
Notes to myself:

  The variable N_dict is not maintained, nor is it actually used for
  anything.  Either remove this variable or keep it updated.

  If the wall isn't defined, and you try a sentence with
  "and" where one element of the and list contains the leftmost
  word, then it won't work.  This is not worth fixing.

  Create two different lists of andable connectors -- one for "and"
      and "or", and another for everything else ("nor", "but")
  Davy suggests:
   Yeah, I would suggest having one list for "and", and another list for
   all the others ("either...or", "neither...nor", "both...and", "not
   only...but", "but").
  I say:
    Not only Mary but John came                     sounds ok
             Mary but John came                     sounds wrong
  Davy:
   Yeah, there are differences between "not only...but" and "but". But I
   think the most egregious differences are between "and" and the others:
   "the not only dog but cat died", etc..


   How to avoid "Not only Jim, John, but Mary came":
 
   1.Make it impossible for the conjunction "but" to connect to a comma.
     As you go up the fat-link tree, the fat links get more and more
     restrictive (see the extensive comment in and.c).   Append an
     extra character to the end of all of the match strings for fat links.
     This character will be, say "^" on comma, and on "and", but it will
     be "*" on but, and on all the normal words.  This will kill the
     possible connection between comma and "but", but all others will
     remain intact.

   2.Actually, I think a much easier way to do it is in post-processing.
     There, we'd just look for a fat link up from a comma to a "but",
     and flag this as a violation.  Easy.

  I wonder if the choice of which fat disjuncts to generate on a word could
  made to depend on where the word is in the sentence?  Would this make
  any difference?  Perhaps pruning does anything this might do.

  Limit the number of linkages to which post-processing is applied (after
  a correct linkage has been found)?

  It might be useful to get rid of the idiom suffixes (.Ixx) at the
  beginning (instead of at the end when you print it) because then
  identical disjuncts would be eliminated.  At the moment it's not too
  much of a problem because most of the expressions get killed of in
  expression pruning.  If there were a huge number of idioms, other
  bottlenecks might appear.
  
  Would RUTHLESS pruning be useful?

  Mystery: why does "dogs and cats who died died" behave differently
  in the current system versus the transcript system.

  Figure out why folding essentially doesn't help.
  
  End of sentence feature -- display a "." or "?" whichever is
  appropriate.

  "Bill ran" fails because it uses the noun "bill" and never considers
  the proper name "Bill".  I "fixed" this to allow it to try to use a
  proper name for the first word if it's capitalized.  This led it to
  accept a lot of junk ("The died", etc), so I removed it.  The correct
  way to solve this has been installed -- namely, all of these ambiguous
  names have been explicitely listed in the dictionary.

  Should I fix it so that using "*" as the first word gives an error
  message rather than subtituting the dictionary?  -- or perhaps
  get rid of "*"  completely.

*/

Word sentence[MAX_SENTENCE];

int N_words;  /* the number of words in the current sentence */

int left_wall_defined;    /* TRUE if the dictionary contains "WALL" */
int right_wall_defined;   /* TRUE if the dictionary contains "RWALL" */
int postprocess_defined;  /* TRUE if the dict contains "POSTPROCESS */
int andable_defined; /* TRUE if the dict contains the andable connector list */
int unknown_word_defined; /* TRUE if the dict contains the generic unknown word */
int capitalized_word_defined;  /* TRUE if the dict contains the generic capitalized word */
int maxlinklength = MAX_SENTENCE;  /* don't consider links longer than this length */
int null_link_search = TRUE;     /* Enable the null-link portion of the search */
int use_unknown_word = TRUE;     /* Enable using unknown word */
int verbosity = 0; /* 0 -- 3 from least to most verbose */
int screen_width = 79;     /* the width of the screen for display purposes */
int display_short = TRUE;  /* abbreviate height of display */
int display_on = TRUE;     /* turn the display on */
int display_links = FALSE;  /* the link display */
int display_bad = FALSE; /* display even the linkages with P.P. violations */
int display_fat = FALSE;   /* display the fat linkage too */
int display_multiple = TRUE;  /* display the component sentences  */
int display_postscript = FALSE;  /* turn on postscript data generation */
int display_word_subscripts = TRUE;  /* display word subscripts, as in "dog.n" as opposed to "dog" */
int display_link_subscripts = TRUE;  /* display link subscripts, as in "Ss" as opposed to "S" */

int display_walls = FALSE;      /* if true, always display the walls */
int echo_on = FALSE;/* whether or not to echo the input sentence */
int www_mode = FALSE;
int just_one = FALSE;

/* command line settable */
int linkage_count_limit = 5000;  /* Don't process more than this many linkages */
int word_count_limit = MAX_SENTENCE;  /* Don't allow more than this many words */

int null_links = TRUE;     /* tells the parsing algorithm that null-links are allowed */
char is_conjunction[MAX_SENTENCE]; /* TRUE if this word is a conjunction */
char * deletable[MAX_SENTENCE];  /* deletable[i][j] if =TRUE  */
  /* the words i+1...j-1 could be non existant in one of      */
  /* the multiple linkages.                                   */

int parse_cost;          /* counts iterations of inner parse loop */
int mark_cost;           /* estimate of the cost of the marking phase */
int N_in_table;          /* hashing statistics for parse */
int N_hash_lookups;      /* ditto */
int work_in_hash_lookups;/* ditto */
double cumulative_time;  /* Cumulative parsing times */

int issue_sentence_word(char * s) {
/* the string s is the next word of the sentence do not issue the empty
 * string.  return false if too many words or the word is too long.  */
    if (*s == '\0') return TRUE;
    if (strlen(s) >= MAX_WORD) {
	printf("The word \"%s\" is too long.\n", s);
	printf("A word can have a maximum of %d characters.\n", MAX_WORD-1);
	return FALSE;
    }
    if (N_words == MAX_SENTENCE) {
	printf("The sentence has too many words.\n");
	return FALSE;
    }
    strcpy(sentence[N_words].string, s);
    N_words++;
    return TRUE;
}

/*
Here's a summary of how subscripts are handled:

    Reading the dictionary:

      If the last "." in a string is followed by a non-digit character,
      then the "." and everything after it is considered to be the subscript
      of the word.

      The dictionary reader does not allow you to have two words that
      match according to the criterion below.  (so you can't have
      "dog.n" and "dog")

      Quote marks are used to allow you to define words in the dictionary
      which would otherwise be considered part of the dictionary, as in

       ";": {@Xca-} & Xx- & (W+ or Qd+) & {Xx+};
       "%" : (ND- & {DD-} & <noun-sub-x> & 
	   (<noun-main-x> or B*x+)) or (ND- & (OD- or AN+));

    Rules for chopping words:

       First the prefix chars are stripped off of the word.  These
       characters are "(" and "$".

       Now, repeat the following as long as necessary:

	   Look up the word in the dictionary.
	   If it's there, the process terminates.

	   If it's not there and it ends in one of the right strippable
	   strings (see "right_strip") then remove the strippable string
	   and make it into a separate word.

	   If there is no strippable string, then the process terminates. 

    Rules for processing words in the sentence:

       The subscript rule is followed just as when reading the dictionary.

    When does a word in the sentence match a word in the dictionary?

       Matching is done as follows: Two words with subscripts must match
       exactly.  If neither has a subscript they must match exactly.  If one
       does and one doesn't then they must match when the subscript is
       removed.  Notice that this is symmetric.

    So, under this system, the dictonary could have the words "Ill" and
    also the word "Ill."  It could also have the word "i.e.", which could be
    used in a sentence.  */

char * strip_left[] = {"(", "$", NULL};
char * strip_right[] = {")", "%", ",", ".", ":", ";", "?", "!", "'", "'s", NULL};

#define MAX_STRIP 10

int separate_word(char * w, char *wend, int is_first_word) {
/* w points to a string, wend points to the car one after the end.  The
 * "word" w contains no blanks.  This function splits up the word if
 * necessary, and calls "issue_sentence_word()" on each of the resulting
 * parts.  The process is described above.  returns TRUE of OK, FALSE if
 * too many punctuation marks */
    int i, len, n_stripped;
    int stripped[MAX_STRIP];  /* these were stripped from the right */
    char word[MAX_WORD+1];
    
    for (;;) {
	for (i=0; strip_left[i] != NULL; i++) {
	    if (strncmp(w, strip_left[i], strlen(strip_left[i])) == 0) {
		if (!issue_sentence_word(strip_left[i])) return FALSE;
		w += strlen(strip_left[i]);
		break;
	    }
	}
	if (strip_left[i] == NULL) break;
    }

    for (n_stripped = 0; n_stripped < MAX_STRIP; n_stripped++) {
	strncpy(word, w, wend-w);
	word[wend-w] = '\0';
	if (wend == w) break;  /* it will work without this */

	if (boolean_dictionary_lookup(word)) break;
	if (is_first_word && isupper(word[0])) {
	    word[0] = tolower(word[0]);
	    if (boolean_dictionary_lookup(word)) {
		word[0] = toupper(word[0]);  /* restore word to what it was */
		break;
	    }
	    word[0] = toupper(word[0]);
	}
	for (i=0; strip_right[i] != NULL; i++) {
	    len = strlen(strip_right[i]);
	    if ((wend-w) < len) continue;  /* the remaining w is too short for a possible match */
	    if (strncmp(wend-len, strip_right[i], len) == 0) {
		stripped[n_stripped] = i;
		wend -= len;
		break;
	    }
	}
	if (strip_right[i] == NULL) break;
    }

    /* word is now what remains after all the stripping has been done */
    
    if (n_stripped == MAX_STRIP) {
	printf("\"%s\" is followed by too many punctuation marks.\n", word);
	return FALSE;
    }

    if (!issue_sentence_word(word)) return FALSE;
    for (i=n_stripped-1; i>=0; i--) {
	if (!issue_sentence_word(strip_right[stripped[i]])) return FALSE;
    }
    return TRUE;
}

int separate_sentence(char * s) {
/* The string s has just been read in from standard input.
   This function breaks it up into words and stores these words in
   the sentence[] array.  Returns TRUE if all is well, FALSE otherwise.

   Quote marks '"' are treated just like blanks.
*/
    char *t;
    int is_first;

    N_words = 0; 

    if (left_wall_defined) if (!issue_sentence_word(LEFT_WALL_WORD)) return FALSE;
    
    is_first = TRUE;
    for(;;) {
	while(isspace(*s) || (*s == '\"')) s++;
	if (*s == '\0') break;
	for (t=s; !((isspace(*t) || (*t == '\"')) || *t=='\0'); t++);
	if (!separate_word(s, t, is_first)) return FALSE;
	is_first = FALSE;
	s = t;
	if (*s == '\0') break;
    }

    if (right_wall_defined) if (!issue_sentence_word(RIGHT_WALL_WORD)) return FALSE;

    return (N_words > left_wall_defined + right_wall_defined);
}


int isnumber(char * s) {
    if (!isdigit(*s)) return FALSE;
    for (; *s != '\0'; s++) {
	if ((!isdigit(*s)) && (*s != '.') && (*s != ',')) {
	    return FALSE;
	}
    }
    return TRUE;
}

int ishyphenated(char * s) {
/* returns TRUE iff it's an an appropritenly formed hyphenated word
   This means all letters, numbers, or hyphens, not beginning and
   ending with a hyphen.
*/
    int hyp, nonalpha;
    hyp = nonalpha = 0;
    if (*s == '-') return FALSE;
    while (*s != '\0') {
	if (!isalpha(*s) && !isdigit(*s) && (*s!='.') && (*s!=',')
	    && (*s!='-')) return FALSE;
	if (*s == '-') hyp++;
	s++;
    }
    return ((*(s-1)!='-') && (hyp>0));
}
/*
    sentence[0].e = build_word_expressions(WALL_WORD);
    if (sentence[0].e == NULL) {
	printf("Your dictionary needs a definition of the word \"%s"\n",
	         WALL_WORD);
	return FALSE;
    }
*/

void free_sentence_disjuncts(void) {
    int i;
    for (i=0; i<N_words; i++) {
	free_disjuncts(sentence[i].d);
    }
}

void free_sentence_expressions(void) {
    int i;
    for (i=0; i<N_words; i++) {
	free_X_nodes(sentence[i].x);
    }
}

int special_string(int i, char * s) {
    X_node * e;
    if (boolean_dictionary_lookup(s)) {
	sentence[i].x = build_word_expressions(s);
	for (e = sentence[i].x; e != NULL; e = e->next) {
	    e->string = sentence[i].string;
	}
	return TRUE;
    } else {
	printf("To process this sentence your dictionary ");
	printf("needs the word \"%s\".\n", s);
	return FALSE;
    }
}

void handle_unknown_word(int i, char * s) {
/* puts into sentence[i].x the expression for the unknown word */
/* the parameter s is the word that was not in the dictionary */    
/* it massages the names to have the corresponding subscripts */
/* to those of the unknown words */
/* so "grok" becomes "grok[?].v"  */
    char *t;
    X_node *d;
    char str[MAX_WORD+1];
    
    sentence[i].x = build_word_expressions(UNKNOWN_WORD);
    if (sentence[i].x == NULL) assert(FALSE, "UNKNOWN_WORD should have been there");

    for (d = sentence[i].x; d != NULL; d = d->next) {
	t = strchr(d->string, '.');
	if (t != NULL) {
	    sprintf(str, "%.50s[?].%.5s", s, t+1);
	} else {
	    sprintf(str, "%.50s[?]", s);
	}
	t = (char *) xalloc(strlen(str)+1);
	free_this_string_later(t, strlen(str)+1);
	strcpy(t,str);
	d->string = t;
    }
}

int build_sentence_expressions(void) {
/* Corrects case of first word, fills in other proper nouns, and
   builds the expression lists for the resulting words.

Algorithm:  
    Apply the following step to all words w:
         if w is in the dictionary, use it.
         else if w is upper case use PROPER_WORD disjuncts for w.
         else if it's hyphenated, use HYPHENATED_WORD
         else if it's a number, use NUMBER_WORD.

    Now, we correct the first word, w.
         if w is upper case, let w' be the lower case version of w.
             if both w and w' are in the dict, concatenate these disjncts.
	     else if w' is in dict, use disjuncts of w'
	     else leave the disjuncts alone
         else leave w alone.
*/
    int i;
    int first_word;  /* the index of the first word after the wall */
    char * s, *t;
    X_node * e;
    if (left_wall_defined) {
	first_word = 1;
    } else {
	first_word = 0;
    }

    /* the following loop treats all words the same (nothing special for 1st word) */
    for (i=0; i<N_words; i++) {
	s = sentence[i].string;
	if (boolean_dictionary_lookup(s)) {
	    sentence[i].x = build_word_expressions(s);
	} else if (isupper(s[0]) && capitalized_word_defined) {
	    if (!special_string(i,PROPER_WORD)) return FALSE;
	} else if (isnumber(s)){
            /* we know it's a plural number, or 1 */
            /* we'll only be here if 1's not in the dictionary */
	    if (!special_string(i,NUMBER_WORD)) return FALSE;
	} else if (ishyphenated(s)) {
	    /* singular hyphenated */
	    if (!special_string(i,HYPHENATED_WORD)) return FALSE;
	} else if (unknown_word_defined && use_unknown_word) {
	    /* Insert the unknown word here */
	    handle_unknown_word(i, s);
	} else {
	    /* the reason I can assert this is that the word
	       should have been looked up alread if we get here. */
	    assert(FALSE, "I should have found that word.");
	}
    }

    /* now we make corrections for the 1st word */

    s = sentence[first_word].string;
    if (isupper(s[0])) {
	t = (char *) xalloc(strlen(s)+1);
	free_this_string_later(t, strlen(s)+1);
	strcpy(t,s);
	t[0] = tolower(t[0]);
	if (boolean_dictionary_lookup(t)) {
	    if (boolean_dictionary_lookup(s)) {
		e = build_word_expressions(t);
		sentence[first_word].x = catenate_X_nodes(sentence[first_word].x, e);
	    } else {
		s[0] = tolower(s[0]);
		e = build_word_expressions(s);
		free_X_nodes(sentence[first_word].x);
		sentence[first_word].x = e;
	    }
	}
    }

/* The only difference between the code above and that below is that
   in the code above: if the first word is capitalized version of a lower
   case word in the dictionary, then it changes it to lower case in the
   sentence[first_word].string.  The version below never changes
   this array.  The change is only made in a new string that's allocated.
*/
/*
    s = sentence[first_word].string;
    if (isupper(s[0])) {
	t = (char *) xalloc(strlen(s)+1);
	free_this_string_later(t, strlen(s)+1);
	strcpy(t,s);
	t[0] = tolower(t[0]);
	if (boolean_dictionary_lookup(t)) {
	    e = build_word_expressions(t);
	    if (boolean_dictionary_lookup(s)) {
		sentence[first_word].e =
		  catenate_disjuncts(sentence[first_word].e, e);
	    } else {
		free_disjuncts(sentence[first_word].e);
		sentence[first_word].e = e;
	    }
	}
    }
*/

    return TRUE;
}



void print_statistics(void) {
    printf("\n");
    printf("%d parse cost\n", parse_cost);
    printf("%d mark cost\n", mark_cost);
    printf("%d in hash table\n", N_in_table);
    printf("%d hash lookups\n", N_hash_lookups);
    printf("%f cost per lookup\n",(float)work_in_hash_lookups/N_hash_lookups);
#ifndef SPEC_CPU2000
    printf("%d maximum bytes ever in use\n", max_space_in_use);
    printf("%d unreclaimed space\n", space_in_use);
#endif
}

void clean_up_string(char * s) {
/* gets rid of all the white space in the string s.  Changes s */
    char * x, * y;
    y = x = s;
    while(*x != '\0') {
	if (!isspace(*x)) {
	    *y = *x; x++; y++;
	} else {
	    x++;
	}
    }
    *y = '\0';
}

struct {char * s; int * p; int isboolean; char * str;} user_variable[] = {
    {"verbosity",           &verbosity,                0, "Level of detail to give about the computation"},
    {"width",               &screen_width,             0, "The width of your screen"},
    {"limit",               &linkage_count_limit,      0, "The maximum number of linkages processed"},
/*    {"maxlinklength",       &maxlinklength,            0, "The length of the maxium allowed link"}, */
/* The above variable is not useful given that the right wall and left wall are connected */
    {"graphics",            &display_on,               1, "Graphical link display"},
    {"multiple",            &display_multiple,         1, "Expansion of fat (conjunctive) linkages"},
    {"short",               &display_short,            1, "Reduced height display"},
    {"postscript",          &display_postscript,       1, "Generating of postscript data"},
    {"links",               &display_links,            1, "Showing of complete link data"},
    {"bad",                 &display_bad,              1, "Showing of linkages failing postprocessing"},
    {"fat",                 &display_fat,              1, "Showing of fat (conjunctive) linkages"},
    {"lsubscripts",         &display_link_subscripts,  1, "Showing of complete link labels"},
    {"wsubscripts",         &display_word_subscripts,  1, "Showing of word subscripts"},
    {"walls",               &display_walls,            1, "Always show the walls"},
    {"null",                &null_link_search,         1, "Null link search"},
    {"unknown",             &use_unknown_word,         1, "Using of the \"unknown word\" definition"},
    {"echo",                &echo_on,                  1, "Echoing of input sentence"},
    {"www",                 &www_mode,                 1, "Suppression of prompt"},
    {"justone",             &just_one,                 1, "Displaying of just one linkage"},
    {"",                    NULL,                      0, ""}
};

struct {char * s; char * str;} user_command[] = {
    {"quit",         "Exit the system"},
    {"save",         "Save your changes to the dictionary"},
    {"variables",    "List user-settable variables and their functions"},
    {"help",         "List the commands and what they do"},
    {NULL,           NULL}
};

int is_numerical_rhs(char *s) {
/* return TRUE if s points to a number:
   optional + or - followed by 1 or more
   digits.
*/
    if (*s=='+' || *s == '-') s++;
    do {
	if (!isdigit(*s)) return FALSE;
	s++;
    } while (*s != '\0');
    return TRUE;
}

void massage_variables(int j) {
/* make sure boolean variables are boolean and make sure assignment is consistent */
/* j is the variable that was just changed */    

    int i;
    for (i=0; user_variable[i].p != NULL; i++) {
	if (user_variable[i].isboolean) {
	    (*(user_variable[i].p)) = !!(*(user_variable[i].p));
	}
    }
    if (!display_on && (display_multiple || display_bad || display_fat)) {
	if (user_variable[j].p == &(display_on)) {
	    display_multiple = display_bad = display_fat = FALSE;
	} else {
	    display_on = TRUE;
	}
    } else if (display_on && !(display_multiple || display_bad || display_fat)) {
	if (user_variable[j].p == &(display_on)) {
	    display_multiple = TRUE;
	} else {
	    display_on = FALSE;
	}
    }
}

void special_command(char * line) {
    char *x, *y, *s;
    char myline[1000];
    int i, count, j, k;

    strncpy(myline, line, sizeof(myline));
    myline[sizeof(myline)-1] = '\0';
    clean_up_string(myline);
    s = myline;
    s++;  /* pass up the ! sign */
/*
    if (strcmp(s,"dictionary") == 0) {
	print_dictionary_words();
        return;
    }
*/
    j = k = -1;
    count = 0;
    for (i=0; user_variable[i].p != NULL; i++) {
	if (user_variable[i].isboolean && strncasecmp(s, user_variable[i].s, strlen(s)) == 0) {
	    count++;
	    j = i;
	}
    }
    for (i=0; user_command[i].s != NULL; i++) {
	if (strncasecmp(s, user_command[i].s, strlen(s)) == 0) {
	    count++;
	    k = i;
	}
    }

    if (count > 1) {
	printf("Ambiguous command.  Type \"!help\" or \"!variables\"\n");
	return;
    } else if (count == 1) {
	if (j >= 0) {
	    *(user_variable[j].p) = !(*(user_variable[j].p));
	    printf("%s turned %s.\n", user_variable[j].str, (*(user_variable[j].p))?"on":"off");
	    massage_variables(j);
	    return;
	} else {
	    strcpy(s, user_command[k].s);  /* replace the abbreviated command by the full one */
	}
    }

    if (strcmp(s,"quit") == 0) {
	if (!files_need_saving()) {
	    exit(1);
	} else {
	    printf("You have changed some files and not saved them.\n");
	    printf("Either save your files with \"!save\" and then quit,\n");
	    printf("or get out without saving your files with control-C.\n");
	}
	return;
    }

    if (strncmp(s, "mark", 4) == 0) {
	printf("mark: %s", line+6);  /* pass "!mark ".  the "line" contains a \n already */
	fflush(stdout);
	return;
    }

    if (strcmp(s,"save") == 0) {
	if (files_need_saving()) {
	    save_files();
	} else {
	    printf("No changes to be saved.\n");
	}
	return;
    }
    if (strcmp(s, "variables")==0) {
	printf(" Variable     Controls                                      Value\n");
	printf(" --------     --------                                      -----\n");
	for (i=0; user_variable[i].p != NULL; i++) {
	    printf(" ");
	    left_print_string(stdout, user_variable[i].s, "             ");
	    left_print_string(stdout, user_variable[i].str, "                                              ");
	    printf("%5d", *user_variable[i].p);
	    if (user_variable[i].isboolean) {
		if (*user_variable[i].p) printf(" (On)"); else printf(" (Off)");
	    }
	    printf("\n");
	}
	printf("\n");
	printf("Toggle a boolean variable as in \"!links\", set a variable as in \"!width=100\".\n");
	return;
    }
    if (strcmp(s, "help")==0) {
	printf("Special commands always begin with \"!\".  Command and variable names\n");
	printf("can be abbreviated.  Here is a list of the commands:\n\n");
	for (i=0; user_command[i].s != NULL; i++) {
	    printf(" !");
	    left_print_string(stdout, user_command[i].s, "                  ");
	    left_print_string(stdout, user_command[i].str, "                                                    ");
	    printf("\n");
	}
	printf("\n");
	printf(" !!<string>         Print all the dictionary words matching <string>.\n");
	printf("                    Also print the number of disjuncts of each.\n");
	printf("\n");
	printf(" !-<string>         Delete all the dictionary words matching <string>.\n");
	printf("\n");
	printf(" !<string>=<word>   This indicates that a new word (<string>) is to be\n");
	printf("                    added to the dictionary.  Its definition will be the\n");
	printf("                    same as that of <word>, and, if appropriate, it will\n");
	printf("                    be added to the word file of <word>.\n");
	printf("\n");
	printf(" !<var>             Toggle the specified boolean variable.\n");
	printf("\n");
	printf(" !<var>=<val>       Assign that value to that variable.\n");
	return;
    }

    if (s[0] == '!') {
    /* display the information about the given word */
	Dict_node * dn;
	Disjunct * d1, * d2;
	int len;
/*	if ((dn=abridged_lookup(s+1)) == NULL) {  */
	if ((dn=dictionary_lookup(s+1)) == NULL) {
	    printf("    \"%s\" matches nothing in the dictionary.\n", s+1);
	    return;
	}
	printf("Matches:\n");
	for (;dn != NULL; dn = dn->right) {
	    len=0;
	    d1 = build_disjuncts_for_dict_node(dn);
	    for(d2 = d1 ; d2!=NULL; d2 = d2->next){
		len++;
	    }
	    free_disjuncts(d1);
	    printf("          ");
	    left_print_string(stdout, dn->string, "                  ");
	    printf(" %5d  ", len);
	    if (dn->file != NULL) {
		printf("<%s>", dn->file->file);
	    }
	    printf("\n");
	}
	return;
    }
    if (*s == '-') {
	/* deleting of a word (or words) from the dictionary */
	Dict_node * dn, *dn1;
	int count;
	dn=abridged_lookup(s+1);
	count = 0;
	if (dn == NULL) {
	    printf("    \"%s\" matches nothing in the dictionary.\n", s+1);
	    return;
	}
/*
This is the version that will not delete nodes from the main dictionary.
To reinstall, the function "find_one_non_idiom_node" must also be changed.

        for (dn1 = dn; dn1 != NULL; dn1 = dn1->right) {
	    if (dn1->file != NULL) count++;
	}
	if (count==0) {
	 printf("    \"%s\" matches only words in the main dictionary.\n",s+1);
	 return;
	}
	printf("Deleting:\n");
	for (;dn != NULL; dn = dn->right) {
	    if (dn->file == NULL) continue;
	    printf(" %s ", dn->string);
	}
*/	
        for (dn1 = dn; dn1 != NULL; dn1 = dn1->right) {
	    if (dn1->file == NULL) count++;
	}
	if (count != 0) {
	    printf("Note: \"%s\" ", s+1);
	    printf("matches the following words in the main dictionary:\n");
	    for (dn1 = dn; dn1 != NULL; dn1 = dn1->right) {
		if (dn1->file == NULL) printf(" %s ", dn1->string);
	    }
	    printf("\n");
	}
	printf("Deleting:\n");
	for (dn1 = dn; dn1 != NULL; dn1 = dn1->right) {
	    printf(" %s ", dn1->string);
	}

	if (!delete_dictionary_words(s+1)) {
	    assert(FALSE, "Attempt to delete a word not in the dictonary.");
	}
	printf("\n");
	return;
    }
    /* test here for an equation */
    for (x=s; (*x != '=') && (*x != '\0') ; x++)
      ;
    if (*x == '=') {
	Dict_node * dn, * dn_new;
	*x = '\0';
	y = x+1;
	x = s;
	/* now x is the first word and y is the rest */

	if (is_numerical_rhs(y)) {
	    for (i=0; user_variable[i].p != NULL; i++) {
		if (strcmp(x, user_variable[i].s) == 0) break;
	    }
	    if (user_variable[i].p == NULL) {
		printf("There is no user variable called \"%s\".\n", x);
	    } else {
		*(user_variable[i].p) = atoi(y);
		printf("%s set to %d\n", x, atoi(y));
		massage_variables(i);
	    }
	    return;
	}
	if (is_idiom_word(x) || is_idiom_word(y)) {
	    printf("    words ending \".Ix\" (x a number) ");
	    printf("are reserved for idioms\n");
	    return;
	}
	if ((dn=abridged_lookup(x)) != NULL) {
	    printf("    \"%s\" matches words already in the dictionary:\n",s);
	    for (;dn != NULL; dn = dn->right) {
		printf("%s ", dn->string);
	    }
	    printf("\n");
	    return;
	}
	if ((dn=abridged_lookup(y)) == NULL) {
	    printf("    \"%s\" is not in the dictionary.\n", y);
	    return;
	}
	if ((dn->right != NULL) || (strcmp(y,dn->string) != 0)) {
	    printf("    Please be more precise.  \"%s\" matches:\n", y);
	    for (;dn != NULL; dn = dn->right) {
		printf("%s ", dn->string);
	    }
	    printf("\n");
	    return;
	}
	if (dn->file == NULL) {
	    printf("    \"%s\" is in the dictionary but not in a file.\n",y);
	    printf("    This word will not be saved.\n");
	}
	dn_new = (Dict_node *) xalloc(sizeof(Dict_node));
	dn_new->string = (char *) xalloc(strlen(x)+1);
	strcpy(dn_new->string, x);
	dn_new->left = dn_new->right = NULL;
	dn_new->file = dn->file;
	dn_new->exp = dn->exp;
	dict_root = insert_dict(dict_root, dn_new);
	printf("    \"%s\" added to the dictionary.\n", x);
	N_dict++;
	if (dn->file != NULL) dn->file->changed = TRUE;
	return;
    }
    printf("Try \"!help\".\n");
}

int sentence_in_dictionary(void){
    int w, ok_so_far;
    char * s;

    ok_so_far = TRUE;
    for (w=0; w<N_words; w++) {
	s = sentence[w].string;
	if (!boolean_dictionary_lookup(s) &&
	    !(isupper(s[0]) && (capitalized_word_defined)) &&
	    !ishyphenated(s) &&
	    !isnumber(s)) {
	    if (ok_so_far) {
		printf("The following words are not in the dictionary:");
		ok_so_far = FALSE;
	    }
	    printf(" \"%s\"", sentence[w].string);
	}
    }
    if (!ok_so_far) printf("\n");
    return ok_so_far;
}

int sentence_contains(char * s) {
/* Returns TRUE if one of the words in the sentence is s */
    int w;
    for (w=0; w<N_words; w++) {
	if (strcmp(sentence[w].string, s) == 0) return TRUE;
    }
    return FALSE;
}

void set_is_conjunction(void) {
    int w;
    char * s;
    for (w=0; w<N_words; w++) {
	s = sentence[w].string;
	is_conjunction[w] = ((strcmp(s, "and")==0) || (strcmp(s, "or" )==0) ||
			     (strcmp(s, "but")==0) || (strcmp(s, "nor")==0));
    }
}

int sentence_contains_conjunction(void) {
/* Return true if the sentence contains a conjunction.  Assumes
   is_conjunction[] has been initialized.
*/
    int w;
    for (w=0; w<N_words; w++) {
	if (is_conjunction[w]) return TRUE;
    }
    return FALSE;
}

int conj_in_range(int lw, int rw) {
/* Returns true if the range lw...rw inclusive contains a conjunction     */
    for (;lw <= rw; lw++) {
	if (is_conjunction[lw]) return TRUE;
    }
    return FALSE;
}

/*  Obsolete for tracking down a bug */
/*
void print_deletable(void) {
    int i,j;
    printf("null_links = %d\n", null_links);
    printf("N_words = %d\n", N_words);
    printf("maxlinklength = %d\n", maxlinklength);
    for (i=0; i<N_words; i++) {
	for (j=0; j<=MIN(i+maxlinklength, N_words); j++) {
	    printf("d[%2d][%2d] = %1d ", i, j, deletable[i][j]);
	}
	printf("\n");
    }
}
*/

void build_deletable(void) {
/* Initialize the array deletable[i][j] to indicate if the words           */
/* i+1...j-1 could be non existant in one of the multiple linkages.  This  */
/* array is used in conjunction_prune and power_prune.  Regions of length  */
/* 0 are always deletable.  A region of length two with a conjunction at   */
/* one end is always deletable.  Another observation is that for the       */
/* comma to form the right end of a deletable region, it must be the case  */
/* that there is a conjunction to the right of the comma.  Also, when      */
/* considering deletable regions with a comma on their left sides, there   */
/* must be a conjunction inside the region to be deleted. Finally, the     */
/* words "either", "neither", "both", "not" and "not only" are all         */
/* deletable.                                                              */
   
    int i,j,k;
    for (i=0; i<N_words; i++) {
	deletable[i] = (char *) xalloc(N_words+1);
	for (j=0; j<=MIN(i+maxlinklength, N_words); j++) {
	    if (null_links) {
		deletable[i][j] = TRUE;
	    } else if (j == i+1) {
		deletable[i][j] = TRUE;
	    } else if ((j>i+2)&&(is_conjunction[i+1] || is_conjunction[j-1] ||
                                (strcmp(",",sentence[i+1].string)==0 && conj_in_range(i+2,j-1)) ||
 	                        (strcmp(",",sentence[j-1].string)==0 && conj_in_range(j,N_words-1)))){
		deletable[i][j] = TRUE;
	    } else if (j > i) {
		for (k=i+1; k<j; k++) {
		    if ((strcmp("either", sentence[k].string) == 0) ||
			(strcmp("neither", sentence[k].string) == 0) ||
			(strcmp("both", sentence[k].string) == 0) ||
			(strcmp("not", sentence[k].string) == 0)) continue;
		    if ((strcmp("only", sentence[k].string)==0) && (k > i+1) &&
                                   (strcmp("not", sentence[k-1].string)==0)) continue;
		    break;
		}
		deletable[i][j] = (k==j);
	    } else {
		deletable[i][j] = FALSE;
	    }
	}
    }
}

void free_deletable(void) {
    int w;
    for (w=0; w<N_words; w++) {
	xfree((char *)deletable[w],N_words+1);
    }
}

void install_fat_connectors(void) {
/* Installs all the special fat disjuncts on all of the words of the   */
/* sentence */  
    int i;
    for (i=0; i<N_words; i++) {
	if (is_conjunction[i]) {
	    sentence[i].d = catenate_disjuncts(sentence[i].d,
			       build_AND_disjunct_list(sentence[i].string));
	} else {
	    sentence[i].d = catenate_disjuncts(sentence[i].d,
			       explode_disjunct_list(sentence[i].d));
	    if (strcmp(sentence[i].string, ",") == 0) {
		sentence[i].d = catenate_disjuncts(sentence[i].d,
					       build_COMMA_disjunct_list());
	    }
	}
    }
}

int compare_parse(Linkage_info * p1, Linkage_info * p2) {
/* for sorting the linkages */
    if (p1->N_violations != p2->N_violations) {
	return (p1->N_violations - p2->N_violations);
    } else if (p1->disjunct_cost != p2->disjunct_cost) {
	return (p1->disjunct_cost - p2->disjunct_cost);
    } else if (p1->and_cost != p2->and_cost) {
	return (p1->and_cost - p2->and_cost);
    } else {
	return (p1->link_cost - p2->link_cost);
    }
}

#if ! defined FOR_RELEASE

static double when_last_called;
static double when_parse_started;

double current_useage_time(void) {
/* returns the current useage time clock in seconds */
    struct rusage u;
    getrusage (RUSAGE_SELF, &u);
    return (u.ru_utime.tv_sec + ((double) u.ru_utime.tv_usec) / 1000000.0);
}

void clear_time(void) {
/* This clears the time variables */    
    when_last_called = when_parse_started = current_useage_time();
}

void print_time(char * s) {
/* print out the cpu ticks since this was last called */
    double new_t;
    new_t = current_useage_time();
    if (verbosity > 1) {
	printf("++++");
	left_print_string(stdout, s, "                                           ");
	printf("%7.2f seconds\n", new_t - when_last_called);
    }
    when_last_called = new_t;
}

void print_total_time(void) {
/* print out the cpu ticks since this was last called */
    double new_t;
    new_t = current_useage_time();
    cumulative_time += (new_t - when_parse_started) ;
    if (verbosity > 0) {
	printf("++++");
	left_print_string(stdout, "Total","                                           ");
	printf("%7.2f seconds (%7.2f total)\n", 
	       new_t - when_parse_started, cumulative_time);
    }
    when_parse_started = new_t;
}

#else
void clear_time(void) {}
void print_time(char * s) {
    if (verbosity > 1) {
	printf("++++%s\n", s);
    }
}
void print_total_time(void) {}
#endif

/* The following functions are used as follows.
    first_prepare_to_parse()
    prepare_to_parse(cost_cutoff);

    loop:
      If the cost cutoff changed then do:
  	    unprepare_parse();
            prepare_to_parse(cost_cutoff);

      Now parse the sentence [parse(null_count)]

    unprepare_to_parse();
    final_unprepare_to_parse()
*/

void first_prepare_to_parse(void) {
    if (echo_on) print_sentence(stdout, 2);
    if (verbosity > 2) {
	printf("Raw expression sizes:\n");
	print_expression_sizes();
    }
    expression_prune(); 
    print_time("Done expression pruning");
}

void prepare_to_parse(int cost_cutoff) {
/* assumes that the sentence expression lists have been generated     */
/* this does all the necessary pruning and building of and            */
/* structures.                                                        */
    int i;

    build_sentence_disjuncts(cost_cutoff);
    if (verbosity > 2) {
	printf("After expanding expressions into disjuncts:") ;
	print_disjunct_counts();
    }
    print_time("Built disjuncts");
    
    for (i=0; i<N_words; i++) {
	sentence[i].d = eliminate_duplicate_disjuncts(sentence[i].d);
    }
    print_time("Eliminated duplicate disjuncts");

    if (verbosity > 2) {
	printf("\nAfter expression pruning and duplicate elimination:\n");
	print_disjunct_counts();
    }

    set_is_conjunction();

    if (sentence_contains_conjunction()) {
	build_deletable();
	
	power_prune(GENTLE);
	if (verbosity > 2) {
	    printf("\nAfter Gentle power pruning:\n");
	    print_disjunct_counts();
	}
	print_time("Finished gentle power pruning");
	N_in_table = N_hash_lookups = work_in_hash_lookups = mark_cost = 0;
	conjunction_prune();
	if (verbosity > 2) {
	    printf("\nAfter conjunction pruning:\n");
	    print_disjunct_counts();
	    print_statistics();
	}
	free_deletable();
	print_time("Done conjunction pruning");
	build_conjunction_tables();
	install_fat_connectors();
	construct_either();      /* special connectors for "either" */
	construct_neither();     /* special connectors for "neither" */
	construct_notonlybut();  /* special connectors for "not..but.." */
	                             /* and               "not only..but.." */
	construct_both();        /* special connectors for "both..and.." */
	construct_comma();       /* special connectors for extra comma */
	if (verbosity > 2) {
	    printf("After conjunctions, disjuncts counts:\n");
	    print_disjunct_counts();
	}
	print_time("Constructed fat disjuncts");
	
	prune();
	print_time("Pruned fat disjuncts");
	
	for (i=0; i<N_words; i++) {
	    sentence[i].d = eliminate_duplicate_disjuncts(sentence[i].d);
	}
	if (verbosity > 2) {
	    printf("After pruning and duplicate elimination:\n");
	    print_disjunct_counts();
	}
	print_time("Eliminated duplicate disjuncts (again)");
	
	if (verbosity > 2) print_AND_statistics();
    }

    power_prune(RUTHLESS);

    if (verbosity > 2) {
	printf("\nAfter power-pruning:\n");
	print_disjunct_counts();
    }
    print_time("Ruthlessly power pruned");
    
    N_in_table = N_hash_lookups = work_in_hash_lookups = parse_cost = 0;
    
    init_fast_matcher();
    init_table();
    print_time("Initialized fast matcher and hash table");
}

void unprepare_parse(void) {
    free_sentence_disjuncts();      
    if (sentence_contains_conjunction()) free_AND_tables();
    free_fast_matcher();
    free_table();
}

void final_unprepare_parse(void) {
/* frees all the tables used for parsing.   */
    free_sentence_expressions();
    free_strings();
    free_lookup_list();  /* only necessary to make space_useage
			    statistic come out to zero.
			    (It will be freed later anyway) */
}

int compute_linkage_arrays(int index, int cost) {
/*  Simply calls extract_links(index) and set_has_fat_down().
    returns TRUE if there is a fat link in this linkage, FALSE
    otherwise
*/
    extract_links(index, cost);
    return (set_has_fat_down());
}

void summary_line(int N_canonical_linkages, int N_valid_linkages, char * stagen, int give_up) {
    if (N_canonical_linkages == 0) {
	if (give_up) {
	    printf("Not accepted (no linkage exists) at %s", stagen);
	} else {
	    printf("No linkages at %s", stagen);
	}
    } else if (N_canonical_linkages==1) {
	if  (N_valid_linkages == 0){
	    if (give_up) {
		printf("Not accepted (unique linkage with P.P. violation) at %s", stagen);
	    } else {
		printf("Unique linkage with P.P. violation at %s", stagen);
	    }
	} else {
	    printf("Accepted at %s", stagen);
	}
    } else {
	if (N_valid_linkages == 0) {
	    if (give_up) {
		printf("Not accepted (%d linkages, all with P.P. violations) at %s",   N_canonical_linkages, stagen);
	    }
	    else {
		printf("%d linkages (all with P.P. violations) at %s", N_canonical_linkages, stagen);
	    }
	} else {
	    printf("Accepted (%d linkages, %d with no P.P. violations) at %s", N_canonical_linkages, N_valid_linkages, stagen);
	}
    }
    if (display_bad) {
	printf(" (shown above)\n\n");
    } else {
	printf("\n");
    }
}

char * stage_name(int phase, int cost_cutoff, int null_count) {
    static char answer[100];
    int stage;
    if (phase == 0) {
	if (cost_cutoff <= 1) stage = 1; else stage = 2;
	sprintf(answer, "stage %d", stage);
    } else {
	sprintf(answer, "null count %d", null_count);
    }
    return answer;
}


void loop(void) {
    int i, N_to_display, index;
    int N_linkages;
    int N_canonical_linkages;
    int N_valid_linkages;
    int has_fatlinks;
    Linkage_info * linkage=NULL;
    char line[MAX_LINE], message[80];
    int line_set = FALSE;
    int cost_cutoff, old_cost_cutoff, maxcost, success, give_up, phase, just_entered_phase_1, null_count;
    char * stagen;

    /* mark_allocation_point(); */ /* Mark the allocation point for reuse */    
    for(;;) {
	null_links = FALSE;
	
	free_lookup_list(); /* to prevent spurious space-use message */
	free_strings();     /* ditto */
	max_space_in_use = 0;
	space_in_use = 0;
	/* reset_allocation_point(); */ /* Try to reuse the static memory */
	
	clear_time();  /* initialize the timing variables         */
	/* the above freeing operatins will not be */
	/* counted anywhere                        */
	
	if (!line_set) {
	    if (!www_mode) printf("> ");
	    if (www_mode) fflush(stdout);
	    if (fgets(line, MAX_LINE, stdin) == NULL) exit(1);
	}
	line_set = FALSE;
	if (line[strlen(line)-1] != '\n') {
	    printf("Your sentence is too long\n");
	    continue;
	}
	if (line[0] == '!') {
	    special_command(line);
	    continue;
	}
	if (!separate_sentence(line)) continue;
	if (N_words - left_wall_defined - right_wall_defined > word_count_limit) {
	    printf("Try a sentence with at most %d words.\n", word_count_limit);
	    continue;
	}
	if (!(unknown_word_defined && use_unknown_word)) {
	    if (!sentence_in_dictionary()) continue;
	}
	if (!build_sentence_expressions()) continue;
	maxcost = maxcost_of_sentence();
	
	print_time("Constructed disjunct expressions");
	
	first_prepare_to_parse();
	old_cost_cutoff = 1;
	prepare_to_parse(1);
	
	phase = 0;  /* phase 0 is no null links, phase 1 is null links */
	success = give_up = FALSE;
	cost_cutoff = 0;
	null_count = 0;
	while(!(success || give_up)) {
	    /* This is an initiation block for the loop.  The same code is used for
	       two different phases (first no null-links, then null-links) and within
	       each phase it's used several times.*/
	    just_entered_phase_1 = FALSE;
	    if (phase == 0) {
		/* Davy wants only 2 phases: (cost 0 or 1) and (cost > 1). */
	        if (cost_cutoff == 0) {
		    cost_cutoff = 1;
	        } else if (cost_cutoff == 1 && maxcost > 1) {
		    cost_cutoff = maxcost;
		} else {
		    phase = 1;    /* enter phase 1 */
		    null_links = TRUE;
		    cost_cutoff = NOCUTOFF;
		    just_entered_phase_1 = TRUE;
		}
		if (cost_cutoff == maxcost && !null_link_search) give_up = TRUE;
		/* the above makes it never even enter phase 1 if the null_link_search is off */
	    } else {
		null_count++;
		give_up = (null_count >= N_words-1);
		/* make this the last pass if we've maxed out the plausible number of null links */
		/* actually this is unnecessary, since it will always be accepted at N_words-1 null links. */
	    }
	    
	    if (verbosity > 2 && phase == 0) printf("Cost cutoff: %d\n", cost_cutoff);
	    
	    if (cost_cutoff != old_cost_cutoff) {
		unprepare_parse();
		prepare_to_parse(cost_cutoff);
		old_cost_cutoff = cost_cutoff;
	    }
	    
	    if (just_entered_phase_1) {
		/*		null_count = calc_min_cost(); */
		null_count = 1;  /* null_count 0 has already been handled in phase 0 */
	    }
	    stagen = stage_name(phase, cost_cutoff, null_count);
	    
	    if (phase == 0) {
		N_linkages = parse(0);
	    } else {
		N_linkages = parse(null_count);
	    }

	    if (N_linkages > linkage_count_limit) {
		printf("Warning: only the first %d of %d linkages will be considered.\n", linkage_count_limit, N_linkages);
		N_linkages = linkage_count_limit;
	    }
	    
	    sprintf(message, "Counted %d linkges", N_linkages);
	    print_time(message);
	    
	    N_canonical_linkages = N_valid_linkages = 0;
	    
	    if (N_linkages != 0) {
		linkage = (Linkage_info *)xalloc(N_linkages * sizeof(Linkage_info));
		for (index=0; index < N_linkages; index++) {
		    has_fatlinks = compute_linkage_arrays(index, null_count);
		    if (has_fatlinks) {
			if (!is_canonical_linkage()) continue;
			linkage[N_canonical_linkages] = analyze_fat_linkage(FALSE);
		    } else {
			linkage[N_canonical_linkages] = analyze_thin_linkage(FALSE);
		    }
		    if (linkage[N_canonical_linkages].N_violations == 0) {
			N_valid_linkages++;
		    }
		    linkage[N_canonical_linkages].index = index;
		    N_canonical_linkages ++;
		}
		qsort((void *)linkage, N_canonical_linkages, 
		      sizeof(Linkage_info),
		      (int (*)(const void *, const void *))compare_parse);
	    }
	    
	    assert(! ((N_canonical_linkages == 0) && (N_linkages > 0) && (N_linkages < linkage_count_limit)),
		   "None of the linkages is canonical");
	    
	    print_time("Postprocessed all linkages");
	    
	    line_set = FALSE;
	    success = (N_valid_linkages > 0);

	    /* put summary line at the end if in display bad mode */
	    if (!display_bad) summary_line(N_canonical_linkages, N_valid_linkages, stagen, give_up);

	    if (display_bad) {
		N_to_display = N_canonical_linkages;
	    } else {
		N_to_display = N_valid_linkages;
	    }
	    
	    if (display_on) {
		for (index=0; index < N_to_display; index++) {
		    has_fatlinks = compute_linkage_arrays(linkage[index].index, null_count);
		    compute_chosen_words();
		    if (N_canonical_linkages > 1) {
			printf("  Linkage %d", index+1);
		    } else {
			printf("  Unique linkage");
		    }
		    if (linkage[index].N_violations > 0) {
			printf(" (bad), ");
		    } else {
			printf(", ");
		    }
		    printf("cost vector = (%d, %d, %d)\n",
			   linkage[index].disjunct_cost,
			   linkage[index].and_cost,
			   linkage[index].link_cost);
		    if (has_fatlinks) {
			(void) analyze_fat_linkage(TRUE);
		    } else {
			(void) analyze_thin_linkage(TRUE);
		    }
		    if (index == N_to_display-1) break;
		    if (just_one) break;
		    if (www_mode) continue;  /* in www mode we never stop in the middle of a parse */
		    if (!display_bad) {
			/* on good linkages stop and wait for input, stream through bad ones */
			printf("(press return for another)\n");
			printf("> ");
			if (fgets(line, MAX_LINE, stdin) == NULL) exit(1);
			for (i=0; line[i] != '\0'; i++) if (!isspace(line[i])) break;
			if (line[i] != '\0') {
			    line_set = TRUE;
			    break;
			}
		    }
		}
	    }

	    if (display_bad) summary_line(N_canonical_linkages, N_valid_linkages, stagen, give_up);

	    if (N_linkages != 0) {
		xfree((char *) linkage, N_linkages*sizeof(Linkage_info));
	    }
	}
	
	print_time("Displayed linkages");
	unprepare_parse();
	final_unprepare_parse();
	print_time("Freed all data structures");
	
	if (verbosity > 2) print_statistics();
	if (space_in_use != 0){
	    printf("Warning: %d bytes of space leaked.\n", space_in_use);
	}
	print_total_time();
    }
}

void batch_process(void) {
    int i; 
    int N_linkages;
    int N_canonical_linkages;
    int N_valid_linkages;
    int index;
    int has_fatlinks;
    Linkage_info * linkage=NULL;

    char s[MAX_LINE];
    int errors;
    int mc;  /* the magic char */
    int cost_cutoff, old_cost_cutoff, maxcost, last_pass;

    null_links = FALSE;
    errors = 0;

    /* mark_allocation_point(); */ /* Mark the allocation point for reuse */
    for(;;) {
	free_lookup_list(); /* to prevent spurious space-use message */
	free_strings();     /* ditto */
	max_space_in_use = 0;
	space_in_use = 0;
	clear_time();
	/* reset_allocation_point(); */ /* Try to reuse the static memory */

	if (fgets(s, MAX_LINE, stdin) == NULL) break;
	if (s[strlen(s)-1] != '\n') {
	    printf("Sentence too long\n");
	    continue;
	}

	for (i=0; isspace(s[i]); i++);

	if (s[i] == '%') continue;   /* it's a comment line if the first non-blank char is a % sign */
	if (s[i] == '\0') continue;

	if ((s[i] == '*') || (s[i] == '+') || (s[i] == '#') || (s[i] == ':') || (s[i] == '-')) {
	    mc = s[i];
	    s[i] = ' ';
	} else {
	    mc = ' ';
	}
	 
	if (s[0] == '!') {
	    special_command(s);
	    continue;
	}
	if (!separate_sentence(s)) continue; /* blank lines are not an error */
	if (!(unknown_word_defined && use_unknown_word)) {
	    if (!sentence_in_dictionary()) {
		errors++;      /* an error if a word is not in the dictionary */
		printf("--- in the following sentence:\n");
		printf("%c ", mc);
		print_sentence(stdout, 2);
		printf("\n");
		continue;
	    }
	}
	if (!build_sentence_expressions()) {
	    errors++;
	    continue;
	}
	maxcost = maxcost_of_sentence();
	print_time("Constructed disjunct expressions");
	if (echo_on) printf("%c ", mc);

	first_prepare_to_parse();

	last_pass = FALSE;

	cost_cutoff = 0;
	old_cost_cutoff = 1;
	prepare_to_parse(1);
	
	while (!last_pass) {
	    if (cost_cutoff == 0) {
		cost_cutoff = 1;
	    } else if (cost_cutoff == 1 && maxcost > 1) {
		cost_cutoff = maxcost;
	    }

	    last_pass = (cost_cutoff >= maxcost);  /* this is the last pass through */
	    
	    if (verbosity > 2) printf("Cost cutoff: %d  maxcost: %d\n", cost_cutoff, maxcost) ;
	    
	    if (cost_cutoff != old_cost_cutoff) {
		unprepare_parse();
		prepare_to_parse(cost_cutoff);
		old_cost_cutoff = cost_cutoff;
	    }

	    N_linkages = parse(0);
	    print_time("Counted linkages");

	    N_canonical_linkages = N_valid_linkages = 0;

	    if (N_linkages != 0) {
		linkage = (Linkage_info *)xalloc(N_linkages*
						 sizeof(Linkage_info));

		for (index=0;(index < N_linkages) && (N_valid_linkages== 0);
		     index++) {
		    /* note that we break after finding the first 
		       valid linkage. */
		    has_fatlinks = compute_linkage_arrays(index, 0);
		    if (has_fatlinks) {
			if (!is_canonical_linkage()) continue;
			linkage[N_canonical_linkages]=
			    analyze_fat_linkage(FALSE);
		    } else {
			linkage[N_canonical_linkages]=
			    analyze_thin_linkage(FALSE);
		    }
		    if (linkage[N_canonical_linkages].N_violations == 0) {
			N_valid_linkages++;
		    }
		    linkage[N_canonical_linkages].index = index;
		    N_canonical_linkages ++;
		}
		qsort((void *)linkage, N_canonical_linkages, 
		      sizeof(Linkage_info),
		      (int (*)(const void *, const void *))compare_parse);
	    }

	    print_time("Postprocessed some linkages");
	    
	    if (N_canonical_linkages == 0) {
	      if (!((mc == '*') || (mc == '#'))) {
		if (last_pass) {
		  errors++;
		  if (!echo_on) {
		    printf("--- No linkage for (%s): ", stage_name(0, cost_cutoff, 0));
		    if (echo_on) printf("%c ", mc);
		    print_sentence(stdout, 13);
		  } else {
		    printf("--- No linkage for this (%s)\n", stage_name(0, cost_cutoff, 0));
		  }
		} else {
/*
			if (!echo_on) {
			   printf("--- No linkage at %s for: ", stage_name(0, cost_cutoff, 0)); 
			    if (echo_on) printf("%c ", mc);
			    print_sentence(stdout, 13);
			} else {
			    printf("--- No linkage at %s for this\n", stage_name(0, cost_cutoff, 0));
			} 
*/
		}
	      }
	    } else if (N_valid_linkages == 0) {
		if (!((mc == '+') || (mc == '*'))) {
		    if (last_pass) {
			if (N_canonical_linkages == 1) {
			    printf("--- unique linkage, with post-processing violation (%s)\n", stage_name(0, cost_cutoff, 0));
			} else {
			    printf("--- %d linkages", N_canonical_linkages);
			    printf(", all with post-processing violations");
			    printf(" (%s)\n",stage_name(0, cost_cutoff, 0));
			}
			errors++;
			has_fatlinks = 
			    compute_linkage_arrays(linkage[0].index, 0);
			compute_chosen_words();
			if (has_fatlinks) {
			    (void) analyze_fat_linkage(TRUE);
			} else {
			    (void) analyze_thin_linkage(TRUE);
			}
		    } else {
/*			if (N_canonical_linkages == 1) {
			    printf("--- unique linkage at %s,", stage_name(0, cost_cutoff, 0));
			    printf(" with post-processing violation\n");
			} else {
			    printf("--- %d linkages at %s", 
			           N_canonical_linkages, stage_name(0, cost_cutoff, 0));
			    printf(", all with post-processing violations\n");
			}*/
		    }
		  }
	    } else if ((mc == '+') || (mc == '*') || (mc == '#')) {
		errors++;
		if (!echo_on) {
		  printf("--- %s Input: ", stage_name(0, cost_cutoff, 0));
		  printf("%c ", mc);
		  print_sentence(stdout, 13);
		} else {
		  printf("--- Accepted %s:\n", stage_name(0, cost_cutoff, 0));
		}
		last_pass = 1;
		has_fatlinks = compute_linkage_arrays(linkage[0].index, 0);
		compute_chosen_words();
		if (has_fatlinks) {
		    (void) analyze_fat_linkage(TRUE);
		} else {
		    (void) analyze_thin_linkage(TRUE);
		}
	    } else if ((linkage[0].disjunct_cost == 0) && (mc == ':')) {
		errors++;
		if (!echo_on) {
		  printf("--- %s Input:  ", stage_name(0, cost_cutoff, 0));
		  printf("%c ", mc);
		  print_sentence(stdout, 13);
		} else {
		  printf("--- Accepted %s:\n", stage_name(0, cost_cutoff, 0));
		}
		last_pass = 1;
		printf("p.p. violations: %d, disjunct cost: %d\n",
		       linkage[0].N_violations, linkage[0].disjunct_cost);
		has_fatlinks = compute_linkage_arrays(linkage[0].index, 0);
		compute_chosen_words();
		if (has_fatlinks) {
		    (void) analyze_fat_linkage(TRUE);
		} else {
		    (void) analyze_thin_linkage(TRUE);
		}
	    } else if ((cost_cutoff == 1) && (mc == '-')) {
	      errors++;
	      if (!echo_on) {
		printf("--- %s Input: ", stage_name(0, cost_cutoff, 0));
		printf("%c ", mc);
		print_sentence(stdout, 13);
	      } else {
		  printf("--- Accepted %s:\n", stage_name(0, cost_cutoff, 0));
		}
		last_pass = 1;
		has_fatlinks = compute_linkage_arrays(linkage[0].index, 0);
		compute_chosen_words();
		if (has_fatlinks) {
		    (void) analyze_fat_linkage(TRUE);
		} else {
		    (void) analyze_thin_linkage(TRUE);
		}
	    } else if (FALSE && (cost_cutoff > 1) && (mc == ' ')) {
		/* I eliminated this case for the purpose of the SPEC test */
		/* So you don't have to preceed stage 2 accepted sentences with */
		/* "-" */
		   
	      errors++;
	      if (!echo_on) {
		  printf("--- %s Input: ", stage_name(0, cost_cutoff, 0));
		  printf("%c ", mc);
		  print_sentence(stdout, 13);
		} else {
		  printf("--- Accepted %s:\n", stage_name(0, cost_cutoff, 0));
		}
	      last_pass = 1;
	      has_fatlinks = compute_linkage_arrays(linkage[0].index, 0);
	      compute_chosen_words();
	      if (has_fatlinks) {
		  (void) analyze_fat_linkage(TRUE);
	      } else {
		  (void) analyze_thin_linkage(TRUE);
	      }
	      
	    } else {
		last_pass = 1;
		/*		printf("OK-> %s\n", s); */
	    }
	    if (N_linkages != 0) {
		xfree((char *) linkage, N_linkages*sizeof(Linkage_info));
	    }
	}

	fflush(stdout);
	print_time("Displayed linkages");
	unprepare_parse();
	final_unprepare_parse();
	print_time("Freed all data structures");

	if (verbosity > 2) print_statistics();
	if (space_in_use != 0){
	    printf("Warning: %d bytes of space leaked.\n", space_in_use);
	}
	print_total_time();
    }
    if (errors == 0) {
	printf("No errors!\n");
    } else if (errors == 1) {
	printf("One error.\n");
    } else {
	printf("%d errors.\n", errors);
    }
}

int main(int argc, char** argv) {
    int batch;
    int prob;
    int i;
    
    (void) initialize_memory();
    prob = FALSE;
    batch = FALSE;
    for (i=2; i<argc && !prob; i++) {
	if (strcmp(argv[i], "-wordlimit") == 0) {
	    prob = (i == argc-1 || (sscanf(argv[i+1], "%d", &word_count_limit) != 1));
	    i++;
	} else if (strcmp(argv[i], "-linklimit") == 0) {
	    prob = (i == argc-1 || (sscanf(argv[i+1], "%d", &linkage_count_limit) != 1));
	    i++;
	} else if (strcmp(argv[i], "-batch") == 0) {
	    batch = TRUE;
	}
    }	    
    if ((argc < 2) || prob) {
	fprintf(stderr, "Usage: %s dictionary-file [-batch] [-wordlimit number] [-linklimit number]\n", argv[0]);
	exit(1);
    }

    open_dictionary(argv[1]);
    printf("\n Reading the dictionary files: ");
    read_dictionary();
#ifndef SPEC_CPU2000
    printf("\n %d words stored in %d bytes\n\n\n", N_dict, space_in_use);
#else
    printf("\n\n\n");
#endif

    printf("Welcome to the Link Parser -- Version 2.1\n\n");
    printf("          ");
    printf("Copyright (C) 1991-1995 Daniel Sleator and Davy Temperley\n\n");
    
    init_randtable();

    left_wall_defined = boolean_dictionary_lookup(LEFT_WALL_WORD);
    right_wall_defined = boolean_dictionary_lookup(RIGHT_WALL_WORD);
    postprocess_defined = boolean_dictionary_lookup(POSTPROCESS_WORD);
    andable_defined = boolean_dictionary_lookup(ANDABLE_CONNECTORS_WORD);
    unknown_word_defined = boolean_dictionary_lookup(UNKNOWN_WORD);
    capitalized_word_defined = boolean_dictionary_lookup(PROPER_WORD);

    if (andable_defined) {
	init_andable_hash_table();
    }

    if (batch) {
	printf("Processing sentences in batch mode\n");
	printf("\n");
	batch_process();
    } else {
	printf("Type your sentence and press Return ");
	printf("(\"!help\" for options).\n");
	printf("\n");
	loop();
    }
    return 0;
}
