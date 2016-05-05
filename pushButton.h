
#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include "Arduino.h"



class PushButton {
public:
  uint8_t pin, bool value;

  PushButton(uint8_t _pin):
    pin(_pin), value(0) 
  { pinMode(pin, INPUT); }


  bool get()
  { return (value = digitalRead(pin)); }
  

};

#endif


