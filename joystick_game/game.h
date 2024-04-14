//Library for the joystick game

#include "SmartLCDI2C.h"      //Include the SmartLCD I2C Library
#define I2C_ADD 0x27          //I2C address of the Smart LCD
SmartLCD SmartLCD(I2C_ADD);   //Create an instance of the library

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin
#define RED_PIN 8 //Arduino pin of red LED
#define YELLOW_PIN 9 //Arduino pin of yellow LED
#define GREEN_PIN 10 //Arduino pin of green LED
#define BLUE_PIN 11 //Arduino pin of blue LED

int x = 0; // To store value of the X axis
int y = 0; // To store value of the Y axis
String direction = "";

String read_joystick() {

  String dir = "";

  // read analog X and Y values of joystick
  x = analogRead(VRX_PIN);
  y = analogRead(VRY_PIN);

  if (x < 200) dir = "up";
  else if (x > 800) dir = "down";
  else if (y > 800) dir = "left";
  else if (y < 200) dir = "right";

  return dir;
}

void light_up(String direction) {

  //Reset all leds
  digitalWrite(RED_PIN, false);
  digitalWrite(YELLOW_PIN, false);
  digitalWrite(GREEN_PIN, false);
  digitalWrite(BLUE_PIN, false);

  //Light up the given LED
  if (direction == "left") digitalWrite(RED_PIN, true);
  else if (direction == "right") digitalWrite(BLUE_PIN, true);
  else if (direction == "up") digitalWrite(YELLOW_PIN, true);
  else if (direction == "down") digitalWrite(GREEN_PIN, true);
}

void print_LCD() 
{
  SmartLCD.init();            //Initiliases the library
  SmartLCD.Clear();           //Clear the screen
  
  SmartLCD.CurPos(0, 2);      //Set the cursor to row 0 column 5
  SmartLCD.Print("Szia Nikol!");    //Print some text
  
  SmartLCD.CurPos(1, 0);      //Set the cursor to row 1 column 4
  SmartLCD.Print("Mehet a jatek?");  //Print some text
}