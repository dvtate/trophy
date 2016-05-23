#ifndef LED_H
#define LED_H

#include "Arduino.h"
#include <inttypes.h>

#include "color.h"


// tri-color pwm RGB LED class
class TriLED {
public:
  Color color;
  unsigned char pr:7, pg:7, pb:7;
  
  TriLED(const uint8_t& redPin, const uint8_t& greenPin, const uint8_t& bluePin):
    pr(redPin), pg(greenPin), pb(bluePin), color(0,0,0) 
  {
    pinMode(pr, OUTPUT);
    pinMode(pg, OUTPUT);
    pinMode(pb, OUTPUT);
  }
  
  TriLED(const uint8_t& redPin, const uint8_t& greenPin, const uint8_t& bluePin, Color _clr):
    pr(redPin), pg(greenPin), pb(bluePin), color(_clr) 
  {
    pinMode(pr, OUTPUT);
    pinMode(pg, OUTPUT);
    pinMode(pb, OUTPUT);
  }
  void setColor(const Color& clr){
    color = clr;
    analogWrite(pr, color.r);
    analogWrite(pg, color.g);
    analogWrite(pb, color.b);
  }
  void setColor()
    { refresh(); }

  void set(const Color& clr)
    { setColor(clr); }
  void set()
    { setColor(); }

  void set(const uint8_t& val){
    color.r = val;
    color.g = val;
    color.b = val;
    refresh();
  }
  void set(const uint8_t& r, const uint8_t& g, const uint8_t& b){
    color.r = r;
    color.g = g;
    color.b = b;
    setColor(); // write/apply changes
  }


  void push(const Color& clr){
    color.r = clr.r;
    color.g = clr.g;
    color.b = clr.g;
  }
  
  void refresh(){
    analogWrite(pr, color.r);
    analogWrite(pg, color.g);
    analogWrite(pb, color.b);
  }

  
  // sets output to zero without clearing the values
  void off(){
    digitalWrite(pr, 0);
    digitalWrite(pg, 0);
    digitalWrite(pb, 0);
  }
  void setNull()
    { color = Color(0, 0, 0); }
  
  Color& getColor()
    { return color; }

