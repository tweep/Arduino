
int ledPin = 13; 
int switchPin = 50;

void setup() {
  // put your setup code here, to run once:
 pinMode(ledPin, OUTPUT); 
 pinMode(switchPin, INPUT); 
 Serial.begin(9600); 
 
}

void loop() {
 
 if ( digitalRead(switchPin) == HIGH ) { 
   Serial.println(digitalRead(switchPin)); 
   digitalWrite(ledPin, HIGH); 
 }
 else { 
  digitalWrite(ledPin,LOW);
 }
}
