#ifndef PATTERNS_H
#define PATTERNS_H



// prototype functions to prevent errors
// these functions get defined later in the file
extern bool checkInput();
extern void pickNextPattern();
extern void soundCheck();
extern void resetLEDs();
extern void refreshLEDs();

#define NUMBER_OF_PATTERNS 3

namespace examplePattern {
  bool initialized = false; // required

  // called once before periodic begins
  void init (){
    
  }

  // cycled, continuously run
  void periodic(){

    // these must be called at least once.
    soundCheck(); // verify sound and input agree
    if(checkInput()) return;

    
    
  }
  
  // called before ending this pattern
  void disable(){
    
  }
  
}


namespace pattern0 {
  bool initialized = false;

  // local variables
  uint8_t cycles = 0, curHi = 0;
  
  void init(){
    cycles = 0;
    curHi = 0;
    top[0].set(Color(255, 0, 0));
    top[1].set(Color(255, 0, 0));
    base[0][0].set(255, 0, 0);
    base[0][1].set(255, 0, 0);
    base[1][0].set(255, 0, 0);
    base[1][1].set(255, 0, 0);

  }

  void periodic(){
    soundCheck(); // should be called before checkInput();
    if (checkInput()) return;


    color::cycle3(top[0].color.r, top[0].color.g, top[0].color.b, curHi);
    color::cycle3(top[1].color.r, top[1].color.g, top[1].color.b, curHi);

    
    
  //    top[1].colorCycle(curHi, 4);

    top[0].refresh();
    top[1].refresh();
    
    for (unsigned char i = 0; i < 4; i++)
      if (!cycles++) {
        base[0][0].colorCycle("rgb");
        base[0][1].colorCycle("rgb");
        base[1][0].colorCycle("rgb");
        base[1][1].colorCycle("rgb");
      }

   

  }

  void disable(){
    
  }
};



namespace pattern1 {
  bool initialized = false;

  // local variables
  bool curHi = 0;
  uint8_t cycles = 0, 
          activeLEDr = 0, 
          activeLEDb = 0, 
          activeLEDg = 0;

  
  void init(){

    resetLEDs();
    top[0].color.g = 0;
    top[1].color.g = 255;

    activeLEDr = activeLEDb = activeLEDg = 0;
    
    curHi = 0;

    cycles = 1;
  }
  
  // a local function
  inline void setLEDsValsZero(){
    top[0].color.r = 0;
    top[0].color.b = 0;
    top[1].color.r = 0;
    top[1].color.b = 0;
    
    base[0][0].setNull();
    base[0][1].setNull();
    base[1][0].setNull();
    base[1][1].setNull();
  }

  void periodic(){
    soundCheck();
    if (checkInput()) return;


    color::cycle2(top[0].color.g, top[1].color.g, curHi, 4);

    // cycle
    //for (unsigned char i = 0; i < 4; i++)
      if ((cycles++) == 0) {
        if (activeLEDr == 5)
          activeLEDr = 0;
        else
          activeLEDr++;

        if (activeLEDb == 5)
          activeLEDb = 0;
        else
          activeLEDb++;

        if (activeLEDg == 3)
          activeLEDg = 0;
        else
          activeLEDg++;
      }


    setLEDsValsZero();
    
    // blues:    
    switch (activeLEDb) {
      case 0: base[0][0].b = HIGH; break;
      case 1: base[0][1].b = HIGH; break;
      case 2: top[1].color.b = 255; break;      
      case 3: top[0].color.b = 255; break;      
      case 4: base[1][1].b = HIGH; break;
      case 5: base[1][0].b = HIGH; break;
    }

    // reds:
    switch (activeLEDb) {
      case 5: base[0][0].r = HIGH; break;
      case 4: base[0][1].r = HIGH; break;
      case 3: top[1].color.r = 255; break;
      case 2: top[0].color.r = 255; break;
      case 1: base[1][1].r = HIGH; break;
      case 0: base[1][0].r = HIGH; break;
    }

    // greens:
    switch (activeLEDg) {
      case 1: base[0][0].g = HIGH; break;
      case 0: base[0][1].g = HIGH; break;
      case 2: base[1][1].g = HIGH; break;
      case 3: base[1][0].g = HIGH; break;
    }
    
    refreshLEDs();
    
  }

  void disable(){}
};



namespace pattern2 {
  bool initialized = false;

  // local variables
  static uint8_t cycles = 0;
  
  void init(){
    top[0].set(Color(0, 0, 255));
    top[1].set(Color(0, 0, 255));
    base[0][0].set(0, 0, 255);
    base[0][1].set(0, 0, 255);
    base[1][0].set(0, 0, 255);
    base[1][1].set(0, 0, 255);

  }

  void periodic(){
    soundCheck(); 
    if (checkInput()) return;

  }

  void disable(){}
};

#endif


