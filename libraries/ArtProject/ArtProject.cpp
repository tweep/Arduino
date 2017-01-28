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
                                        start     end

    - hsvCycle()   
    - percentToRGB() Cycles trough the HSV spectrum (1..100)   
                      The full strad will be lit in a single color, and transition 
                      together trough the spectrum 
                      SpectrumStart and SpectrumEnd have to be set before, 
                      trough constructonr or setSpectrumStart/End methods.  
                      See: http://jsfiddle.net/vogelj/6scfhqed/
                       
*/ 


#include "Arduino.h"
#include "ArtProject.h"
#include "SpectrumBand.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


/**
 * Initialize an ArtProject with a pectrum band 
 * 
 * @param  (int) Number of LEDs of the strand we like to initialize
 * @param  (int) PWM pin connected to the strand 
 * @param  (int) Brightness of the strand  
 * @param  (SpectrumBand) type defintion of a spectrum band 
 *
 */

ArtProject::ArtProject(uint8_t nrLeds, uint8_t pin, uint8_t brightness, SpectrumBand specBand ){  
    // initialize strip 
    _strip = Adafruit_NeoPixel(nrLeds, pin, NEO_GRB + NEO_KHZ800);  
    _strip.begin();
   // Bitwise & : assure that value is always between 0 - 255 
    _strip.setBrightness(brightness & 255 );  
   
    // set spectrum values 
    _spectrumStart = specBand.start; 
    _spectrumEnd = specBand.end;  
}


/**
 * Initialize an ArtProject pixel, pin, brightness, spectrum start and spectrum end 
 * Note: Initalize with Start,End is also possible  
 * @param  (int) Number of LEDs of the strand we like to initialize
 * @param  (int) PWM pin connected to the strand 
 * @param  (int) Brightness of the strand 
 * @param  (int) Spectrum color start 
 * @param  (int) Width of the color spectrum 
 */

ArtProject::ArtProject(uint8_t nrLeds, uint8_t pin, uint8_t brightness, uint8_t startColor, uint8_t endColor){    
    // check data 
    if ( startColor > endColor ) {  
        startColor = 0; 
    }
    if (endColor < startColor) {  
       endColor = 100;
    }  
    _spectrumStart = startColor; 
    _colorNumber = startColor;
    _spectrumEnd = endColor;

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
   // Bitwise & : assure that value is always between 0 - 255 
    _strip.setBrightness(255); 
}  

ArtProject::~ArtProject(){ /* nothing to destruct */ }  



/**
 * Calculates the next color number - and walks trough the 
 * spectrum up and down like a sinus function. 
 * 
 * @param  (int) Number of LEDs of the strand we like to initialize
 * @param  (int) PWM pin connected to the strand.
 * Default brightness is 128  
 */


void ArtProject::setNextColorNumber() {     

  if ( _colorNumber >= _spectrumEnd ) {  
     _var = -1;  // ugly - can we do this without a global variable ?
  }  
  if ( _colorNumber <= _spectrumStart) { 
     _var = 1;  // ugly - can we do this without a global variable ?
  }  
  _colorNumber +=  _var;  
} 


// unsure why i added this ... 
uint8_t ArtProject::setNextColorNumber(uint8_t color) {     
  
  if ( color >= _spectrumEnd ) {  
     _var = -1;
  }  
  if ( color <= _spectrumStart) { 
     _var = 1;
  }  
  color +=  _var;  
  return color; 
} 

/* 
   Function   :  rgbColorConversion(int, int, int) 
   Description:  Converts 3 integers into a single integer which 
                 represents a color.
*/

uint32_t rgbColorConversion(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
} 



/** 
 *   Function  : percentToRGB() 
  *  Description:  Lights a full LED strand IN THE SAME color
                   and transitions the full strand trough the HSV spectrum 
                   (from green --> yellow --> red ) and back. 
 *   Note: This function requires that spec
 *   Converts a number between 0 and 100 into a color 
 *   0   - green 
 *   50  - yellow 
 *   100 - red  
 * 
 */


void ArtProject::percentToRGB() {   
  uint32_t calcStripColor = hsvToRGBconversion(_colorNumber); 

   for (uint8_t pixelNr=0; pixelNr< _strip.numPixels(); pixelNr++) {
     _strip.setPixelColor(pixelNr, calcStripColor);
   }
   _strip.show(); 

    setNextColorNumber(); 
}


/* 
   Function   :  hsvbow() 
   Description:  Colors individual pixels of an LED strand individually, 
                 The full strand will show at any time the 255 colors of the 
                 HSV spectrum ( 0 - 100 percent) 
                 On each call, the color of a pixel blends into the next color.
                  
*/


