
/* Example on using an HX 1838 IR remote 
 *  receiver
 *  HX1838 VS1838 NEC Infrared IR Wireless Remote Control Sensor Module For Arduino
 *  
 *  Amazon 7.00 $ 
 *  https://www.amazon.com/gp/product/B019I4MYSE 
 */

#include <IRremote.h>
#include <IRremoteInt.h>

uint8_t RECV_PIN = 8;

IRrecv irrecv(RECV_PIN);
decode_results results;



void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
    
    if (irrecv.decode(&results)) {
      configure_stuff(results.value); 
      irrecv.resume(); // Receive the next value
    }
    
    delay(100);
}


void configure_stuff (int tmp) {
      
       switch (tmp) {
         case 0xE0E020DF :
           Serial.println("dark");
           break;
           
         case 0xE0E0A05F :
           Serial.println("dim");
           break;
       }

}

