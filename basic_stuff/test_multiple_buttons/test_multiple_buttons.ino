
int a = 53; 
int b = 51; 
int c = 49; 
int d = 47; 
int e = 45; 
int f = 43; 
int g = 41; 
int h = 39; 
int j = 37; 
int k = 35; 
int l = 33; 

void setup() {
  // put your setup code here, to run once:
  pinMode(a, INPUT_PULLUP);  
  pinMode(b, INPUT_PULLUP);  
  pinMode(c, INPUT_PULLUP);  
  pinMode(d, INPUT_PULLUP);  
  pinMode(e, INPUT_PULLUP);  
  pinMode(f, INPUT_PULLUP);  
  pinMode(g, INPUT_PULLUP);  
  pinMode(h, INPUT_PULLUP);  
  pinMode(j, INPUT_PULLUP);  
  pinMode(k, INPUT_PULLUP);  
  pinMode(l, INPUT_PULLUP);  
  Serial.begin(9600);

}

void loop() {

  if (digitalRead(a) == LOW) {
     Serial.println("SWITCH A");
  }
   if (digitalRead(b) == LOW) {
     Serial.println("SWITCH B");
  }
   if (digitalRead(c) == LOW) {
     Serial.println("SWITCH C");
  }
   if (digitalRead(d) == LOW) {
     Serial.println("SWITCH D");
  }
   if (digitalRead(e) == LOW) {
     Serial.println("SWITCH E");
  }
   if (digitalRead(f) == LOW) {
     Serial.println("SWITCH F");
  }
   if (digitalRead(g) == LOW) {
     Serial.println("SWITCH G");
  }
   if (digitalRead(h) == LOW) {
     Serial.println("SWITCH H");
  }
   if (digitalRead(j) == LOW) {
     Serial.println("SWITCH J");
  }
   if (digitalRead(k) == LOW) {
     Serial.println("SWITCH K");
  }
   if (digitalRead(l) == LOW) {
     Serial.println("SWITCH L");
  }
}








