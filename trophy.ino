#include "Arduino.h"

#include <inttypes.h>

#include "led.h"
#include "color.h" //included by led.h
#include "ultrasonic.h" 
#include "pushButton.h"



//hardware:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
TriLED rgb0(13,12,11,Color(255,0,0));

BiLED flasher(6, 5, 255, 0);

// the ultrasonic sensor user interface
Ultrasonic sonar(7);


// buzzer
#define BUZZPIN 3
bool audioEnabled = true;
// audio toggle
PushButton buzzButton(39);
// audio indicator
#define BUZZLEDPIN 22


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
    
    if (audioEnabled)
      tone(BUZZPIN,150,25);
    
    return true;
  }
  previous = (sonar.getCm() < 20);
  return false;
}

void soundCheck(){
  audioEnabled = !buzzButton.toggle();
  digitalWrite(BUZZLEDPIN, audioEnabled);
}

inline void resetLEDs(){
  rgb0.setColor(Color(0,0,0));
  flasher.set(0,0);
}

void setup(){
  Serial.begin(9600);

  while(1){
    currentPattern();
    if (checkInput()) break;
    delay(5);
    
  }

  // reset the LEDs
  rgb0.setColor(Color(0,0,0));
  flasher.set(0,0);
}

void loop(){

  //so simple :D
  currentPattern();
  checkInput(); // might not be needed
  delay(5);

  /*
  Serial.print("Dist =");
  Serial.print(sonar.getCm()); //0~400cm (796 = timeout)
  Serial.println(" cm");
  */
}
