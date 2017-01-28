
byte relais[] = {24,26,28,30}; // pins for the LED (poofer later). do not use INT as size.

void setup() {
 
  Serial.begin(9600);
  for (int i=0; i < sizeof(relais); i++ ) { 
    pinMode(relais[i], OUTPUT); 
    digitalWrite(relais[i], HIGH);
  }

}

void loop() {
  for (int i=0; i < sizeof(relais); i++ ) { 
    delay(1000);
    Serial.print("Array "); 
    Serial.print(i);
    Serial.println("LOW"); 
    digitalWrite(relais[i], LOW);
    
    delay(1000);
     Serial.print("Array "); 
    Serial.print(i); 
    Serial.println("HIGH"); 
    digitalWrite(relais[i], HIGH);
 

  }

}
