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
  TriLED(const uint8_t& redPin, const uint8_t& bluePin, const uint8_t& greenPin):
    pr(redPin), pb(bluePin), pg(greenPin), color(0,0,0) 
  {
    pinMode(pr, OUTPUT);
    pinMode(pg, OUTPUT);
    pinMode(pb, OUTPUT);
  }
  TriLED(const uint8_t& redPin, const uint8_t& bluePin, const uint8_t& greenPin, Color _clr):
    pr(redPin), pb(bluePin), pg(greenPin), color(_clr) 
  {
    pinMode(pr, OUTPUT);
    pinMode(pg, OUTPUT);
    pinMode(pb, OUTPUT);
  }
  void setColor(const Color& clr){
    color = clr;
  }
  Color& getColor(){
    return color;
  }

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
      cycle3(color.r, color.g, color.b, curHi);


    /* for debugging (uses too much resources)
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
};

#endif
