#ifndef blinker_h

#define blinker_h

#define ON  true
#define OFF false

class blinker {

  private:
    int		blinkPin;
    bool	isPWM;
    unsigned long blinkOnTime;
    unsigned long blinkOffTime;
    bool	blinkState;
    int		brightness;
    bool	needsUpdate;

    unsigned long microPWMOn;
    unsigned long microPWMOff;

    unsigned long startTime;
    unsigned long phaseDelay;

    void activate();

  public:
    blinker( int pin );  // instantiate a new object on given pin

    void setBrightness( int val );
    void setPhase( unsigned long val );
    void setPeriod( unsigned long val );
    void setPeriod( unsigned long valOn, unsigned long valOff );
    void setState( bool val );

    void reset();
    static void resetAll();

    void check();
    static void checkAll();

    static void BlinkerBegin();

  protected:
    // class variable to indicate the SPWM has been initialized
    static bool SPWM_INIT;
    static blinker* BLINKERS[16];  // lists of this elements for updating.
    static int BLINKER_COUNT;

};





#endif
