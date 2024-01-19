#include <AFMotor.h>
#include <RH_ASK.h>
#include <SPI.h>

#define motor1PIN 1
#define motor2PIN 2
#define motor3PIN 3
#define motor4PIN 4
#define recPIN 16

AF_DCMotor motor1(motor1PIN); //top right
AF_DCMotor motor2(motor2PIN); //top left
AF_DCMotor motor3(motor3PIN); //back left
AF_DCMotor motor4(motor4PIN); //back right

void setup() {
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
