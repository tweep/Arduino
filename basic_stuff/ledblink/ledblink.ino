
int ledPinOne = 13;

void setup() {
  pinMode(ledPinOne, OUTPUT); 
  Serial.begin(9600); 

}

void loop() {
     Serial.println(HIGH);

  digitalWrite(ledPinOne, HIGH); 
  delay(500);
  digitalWrite(ledPinOne, LOW); 
  Serial.println(LOW);


}
