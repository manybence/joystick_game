#include "game.h"

void setup() {

  //Configure pins
  pinMode(YELLOW_PIN, OUTPUT); 
  pinMode(GREEN_PIN, OUTPUT); 
  pinMode(RED_PIN, OUTPUT); 
  pinMode(BLUE_PIN, OUTPUT); 
  pinMode(SW_PIN, INPUT); 

  //Read high score
  highscore = EEPROM.read(0);
  String message = "HighScore: " + String(highscore);
  char messageArray[30];
  message.toCharArray(messageArray, message.length()+1);

  //Initialize LCD screen
  SmartLCD.init();  
  print_LCD("Szia Nikol! :)");
  print_LCD(messageArray, 1, false);
  int start = -1;
  while (start == -1) start = read_joystick();
  delay(150);

  //Reading noise to seed the random generator
  randomSeed(analogRead(A2)); 
}

void loop() {

  //Wait for player to start
  wait_to_start();

  //Generating new sequence
  if (result) new_sequence();

  //Show sequence of lights (directions)
  show_sequence();

  //Player repeats
  result = player_turn();

  //Restart the game
  if (loss_counter > 1) game_over(); 
}

