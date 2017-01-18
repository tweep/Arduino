/* 
    SimpleLed.cpp - a simple library for LED objects
*/ 


#include "Arduino.h"
#include "SimpleLed.h"       // include the header file declartion


// constructor - returns object SimpleLed
SimpleLed::SimpleLed(){   
}  

SimpleLed::SimpleLed(byte pin){   
    pinMode(pin, OUTPUT);
    _pin = pin;
}  

// destructor 
SimpleLed::~SimpleLed(){ /* nothing to destruct */ }  

void SimpleLed::on() { 
   Serial.println("SimpleLed::on()"); 
   digitalWrite(_pin, HIGH); 
}  

void SimpleLed::off() { 
   digitalWrite(_pin, LOW); 
   Serial.println("SimpleLed::off()"); 

}  




