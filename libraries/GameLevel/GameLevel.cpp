
#include "Arduino.h"
#include "GameLevel.h"       // include the header file declartion


// constructor - returns object GameLevel
GameLevel::GameLevel(){   
}  


// initialize GameLevel with SimpleLed array and poofer array 
//GameLevel::GameLevel(byte pin){   
//    pinMode(pin, OUTPUT); 
//}  

GameLevel::~GameLevel(){ /* nothing to destruct */ }  

void GameLevel::nextLevel() { 
   _level++;  

   switch (_level) { 
    case 1: 
      // do sth - little poof and melody 
      break; 
    case 2: 
      // do sth - bigger poof and melody 
      break; 
    case 3: 
      // do sth - bigger poof and melody 
      break; 
    default:  
      // if noothing else matches do the default 
      break ;  
  }  
} 


void GameLevel::init() { 
   _level = 0;
}  

byte GameLevel::getLevel() { 
   return _level; 
}  



