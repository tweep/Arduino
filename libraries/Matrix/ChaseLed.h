#ifndef ChaseLed_h
#define ChaseLed_h


// enable basic commands: pinMode, digitalWrite, delay,..
#include "Arduino.h" 


class ChaseLed { 
   public: 
     ChaseLed(byte pin[]); 
     ~ChaseLed(); 
     void on(byte led); 
     void off(byte led); 
    private:        
     byte _pins[]; 
}; 

#endif

