#ifndef PATTERN_H
#define PATTERN_H

#include "patterns.h"


uint8_t patternNumber = 0;

// these are defined elsewhere.
extern bool checkInput();
extern void soundCheck();


// some things are most efficient to be defined once for
// all the patterns instead of being declared and defined
// multiple times as each pattern needs it.
namespace patterns_common {

  DigitalColor colors[8] {
    D_COLOR_RED, D_COLOR_YELLOW, D_COLOR_GREEN, D_COLOR_CYAN,
    D_COLOR_BLUE, D_COLOR_PURPLE, D_COLOR_WHITE, D_COLOR_OFF
  };

  bool initialized = false;

}


// takes a namespace as a parameter :P
#define CALL_PATTERN(N) \
  if (!patterns_common::initialized) {\
    patterns_common::initialized = true;\
    N::init();\
  } else {\
    N::periodic();\
  }

// initialize once and then call pattern::periodic()
void callPattern(uint8_t patNum){
  switch (patNum) {
  case 0:
    CALL_PATTERN(pattern0);
    break;
  case 1:
    CALL_PATTERN(pattern1);
    break;
  case 2:
    CALL_PATTERN(pattern2);
    break;
  case 3:
    CALL_PATTERN(pattern3);
    break;
  case 4:
    CALL_PATTERN(pattern4);
    break;
  case 5:
    CALL_PATTERN(pattern5);
    break;
  case 6:
    CALL_PATTERN(pattern6);
    break;
  }
}

// clean up after each pattern
void endPattern(uint8_t patNum){
  switch (patNum) {
  case 0:
    pattern0::disable();
    break;
  case 1:
    pattern1::disable();
    break;
  case 2:
    pattern2::disable();
    break;
  case 3:
    pattern3::disable();
    break;
  case 4:
    pattern4::disable();
    break;
  case 5:
    pattern5::disable();
    break;
  case 6:
    pattern6::disable();
    break;
  }

  patterns_common::initialized = false;
  resetLEDs();
}


// choose a different pattern
inline void pickNextPattern(){

  endPattern(patternNumber);

  if (patternNumber < (NUMBER_OF_PATTERNS - 1))
    patternNumber++;
  else
    patternNumber = 0;
}

#endif
