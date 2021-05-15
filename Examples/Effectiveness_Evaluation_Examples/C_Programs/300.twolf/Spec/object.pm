$benchnum  = '300';
$benchname = 'twolf';
$exename   = 'twolf';
$benchlang = 'C';
@base_exe  = ($exename);

$obiwan = 1;

@sources=qw(acceptt.c addimp.c alignfeed.c buildimp.c changrid.c clean.c
	    closepins.c config1.c configure.c configuref.c controlf.c countf.c
	    date.c debug.c dimbox.c finalwire.c findcost.c findcostf.c
	    findest.c findfeeds.c findrchk.c findrcost.c findunlap.c globe.c
	    globedbg.c globroute.c gparser.c grdcell.c hash.c implfeeds.c
	    main.c mergplist.c move.c mt.c okmalloc.c outcm.c outpins.c
	    output.c parser.c purcost.c qsorte.c qsortg.c qsortgdx.c qsortx.c
	    rand.c readblck.c readcell.c readnets.c readpar.c readseg.c
	    savewolf.c sortpin.c stats.c uc0.c ucg0.c ucgxp.c uclosepns.c
	    ucxx1.c ucxx2.c ucxxo1.c ucxxo2.c ucxxp.c uglobe.c uglobrout.c
	    ugpair.c uloop.c uloop2.c unetseg.c unlap.c upair.c urcost.c
	    utemp.c utils.c xcompact.c xpickint.c);
$need_math='yes';
$bench_flags = '-DSPEC_CPU2000';

sub invoke {
    my ($me) = @_;
    my @rc;

    my $exe  = $me->exe_file;
    my $name = $me->name;

    for ($me->input_files_base) {
	if (($name) = m/(.*).net$/) {
	    push (@rc, { 'command' => $exe, 
			 'args'    => [ $name ], 
			 'output'  => "$name.stdout",
			 'error'   => "$name.err",
			});
	}
    }
    @rc;
}

1;
