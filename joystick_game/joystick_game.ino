#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

int x = 0; // To store value of the X axis
int y = 0; // To store value of the Y axis
String direction = "";

void setup() {
  Serial.begin(9600) ;
}

void loop() {
  // read analog X and Y analog values
  x = analogRead(VRX_PIN);
  y = analogRead(VRY_PIN);

  if (x < 200) direction = "up";
  else if (x > 800) direction = "down";
  else if (y > 800) direction = "left";
  else if (y < 200) direction = "right";

  // print data to Serial Monitor on Arduino IDE
  Serial.print(direction = ");
  Serial.println(direction);
  delay(200);

  // Reset direction
  direction = ""
}

