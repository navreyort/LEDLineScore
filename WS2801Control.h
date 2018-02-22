#ifndef WS2810Control_H_INCLUDED
#define WS2810Control_H_INCLUDED

#include "Adafruit_WS2801.h"

class WS2801Control {
  public:
    WS2801Control(uint8_t dataPin, uint8_t clockPin):dataPin(dataPin),clockPin(clockPin){
      this->strip = new Adafruit_WS2801(25, dataPin, clockPin);
      this->strip->begin();
      this->strip->show();  
    };
    
    ~WS2801Control(){
      delete strip;
    };
    
    void setup(void);
    void update(void);
    void setPixel(uint8_t index, uint32_t color);
    
  private:
    Adafruit_WS2801 *strip;
    uint8_t dataPin;
    uint8_t clockPin;
};

inline void WS2801Control::update(void){
  this->strip->show();
}

inline void WS2801Control::setPixel(uint8_t index, uint32_t color){
  this->strip->setPixelColor(index, color);
}

#endif // WS2810Control_H_INCLUDED
