/* hashDecode.ino Example sketch for IRLib2
 * Instead of decoding using a standard encoding scheme
 * (e.g. Sony, NEC, RC5), the code is hashed to a 32-bit value.
 * This should produce a unique 32-bit number however that number 
 * cannot be used to retransmit the same code. This is just a quick 
 * and dirty way to detect a unique code for controlling a device 
 * when you don't really care what protocol or values are being sent.
 */
//First will create a decoder that handles only NEC, Sony and the hash
// decoder. If it is not NEC or Sony that it will return a 32 bit hash.


#define MY_PIN 2 


#include <IRLibRecvLoop.h>
IRrecvLoop myReceiver(MY_PIN); // create IRrecvLoop on pin 2


//#include <IRLibRecvPCI.h>
//IRrecvPCI myReceiver(MY_PIN);    //create a IRrecv on pin number 2

//#include <IRLibRecv.h> 
//IRrecv myReceiver(MY_PIN);    //create a IRrecv on pin number 2

#include <IRLibDecodeBase.h> 
#include <IRLib_HashRaw.h> 
#include <IRLibCombo.h>     
IRdecode myDecoder;



#include "FastLED.h"
FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif



#define DATA_PIN    7
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    64
#define FRAMES_PER_SECOND  120 

CRGB leds[NUM_LEDS];

byte BRIGHTNESS = 96; 
uint16_t myBuffer[RECV_BUF_LENGTH]; // auto resume 

//IRrecvLoop myReceiver(MY_PIN); // create IRrecvLoop on pin 2
//IRrecv myReceiver(MY_PIN);    //create a IRrecv on pin number 2

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo

   if(digitalPinToInterrupt(MY_PIN)==NOT_AN_INTERRUPT) {
     Serial.println(F("Invalid frequency pin number."));
     while (1) {};//infinite loop because of fatal error 
   }
  
  //Enable auto resume and pass it the address of your extra buffer 
  myReceiver.enableAutoResume(myBuffer); // must call BEFORE enableIRIn()
  myReceiver.enableIRIn(); // Start the receiver
  
  Serial.println(F("Ready to receive IR signals"));
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}



void loop() {
  if(myReceiver.getResults()) {

    myDecoder.decode();
    //myDecoder.dumpResults(true);
    
    if(myDecoder.protocolNum==UNKNOWN) {
      Serial.print(F("Unknown protocol. Hash value is: 0x"));
      Serial.println(myDecoder.value,HEX);
    } else {
      myDecoder.dumpResults(false);
    };
    myReceiver.enableIRIn(); 
  }
 
  fill_rainbow( leds, NUM_LEDS, 0, 7);
 // myReceiver.disableIRIn();
  FastLED.delay(50); 
 // myReceiver.enableIRIn();  
}






