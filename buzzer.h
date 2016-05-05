#ifndef BUZZER_H
#define BUZZER_H


#include "Arduino.h"
#include <inttypes.h>


class Buzzer {
public:
  uint8_t pin;
  bool enabled, value;
  
  Buzzer(uint8_t _pin):
    pin(_pin), enabled(1), value(HIGH)
  { pinMode(pin, OUTPUT); }

  void set(bool val){
  }

  void refresh(){
    
  }
  
};


#endif
