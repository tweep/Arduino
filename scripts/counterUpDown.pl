#!/usr/local/bin/env perl 

use strict;
use warnings; 

my $index_max = 100;           # range 
my $operator = "-1"; 
my $index_start = 0;        # start index  ( A start of 20 with a range=5 goes from 20,21,22,23,24, 25 ,24,23...

while(1){
   $index_start = getNumber($index_start,$index_max); 
   print "color: $index_start\n";  
}  


sub getNumber{  
  my ($number, $index_max) = @_; 

  if ( $number % $index_max == 0 ) {  
     $operator = $operator * -1; 
  }  
  $number = $number + $operator;
  return $number;
} 
