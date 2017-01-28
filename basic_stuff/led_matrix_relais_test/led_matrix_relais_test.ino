
int pin[] = {52, 50, 48, 46, 44, 42, 40, 38, 36}; 
int ledState=LOW;

unsigned long previousMillis = 0;        // will store last time LED was updated
//const long interval = 50;           // interval at which to blink (milliseconds)


long randNumber;
void setup() {
  // put your setup code here, to run once:

  for (int i : pin ) { 
    pinMode(i, OUTPUT);
    digitalWrite(i,HIGH);
  }
  Serial.begin(9600); 
  randomSeed(analogRead(0)); 
}

void loop() {
  long interval = random(40, 8000);
  long time = millis(); 
  randNumber = random(0, 9); 
  int randPin = pin[randNumber];
//  Serial.println(randPin);

  unsigned long currentMillis = millis();

   if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
      digitalWrite(randPin,ledState); 

   }

}
