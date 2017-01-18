#ifndef SimpleButton_h
#define SimpleButton_h


// enable basic commands: pinMode, digitalWrite, delay,..
#include "Arduino.h" 


class SimpleButton { 
   public: 
     SimpleButton();
     SimpleButton(byte pin);
     ~SimpleButton(); 
     byte active(); 
    private:        
     byte _pin; 
}; 

#endif

