#include <SoftPWM.h>

#define DELAY 100
uint8_t leds[] = {12, 3, 4, 5, 6, 7, 8 };

void setup()
{
  SoftPWMBegin();

  for (int i = 0; i < 7; i++)
    SoftPWMSet(leds[i], 0);

  SoftPWMSetFadeTime(ALL, 100, 100);
}

void loop()
{
  int i;

  for (i = 0; i < 7; i++)
  {
    int j = (i+1) % 7;
    SoftPWMSet(leds[j], 150);
    SoftPWMSet(leds[i], 0);
    delay(DELAY);
  }
  
//  delay(300);
  
//  for (i = 7; i > 0; i--)
//  {
//    SoftPWMSet(leds[i-1], 255);
//    SoftPWMSet(leds[i], 0);
//    delay(DELAY);
//  }
//
//  delay(400);

}
