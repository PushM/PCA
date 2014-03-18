#!/usr/bin/perl
my $SOURCE=$ARGV[0];
my $OPTIM=$ARGV[1];
my $topt = `(/usr/bin/time -f "%e" ./$OPTIM > /dev/null) 2>&1`;
my $torg = `(/usr/bin/time -f "%e" ./$SOURCE > /dev/null) 2>&1`;
my $quoc = $torg/$torg;
print "$quoc\n";
