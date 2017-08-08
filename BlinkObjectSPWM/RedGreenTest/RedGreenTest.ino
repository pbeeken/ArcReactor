#include <SoftPWM.h>

#define LED09 9
#define LED10 10 
#define LED11 11
#define LED12 12 
#define LED13 13

volatile int buttonPress = 0;
volatile unsigned long tapTime;


void handleButtonPush() {
  
  if ( millis() > tapTime + 6 ) // if the last tap came within 2ms ignore tap
    buttonPress++;
  tapTime = millis(); // reset tap time.
  
}




void setup()
{
//  Serial.begin(9600);
  pinMode( 2, INPUT_PULLUP );
  digitalWrite (2, HIGH);  // internal pull-up resistor
  attachInterrupt( 0, handleButtonPush, LOW );

  
  SoftPWMBegin();
  
  SoftPWMSet(5, 0);
  SoftPWMSet(6, 0);
  SoftPWMSet(7, 0);

  SoftPWMSetFadeTime(ALL, 1000, 1000);
//  SoftPWMSetFadeTime(6, 1000, 1000);
//  SoftPWMSetFadeTime(7, 1000, 1000);

}

void loop()
{
  
  displayButtonPress();
  
  SoftPWMSet(5, 0);
  SoftPWMSet(6, 100);
  SoftPWMSet(7, 0);

  delay(1000);

  SoftPWMSet(5, 255);
  SoftPWMSet(6, 0);
  SoftPWMSet(7, 255);

  delay(1000);
  
  if ( buttonPress > 7 ) {
    buttonPress = 0;
    Serial.println( "----reset" );
  }
    
}

void displayButtonPress() {
  switch( buttonPress ) {
    case 1:    SoftPWMSet(3, 200); delay( 100 ); SoftPWMSet(3, 0); delay(100); break;
    case 2:    SoftPWMSet(4, 200); delay( 100 ); SoftPWMSet(4, 0); delay(100); break;
    case 3:    SoftPWMSet(5, 200); delay( 100 ); SoftPWMSet(5, 0); delay(100); break;
    case 4:    SoftPWMSet(6, 200); delay( 100 ); SoftPWMSet(6, 0); delay(100); break;
    case 5:    SoftPWMSet(7, 200); delay( 100 ); SoftPWMSet(7, 0); delay(100); break;
    case 6:    SoftPWMSet(8, 200); delay( 100 ); SoftPWMSet(8, 0); delay(100); break;
    case 7:    SoftPWMSet(9, 200); delay( 100 ); SoftPWMSet(9, 0); delay(100); break;
  }
}


