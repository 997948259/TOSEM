/*
** This C program extracts all "words" from an input document and adds them
** to an SQLite database.  A "word" is any contiguous sequence of alphabetic
** characters.  All digits, punctuation, and whitespace characters are 
** word separators.  The database stores a single entry for each distinct
** word together with a count of the number of occurrences of that word.
** A fresh database is created automatically on each run.
**
**     wordcount DATABASE INPUTFILE
**
** The INPUTFILE name can be omitted, in which case input it taken from
** standard input.
**
** Option:
**
**
** Modes:
**
** Insert mode means:
**    (1) INSERT OR IGNORE INTO wordcount VALUES($new,1)
**    (2) UPDATE wordcount SET cnt=cnt+1 WHERE word=$new -- if (1) is a noop
**
** Update mode means:
**    (1) INSERT OR IGNORE INTO wordcount VALUES($new,0)
**    (2) UPDATE wordcount SET cnt=cnt+1 WHERE word=$new
**
** Replace mode means:
**    (1) REPLACE INTO wordcount
**        VALUES($new,ifnull((SELECT cnt FROM wordcount WHERE word=$new),0)+1);
**
** Select mode means:
**    (1) SELECT 1 FROM wordcount WHERE word=$new
**    (2) INSERT INTO wordcount VALUES($new,1) -- if (1) returns nothing
**    (3) UPDATE wordcount SET cnt=cnt+1 WHERE word=$new  --if (1) return TRUE
**
** Delete mode means:
**    (1) DELETE FROM wordcount WHERE word=$new
**
** Query mode means:
**    (1) SELECT cnt FROM wordcount WHERE word=$new
**
** Note that delete mode and query mode are only useful for preexisting
** databases.  The wordcount table is created using IF NOT EXISTS so this
** utility can be run multiple times on the same database file.  The
** --without-rowid, --nocase, and --pagesize parameters are only effective
** when creating a new database and are harmless no-ops on preexisting
** databases.
**
******************************************************************************
**
** Compile as follows:
**
**    gcc -I. wordcount.c sqlite3.c -ldl -lpthreads
**
** Or:
**
**    gcc -I. -DSQLITE_THREADSAFE=0 -DSQLITE_OMIT_LOAD_EXTENSION \
**        wordcount.c sqlite3.c
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include "sqlite3.h"
# include <io.h>

const char zHelp[] = 
"Usage: wordcount [OPTIONS] DATABASE [INPUT]\n"
" --all                Repeat the test for all test modes\n"
" --cachesize NNN      Use a cache size of NNN\n"
" --commit NNN         Commit after every NNN operations\n"
" --delete             Use DELETE mode\n"
" --insert             Use INSERT mode (the default)\n"
" --journal MMMM       Use PRAGMA journal_mode=MMMM\n"
" --nocase             Add the NOCASE collating sequence to the words.\n"
" --nosync             Use PRAGMA synchronous=OFF\n"
" --pagesize NNN       Use a page size of NNN\n"
" --query              Use QUERY mode\n"
" --replace            Use REPLACE mode\n"
" --select             Use SELECT mode\n"
" --stats              Show sqlite3_status() results at the end.\n"
" --summary            Show summary information on the collected data.\n"
" --tag NAME           Tag all output using NAME.  Use only stdout.\n"
" --timer              Time the operation of this program\n"
" --trace              Enable sqlite3_trace() output.\n"
" --update             Use UPDATE mode\n"
" --without-rowid      Use a WITHOUT ROWID table to store the words.\n"
;

/* Output tag */
char *zTag = "--";


/* Print an error message and exit */
static void fatal_error(const char *zMsg, ...){
  va_list ap;
  va_start(ap, zMsg);
  vfprintf(stderr, zMsg, ap);
  va_end(ap);
  exit(1);
}

/* Print a usage message and quit */
static void usage(void){
  printf("%s",zHelp);
  exit(0);
}

/* The sqlite3_trace() callback function */
static void traceCallback(void *NotUsed, const char *zSql){
  printf("%s;\n", zSql);
}

