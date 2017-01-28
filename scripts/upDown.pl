#!/usr/local/bin/env perl 

use strict;
use warnings; 

my $index_start = 30;    # first value of range 
my $index_end =   60;    # 2nd value of range  
my $index ;   
my $op = "+1"; 

while(1){ 
    if ( $index >=$index_end) {  
      $op = -1;
    }
    if ( $index <= $index_start ) { 
      $op = +1;
    }  
    $index = $index + $op;
   print "color: $index\n";  
}  

