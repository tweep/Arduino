#!/usr/local/bin/env perl 

use strict;
use warnings;

my $numPixel = 64; 

my $counter = 0; 

while (1) {   
    $counter++;
    for(my $pixelNr=0; $pixelNr < $numPixel ; $pixelNr++) { 
        print "Pixel Nr: $pixelNr\t:  ";  
        Wheel((($pixelNr * 256 / $numPixel) + $counter) &  255) ;
    }
    $counter = 0 if ( $counter > 256 ) ;  
   print "\n\n"; 
}

=head 
Wheel (int 1 - 255 )  

Converts a number between 1 and 255 into an RGB color. 
The number is the "index" of a color on the rainbow.

=cut 

sub Wheel {  
  my $wheel_position = shift; 

  print "Wheelposition: $wheel_position\t";  

  $wheel_position = 255 - $wheel_position;
  if($wheel_position < 85) {
     rgbPrint((255 - $wheel_position * 3), 0, $wheel_position * 3); 
     return;
  } 

  if($wheel_position < 170) {
    $wheel_position -= 85;
     rgbPrint(0, $wheel_position * 3, 255 - $wheel_position * 3); 
     return;
  } 

  $wheel_position = $wheel_position - 170;
  rgbPrint($wheel_position * 3, 255 - $wheel_position * 3, 0); 
  return;
}  


sub rgbPrint{  
  my (  $r, $g, $b) = @_; 

  print "RGB: " . int($r).",".int($g).",".int($b)."\n"; 
} 
