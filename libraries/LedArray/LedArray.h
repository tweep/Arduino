#ifndef LedArray_h
#define LedArray_h


// enable basic commands: pinMode, digitalWrite, delay,..
#include "Arduino.h" 
#include "SimpleLed.h" 
#include "QueueArray.h"

class LedArray { 
   public: 
     LedArray();
     ~LedArray(); 
     void addCenterLED(SimpleLed led); 
     void addMiddleLED(SimpleLed led); 
     void addOuterLED(SimpleLed led); 
     //void on(); 
     //void off(); 
    private:        
     SimpleLed _led[];  
     QueueArray <SimpleLed> _ledstack; 
}; 

#endif

