#ifndef ExampleLib_h
#define ExampleLib_h


// enable basic commands: pinMode, digitalWrite, delay,..
#include "Arduino.h" 


class ExampleLib { 
   public: 
     ExampleLib(byte pin); 
     ~ExampleLib(); 
    void on(); 
    void off(); 
    void blink(int time);     
    private:        
     byte _pin; 
}; 

#endif

