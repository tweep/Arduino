# Notes on IR Libraries 

## IRlib2 
Available here: https://github.com/cyborg5/IRLib2
This library has problems when used with the FastLED library - when calling the delay function ( which sets the frame rate ) - the IR remote codes are not read correctly anymore: 

     FastLED.delay(40) 


## IRremote.h and IRremoteInt.h 
Works ok, but seems to not handle interrupts - the IR singal gets only read 
every now-and-than. 



