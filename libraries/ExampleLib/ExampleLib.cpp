/* ExampleLib.cpp - a simple test library
   
*/ 


#include "Arduino.h"
#include "ExampleLib.h"       // include the header file declartion


// constructor 

ExampleLib::ExampleLib(byte pin){ 
    pinMode(pin , OUTPUT);  
    _pin = pin; 
}  

// destructor 
ExampleLib::~ExampleLib(){ /* nothing to destruct */ }  

void ExampleLib::on() { 
   digitalWrite(_pin, HIGH); 
}  

void ExampleLib::off() { 
   digitalWrite(_pin, LOW); 
}  


void ExampleLib::blink(int time) {  
    on(); 
    delay(time/2); 
    off(); 
    delay(time/2); 
}  


