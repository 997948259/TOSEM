 /***************************************************************************/
 /*                                                                         */
 /* This link grammar system is copyright (C) 1991-1997 by Daniel Sleator   */
 /* (sleator@cs.cmu.edu) and Davy Temperley.  This is work in progress.     */
 /* See http://www.cs.cmu.edu/~sleator for announcements of the latest      */
 /* version, detailed documentation, and rules for commercial use.          */
 /*                                                                         */
 /***************************************************************************/

#include "header.h"

static int center[MAX_SENTENCE];
char * chosen_words[MAX_SENTENCE];

static int N_words_to_print;  /* version of N_words in this file for printing links */

void set_centers(int print_word_0) {
    int i, len, tot;
    tot = 0;
    if (print_word_0) i=0; else i=1;
    for (; i<N_words_to_print; i++) {
	len = strlen(chosen_words[i]);
	center[i] = tot + (len/2);
	tot += len+1;
    }
}

/* the following are all for generating postscript */
static int link_heights[MAX_LINKS];
  /* tells the height of the links above the sentence */
static int row_starts[MAX_SENTENCE];
  /* the word beginning each row of the display */
static int N_rows;
  /* the number of rows */

void print_postscript_data(FILE *fp, int print_word_0, int print_word_N) {
    int link, i,j;
    int d;

    if (print_word_0) d=0; else d=1;

    i = 0;
    fprintf(fp,"[");
    for (j=d; j<N_words_to_print; j++) {
	if ((i%7 == 0) && (i>0)) fprintf(fp,"\n");
	i++;
	fprintf(fp,"(%s)",chosen_words[j]);
    }
    fprintf(fp,"]");
    fprintf(fp,"\n");

    fprintf(fp,"[");
    j = 0;
    for (link=0; link<N_links; link++) {
	if (!print_word_0 && (pp_link_array[link].l == 0)) continue;
	if (!print_word_N && (pp_link_array[link].r == N_words-1)) continue;
	if (pp_link_array[link].l == -1) continue;
	if ((j%5 == 0) && (j>0)) fprintf(fp,"\n");
	j++;
	fprintf(fp,"[%d %d %d",
		pp_link_array[link].l-d, pp_link_array[link].r-d, link_heights[link]);
	if (pp_link_array[link].lc->label < 0) {
	    fprintf(fp," (%s)]", pp_link_array[link].name);
	} else {
	    fprintf(fp," ()]");
	}
    }
    fprintf(fp,"]");
    fprintf(fp,"\n");
    fprintf(fp,"[");
    for (j=0; j<N_rows; j++ ){
	fprintf(fp,"%d ", row_starts[j]);
    }
    fprintf(fp,"]\n");
}

void compute_chosen_words(void) {
    /*
       This takes the current chosen_disjuncts array and uses it to
       compute the chosen_words array.  "I.xx" suffixes are eliminated.
       */
    int i, l;
    char * s, *t, *u;
    for (i=0; i<N_words; i++) {   /* get rid of those ugly ".Ixx" */
	chosen_words[i] = sentence[i].string;
	if (chosen_disjuncts[i] == NULL) {  /* no disjunct is used on this word because of null-links */
	    t = chosen_words[i];
	    l = strlen(t) + 2;
	    s = (char *) xalloc(l+1);
	    sprintf(s, "[%s]", t);
	    free_this_string_later(s, l+1);
	    chosen_words[i] = s;
	} else if (display_word_subscripts) {
	    t = chosen_disjuncts[i]->string;	
	    if (is_idiom_word(t)) {
		l = strlen(t);
		s = (char *) xalloc(l+1);
		free_this_string_later(s, l+1);
		strcpy(s,t);
		for (u=s; *u != '.'; u++)
		  ;
		*u = '\0';
		chosen_words[i] = s;
	    } else {
		chosen_words[i] = t;
	    }
	}
    }
    if (left_wall_defined) {
	chosen_words[0] = LEFT_WALL_DISPLAY;
    }
    if (right_wall_defined) {
	chosen_words[N_words-1] = RIGHT_WALL_DISPLAY;
    }
}


#define MAX_HEIGHT 30

