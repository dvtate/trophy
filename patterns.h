#ifndef PATTERNS_H
#define PATTERNS_H


// prototype functions to prevent errors
// these functions get defined later in the file
extern bool checkInput(void);
extern void pickNextPattern(void);
extern void soundCheck(void);
extern void resetLEDs(void);
extern void refreshLEDs(void);


#define NUMBER_OF_PATTERNS 7     // edit when changed...

// defined in pattern.h
namespace patterns_common {
  extern DigitalColor colors[8];
}


namespace examplePattern {

  // called once before periodic begins
  void init (){

    soundCheck(); // should be called before checkInput();
    if(checkInput()) return;

    // init code here...
  }

  // cycled, continuously run
  void periodic(){

    // these must be called at least once.
    soundCheck();
    if(checkInput()) return; // NOTE: this delays 4 or 8 miliseconds

  }

  // called before ending this pattern
  void disable(){ }

}


namespace pattern0 {
  /// color cycle everything
  // local variables
  uint8_t cycles, curHi;

  void init(){

    // pre-checks
    resetLEDs();
    soundCheck();
    if (checkInput()) return;

    // reset variables
    cycles = 0;
    curHi = 0;

    // set LEDs to red
    top[0].set(Color(255, 0, 0));
    top[1].set(Color(255, 0, 0));
    base[0][0].set(255, 0, 0);
    base[0][1].set(255, 0, 0);
    base[1][0].set(255, 0, 0);
    base[1][1].set(255, 0, 0);

    //Serial.println("pattern0");
  }

  void periodic(){

    soundCheck();
    if (checkInput()) return;

    top[0].colorCycle(curHi, 4);
    top[1].colorCycle(curHi, 4);

    // every 255/4 = 63.75 cycles switch color
    for (uint8_t i = 0; i < 4; i++) // runs 4x faster
      if ( ( ++cycles ) == 0 ) {
        base[0][0].colorCycle("rgb"); // boolean types don't need a static curHi
        base[0][1].colorCycle("rgb"); //  a static curHi...
        base[1][0].colorCycle("rgb"); // this is good :D
        base[1][1].colorCycle("rgb");
      }

  }

  void disable(){
    // there's nothing to do here...
  }
}


namespace pattern1 {
  /// explaining this will take too much text...
  
  
  // local variables
  bool curHi;
  uint8_t cycles;

  struct {
    unsigned int r : 3, g : 3;
  } activeLED;

  void init(){

    resetLEDs();
    soundCheck();
    if (checkInput()) return;

    top[0].color.g = 0;
    top[1].color.g = 255;

    activeLED.r = activeLED.g = 0;

    curHi = 0;

    cycles = 0;
    //Serial.println("pattern1");
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
    for (bool i = true; i; i = !i) // runs 2x
      if ( ( ++cycles ) == 0 ) {

        // the greens :D
        if (activeLED.g == 3)
          activeLED.g = 0;
        else
          activeLED.g++;

        //the reds (and those pesky blues)...
        if (activeLED.r == 5)
          activeLED.r = 0;
        else
          activeLED.r++;

      }


    // this sets the values to 0 without writing to the lights
    // we will tell which lights to turn on.
    setLEDsValsZero();


    // greens:
    switch (activeLED.g) {
      case 0: base[0][0].g = HIGH; break;
      case 1: base[0][1].g = HIGH; break;
      case 2: base[1][1].g = HIGH; break;
      case 3: base[1][0].g = HIGH; break;
    }


    // reds:
    switch (activeLED.r) {
      case 5: base[0][0].r = HIGH; break;
      case 4: base[0][1].r = HIGH; break;
      case 3: top[1].color.r = 255; break;
      case 2: top[0].color.r = 255; break;
      case 1: base[1][1].r = HIGH; break;
      case 0: base[1][0].r = HIGH; break;
    }


    // blues:
    switch (activeLED.r) {
      case 0: base[0][0].b = HIGH; break;
      case 1: base[0][1].b = HIGH; break;
      case 2: top[1].color.b = 255; break;
      case 3: top[0].color.b = 255; break;
      case 4: base[1][1].b = HIGH; break;
      case 5: base[1][0].b = HIGH; break;
    }

    refreshLEDs();

  }

  void disable(){}
}


namespace pattern2 {
  /// whirlpool effect where the lights change color as they 
  /// circle around
  
