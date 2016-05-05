#ifndef COLOR_H
#define COLOR_H

#include <inttypes.h>

// POD color class
class Color {
public:
  uint8_t r, g, b;

  Color(): r(0), g(0), b(0) {}
  Color(const uint8_t& _r, const uint8_t& _g, const uint8_t& _b):
    r(_r), g(_g), b(_b) 
  {}

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

};

Color invert(Color c){
  c.r = 255 - c.r;
  c.g = 255 - c.g;
  c.b = 255 - c.b;
  return c;
}


namespace color {
  void cycle3(uint8_t& v1, uint8_t& v2, uint8_t& v3, uint8_t& curHi){
    if (curHi == 1) {
      v1--; v2++;
    } else if (curHi == 2) {
      v2--; v3++;
    } else if (curHi == 3) {
      v3--; v1++;
    }
    
    if (v1 <= 0 && curHi == 1)
      curHi = 2;
    else if (v2 <= 0 && curHi == 2)
      curHi = 3;
    else if (v3 <= 0 && curHi == 3)
      curHi = 1;
  }
}
#endif
