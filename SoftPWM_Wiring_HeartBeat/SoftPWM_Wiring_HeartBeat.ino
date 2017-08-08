#include <SoftPWM.h>

void setup()
{
  SoftPWMBegin();

  // Sets the PWM value to 0 for the built-in LED (WLED).
  SoftPWMSet(7, 0);
  
  // Sets the default fade time for WLED to
  // 100 ms fade-up and 550 ms to fade-down.
  SoftPWMSetFadeTime(7, 100, 550);
}

void loop() 
{
  // Turn on WLED
  SoftPWMSet(7, 255);
  // Wait for the fade-up and some extra delay.
  delay(250);
  // Turn off WLED
  SoftPWMSet(7, 0);
  // Wait for the fade-down, and some extra delay.
  delay(650);
}

