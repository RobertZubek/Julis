#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(14);
}

void loop() {

  
  mySwitch.send("000000000001010100010001");
  delay(500);  
  mySwitch.send("000000000001010100010100");
  delay(500);

}
