#include <Arduino_FreeRTOS.h>
//#include <AFMotor.h>
#include <Servo.h>
#define servoPIN 9

Servo servo; 



void setup() {
  servo.attach(servoPIN);
}

void loop() {}
