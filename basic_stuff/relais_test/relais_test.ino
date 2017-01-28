
//relais test 
int relaisPin = 50; 
int delaysec  = 15; 

void setup() {
  // put your setup code here, to run once:
  pinMode(relaisPin, OUTPUT); 
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(delaysec); 
  Serial.println("High"); 
  digitalWrite(relaisPin, HIGH); 
  delay(delaysec); 
    Serial.println("low"); 

  digitalWrite(relaisPin, LOW);   
}
