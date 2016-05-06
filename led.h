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
  void refresh()
    { setColor(); }
  
  Color& getColor()
    { return color; }

  void colorCycle(uint8_t incr = 1, uint8_t curHi = 1){ 

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
  Uint8_t v0, v1; // could be replaced by uint8_t for PWM output
  
  BiLED(uint8_t pin0, uint8_t pin1):
    p0(pin0), p1(pin1), v0(LOW), v1(LOW)
  {
    pinMode(p0, OUTPUT);
    pinMode(p1, OUTPUT);
  }  
  BiLED(uint8_t pin0, uint8_t pin1, uint8_t val0, uint8_t val1):
    p0(pin0), p1(pin1), v0(val0), v1(val1)
  {
    pinMode(p0, OUTPUT);
    pinMode(p1, OUTPUT);
  }

  void refresh(){
    digitalWrite(p0,v0);
    digitalWrite(p1,v1);
  }
  void set(uint8_t val0, uint8_t val1){
    v0 = val0;
    v1 = val1;
    refresh();
  }
  void swap(){
    uint8_t temp = v0;
    v0 = v1;
    v1 = temp;
    refresh();
  }

  
};

#endif
