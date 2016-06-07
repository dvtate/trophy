#ifndef COLOR_H
#define COLOR_H

#include <inttypes.h>

// POD color class
class Color { // 16777216 colors
public:
  uint8_t r, g, b;

  Color(): r(0), g(0), b(0) {}
  Color(const uint8_t& _r, const uint8_t& _g, const uint8_t& _b):
    r(_r), g(_g), b(_b)
  { }

  Color(const uint8_t& val) :
    r(val), g(val), b(val)
  { }

  Color& invert(){
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
    return *this;
  }

  Color& brighten(const float& multiplier){
    r *= multiplier;
    g *= multiplier;
    b *= multiplier;
    return *this;
  }

  void set(uint8_t red, uint8_t green, uint8_t blue){
    r = red;
    g = green;
    b = blue;
  }

  void set(uint8_t val)
    { r = g = b = val; }
};

// POD digital color class
class DigitalColor {

public:
  bool r : 1, g : 1, b : 1;

  Color(): r(LOW), g(LOW), b(LOW) {}
  Color(bool red, bool green, bool blue):
    r(red), g(green), b(blue)
  { }
  Color(bool value):
    r(value), g(value), b(value)
  { }

  DigitalColor& invert(){
    r = !r;
    g = !g;
    b = !b;
    return *this;
  }

  void set(bool red, bool green, bool blue){
    r = red;
    g = green;
    b = blue;
  }

  void set(bool val)
    { r = g = b = val; }

};

namespace color {

  inline Color& invert(Color& c){
    c.r = 255 - c.r;
    c.g = 255 - c.g;
    c.b = 255 - c.b;
    return c;
  }

  // cycle between 3 values/colors
  inline void cycle3(uint8_t& v0, uint8_t& v1, uint8_t& v2, uint8_t& curHi){
    if (curHi == 0) {
      v0--; v1++;
    } else if (curHi == 1) {
      v1--; v2++;
    } else if (curHi == 2) {
      v2--; v0++;
    }

    if (v0 <= 0 && curHi == 0)
      curHi = 1;
    else if (v1 <= 0 && curHi == 1)
      curHi = 2;
    else if (v2 <= 0 && curHi == 2)
      curHi = 0;
  }

  // reciprocate between 2 values
  inline void cycle2(uint8_t& v0, uint8_t& v1, bool& curHi){
    if (v0 == 0)
      curHi = 1;
    else if (v1 == 0)
      curHi = 0;

    if (curHi == 0) {
      v0--; v1++;
    } else {
      v1--; v0++;
    }

  }

  // reciprocate between 2 values
  inline void cycle2(uint8_t& v0, uint8_t& v1, bool& curHi, uint8_t incr){
    while (incr--) {
      if (v0 == 0)
        curHi = 1;
      else if (v1 == 0)
        curHi = 0;

      if (curHi == 0) {
        v0--; v1++;
      } else {
        v1--; v0++;
      }
    }
  }
}



// base colors
#define COLOR_RED Color(255, 0, 0)
#define COLOR_YELLOW Color(255, 255, 0)
#define COLOR_GREEN Color(0, 255, 0)
#define COLOR_CYAN Color(0, 255, 255)
#define COLOR_BLUE Color(0, 0, 255)
#define COLOR_PURPLE Color(255, 0, 255)
#define COLOR_WHITE Color(255, 255, 255)
#define COLOR_OFF Color(0, 0, 0)
#define COLOR_BLACK COLOR_OFF
#endif
