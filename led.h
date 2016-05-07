#ifndef LED_H
#define LED_H

#include "Arduino.h"
#include <inttypes.h>

#include "color.h"


// tri-color RGB LED class
class TriLED {
public:
  Color color;
  uint8_t pr, pg, pb;
  
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
  void setColor(){
    analogWrite(pr, color.r);
    analogWrite(pg, color.g);
    analogWrite(pb, color.b);
  }
  void refresh(){
    setColor(); 
  }

  
  // sets output to zero without clearing the values
  void off(){
    analogWrite(pr, 0);
    analogWrite(pg, 0);
    analogWrite(pb, 0);
  }
  
  Color& getColor()
    { return color; }

  void colorCycle(uint8_t incr = 1){

    /* this is glitchy for unknown reasons...
    uint8_t &c1 = color.r, &c2 = color.g, &c3 = color.b;
    
    if (*order == 'r')
    c1 = color.r;
    else if (*order == 'g')
    c1 = color.g;
    else if (*order == 'b')
    c1 = color.b;
    
    order++; //next char
    
    if (*order == 'r')
    c2 = color.r;
    else if (*order == 'g')
    c2 = color.g;
    else if (*order == 'b')
    c2 = color.b;
    
    order++; //next char
    
    if (*order == 'r')
    c3 = color.r;
    else if (*order == 'g')
    c3 = color.g;
    else if (*order == 'b')
    c3 = color.b;
    */
    
    static uint8_t curHi = 0;
    
    while (incr-- > 0)
      color::cycle3(color.r, color.g, color.b, curHi);


    /* for debugging only (uses too much resources)
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
  
  void colorCycle(uint8_t& curHi, uint8_t incr = 1){
    while (incr-- > 0)
      color::cycle3(color.r, color.g, color.b, curHi);

    setColor();
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

class BiLED {
public:
  uint8_t p0, p1;
  uint8_t v0, v1; // could be replaced by uint8_t for PWM output
  
  BiLED(const uint8_t& pin0, const uint8_t& pin1):
    p0(pin0), p1(pin1), v0(0), v1(0)
  {
    pinMode(p0, OUTPUT);
    pinMode(p1, OUTPUT);
  }
  BiLED(const uint8_t& pin0, const uint8_t& pin1, const uint8_t& val0, const uint8_t& val1):
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
    
      if (!curHi) {
        v0--; v1++;
      } else {
        v1--; v0++;
      }
      
      if (!v0 || !v1)
        curHi = !curHi;
        
    }
    refresh();
   
  }
  
  void seeSaw(uint8_t& curHi, uint8_t incr = 1){
  
    while (incr-- > 0) {
      if (!curHi) {
        v0--; v1++;
      } else {
        v1--; v0++;
      }
      
      if (!v0 || !v1)
        curHi = !curHi;
    }
    
    refresh();
  }

  
};

#endif
