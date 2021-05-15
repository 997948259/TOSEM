$benchnum  = '164';
$benchname = 'gzip';
$exename   = 'gzip';
$benchlang = 'C';
@base_exe  = ($exename);

@sources=qw(bits.c deflate.c gzip.c getopt.c inflate.c lzw.c spec.c trees.c
	    unlzh.c unlzw.c unpack.c unzip.c util.c zip.c);

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
