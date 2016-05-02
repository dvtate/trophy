#include "Arduino.h"

#include "led.h"
#include "color.h" //already included by led.h


void setup(){}

void loop(){

  // init with red on high
  static TriLED lys(13, 12, 11, Color(255,0,0));

  // cycle through rainbow
  lys.colorCycle();

  delay(10);
}
