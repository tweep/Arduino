#ifndef GameLevel_h
#define GameLevel_h


// enable basic commands: pinMode, digitalWrite, delay,..
#include "Arduino.h" 


class GameLevel { 
   public: 
     GameLevel();
     //GameLevel(byte pin);
     ~GameLevel(); 
     void init(); 
     byte getLevel(); 
     void nextLevel(); 
    private:        
     byte _level ; 
}; 

#endif

