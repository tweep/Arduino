#ifndef Circus_h
#define Circus_h

#include "Arduino.h" 
#include "SimpleLed.h"
#include "SimpleButton.h"

class Circus{ 
   public: 
     Circus();
     Circus(SimpleLed led[]); 
     ~Circus();  
     void kickOff();
     void allLightsOn();
     void allLightsOff();
     byte attractMode();
     byte checkButton();
    private:        
     SimpleLed _led[]; 
     SimpleButton _button[]; 
     byte _pooferpin[]; 
}; 

#endif