/* An sqlite3_exec() callback that prints results on standard output,
** each column separated by a single space. */
static int printResult(void *NotUsed, int nArg, char **azArg, char **azNm){
  int i;
  printf("%s", zTag);
  for(i=0; i<nArg; i++){
    printf(" %s", azArg[i] ? azArg[i] : "(null)");
  }
  printf("\n");
  return 0;
}


/*
** Add one character to a hash
*/
static void addCharToHash(unsigned int *a, unsigned char x){
  if( a[0]<4 ){
    a[1] = (a[1]<<8) | x;
    a[0]++;
  }else{
    a[2] = (a[2]<<8) | x;
    a[0]++;
    if( a[0]==8 ){
      a[3] += a[1] + a[4];
      a[4] += a[2] + a[3];
      a[0] = a[1] = a[2] = 0;
    }
  }    
}

/*
** Compute the final hash value.
*/
static void finalHash(unsigned int *a, char *z){
  a[3] += a[1] + a[4] + a[0];
  a[4] += a[2] + a[3];
  sqlite3_snprintf(17, z, "%08x%08x", a[3], a[4]);
}

/* Mode names */
static const char *azMode[] = {
  "--insert",
  "--replace",
  "--select",
  "--update",
  "--delete",
  "--query"
};

/*
** Determine if another iteration of the test is required.  Return true
** if so.  Return zero if all iterations have finished.
*/
static int allLoop(
  int iMode,                /* The selected test mode */
  int *piLoopCnt,           /* Iteration loop counter */
  int *piMode2,             /* The test mode to use on the next iteration */
  int *pUseWithoutRowid     /* Whether or not to use --without-rowid */
){
  int i;
  if( iMode!=-1 ){
    if( *piLoopCnt ) return 0;
    *piMode2 = iMode;
    *piLoopCnt = 1;
    return 1;
  }
  if( (*piLoopCnt)>=6*2 ) return 0;
  i = (*piLoopCnt)++;
  *pUseWithoutRowid = i&1;
  *piMode2 = i>>1;
  return 1;
}

