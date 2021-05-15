###############################################################################
# SPECtools2000
#   Version 0.3
#   This makefile should NOT be changed other than to customize for a 
#   particular benchmark.  Users may overide variables by placing them
#   in the Makefile.spec file.  Or by using the "runspec" program to 
#   build the Makefile.spec file for them.
###############################################################################
#	BENCHMARK	-- standard definitions for this benchmark

NUMBER    = 197
NAME      = parser
EXEBASE   = parser
BENCHLANG = C
SOURCES	  = analyze-linkage.c and.c build-disjuncts.c extract-links.c \
	    fast-match.c idiom.c main.c massage.c parse.c \
	    post-process.c print.c prune.c read-dict.c utilities.c \
	    xalloc.c word-file.c strncasecmp.c
NEED_MATH = yes

# Include standard template for this suite
-include ../../../../Makefile.defaults
-include ../../../Makefile.defaults
-include ../../Makefile.defaults
-include ../Makefile.defaults

nomakefiles:
	@echo "*** Whoops!  I didn't find a Makefile.defaults file."
	@echo "*** Your distribution is probably corrupt."
	@echo
