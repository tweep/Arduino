/* 
    SimpleButton.cpp - a simple library for LED objects
*/ 


#include "Arduino.h"
#include "SimpleButton.h"       // include the header file declartion


// constructor - returns object SimpleButton
SimpleButton::SimpleButton(){   
}  

SimpleButton::SimpleButton(byte pin){   
    pinMode(_pin, INPUT_PULLUP);
}  

// destructor 
SimpleButton::~SimpleButton(){ /* nothing to destruct */ }  

byte SimpleButton::active() {  
   if (digitalRead(_pin) == 0) return 1;  
}  





