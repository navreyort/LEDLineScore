#include "ColorEnvelope.h"
#include "WS2801Control.h"

#define kDataPin 2    // Yellow wire
#define kClockPin 3    // Green wire
#define kNumLEDs 7    //Number of LEDs to control

WS2801Control *wsControl;
ColorEnvelope *envelopes[kNumLEDs];

//------ START: Increase Number of Colors here ------------------
Color *WHITE = new Color(255,255,255);
Color *YELLOW = new Color(255,255,0);
Color *BLUE = new Color(0,0,255);
Color *GREEN = new Color(0,255,0);
Color *RED = new Color(255,0,0);
Color *BLACK = new Color(0,0,0);
//------ END: Increase Number of Colors here ------------------
//------- START: Score for LEDS -------------------
#define kNumEvents1 5
Color *color1[kNumEvents1] = {BLUE, BLACK, BLACK, GREEN, BLACK};
uint8_t time1[kNumEvents1] = {4,2,4,6,2};

#define kNumEvents2 3
Color *color2[kNumEvents2] = {YELLOW, BLACK, BLACK};
uint8_t time2[kNumEvents2] = {4,2,4};

#define kNumEvents3 5
Color *color3[kNumEvents3] = {BLACK, RED, BLACK, BLACK, YELLOW};
uint8_t time3[kNumEvents3] = {4,2,4,2,4};

#define kNumEvents4 3
Color *color4[kNumEvents4] = {BLACK, BLACK, YELLOW};
uint8_t time4[kNumEvents4] = {4,2,4};

#define kNumEvents5 5
Color *color5[kNumEvents5] = {YELLOW, BLACK, BLUE, BLACK, RED};
uint8_t time5[kNumEvents5] = {4,2,4,3,3};

#define kNumEvents6 6
Color *color6[kNumEvents6] = {YELLOW, BLACK, RED, BLACK, BLUE, BLACK};
uint8_t time6[kNumEvents6] = {4,2,4,3,2,4};

#define kNumEvents7 3
Color *color7[kNumEvents7] = {YELLOW, BLUE, RED};
uint8_t time7[kNumEvents7] = {4,2,4};
//------- END: Score for LEDS -------------------

void setup() {
  wsControl = new WS2801Control(kDataPin, kClockPin);

  //XXX Parameters: colors, times, number of events, an id of led
  envelopes[0] = new ColorEnvelope(color1,time1,kNumEvents1,0);  
  envelopes[1] = new ColorEnvelope(color2,time2,kNumEvents2,2);  
  envelopes[2] = new ColorEnvelope(color3,time3,kNumEvents3,4);  
  envelopes[3] = new ColorEnvelope(color4,time4,kNumEvents4,6);  
  envelopes[4] = new ColorEnvelope(color5,time5,kNumEvents5,8);  
  envelopes[5] = new ColorEnvelope(color6,time6,kNumEvents6,10);  
  envelopes[6] = new ColorEnvelope(color7,time7,kNumEvents7,12);  
  //------- Add new color sequences here -------------------
  
}

void loop() {
  for(uint8_t i=0;i<kNumLEDs;i++){
    envelopes[i]->update(); 
    wsControl->setPixel(envelopes[i]->getID(),envelopes[i]->getCurrentColor());
  }
  wsControl->update();
}