  // local variables
  uint8_t cycles;


  struct {
      unsigned int activeLED : 3, colorNum : 3;
  } light;

  DigitalColor* currentColor;

  void init(){

    resetLEDs();
    soundCheck();
    if (checkInput()) return;

    light.activeLED = 0;
    light.colorNum = 0;
    currentColor = &patterns_common::colors[0];
    //Serial.println("pattern2");
  }

  void periodic(){
    soundCheck();
    if (checkInput()) return;

    for (unsigned char i = 0; i < 10; i++) // runs 8x faster
      if ( ( ++cycles ) == 0 )
        if (light.activeLED == 5) {

          light.activeLED = 0;

          if (light.colorNum == 5) // after each cycle change the color
            light.colorNum = 0;
          else
            light.colorNum++;

          currentColor = &patterns_common::colors[light.colorNum];

        } else {
          light.activeLED++;
        }


    switch (light.activeLED) {
      case 0: base[0][0].set(*currentColor); break;
      case 1: base[0][1].set(*currentColor); break;
      case 2: top[1].set(*currentColor); break;
      case 3: top[0].set(*currentColor); break;
      case 4: base[1][1].set(*currentColor); break;
      case 5: base[1][0].set(*currentColor); break;
    }


  }

  void disable(){}
}

namespace pattern3 {
  // this doesn't work the way I wanted it to...
  // but it stil looks good...

  uint8_t cycles, startColor, curColor;
  bool reverse;

  DigitalTriLED &center0 = base[0][1], &center1 = base[1][1];

  void nullCorners(){
    top[0].setNull();
    top[1].setNull();
    base[0][0].setNull();
    base[1][0].setNull();
  }
  void pushCorners(const DigitalColor& clr){
    top[0].push(clr);
    top[1].push(clr);
    base[0][0].push(clr);
    base[1][0].push(clr);
  }

  void pmRed(){
    if (!reverse) {
      pushCorners(D_COLOR_RED);
      center0.r = HIGH;
      center1.r = HIGH;
    } else {
      pushCorners(D_COLOR_RED);
      center0.r = LOW;
      center1.r = LOW;
    }
  }
  void pmGreen(){
    if (!reverse) {
      pushCorners(D_COLOR_GREEN);
      center0.g = HIGH;
      center1.g = HIGH;
    } else {
      pushCorners(D_COLOR_GREEN);
      center0.g = LOW;
      center1.g = LOW;
    }
  }
  void pmBlue(){
    if (!reverse) {
      pushCorners(D_COLOR_BLUE);
      center0.b = HIGH;
      center1.b = HIGH;
    } else {
      pushCorners(D_COLOR_BLUE);
      center0.b = LOW;
      center1.b = LOW;
    }
  }
  void init(){
    resetLEDs();
    soundCheck();
    if (checkInput()) return;


    cycles = 0;
    startColor = 0;
    curColor = 0;
    reverse = false;

    //Serial.println("pattern3");
  }

  void periodic(){

    soundCheck();
    if (checkInput()) return;

    for (unsigned char i = 0; i < 4; i++) // runs 4x faster
      if ( ( ++cycles ) == 0 ) {
        if (curColor == 2) {

          if (startColor == 2)
            startColor = 0;
          else
            startColor++;
            curColor = 0;
            reverse = !reverse;
        } else {
          curColor++;
        }

      }

    nullCorners();

    // I don't know what I was thinking... SMH
    switch (startColor) {
    case 0:
      switch (curColor) {
        case 0: pmRed(); break;
        case 1: pmGreen(); break;
        case 2: pmBlue(); break;
      }
      break;
    case 1:
      switch (curColor) {
        case 0: pmGreen(); break;
        case 1: pmBlue(); break;
        case 2: pmRed(); break;
      }
      break;
    case 2:
      switch (curColor) {
        case 0: pmBlue(); break;
        case 1: pmRed(); break;
        case 2: pmGreen(); break;
      }
      break;

    }

    refreshLEDs();
  }

  void disable(){} // do nothing...

}


namespace pattern4 {
  // color selection goes from one side to the other
  // resulting in a line of different colors
  uint8_t cycles, offset;

