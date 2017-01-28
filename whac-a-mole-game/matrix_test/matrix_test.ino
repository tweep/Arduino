
#define NR_LEDS 4

int choice[100]; 
int ontime[100];
byte led_status[100];

void setup() {
   Serial.begin(9600); 
   
   for (byte i=0; i < NR_LEDS; i++ ) { 
    choice[i] = ( 1 << i );
    Serial.print("Setup LED "); 
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(choice[i],BIN); 
   }
}

void loop() {
   run_matrix();
}

void run_matrix(void) { 
    randomSeed(millis());

   // randomly turn on 1,2, 3 or 4 leds.  
   byte leds_to_turn_on  = random(1, NR_LEDS+1); // minimum is 1 LED to be turned on.
  

   byte led_bytes;
   for (byte y = 0; y < leds_to_turn_on; y++) { 
     byte pick_random_led = random(0, NR_LEDS);    
     led_bytes = (led_bytes | choice[pick_random_led]); 
   }

   setLEDs(led_bytes); 

}


/* function below just turns LEDs on, again and again. 
 *  If LED is on for X, we should turn it off. 
 *  How to track the amount of time the LED is on ? 
 */
void setLEDs(byte leds)
{

  for (byte x = 0; x < NR_LEDS; x++) { 
        Serial.print("LED-"); 
        Serial.print(x); 
        
   if ((leds & choice[x]) != 0) {

         if (led_status[x] == 1 ) { 
          // led was on before
          int uptime_ms =  (ontime[x] - millis());
          Serial.println(uptime_ms);
            if (uptime_ms > 3000 ) { 
              // led has been on over 3000 ms - turn it off
              led_status[x]=0;
            }
          
         }else {
            // led was turned off before - initialize counter 
             ontime[x]=millis();
             led_status[x] = 1;
         }
         
         if (led_status[x] == 1 ) {
            // turn LED on
            Serial.println(" ON");
         }else {
            Serial.println(" OFF - too long"); 
         }
         
    }else {
        Serial.println(" OFF"); 
    }
  }
  
   Serial.println(" "); 
   delay(5000);
}


