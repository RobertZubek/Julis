#include <Arduino_FreeRTOS.h>
#include <AFMotor.h>
#include <Servo.h>

#define servoPIN 9
#define motor1PIN 1
#define motor2PIN 2
#define motor3PIN 3
#define motor4PIN 4

Servo servo;
AF_DCMotor motor1(motor1PIN); 
AF_DCMotor motor2(motor2PIN); 
AF_DCMotor motor3(motor3PIN); 
AF_DCMotor motor4(motor4PIN); 

void setup() {
  servo.attach(servoPIN);
}

void loop() {}
