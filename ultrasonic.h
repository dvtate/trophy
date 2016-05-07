#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "Arduino.h"

class Ultrasonic {
public:
  uint8_t pin; //the SIG pin
  uint16_t duration;// the Pulse time received;
    
  Ultrasonic(int _pin): pin(_pin){}
    
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
    duration = pulseIn(pin, HIGH, 59200); // timeout of 400cm
  }

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

// According to Parallax's datasheet for the PING))), there are
// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
// second).  This gives the distance travelled by the ping, outbound
// and return, so we divide by 2 to get the distance of the obstacle.
// See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
long microsecondsToCentimeters(const long& microseconds) // 0 ~ 400cm
  {return microseconds / 29 / 2;}

// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
long microsecondsToInches(const long& microseconds) // 0 ~ 157 inches
  {return microseconds / 74 / 2;}

#endif
