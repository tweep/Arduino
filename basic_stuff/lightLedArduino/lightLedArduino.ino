/*
 *  first program to blink an LED on the  
 * 
 */

int ledPin = 13; 
 
 void setup() {
  // tell arduino how to use pins.
  // define digital pins in- our outputs for our arduino  ( all pins can be used as in- or output ) 
  pinMode(ledPin, OUTPUT); 

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH); 
  delay(300);
  digitalWrite(ledPin, LOW); 
  delay(300);
}
