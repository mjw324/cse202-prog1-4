#!/usr/bin/perl

# $ARGV[0] is file to be scanned
# $ARGV[1] is number of children

use strict;
use warnings;

if ($#ARGV < 0) {
  print "\nUsage example: $0 output\n";
  print "\n  where 8 is value of NUMCHILDREN and output is file produced as follows:\n";
  print "\n    prog3 2>&1 | tee output\n\n";
  exit(0);
}

my $score = 0;
my $numChildren = $ARGV[1];
my $installing = 0;
my $childAdding = 0;
my $sending = 0;
my $caught = 0;
my $normally = 0;
my $abnormally = 0;
my $finalSum = 0;
my $parentAdding = 0;

open(IN, "<$ARGV[0]") || die("Can't open $ARGV[0] for reading - $!");
while (<IN>) {
  if (/Parent process \d+ installing SIGUSR2 handler/i) {
    $installing++;
  } elsif (/Child process \d+ sending SIGUSR2 to parent process with the partial sum \d+/i) {
    $sending++;
  } elsif (/Parent process caught SIGUSR2 with partial sum: \d+/i) {
    $caught++;
  } elsif (/Child process \d+ terminated normally with exit status \d+/i) {
    $normally++;
  } elsif (/Child process \d+ terminated abnormally/i) {
    $abnormally++;
  } elsif(/Final sum = 8390656/i){
    $finalSum++;
  } elsif(/Parent process \d+ adding the elements from index \d+ to \d+/i){
    $parentAdding++;
  } elsif(/Child process \d+ adding the elements from index \d+ to \d+/i){
    $childAdding++;
  }
}
close(IN);
my $processes = $numChildren+1;
print "Testing for P = $processes\n";
print "installing = $installing\n";
print "sending    = $sending\n";
print "caught     = $caught\n";
print "normally   = $normally\n";
print "abnormally = $abnormally\n";
print "parent adding = $parentAdding\n";
print "child adding = $childAdding\n";
print "final sum = $finalSum\n";

if ($installing == 1) {
  $score += 2;
} elsif ($installing > 1) {
  $score += 1;
}
if ($sending == $numChildren) {
  $score += 20;
} elsif ($sending > 0) {
  $score += 10;
}
if ($caught == $numChildren) {
  $score += 20;
} elsif ($caught > 0) {
  $score += 10;
}
if ($normally == $numChildren) {
  $score += 20;
} elsif ($normally > 0) {
  $score += 10;
}
if ($abnormally == 0) {
  $score += 2;
}
if($finalSum == 1){
    $score += 4;
}
if($parentAdding == 1){
    $score += 2;
}
if($childAdding == $numChildren){
    $score += 20;
} elsif($childAdding > 0){
    $score += 10;
}
print "---------------\n";
print "sub-score  = $score/90\n";
print "\n\n";
exit($score);
