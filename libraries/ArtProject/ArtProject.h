#ifndef ArtProject_h
#define ArtProject_h


// enable basic commands: pinMode, digitalWrite, delay,..
#include "Arduino.h" 
#include "SpectrumBand.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

class ArtProject {  

   // Class member variables - initialization  
   public: 
   ArtProject(uint8_t nrLeds, uint8_t pin) ; 
   ArtProject(uint8_t nrLeds, uint8_t pin, uint8_t brightness) ; 
   ArtProject(uint8_t nrLeds, uint8_t pin, uint8_t brightness, uint8_t startColor, uint8_t endColor);  

   // Initialize with SpectrumBand data stucture  
   ArtProject(uint8_t nrLeds, uint8_t pin, uint8_t brightness, SpectrumBand specBand ); 

   ~ArtProject();  

   void   
     percentToRGB(),
     rainbow(), 
     rainbowCycle(),
     rgbBand(),
     lightUp(uint8_t r, uint8_t g, uint8_t b),
     setSpectrumStart(uint8_t start), 
     setSpectrumEnd(uint8_t end), 
     setSpectrum(uint8_t start,uint8_t end) ; 
     //colorWipe(uint32_t color),
   //static uint32_t 
    // Color(uint8_t r, uint8_t g, uint8_t b);


   private:       
     uint32_t colorWheel(byte WheelPos) ;
     Adafruit_NeoPixel _strip; 
     uint8_t 
       _colorNumber,                  // 8 bit color number; with values between 0 - 255 (depending on the transition it can also be 0-99) 
       _spectrumStart,                // Start of the color spectrum band 
       _spectrumEnd,                  // end of the color spectrum band 
       _var;
};  

#endif

