## LED propane Whack-a-mole 

### Summary 
This is a small project which emulates the whack-a-mole game on an Arduino mega. 

### Details
This repository holds various iterations and versions and is basically my build-log. The end-product is some large-size whack-a-mole game with 
- RGB LEDS which light up to be whacked 
- vibration sensors which have to be whacked 
- an indicator for the level you are in (LED strip partially light up?)
- play sound when an LED is hit ( different sounds for different levels and leds) 
- play sound when reaching the next level 
- play sound when user looses
- support RGB LEDs - fail if hits incorrect light ( only hit Green, not red )  
- additional control of propane poofers which are controlled by 5V relais. 
- attract mode which runs for xx min after a game 
- lounge mode - which lights up the LEDs in a nice pattern after xx minutes of attract mode / after no-one played the game for a while.

Note: Instead of moles popping up, LEDs will light up.


### Todo 
- program logic that mulitple LEDs will light up and turn off, independently  
- no punishment for wrongly hit buttons
- program logic to count score 
- logic to display score, somehow. 
- program counter / timer to indicate that the level time is up. 
 
### Sketch: 
Date: 2016-03-18 



### Sketch: wam
Date: 2016-03-18 
This is a first very simple version which lights up an LED, waits some time and then either times out, or - if you hit the correct sensor/button, the next LED lights up. It supports multiple levels ( time to react reduces in every round) - however, the main issues with this implementation is 
- it's not whack-a-mole
- we don't want to punish the user if he hits the wrong button 
- only one LEDs lights up at a time - whack-a-mole has various moles in a run. 
- setup routine has a lot of hard-coded values and constants - I would like to move this out into libraries. 
- no support for multiple 'gratification-levels' - if a user gets further and further, I would like to light more and more poofers 
- no support / inidication what level the user is in (implement a LEVEL indicator to see how far the player is ? maybe with LED strip which is lit up 10 % / 20 % ??? ) 
- no support for 'incorrect' hits - in a future version, I would like to punish the user if he hits lights of a certain color 
- no support for different LED colors ( all LEDs are basically just lights which turn on / off ). I orderd some WS2812B LED strips which I will use for this in the future 




### Shopping list 
Here are some Amazon links on what I've purchased to get this project going
- Adafruit Arduino Mega
- Arduino starter set 
- Adafruit Fast Vibration Sensor (easy to trigger) https://www.adafruit.com/products/1766
- Anycubic 5V 16 Channel Relay Module Board with Optocoupler Protection LM2576 Power for Arduino http://www.amazon.com/gp/product/B014SV3II2
- 12V LEDs for testing http://www.amazon.com/gp/product/B019W8T65K
- 12V Solenoid valves
- Stuff for the poofer from http://www.poofersupply.com 
- NAVA 1/2" Stainless Steel Spiral Cone Atomization Nozzle for large-volumne poof  http://www.amazon.com/gp/product/B00MHNEJXW 

### Adding code   

    git commit -m" " 
    git push -u origin master 


#### Other links 
- https://learn.sparkfun.com/tutorials/esp8266-powered-propane-poofer
- Hollow cone nozzle 
- tangential hollow cone nozzle  - http://www.sealpump.com/hollow-cone-nozzles.php

#### Arduino code references
- Time multiple LEDs independently with a table approach: http://playground.arduino.cc/Code/MultiBlink
- C++ objects http://playground.arduino.cc/Code/ObjectTimeslicer
- LED on/off timed http://stackoverflow.com/questions/1735990/using-classes-with-the-arduino
- https://learn.adafruit.com/multi-tasking-the-arduino-part-2/pin-change-interrupts
- https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers
- https://learn.adafruit.com/multi-tasking-the-arduino-part-2/external-interrupts 

