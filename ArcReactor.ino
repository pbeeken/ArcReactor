/**
I have tried elaborate efforts at manipulting the SoftPWM code
so as not to include "delay" to no avail.  The pulse and sequencing
operations don't behave properly.  This code is straight top down

**/

#include <SoftPWM.h>



const uint8_t arcLEDs[] = {12, 3, 4, 5, 6, 7, 8 };
const uint8_t red1LED = 9;
const uint8_t grnLED = 10;
const uint8_t red2LED = 11;

#define NUM_TAPS   6

/** ######## INTERRUPT SERVICE ROUTINE #############
  These are all the elements of the ISR that handles the button
  presses.
**/
volatile int buttonPress = 0;
volatile bool buttonPressChanged = false;
volatile unsigned long tapTime = 0L;
void handleButtonPush() {
  if ( millis() > tapTime + 6 ) {// if the last tap came within 6ms ignore tap
    buttonPress++;
    buttonPressChanged = true;
  }
  tapTime = millis(); // reset tap time.
  buttonPress %= NUM_TAPS; // only 3 states 0, 1, 2
}


// Key setup loop
void setup() {
  // Establish the interrupt routines.
  pinMode( 2, INPUT_PULLUP );
  attachInterrupt( 0, handleButtonPush, LOW );

  // Initialize the Software PWM
  SoftPWMBegin();
  resetLEDs();

  SoftPWMSetFadeTime(ALL, 500, 500);

}

// for those elements requiring a time flag
unsigned long cycleCount = 0L;

// Key execution loop
void loop() {
  // put your main code here, to run repeatedly:

  if ( buttonPressChanged ) {
    resetLEDs();
    buttonPressChanged = false;
    cycleCount = 0L;
  }

  switch ( buttonPress ) {
    case 0:
      passivePulse();
      break;
    case 1:
      roundPulse();
      break;
    case 2:
      freneticPulse();
      break;
    case 3:
      randomBlink();
      break;
    case 4:
      breakDown();
      break;
    case 5:
      weakError();
      break;

  }
}

/** ###########  SERVICE ROUTINES ########################
**/

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void passivePulse() {
  unsigned long fade = 800;

  SoftPWMSetFadeTime(ALL, fade, fade);
  SoftPWMSetFadeTime(grnLED, fade >> 1, fade >> 1);

  for ( int i = 0; i < 7; i++ )
    SoftPWMSet(arcLEDs[i], 200);  // On, not too bright

  SoftPWMSet(grnLED, 20);  // On, not too bright
  myDelay( fade );
  for ( int i = 0; i < 7; i++ )
    SoftPWMSet(arcLEDs[i], 0);  // Off
  SoftPWMSet(grnLED, 0);  // On, not too bright
  myDelay( fade );
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void roundPulse() {
  unsigned long fade = 100;

  SoftPWMSetFadeTime(ALL, fade, fade);
  for ( int i = 0; i < 7; i++ ) {
    int j = (i + 1) % 7;
    SoftPWMSet(arcLEDs[j], 200);  // On, not too bright
    SoftPWMSet(arcLEDs[i], 0);  // Off
    myDelay( fade );
  }
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void freneticPulse() {
  unsigned long fade = 50;

  SoftPWMSetFadeTime(ALL, fade, fade);
  SoftPWMSetFadeTime(grnLED, fade >> 1, fade >> 1);
  ++cycleCount;
  if ( cycleCount % 2 == 0 )
    SoftPWMSet(red1LED, 0);  // Off
  else
    SoftPWMSet(red2LED, 0);  // Off

  for ( int i = 0; i < 7; i++ ) {
    int j = (i + 2) % 7;
    SoftPWMSet(arcLEDs[j], 200);  // On, not too bright
    SoftPWMSet(arcLEDs[i], 0);  // Off
    myDelay( fade );
  }
  
  if ( cycleCount % 2 == 0 )
    SoftPWMSet(red2LED, 255);  // On, not too bright
  else
    SoftPWMSet(red1LED, 255);  // On, not too bright

  myDelay(10);

}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void randomBlink() {
  SoftPWMSetFadeTime(ALL, 50, 400);
  uint8_t pin = random(8);
  SoftPWMSet(red1LED, 0);  // Off
  SoftPWMSet(red2LED, 0);  // Off

  SoftPWMSet(arcLEDs[pin], 255);
  myDelay(50);
  SoftPWMSet(arcLEDs[pin], 0);
  myDelay(random(100));
  
  if ( random(2) )
    SoftPWMSet(red1LED, 20);  // On, not too bright
    else
    SoftPWMSet(red2LED, 20);  // On, not too bright

  myDelay(10);
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void breakDown() {
  ++cycleCount;
  unsigned long fade = 100;
  SoftPWMSetFadeTime(ALL, fade, fade);

  // Starting failure
  if ( cycleCount < 6 ) {
    uint8_t pin = random(8);
    for ( int i = 0; i < 7; i++ ) {
      int j = (i + 1) % 7;
      if ( i != pin ) {
        SoftPWMSet(arcLEDs[j], random(100, 250) ); // On, not too bright
        SoftPWMSet(arcLEDs[i], 0);  // Off
      }
      myDelay( fade );
    }
    // Later failure
  } else if ( cycleCount < 12 ) {
    uint8_t pin1 = random(0, 4);
    uint8_t pin2 = random(4, 8);
    for ( int i = 0; i < 7; i++ ) {
      int j = (i + 1) % 7;
      if ( i != pin1 && i != pin2 ) {
        SoftPWMSet(arcLEDs[j], random(20, 150) ); // On, not too bright
        SoftPWMSet(arcLEDs[i], 0);  // Off
      }
      myDelay( fade );
    }
    // final crash
  } else if ( cycleCount < 13 ) {
    uint8_t pins[3];
    pins[0] = random(0, 4);
    pins[1] = random(4, 8);
    pins[2] = 7;
    for ( int i = 0; i < 3; i++ ) {
      int j = (i + 3) % 7;
      SoftPWMSet(arcLEDs[pins[j]], random(20, 150) ); // On, not too bright
      SoftPWMSet(arcLEDs[pins[i]], 0);  // Off
      myDelay( fade );
    }
  } else {
    bigError();
  }
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void bigError() {
  int fade = 50;
  SoftPWMSetFadeTime(ALL, fade, fade);

  SoftPWMSet(red1LED, 200);
  SoftPWMSet(red2LED, 200);
  myDelay( fade );

  SoftPWMSet(red1LED, 0);
  SoftPWMSet(red2LED, 0);
  myDelay( fade );
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void weakError() {
  int fade = 200;
  SoftPWMSetFadeTime(ALL, fade + 50, fade + 50);

  SoftPWMSet(red1LED, 100);
  SoftPWMSet(red2LED, 0);
  myDelay( fade );

  SoftPWMSet(red1LED, 0);
  SoftPWMSet(red2LED, 100);
  myDelay( fade );
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void resetLEDs() {
  SoftPWMSetFadeTime(ALL, 100, 100);
  for ( int i = 0; i < 7; i++ ) SoftPWMSet(arcLEDs[i], 0);
  SoftPWMSet(grnLED, 0);
  SoftPWMSet(red1LED, 0);
  SoftPWMSet(red2LED, 0);
}


void myDelay(unsigned int delta) {
  unsigned long endTime = millis() + delta;
  while ( millis() < endTime );
}
