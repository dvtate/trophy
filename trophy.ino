#include "Arduino.h"

#include <inttypes.h>

#include "led.h"
#include "color.h" //already included by led.h
#include "ultrasonic.h" 
#include "buzzer.h"


// prototype functions to preavent errors
bool checkInput();
void nextPattern();

// a namespace filled with functions which are called to make the trophy light up and stuff
namespace lightPatterns {
  // the pattern that gets replaced by other patterns
  void initial(){
    static TriLED lys(13,12,11,Color(255,0,0));
    
    if (checkInput()) return; // break out of the function on user input 
    
  }

  void pattern1(){
    
  }
  void pattern2(){
    
  }
  void pattern3(){
    
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





// the ultrasonic sensor user interface
Ultrasonic sonar(7);




// choose a different pattern
void nextPattern(){
  currentPattern = patterns[random(NUMBER_OF_PATTERNS)];  
}

// returns true when it's time to switch patterns
bool checkInput(){
  // if user's hand is detected
  if (sonar.getCm() < 20) {
    nextPattern();
    return true;
  }
  return false;
}


void setup(){

  Serial.begin(9600);

  // we need a random seed to get our random numbers from 
  // reading from an unused pin results in a relatively random number
  // however, we dont want to sacrifice a pin for this, so I inserted `686`
  randomSeed(686); 
  
}

void loop(){

  currentPattern();

/*  
  Serial.print("Dist =");
  Serial.print(sonar.getCm()); //0~400cm (796 = timeout)
  Serial.println(" cm");
*/
}
