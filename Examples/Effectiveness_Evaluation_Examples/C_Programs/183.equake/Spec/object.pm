$benchnum  = '183';
$benchname = 'equake';
$exename   = 'equake';
$benchlang = 'C';
@base_exe  = ($exename);

$reltol = 0.00001;
$abstol = undef;

@sources=qw(quake.c);
$need_math='yes';

sub invoke {
    my ($me) = @_;
    my $name;
    my @rc;

    my $exe = $me->exe_file;
    for ($me->input_files_base) {
	if (($name) = m/(.*).in$/) {
	    push (@rc, { 'command' => $exe, 
			 'args'    => [ ], 
			 'input'   => $_,
			 'output'  => "$name.out",
			 'error'   => "$name.err",
			});
	}
    }
    return @rc;
}

1;
