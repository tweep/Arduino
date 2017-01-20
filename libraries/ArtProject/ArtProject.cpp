/* 
    ArtProject.cpp - a simple library for the Vasily Kadinsky project 
    The functions let an LED strip cycle trough different colors. 
    
    Note: New transitions can easily be visualized via JSfiddle: 
    
    http://jsfiddle.net/vogelj/6scfhqed/
    
    
    Main functions: 
    - rainbow()    : lights up individual pixels of the LED strand 
                     in different colors. The colors "flow" into 
                     the next color. At any time the whole strand 
                     shows the colors of the rainbow. 
                     
    - rainbowCycle(): lights up the full strand in a single color, 
                      then moves onto the next color - until all  

    - rgbBand():      Cycles the strip only trough a part of a given 
                      RGB spectrum - back and forth 
                      red ---- green -- purple -- blue 
                                          ^        ^
                                          |--BAND--| 
                       
    - hsvTransition() Cycles trough the HSV spectrum 
                      See: http://jsfiddle.net/vogelj/6scfhqed/
                       
*/ 


#include "Arduino.h"
#include "ArtProject.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


ArtProject::ArtProject(uint8_t nrLeds, uint8_t pin, uint8_t brightness, uint8_t startColor, uint8_t spectrumWidth  ){  
    _spectrumStart = startColor; 
    _colorNumber = startColor;
    _spectrumEnd = startColor + spectrumWidth;

    _strip = Adafruit_NeoPixel(nrLeds, pin, NEO_GRB + NEO_KHZ800);  
    _strip.begin();
   // Bitwise & : assure that value is always between 0 - 255 
    _strip.setBrightness(brightness & 255 ); 
    
}  



/**
 * Initialize an ArtProject pixel, pin and brightness 
 * 
 * @param  (int) Number of LEDs of the strand we like to initialize
 * @param  (int) PWM pin connected to the strand 
 * @param  (int) Brightness of the strand 
 */


ArtProject::ArtProject(uint8_t nrLeds, uint8_t pin, uint8_t brightness  ){  
    _strip = Adafruit_NeoPixel(nrLeds, pin, NEO_GRB + NEO_KHZ800);  
    _strip.begin();
   // Bitwise & : a`ssure that value is always between 0 - 255 
    _strip.setBrightness(brightness & 255 ); 
}  

/**
 * Initialize an ArtProject pixel and pin 
 * 
 * @param  (int) Number of LEDs of the strand we like to initialize
 * @param  (int) PWM pin connected to the strand.
 * Default brightness is 128  
 */


ArtProject::ArtProject(uint8_t nrLeds, uint8_t pin ){  
    _strip = Adafruit_NeoPixel(nrLeds, pin, NEO_GRB + NEO_KHZ800);  
    _strip.begin();
    _strip.setBrightness(255); 
}  

ArtProject::~ArtProject(){ /* nothing to destruct */ }  


/** 
 *   Function  : rgbBand() 
 *
 *   Cycles trough a part of an RGB spectrum 
 *
 *   _spectrumStart  - set during initialization
 *   _spectrumEnd    - set during initialization
 */


void ArtProject::rgbBand() {   

  if ( _colorNumber >= _spectrumEnd ) {  
     _var = -1;  // ugly - can we do this without a global variable ?
  }  
  if ( _colorNumber <= _spectrumStart) { 
     _var = 1;  // ugly - can we do this without a global variable ?
  }  

  _colorNumber +=  _var;  
  _colorNumber = _colorNumber & 255;

  uint32_t calcStripColor = Wheel(_colorNumber);

  for (uint8_t pixelNr=0; pixelNr< _strip.numPixels(); pixelNr++) {
    _strip.setPixelColor(pixelNr, calcStripColor);
  }
  _strip.show();
}



/**
 *  Function   :  rainbowCycle()
 *  Description:  Lights a full LED strand in the same color. 
 *
 *  Note: The bitwise AND operator  (_colorNumber & 255 ) is not 
 *  really needed. It assures that the value will always be between 
 *  0 - 255. 
 *  perl -e 'print 260 & 250' = 4 
 *
*/

void ArtProject::rainbowCycle() {  

  // Computes the next color based on _colorNumber 
  
  uint32_t currentStripColor = Wheel(_colorNumber & 255);  // remove &255
  
  for (uint8_t pixelNr=0; pixelNr< _strip.numPixels(); pixelNr++) {
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

  for (uint8_t pixelNr=0; pixelNr< _strip.numPixels(); pixelNr++) {
    _strip.setPixelColor(pixelNr, Wheel(((pixelNr * 256 / _strip.numPixels()) + _colorIndex) & 255) ); // remove &255
  }
  _strip.show();
  _colorIndex++;
  
  // reset color spectrum once we reach the end of the rainbow ( colors from 0 - 255 ) 
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
  WheelPos = WheelPos & 255; // Avoid we pass any value > 255
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



void ArtProject::lightUp(uint8_t r, uint8_t g, uint8_t b){ 

  _strip.show(); // Initialize all pixels to 'off'
  for (uint8_t i=0; i< _strip.numPixels(); i++) {
    _strip.setPixelColor(i, rgbColorConversion(r, g, b)) ;
    _strip.show(); 
    delay(50);
  }
}  





