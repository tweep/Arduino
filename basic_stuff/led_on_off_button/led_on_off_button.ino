/*
    Sketch to monentarily light an LED when a button is pressed.
    https://www.youtube.com/watch?v=_LCCGFSMOr4
    10k pull down resistor to reduce voltage to 0 ( as we work digitally )
    The code below allows you to monitor if a switch has been pressed or not.
*/

int switchPinOne = 40;
int ledPin = 11;

boolean lastButton = LOW;
int     ledActive = 0;
boolean currentButton = LOW; 


void setup() {
  // put your setup code here, to run once:
  pinMode(switchPinOne, INPUT);   // to read input
  pinMode(ledPin, OUTPUT);     // to set signal (led) to out
}

void loop() {
  currentButton = debounce(lastButton); 
   
  if (lastButton == LOW && currentButton == HIGH)
  {
    ledActive = ledActive+30;
  } 
  lastButton = currentButton;
  if ( ledActive > 255 ) ledActive =0; 
  
  analogWrite(ledPin, ledActive);
}

boolean debounce (boolean last) {
  
   boolean current = digitalRead(switchPinOne); 
   if ( last != current ) { 
      delay(5); 
      current = digitalRead(switchPinOne); 
   }
   return current; 
}


