/*
** 2015-04-17
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
**
** This is a utility program designed to aid running the SQLite library
** against an external fuzzer, such as American Fuzzy Lop (AFL)
** (http://lcamtuf.coredump.cx/afl/).  Basically, this program reads
** SQL text from standard input and passes it through to SQLite for evaluation,
** just like the "sqlite3" command-line shell.  Differences from the
** command-line shell:
**
**    (1)  The complex "dot-command" extensions are omitted.  This
**         prevents the fuzzer from discovering that it can run things
**         like ".shell rm -rf ~"
**
**    (2)  The database is opened with the SQLITE_OPEN_MEMORY flag so that
**         no disk I/O from the database is permitted.  The ATTACH command
**         with a filename still uses an in-memory database.
**
**    (3)  The main in-memory database can be initialized from a template
**         disk database so that the fuzzer starts with a database containing
**         content.
**
**    (4)  The eval() SQL function is added, allowing the fuzzer to do
**         interesting recursive operations.
**
**    (5)  An error is raised if there is a memory leak.
**
** The input text can be divided into separate test cases using comments
** of the form:
**
**       |****<...>****|
**
** where the "..." is arbitrary text. (Except the "|" should really be "/".
** "|" is used here to avoid compiler errors about nested comments.)
** A separate in-memory SQLite database is created to run each test case.
** This feature allows the "queue" of AFL to be captured into a single big
** file using a command like this:
**
**    (for i in id:*; do echo '|****<'$i'>****|'; cat $i; done) >~/all-queue.txt
**
** (Once again, change the "|" to "/") Then all elements of the AFL queue
** can be run in a single go (for regression testing, for example) by typing:
**
**    fuzzershell -f ~/all-queue.txt
**
** After running each chunk of SQL, the database connection is closed.  The
** program aborts if the close fails or if there is any unfreed memory after
** the close.
**
** New test cases can be appended to all-queue.txt at any time.  If redundant
** test cases are added, they can be eliminated by running:
**
**    fuzzershell -f ~/all-queue.txt --unique-cases ~/unique-cases.txt
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "sqlite3.h"
#define ISDIGIT(X) isdigit((unsigned char)(X))

/*
** All global variables are gathered into the "g" singleton.
*/
struct GlobalVars {
	const char *zArgv0;              /* Name of program */
	int iOomCntdown;                 /* Memory fails on 1 to 0 transition */
	int nOomFault;                   /* Increments for each OOM fault */
	int bOomOnce;                    /* Fail just once if true */
	int bOomEnable;                  /* True to enable OOM simulation */
	int nOomBrkpt;                   /* Number of calls to oomFault() */
	char zTestName[100];             /* Name of current test */
} g;

/*
** Maximum number of iterations for an OOM test
*/
#ifndef OOM_MAX
# define OOM_MAX 625
#endif

/*
** This routine is called when a simulated OOM occurs.  It exists as a
** convenient place to set a debugger breakpoint.
*/
static void oomFault(void){
	g.nOomBrkpt++; /* Prevent oomFault() from being optimized out */
}

/*
** This callback is invoked by sqlite3_log().
*/
static void shellLog(void *pNotUsed, int iErrCode, const char *zMsg){
	printf("LOG: (%d) %s\n", iErrCode, zMsg);
	fflush(stdout);
}
static void shellLogNoop(void *pNotUsed, int iErrCode, const char *zMsg){
	return;
}

/*
** This callback is invoked by sqlite3_exec() to return query results.
*/
static int execCallback(void *NotUsed, int argc, char **argv, char **colv){
	int i;
	static unsigned cnt = 0;
	printf("ROW #%u:\n", ++cnt);
	if (argv){
		for (i = 0; i<argc; i++){
			printf(" %s=", colv[i]);
			if (argv[i]){
				printf("[%s]\n", argv[i]);
			}
			else{
				printf("NULL\n");
			}
		}
	}
	fflush(stdout);
	return 0;
}
static int execNoop(void *NotUsed, int argc, char **argv, char **colv){
	return 0;
}

#ifndef SQLITE_OMIT_TRACE
/*
** This callback is invoked by sqlite3_trace() as each SQL statement
** starts.
*/
static void traceCallback(void *NotUsed, const char *zMsg){
	printf("TRACE: %s\n", zMsg);
	fflush(stdout);
}
static void traceNoop(void *NotUsed, const char *zMsg){
	return;
}
#endif

