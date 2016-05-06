#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include "Arduino.h"

// this shouldn't be an object

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
    static bool previous = false;
    
    if (!digitalRead(pin) && previous)
      return previous = false;
    else if (digitalRead(pin) && !previous)
      return previous = true;
    
    return false;
  }

};

#endif
