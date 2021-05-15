###############################################################################
# SPECtools2000
#   Version 0.3
#   This makefile should NOT be changed other than to customize for a 
#   particular benchmark.  Users may overide variables by placing them
#   in the Makefile.spec file.  Or by using the "runspec" program to 
#   build the Makefile.spec file for them.
###############################################################################
#	BENCHMARK	-- standard definitions for this benchmark

NUMBER    = 300
NAME      = twolf
EXEBASE   = twolf
BENCHLANG = C
SOURCES   = acceptt.c addimp.c alignfeed.c buildimp.c changrid.c clean.c   \
	    closepins.c config1.c configure.c configuref.c controlf.c      \
	    countf.c date.c debug.c dimbox.c finalwire.c findcost.c        \
	    findcostf.c findest.c findfeeds.c findrchk.c findrcost.c       \
	    findunlap.c globe.c globedbg.c globroute.c gparser.c grdcell.c \
	    hash.c implfeeds.c main.c mergplist.c move.c mt.c okmalloc.c   \
	    outcm.c outpins.c output.c parser.c purcost.c qsorte.c         \
	    qsortg.c qsortgdx.c qsortx.c rand.c readblck.c readcell.c      \
	    readnets.c readpar.c readseg.c savewolf.c sortpin.c stats.c    \
	    uc0.c ucg0.c ucgxp.c uclosepns.c ucxx1.c ucxx2.c ucxxo1.c      \
	    ucxxo2.c ucxxp.c uglobe.c uglobrout.c ugpair.c uloop.c         \
	    uloop2.c unetseg.c unlap.c upair.c urcost.c utemp.c utils.c    \
	    xcompact.c xpickint.c
NEED_MATH = yes
BENCH_FLAGS = -DSPEC_CPU2000

# Include standard template for this suite
-include ../../../../Makefile.defaults
-include ../../../Makefile.defaults
-include ../../Makefile.defaults
-include ../Makefile.defaults

nomakefiles:
	@echo "*** Whoops!  I didn't find a Makefile.defaults file."
	@echo "*** Your distribution is probably corrupt."
	@echo
