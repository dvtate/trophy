#ifndef PATTERN_H
#define PATTERN_H

#include "patterns.h"

#define NUMBER_OF_PATTERNS 3

uint8_t patternNumber = 0;



namespace patterns_common {
  // resets all of the functions...
  inline void uninitializeAll(){
    pattern0::initialized = false;
    pattern1::initialized = false;
    pattern2::initialized = false;
  }

};



// choose a different pattern
void pickNextPattern(){

  if (patternNumber < (NUMBER_OF_PATTERNS - 1))
    patternNumber++;
  else
    patternNumber = 0;



}

#define CALL_PATTERN(N) \
  if (!N::initialized) {\
        patterns_common::uninitializeAll();\
        N::initialized = true;\
        N::init();\
  } else {\
    N::periodic();\ 
  }


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
  }
}

#define KILL_PATTERN(N)\
  N::disable();\
  patterns_common::uninitializeAll();
  

void endPattern(uint8_t patNum){
  switch (patNum) {
  case 0:
    KILL_PATTERN(pattern0);
    break;
  case 1:
    KILL_PATTERN(pattern1);
    break;
  case 2:
    KILL_PATTERN(pattern2);
    break;
  }
}


#endif