static char picture[MAX_HEIGHT][MAX_LINE];
static char xpicture[MAX_HEIGHT][MAX_LINE];

void print_links_graphically(FILE *fp) {
/* print the diagram using globals: pp_link_array[], N_links, chosen_words[] */

    int i, j, k, cl, cr, row, top_row, width, flag;
    char *t, *s;
    int print_word_0 = 0, print_word_N = 0, N_wall_connectors, suppressor_used;
    char connector[MAX_TOKEN_LENGTH];
    int line_len, link_length;

    N_wall_connectors = 0;
    if (left_wall_defined) {
	suppressor_used = FALSE;
	for (j=0; j<N_links; j++) {
	    if (pp_link_array[j].l == 0) {
		N_wall_connectors ++;
		if (strcmp(pp_link_array[j].lc->string, LEFT_WALL_SUPPRESS)==0){
		    suppressor_used = TRUE;
		}
	    }
	}
	print_word_0 = (!suppressor_used) || (N_wall_connectors > 1) || display_walls;
    } else {
	print_word_0 = TRUE;
    }

    N_wall_connectors = 0;
    if (right_wall_defined) {
	suppressor_used = FALSE;
	for (j=0; j<N_links; j++) {
	    if (pp_link_array[j].r == N_words-1) {
		N_wall_connectors ++;
		if (strcmp(pp_link_array[j].lc->string, RIGHT_WALL_SUPPRESS)==0){
		    suppressor_used = TRUE;
		}
	    }
	}
	print_word_N = (!suppressor_used) || (N_wall_connectors > 1) || display_walls;
    } else {
	print_word_N = TRUE;
    }

    N_words_to_print = N_words;
    if (!print_word_N) N_words_to_print--;
    
    set_centers(print_word_0);
    line_len = center[N_words_to_print-1]+1;
    
    for (k=0; k<MAX_HEIGHT; k++) {
	for (j=0; j<line_len; j++) picture[k][j] = ' ';
	picture[k][line_len] = '\0';
    }
    top_row = 0;
    
    for (link_length = 1; link_length < N_words_to_print; link_length++) {
	for (j=0; j<N_links; j++) {
	    if (pp_link_array[j].l == -1) continue;
	    if ((pp_link_array[j].r - pp_link_array[j].l) != link_length)
	      continue;
	    if (!print_word_0 && (pp_link_array[j].l == 0)) continue;
	    /* gets rid of the irrelevant link to the left wall */
	    if (!print_word_N && (pp_link_array[j].r == N_words-1)) continue;	    
	    /* gets rid of the irrelevant link to the right wall */

	    /* put it into the lowest position */
	    cl = center[pp_link_array[j].l];
	    cr = center[pp_link_array[j].r];
	    for (row=0; row < MAX_HEIGHT; row++) {
		for (k=cl+1; k<cr; k++) {
		    if (picture[row][k] != ' ') break;
		}
		if (k == cr) break;
	    }
	    /* we know it fits, so put it in this row */

	    link_heights[j] = row;
	    
	    if (2*row+2 > MAX_HEIGHT-1) {
		fprintf(fp,"The diagram is too high.\n");
		return;
	    }
	    if (row > top_row) top_row = row;
	    
	    picture[row][cl] = '+';
	    picture[row][cr] = '+';
	    for (k=cl+1; k<cr; k++) {
		picture[row][k] = '-';
	    }
	    /* s = pp_link_array[j].lc->string; changed 1/11/95 by dennis */
	    s = pp_link_array[j].name;
	    
	    if (display_link_subscripts) {
	      if (!isalpha(*s))
		s = "";
	    } else {
	      if (!isupper(*s)) {
		s = "";   /* Don't print fat link connector name */
	      }
	    }
	    strncpy(connector, s, MAX_TOKEN_LENGTH-1);
	    connector[MAX_TOKEN_LENGTH-1] = '\0';
	    k=0;
	    if (display_link_subscripts)
	      k = strlen(connector);
	    else
	      for (t=connector; isupper(*t); t++) k++; /* uppercase len of conn*/
	    if ((cl+cr-k)/2 + 1 <= cl) {
		t = picture[row] + cl + 1;
	    } else {
		t = picture[row] + (cl+cr-k)/2 + 1;
	    }
	    s = connector;
	    if (display_link_subscripts)
	      while((*s != '\0') && (*t == '-')) *t++ = *s++; 
	    else
	      while(isupper(*s) && (*t == '-')) *t++ = *s++; 

	    /* now put in the | below this one, where needed */
	    for (k=0; k<row; k++) {
		if (picture[k][cl] == ' ') {
		    picture[k][cl] = '|';
		}
		if (picture[k][cr] == ' ') {
		    picture[k][cr] = '|';
		}
	    }
	}
    }
    
    /* we have the link picture, now put in the words and extra "|"s */
    
    s = xpicture[0];
    if (print_word_0) k = 0; else k = 1;
    for (; k<N_words_to_print; k++) {
	t = chosen_words[k];
	i=0;
	while(*t != '\0') {
	    *s++ = *t++;
	    i++;
	}
	*s++ = ' ';
    }
    *s = '\0';
    
    if (display_short) {
	for (k=0; picture[0][k] != '\0'; k++) {
	    if ((picture[0][k] == '+') || (picture[0][k] == '|')) {
		xpicture[1][k] = '|';
	    } else {
		xpicture[1][k] = ' ';
	    }
	}
	xpicture[1][k] = '\0';
	for (row=0; row <= top_row; row++) {
	    strcpy(xpicture[row+2],picture[row]);
	}
	top_row = top_row+2;
    } else {
	for (row=0; row <= top_row; row++) {
	    strcpy(xpicture[2*row+2],picture[row]);
	    for (k=0; picture[row][k] != '\0'; k++) {
		if ((picture[row][k] == '+') || (picture[row][k] == '|')) {
		    xpicture[2*row+1][k] = '|';
		} else {
		    xpicture[2*row+1][k] = ' ';
		}
	    }
	    xpicture[2*row+1][k] = '\0';
	}
	top_row = 2*top_row + 2;
    }
    
    /* we've built the picture, now print it out */
    
    if (print_word_0) i = 0; else i = 1;
    k = 0;
    N_rows = 0;
    row_starts[N_rows] = 0;
    N_rows++;
    while(i < N_words_to_print) {
	putc('\n',fp);
	width = 0;
	do {
	    width += strlen(chosen_words[i])+1;
	    i++;
	} while((i<N_words_to_print) &&
	      (width + ((int) strlen(chosen_words[i]))+1 < screen_width));
	row_starts[N_rows] = i - (!print_word_0);    /* PS junk */
	if (i<N_words_to_print) N_rows++;     /* same */
	for (row = top_row; row >= 0; row--) {
	    flag = TRUE;
	    for (j=k;flag&&(j<k+width)&&(xpicture[row][j]!='\0'); j++){
		flag = flag && (xpicture[row][j] == ' ');
	    }
	    if (!flag) {
		for (j=k;(j<k+width)&&(xpicture[row][j]!='\0'); j++){
		    putc(xpicture[row][j], fp);
		}
		putc('\n', fp);
	    }
	}
	putc('\n', fp);
	k += width;
    }
    if (display_postscript) print_postscript_data(fp, print_word_0, print_word_N);
}

void print_disjunct_counts(void) {
    int i;
    int c;
    Disjunct *d;
    for (i=0; i<N_words; i++) {
	c = 0;
	for (d=sentence[i].d; d != NULL; d = d->next) {
	    c++;
	}
	printf("%s(%d) ",sentence[i].string, c);
    }
    printf("\n\n");
}

void print_expression_sizes(void) {
    X_node * x;
    int w, size;
    for (w=0; w<N_words; w++) {
	size = 0;
	for (x=sentence[w].x; x!=NULL; x = x->next) {
	    size += size_of_expression(x->exp);
	}
	printf("%s[%d] ",sentence[w].string, size);
    }
    printf("\n\n");
}

void print_sentence(FILE *fp, int w) {
/* this version just prints it on one line.  */
    int i;
    if (left_wall_defined) i=1; else i=0;
    if (w == 0) i+=w;      /* a noop command to stop a pedantic compiler message */
    for (; i<N_words - right_wall_defined; i++) {
	fprintf(fp, "%s ", sentence[i].string);
    }
    fprintf(fp, "\n");
}
