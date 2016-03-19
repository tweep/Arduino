
#define CHOICE_OFF      0 //Used to control LEDs
#define CHOICE_NONE     0 //Used to check buttons
#define CHOICE_RED  (1 << 0)
#define CHOICE_GREEN    (1 << 1)
#define CHOICE_BLUE (1 << 2)
#define CHOICE_YELLOW   (1 << 3)

#define LED_RED     10
#define LED_GREEN   3
#define LED_BLUE    13
#define LED_YELLOW  5

// Button pin definitions
#define BUTTON_RED    9
#define BUTTON_GREEN  2
#define BUTTON_BLUE   12
#define BUTTON_YELLOW 6


#define BUZZER1  4
#define BUZZER2  7

// Define game parameters
#define ROUNDS_TO_WIN      13 //Number of rounds to succesfully remember before you win. 13 is do-able.
#define ENTRY_TIME_LIMIT   3000 //Amount of time to press a button before game times out. 3000ms = 3 sec

#define MODE_MEMORY  0
#define MODE_BATTLE  1
#define MODE_BEEGEES 2

byte gameMode = MODE_MEMORY; //By default, let's play the memory game
byte gameRound = 0; //Counts the number of succesful rounds the player has made it through

int buttonsPerLevel [] = {2, 4, 8, 10, 15};


/* use library - define this outside of setup(). Access object with ch_inst.function() */ 
//#include <ChaseLed.h> 
//ChaseLed ch_inst(13);    // create new instance called ch_inst


void setup()
{
  //Setup hardware inputs/outputs. These pins are defined in the hardware_versions header file
  // executed after startup + reset only
  //Enable pull ups on inputs
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

  // Check to see if the lower right button is pressed
  if (checkButton() == CHOICE_YELLOW) play_beegees();

  // Check to see if upper right button is pressed
  if (checkButton() == CHOICE_GREEN)
  {
    gameMode = MODE_BATTLE; //Put game into battle mode

    //Turn on the upper right (green) LED
    setLEDs(CHOICE_GREEN);
    toner(CHOICE_GREEN, 150);

    setLEDs(CHOICE_RED | CHOICE_BLUE | CHOICE_YELLOW); // Turn on the other LEDs until you release button

    while(checkButton() != CHOICE_NONE) ; // Wait for user to stop pressing button

    //Now do nothing. Battle mode will be serviced in the main routine
  }

  play_winner(); // After setup is complete, say hello to the world
}

void loop()
{
  attractMode(); // Blink lights while waiting for user to press a button

  // Indicate the start of game play
  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW); // Turn all LEDs on
  delay(1000);
  setLEDs(CHOICE_OFF); // Turn off LEDs
  delay(250);

  if (gameMode == MODE_MEMORY)
  {
    if (led_game() == true)
      play_winner(); // Player won
    else 
      play_loser(); // Player lost
  }

  if (gameMode == MODE_BATTLE)
  {
    play_battle(); // Play game until someone loses

    play_loser(); // Player lost, play loser tones
  }
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//The following functions are related to game play only

/* 
* 
*   Jans LED game
*
*   Returns 0 if player loses, or 1 if player wins
*
#   Args      : None
*   Returnval : [0/1] 
* 
*
*/ 

    // game logic 
    // - get random choice 
    // - illuminate choice 
    // - user has to hit button before timeout 
    // - after X lights have been illuminated, start new level 
    // - announce new level 
    // - illuminate more LEDs  / from level X onwards, illuminate 2-3 leds at the same time
    // - end game after X rounds

void announceLevel(byte level)
{
} 

boolean led_game(void)
{
  randomSeed(millis()); 
  gameRound = 0; // Reset the game frame back to one frame

  while (gameRound < ROUNDS_TO_WIN)
  {  
      announceLevel(gameRound); 
      // loop until set number of correct buttons has been hit
      for (byte correctButtons = 0 ; correctButtons < buttonsPerLevel[gameRound] ; correctButtons++)
      { 
        // get random choice(=LED) and turn it on
        byte randButton = set_random_button();
        setLEDs(randButton);  

        // get user input || or timeout 
        byte choice = wait_for_button(); 

        if ( (choice == 0) || (choice != randButton))  return false; // If the choice is incorect, player loses.

        delay(100); // Give the user a 100ms rest 
        
      }
      gameRound++;
      delay(5000); // Rest 5000ms between levels
  }
  return true; // We should never get here
}


boolean play_battle(void) {}



byte set_random_button(void)
{
  byte newButton = random(0, 4); //min (included), max (exluded)

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

// Wait for a button to be pressed. 
// Returns one of LED colors (LED_RED, etc.) if successful, 0 if timed out
byte wait_for_button(void)
{
  long startTime = millis(); // Remember the time we started the this loop

  while ( (millis() - startTime) < ENTRY_TIME_LIMIT) // Loop until too much time has passed
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
    break;
  case CHOICE_GREEN:
    break;
  case CHOICE_BLUE:
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
}



// Play the loser sound/lights
void play_loser(void)
{
}

// Show an "attract mode" display while waiting for user to press button.
void attractMode(void)
{
  while(1) 
  {
    setLEDs(CHOICE_RED);
    delay(100);
    if (checkButton() != CHOICE_NONE) return;

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



int LEDnumber = 0; // Keeps track of which LED we are on during the beegees loop

// This function is activated when user holds bottom right button during power up
void play_beegees()
{
  //Turn on the bottom right (yellow) LED
  setLEDs(CHOICE_YELLOW);
  toner(CHOICE_YELLOW, 150);

  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE); // Turn on the other LEDs until you release button

  while(checkButton() != CHOICE_NONE) ; // Wait for user to stop pressing button

  setLEDs(CHOICE_NONE); // Turn off LEDs

  digitalWrite(BUZZER1, LOW); // setup the "BUZZER1" side of the buzzer to stay low, while we play the tone on the other pin.

  while(checkButton() == CHOICE_NONE) //Play song until you press a button
  {
  }
}

// Each time this function is called the board moves to the next LED
void changeLED(void)
{
  setLEDs(1 << LEDnumber); // Change the LED

  LEDnumber++; // Goto the next LED
  if(LEDnumber > 3) LEDnumber = 0; // Wrap the counter if needed
}