  void init(){
    resetLEDs();
    soundCheck();
    if (checkInput()) return;

    // apply initial colors
    base[0][0].set(patterns_common::colors[0]);
    base[0][1].set(patterns_common::colors[1]);
    top[1].set(patterns_common::colors[2]);

    top[0].set(patterns_common::colors[3]);
    base[1][1].set(patterns_common::colors[4]);
    base[1][0].set(patterns_common::colors[5]);

    cycles = 0;
    offset = 0;
    //Serial.println("pattern4");
  }

  void periodic(){
    soundCheck();
    if (checkInput()) return;

    for (unsigned char i = 0; i < 4; i++) // runs 4x faster
      if ( ( cycles++ ) == 0 ) {
        base[0][0].set(patterns_common::colors[offset % 8]);
        base[0][1].set(patterns_common::colors[(offset + 1) % 8]);
        top[1].set(patterns_common::colors[(offset + 2) % 8]);

        top[0].set(patterns_common::colors[(offset + 3) % 8]);
        base[1][1].set(patterns_common::colors[(offset + 4) % 8]);
        base[1][0].set(patterns_common::colors[(offset + 5) % 8]);
        offset++;
      }
  }

  void disable(){}
}

namespace pattern5 {
  // rgb version of pattern 4
  uint8_t cycles = 0;

  void init(){
    resetLEDs();
    soundCheck();
    if (checkInput()) return;

    base[0][0].set(255, 0, 0);
    base[0][1].set(0, 255, 0);
    top[1].color.set(0, 0, 255);

    top[0].color.set(255, 0, 0);
    base[1][1].set(0, 255, 0);
    base[1][0].set(0, 0, 255);

    //Serial.println("pattern5");

  }

  void periodic(){
    soundCheck();
    if (checkInput()) return;

    for (unsigned char i = 0; i < 3; i++) // runs 3x faster
      if ( ( cycles++ ) == 0 ) {
        base[0][0].colorCycle("rgb");
        base[0][1].colorCycle("gbr");
        top[1].digitalColorCycle("brg");
        top[0].digitalColorCycle("rgb");
        base[1][1].colorCycle("gbr");
        base[1][0].colorCycle("brg");
      }

  }

  void disable(){}
}

namespace pattern6 {
  /// color waves that go back and fourth switching colors each time


  uint8_t cycles;

  struct {
    unsigned int  color : 3,
                  phase : 3;
  } data;
  
  
  
  void init(){
    resetLEDs();
    soundCheck();
    if (checkInput()) return;


    cycles = data.phase = 0;
    // NOTE: I didn't reset data.color because I want it to be
    //       less predictable.
  }

  void periodic(){
    soundCheck();
    if (checkInput()) return;

    // this nesting is ugly
    for (unsigned char i = 0; i < 4; i++) // runs 4x quicker
      if ( ( ++cycles ) == 0 ) {
        if (data.phase == 5)
          data.phase = 0;
        else
          data.phase++;

        
        switch (data.phase) {

        case 0: // bottom 2
          base[0][0].setColor(patterns_common::colors[data.color]);
          base[1][0].setColor(patterns_common::colors[data.color]);
          break;

        case 1: // bottom 4
          base[0][0].setColor(patterns_common::colors[data.color]);
          base[0][1].setColor(patterns_common::colors[data.color]);
          base[1][0].setColor(patterns_common::colors[data.color]);
          base[1][1].setColor(patterns_common::colors[data.color]);
          break;

        case 2: case 5: // all HIGH
          base[0][0].setColor(patterns_common::colors[data.color]);
          base[0][1].setColor(patterns_common::colors[data.color]);
          base[1][0].setColor(patterns_common::colors[data.color]);
          base[1][1].setColor(patterns_common::colors[data.color]);
          top[0].setColor(patterns_common::colors[data.color]);
          top[1].setColor(patterns_common::colors[data.color]);

          // pick next color to write
          // not random, but close enough :T
          for (uint8_t i = 0; i < 6; i++)
            if (data.color == 7) data.color = 0;
            else data.color++;

          break;

        case 3: // top 2
          top[0].setColor(patterns_common::colors[data.color]);
          top[1].setColor(patterns_common::colors[data.color]);
          break;

        case 4: // top 4
          top[0].setColor(patterns_common::colors[data.color]);
          top[1].setColor(patterns_common::colors[data.color]);
          base[0][1].setColor(patterns_common::colors[data.color]);
          base[1][1].setColor(patterns_common::colors[data.color]);
          break;

        }
      }
  }

  void disable(){}
}
#endif
