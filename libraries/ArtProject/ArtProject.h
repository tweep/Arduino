#ifndef ArtProject_h
#define ArtProject_h


// enable basic commands: pinMode, digitalWrite, delay,..
#include "Arduino.h" 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

class ArtProject {  

   // Class member variables - initialization  
   public: 
   ArtProject(uint8_t nrLeds, uint8_t pin) ; 
   ArtProject(uint8_t nrLeds, uint8_t pin, uint8_t brightness) ; 
   ArtProject(uint8_t nrLeds, uint8_t pin, uint8_t brightness, uint8_t startColor, uint8_t spectrumWidth  ); 

   ~ArtProject();  

   void   
     percentToRGB(),
     rainbow(), 
     rainbowCycle(),
     rgbBand(),
     //colorWipe(uint32_t color),
     lightUp(uint8_t r, uint8_t g, uint8_t b); 
   //static uint32_t 
    // Color(uint8_t r, uint8_t g, uint8_t b);


   private:       
     uint32_t Wheel(byte WheelPos) ;
     Adafruit_NeoPixel _strip; 
     uint8_t 
       _colorIndex,
       _colorNumber,
       _percent,
       _spectrumStart,
       _spectrumEnd,
       _var;
};  

#endif

