#include <ChaseLed.h>

#define CHOICE_OFF      0 //Used to control LEDs
#define CHOICE_NONE     0 //Used to check buttons
#define CHOICE_RED      (1 << 0)  // 0001
#define CHOICE_GREEN    (1 << 1)  // 0010
#define CHOICE_BLUE     (1 << 2)  // 0100
#define CHOICE_YELLOW   (1 << 3)  // 1000 


//byte buttonPin[]={9,2,12,6};
//byte ledPin[]={10,3,13,5}; 

#define LED_RED     22
#define LED_GREEN   24
#define LED_BLUE    26
#define LED_YELLOW  28

// Button pin definitions
#define BUTTON_RED    46
#define BUTTON_GREEN  48
#define BUTTON_BLUE   50
#define BUTTON_YELLOW 52
#define NR_LEDS 4

#define BUZZER1  51
#define BUZZER2  53


#define MODE_MEMORY  0

byte gameMode = MODE_MEMORY; //By default, let's play the memory game
byte gameRound = 0; //Counts the number of succesful rounds the player has made it through

byte buttonsPerLevel [] = {2,4,6,8};
int entry_time_limit[] = { 3000, 2000, 1000, 500}; 


/* use library - define this outside of setup(). Access object with ch_inst.function() */ 
//#include <ChaseLed.h> 
//ChaseLed ch_inst(13);    // create new instance called ch_inst



// what happens if i call a function like testFunc( val) or testFunc(val | val2 ) ?  

void setup()
{  
  Serial.begin(9600); 
  //ChaseLed leds(ledPin); 

  pinMode(BUTTON_RED,   INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_BLUE,  INPUT_PULLUP);
  pinMode(BUTTON_YELLOW,INPUT_PULLUP);

  pinMode(LED_RED,   OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE,  OUTPUT);
  pinMode(LED_YELLOW,OUTPUT);

  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);

  //play_winner(); 
}

void loop()
{
 // testMode();     // test that LED and pins match
  Serial.println(CHOICE_RED,BIN);
  Serial.println(CHOICE_GREEN,BIN);
  Serial.println(CHOICE_BLUE,BIN);
  Serial.println(CHOICE_YELLOW,BIN);



  attractMode(); // Blink lights while waiting for user to press a button

  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW); // Turn all LEDs on
  delay(250);
  setLEDs(CHOICE_OFF); // Turn off LEDs
  delay(250);

  if (gameMode == MODE_MEMORY)
  {
    if (led_game() == true)
      play_winner(); // Player won
    else 
      play_loser(); // Player lost
  }
}


void announceLevel(byte level)
{
    if (level == 0 ) {
      return ; 
    }
    Serial.print("Level: "); 
    Serial.println(level, DEC); 

    delay(500);
    for (int i = 0; i < level ; i++) { 
            buzz_sound(100, 1000);
          delay(100);
    }
} 

boolean led_game(void)
{

  randomSeed(millis()); 
  gameRound = 0; 
  
  while (gameRound < sizeof(buttonsPerLevel))
  {  
      announceLevel(gameRound); 
      
      // loop until set number of correct buttons has been hit
      for (byte correctButtons = 0 ; correctButtons < buttonsPerLevel[gameRound] ; correctButtons++)
      { 
        // get random choice(=LED) and turn it on
        /*
        byte randButton = set_random_button();
        setLEDs(randButton);  
        byte choice = wait_for_button(entry_time_limit[gameRound]); 
        */

        // get user input || or timeout 
        byte choice = led_and_button_sim(entry_time_limit[gameRound], gameRound);

        //if ( (choice == 0) || (choice != randButton))  return false; // If the choice is incorect, player loses.
        if (choice == 0 )  return false;
        setLEDs(CHOICE_OFF); // Turn off LEDs

        delay(100); // Give the user a 100ms rest 
        
      }
      gameRound++;
  }
  return true; // We should never get here
}


boolean play_battle(void) {}



byte set_random_button(void)
{
  byte newButton = random(0, NR_LEDS); //min (included), max (exluded)

  // We have to convert this number, 0 to 3, to CHOICEs
  if(newButton == 0)      return CHOICE_RED;
  else if(newButton == 1) return CHOICE_GREEN;
  else if(newButton == 2) return CHOICE_BLUE;
  else if(newButton == 3) return CHOICE_YELLOW;

}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//The following functions control the hardware

// Lights a given LEDs
// Pass in a byte that is made up from CHOICE_RED, CHOICE_YELLOW, etc
void setLEDs(byte leds)
{
  if ((leds & CHOICE_RED) != 0)
    digitalWrite(LED_RED, HIGH);
  else
    digitalWrite(LED_RED, LOW);

  if ((leds & CHOICE_GREEN) != 0)
    digitalWrite(LED_GREEN, HIGH);
  else
    digitalWrite(LED_GREEN, LOW);

  if ((leds & CHOICE_BLUE) != 0)
    digitalWrite(LED_BLUE, HIGH);
  else
    digitalWrite(LED_BLUE, LOW);

  if ((leds & CHOICE_YELLOW) != 0)
    digitalWrite(LED_YELLOW, HIGH);
  else
    digitalWrite(LED_YELLOW, LOW);
}



