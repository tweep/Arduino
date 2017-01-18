#ifndef SimpleLed_h
#define SimpleLed_h


// enable basic commands: pinMode, digitalWrite, delay,..
#include "Arduino.h" 


class SimpleLed { 
   public: 
 SimpleLed();
 SimpleLed(byte pin);
 ~SimpleLed(); 
 void on(); 
 void off(); 
private:        
 byte _pin; 
}; 

#endif

