#!/usr/bin/perl
my $SOURCE=$ARGV[0];
my $OPTIM=$ARGV[1];
my $NMIN=$ARGV[2];
my $NMAX=$ARGV[3];
my $NSTEP=$ARGV[4];
my $NEXEC=$ARGV[5];
for(my $DECS = $NMIN; $DECS <= $NMAX; $DECS += $NSTEP) {
    my $org = `./$SOURCE $DECS`;
    my $opt = `./$OPTIM $DECS`;
    unless($org eq $opt){
	print "No correct results for N=$DECS\n";
	exit 1;
    }
    my $avg = 0.0;
    for(my $i = 0; $i<$NEXEC; $i++){
	$avg += `(/usr/bin/time -f "%e" ./$OPTIM $DECS > /dev/null) 2>&1`;
    }
    $avg = $avg / $NEXEC;
    print "$DECS\t$avg\n";
}
