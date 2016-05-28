#include "Arduino.h"

#include <inttypes.h>

#include "led.h"
#include "color.h" //included by led.h
#include "ultrasonic.h" 
#include "pushButton.h"


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//hardware:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

// 2 PWM RGB LEDs
TriLED top[2] {
  TriLED(13, 12, 11, Color(255, 0, 0)),
  TriLED(10, 9, 8, Color(255, 0, 0))
};

// 4 digital RGB LEDs 
// pretend its like a coordinate plane... this is bad...
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

void refreshLEDs(){
  top[0].refresh();
  top[1].refresh();

  base[0][0].refresh();
  base[0][1].refresh();
  base[1][0].refresh();
  base[1][1].refresh();
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
  
  // NOTE: this delays 4 or 8miliseconds 
  // if user's hand is detected
  if (sonar.getCm() < 30 && previous) {

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

  //Serial.begin(9600);

  // disable pull-up resistor
  pinMode(BUZZLEDPIN, OUTPUT);
  pinMode(BUZZPIN, OUTPUT);

}

void loop(){


  // so simple 
  callPattern(patternNumber);
}
