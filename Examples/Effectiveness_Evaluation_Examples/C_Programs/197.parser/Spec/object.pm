$benchnum  = '197';
$benchname = 'parser';
$exename   = 'parser';
$benchlang = 'C';
@base_exe  = ($exename);

@sources=qw(analyze-linkage.c and.c build-disjuncts.c extract-links.c
	    fast-match.c idiom.c main.c massage.c parse.c post-process.c
	    print.c prune.c read-dict.c utilities.c xalloc.c word-file.c);
$need_math='yes';
$bench_flags = '-DSPEC_CPU2000';

sub invoke {
    my ($me) = @_;
    my (@rc);

    my $dictionary = "2.1.dict";
    my $exe = $me->exe_file;

    for ($me->input_files_base) {
	if (($name) = m/(.*).in$/) {
	    push (@rc, { 'command' => $exe, 
			 'args'    => [ $dictionary, '-batch' ],
			 'input'   => $_,
			 'output'  => "$name.out",
			 'error'   => "$name.err",
			});
	}
    }
    @rc;
}

1;
