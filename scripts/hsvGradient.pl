#!/usr/local/bin/env perl 

use strict;
use warnings;
 use POSIX;

while(1){ 
  for (my $i=0; $i< 100; $i++ ) {  
    getGreenToRed($i);  
    getGreenToRedNew($i);  
  } 
} 


# See also JSfiddle  http://jsfiddle.net/vogelj/3rvhhqcp/

sub getGreenToRed{ 
    my $percent = shift; 
    my $red   = $percent<50 ? 255 : floor(255-($percent*2-100)*255/100);
    my $green = $percent>50 ? 255 : floor(($percent*2)*255/100);
    print "rgb($red,$green,0)\n"; 
} 


sub getGreenToRedNew{
    my $percent = shift; 

    my ($red, $green); 
    if ( $percent <= 50 ) {  
      $red = 255;
      $green = floor(($percent*2)*255/100); 
    } else {  
      # percent > 50  
       $red = floor(255-($percent*2-100)*255/100);
       $green = 255;
    } 

    #my $red   = $percent<50 ? 255 : floor(255-($percent*2-100)*255/100);
    #my $green = $percent>50 ? 255 : floor(($percent*2)*255/100);
    print "rgb($red,$green,0)\n";
}

