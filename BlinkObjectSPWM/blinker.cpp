#include <SoftPWM.h>
#include <SoftPWM_timer.h>
#include <arduino.h>


/*************
7/6/15	Library modified to include SPWM so that all DIO pins are PWM
*************/
#include "blinker.h"

// With SoftPWM, all DOIO pins are PWM (after a fashion, good enough for LEDs)
// 3, 5, 6, 9, 10, and 11 can provide PWM output
// 2,3,4,5,6,7,8,9,10,11,12,13 are all DO

bool blinker::SPWM_INIT = false;
blinker* blinker::BLINKERS[16] = {0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L}; // lists of this elements for updating.
int blinker::BLINKER_COUNT = 0;

/**
* blinker instantiate a new object on given pin
* @param {int} pin is the physical pin to use
*/
blinker::blinker( int pin ) {

  blinkPin = pin;
  pinMode(blinkPin, OUTPUT);
  isPWM = true;	 // All pins are PWM with the SoftPWM
  // For Arduino Mini 04:
  //	if ( pin == 3 || pin == 5 || pin == 6 || pin == 9 || pin == 10 || pin == 11 ) isPWM = true;

  setPeriod( 0L );	// default is no blinking (setState determines if on or off.)
  setBrightness( 255 ); // full on
  setState( OFF ); // Off
  setPhase( 0L ); // 0 Phase delay
  reset();

  // for the update routine
  BLINKERS[ BLINKER_COUNT ] = this;
  ++BLINKER_COUNT;
}

void blinker::BlinkerBegin() {
  SoftPWMBegin();
  SPWM_INIT = true;
}

/**
* set brightness
* @param {int} val between 0 and 255
*/
void blinker::setBrightness( int val ) {
  blinkState = ON;	// changing brightness sets state to on.
  brightness = constrain( val, 0, 255 );
  needsUpdate = true; // mark for
  needsUpdate = true;
}

/**
* set period
* @param {ulong} milliseconds for full cycle.
*/
void blinker::setPeriod( unsigned long val ) {
  blinkOnTime = blinkOffTime = val >> 1;
  needsUpdate = true;
}

/**
* set phase
* @param {ulong} milliseconds delay for start the first time or on reset
*/
void blinker::setPhase( unsigned long val ) {
  phaseDelay = val;
  needsUpdate = true;
}

/**
* set period with different on and off cycles
* @param {ulong, ulong} time for on and off
*/
void blinker::setPeriod( unsigned long valOn, unsigned long valOff ) {
  blinkOnTime = valOn;
  blinkOffTime = valOff;
  needsUpdate = true;
}

/**
* set the state (on or off)
* @param
*/
void blinker::setState( bool val ) {
  blinkState = val;
  needsUpdate = true;
}

/**
* restart the timer.
*/
void blinker::reset() {
  startTime = millis() + phaseDelay;
  needsUpdate = true;
}

/**
* class method to reset all the objects
*/
void blinker::resetAll() {
  for ( int i = 0; i < BLINKER_COUNT; i++ )
    BLINKERS[i]->reset();
}

/**
* private routine to activate or deactivate the LED based on the statusFlag
**/
void blinker::activate() {
  SoftPWMSet( blinkPin, blinkState ? brightness : 0 );
  needsUpdate = false;
}

/**
* periodic call to check and set status for this object
*/
void blinker::check() {

  if ( !needsUpdate ) return;  // Nothing to see here.

  // we are simply turning on or off based on the status.
  if ( blinkOnTime == 0L && blinkOffTime == 0L ) {
    activate();		// implements the update change
    return;             // no need to do anything else.
  }

  if ( blinkState ) { // is ON
    if ( millis() > startTime + blinkOnTime ) { // time to turn off
      setState( OFF );
      activate();
      startTime = millis();
    }
  }
  else { // is OFF
    if ( millis() > startTime + blinkOffTime ) { // time to turn off
      setState( ON );
      activate();
      startTime = millis();
    }
  }

}

/**
* class method to reset all the objects
*/
void blinker::checkAll() {
  for ( int i = 0; i < BLINKER_COUNT; i++ )
    BLINKERS[i]->check();
}


