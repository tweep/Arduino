/* 
    ChaseLed.cpp - a simple test library
*/ 


#include "Arduino.h"
#include "ChaseLed.h"       // include the header file declartion


// constructor - returns object ChaseLed 

ChaseLed::ChaseLed(byte pin[]){   

  for(int x=0; x<sizeof(pin); x++)
  {
    pinMode(pin[x], OUTPUT);
    _pins[x] = pin[x]; 
  }
}  



// destructor 
ChaseLed::~ChaseLed(){ /* nothing to destruct */ }  



/* Method      : setLEDs()
   Description: Lights a given LEDs
                Pass in a byte that is made up from CHOICE_RED, CHOICE_YELLOW, etc
   Example    : setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW);

*/ 

//led 1    (0 << 1 )    0001 
//led 2    (0 << 2 )    0010
//led 3    (0 << 3 )    0100

/*
setLEDS( led1 | led ) 

// setLEDS (0011 ) 

// 0011 & 0001  => ysô

void setLEDs(byte leds)
{
  if ((leds & CHOICE_RED) != 0)  // bitwise and operator 
    digitalWrite(LED_RED, HIGH);
  else
    digitalWrite(LED_RED, LOW);

  if ((leds & CHOICE_GREEN) != 0)
    digitalWrite(LED_GREEN, HIGH);
  else
    digitalWrite(LED_GREEN, LOW);

  if ((leds & CHOICE_BLUE) != 0)
    digitalWrite(LED_BLUE, HIGH);
  else
    digitalWrite(LED_BLUE, LOW);

  if ((leds & CHOICE_YELLOW) != 0)
    digitalWrite(LED_YELLOW, HIGH);
  else
    digitalWrite(LED_YELLOW, LOW);
}

*/



void ChaseLed::on(byte led) { 
   digitalWrite(_pins[led], HIGH); 
}  

void ChaseLed::off(byte led) { 
   digitalWrite(_pins[led], LOW); 
}  




