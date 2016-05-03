#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "Arduino.h"

class Ultrasonic {
  public:
    int pin; //the SIG pin
    uint16_t duration;// the Pulse time received;
    
    Ultrasonic(int _pin): pin(_pin){}
    
    void measureDistance();

    // returns 796 upon timeout
    uint16_t getCm(){ // 0 ~ 400cm
      measureDistance();
      return duration / 29 / 2;
    }

    uint8_t getInches(){ // 0 ~ 157 inches
      measureDistance();
      return duration / 74 / 2;
    }
};

void Ultrasonic::measureDistance(){
  
  // produce a pulse
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2); //thats a delay!!
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin, LOW);

  // detect the echo from the pulse
  pinMode(pin, INPUT);
  duration = pulseIn(pin, HIGH);
  
}

long microsecondsToCentimeters(long microseconds) // 0 ~ 400cm
  {return microseconds / 29 / 2;}

long microsecondsToInches(long microseconds) // 0 ~ 157 inches
  {return microseconds / 74 / 2;}

#endif
