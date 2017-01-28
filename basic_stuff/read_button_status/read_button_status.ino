// button test 

int buttonPin = 2; 

void setup() {
  // put your setup code here, to run once:

    pinMode(buttonPin, INPUT); 
    Serial.begin(9600); 

}

void loop() {

   if ( digitalRead(buttonPin) == HIGH ) { 
     Serial.println("high"); 
   }else { 
       Serial.println("low"); 

   }
  delay(50);

}
