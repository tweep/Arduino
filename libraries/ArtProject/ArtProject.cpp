/* 
    ArtProject.cpp - a simple library for the Vasily Kadinsky project 
    The functions let an LED strip cycle trough different colors. 
    Main functions: 
    - rainbow()    : lights up individual pixels of the LED strand 
                     in different colors. The colors "flow" into 
                     the next color. At any time the whole strand 
                     shows the colors of the rainbow. 
                     
    - rainbowCycle : lights up the full strand in a single color, 
                      then moves onto the next color - until all 
                       
*/ 


#include "Arduino.h"
#include "ArtProject.h"       // include the header file declartion 

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


// constructor - returns object ArtProject Obj

ArtProject::ArtProject(int nrLeds, int pin){  
    _strip = Adafruit_NeoPixel(nrLeds, pin, NEO_GRB + NEO_KHZ800);  
    _strip.begin();
    _strip.setBrightness(128); // max 255
    //_strip.show(); // Initialize all pixels to 'off'
}  

ArtProject::~ArtProject(){ /* nothing to destruct */ }  

/* 
   Function   :  rainbowCycle()
   Description:  Lights a full LED strand in the same color.
*/



void ArtProject::rainbowCycle() {  

  // loop trough all pixels in the strand
  // color the full strip in the same color 
  
  // bitwise AND 
  // (_colorNumber & 255 ) is not really needed. It assures that the value 
  // will always be between 0 - 255. 
  // perl -e 'print 260 & 250' = 4
   
  uint32_t currentStripColor = Wheel(_colorNumber & 255);
  
  for(int pixelNr=0; pixelNr< _strip.numPixels(); pixelNr++) {
    _strip.setPixelColor(pixelNr, currentStripColor);
  }
  _strip.show();
  
  _colorNumber++;
  
  // reset color spectrum again at the beginning of the rainbow.
  if (_colorNumber > 256 ) _colorNumber=0;
}



/* 
   Function   :  rainbow() 
   Description:  Colors individual pixels of an LED strand individually, 
                 The full strand will show at any time the 255 colors of the 
                 rainbow.
                 On each call, the color of a pixel blends into the next color.
                  
*/


void ArtProject::rainbow() {  

  for(int pixelNr=0; pixelNr< _strip.numPixels(); pixelNr++) {
    _strip.setPixelColor(pixelNr, Wheel(((pixelNr * 256 / _strip.numPixels()) + _colorIndex) & 255) );
  }
  _strip.show();
  
  _colorIndex++;
  
  // reset color spectrum again at the beginning of the rainbow.
  if (_colorIndex > 256 ) _colorIndex=0;
}


/* 
   Function   :  rgbColorConversion(int, int, int) 
   Description:  Converts 3 integers into a single integer which 
                 represents a color.
*/

uint32_t rgbColorConversion(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
} 




/* 
   Function   :  Wheel(int 0 - 255 )
   Description:  Converts an integer into a color, represented by R,G,B values.
                 The colors from 0 - 255 represent a full rainbow.
*/

uint32_t ArtProject::Wheel(byte WheelPos) {
  
  WheelPos = 255 - WheelPos;
  
  if(WheelPos < 85) {
    return rgbColorConversion(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  
  if(WheelPos < 170) {
    WheelPos -= 85;
    return rgbColorConversion(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  
  WheelPos = WheelPos - 170;
  return rgbColorConversion(WheelPos * 3, 255 - WheelPos * 3, 0);
} 


/*
uint32_t ArtProject::Wheel(byte WheelPos) {
  
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return _strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return _strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos = WheelPos - 170;
  
  return _strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
*/


void ArtProject::lightUp(uint8_t r, uint8_t g, uint8_t b){ 

  _strip.show(); // Initialize all pixels to 'off'
  for(uint16_t i=0; i< _strip.numPixels(); i++) {
    _strip.setPixelColor(i, rgbColorConversion(r, g, b)) ;
    _strip.show(); 
    delay(50);
  }
  //_strip.show(); // Initialize all pixels to 'off'
}  





