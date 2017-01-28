/* 
    LedArray.cpp - a simple library for LED objects
*/ 


#include "Arduino.h"
#include "SimpleLed.h"       // include the header file declartion
#include "LedArray.h"       // include the header file declartion
#include "QueueArray.h"
//#include "QueueArray.h"

LedArray::LedArray(){   
}  


void LedArray::addCenterLED(SimpleLed led){    
    _ledstack.push(led); 
}

void LedArray::addMiddleLED(SimpleLed led){    
    _ledstack.push(led); 
} 

void LedArray::addOuterLED(SimpleLed led){    
    _ledstack.push(led); 
}


LedArray::~LedArray(){ /* destructor */ }  





