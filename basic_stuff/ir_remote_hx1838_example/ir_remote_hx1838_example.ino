
/* Example on using an HX 1838 IR remote 
 *  receiver
 *  HX1838 VS1838 NEC Infrared IR Wireless Remote Control Sensor Module For Arduino
 *  
 *  Amazon 7.00 $ 
 *  https://www.amazon.com/gp/product/B019I4MYSE 
 */

#include <IRremote.h>
#include <IRremoteInt.h>

uint8_t RECV_PIN = 7;

IRrecv irrecv(RECV_PIN);
decode_results results;



void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  // put your main code here, to run repeatedly
  
    if (irrecv.decode(&results)) {
      Serial.println(results.value, HEX);
      irrecv.resume(); // Receive the next value
    }
}

