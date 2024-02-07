#include <RCSwitch.h>

#define upPIN 2//D4
#define downPIN 0//D3
#define leftPIN 5//D1
#define rightPIN 13//D7!!!!!!!!!!!!!!!!!!!do lutowanska

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(14);
  pinMode(upPIN, INPUT_PULLUP);
  pinMode(downPIN, INPUT_PULLUP);
  pinMode(leftPIN, INPUT_PULLUP);
  pinMode(rightPIN, INPUT_PULLUP);
}

void loop() {

  if (digitalRead(upPIN) == LOW) {mySwitch.send("000000000000000000000001");}
  else if (digitalRead(downPIN) == LOW) {mySwitch.send("000000000000000000000010");}
  else if (digitalRead(leftPIN) == LOW) {mySwitch.send("000000000000000000000011");}
  else if (digitalRead(rightPIN) == LOW) {mySwitch.send("000000000000000000000100");}
  else {mySwitch.send("000000000000000000000101");}
  delay(600);
/*
  mySwitch.send("000000000001010100010001");
  delay(500);  
  mySwitch.send("000000000001010100010100");
  delay(500);*/

}
