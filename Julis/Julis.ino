#include <Arduino_FreeRTOS.h>
#include <AFMotor.h>
#include <Servo.h>

#define rtDelay(v) vTaskDelay(v/15)

#define servoPIN 9
#define motor1PIN 1
#define motor2PIN 2
#define motor3PIN 3
#define motor4PIN 4

Servo servo;
AF_DCMotor motor1(motor1PIN); //top right
AF_DCMotor motor2(motor2PIN); //top left
AF_DCMotor motor3(motor3PIN); //back left
AF_DCMotor motor4(motor4PIN); //back right

void setup() {
  servo.attach(servoPIN);
  xTaskCreate(run, "run", 128, NULL, 1, NULL);
  xTaskCreate(guard, "guard", 128, NULL, 1, NULL);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  for(i=0;i<=255;i++)
  {
    motor1.setSpeed(i);
    motor2.setSpeed(i);
    motor3.setSpeed(i);
    motor4.setSpeed(i);
  }
}
void run(void*){

}


void guard(void*){

}



void loop() {}






