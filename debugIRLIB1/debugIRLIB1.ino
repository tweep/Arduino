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

#include <IRLib.h>

IRrecv My_Receiver(MY_PIN);

IRdecode My_Decoder;
IRdecodeHash My_Hash_Decoder;

unsigned int Buffer[RAWBUF];


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

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo

  My_Receiver.enableIRIn(); // Start the receiver
  My_Decoder.UseExtnBuf(Buffer);
  
  Serial.println(F("Ready to receive IR signals"));
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

// does not work ! 

void loop() {
  if (My_Receiver.GetResults(&My_Decoder)) {
    My_Hash_Decoder.copyBuf(&My_Decoder);//copy the results to the hash decoder
    My_Decoder.decode();
    Serial.print("real decode type:");
    Serial.print(Pnames(My_Decoder.decode_type));
    Serial.print(" value: 0x");
    Serial.print(My_Decoder.value, HEX);
    My_Hash_Decoder.decode();
    Serial.print(", hash decode: 0x");
    Serial.println(My_Hash_Decoder.hash, HEX); // Do something interesting with this value
    My_Receiver.resume(); 
  }
 
  fill_rainbow( leds, NUM_LEDS, 0, 7);
 // myReceiver.disableIRIn();
 FastLED.delay(50); 
 // myReceiver.enableIRIn();  
}






