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
blinker pin03( 3 );
blinker pin05( 5 );
blinker pin06( 6 );
blinker pin09( 9 );
blinker pin04( 4 );
blinker pin08( 8 );
blinker pin07( 7 );

int dim = 0;
int dir = 1;

// the setup function runs once when you press reset or power the board
void setup() {
  pin07.setPeriod( 100,900 );
  pin04.setPeriod( 1000 );
  pin08.setPeriod( 1000 );
  pin08.setPhase( 250 );
  pin03.restart();
  pin05.restart();
  pin06.restart();
  pin09.restart();
  pin04.restart();
  pin08.restart();
  pin07.restart();
}

// the loop function runs over and over again forever
void loop() {

  pin03.setBrightness( dim );
  pin05.setBrightness( dim );
  pin06.setBrightness( dim );
  pin09.setBrightness( dim );

  pin03.checkWatch();
  pin05.checkWatch();
  pin06.checkWatch();
  pin09.checkWatch();
  pin04.checkWatch();
  pin08.checkWatch();
  pin07.checkWatch();

  dim += dir;

  if ( dim < 0 ) {
    dim = 0; dir = 1;
  }

  if ( dim > 255 ) {
    dim = 255; dir = -1;
  }

  delay( 10 );
}



