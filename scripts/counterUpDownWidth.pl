#!/usr/local/bin/env perl 

use strict;
use warnings; 

my $width = 10; 
my $operator = "1"; 
my $start = 250; 
my $end = $start + $width;
my $global = $start;

while(1){
   my $var =  getNumber($start, $end); 
   print "color: $var\n";  
}  


sub getNumber{  
  my ( $start, $end) = @_; 

  if ($global >= $end) {  
     $operator = -1; 
  }   
  if ( $global <= $start ) {  
     $operator = 1; 
  } 
  $global += $operator;
  return $global & 255;
} 
