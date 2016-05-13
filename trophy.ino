#include "Arduino.h"

#include <inttypes.h>

#include "led.h"
#include "color.h" //included by led.h
#include "ultrasonic.h" 
#include "pushButton.h"




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//hardware
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


TriLED rgbs[2] {
  TriLED(13, 12, 11, Color(255, 0, 0));
  TriLED(10, 9, 8, Color(255, 0, 0));
};

const& TriLED rgb0 = rgbs[0], rgb1 = rgbs[1];


BiLED redBlues[2][2]{
  BiLED(A0, A1), BiLED(A2, A3),
  BiLED(A4, A5), BiLED(A6, A7)
};


// the ultrasonic sensor / user interface
Ultrasonic sonar(52);


// buzzer
#define BUZZPIN 27

// audio toggle
PushButton buzzButton(23);

// audio indicator
#define BUZZLEDPIN 22
bool audioEnabled = true;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


// namespace lightpatterns & NUMBER_OF_PATTERNS
#include "patterns.h"

// the jump table of the different light patterns
void (*patterns[NUMBER_OF_PATTERNS])(void) = {
  lightPatterns::pattern1,
  lightPatterns::pattern2,
  lightPatterns::pattern3
};

// the currently selected light pattern
void (*currentPattern)(void) = lightPatterns::initial;


// choose a different pattern
void nextPattern(){

  static uint8_t patternNumber = 0;

  if (patternNumber < (NUMBER_OF_PATTERNS - 1))
    patternNumber++;
  else
    patternNumber = 0;

  currentPattern = patterns[patternNumber];

}

// returns true when it's time to switch patterns
bool checkInput(){

  static bool previous = false;

  // if user's hand is detected
  if (previous && sonar.getCm() < 20) {

    nextPattern();

    if (audioEnabled) // ring 150Hz Square tone for 10ms
      tone(BUZZPIN, 150, 10); 
    
    return true;
  }
  previous = sonar.getCm() < 20;
  return false;
}

void soundCheck(){
  audioEnabled = !buzzButton.toggle();
  digitalWrite(BUZZLEDPIN, audioEnabled);
}

inline void resetLEDs(){
  rgb0.setColor(Color(0, 0, 0));
  flasher.set(0,0);
}

void setup(){
  
  // Serial.begin(9600);

  // disable pull-up resistor
  pinMode(BUZZLEDPIN, OUTPUT);

  for (;1;) { // infinite crying
    currentPattern(); // call initial pattern until user input is recieved
    delay(4);

  }

  // reset the LEDs
  rgb0.setColor(Color(0, 0, 0));
  flasher.set(0, 0);

}

void loop(){

  //so simple :D
  currentPattern();

 // called in currentPattern()  
//  soundCheck();
//  checkInput();

  delay(5);

  /*
  Serial.print("Dist =");
  Serial.print(sonar.getCm()); //0~400cm (796 = timeout)
  Serial.println(" cm");
  */
}
