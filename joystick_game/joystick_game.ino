#include "game.h"

void setup() {
  Serial.begin(9600) ;
}

void loop() {
  //Show sequence
  //TODO

  // Read analog X and Y analog values
  direction = read_joystick();

  //Display direction LED
  light_up(direction);
  delay(200);
  light_up("");
}

