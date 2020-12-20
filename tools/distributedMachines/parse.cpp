
/*  A Bison parser, made from nf.y with Bison version GNU Bison version 1.24
*/

#define YYBISON 1  /* Identify Bison output.  */

#define	ERROR_TOKEN	258
#define	OPEN_PAR	259
#define	CLOSE_PAR	260
#define	PROJECTION	261
#define	MY_TRUE	262
#define	MY_FALSE	263
#define	MY_EMPTY	264
#define	MY_SKIP	265
#define	MY_MORE	266
#define	COMMA	267
#define	CHOP	268
#define	IMPLY	269
#define	IFF	270
#define	OR	271
#define	AND	272
#define	UNTIL	273
#define	NEGATION	274
#define	NEXT	275
#define	W_NEXT	276
#define	STIME	277
#define	ALWAYS	278
#define	LENGTH	279
#define	CHOPSTAR	280
#define	MY_FIN	281
#define	ID	282
#define	INTEGER	283

#line 1 "nf.y"

#include <malloc.h>
#include <string.h>      // strcpy
#include "lex.h"
#include "TreeNode.h"

SyntaxTree  g_syntaxTree = NULL;

void yyerror(char *msg);

#define YYDEBUG 1	          // Generate debug code; needed for YYERROR_VERBOSE
#define YYERROR_VERBOSE       // Give a more specific parse error message


#line 16 "nf.y"
typedef union{
	char      *cString;   /* A character string */
	int       nInteger;   /* An integer value */
	CTreeNode *tnode;    /* Node in the syntax tree */
} YYSTYPE;

#ifndef YYLTYPE
typedef
struct yyltype
{
	int timestamp;
	int first_line;
	int first_column;
	int last_line;
	int last_column;
	char *text;
}
yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		54
#define	YYFLAG		-32768
#define	YYNTBASE	29

#define YYTRANSLATE(x) ((unsigned)(x) <= 283 ? yytranslate[x] : 34)

static const char yytranslate[] = { 0,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 1, 2, 3, 4, 5,
6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
26, 27, 28
};

#if YYDEBUG != 0
static const short yyprhs[] = { 0,
0, 2, 4, 8, 12, 16, 20, 24, 28, 32,
35, 38, 41, 44, 47, 50, 52, 55, 57, 59,
61, 63, 66, 73, 79, 83, 84, 86, 90
};

static const short yyrhs[] = { 30,
0, 33, 0, 4, 30, 5, 0, 30, 14, 30,
0, 30, 15, 30, 0, 30, 17, 30, 0, 30,
16, 30, 0, 30, 13, 30, 0, 30, 18, 30,
0, 30, 25, 0, 19, 30, 0, 20, 30, 0,
21, 30, 0, 23, 30, 0, 22, 30, 0, 7,
0, 26, 30, 0, 8, 0, 9, 0, 10, 0,
11, 0, 24, 32, 0, 4, 30, 31, 5, 6,
30, 0, 4, 30, 5, 6, 30, 0, 12, 30,
31, 0, 0, 27, 0, 4, 32, 5, 0, 27,
0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
46, 49, 50, 51, 52, 53, 54, 55, 56, 57,
58, 59, 60, 61, 62, 63, 64, 65, 66, 67,
68, 69, 70, 72, 76, 80, 83, 84, 87
};

static const char * const yytname[] = { "$", "error", "$undefined.", "ERROR_TOKEN",
"OPEN_PAR", "CLOSE_PAR", "PROJECTION", "MY_TRUE", "MY_FALSE", "MY_EMPTY", "MY_SKIP",
"MY_MORE", "COMMA", "CHOP", "IMPLY", "IFF", "OR", "AND", "UNTIL", "NEGATION", "NEXT",
"W_NEXT", "STIME", "ALWAYS", "LENGTH", "CHOPSTAR", "MY_FIN", "ID", "INTEGER", "program",
"statement", "optional_projection", "int_exp", "identifier", ""
};
#endif

static const short yyr1[] = { 0,
29, 30, 30, 30, 30, 30, 30, 30, 30, 30,
30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
30, 30, 30, 30, 31, 31, 32, 32, 33
};