  void colorCycle(const char order[4], uint8_t incr = 1){

    // I don't like this solution...
    uint8_t *c1, *c2, *c3;
    
    if (*order == 'r')
      c1 = &color.r;
    else if (*order == 'g')
      c1 = &color.g;
    else if (*order == 'b')
      c1 = &color.b;
    else
      c1 = &color.r;

    order++; //next char
    
    if (*order == 'r')
      c2 = &color.r;
    else if (*order == 'g')
      c2 = &color.g;
    else if (*order == 'b')
      c2 = &color.b;
    else
      c2 = &color.g;

    order++; //next char
    
    if (*order == 'r')
      c3 = &color.r;
    else if (*order == 'g')
      c3 = &color.g;
    else if (*order == 'b')
      c3 = &color.b;
    else
      c3 = &color.b;


    static uint8_t curHi = 0;
    
    while (incr-- > 0)
      color::cycle3(*c1, *c2, *c3, curHi);

    /* but this one is worse
    while (incr-- > 0)
      if (*order == 'r') {
        order++;
        if (*order == 'r') {
          order++;
          if (*order == 'r') {
            color::cycle3(color.r, color.r, color.r, curHi);
          } else if (*order == 'g') {
            color::cycle3(color.r, color.r, color.g, curHi);
          } else if (*order == 'b') {
            color::cycle3(color.r, color.r, color.b, curHi);
          } else {
            color::cycle3(color.r, color.g, color.b, curHi);
          }
        } else if (*order == 'g') {
          order++;
          if (*order == 'r') {
            color::cycle3(color.r, color.g, color.r, curHi);
          } else if (*order == 'g') {
            color::cycle3(color.r, color.g, color.g, curHi);
          } else if (*order == 'b') {
            color::cycle3(color.r, color.g, color.b, curHi);
          } else {
            color::cycle3(color.r, color.g, color.b, curHi);
          }
        } else if (*order == 'b') {
          order++;
          if (*order == 'r') {
            color::cycle3(color.r, color.b, color.r, curHi);
          } else if (*order == 'g') {
            color::cycle3(color.r, color.b, color.g, curHi);
          } else if (*order == 'b') {
            color::cycle3(color.r, color.b, color.b, curHi);
          } else {
            color::cycle3(color.r, color.g, color.b, curHi);
          }
        } else {
          color::cycle3(color.r, color.g, color.b, curHi);
        }
      } else if (*order == 'g') {
        order++;
        if (*order == 'r') {
          order++;
          if (*order == 'r') {
            color::cycle3(color.g, color.r, color.r, curHi);
          } else if (*order == 'g') {
            color::cycle3(color.g, color.r, color.g, curHi);
          } else if (*order == 'b') {
            color::cycle3(color.g, color.r, color.b, curHi);
          } else {
            color::cycle3(color.r, color.g, color.b, curHi);
          }
        } else if (*order == 'g') {
          order++;
          if (*order == 'r') {
            color::cycle3(color.g, color.g, color.r, curHi);
          } else if (*order == 'g') {
            color::cycle3(color.g, color.g, color.g, curHi);
          } else if (*order == 'b') {
            color::cycle3(color.g, color.g, color.b, curHi);
          } else {
            color::cycle3(color.r, color.g, color.b, curHi);
          }
        } else if (*order == 'b') {
          order++;
          if (*order == 'r') {
            color::cycle3(color.g, color.b, color.r, curHi);
          } else if (*order == 'g') {
            color::cycle3(color.g, color.b, color.g, curHi);
          } else if (*order == 'b') {
            color::cycle3(color.g, color.b, color.b, curHi);
          } else {
            color::cycle3(color.r, color.g, color.b, curHi);
          }
        } else {
          color::cycle3(color.r, color.g, color.b, curHi);
        }
      } else if (*order == 'b') {
        order++;
        if (*order == 'r') {
          order++;
          if (*order == 'r') {
            color::cycle3(color.b, color.r, color.r, curHi);
          } else if (*order == 'g') {
            color::cycle3(color.b, color.r, color.g, curHi);
          } else if (*order == 'b') {
            color::cycle3(color.b, color.r, color.b, curHi);
          } else {
            color::cycle3(color.r, color.g, color.b, curHi);
          }
        } else if (*order == 'g') {
          order++;
          if (*order == 'r') {
            color::cycle3(color.b, color.g, color.r, curHi);
          } else if (*order == 'g') {
            color::cycle3(color.b, color.g, color.g, curHi);
          } else if (*order == 'b') {
            color::cycle3(color.b, color.g, color.b, curHi);
          } else {
            color::cycle3(color.r, color.g, color.b, curHi);
          }
        } else if (*order == 'b') {
          order++;
          if (*order == 'r') {
            color::cycle3(color.b, color.b, color.r, curHi);
          } else if (*order == 'g') {
            color::cycle3(color.b, color.b, color.g, curHi);
          } else if (*order == 'b') {
            color::cycle3(color.b, color.b, color.b, curHi);
          } else {
            color::cycle3(color.r, color.g, color.b, curHi);
          }
        } else {
          color::cycle3(color.r, color.g, color.b, curHi);
        }
      } else {
        color::cycle3(color.r, color.g, color.b, curHi);
      }
      */

    /*
    // for debugging only (uses too much resources)
     Serial.print("r:");
     Serial.print(color.r, DEC);
     Serial.print(" g:");
     Serial.print(color.g, DEC);
     Serial.print(" b:");
     Serial.print(color.b, DEC);
     Serial.print(" CurHi: ");
     Serial.println(curHi, DEC);
    */
    setColor();
    
  }
  
