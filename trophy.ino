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




// prototype functions to preavent errors
extern bool checkInput();
extern void nextPattern();
extern void soundCheck();
extern void resetLEDs();

// a namespace filled with functions which are called to make the trophy light up and stuff
namespace lightPatterns {
  // the pattern that gets replaced by other patterns
  void initial(){

    // pattern code goes here...

    rgb0.colorCycle(4);
    flasher.seeSaw(16);
    delay(5);
    rgb0.colorCycle(4);
    flasher.seeSaw(16);



    // must be called periodically 
    soundCheck();
    //resetLEDs();

    // don't call checkInput() here...
      // (freezes leds in their current state)
  }

  void pattern1(){

    // pattern code goes here...
    rgb0.setColor(Color(255, 0, 0));

    // should get called periodically
    if (checkInput()) return;
    soundCheck();
  }
  void pattern2(){
    
    // pattern code goes here...
    rgb0.setColor(Color(0, 255, 0));

    
    // should get called periodically
    if (checkInput()) return;
    soundCheck();
  }
  void pattern3(){
    
    // pattern code goes here...
    rgb0.setColor(Color(0, 0, 255));

    
    // should get called periodically
    if (checkInput()) return;
    soundCheck();
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
  previous = (sonar.getCm() < 20);
  return false;
}

void soundCheck(){
  audioEnabled = !buzzButton.toggle();
  digitalWrite(BUZZLEDPIN, audioEnabled);
}

inline void resetLEDs(){

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
  checkInput();
  delay(5);

  // just to make me happy :)

  /*
  Serial.print("Dist =");
  Serial.print(sonar.getCm()); //0~400cm (796 = timeout)
  Serial.println(" cm");
  */
}
