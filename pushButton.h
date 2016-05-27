#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include "Arduino.h"

class PushButton {
public:
  unsigned char pin : 7;
  bool value : 1;

  PushButton(uint8_t _pin):
    pin(_pin), value(0) 
  { pinMode(pin, INPUT); }


  bool get()
    { return (value = digitalRead(pin)); }
  
  bool toggle(){
    static bool canChange = false, state = LOW;

    
    if (digitalRead(pin) && !canChange) {
      canChange = true;
    } else if (!digitalRead(pin) && canChange) {
      canChange = false;
      return state = !state;
    }
    
    return state;
  }
  
  bool toggle(bool& state, bool& canChange){
    
    if (digitalRead(pin) && !canChange) {
      canChange = true;
    } else if (!digitalRead(pin) && canChange) {
      canChange = false;
      return state = !state;
    }
    
    return state;
  }
};

#endif