  void colorCycle(const char order[4], uint8_t& curHi, uint8_t incr = 1){

    // I don't like this solution...
    uint8_t *c1, *c2, *c3;
    
    if (*order == 'r')
      c1 = &color.r;
    else if (*order == 'g')
      c1 = &color.g;
    else if (*order == 'b')
      c1 = &color.b;
    else
      c1 = &color.r;

    order++; //next char
    
    if (*order == 'r')
      c2 = &color.r;
    else if (*order == 'g')
      c2 = &color.g;
    else if (*order == 'b')
      c2 = &color.b;
    else
      c2 = &color.g;

    order++; //next char
    
    if (*order == 'r')
      c3 = &color.r;
    else if (*order == 'g')
      c3 = &color.g;
    else if (*order == 'b')
      c3 = &color.b;
    else
      c3 = &color.b;

    while (incr-- > 0)
      color::cycle3(*c1, *c2, *c3, curHi);
 

    /*
    // for debugging only (uses too much resources)
     Serial.print("r:");
     Serial.print(color.r, DEC);
     Serial.print(" g:");
     Serial.print(color.g, DEC);
     Serial.print(" b:");
     Serial.print(color.b, DEC);
     Serial.print(" CurHi: ");
     Serial.println(curHi, DEC);
    */
    setColor();
    
  }
  void colorCycle(uint8_t incr = 1){
    
    static uint8_t curHi = 0;
  
    while (incr-- > 0)
      color::cycle3(color.r, color.g, color.b, curHi);

    setColor();
  }

  void colorCycle(uint8_t& curHi, uint8_t incr = 1){
    while (incr-- > 0)
      color::cycle3(color.r, color.g, color.b, curHi);

    setColor();
  }

  void digitalSetColor(const Color& clr){
    color.r = clr.r ? 255 : 0;
    color.g = clr.g ? 255 : 0;
    color.b = clr.b ? 255 : 0;
    refresh();
  }
  void digitalRefresh() {
    //color.r = color.r ? 255 : 0;
    //color.g = color.g ? 255 : 0;
    //color.b = color.b ? 255 : 0;
    digitalWrite(pr, color.r);
    digitalWrite(pg, color.g);
    digitalWrite(pb, color.b);
  }
  void digitalColorCycle(char order[4]){
    char curHi = color.r? 
                    'r' : color.g? 
                      'g' : color.b? 
                        'b': *order;

    
    uint8_t i = 0;
    while (curHi != *(order + i) && i <= 4)
      i++;
    
    i++;
    
    curHi = (i < 3) ? *(order + i) : *order;

    switch (curHi) {
    case 'r':
      color.r = HIGH;
      color.g = LOW;
      color.b = LOW;
      break;
      
    case 'g':
      color.r = LOW;
      color.g = HIGH;
      color.b = LOW;
      break;
      
    case 'b':
      color.r = LOW;
      color.g = LOW;
      color.b = HIGH;
      break;  
    }

    digitalRefresh();
        
  }
  void digitalColorCycle(){
    
    char nextHi = color.g? 
                    'b' : color.b? 
                      'r' : 'g';

    switch (nextHi) {
    case 'r':
      color.r = HIGH;
      color.g = LOW;
      color.b = LOW;
      break;
      
    case 'g':
      color.r = LOW;
      color.g = HIGH;
      color.b = LOW;
      break;
      
    case 'b':
      color.r = LOW;
      color.g = LOW;
      color.b = HIGH;
      break;
    }
    
    digitalRefresh();
  }

  void invert(){
    color.r = 255 - color.r;
    color.g = 255 - color.g;
    color.b = 255 - color.b;
    refresh();
  }
  
  void writeInverse(){
    analogWrite(pr, 255 - color.r);
    analogWrite(pg, 255 - color.g);
    analogWrite(pb, 255 - color.b);
  }

