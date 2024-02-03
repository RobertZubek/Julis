#include <RH_ASK.h>
#include <SPI.h>

#define upPIN 2//D4
#define downPIN 0//D3
#define leftPIN 5//D1
#define rightPIN 14//D7!!!!!!!!!!!!!!!!!!!do lutowanska
#define transPIN 13//D5

char *msg;
RH_ASK driver;

void setup() {

  Serial.begin(9600);

  pinMode(upPIN, INPUT_PULLUP);
  pinMode(downPIN, INPUT_PULLUP);
  pinMode(leftPIN, INPUT_PULLUP);
  pinMode(rightPIN, INPUT_PULLUP);

  if (!driver.init()) {
    Serial.println("RF driver init failed");
  } 
}

void loop() {
  if (digitalRead(upPIN) == LOW) msg = "u";
  else if (digitalRead(downPIN) == LOW) msg = "d";
  else if (digitalRead(leftPIN) == LOW) msg = "l";
  else if (digitalRead(rightPIN) == LOW) msg = "r";
  else msg = "n";

  Serial.print("Button State: ");
  Serial.println(msg);

  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  delay(1000);
}

