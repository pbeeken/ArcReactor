#include <SoftPWM.h>
#include <SoftPWM_timer.h>

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#include "blinker.h"

// 3, 5, 6, 9, 10, and 11 can provide PWM output
blinker pin12( 12 );


volatile int buttonPress = 0;
volatile unsigned long tapTime;


void handleButtonPush() {
  
  if ( millis() > tapTime + 6 ) // if the last tap came within 6ms ignore tap
    buttonPress++;
  tapTime = millis(); // reset tap time.
  buttonPress %= 3; // only 3 states 0, 1, 2
}





// the setup function runs once when you press reset or power the board
void setup() {
  // Establish the interrupt routines.
  pinMode( 2, INPUT_PULLUP );
//  digitalWrite (2, HIGH);  // internal pull-up resistor
  attachInterrupt( 0, handleButtonPush, LOW );

  blinker::BlinkerBegin();
  pin12.setPeriod( 500, 500 );
  pin12.setBrightness( 100 );
  pin12.setState( ON );

 // SoftPWMSetFadeTime(ALL, 1000, 1000);

  blinker::resetAll();

}

// the loop function runs over and over again forever
void loop() {

  blinker::checkAll();

  if ( buttonPress == 1 ) pin12.setState( ON );
  if ( buttonPress == 2 ) pin12.setState( OFF );
  

}



