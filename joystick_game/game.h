//Library for the joystick game

#include <EEPROM.h>
#include "SmartLCDI2C.h"      //Include the SmartLCD I2C Library
#define I2C_ADD 0x27          //I2C address of the Smart LCD
SmartLCD SmartLCD(I2C_ADD);   //Create an instance of the library

#define VRY_PIN  A0 // Arduino pin connected to Joystick VRY pin
#define VRX_PIN  A1 // Arduino pin connected to Joystick VRX pin
#define SW_PIN 7 //Joystick press pin

#define YELLOW_PIN 6 //Arduino pin of yellow LED
#define GREEN_PIN 3 //Arduino pin of green LED
#define RED_PIN 9 //Arduino pin of red LED
#define BLUE_PIN 5 //Arduino pin of blue LED

int counter = 4;
int seq[31];
bool result = true;
int loss_counter = 0;
int highscore = 0;


int read_joystick(){

  int dir = -1;
  while (dir == -1){
    // read analog X and Y values of joystick
    int x = analogRead(VRX_PIN);
    int y = analogRead(VRY_PIN);

    //Decide direction based on XY coordinates
    if (x < 200) dir = 1;       //Up
    else if (x > 800) dir = 0;  //Down
    else if (y > 800) dir = 2;  //Left
    else if (y < 200) dir = 3;  //Right
  }
  
  return dir;
}

void light_up(int direction){

  //Reset all leds
  digitalWrite(RED_PIN, false);
  digitalWrite(YELLOW_PIN, false);
  digitalWrite(GREEN_PIN, false);
  digitalWrite(BLUE_PIN, false);

  //Light up the given LED
  if (direction == 0) analogWrite(RED_PIN, 1);
  else if (direction == 1) analogWrite(BLUE_PIN, 1);
  else if (direction == 2) analogWrite(YELLOW_PIN, 50);
  else if (direction == 3) analogWrite(GREEN_PIN, 1);
}

void print_LCD(char *message, int row=0, bool clear=true){
  if (clear) SmartLCD.Clear();           //Clear the screen
  SmartLCD.CurPos(row, 0);      //Set the cursor to row 0 column 0
  SmartLCD.Print(message);    //Print the message
}

void show_sequence(){

  print_LCD("...");

  for (int i=0; i<counter; i++){
    int dir = seq[i];
    light_up(dir);
    delay(350);
    light_up(-1);
    delay(350);
  }

  print_LCD("Your turn!");
}

void new_sequence(){

  //Creating a sequence of random directions
  for (int i=0; i<counter; i++){
    int rand_dir = random(4);   //Select random colour
    seq[i] = rand_dir;
  }
}

bool player_turn(){

  //Read player input
  int counterPlayer = 0;
  while (counterPlayer < counter){
    int direction = read_joystick();
    light_up(direction);
    delay(300);
    light_up(-1);
    delay(300);
    if (seq[counterPlayer] != direction){
      break;
    }
    else{
      counterPlayer++;
    }
  }

  //Assess the round -> win/lose
  if (counterPlayer < counter){
    loss_counter++;
    if (loss_counter < 2){
      print_LCD("Meeeh you lost...");
      print_LCD("Try again!", 1, false);
      delay(1000);
    }
    return false;
  }
  else{
    print_LCD("Nice job!");
    print_LCD("Let's go higher!", 1, false);
    counter++;
    delay(1000);
    return true;
  }
}

void wait_to_start(){
  
  //Display message, round number
  String message = "Round " + String(counter);
  char messageArray[30];
  message.toCharArray(messageArray, message.length()+1);
  print_LCD(messageArray);
  print_LCD("Move to start!", 1, false);

  //Wait for input
  int start = -1;
  while (start == -1) start = read_joystick();
  delay(600);
}

void game_over(){

  int rainbow[] = {0, 2, 1, 3};

  //Store high score
  if (counter-1 > highscore){
    highscore = counter-1;
    EEPROM.write(0, highscore);
    print_LCD("New highscore :)");
    //Rainbow lights
    for (int i=0; i<16; i++){
      light_up(rainbow[i%4]);
      delay(100);
      light_up(-1);
      delay(100);
    }
  } 
  else {
    print_LCD("Game over :(");
    //Red lights
    for (int i=0; i<5; i++){
      light_up(0);
      delay(300);
      light_up(-1);
      delay(250);
    }
  }

  //Print score
  String message = "Score: " + String(counter-1);
  char messageArray[30];
  message.toCharArray(messageArray, message.length()+1);
  print_LCD(messageArray, 1, false);

  //Reset the game
  counter = 4;
  loss_counter = 0;
  result = true;
  int start = -1;
  delay(2000);
  while (start == -1) start = read_joystick();
}

