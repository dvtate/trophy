#ifndef PATTERNS_H
#define PATTERNS_H


// prototype functions to prevent errors
// these functions get defined later in the file
extern bool checkInput(void);
extern void pickNextPattern(void);
extern void soundCheck(void);
extern void resetLEDs(void);
extern void refreshLEDs(void);

#define NUMBER_OF_PATTERNS 4



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
    
    resetLEDs();
    soundCheck();
    if (checkInput()) return;
    
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

    // I should use the color cycle member function...
    color::cycle3(top[0].color.r, top[0].color.g, top[0].color.b, curHi);
    color::cycle3(top[1].color.r, top[1].color.g, top[1].color.b, curHi);
   

    top[0].refresh();
    top[1].refresh();

    // every 255/4 = 63.75 cycles switch color
    for (uint8_t i = 0; i < 4; i++)
      if ( ( cycles++ ) == 0 ) {
        base[0][0].colorCycle("rgb"); // boolean types don't need a static curHi
        base[0][1].colorCycle("rgb"); //  a static curHi
        base[1][0].colorCycle("rgb"); // this is good...
        base[1][1].colorCycle("rgb"); 
      }

   

  }

  void disable(){
    
  }
}


namespace pattern1 {
  bool initialized = false;

  // local variables
  bool curHi = 0;
  uint8_t cycles = 0;

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
      if ( ( cycles++ ) == 0 ) {

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
  bool initialized = false;

  // local variables
  uint8_t cycles = 0;
  

  // I don't like this solution...
  Color colors[6] {
       COLOR_RED, COLOR_YELLOW, COLOR_GREEN,
       COLOR_CYAN, COLOR_BLUE, COLOR_PURPLE//, COLOR_WHITE
  };

  struct {
      unsigned int activeLED : 3, colorNum : 3;
  } light;
  
  Color* currentColor;
  
  void init(){
    
    resetLEDs();
    soundCheck();
    if (checkInput()) return;

    light.activeLED = 0;
    light.colorNum = 0;
    currentColor = &colors[0];
  }

  void periodic(){
    soundCheck(); 
    if (checkInput()) return;

    for (unsigned char i = 0; i < 8; i++)
      if ( ( cycles++ ) == 0 )
        if (light.activeLED == 5) {
          
          light.activeLED = 0;
          
          if (light.colorNum == 5) // after each cycle change the color
            light.colorNum = 0;
          else 
            light.colorNum++;
  
          currentColor = &colors[light.colorNum];
          
        } else light.activeLED++;
      
   
    
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


// this doesn't work the way I wanted it to...
// but it stil looks good...
namespace pattern3 {
  
  bool initialized = false;
  uint8_t cycles = 0;

  uint8_t startColor = 0;
  uint8_t curColor = 0;
  
  bool reverse = false;

  DigitalTriLED &center0 = base[0][1], &center1 = base[1][1];

  Color colors[3] { COLOR_RED, COLOR_BLUE, COLOR_GREEN };
  
  void nullCorners(){
    top[0].setNull();
    top[1].setNull();
    base[0][0].setNull();
    base[1][0].setNull();
  }
  
  void pushCorners(const Color& clr){
    top[0].push(clr);
    top[1].push(clr);
    base[0][0].push(clr);
    base[1][0].push(clr);
  }

  void pmRed(){
    if (!reverse) {
      pushCorners(COLOR_RED);
      center0.r = HIGH;
      center1.r = HIGH;
    } else {
      pushCorners(COLOR_RED);
      center0.r = LOW;
      center1.r = LOW;
    }
  }
  void pmGreen(){
    if (!reverse) {
      pushCorners(COLOR_GREEN);
      center0.g = HIGH;
      center1.g = HIGH;
    } else {
      pushCorners(COLOR_GREEN);
      center0.g = LOW;
      center1.g = LOW;
    }
  }
  void pmBlue(){
    if (!reverse) {
      pushCorners(COLOR_BLUE);
      center0.b = HIGH;
      center1.b = HIGH;
    } else {
      pushCorners(COLOR_BLUE);
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
  
  }

  void periodic(){
    soundCheck(); 
    if (checkInput()) return;
    
    //for (unsigned char i = 0; i < 4; i++)
    if ( ( ++cycles ) == 0 ) {
      if (curColor == 2) {
        
        if (startColor == 2)
          startColor = 0;
        else 
          startColor++;

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

    // this is because I'm a dumbass...
    uint8_t temp = (((curColor + 1) == 3) ? 0 : curColor + 1);
    
    switch (startColor) {
    
    case 0: 
      switch (temp) {
        case 0: pmRed(); break;
        case 1: pmGreen(); break;
        case 2: pmBlue(); break;
      } break;
    case 1: 
      switch (temp) {
        case 0: pmGreen(); break;
        case 1: pmBlue(); break;
        case 2: pmRed(); break;
      } break;
    case 2: 
      switch (temp) {
        case 0: pmBlue(); break;
        case 1: pmRed(); break;
        case 2: pmGreen(); break;
      } break;
    }

    refreshLEDs();
  }
  
  void disable(){} // do nothing...

}


#endif
