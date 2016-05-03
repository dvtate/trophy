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

  void colorCycle(uint8_t incr = 1){
    static uint8_t curHi = 1;

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

    analogWrite(pr, color.r);
    analogWrite(pg, color.g);
    analogWrite(pb, color.b);
  }
  
  void swapPins(const uint8_t& redPin, const uint8_t& bluePin, const uint8_t& greenPin){
    pr = redPin;
    pg = greenpin;
    pb = bluepin;
    // set them as output
    pinMode(pr, OUTPUT);
    pinMode(pg, OUTPUT);
    pinMode(pb, OUTPUT);
    // write the color out
    analogWrite(pr, color.r);
    analogWrite(pg, color.g);
    analogWrite(pb, color.b);
  }
  
};

class BiLED {
public:
  uint8_t p1, p2, v1, v2;
  
  BiLED(uint8_t pin1, uint8_t pin2):
    p1(pin1), p2(pin2)
  {
    pinMode(p1, OUTPUT);
    pinMode(p2, OUTPUT);
  }
  
  BiLED(uint8_t pin1, uint8_t pin2, uint8_t val1, uint8_t val2):
    p1(pin1), p2(pin2), v1(val1), v2(val2)
  {
    pinMode(p1, OUTPUT);
    pinMode(p2, OUTPUT);
  }

  void swap(){
    register uint8_t temp = v1;
    v1 = v2;
    v2 = temp;
  }
};

#endif
