#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "Arduino.h"

class Ultrasonic {

public:
  unsigned char pin : 7; //the SIG pin
  uint16_t duration;// the Pulse time received;
    
  Ultrasonic(int _pin): pin(_pin){}

  // takes 4 miliseconds to complete
  void measureDistance(){
   
    // produce a pulse
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(2); //thats a delay!!
    digitalWrite(pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pin, LOW);
  
    // detect the echo from the pulse
    pinMode(pin, INPUT);

    // I want a consistent scan duration...
    duration = pulseIn(pin, HIGH, 4000 /*59200*/); // NOTE: timeout

    if (duration == 0)
      duration = 4000;
    else  
      // I want a consistent scan duration of 4000 microseconds...
      delayMicroseconds(4000 - 2 - 5 - duration);
    

    
  }
  
  // idk why this is glitchy...
  bool lessThan20Cm(){
   
    // produce a pulse
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(2); //thats a delay!!
    digitalWrite(pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pin, LOW);
  
    // detect the echo from the pulse
    pinMode(pin, INPUT);
    return pulseIn(pin, HIGH, 1160); // returns 0 if >20cm
    
  }
  uint16_t getMicroseconds(){
    // produce a pulse
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(2); //thats a delay!!
    digitalWrite(pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pin, LOW);
  
    // detect the echo from the pulse
    pinMode(pin, INPUT);
    duration = pulseIn(pin, HIGH, 4000/*59200*/); // NOTE: timeout

    return duration;
  }

  uint16_t getCm(){ // 0 ~ 400cm
    measureDistance();
    return duration / 29 / 2;
  }

  uint8_t getInches(){ // 0 ~ 157 inches
    measureDistance();
    return duration / 74 / 2;
  }
  
};

inline long microsecondsToCentimeters(const long& microseconds) // 0 ~ 400cm
  { return microseconds / 29 / 2; }

inline long microsecondsToInches(const long& microseconds) // 0 ~ 157 inches
  { return microseconds / 74 / 2; }

#endif