  // this will never get used...
  void swapPins(const uint8_t& redPin, const uint8_t& bluePin, const uint8_t& greenPin){
    pr = redPin;
    pg = greenPin;
    pb = bluePin;
    // set them as output
    pinMode(pr, OUTPUT);
    pinMode(pg, OUTPUT);
    pinMode(pb, OUTPUT);
    
    setColor();
  }
    
};

// tri-color RGB LED class
class DigitalTriLED {
public:
  bool r : 1, g : 1, b : 1;
  unsigned char pr : 7, pg : 7, pb : 7;
  
  DigitalTriLED(const uint8_t& redPin, const uint8_t& greenPin, const uint8_t& bluePin):
    pr(redPin), pg(greenPin), pb(bluePin), r(LOW), g(LOW), b(LOW) 
  {
    pinMode(pr, OUTPUT);
    pinMode(pg, OUTPUT);
    pinMode(pb, OUTPUT);
  }
  
  DigitalTriLED(const uint8_t& redPin, const uint8_t& greenPin, const uint8_t& bluePin, Color _clr):
    pr(redPin), pg(greenPin), pb(bluePin), r(_clr.r), g(_clr.g), b(_clr.b) 
  {
    pinMode(pr, OUTPUT);
    pinMode(pg, OUTPUT);
    pinMode(pb, OUTPUT);
  }
  void setColor(const bool& red, const bool& green, const bool& blue){
    set(red, green, blue);
    refresh();
  }
  void setColor(const Color& clr){
    r = clr.r;
    g = clr.g;
    b = clr.b;
    refresh();
  }
  
  void setColor()
    { refresh(); }

  void set(const Color& clr)
    { setColor(clr); }
  void set()
    { setColor(); }

  void set(const bool& red, const bool& green, const bool& blue){
    r = red;
    g = green;
    b = blue;
    setColor(); // write/apply changes
  }
  
  void set(const bool& val){
    r = val;
    g = val;
    b = val;
    refresh();
  }

  void push(const Color& clr){
    r = clr.r;
    g = clr.g;
    b = clr.g;
  }
  void refresh(){
    digitalWrite(pr, r);
    digitalWrite(pg, g);
    digitalWrite(pb, b);
  }
  
  // sets output to zero without clearing the values
  void off(){
    digitalWrite(pr, 0);
    digitalWrite(pg, 0);
    digitalWrite(pb, 0);
  }
  
  void setNull(){
    r = LOW;
    g = LOW;
    b = LOW;
  }
  
  void colorCycle(char order[4]){
    char curHi = r ? 
        'r' : g ? 
          'g' : b? 
            'b': *order;

    
    uint8_t i = 0;
    while (curHi != *(order + i) && i <= 4)
      i++;
    
    i++;
    
    curHi = (i < 3) ? *(order + i) : *order;

    switch (curHi) {
    case 'r':
      r = HIGH;
      g = LOW;
      b = LOW;
      break;
      
    case 'g':
      r = LOW;
      g = HIGH;
      b = LOW;
      break;
      
    case 'b':
      r = LOW;
      g = LOW;
      b = HIGH;
      break;  
    }

    
    refresh();
        
  }

  void colorCycle(char* order, uint8_t len){
    char curHi = r ?
        'r' : g ? 
          'g' : b? 
            'b': *order;

    
    uint8_t i = 0;
    while (curHi != *(order + i) && i < len)
      i++;
    i++;
    curHi = (i < len) ? *(order + i) : *order;

    switch (curHi) {
    case 'r':
      r = HIGH;
      g = LOW;
      b = LOW;
      break;
      
    case 'g':
      r = LOW;
      g = HIGH;
      b = LOW;
      break;
      
    case 'b':
      r = LOW;
      g = LOW;
      b = HIGH;
      break;  
      
    }
    
    refresh();
    
  }

