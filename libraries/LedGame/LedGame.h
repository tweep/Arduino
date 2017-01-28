#ifndef LedGame_h
#define LedGame_h


// enable basic commands: pinMode, digitalWrite, delay,..
#include "Arduino.h" 
#include "SimpleLed.h"
//#include "SimpleButton.h"
#include "GameLevel.h"

class LedGame{ 
   public: 
     LedGame();
     LedGame(SimpleLed led[], int size); 
     ~LedGame();  
     void playGame();
    private:        
     SimpleLed _led[]; 
     byte _buttonpin[]; 
     byte _pooferpin[]; 
     byte _binaryMap[];  
     GameLevel _level;  
     void playLevel(); 
}; 

#endif