/***************************************************************************
** String accumulator object
*/
typedef struct Str Str;
struct Str {
	char *z;                /* The string.  Memory from malloc() */
	sqlite3_uint64 n;       /* Bytes of input used */
	sqlite3_uint64 nAlloc;  /* Bytes allocated to z[] */
	int oomErr;             /* OOM error has been seen */
};

/* Initialize a Str object */
static void StrInit(Str *p){
	memset(p, 0, sizeof(*p));
}

/* Append text to the end of a Str object */
static void StrAppend(Str *p, const char *z){
	sqlite3_uint64 n = strlen(z);
	if (p->n + n >= p->nAlloc){
		char *zNew;
		sqlite3_uint64 nNew;
		if (p->oomErr) return;
		nNew = p->nAlloc * 2 + 100 + n;
		zNew = sqlite3_realloc(p->z, (int)nNew);
		if (zNew == 0){
			sqlite3_free(p->z);
			memset(p, 0, sizeof(*p));
			p->oomErr = 1;
			return;
		}
		p->z = zNew;
		p->nAlloc = nNew;
	}
	memcpy(p->z + p->n, z, (int)n);
	p->n += n;
	p->z[p->n] = 0;
}

/* Return the current string content */
static char *StrStr(Str *p){
	return p->z;
}

/* Free the string */
static void StrFree(Str *p){
	sqlite3_free(p->z);
	StrInit(p);
}

/***************************************************************************
** eval() implementation copied from ../ext/misc/eval.c
*/
/*
** Structure used to accumulate the output
*/
struct EvalResult {
	char *z;               /* Accumulated output */
	const char *zSep;      /* Separator */
	int szSep;             /* Size of the separator string */
	int nAlloc;  /* Number of bytes allocated for z[] */
	int nUsed;   /* Number of bytes of z[] actually used */
};

/*
** Callback from sqlite_exec() for the eval() function.
*/
static int callback(void *pCtx, int argc, char **argv, char **colnames){
	struct EvalResult *p = (struct EvalResult*)pCtx;
	int i;
	for (i = 0; i<argc; i++){
		const char *z = argv[i] ? argv[i] : "";
		int sz = strlen(z);
		if ((int)sz + p->nUsed + p->szSep + 1 > p->nAlloc){
			char *zNew;
			p->nAlloc = p->nAlloc * 2 + sz + p->szSep + 1;
			/* Using sqlite3_realloc64() would be better, but it is a recent
			** addition and will cause a segfault if loaded by an older version
			** of SQLite.  */
			zNew = p->nAlloc <= 0x7fffffff ? sqlite3_realloc(p->z, (int)p->nAlloc) : 0;
			if (zNew == 0){
				sqlite3_free(p->z);
				memset(p, 0, sizeof(*p));
				return 1;
			}
			p->z = zNew;
		}
		if (p->nUsed>0){
			memcpy(&p->z[p->nUsed], p->zSep, p->szSep);
			p->nUsed += p->szSep;
		}
		memcpy(&p->z[p->nUsed], z, sz);
		p->nUsed += sz;
	}
	return 0;
}


/* True to cause run-time checking of the start=, stop=, and/or step=
** parameters.  The only reason to do this is for testing the
** constraint checking logic for virtual tables in the SQLite core.
*/
#ifndef SQLITE_SERIES_CONSTRAINT_VERIFY
# define SQLITE_SERIES_CONSTRAINT_VERIFY 0
#endif

/*
** Print sketchy documentation for this utility program
*/
static void showHelp(void){
	printf("Usage: %s [options] ?FILE...?\n", g.zArgv0);
	printf(
		"Read SQL text from FILE... (or from standard input if FILE... is omitted)\n"
		"and then evaluate each block of SQL contained therein.\n"
		"Options:\n"
		"  --autovacuum          Enable AUTOVACUUM mode\n"
		"  --database FILE       Use database FILE instead of an in-memory database\n"
		"  --disable-lookaside   Turn off lookaside memory\n"
		"  --heap SZ MIN         Memory allocator uses SZ bytes & min allocation MIN\n"
		"  --help                Show this help text\n"
		"  --lookaside N SZ      Configure lookaside for N slots of SZ bytes each\n"
		"  --oom                 Run each test multiple times in a simulated OOM loop\n"
		"  --pagesize N          Set the page size to N\n"
		"  --pcache N SZ         Configure N pages of pagecache each of size SZ bytes\n"
		"  -q                    Reduced output\n"
		"  --quiet               Reduced output\n"
		"  --scratch N SZ        Configure scratch memory for N slots of SZ bytes each\n"
		"  --unique-cases FILE   Write all unique test cases to FILE\n"
		"  --utf16be             Set text encoding to UTF-16BE\n"
		"  --utf16le             Set text encoding to UTF-16LE\n"
		"  -v                    Increased output\n"
		"  --verbose             Increased output\n"
		);
}

