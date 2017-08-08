#ifndef blinker_h

#define blinker_h

#define ON  true
#define OFF false

class blinker {
  
  private:
    int blinkPin;
    bool isPWM;
    unsigned long blinkOnTime;
    unsigned long blinkOffTime;
    bool blinkStatus;
    int brightness;
    
    unsigned long microPWMOn;
    unsigned long microPWMOff;
    
    unsigned long startTime;
    unsigned long phaseDelay;

  
  public:
    blinker( int pin );  // instantiate a new object on given pin
    
    void setBrightness( int val );
    void setPhase( unsigned long val );
    void setPeriod( unsigned long val );
    void setPeriod( unsigned long valOn, unsigned long valOff );
    void setState( bool val );
    
    void restart();
    
    void checkWatch();
    void pulse();
  
};





#endif
