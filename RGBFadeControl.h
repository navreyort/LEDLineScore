#ifndef RGBFadeControl_H_INCLUDED
#define RGBFadeControl_H_INCLUDED

typedef struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    Color(){
      this->red = 0;
      this->green = 0;
      this->blue = 0;
    }
    Color(uint8_t red, uint8_t green, uint8_t blue){
      this->red = red;
      this->green = green;
      this->blue = blue;
    }
} Color;

//------ START: Increase Number of Colors here ------------------
#define WHITE new Color(255,255,255)
#define YELLOW new Color(255,255,0)
#define BLUE new Color(0,0,255)
#define GREEN new Color(0,255,0)
#define RED new Color(255,0,0)
#define BLACK new Color(0,0,0)
//------ END: Increase Number of Colors here ------------------

//maxStep is multiplied by 60 so that steps can be measured in time/second
class RGBFadeControl {
  public:
    RGBFadeControl(uint16_t maxStep, uint8_t id):step(0x00),isDone(false),maxStep(maxStep*60),id(id){}
    void setup(void);
    void update(void);
    void interpolate(void);

    void swapColor(Color *c, Color *oc);
    void setColor(Color *c, uint32_t newColor);
    void setFutureColor(Color *c);
    boolean getIsDone(void) const;
    uint32_t getCurrentColor(void) const;
    void setDuration(uint16_t duration);
    
  private:
    uint8_t id;
    Color *prevColor;
    Color *curColor;
    Color *futureColor;
    boolean isDone;
    uint16_t step;
    uint16_t maxStep;
    uint32_t curTime;
    static uint8_t scaleFactor;
};

uint8_t RGBFadeControl::scaleFactor = 5;

inline void RGBFadeControl::setup(void){
  this->prevColor = new Color();
  this->curColor = new Color();
  this->futureColor = new Color();
  
  this->setColor(prevColor,0x00);
  this->setColor(curColor,0x00);
  
  this->curTime = millis();
}

inline void RGBFadeControl::update(void){
  if(millis() - this->curTime > 17){ //60 frame per second
    this->curTime = millis();
    if(++this->step <= this->maxStep) this->interpolate(); 
    else if(!this->isDone) {
      this->isDone = true;    
    }
  }
}

inline void RGBFadeControl::interpolate(void){
  static int32_t scalePrevRed,scalePrevGreen,scalePrevBlue,scaleFutureRed,scaleFutureGreen,scaleFutureBlue;
  scalePrevRed = ((int32_t) this->prevColor->red) << RGBFadeControl::scaleFactor;
  scalePrevGreen = ((int32_t) this->prevColor->green) << RGBFadeControl::scaleFactor;
  scalePrevBlue = ((int32_t) this->prevColor->blue) << RGBFadeControl::scaleFactor;

  scaleFutureRed= ((int32_t) this->futureColor->red) << RGBFadeControl::scaleFactor;
  scaleFutureGreen = ((int32_t) this->futureColor->green) << RGBFadeControl::scaleFactor;
  scaleFutureBlue = ((int32_t) this->futureColor->blue) << RGBFadeControl::scaleFactor;

  this->curColor->red = (scalePrevRed + (((scaleFutureRed - scalePrevRed)/this->maxStep) * this->step)) >> RGBFadeControl::scaleFactor;
  this->curColor->green = (scalePrevGreen + (((scaleFutureGreen - scalePrevGreen)/this->maxStep) * this->step)) >> RGBFadeControl::scaleFactor;
  this->curColor->blue = (scalePrevBlue + (((scaleFutureBlue - scalePrevBlue)/this->maxStep) * this->step)) >> RGBFadeControl::scaleFactor;
}

inline void RGBFadeControl::setFutureColor(Color *c){
  this->swapColor(this->prevColor,this->futureColor);
  this->swapColor(this->futureColor,c);
  this->isDone = false;
  this->step = 0;
}

inline void RGBFadeControl::swapColor(Color *c, Color *oc){
  c->red = oc->red;
  c->green = oc->green;
  c->blue = oc->blue;
}

inline void RGBFadeControl::setColor(Color *c, uint32_t newColor){
  c->red = newColor >> 16;
  c->green = (newColor & 0x00ff00) >> 8;
  c->blue = newColor & 0x0000ff;
}

inline boolean RGBFadeControl::getIsDone(void) const {
  return this->isDone;
}

inline uint32_t RGBFadeControl::getCurrentColor(void) const{
  return (((uint32_t) this->curColor->red) << 16) | (((uint32_t) this->curColor->green) << 8) | this->curColor->blue;
}

inline void RGBFadeControl::setDuration(uint16_t duration){
  this->maxStep = duration * 60;  
}

#endif // RGBFadeControl_H_INCLUDED
