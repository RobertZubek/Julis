#include <RH_ASK.h>
#include <SPI.h>

#define upPIN 2//D4
#define downPIN 0//D3
#define leftPIN 5//D1
#define rightPIN 15//D8
#define transPIN 14//D5

uint8_t msg;
RH_ASK driver;

void setup() {

  pinMode(upPIN, INPUT_PULLUP);
  pinMode(downPIN, INPUT_PULLUP);
  pinMode(leftPIN, INPUT_PULLUP);
  pinMode(rightPIN, INPUT_PULLUP);

}

void loop() {

  if(digitalRead(upPIN)==LOW) msg = 1;
  else if(digitalRead(downPIN)==LOW) msg = 2;
  else if(digitalRead(leftPIN)==LOW) msg = 3;
  else if(digitalRead(rightPIN)==LOW) msg = 4;
  else msg = 5;

  driver.send((uint8_t *)msg, 8);
  driver.waitPacketSent();
  delay(1000);


}