/*
** Return the value of a hexadecimal digit.  Return -1 if the input
** is not a hex digit.
*/
static int hexDigitValue(char c){
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	return -1;
}

/* Return the current wall-clock time */
static sqlite3_int64 timeOfDay(void){
	static sqlite3_vfs *clockVfs = 0;
	sqlite3_int64 t;
	if (clockVfs == 0) clockVfs = sqlite3_vfs_find(0);
	if (clockVfs->iVersion >= 1 && clockVfs->xCurrentTimeInt64 != 0){
		clockVfs->xCurrentTimeInt64(clockVfs, &t);
	}
	else{
		double r;
		clockVfs->xCurrentTime(clockVfs, &r);
		t = (sqlite3_int64)(r*86400000.0);
	}
	return t;
}

int main(int argc, char **argv){
	char *zIn = 0;                /* Input text */
	int nAlloc = 0;               /* Number of bytes allocated for zIn[] */
	int nIn = 0;                  /* Number of bytes of zIn[] used */
	size_t got;                   /* Bytes read from input */
	int rc = SQLITE_OK;           /* Result codes from API functions */
	int i;                        /* Loop counter */
	int iNext;                    /* Next block of SQL */
	sqlite3 *db;                  /* Open database */
	char *zErrMsg = 0;            /* Error message returned from sqlite3_exec() */
	const char *zEncoding = 0;    /* --utf16be or --utf16le */
	int nHeap = 0, mnHeap = 0;    /* Heap size from --heap */
	int nLook = 0, szLook = 0;    /* --lookaside configuration */
	int nPCache = 0, szPCache = 0;/* --pcache configuration */
	int nScratch = 0, szScratch = 0;/* --scratch configuration */
	int pageSize = 0;             /* Desired page size.  0 means default */
	void *pHeap = 0;              /* Allocated heap space */
	void *pLook = 0;              /* Allocated lookaside space */
	void *pPCache = 0;            /* Allocated storage for pcache */
	void *pScratch = 0;           /* Allocated storage for scratch */
	int doAutovac = 0;            /* True for --autovacuum */
	char *zSql;                   /* SQL to run */
	char *zToFree = 0;            /* Call sqlite3_free() on this afte running zSql */
	int verboseFlag = 0;          /* --verbose or -v flag */
	int quietFlag = 0;            /* --quiet or -q flag */
	int nTest = 0;                /* Number of test cases run */
	int multiTest = 0;            /* True if there will be multiple test cases */
	int lastPct = -1;             /* Previous percentage done output */
	sqlite3 *dataDb = 0;          /* Database holding compacted input data */
	sqlite3_stmt *pStmt = 0;      /* Statement to insert testcase into dataDb */
	const char *zDataOut = 0;     /* Write compacted data to this output file */
	int nHeader = 0;              /* Bytes of header comment text on input file */
	int oomFlag = 0;              /* --oom */
	int oomCnt = 0;               /* Counter for the OOM loop */
	char zErrBuf[200];            /* Space for the error message */
	const char *zFailCode;        /* Value of the TEST_FAILURE environment var */
	const char *zPrompt;          /* Initial prompt when large-file fuzzing */
	int nInFile = 0;              /* Number of input files to read */
	char azInFile[10][10];          /* Array of input file names */
	int jj;                       /* Loop counter for azInFile[] */
	int iBegin;         /* Start time for the whole program */
	int iStart, iEnd;   /* Start and end-times for a test case */
	const char *zDbName = 0;      /* Name of an on-disk database file to open */

	iBegin = timeOfDay();
	sqlite3_shutdown();
	zFailCode = getenv("TEST_FAILURE");
	g.zArgv0 = argv[0];
	zPrompt = "<stdin>";

	zDataOut = "fuzzershell_b.txt";
	nInFile++;
	//azInFile = realloc(azInFile, sizeof(azInFile[0])*nInFile);
	//azInFile[nInFile - 1] = "a.txt";
	strcpy(azInFile[nInFile - 1], "fuzzershell_a.txt");

	/* Do global SQLite initialization */
	//sqlite3_config(SQLITE_CONFIG_LOG, verboseFlag ? shellLog : shellLogNoop, 0);

	/* If the --unique-cases option was supplied, open the database that will
	** be used to gather unique test cases.
	*/
	if (zDataOut){
		rc = sqlite3_open(":memory:", &dataDb);
		rc = sqlite3_exec(dataDb,
			"CREATE TABLE testcase(sql BLOB PRIMARY KEY, tm) WITHOUT ROWID;", 0, 0, 0);
		rc = sqlite3_prepare_v2(dataDb,
			"INSERT OR IGNORE INTO testcase(sql,tm)VALUES(?1,?2)",
			-1, &pStmt, 0);
	}

	/* Initialize the input buffer used to hold SQL text */
	if (nInFile == 0) nInFile = 1;
	nAlloc = 1000;
	zIn = malloc(nAlloc);

	/* Loop over all input files */
	for (jj = 0; jj<nInFile; jj++){

		/* Read the complete content of the next input file into zIn[] */
		FILE *in;
		if (azInFile){
			int j, k;
			in = fopen(azInFile[jj], "rb");
			zPrompt = azInFile[jj];
			for (j = k = 0; zPrompt[j]; j++) if (zPrompt[j] == '/') k = j + 1;
			zPrompt += k;
		}
		else{
			in = stdin;
			zPrompt = "<stdin>";
		}
		while (!feof(in)){
			got = fread(zIn + nIn, 1, nAlloc - nIn - 1, in);
			nIn += (int)got;
			zIn[nIn] = 0;
			if (got == 0) break;
			if (nAlloc - nIn - 1 < 100){
				nAlloc += nAlloc + 1000;
				zIn = realloc(zIn, nAlloc);
			}
		}
		if (in != stdin) fclose(in);
		lastPct = -1;

		/* Skip initial lines of the input file that begin with "#" */
		for (i = 0; i<nIn; i = iNext + 1){
			if (zIn[i] != '#') break;
			for (iNext = i + 1; iNext<nIn && zIn[iNext] != '\n'; iNext++){}
		}
		nHeader = i;

		/* Process all test cases contained within the input file.
		*/
		for (; i<nIn; i = iNext, nTest++){
			char cSaved;
			for (iNext = i; iNext<nIn && strncmp(&zIn[iNext], "****<", 6) != 0; iNext++){}
			cSaved = zIn[iNext];
			zIn[iNext] = 0;


			/* Print out the SQL of the next test case is --verbose is enabled
			*/
			zSql = &zIn[i];
			if (verboseFlag){
				printf("INPUT (offset: %d, size: %d): [%s]\n",
					i, (int)strlen(&zIn[i]), &zIn[i]);
			}
			else if (multiTest && !quietFlag){
				if (oomFlag){
					printf("%s\n", g.zTestName);
				}
				else{
					int pct = (10 * iNext) / nIn;
					if (pct != lastPct){
						if (lastPct<0) printf("%s:", zPrompt);
						printf(" %d%%", pct * 10);
						lastPct = pct;
					}
				}
			}
			else if (nInFile>1){
				printf("%s\n", zPrompt);
			}
			fflush(stdout);

			/* Run the next test case.  Run it multiple times in --oom mode
			*/

			oomCnt = 0;
			do{
				Str sql;
				//StrInit(&sql);
				if (zDbName){
					rc = sqlite3_open_v2(zDbName, &db, SQLITE_OPEN_READWRITE, 0);
				}
				else{
					rc = sqlite3_open_v2(
						"main.db", &db,
						SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_MEMORY,
						0);
				}

				sqlite3_limit(db, SQLITE_LIMIT_LENGTH, 1000000);
				iStart = timeOfDay();

				/* If using an input database file and that database contains a table
				** named "autoexec" with a column "sql", then replace the input SQL
				** with the concatenated text of the autoexec table.  In this way,
				** if the database file is the input being fuzzed, the SQL text is
				** fuzzed at the same time. */
				if (sqlite3_table_column_metadata(db, 0, "autoexec", "sql", 0, 0, 0, 0, 0) == 0){
					sqlite3_stmt *pStmt2;
					rc = sqlite3_prepare_v2(db, "SELECT sql FROM autoexec", -1, &pStmt2, 0);
					if (rc == SQLITE_OK){
						while (sqlite3_step(pStmt2) == SQLITE_ROW){
							StrAppend(&sql, (const char*)sqlite3_column_text(pStmt2, 0));
							StrAppend(&sql, "\n");
						}
					}
					sqlite3_finalize(pStmt2);
					zSql = StrStr(&sql);
				}

				g.bOomEnable = 1;
				if (verboseFlag){
					zErrMsg = 0;
					rc = sqlite3_exec(db, zSql, execCallback, 0, &zErrMsg);
					if (zErrMsg){
						sqlite3_snprintf(sizeof(zErrBuf), zErrBuf, "%z", zErrMsg);
						zErrMsg = 0;
					}
				}
				else {
					rc = sqlite3_exec(db, zSql, execNoop, 0, 0);
				}
				g.bOomEnable = 0;
				iEnd = timeOfDay();
				//StrFree(&sql);
				rc = sqlite3_close(db);
			} while (oomCnt>0);

			/* Store unique test cases in the in the dataDb database if the
			** --unique-cases flag is present
			*/
			if (zDataOut){
				sqlite3_bind_blob(pStmt, 1, &zIn[i], iNext - i, NULL);
				sqlite3_bind_int64(pStmt, 2, iEnd - iStart);
				rc = sqlite3_step(pStmt);
				sqlite3_reset(pStmt);
			}

			/* Free the SQL from the current test case
			*/
			if (zToFree){
				sqlite3_free(zToFree);
				zToFree = 0;
			}
			zIn[iNext] = cSaved;

			/* Show test-case results in --verbose mode
			*/
			if (verboseFlag){
				printf("RESULT-CODE: %d\n", rc);
				if (zErrMsg){
					printf("ERROR-MSG: [%s]\n", zErrBuf);
				}
				fflush(stdout);
			}

			/* Simulate an error if the TEST_FAILURE environment variable is "5".
			** This is used to verify that automated test script really do spot
			** errors that occur in this test program.
			*/
			if (zFailCode){
				if (zFailCode[0] == '5' && zFailCode[1] == 0){
					//abendError("simulated failure");
				}
				else if (zFailCode[0] != 0){
					/* If TEST_FAILURE is something other than 5, just exit the test
					** early */
					printf("\nExit early due to TEST_FAILURE being set");
					break;
				}
			}
		}
		if (!verboseFlag && multiTest && !quietFlag && !oomFlag) printf("\n");
	}

	/* Report total number of tests run
	*/
	if (nTest>1 && !quietFlag){
		int iElapse = timeOfDay() - iBegin;
		printf("%s: 0 errors out of %d tests in %d.%03d seconds\nSQLite %s %s\n",
			g.zArgv0, nTest, (int)(iElapse / 1000), (int)(iElapse % 1000),
			sqlite3_libversion(), sqlite3_sourceid());
	}

	/* Write the unique test cases if the --unique-cases flag was used
	*/
	if (zDataOut){
		int n = 0;
		FILE *out = fopen(zDataOut, "wb");
		if (nHeader>0) fwrite(zIn, nHeader, 1, out);
		sqlite3_finalize(pStmt);
		rc = sqlite3_prepare_v2(dataDb, "SELECT sql, tm FROM testcase ORDER BY tm, sql",
			-1, &pStmt, 0);
		while (sqlite3_step(pStmt) == SQLITE_ROW){
			fprintf(out, "/****<%d:%dms>****/", ++n, sqlite3_column_int(pStmt, 1));
			fwrite(sqlite3_column_blob(pStmt, 0), sqlite3_column_bytes(pStmt, 0), 1, out);
		}
		fclose(out);
		sqlite3_finalize(pStmt);
		sqlite3_close(dataDb);
	}

	/* Clean up and exit.
	*/
	//free(azInFile);
	free(zIn);
	free(pHeap);
	free(pLook);
	free(pScratch);
	free(pPCache);
	return 0;
}