sqlite3 *db;                  /* The SQLite database connection */
sqlite3_stmt *stmt = 0;    /* The INSERT statement */
sqlite3_stmt *pstmt = 0;    /* The UPDATE statement */
sqlite3_stmt *pStmt1 = 0;    /* The SELECT statement */
sqlite3_stmt *pStmt2 = 0;    /* The DELETE statement */
int main(){
	int argc = 4;
	//char*argv[] = {"wordcount.exe","--insert","testdb.db","wordcount.txt"};
	char **argv = (char **)malloc(4 * sizeof(char *));
	int tmp = 0;
	while (tmp<4)
	{
		argv[tmp] = (char *)malloc(20);
		tmp = tmp + 1;
	}
	strcpy(argv[0], "wordcount.exe");
	strcpy(argv[1], "--insert");
	strcpy(argv[2], "testdb.db");
	strcpy(argv[3], "wordcount.txt");

  const char *zFileToRead = 0;  /* Input file.  NULL for stdin */
  const char *zDbName = 0;      /* Name of the database file to create */
  int useWithoutRowid = 0;      /* True for --without-rowid */
  int iMode = 0;      /* One of MODE_xxxxx */
  int iMode2;                   /* Mode to use for current --all iteration */
  int iLoopCnt = 0;             /* Which iteration when running --all */
  int useNocase = 0;            /* True for --nocase */
  int doTrace = 0;              /* True for --trace */
  int showStats = 0;            /* True for --stats */
  int showSummary = 0;          /* True for --summary */
  int showTimer = 0;            /* True for --timer */
  int cacheSize = 0;            /* Desired cache size.  0 means default */
  int pageSize = 0;             /* Desired page size.  0 means default */
  int commitInterval = 0;       /* How often to commit.  0 means never */
  int noSync = 0;               /* True for --nosync */
  const char *zJMode = 0;       /* Journal mode */
  int nOp = 0;                  /* Operation counter */
  int i, j;                     /* Loop counters */
  char *zSql;                   /* Constructed SQL statement */
  FILE *in;                     /* The open input file */
  int rc;                       /* Return code from an SQLite interface */
  int iCur, iHiwtr;             /* Statistics values, current and "highwater" */
  int sumCnt = 0;     /* Sum in QUERY mode */
  int totalTime = 0;  /* Total time */
  char zInput[2000];            /* A single line of input */

  /* Process command-line arguments */
  for(i=1; i<argc; i++){
    const char *z = argv[i];
    if( z[0]=='-' ){
      do{ z++; }while( z[0]=='-' );
      if( strcmp(z,"without-rowid")==0 ){
        useWithoutRowid = 1;
      }else if( strcmp(z,"replace")==0 ){
        iMode = 1;
      }else if( strcmp(z,"select")==0 ){
        iMode = 2;
      }else if( strcmp(z,"insert")==0 ){
        iMode = 0;
      }else if( strcmp(z,"update")==0 ){
        iMode = 3;
      }else if( strcmp(z,"delete")==0 ){
        iMode = 4;
      }else if( strcmp(z,"query")==0 ){
        iMode = 5;
      }else if( strcmp(z,"all")==0 ){
        iMode = -1;
        showTimer = -99;
      }else if( strcmp(z,"nocase")==0 ){
        useNocase = 1;
      }else if( strcmp(z,"trace")==0 ){
        doTrace = 1;
      }else if( strcmp(z,"nosync")==0 ){
        noSync = 1;
      }else if( strcmp(z,"stats")==0 ){
        showStats = 1;
      }else if( strcmp(z,"summary")==0 ){
        showSummary = 1;
      }else if( strcmp(z,"timer")==0 ){
        showTimer = i;
      }else if( strcmp(z,"cachesize")==0 && i<argc-1 ){
        i++;
        cacheSize = atoi(argv[i]);
      }else if( strcmp(z,"pagesize")==0 && i<argc-1 ){
        i++;
        pageSize = atoi(argv[i]);
      }else if( strcmp(z,"commit")==0 && i<argc-1 ){
        i++;
        commitInterval = atoi(argv[i]);
      }else if( strcmp(z,"journal")==0 && i<argc-1 ){
        zJMode = argv[++i];
      }else if( strcmp(z,"tag")==0 && i<argc-1 ){
        zTag = argv[++i];
      }else if( strcmp(z, "help")==0 || strcmp(z,"?")==0 ){
        usage();
      }else{
        fatal_error("unknown option: \"%s\"\n"
                    "Use --help for a list of options\n",
                    argv[i]);
      }
    }else if( zDbName==0 ){
      zDbName = argv[i];
    }else if( zFileToRead==0 ){
      zFileToRead = argv[i];
    }else{
      fatal_error("surplus argument: \"%s\"\n", argv[i]);
    }
  }
  if( zDbName==0 ){
    usage();
  }


  /* Open the database and the input file */
  if( zDbName[0] && strcmp(zDbName,":memory:")!=0 ){
    _unlink(zDbName);
  }
  if( sqlite3_open(zDbName, &db) ){
    fatal_error("Cannot open database file: %s\n", zDbName);
  }
  if( zFileToRead ){
    in = fopen(zFileToRead, "rb");
    if( in==0 ){
      fatal_error("Could not open input file \"%s\"\n", zFileToRead);
    }
  }else{
    if( iMode==-1 ){
      fatal_error("The --all mode cannot be used with stdin\n");
    }
	in = fopen(zFileToRead, "rb");
  }

  /* Set database connection options */
  if( doTrace ) sqlite3_trace(db, traceCallback, 0);
  if( pageSize ){
    zSql = sqlite3_mprintf("PRAGMA page_size=%d", pageSize);
    sqlite3_exec(db, zSql, 0, 0, 0);
    sqlite3_free(zSql);
  }
  if( cacheSize ){
    zSql = sqlite3_mprintf("PRAGMA cache_size=%d", cacheSize);
    sqlite3_exec(db, zSql, 0, 0, 0);
    sqlite3_free(zSql);
  }
  if( noSync ) sqlite3_exec(db, "PRAGMA synchronous=OFF", 0, 0, 0);
  if( zJMode ){
    zSql = sqlite3_mprintf("PRAGMA journal_mode=%s", zJMode);
    sqlite3_exec(db, zSql, 0, 0, 0);
    sqlite3_free(zSql);
  }

  iLoopCnt = 0;
  while( allLoop(iMode, &iLoopCnt, &iMode2, &useWithoutRowid) ){
    /* Delete prior content in --all mode */
    if( iMode==-1 ){
      if( sqlite3_exec(db, "DROP TABLE IF EXISTS wordcount; VACUUM;",0,0,0) ){
        fatal_error("Could not clean up prior iteration\n");
      }
      
      rewind(in);
    }
 
    /* Construct the "wordcount" table into which to put the words */
    if( sqlite3_exec(db, "BEGIN IMMEDIATE", 0, 0, 0) ){
      fatal_error("Could not start a transaction\n");
    }
    zSql = sqlite3_mprintf(
       "CREATE TABLE IF NOT EXISTS wordcount(\n"
       "  word TEXT PRIMARY KEY COLLATE %s,\n"
       "  cnt INTEGER\n"
       ")%s",
       useNocase ? "nocase" : "binary",
       useWithoutRowid ? " WITHOUT ROWID" : ""
    );
    if( zSql==0 ) fatal_error("out of memory\n");
    rc = sqlite3_exec(db, zSql, 0, 0, 0);
    if( rc ) fatal_error("Could not create the wordcount table: %s.\n",
                         sqlite3_errmsg(db));
    sqlite3_free(zSql);
  
    /* Prepare SQL statements that will be needed */
    if( iMode2==5 ){
      rc = sqlite3_prepare_v2(db,
            "SELECT cnt FROM wordcount WHERE word=?1",
            -1, &pStmt1, 0);
      if( rc ) fatal_error("Could not prepare the SELECT statement: %s\n",
                            sqlite3_errmsg(db));
    }
    if( iMode2==2 ){
      rc = sqlite3_prepare_v2(db,
            "SELECT 1 FROM wordcount WHERE word=?1",
            -1, &pStmt1, 0);
      if( rc ) fatal_error("Could not prepare the SELECT statement: %s\n",
                            sqlite3_errmsg(db));
      rc = sqlite3_prepare_v2(db,
            "INSERT INTO wordcount(word,cnt) VALUES(?1,1)",
            -1, &stmt, 0);
      if( rc ) fatal_error("Could not prepare the INSERT statement: %s\n",
                           sqlite3_errmsg(db));
    }
    if( iMode2==2 || iMode2==3 || iMode2==0 ){
      rc = sqlite3_prepare_v2(db,
            "UPDATE wordcount SET cnt=cnt+1 WHERE word=?1",
            -1, &pstmt, 0);
      if( rc ) fatal_error("Could not prepare the UPDATE statement: %s\n",
                           sqlite3_errmsg(db));
    }
    if( iMode2==0 ){
      rc = sqlite3_prepare_v2(db,
            "INSERT OR IGNORE INTO wordcount(word,cnt) VALUES(?1,1)",
            -1, &stmt, 0);
      if( rc ) fatal_error("Could not prepare the INSERT statement: %s\n",
                           sqlite3_errmsg(db));
    }
    if( iMode2==3 ){
      rc = sqlite3_prepare_v2(db,
            "INSERT OR IGNORE INTO wordcount(word,cnt) VALUES(?1,0)",
            -1, &stmt, 0);
      if( rc ) fatal_error("Could not prepare the INSERT statement: %s\n",
                           sqlite3_errmsg(db));
    }
    if( iMode2==1 ){
      rc = sqlite3_prepare_v2(db,
          "REPLACE INTO wordcount(word,cnt)"
          "VALUES(?1,coalesce((SELECT cnt FROM wordcount WHERE word=?1),0)+1)",
          -1, &stmt, 0);
      if( rc ) fatal_error("Could not prepare the REPLACE statement: %s\n",
                            sqlite3_errmsg(db));
    }
    if( iMode2==4 ){
      rc = sqlite3_prepare_v2(db,
            "DELETE FROM wordcount WHERE word=?1",
            -1, &pStmt2, 0);
      if( rc ) fatal_error("Could not prepare the DELETE statement: %s\n",
                           sqlite3_errmsg(db));
    }
  
    /* Process the input file */
    while( fgets(zInput, sizeof(zInput), in) ){
      for(i=0; zInput[i]; i++){
		  if (!isalpha((unsigned char)(zInput[i]))) continue;
		  for (j = i + 1; isalpha((unsigned char)(zInput[j])); j++){}
  
        /* Found a new word at zInput[i] that is j-i bytes long. 
        ** Process it into the wordcount table.  */
        if( iMode2==4 ){
          sqlite3_bind_text(pStmt2, 1, zInput+i, j-i, SQLITE_STATIC);
          if( sqlite3_step(pStmt2)!=SQLITE_DONE ){
            fatal_error("DELETE failed: %s\n", sqlite3_errmsg(db));
          }
          sqlite3_reset(pStmt2);
        }else if( iMode2==2 ){
          sqlite3_bind_text(pStmt1, 1, zInput+i, j-i, SQLITE_STATIC);
          rc = sqlite3_step(pStmt1);
          sqlite3_reset(pStmt1);
          if( rc==SQLITE_ROW ){
            sqlite3_bind_text(pstmt, 1, zInput+i, j-i, SQLITE_STATIC);
            if( sqlite3_step(pstmt)!=SQLITE_DONE ){
              fatal_error("UPDATE failed: %s\n", sqlite3_errmsg(db));
            }
            sqlite3_reset(pstmt);
          }else if( rc==SQLITE_DONE ){
            sqlite3_bind_text(stmt, 1, zInput+i, j-i, SQLITE_STATIC);
            if( sqlite3_step(stmt)!=SQLITE_DONE ){
              fatal_error("Insert failed: %s\n", sqlite3_errmsg(db));
            }
            sqlite3_reset(stmt);
          }else{
            fatal_error("SELECT failed: %s\n", sqlite3_errmsg(db));
          }
        }else if( iMode2==5 ){
          sqlite3_bind_text(pStmt1, 1, zInput+i, j-i, SQLITE_STATIC);
          if( sqlite3_step(pStmt1)==SQLITE_ROW ){
            sumCnt += sqlite3_column_int64(pStmt1, 0);
          }
          sqlite3_reset(pStmt1);
        }else{
          sqlite3_bind_text(stmt, 1, zInput+i, j-i, SQLITE_STATIC);
          if( sqlite3_step(stmt)!=SQLITE_DONE ){
            fatal_error("INSERT failed: %s\n", sqlite3_errmsg(db));
          }
          sqlite3_reset(stmt);
          if( iMode2==3
           || (iMode2==0 && sqlite3_changes(db)==0)
          ){
            sqlite3_bind_text(pstmt, 1, zInput+i, j-i, SQLITE_STATIC);
            if( sqlite3_step(pstmt)!=SQLITE_DONE ){
              fatal_error("UPDATE failed: %s\n", sqlite3_errmsg(db));
            }
            sqlite3_reset(pstmt);
          }
        }
        i = j-1;
  
        /* Increment the operation counter.  Do a COMMIT if it is time. */
        nOp++;
        if( commitInterval>0 && (nOp%commitInterval)==0 ){
          sqlite3_exec(db, "COMMIT; BEGIN IMMEDIATE", 0, 0, 0);
        }
      }
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);
    sqlite3_finalize(stmt);  stmt = 0;
    sqlite3_finalize(pstmt);  pstmt = 0;
    sqlite3_finalize(pStmt1);  pStmt1 = 0;
    sqlite3_finalize(pStmt2);  pStmt2 = 0;
  
    if( iMode2==5 && iMode!=-1 ){
      printf("%s sum of cnt: %lld\n", zTag, sumCnt);
      rc = sqlite3_prepare_v2(db,"SELECT sum(cnt*cnt) FROM wordcount", -1,
                              &pStmt1, 0);
      if( rc==SQLITE_OK && sqlite3_step(pStmt1)==SQLITE_ROW ){
        printf("%s double-check: %lld\n", zTag,sqlite3_column_int64(pStmt1,0));
      }
      sqlite3_finalize(pStmt1);
    }
  } /* End the --all loop */

  /* Close the input file after the last read */
  if( zFileToRead ) fclose(in);

  /* Database connection statistics printed after both prepared statements
  ** have been finalized */
  if( showStats ){
    sqlite3_db_status(db, SQLITE_DBSTATUS_LOOKASIDE_USED, &iCur, &iHiwtr, 0);
    printf("%s Lookaside Slots Used:        %d (max %d)\n", zTag, iCur,iHiwtr);
    sqlite3_db_status(db, SQLITE_DBSTATUS_LOOKASIDE_HIT, &iCur, &iHiwtr, 0);
    printf("%s Successful lookasides:       %d\n", zTag, iHiwtr);
    sqlite3_db_status(db, SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE, &iCur,&iHiwtr,0);
    printf("%s Lookaside size faults:       %d\n", zTag, iHiwtr);
    sqlite3_db_status(db, SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL, &iCur,&iHiwtr,0);
    printf("%s Lookaside OOM faults:        %d\n", zTag, iHiwtr);
    sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_USED, &iCur, &iHiwtr, 0);
    printf("%s Pager Heap Usage:            %d bytes\n", zTag, iCur);
    sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_HIT, &iCur, &iHiwtr, 1);
    printf("%s Page cache hits:             %d\n", zTag, iCur);
    sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_MISS, &iCur, &iHiwtr, 1);
    printf("%s Page cache misses:           %d\n", zTag, iCur); 
    sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_WRITE, &iCur, &iHiwtr, 1);
    printf("%s Page cache writes:           %d\n", zTag, iCur); 
    sqlite3_db_status(db, SQLITE_DBSTATUS_SCHEMA_USED, &iCur, &iHiwtr, 0);
    printf("%s Schema Heap Usage:           %d bytes\n", zTag, iCur); 
    sqlite3_db_status(db, SQLITE_DBSTATUS_STMT_USED, &iCur, &iHiwtr, 0);
    printf("%s Statement Heap Usage:        %d bytes\n", zTag, iCur); 
  }

  sqlite3_close(db);

  /* Global memory usage statistics printed after the database connection
  ** has closed.  Memory usage should be zero at this point. */
  if( showStats ){
    sqlite3_status(SQLITE_STATUS_MEMORY_USED, &iCur, &iHiwtr, 0);
    printf("%s Memory Used (bytes):         %d (max %d)\n", zTag,iCur,iHiwtr);
    sqlite3_status(SQLITE_STATUS_MALLOC_COUNT, &iCur, &iHiwtr, 0);
    printf("%s Outstanding Allocations:     %d (max %d)\n",zTag,iCur,iHiwtr);
    sqlite3_status(SQLITE_STATUS_PAGECACHE_OVERFLOW, &iCur, &iHiwtr, 0);
    printf("%s Pcache Overflow Bytes:       %d (max %d)\n",zTag,iCur,iHiwtr);
    sqlite3_status(SQLITE_STATUS_SCRATCH_OVERFLOW, &iCur, &iHiwtr, 0);
    printf("%s Scratch Overflow Bytes:      %d (max %d)\n",zTag,iCur,iHiwtr);
    sqlite3_status(SQLITE_STATUS_MALLOC_SIZE, &iCur, &iHiwtr, 0);
    printf("%s Largest Allocation:          %d bytes\n",zTag,iHiwtr);
    sqlite3_status(SQLITE_STATUS_PAGECACHE_SIZE, &iCur, &iHiwtr, 0);
    printf("%s Largest Pcache Allocation:   %d bytes\n",zTag,iHiwtr);
    sqlite3_status(SQLITE_STATUS_SCRATCH_SIZE, &iCur, &iHiwtr, 0);
    printf("%s Largest Scratch Allocation:  %d bytes\n",zTag,iHiwtr);
  }
  return 0;
}
