
#include "ArtProject.h"
#include "TimedAction.h"

#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

ArtProject a1 = ArtProject(60,4); 

ArtProject a2 = ArtProject(60,PIN5); 
ArtProject a3 = ArtProject(60,PIN6); 
ArtProject a4 = ArtProject(60,PIN7);

/*
TimedAction stripActionOne = TimedAction(10,&one);
TimedAction stripActionTwo = TimedAction(20,&two);
TimedAction stripActionThree = TimedAction(60,&three);
TimedAction stripActionFour = TimedAction(160,&four);
*/
void setup() {
  Serial.begin(9600);
  Serial.println("in setup()"); 
}

void loop() {
    Serial.println("loop()"); 

     a1.rainbow();
     a2.rainbowCycle();


}



