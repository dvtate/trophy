#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include "Arduino.h"

class PushButton {
public:
  uint8_t pin;
  bool value;

  PushButton(uint8_t _pin):
    pin(_pin), value(0) 
  { pinMode(pin, INPUT); }


  bool get()
    { return (value = digitalRead(pin)); }
  
  bool toggle(){
    static bool canChange = false;
    static bool state = LOW;

    
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
