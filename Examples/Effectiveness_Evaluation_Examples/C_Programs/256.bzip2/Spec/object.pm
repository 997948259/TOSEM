$benchnum  = '256';
$benchname = 'bzip2';
$exename   = 'bzip2';
$benchlang = 'C';
@base_exe  = ($exename);

@sources=qw(spec.c bzip2.c);

sub invoke {
    my ($me) = @_;
    my (@rc);

    my @temp = main::read_file('control');
    my $exe = $me->exe_file;

    for (@temp) {
	my ($name, $size) = split;
	next if m/^\s*#/ || m/^\s*$/;
	next if $size <= 0;
	push (@rc, { 'command' => $exe, 
	             'args'    => [ $name, $size ], 
		     'output'  => "$name.out",
		     'error'   => "$name.err",
		    });
    }
    return @rc;
}

1;
