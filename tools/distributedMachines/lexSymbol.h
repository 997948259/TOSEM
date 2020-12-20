#ifndef _LEXSYMBOL_H_
#define _LEXSYMBOL_H_
typedef union{
	char      *cString;   /* A character string */
	int       nInteger;   /* An integer value */
	CTreeNode *tnode;    /* Node in the syntax tree */
} YYSTYPE;
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


extern YYSTYPE yylval;
#endif
