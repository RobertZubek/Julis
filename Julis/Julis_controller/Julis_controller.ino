#include <RH_ASK.h>
#include <SPI.h>

#define upPIN 2//D4
#define downPIN 0//D3
#define leftPIN 5//D1
#define rightPIN 14//D7!!!!!!!!!!!!!!!!!!!do lutowanska
#define transPIN 13//D5

int msg;
//RH_ASK driver;

void setup() {

  Serial.begin(9600);
  pinMode(upPIN, INPUT_PULLUP);
  pinMode(downPIN, INPUT_PULLUP);
  pinMode(leftPIN, INPUT_PULLUP);
  pinMode(rightPIN, INPUT_PULLUP);
//  if (!driver.init()) {
//    Serial.println("RF driver init failed");
//  }

}

void loop() {

  if(digitalRead(upPIN)==LOW) msg = 1;
  else if(digitalRead(downPIN)==LOW) msg = 2;
  else if(digitalRead(leftPIN)==LOW) msg = 3;
  else if(digitalRead(rightPIN)==LOW) msg = 4;
  else msg = 5;

  Serial.println(msg);
 // driver.send(&msg, sizeof(msg));
  //driver.waitPacketSent();
  delay(1000);


}