static const short yyr2[] = { 0,
1, 1, 3, 3, 3, 3, 3, 3, 3, 2,
2, 2, 2, 2, 2, 1, 2, 1, 1, 1,
1, 2, 6, 5, 3, 0, 1, 3, 1
};

static const short yydefact[] = { 0,
0, 16, 18, 19, 20, 21, 0, 0, 0, 0,
0, 0, 0, 29, 1, 2, 0, 11, 12, 13,
15, 14, 0, 27, 22, 17, 0, 0, 0, 0,
0, 0, 10, 3, 0, 0, 0, 8, 4, 5,
7, 6, 9, 0, 26, 0, 28, 24, 25, 0,
23, 0, 0, 0
};

static const short yydefgoto[] = { 52,
15, 36, 25, 16
};

static const short yypact[] = { 31,
31, -32768, -32768, -32768, -32768, -32768, 31, 31, 31, 31,
31, -3, 31, -32768, 0, -32768, 51, -20, -20, -20,
-20, -20, -3, -32768, -32768, -20, 31, 31, 31, 31,
31, 31, -32768, 13, 31, 15, 16, 70, -14, -14,
19, 71, 71, 31, 65, 17, -32768, 0, -32768, 31,
0, 22, 32, -32768
};

static const short yypgoto[] = { -32768,
-1, -12, 23, -32768
};


#define	YYLAST		96


static const short yytable[] = { 17,
23, 30, 31, 32, -32768, 18, 19, 20, 21, 22,
33, 26, 27, 28, 29, 30, 31, 32, 44, 46,
47, 53, 50, 24, 33, 38, 39, 40, 41, 42,
43, 54, 49, 45, 1, 31, 32, 2, 3, 4,
5, 6, 48, 33, 0, 37, 0, 0, 51, 7,
8, 9, 10, 11, 12, 34, 13, 14, 0, 0,
0, 0, 35, 27, 28, 29, 30, 31, 32, 0,
0, 0, 0, 0, 0, 33, 35, 27, 28, 29,
30, 31, 32, 28, 29, 30, 31, 32, 32, 33,
0, 0, 0, 0, 33, 33
};

static const short yycheck[] = { 1,
4, 16, 17, 18, 25, 7, 8, 9, 10, 11,
25, 13, 13, 14, 15, 16, 17, 18, 6, 5,
5, 0, 6, 27, 25, 27, 28, 29, 30, 31,
32, 0, 45, 35, 4, 17, 18, 7, 8, 9,
10, 11, 44, 25, -1, 23, -1, -1, 50, 19,
20, 21, 22, 23, 24, 5, 26, 27, -1, -1,
-1, -1, 12, 13, 14, 15, 16, 17, 18, -1,
-1, -1, -1, -1, -1, 25, 12, 13, 14, 15,
16, 17, 18, 14, 15, 16, 17, 18, 18, 25,
-1, -1, -1, -1, 25, 25
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
Bison output file, you may use that output file without restriction.
This special exception was added by the Free Software Foundation
in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
#pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
	void *alloca(unsigned int);
};
#else /* not __cplusplus */
void *alloca();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
when the %semantic_parser declaration is not specified in the grammar.
It was written by Richard Stallman by simplifying the hairy parser
used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
It is replaced by the list of actions, each action
as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
This remains here temporarily to ease the
transition to the new meaning of YYERROR, for GCC.
Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
      { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
      }								\
    else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
	while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
(effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse(void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
in available built-in functions on various systems.  */
static void
__yy_memcpy(from, to, count)
char *from;
char *to;
int count;
{
	register char *f = from;
	register char *t = to;
	register int i = count;

	while (i-- > 0)
		*t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
in available built-in functions on various systems.  */
static void
__yy_memcpy(char *from, char *to, int count)
{
	register char *f = from;
	register char *t = to;
	register int i = count;

	while (i-- > 0)
		*t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
into yyparse.  The argument should have type void *.
It should actually point to an object.
Grammar actions can access the variable by casting it
to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
YYPARSE_PARAM_DECL
{
	register int yystate;
	register int yyn;
	register short *yyssp;
	register YYSTYPE *yyvsp;
	int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
	int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

	short	yyssa[YYINITDEPTH];	/*  the state stack			*/
	YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

	short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
	YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
	YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
	YYLTYPE *yyls = yylsa;
	YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

	int yystacksize = YYINITDEPTH;

#ifdef YYPURE
	int yychar;
	YYSTYPE yylval;
	int yynerrs;
#ifdef YYLSP_NEEDED
	YYLTYPE yylloc;
#endif
#endif

	YYSTYPE yyval;		/*  the variable used to return		*/
	/*  semantic values from the action	*/
	/*  routines				*/

	int yylen;

#if YYDEBUG != 0
	if (yydebug)
		fprintf(stderr, "Starting parse\n");
#endif

	yystate = 0;
	yyerrstatus = 0;
	yynerrs = 0;
	yychar = YYEMPTY;		/* Cause a token to be read.  */

	/* Initialize stack pointers.
	Waste one element of value and location stack
	so that they stay on the same level as the state stack.
	The wasted elements are never initialized.  */

	yyssp = yyss - 1;
	yyvsp = yyvs;
#ifdef YYLSP_NEEDED
	yylsp = yyls;
#endif

	/* Push a new state, which is found in  yystate  .  */
	/* In all cases, when you get here, the value and location stacks
	have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

	*++yyssp = yystate;

	if (yyssp >= yyss + yystacksize - 1)
	{
		/* Give user a chance to reallocate the stack */
		/* Use copies of these so that the &'s don't force the real ones into memory. */
		YYSTYPE *yyvs1 = yyvs;
		short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
		YYLTYPE *yyls1 = yyls;
#endif

		/* Get the current used size of the three stacks, in elements.  */
		int size = yyssp - yyss + 1;

#ifdef yyoverflow
		/* Each stack pointer address is followed by the size of
		the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
		/* This used to be a conditional around just the two extra args,
		but that might be undefined if yyoverflow is a macro.  */
		yyoverflow("parser stack overflow",
			&yyss1, size * sizeof(*yyssp),
			&yyvs1, size * sizeof(*yyvsp),
			&yyls1, size * sizeof(*yylsp),
			&yystacksize);
#else
		yyoverflow("parser stack overflow",
			&yyss1, size * sizeof(*yyssp),
			&yyvs1, size * sizeof(*yyvsp),
			&yystacksize);
#endif

		yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
		yyls = yyls1;
#endif
#else /* no yyoverflow */
		/* Extend the stack our own way.  */
		if (yystacksize >= YYMAXDEPTH)
		{
			yyerror("parser stack overflow");
			return 2;
		}
		yystacksize *= 2;
		if (yystacksize > YYMAXDEPTH)
			yystacksize = YYMAXDEPTH;
		yyss = (short *)alloca(yystacksize * sizeof(*yyssp));
		__yy_memcpy((char *)yyss1, (char *)yyss, size * sizeof(*yyssp));
		yyvs = (YYSTYPE *)alloca(yystacksize * sizeof(*yyvsp));
		__yy_memcpy((char *)yyvs1, (char *)yyvs, size * sizeof(*yyvsp));
#ifdef YYLSP_NEEDED
		yyls = (YYLTYPE *)alloca(yystacksize * sizeof(*yylsp));
		__yy_memcpy((char *)yyls1, (char *)yyls, size * sizeof(*yylsp));
#endif
#endif /* no yyoverflow */

		yyssp = yyss + size - 1;
		yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
		yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
		if (yydebug)
			fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

		if (yyssp >= yyss + yystacksize - 1)
			YYABORT;
	}

#if YYDEBUG != 0
	if (yydebug)
		fprintf(stderr, "Entering state %d\n", yystate);
#endif

	goto yybackup;
yybackup:

	/* Do appropriate processing given the current state.  */
	/* Read a lookahead token if we need one and don't already have one.  */
	/* yyresume: */

	/* First try to decide what to do without reference to lookahead token.  */

	yyn = yypact[yystate];
	if (yyn == YYFLAG)
		goto yydefault;

	/* Not known => get a lookahead token if don't already have one.  */

	/* yychar is either YYEMPTY or YYEOF
	or a valid token in external form.  */

	if (yychar == YYEMPTY)
	{
#if YYDEBUG != 0
		if (yydebug)
			fprintf(stderr, "Reading a token: ");
#endif
		yychar = YYLEX;
	}

	/* Convert token to internal form (in yychar1) for indexing tables with */

	if (yychar <= 0)		/* This means end of input. */
	{
		yychar1 = 0;
		yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
		if (yydebug)
			fprintf(stderr, "Now at end of input.\n");
#endif
	}
	else
	{
		yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
		if (yydebug)
		{
			fprintf(stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
			/* Give the individual parser a way to print the precise meaning
			of a token, for further debugging info.  */
#ifdef YYPRINT
			YYPRINT(stderr, yychar, yylval);
#endif
			fprintf(stderr, ")\n");
		}
#endif
	}

	yyn += yychar1;
	if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
		goto yydefault;

	yyn = yytable[yyn];

	/* yyn is what to do for this token type in this state.
	Negative => reduce, -yyn is rule number.
	Positive => shift, yyn is new state.
	New state is final state => don't bother to shift,
	just return success.
	0, or most negative number => error.  */

	if (yyn < 0)
	{
		if (yyn == YYFLAG)
			goto yyerrlab;
		yyn = -yyn;
		goto yyreduce;
	}
	else if (yyn == 0)
		goto yyerrlab;

	if (yyn == YYFINAL)
		YYACCEPT;

	/* Shift the lookahead token.  */

#if YYDEBUG != 0
	if (yydebug)
		fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

	/* Discard the token being shifted unless it is eof.  */
	if (yychar != YYEOF)
		yychar = YYEMPTY;

	*++yyvsp = yylval;
#ifdef YYLSP_NEEDED
	*++yylsp = yylloc;
#endif

	/* count tokens shifted since error; after three, turn off error status.  */
	if (yyerrstatus) yyerrstatus--;

	yystate = yyn;
	goto yynewstate;

	/* Do the default action for the current state.  */
yydefault:

	yyn = yydefact[yystate];
	if (yyn == 0)
		goto yyerrlab;

	/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
	yylen = yyr2[yyn];
	if (yylen > 0)
		yyval = yyvsp[1 - yylen]; /* implement default value of the action */

#if YYDEBUG != 0
	if (yydebug)
	{
		int i;

		fprintf(stderr, "Reducing via rule %d (line %d), ",
			yyn, yyrline[yyn]);

		/* Print the symbols being reduced, and their result.  */
		for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
			fprintf(stderr, "%s ", yytname[yyrhs[i]]);
		fprintf(stderr, " -> %s\n", yytname[yyr1[yyn]]);
	}
#endif


	switch (yyn) {

	case 1:
#line 46 "nf.y"
	{g_syntaxTree = yyvsp[0].tnode;;
	break; }
	case 2:
#line 49 "nf.y"
	{yyval.tnode = yyvsp[0].tnode;
	break; }
	case 3:
#line 50 "nf.y"
	{yyval.tnode = yyvsp[-1].tnode;;
	break; }
	case 4:
#line 51 "nf.y"
	{yyval.tnode = new CTreeNode(IMPLY_STA, "", 0, yyvsp[-2].tnode, yyvsp[0].tnode);;
	break; }
	case 5:
#line 52 "nf.y"
	{yyval.tnode = new CTreeNode(IFF_STA, "", 0, yyvsp[-2].tnode, yyvsp[0].tnode);;
	break; }
	case 6:
#line 53 "nf.y"
	{yyval.tnode = new CTreeNode(AND_STA, "", 0, yyvsp[-2].tnode, yyvsp[0].tnode);;
	break; }
	case 7:
#line 54 "nf.y"
	{yyval.tnode = new CTreeNode(OR_STA, "", 0, yyvsp[-2].tnode, yyvsp[0].tnode);;
	break; }
	case 8:
#line 55 "nf.y"
	{yyval.tnode = new CTreeNode(CHOP_STA, "", 0, yyvsp[-2].tnode, yyvsp[0].tnode);;
	break; }
	case 9:
#line 56 "nf.y"
	{yyval.tnode = new CTreeNode(UNTIL_STA, "", 0, yyvsp[-2].tnode, yyvsp[0].tnode);;
	break; }
	case 10:
#line 57 "nf.y"
	{yyval.tnode = new CTreeNode(CHOPSTAR_STA, "", 0, yyvsp[-1].tnode);;
	break; }
	case 11:
#line 58 "nf.y"
	{yyval.tnode = new CTreeNode(NEGATION_STA, "", 0, yyvsp[0].tnode);;
	break; }
	case 12:
#line 59 "nf.y"
	{yyval.tnode = new CTreeNode(NEXT_STA, "", 0, yyvsp[0].tnode);;
	break; }
	case 13:
#line 60 "nf.y"
	{yyval.tnode = new CTreeNode(WNEXT_STA, "", 0, yyvsp[0].tnode);;
	break; }
	case 14:
#line 61 "nf.y"
	{yyval.tnode = new CTreeNode(ALWAYS_STA, "", 0, yyvsp[0].tnode);;
	break; }
	case 15:
#line 62 "nf.y"
	{yyval.tnode = new CTreeNode(STIME_STA, "", 0, yyvsp[0].tnode);;
	break; }
	case 16:
#line 63 "nf.y"
	{yyval.tnode = new CTreeNode(TRUE_EXP, "TRUE", 0);;
	break; }
	case 17:
#line 64 "nf.y"
	{yyval.tnode = new CTreeNode(FIN_EXP, "FIN", 0, yyvsp[0].tnode);;
	break; }
	case 18:
#line 65 "nf.y"
	{yyval.tnode = new CTreeNode(FALSE_EXP, "FALSE", 0);;
	break; }
	case 19:
#line 66 "nf.y"
	{yyval.tnode = new CTreeNode(EMPTY_EXP, "EMPTY", 0);;
	break; }
	case 20:
#line 67 "nf.y"
	{yyval.tnode = new CTreeNode(SKIP_EXP, "SKIP", 0);;
	break; }
	case 21:
#line 68 "nf.y"
	{yyval.tnode = new CTreeNode(MORE_EXP, "MORE", 0);;
	break; }
	case 22:
#line 69 "nf.y"
	{yyval.tnode = new CTreeNode(LEN_STA, "", 0, yyvsp[0].tnode);;
	break; }
	case 23:
#line 71 "nf.y"
	{yyval.tnode = new CTreeNode(PROJECTION_STA, "", 0, yyvsp[-4].tnode, yyvsp[-3].tnode, yyvsp[0].tnode);;
	break; }
	case 24:
#line 73 "nf.y"
	{yyval.tnode = new CTreeNode(PROJECTION_STA, "", 0, yyvsp[-3].tnode, NULL, yyvsp[0].tnode);;
	break; }
	case 25:
#line 77 "nf.y"
	{
		yyval.tnode = new CTreeNode(PROJECTION_STA, "", 0, yyvsp[-1].tnode, yyvsp[0].tnode);
		;
		break; }
	case 26:
#line 80 "nf.y"
	{yyval.tnode = NULL;;
	break; }
	case 27:
#line 83 "nf.y"
	{yyval.tnode = new CTreeNode(INTEGER_EXP, yyvsp[0].cString, 0);;
	break; }
	case 28:
#line 84 "nf.y"
	{yyval.tnode = yyvsp[-1].tnode;;
	break; }
	case 29:
#line 87 "nf.y"
	{yyval.tnode = new CTreeNode(IDENT_EXP, yyvsp[0].cString, 0);;
	break; }
	}
	/* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

	yyvsp -= yylen;
	yyssp -= yylen;
#ifdef YYLSP_NEEDED
	yylsp -= yylen;
#endif

#if YYDEBUG != 0
	if (yydebug)
	{
		short *ssp1 = yyss - 1;
		fprintf(stderr, "state stack now");
		while (ssp1 != yyssp)
			fprintf(stderr, " %d", *++ssp1);
		fprintf(stderr, "\n");
	}
#endif

	*++yyvsp = yyval;

#ifdef YYLSP_NEEDED
	yylsp++;
	if (yylen == 0)
	{
		yylsp->first_line = yylloc.first_line;
		yylsp->first_column = yylloc.first_column;
		yylsp->last_line = (yylsp - 1)->last_line;
		yylsp->last_column = (yylsp - 1)->last_column;
		yylsp->text = 0;
	}
	else
	{
		yylsp->last_line = (yylsp + yylen - 1)->last_line;
		yylsp->last_column = (yylsp + yylen - 1)->last_column;
	}
#endif

	/* Now "shift" the result of the reduction.
	Determine what state that goes to,
	based on the state we popped back to
	and the rule number reduced by.  */

	yyn = yyr1[yyn];

	yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
	if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
		yystate = yytable[yystate];
	else
		yystate = yydefgoto[yyn - YYNTBASE];

	goto yynewstate;

yyerrlab:   /* here on detecting error */

	if (!yyerrstatus)
		/* If not already recovering from an error, report this error.  */
	{
		++yynerrs;

#ifdef YYERROR_VERBOSE
		yyn = yypact[yystate];

		if (yyn > YYFLAG && yyn < YYLAST)
		{
			int size = 0;
			char *msg;
			int x, count;

			count = 0;
			/* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
			for (x = (yyn < 0 ? -yyn : 0);
				x < (sizeof(yytname) / sizeof(char *)); x++)
				if (yycheck[x + yyn] == x)
					size += strlen(yytname[x]) + 15, count++;
			msg = (char *)malloc(size + 15);
			if (msg != 0)
			{
				strcpy(msg, "parse error");

				if (count < 5)
				{
					count = 0;
					for (x = (yyn < 0 ? -yyn : 0);
						x < (sizeof(yytname) / sizeof(char *)); x++)
						if (yycheck[x + yyn] == x)
						{
							strcat(msg, count == 0 ? ", expecting `" : " or `");
							strcat(msg, yytname[x]);
							strcat(msg, "'");
							count++;
						}
				}
				yyerror(msg);
				free(msg);
			}
			else
				yyerror("parse error; also virtual memory exceeded");
		}
		else
#endif /* YYERROR_VERBOSE */
			yyerror("parse error");
	}

	goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

	if (yyerrstatus == 3)
	{
		/* if just tried and failed to reuse lookahead token after an error, discard it.  */

		/* return failure if at end of input */
		if (yychar == YYEOF)
			YYABORT;

#if YYDEBUG != 0
		if (yydebug)
			fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

		yychar = YYEMPTY;
	}

	/* Else will try to reuse lookahead token
	after shifting the error token.  */

	yyerrstatus = 3;		/* Each real token shifted decrements this */

	goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
	/* This is wrong; only states that explicitly want error tokens
	should shift them.  */
	yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
	if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

	if (yyssp == yyss) YYABORT;
	yyvsp--;
	yystate = *--yyssp;
#ifdef YYLSP_NEEDED
	yylsp--;
#endif

#if YYDEBUG != 0
	if (yydebug)
	{
		short *ssp1 = yyss - 1;
		fprintf(stderr, "Error: state stack now");
		while (ssp1 != yyssp)
			fprintf(stderr, " %d", *++ssp1);
		fprintf(stderr, "\n");
	}
#endif

yyerrhandle:

	yyn = yypact[yystate];
	if (yyn == YYFLAG)
		goto yyerrdefault;

	yyn += YYTERROR;
	if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
		goto yyerrdefault;

	yyn = yytable[yyn];
	if (yyn < 0)
	{
		if (yyn == YYFLAG)
			goto yyerrpop;
		yyn = -yyn;
		goto yyreduce;
	}
	else if (yyn == 0)
		goto yyerrpop;

	if (yyn == YYFINAL)
		YYACCEPT;

#if YYDEBUG != 0
	if (yydebug)
		fprintf(stderr, "Shifting error token, ");
#endif

	*++yyvsp = yylval;
#ifdef YYLSP_NEEDED
	*++yylsp = yylloc;
#endif

	yystate = yyn;
	goto yynewstate;
}
#line 91 "nf.y"
