/* 
    ArtProject.cpp - a simple library for LED objects
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
    _pin = pin; 
    _nrLeds = nrLeds; 
    _strip.begin();
    //_strip.setBrightness(255);
    _strip.setBrightness(128);
    _strip.show(); // Initialize all pixels to 'off'
}  

// destructor 
ArtProject::~ArtProject(){ /* nothing to destruct */ }  

void ArtProject::rainbow() {  

  for(int pixelNr=0; pixelNr< _strip.numPixels(); pixelNr++) {
    _strip.setPixelColor(pixelNr, Wheel(((pixelNr * 256 / _strip.numPixels()) + _counter) & 255) );
  }
  _strip.show();
  _counter++;
  if (_counter > 256 ) {
    _counter=0;
  }
}

uint32_t rgbColorConversion(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
} 

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





