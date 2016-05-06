#include "Arduino.h"

#include <inttypes.h>

#include "led.h"
#include "color.h" //already included by led.h
#include "ultrasonic.h" 
#include "pushButton.h"



//hardware:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
TriLED rgb0(13,12,11,Color(255,0,0));


// the ultrasonic sensor user interface
Ultrasonic sonar(7);


// buzzer
#define BUZZPIN 5
bool audioEnabled = true;
// audio toggle
PushButton buzzButton(39);
// audio indicator
#define BUZZLEDPIN 22


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


void soundCheck(){
  audioEnabled = !buzzButton.toggle();
  digitalWrite(BUZZLEDPIN, audioEnabled);
}

// prototype functions to preavent errors
extern bool checkInput();
extern void nextPattern();

// a namespace filled with functions which are called to make the trophy light up and stuff
namespace lightPatterns {
  // the pattern that gets replaced by other patterns
  void initial(){

    // pattern code goes here:
    rgb0.colorCycle();
    // must be called periodically 
    soundCheck();
    if (checkInput()) return;
  }

  void pattern1(){
    rgb0.setColor(Color(255,0,0));
    // pattern code goes here:
  }
  void pattern2(){
    rgb0.setColor(Color(0,0,255));
    // pattern code goes here:
  }
  void pattern3(){
    rgb0.setColor(Color(0,255,0));
    // pattern code goes here:
  }
}

// sofar only 3 light patterns
#define NUMBER_OF_PATTERNS 3


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
  digitalWrite(13, LOW);
  previous = (sonar.getCm() < 20);
  return false;
}


void setup(){

  Serial.begin(9600);
  

}

void loop(){

  currentPattern();

  checkInput();
    


  Serial.print("Dist =");
  Serial.print(sonar.getCm()); //0~400cm (796 = timeout)
  Serial.println(" cm");

}