  void colorCycle(){
    
    char nextHi = g ? 'b' : ( b? 'r': 'g');

    switch (nextHi) {
    case 'r':
      r = HIGH;
      g = LOW;
      b = LOW;
      break;
      
    case 'g':
      r = LOW;
      g = HIGH;
      b = LOW;
      break;
      
    case 'b':
      r = LOW;
      g = LOW;
      b = HIGH;
      break;
    }
    refresh();
  }

  void invert(){
    r = !r;
    g = !g;
    b = !b;
  }

  // this will never get used...
  void swapPins(const uint8_t& redPin, const uint8_t& bluePin, const uint8_t& greenPin){
    pr = redPin;
    pg = greenPin;
    pb = bluePin;
    // set them as output
    pinMode(pr, OUTPUT);
    pinMode(pg, OUTPUT);
    pinMode(pb, OUTPUT);
    
    setColor();
  }
  
};



// will no longer get used...

class BiLED { // digital
public:
  unsigned char p0:7, p1:7;
  bool v0:1, v1:1; // could be replaced by uint8_t for PWM output
  
  BiLED(const uint8_t& pin0, const uint8_t& pin1):
    p0(pin0), p1(pin1), v0(0), v1(0)
  {
    pinMode(p0, OUTPUT);
    pinMode(p1, OUTPUT);
  }
  BiLED(const uint8_t& pin0, const uint8_t& pin1, const bool& val0, const bool& val1):
    p0(pin0), p1(pin1), v0(val0), v1(val1)
  {
    pinMode(p0, OUTPUT);
    pinMode(p1, OUTPUT);
  }

  void refresh(){
    digitalWrite(p0,v0);
    digitalWrite(p1,v1);
  }
  void set(const uint8_t& val0, const uint8_t& val1){
    v0 = val0;
    v1 = val1;
    refresh();
  }
  void set(const uint8_t& val){
    v0 = val;
    v1 = val;
    refresh();
  }

  // sets output to zero without clearing the values
  void off(){
    digitalWrite(p0, 0);
    digitalWrite(p1, 0);
  }
  
  void swap(){
    bool temp = v0;
    v0 = v1;
    v1 = temp;
    refresh();
  }
};


class BiLED_pwm {
public:
  uint8_t p0, p1;
  uint8_t v0, v1; // could be replaced by uint8_t for PWM output
  
  BiLED_pwm(const uint8_t& pin0, const uint8_t& pin1):
    p0(pin0), p1(pin1), v0(0), v1(0)
  {
    pinMode(p0, OUTPUT);
    pinMode(p1, OUTPUT);
  }
  BiLED_pwm(const uint8_t& pin0, const uint8_t& pin1, const uint8_t& val0, const uint8_t& val1):
    p0(pin0), p1(pin1), v0(val0), v1(val1)
  {
    pinMode(p0, OUTPUT);
    pinMode(p1, OUTPUT);
  }

  void refresh(){
    analogWrite(p0,v0);
    analogWrite(p1,v1);
  }
  void set(const uint8_t& val0, const uint8_t& val1){
    v0 = val0;
    v1 = val1;
    refresh();
  }

  // sets output to zero without clearing the values
  void off(){
    analogWrite(p0, 0);
    analogWrite(p1, 0);
  }
  
  void swap(){
    uint8_t temp = v0;
    v0 = v1;
    v1 = temp;
    refresh();
  }

  void seeSaw(uint8_t incr = 1){
 
    static bool curHi = 0;
    
    while (incr-- > 0) {

      if (!v0 || !v1)
        curHi = !curHi;
      if (!curHi) {
        v0--; v1++;
      } else {
        v1--; v0++;
      }

    }
    refresh();
  }
  
  void seeSaw(bool& curHi, uint8_t incr = 1){
  
    while (incr-- > 0) {

      // switch directions
      if (v0 == 0 || v1 == 0)
        curHi = !curHi;
        
      if (!curHi) {
        v0--; v1++;
      } else {
        v1--; v0++;
      }
        
    }

    refresh();
  }
  
};


#endif
