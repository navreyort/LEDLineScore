#ifndef ENVELOPE_H
#define ENVELOPE_H

#include "RGBFadeControl.h"

class ColorEnvelope {
public:
  ColorEnvelope(Color **colors, uint8_t *times, uint16_t numEvents, uint8_t id):
  colors(colors),times(times),numEvents(numEvents),id(id),curIndex(0){
    this->rgbControl = new RGBFadeControl(this->times[0],this->id);
    this->rgbControl->setup();
    this->rgbControl->setFutureColor(this->colors[0]);  
  }

  void update();
  inline uint8_t getID();
  uint32_t getCurrentColor();
  
private:
  RGBFadeControl *rgbControl;
  Color **colors;
  uint8_t *times;
  uint16_t numEvents;
  uint8_t id;
  uint16_t curIndex;
};

inline void ColorEnvelope::update(){
  this->rgbControl->update();
  
  if(this->rgbControl->getIsDone()){
    this->curIndex = (this->curIndex + 1) % this->numEvents;
    this->rgbControl->setFutureColor(this->colors[this->curIndex]);
    this->rgbControl->setDuration(this->times[this->curIndex]);
  }
}

inline uint8_t ColorEnvelope::getID() {
  return this->id;
}

inline uint32_t ColorEnvelope::getCurrentColor(){
  return this->rgbControl->getCurrentColor();
}

#endif //ENVELOPE_H
