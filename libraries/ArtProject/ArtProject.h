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
   ArtProject(Adafruit_NeoPixel strip) ;
   ArtProject(int nrLeds, int pin) ; 
   ~ArtProject();  
   byte active();  

   void  
     rainbow(), 
     //colorWipe(uint32_t color),
     lightUp(uint8_t r, uint8_t g, uint8_t b); 
   //static uint32_t 
    // Color(uint8_t r, uint8_t g, uint8_t b);


   private:       
     uint32_t Wheel(byte WheelPos) ;
     Adafruit_NeoPixel _strip; 
     int 
       _nrLeds,  
       _pin, 
       _counter;
};  

#endif

