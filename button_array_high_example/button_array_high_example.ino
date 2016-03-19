
byte button[] = {52,50,48,46}; 

void setup() {
  Serial.begin(9600); 

  for (int i=0; i < sizeof(button); i++ ) { 
    pinMode(button[i], INPUT); 
    digitalWrite(button[i], HIGH);
  }
}

void loop() {
  
  delay(50); 
  for (int i=0; i < sizeof(button); i++ ) { 
    
    if ( digitalRead(button[i])== LOW) { 
        Serial.print("Pressed Button : "); 
        Serial.println(i); 
        delay(15);
    }
  }
}
