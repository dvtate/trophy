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



namespace color {

  
  Color invert(Color c){
    c.r = 255 - c.r;
    c.g = 255 - c.g;
    c.b = 255 - c.b;
    return c;
  }

  void cycle3(uint8_t& v0, uint8_t& v1, uint8_t& v2, uint8_t& curHi){
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

  void cycle2(uint8_t& v0, uint8_t& v1, bool& curHi){
    if (!curHi) {
      v0--; v1++;
    } else {
      v1--; v0--;
    }
    
    if (v0 == 0 || !v1 == 0)
      curHi = !curHi;

  }

}

#endif