byte led_and_button_sim(int entry_time_limit, byte gameRound)
{
  long startTime = millis(); 
  byte button =0;
  while ( (millis() - startTime) < entry_time_limit) // Loop until too much time has passed
  {
    long delta = millis() - startTime;
    
    if ((delta % 1000) == 0 ){
      Serial.print("Delta: ");
      Serial.println(delta);
      byte randButton = set_random_button();
       Serial.print("RandButton: ");
      Serial.println(randButton, BIN); 

      button = ( randButton | button ); 
      Serial.print("Button: ");
      Serial.println(button, BIN); 
      setLEDs(button);  
      delay(50);
    }
    byte button = checkButton();

    if (button != CHOICE_NONE) // if user pressed button
    { 
      toner(button, 150); // Play the button the user just pressed
      while(checkButton() != CHOICE_NONE) ;  // Now let's wait for user to release button
      delay(10); // This helps with debouncing and accidental double taps
      return button;
    }
  }
  return CHOICE_NONE; // time-out 
}


// Wait for a button to be pressed. 
// Returns one of LED colors (LED_RED, etc.) if successful, 0 if timed out

byte wait_for_button(int entry_time_limit)
{
  long startTime = millis(); // Remember the time we started the this loop

  while ( (millis() - startTime) < entry_time_limit) // Loop until too much time has passed
  {
    byte button = checkButton();

    if (button != CHOICE_NONE)
    { 
      toner(button, 150); // Play the button the user just pressed

      while(checkButton() != CHOICE_NONE) ;  // Now let's wait for user to release button

      delay(10); // This helps with debouncing and accidental double taps

      return button;
    }
  }
  return CHOICE_NONE; // time-out 
}


// Returns a '1' bit in the position corresponding to CHOICE_RED, CHOICE_GREEN, etc.
byte checkButton(void)
{
  if (digitalRead(BUTTON_RED) == 0) return(CHOICE_RED); 
  else if (digitalRead(BUTTON_GREEN) == 0) return(CHOICE_GREEN); 
  else if (digitalRead(BUTTON_BLUE) == 0) return(CHOICE_BLUE); 
  else if (digitalRead(BUTTON_YELLOW) == 0) return(CHOICE_YELLOW);

  return(CHOICE_NONE); // If no button is pressed, return none
}

// Light an LED and play tone
// Red, upper left:     440Hz - 2.272ms - 1.136ms pulse
// Green, upper right:  880Hz - 1.136ms - 0.568ms pulse
// Blue, lower left:    587.33Hz - 1.702ms - 0.851ms pulse
// Yellow, lower right: 784Hz - 1.276ms - 0.638ms pulse
void toner(byte which, int buzz_length_ms)
{
  setLEDs(which); //Turn on a given LED

  //Play the sound associated with the given LED
  switch(which)
  {
  case CHOICE_RED:
    buzz_sound(buzz_length_ms, 1136);
    break;
  case CHOICE_GREEN:
    buzz_sound(buzz_length_ms, 568);
    break;
  case CHOICE_BLUE:
    buzz_sound(buzz_length_ms, 851);
    break;
  case CHOICE_YELLOW:
    buzz_sound(buzz_length_ms, 638);
    break;
  }
  setLEDs(CHOICE_OFF); // Turn off all LEDs
}


// Toggle buzzer every buzz_delay_us, for a duration of buzz_length_ms.
void buzz_sound(int buzz_length_ms, int buzz_delay_us)
{
  // Convert total play time from milliseconds to microseconds
  long buzz_length_us = buzz_length_ms * (long)1000;

  // Loop until the remaining play time is less than a single buzz_delay_us
  while (buzz_length_us > (buzz_delay_us * 2))
  {
    buzz_length_us -= buzz_delay_us * 2; //Decrease the remaining play time

    // Toggle the buzzer at various speeds
    digitalWrite(BUZZER1, LOW);
    digitalWrite(BUZZER2, HIGH);
    delayMicroseconds(buzz_delay_us);

    digitalWrite(BUZZER1, HIGH);
    digitalWrite(BUZZER2, LOW);
    delayMicroseconds(buzz_delay_us);
  }
}


// Play the winner sound and lights
void play_winner(void)
{
  for (int i = 0; i < 3; i++) { 
    buzz_sound(100, 2000);
    setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW); // Turn all LEDs on
    delay(250);
    buzz_sound(100, 1000);

    setLEDs(CHOICE_OFF); // Turn off LEDs
    delay(250);
    buzz_sound(100, 500);

  }
}



// Play the loser sound/lights
void play_loser(void)
{
  buzz_sound(1000,15000);
}

// Show an "attract mode" display while waiting for user to press button.
void attractMode(void)
{
  while(1) 
  {
    setLEDs(CHOICE_RED);
    delay(100);
    if (checkButton() != CHOICE_NONE) return; // if button is pressed 

    setLEDs(CHOICE_BLUE);
    delay(100);
    if (checkButton() != CHOICE_NONE) return;

    setLEDs(CHOICE_GREEN);
    delay(100);
    if (checkButton() != CHOICE_NONE) return;

    setLEDs(CHOICE_YELLOW);
    delay(100);
    if (checkButton() != CHOICE_NONE) return;
  }
}




// Which button is related to which LED ? 
void testMode(){  
   Serial.println("testMode"); 
    do { 
      setLEDs(CHOICE_RED);
      delay(100);
    } while ( checkButton() != CHOICE_RED );  
    Serial.println("RED pressed");

    do { 
      setLEDs(CHOICE_GREEN);
      delay(100);
    } while ( checkButton() != CHOICE_GREEN);   
      Serial.println("GREEN pressed"); 

    do { 
      setLEDs(CHOICE_BLUE);
      delay(100);
    } while ( checkButton() != CHOICE_BLUE);   
      Serial.println("BLUE pressed"); 

    do { 
      setLEDs(CHOICE_YELLOW);
      delay(100);
    } while ( checkButton() != CHOICE_YELLOW);  
    Serial.println("YELLOW pressed"); 
}



