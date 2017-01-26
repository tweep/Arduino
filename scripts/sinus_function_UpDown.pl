#!/usr/local/bin/env perl 

use strict;
use warnings;


my $min = 0; 
my $max = 99;   

my $interval = $max - $min; 
my $counter; 
my $color_index; 
while (1) { 

  if ( $counter >= 2*$interval) {  
    $counter = -1; 
  }   

  if ( sin( $counter * (6.28 / (2*$interval))) >= 0  ) {   
   $color_index++;
  }
  if ( sin( $counter * (6.28 / (2*$interval))) <= 0 ) {  
   $color_index--;
  }
  $counter++;
  print "Color index ($min - $max ) : $color_index\n";   
}
