
#include <ArtProject.h>
#include <TimedAction.h>

#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

ArtProject a1 = ArtProject(60,PIN4); 
ArtProject a2 = ArtProject(60,PIN5); 
ArtProject a3 = ArtProject(60,PIN6); 
ArtProject a4 = ArtProject(60,PIN7);

TimedAction stripActionOne = TimedAction(10,&one);
TimedAction stripActionTwo = TimedAction(20,&two);
TimedAction stripActionThree = TimedAction(60,&three);
TimedAction stripActionFour = TimedAction(160,&four);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("in setup()"); 
 // a1.lightUp(255,0,0);
 // a2.lightUp(255,0,0); 
//  a3.lightUp(255,0,0);
 // a4.lightUp(255,0,0);
  Serial.println("setup done()"); 
}

void loop() {
   stripActionOne.check();
   stripActionTwo.check();
   stripActionThree.check();
   stripActionFour.check();
}


void one() { 
  a1.rainbow(); 
}

void two() {
 a2.rainbow();
}

void three() { 
 a3.rainbow();
} 

void four() { 
 a4.rainbow();
} 



