#include <RCSwitch.h>
#define transPIN 13 //D5

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableTransmit(transPIN);

}

void loop() {
  mySwitch.send(1394007, 24);
  delay(1000);
  mySwitch.send(1394006, 24);
  delay(1000);

}
