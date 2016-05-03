#include "Arduino.h"

#include "led.h"
#include "color.h" //already included by led.h
#include "ultrasonic.h" 

void setup(){
  Serial.begin(9600);
}

void loop(){


  // init with red on high
  static TriLED lys(13, 12, 11, Color(255,0,0));

  // cycle through rainbow
  lys.colorCycle(10);

  static Ultrasonic sonar(7);
  
  Serial.print("Dist =");
  Serial.print(sonar.getInches());//0~400cm
  Serial.println(" cm");
  delay(100);


}
