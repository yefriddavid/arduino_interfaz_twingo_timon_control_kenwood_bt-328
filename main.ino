// By: Rutger de Graaf
// 06-10-2018
 
#include "Keyboard.h"
 
// buttons[i][0] = minTrigger,
// buttons[i][1] = maxTrigger,
// buttons[i][2] = funcType(1=pinOut or 2=Usb),
// buttons[i][3] = funcValue(pinout or ascii),
const int buttons[][4] = {
  {880, 940, 2, 77}, //phone    905 m 
  {790, 860, 2, 66}, //source   810 b 
  {651, 780, 2, 86}, //down     685 v 
  {450, 650, 2, 78}, //up       530 n 
  {270, 440, 1, 2},  //vol_u    355   
  {80, 260, 1, 3},   //vol_d    140   
};
const int analogInPin = A0;  // Analog input pin that the stepped resistor circuit is attached to
 
int x = 0;                //value read from the pot
int i;                    //button loop-counter
int c = 0;                //button streak-counter
boolean found = false;    //global counter-stop
int v = 4;                //verify necessary detection length in loops to press button
int vr = 4;               //verify necessary detection length in loops to release button
int d = 10;               //check-loop duration in ms
 
int d2 = 10;              //button-hold-loop duration in ms
int pressed = false;      //loop break condition for holding the button
 
void setup() {
  //initialize serial communications at 9600 bps
  Serial.begin(9600);
  //set pinout types
  int j;
  for(j = 0; j <= 5; j = j + 1) {
    //if button type is pinOut
    if(buttons[j][2] == 1) {
      //enable that pin as output
      pinMode(buttons[j][3], OUTPUT);
    }
  }
  Keyboard.begin();
}
 
void loop() {
  //read the analog in value and print to serial
  x = analogRead(analogInPin);
  Serial.println(x);
 
  //loop through all possible buttons
  for(i = 0; i <= 5; i = i + 1) {
    //if this button is not detected: skip to next iteration
    if(x <= buttons[i][0] || x >= buttons[i][1]) {
      continue;
    }
    //button is detected
    Serial.print("button detected for value ");
    Serial.print(x);
    c = c + 1;
    Serial.print(", c = ");
    Serial.println(c);
    //if button is not detected enough times: break
    if(c < v) {
      break;
    }
    //send button press event
    buttonPress(i);
    c = 0;
    break;
  }
  
  //delay next read
  delay(d);
}
 
void buttonPress(int i){
  Serial.print("going to send press for button int ");
  Serial.println(i);
  if(buttons[i][2] == 1) {
    Serial.println("sending gpio");
    buttonGpio(i);
  }
  if(buttons[i][2] == 2) {
    Serial.println("sending usb");
    buttonUsb(i);
  }
}
 
void buttonGpio(int i) {
  int pinOut = buttons[i][3];
  c = 0;
  Serial.print("pressed gpio button ");
  Serial.println(pinOut);
  digitalWrite(pinOut, HIGH);
  pressed = true;
  while(pressed) {
    x = analogRead(analogInPin);
    if(x <= buttons[i][0] || x >= buttons[i][1]) {
      Serial.print("Outvalue detected: ");
      Serial.println(x);
      c = c + 1;
    } else {
      c = 0;
    }
    if(c >= vr) {
      pressed = false;
    }
    delay(d2);
  }
  digitalWrite(pinOut, LOW);
  Serial.print("released gpio button ");
  Serial.println(pinOut);
}
 
void buttonUsb(int i) {
  Keyboard.begin();
  int ascii = buttons[i][3];
  c = 0;
  Serial.print("pressed usb button ");
  Serial.println(ascii);
  Keyboard.press(ascii);
  pressed = true;
  while(pressed) {
    x = analogRead(analogInPin);
    if(x <= buttons[i][0] || x >= buttons[i][1]) {
      Serial.print("Outvalue detected: ");
      Serial.println(x);
      c = c + 1;
    } else {
      c = 0;
    }
    if(c >= vr) {
      pressed = false;
    }
    delay(d2);
  }
  Keyboard.release(ascii);
  Serial.print("released usb button ");
  Serial.println(ascii);
}
