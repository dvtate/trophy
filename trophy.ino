#include "Arduino.h"

#include <inttypes.h>

#include "led.h"
#include "color.h" //included by led.h
#include "ultrasonic.h" 
#include "pushButton.h"




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//hardware:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


TriLED top[2] {
  TriLED(13, 12, 11, Color(255, 0, 0)),
  TriLED(10, 9, 8, Color(255, 0, 0))
};

TriLED& top0 = top[0], top1 = top[1];

// pretend its like a coordinate plane...
DigitalTriLED base[2][2]{
  DigitalTriLED(47, 46, 51), DigitalTriLED(42, 43, 52),
  DigitalTriLED(49, 48, 50), DigitalTriLED(45, 44, 53),
};



// the ultrasonic sensor / user interface
Ultrasonic sonar(A0);


// buzzer
#define BUZZPIN 27

// audio toggle
PushButton buzzButton(23);

// audio indicator
#define BUZZLEDPIN 22
bool audioEnabled = true;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



void resetLEDs(){
  top[0].set(0);
  top[1].set(0);

  base[0][0].set(0);
  base[0][1].set(0);
  base[1][0].set(0);
  base[1][1].set(0);
}

inline void refreshLEDs(){
  top[0].refresh();
  top[1].refresh();

  base[0][0].refresh();
  base[0][1].refresh();
  base[1][0].refresh();
  base[1][1].refresh();
}

void setLEDsValsZero(){
  top[0].setNull();
  top[1].setNull();

  base[0][0].setNull();
  base[0][1].setNull();
  base[1][0].setNull();
  base[1][1].setNull();
}


// patterns code:
#include "patterns.h" // the definitions for the patterns
#include "pattern.h" // the common functions for patterns


// returns true when it's time to switch patterns
bool checkInput(){

  static bool previous = false;

  // if user's hand is detected
  if (previous && sonar.getCm() < 20) {

    pickNextPattern();

    if (audioEnabled) // ring 150Hz Square tone for 10ms
      tone(BUZZPIN, 150, 50); 
    
    return true;
  }
  previous = sonar.getCm() < 20;
  return false;
}

void soundCheck(){
  audioEnabled = !buzzButton.toggle();
  digitalWrite(BUZZLEDPIN, audioEnabled);
}


void setup(){

  //Serial.begin(9600);
  
  resetLEDs(); //set all leds to 0

 
  // disable pull-up resistor
  pinMode(BUZZLEDPIN, OUTPUT);

}

void loop(){

  callPattern(patternNumber);

  
}



