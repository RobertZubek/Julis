#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#include <AFMotor.h>
#include <Servo.h>


#define rtDelay(v) vTaskDelay(v/15)

#define servoPIN 9
#define motor1PIN 1
#define motor2PIN 2
#define motor3PIN 3
#define motor4PIN 4
#define triggerPIN A5
#define echoPIN A4

SemaphoreHandle_t binarySemaphore;

Servo servo;
AF_DCMotor motor1(motor1PIN); //top right
AF_DCMotor motor2(motor2PIN); //top left
AF_DCMotor motor3(motor3PIN); //back left
AF_DCMotor motor4(motor4PIN); //back right

int speed;

void setup() {
  
  servo.attach(servoPIN);

  xTaskCreate(run, "run", 128, NULL, 1, NULL);
  xTaskCreate(guard, "guard", 128, NULL, 1, NULL);

  binarySemaphore = xSemaphoreCreateBinary();
  xSemaphoreGive(binarySemaphore);

  pinMode(triggerPIN, OUTPUT);
  pinMode(echoPIN, INPUT);

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  for(speed=0;speed=255;speed++)
  {
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    motor3.setSpeed(speed);
    motor4.setSpeed(speed);
  }
}
void run(void*){

  speed=255;

  xSemaphoreTake(binarySemaphore, portMAX_DELAY);
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  xSemaphoreGive(binarySemaphore);
}


void guard(void*){
  
  long time;
  long distance;
  while(1){
    digitalWrite(triggerPIN, LOW);
    rtDelay(1);
    digitalWrite(triggerPIN, HIGH);
    rtdelay(2);
    digitalWrite(triggerPIN, LOW);

    time = pulseIn(echoPIN, HIGH);
    distance=time/29/2;
  }


void loop() {}






