$benchnum  = '179';
$benchname = 'art';
$exename   = 'art';
$benchlang = 'C';
@base_exe  = ($exename);

$reltol = 0.01; 

@sources=qw(scanner.c);
$need_math='yes';

sub invoke {
    my ($me) = @_;
    my @rc;
    my $size = $me->size;
    my $exe  = $me->exe_file;

    if($size eq 'ref') {
	push (@rc, { 'command' => $exe, 
			'args'    => [  '-scanfile c756hel.in',
					'-trainfile1 a10.img',
					'-trainfile2 hc.img',
					'-stride 2',
					'-startx 110',
					'-starty 200',
					'-endx 160',
					'-endy 240', 
                                        '-objects 10' ],
			'output'  => "$size.1.out",
			'error'   => "$size.1.err",
		    });

	push (@rc, { 'command' => $exe, 
			'args'    => [  '-scanfile c756hel.in',
					'-trainfile1 a10.img',
					'-trainfile2 hc.img',
					'-stride 2',
					'-startx 470',
					'-starty 140',
					'-endx 520',
					'-endy 180', 
                                        '-objects 10'],
			'output'  => "$size.2.out",
			'error'   => "$size.2.err",
		    });
    } elsif($size eq 'test') {
	push (@rc, { 'command' => $exe, 
			'args'    => [  '-scanfile c756hel.in',
					'-trainfile1 a10.img',
					'-stride 2',
					'-startx 134',
					'-starty 220',
					'-endx 139',
					'-endy 225', 
                                        '-objects 1' ],
			'output'  => "$size.out",
			'error'   => "$size.err",
		    });
    } elsif($size eq 'train') {
	push (@rc, { 'command' => $exe, 
			'args'    => [ '-scanfile c756hel.in',
			               '-trainfile1 a10.img',
				       '-stride 2',
				       '-startx 134',
				       '-starty 220',
				       '-endx 184',
				       '-endy 240', 
                                       '-objects 3' ], 
			'output'  => "$size.out",
			'error'   => "$size.err",
		    });
    } else {
	Log (0, $me->benchmark . ": Doesn't support size '$size'\n");
    }
    return @rc;
}

1;
