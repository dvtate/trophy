#ifndef PATTERNS_H
#define PATTERNS_H

// prototype functions to prevent errors
// these functions get defined later in the file
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
    soundCheck(); // should be called before checkInput();
    if (checkInput()) return;
    
  }

  void pattern1(){

    // reset from previous pattern... (run once)
    static bool initialized = false;
    if (!initialized) {
      resetLEDs();
    }

    // pattern code goes here...
    rgb0.setColor(Color(255, 0, 0)); // for now this is it...

    // should get called periodically
    if (checkInput()) return;
    soundCheck();
  }
  
  void pattern2(){
    
    // reset from previous pattern... (run once)
    static bool initialized = false;
    if (!initialized) {
      resetLEDs();
    }
    
    // pattern code goes here...
    rgb0.setColor(Color(0, 255, 0)); //for now this is it...

    
    // should get called periodically
    soundCheck();
    if (checkInput()) return;
    
  }
  
  void pattern3(){
    
    // reset from previous pattern... (run once)
    static bool initialized = false;
    if (!initialized) {
      resetLEDs();
    }
    
    // pattern code goes here...
    rgb0.setColor(Color(0, 0, 255)); //for now this is it...

    
    // should get called periodically
    soundCheck();
    if (checkInput()) return;
  }
  
}

// so far only 3 light patterns
#define NUMBER_OF_PATTERNS 3


#endif
