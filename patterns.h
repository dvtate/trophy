#ifndef PATTERNS_H
#define PATTERNS_H

// prototype functions to prevent errors
// these functions get defined later in the file
extern bool checkInput();
extern void nextPattern();
extern void soundCheck();
extern void resetLEDs();
extern void refreshLEDs();


// a namespace filled with functions which are called to make the trophy light up and stuff
namespace lightPatterns {
  
  bool initialized[3] {false, false, false};

  
  // the pattern that gets replaced by other patterns
  void initial(){

    rgb0.colorCycle(4);
    rgb1.colorCycle(4);

    static uint8_t cycles = 0;
    
    for (unsigned char i = 0; i < 4; i++)
      if (!cycles++) {
        redBlues[0][0].swap();
        redBlues[0][1].swap();
        redBlues[1][0].swap();
        redBlues[1][1].swap();
      }


    // must be called periodically 
    soundCheck(); // should be called before checkInput();
    if (checkInput()) return;
    
  }

  void pattern0(){

    // reset from previous pattern... (run once)
    static bool initialized = false;
    if (!initialized[0]) {
      initialized = true;
      
      resetLEDs();
      
      rgb0.color.g = 255;
      rgb1.color.g = 0;
      
    }

    rgb1.colorCycle();

    static bool curHi = 0;
    color::cycle2(rgb0.color.g, rgb1.color.g, curHi);

    
    static uint8_t cycles = 0, activeLED0 = 0, activeLED1 = 0;

    
    // cycle
    for (unsigned char i = 0; i < 4; i++)
      if (!cycles++) {
        if (activeLED0 == 5)
          activeLED0 = 0;
        else
          activeLED0++;

        if (activeLED1 == 5)
          activeLED1 = 0;
        else
          activeLED1++;
        
      }
    // cycle the blues    
    switch (activeLED0) {
    case 0: 
      redBlues[0][0].v1 = !redBlues[0][0].v1;
      break;

    case 1: 
      redBlues[0][1].v1 = !redBlues[0][1].v1;
      break;

    case 2:
      rgb1.color.b = rgb1.color.b ? 0 : 255;
      break;
      
    case 3:
      rgb0.color.b = rgb0.color.b ? 0 : 255;
      break;
      
    case 4: 
      redBlues[1][1].v1 = !redBlues[1][1].v1;
      break;

    case 5: 
      redBlues[1][0].v1 = !redBlues[1][0].v1;
      break;

    }

    // cycle the reds
    switch (activeLED1) {
    case 5: 
      redBlues[0][0].v0 = !redBlues[0][0].v0;
      break;

    case 4: 
      redBlues[0][1].v0 = !redBlues[0][1].v0;
      break;

    case 3:
      rgb1.color.r = rgb1.color.r ? 0 : 255;
      break;
      
    case 2:
      rgb0.color.r = rgb0.color.r ? 0 : 255;
      break;
      
    case 1: 
      redBlues[1][1].v0 = !redBlues[1][1].v0;
      break;

    case 0: 
      redBlues[1][0].v0 = !redBlues[1][0].v0;
      break;

    }

    

    refreshLEDs();

    
    // should get called periodically
    if (checkInput()) return;
    //soundCheck();
  }
  
  void pattern1(){
    
    // reset from previous pattern... (run once)
    static bool initialized = false;
    if (!initialized) {
      resetLEDs();
      initialized = true;
    }
    
    rgb0.setColor(Color(0, 255, 0)); //for now this is it...

    
    // should get called periodically
    soundCheck();
    if (checkInput()) return;
    
  }
  
  void pattern2(){
    
    // reset from previous pattern... (run once)
    static bool initialized = false;
    if (!initialized) {
      resetLEDs();
      initialized = true;
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
