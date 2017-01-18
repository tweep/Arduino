/* 
   Circus.cpp 
*/ 


#include "Arduino.h"
#include "Circus.h"
#include "SimpleLed.h"

#define CHOICE_NONE  -1

Circus::Circus(){ 
}  

Circus::Circus(SimpleLed led[]){ 
  Serial.println("Circus::Circus :Initialization with SimpleLed Array"); 

  for(int x=0; x<sizeof(led); x++)
  {
    Serial.println("Circus::Circus: Setup led"); 

    _led[x] = led[x]; 
  } 
}  



Circus::~Circus(){ /* nothing to destruct */ }   


// Show an "attract mode" display while waiting for user to press button.
byte Circus::attractMode(void)
{
  Serial.println("Circus::attractMode()"); 

  while(1)
  {  
     Serial.println("Circus-while"); 

    for ( byte i = 0; i < sizeof(_led);  i++) { 
      _led[i].on(); 
      delay(100); 
      _led[i].off(); 
      byte button = checkButton();
        Serial.println("Circus"); 

      if (button != CHOICE_NONE) return button;  // leave while() if button is pressed and return value of pressed button 
    } 
  }
          Serial.println("oopsy"); 

}

byte Circus::checkButton(void)
{ 
  for (byte i=0; i<sizeof(_button); i++ )
  { 
     if (_button[i].active() == 0 ) return i; 
  }
  return CHOICE_NONE;  
}

void Circus::kickOff(void)
{  
  // show some lights to start the game.  
  allLightsOn(); 
  delay(250); 
  allLightsOff();       
}


void Circus::allLightsOn(void) {  
   for ( byte i = 0; i < sizeof(_led);  i++) {  
      _led[i].on(); 
   }  
}  

void Circus::allLightsOff(void) {  
   for ( byte i = 0; i < sizeof(_led);  i++) {  
      _led[i].off(); 
   }  
} 
