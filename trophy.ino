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
DigitalTriLED base[2][2]{ // fix this in final draft...
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
  top[0].set(LOW);
  top[1].set(LOW);

  base[0][0].set(LOW);
  base[0][1].set(LOW);
  base[1][0].set(LOW);
  base[1][1].set(LOW);
}
void setLEDsHigh(){
  top[0].set(255);
  top[1].set(255);

  base[0][0].set(HIGH);
  base[0][1].set(HIGH);
  base[1][0].set(HIGH);
  base[1][1].set(HIGH);
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

// needed because my dumb ass bought common anode instead of common cathode LEDs
inline void invertLEDs(){
  top[0].color.invert();
  top[1].color.invert();

  base[0][0].invert();
  base[0][1].invert();
  base[1][0].invert();
  base[1][1].invert();
  refreshLEDs();
}

// patterns code:
#include "patterns.h" // the definitions for the patterns
#include "pattern.h" // the common functions for patterns



void theremin(){
  uint16_t resp = 0;
  bool state = LOW;
  while ((resp = sonar.getMicroseconds()) < 5000 && resp != 0 && audioEnabled == true) { 
    digitalWrite(BUZZPIN, state);
    state = !state;
    //delayMicroseconds(resp);
    pickNextPattern();
    soundCheck();
  }
  digitalWrite(BUZZPIN, LOW);
}

// returns true when it's time to switch patterns
bool checkInput(){

  static bool previous = false;

  // if user's hand is detected
  if (previous && sonar.getCm() < 30) {

    pickNextPattern();

    if (audioEnabled) // ring 150Hz Square tone for 10ms
      theremin();//tone(BUZZPIN, 150, 50); 
      
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

  Serial.begin(9600);

  

 
  // disable pull-up resistor
  pinMode(BUZZLEDPIN, OUTPUT);
  pinMode(BUZZPIN, OUTPUT);

}

void loop(){


  // so simple 
  callPattern(patternNumber);
  
}


