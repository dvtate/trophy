#ifndef PATTERN_H
#define PATTERN_H

#include "patterns.h"


uint8_t patternNumber = 0;

extern bool checkInput();
extern void soundCheck();


namespace patterns_common {
  // resets all of the functions...
  inline void uninitializeAll(){
    pattern0::initialized = false;
    pattern1::initialized = false;
    pattern2::initialized = false;
  }

};



#define CALL_PATTERN(N) \
  if (!N::initialized) {\
        patterns_common::uninitializeAll();\
        N::initialized = true;\
        N::init();\
  } else {\
    N::periodic();\ 
  }


inline void callPattern(const uint8_t& patNum){
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
  

inline void endPattern(const uint8_t& patNum){
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



// choose a different pattern
void pickNextPattern(){

  endPattern(patternNumber);

  if (patternNumber < (NUMBER_OF_PATTERNS - 1))
    patternNumber++;
  else
    patternNumber = 0;



}


#endif
