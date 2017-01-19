#!/usr/local/bin/env perl 

use strict;
use warnings; 

my $mod = 5; 
my $operator = "-1"; 
my $start = 0; 

for (my $i = 1 ; $i < 20; $i++ ) { 

   $start = getNumber($start,$mod); 
   print "start $start\n";  
}  


sub getNumber{  
  my ($number, $mod) = @_; 

  if ( $number % $mod == 0 ) {  
     $operator = $operator * -1; 
  }  
  $number = $number + $operator;
  return $number;
} 
