#ifndef PATTERNS_H
#define PATTERNS_H

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


#endif