void ArtProject::hsvbow() {  

  for (uint8_t pixelNr=0; pixelNr< _strip.numPixels(); pixelNr++) { 
    _strip.setPixelColor(pixelNr, hsvToRGBconversion( (pixelNr * 100  / _strip.numPixels()) + _colorNumber) ); 
  }
  _strip.show();
  _colorNumber++;
 
  // cycle forward and back / up and down here.  
  // reset color spectrum once we reach the end of the rainbow ( colors from 0 - 255 ) 
  if (_colorNumber >= 100 ) {
    _colorNumber = 0;
  }
}


/** 
 *   Function  : rgbBand() 
 *
 *   Cycles trough a part of an RGB spectrum 
 *
 *   _spectrumStart  - set during initialization
 *   _spectrumEnd    - set during initialization
 */


void ArtProject::rgbBand() {   
  setNextColorNumber(); 

  _colorNumber = _colorNumber & 255;

  uint32_t calcStripColor = colorWheel(_colorNumber);

  for (uint8_t pixelNr=0; pixelNr< _strip.numPixels(); pixelNr++) {
    _strip.setPixelColor(pixelNr, calcStripColor);
  }
  _strip.show();
}



/**
 *  Function   :  rainbowCycle()
 *  Description:  Lights a full LED strand IN THE SAME color. 
 *
 *  Note: The bitwise AND operator  (_colorNumber & 255 ) is not 
 *  really needed. It assures that the value will always be between 
 *  0 - 255. 
 *  perl -e 'print 260 & 250' = 4 
 *
*/

void ArtProject::rainbowCycle() {  

  uint32_t nextStripColor = colorWheel(_colorNumber & 255);  // remove &255
  
  for (uint8_t pixelNr=0; pixelNr< _strip.numPixels(); pixelNr++) {
    _strip.setPixelColor(pixelNr, nextStripColor);
  }
  _strip.show();
  _colorNumber++;
  
  // reset color spectrum again at the beginning of the rainbow.
  if (_colorNumber >= 255 ) _colorNumber=0;
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
    _strip.setPixelColor(pixelNr, colorWheel(((pixelNr * 256 / _strip.numPixels()) + _colorNumber) & 255) ); // remove &255
  }
  _strip.show();
  _colorNumber++;
  
  // reset color spectrum once we reach the end of the rainbow ( colors from 0 - 255 ) 
  if (_colorNumber >= 255 ) {
    _colorNumber = 0;
  }
}




/* 
   Function   :  colorWheel(int 0 - 255 )
   Description:  Converts an integer into a color, represented by R,G,B values.
                 The colors from 0 - 255 represent a full rainbow.
*/

uint32_t ArtProject::colorWheel(byte WheelPos) { 
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

/*
 * Function   : hsvToRGBconversion( int 0 .. 100 ) 
 * Description: Converts an HSV percentage value ( integer between 0 .. 100 ) 
 *              into an RGB color.
 *              the HSV transition cycles from green over yellow to red. 
 *              (no purple or blue colors are used ) 
 *
 */ 

uint32_t ArtProject::hsvToRGBconversion(byte percent ) { 
   uint8_t r, g, b;  

   if (percent < 50) {
        // green to yellow
        r = (uint8_t)(255 * (percent / 50.0)); 
        g = 255;

    } else {
        // yellow to red
        r = 255;
        g = (uint8_t)(255 * ((50 - percent % 50) / 50.0));
    }
    b = 0; 

    uint32_t rgbColorEquivalent = rgbColorConversion(r, g, b);
    return rgbColorEquivalent; 
}

/*
 * Function   : lightUp(r, g, b); 
 * Description: Lights the LED strip up in a specified RGB color, 
 *              one pixel after the other. 
 *
*/


void ArtProject::lightUp(uint8_t r, uint8_t g, uint8_t b){ 

  _strip.show(); // Initialize all pixels to 'off' 

  for (uint8_t i=0; i< _strip.numPixels(); i++) {
    _strip.setPixelColor(i, rgbColorConversion(r, g, b)) ;
    _strip.show(); 
    delay(50);
  }
}  


// Set the spectrum start 

void ArtProject::setSpectrumStart(uint8_t s) {  
   _spectrumStart = s;  
}  

// Set the spectrum end 

void ArtProject::setSpectrumEnd(uint8_t e) {  
   _spectrumEnd = e; 
} 



void ArtProject::setSpectrum(uint8_t s, uint8_t e) {  
   _spectrumStart = s;  
   _spectrumEnd = e;  
}  
