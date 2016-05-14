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


DigitalTriLED base[2][2]{
  DigitalTriLED(48, 49, 50), DigitalTriLED(46,47,51),
  DigitalTriLED(44, 45, 52), DigitalTriLED(42, 43, 53)
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


#include "patterns.h" // the definitions for the patterns
#include "pattern.h" // the common functions for patterns




inline void resetLEDs(){
  top[0].set(Color(0,0,0));
  top[1].set(Color(0,0,0));
  
  base[0][0].set(0, 0, 0);
  base[0][1].set(0, 0, 0);
  base[1][0].set(0, 0, 0);
  base[1][1].set(0, 0, 0);
  
}
inline void refreshLEDs(){
  top[0].refresh();
  top[1].refresh();
  
  base[0][0].refresh();
  base[0][1].refresh();
  base[1][0].refresh();
  base[1][1].refresh();
}




// returns true when it's time to switch patterns
bool checkInput(){

  static bool previous = false;

  // if user's hand is detected
  if (previous && sonar.getCm() < 20) {

    pickNextPattern();

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


void setup(){

 
  // disable pull-up resistor
  pinMode(BUZZLEDPIN, OUTPUT);

}

void loop(){



  delay(5);

  /*
  Serial.print("Dist =");
  Serial.print(sonar.getCm()); //0~400cm (796 = timeout)
  Serial.println(" cm");
  */
}
