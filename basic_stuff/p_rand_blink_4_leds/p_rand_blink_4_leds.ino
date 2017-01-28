// randomly blink four LEDs

// define the connection Pins for PWM out
int ledPin1 = 13;
int ledPin2 = 12;
int ledPin3 = 11;
int ledPin4 = 10;

long randNumber;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  randomSeed(analogRead(0));
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  blinkLed(); 
  delay(200);
  turnLightsOff();
}

void blinkLed(){
  randNumber = random(1, 5);

  if (randNumber == 1 ) {
    digitalWrite(ledPin1, HIGH);

  } else if ( randNumber == 2 ) {
    digitalWrite(ledPin2, HIGH);

  } else if ( randNumber == 3 ) {
    digitalWrite(ledPin3, HIGH);

  } else if ( randNumber == 4 ) {
    digitalWrite(ledPin4, HIGH);
  }
  Serial.println(randNumber);

}

void turnLightsOff () {
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
  delay(200);
}

