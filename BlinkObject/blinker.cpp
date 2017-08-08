#include <arduino.h>

#include "blinker.h"

// 3, 5, 6, 9, 10, and 11 can provide PWM output
// 2,3,4,5,6,7,8,9,10,11,12,13 are all DO

unsigned char sinVals[] = {};

/**
* blinker instantiate a new object on given pin
* @param {int} pin is the physical pin to use
*/
blinker::blinker( int pin ) {
  blinkPin = pin;
  pinMode(blinkPin, OUTPUT);
  isPWM = false;
  // For Arduino Mini 04:
  if ( pin == 3 || pin == 5 || pin == 6 || pin == 9 || pin == 10 || pin == 11 ) isPWM = true;

  setPeriod( 0L );  // default is no blinking (setState determines if on or off.)
  setState( OFF );
  setPhase( 0L );
  restart();
}

/**
* set brightness
* @param {int} val between 0 and 255
  */
void blinker::setBrightness( int val ) {
  blinkStatus = ON;  // changing brightness sets state to on.
  brightness = constrain( val, 0, 255 );
}


/**
* set period
* @param {ulong} milliseconds for full cycle.
*/
void blinker::setPeriod( unsigned long val ) {
  blinkOnTime = blinkOffTime = val >> 2;
}

/**
* set phase
* @param {ulong} milliseconds delay for start.
*/
void blinker::setPhase( unsigned long val ) {
  phaseDelay = val;
}


/**
* set period with different on and off cycles
* @param {ulong, ulong} time for on and off
*/
void blinker::setPeriod( unsigned long valOn, unsigned long valOff ) {
  blinkOnTime = valOn;
  blinkOffTime = valOff;
}

/**
* set the state (on or off)
* @param
*/
void blinker::setState( bool val ) {
  blinkStatus = val;
  if ( isPWM )
    analogWrite( blinkPin, val ? brightness : 0 );
  else
    digitalWrite(blinkPin, val ? HIGH : LOW);
}

/**
* restart the timer.
*/
void blinker::restart() {
  startTime = millis() + phaseDelay;
}

/**
* periodic call to check and set status.
*/
void blinker::checkWatch() {
  if ( blinkOnTime == 0L && blinkOffTime == 0L ) {
    setState( blinkStatus );  // automatically updates the brightness.
    return; // no need to do anything else.
  }

  if ( blinkStatus ) { // is ON
    if ( !isPWM ) pulse(); // run algorithm to dim
    if ( millis() > startTime + blinkOnTime ) { // time to turn off
      setState( OFF );
      startTime = millis();
    }
  }
  else { // is OFF
    if ( millis() > startTime + blinkOffTime ) { // time to turn off
      setState( ON );
      startTime = millis();
    }
  }
}


/**
* manage pseudo pwm on other pins
*/
void blinker::pulse() {
}



