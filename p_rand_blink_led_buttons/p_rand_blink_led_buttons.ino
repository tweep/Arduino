#include <Bounce2.h>


// randomly blink four LEDs

// PWM LED connection pins
int ledPin1 = 13;
int ledPin2 = 12;


// digital Switch Pins
int switchPin1 = 52;
int switchPin2 = 50;

long randNumber;
Bounce  bouncer  = Bounce(); 

void setup() {
  pinMode(ledPin1, OUTPUT); // 52
  pinMode(ledPin2, OUTPUT); // 50
  pinMode(switchPin1, INPUT); 
  pinMode(switchPin2, INPUT); 
  
  randomSeed(analogRead(0));
  Serial.begin(9600);

  // attach the bouncer fuction to the our switch
  bouncer .attach( switchPin1 );
  bouncer .interval(5);
  bouncer .attach( switchPin2 );
  bouncer .interval(5);
}

void loop() {
  randNumber = random(1, 3);
  
  blinkLed(randNumber,1000); 

  
  // check if right button is pressed 
  checkButton(randNumber); 
  
  turnLightsOff();
}


void checkButton(int activeLed) { 

  while(Serial.available() == 0) { }   
  char x = Serial.read();

  Serial.println(x);


  if (digitalRead(switchPin1)==HIGH && activeLed == 1){
      Serial.println("Button Pressed");
  }

  if (digitalRead(switchPin1)==HIGH && activeLed == 2){
      Serial.println("Button Pressed");
  }

  
}

/* 
 *  Randomly blink an an LED 
*/

void blinkLed(int activeLed, int wait){

  if (activeLed == 1 ) {
    digitalWrite(ledPin1, HIGH);

  } else if ( activeLed == 2 ) {
    digitalWrite(ledPin2, HIGH);

  }
  delay(wait);
  Serial.print("Active LED:");
  Serial.println(activeLed);

}

void turnLightsOff () {
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  Serial.println("LEDS OFF");

  delay(1000);
}

