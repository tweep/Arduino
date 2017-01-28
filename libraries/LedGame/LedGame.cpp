/* 
   LedGame.cpp 
*/ 


#include "Arduino.h"
#include "LedGame.h"    
#include "SimpleLed.h"  
#include "GameLevel.h"  

/* 
*  Constructor : 
*   - gets 2 arrays 
*   - setups up Leds and buttons 
*   - returns object ledGame  
*/ 

LedGame::LedGame(){ 
  GameLevel _level; 
}  

LedGame::LedGame(SimpleLed led[], int arraysize){ 

// read : http://arduino.stackexchange.com/questions/1433/arduino-sizeof-servo-array-objects-is-wrong
// i have  to hand over the size of the array immediately.

  // the problem is that i can't handover the array with my 12 leds to the LEdGAme ... 
  // i can somehow only hand over 2 ...
  Serial.println("LedGame::LedGame : constructor()"); 
  Serial.println(sizeof(SimpleLed)); 
  Serial.println(sizeof(led)); 

  //my problem has something to with the sizeof. 

  //int arraysize = (sizeof(led)/sizeof(SimpleLed));

  for(int x=0; x< arraysize ; x++)  {
  
  //for(int x=0; x<12; x++) { i works if i iterate over the 12 eelements - but i can't get the size / length of the array
  


   _led[x] = led[x];
   
    Serial.println("LedGame::LedGame : setup-led()"); 
    Serial.println(x);
    
    //TEST SCHLEIFE
    for(int cc=0; cc<100; cc++){
      _led[x].on();
      delay(10);
      _led[x].off();
      delay(10);
    }

  } 
      Serial.println(sizeof(_led)); 

}  



// destructor 
LedGame::~LedGame(){ /* nothing to destruct */ }  




void LedGame::playGame(){ 
 _level.init();  // set level to 0 

 // 1st level : light a single LED ( from inner circle leds ) , turn it off after 3 seconds       - or if user presses the correct key  
 // 2nd level : light 1-2 LED (from inner circle leds ) , turn it off after 2-3 seconds          - or if user presses the correct key  
 // 3nd level : light 1-2 LED (from inner + middle circle )  turn it off after 1.5 - 2.5 seconds    - or if user presses the correct key  
 // 3nd level : light 1-3 LED (from inner + middle circle )  turn it off after 1.5 - 2.5 seconds    - or if user presses the correct key  
 // 3nd level : light 1-2 LED (from inner + middle + outer circle )  turn it off after 1.5 - 2.5 seconds    - or if user presses the correct key  

  playLevel(); 

 
 _level.nextLevel();
}   


void LedGame::playLevel(void) {  

  byte l = _level.getLevel();  
  int num = random(0, 5);
  _led[num]; 
  // random(0, nr_leds[l]); 

} 

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



void  setupBinaryMap(byte leds)
{ 
  for ( int i = 0 ; i < sizeof(_ledpin); i++ ) {  
     binaryMap[i] = ( 0 << i ) ; 
  } 
} 


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


