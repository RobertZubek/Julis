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

int state = 1;

Servo servo;
AF_DCMotor motor1(motor1PIN); //top right
AF_DCMotor motor2(motor2PIN); //top left
AF_DCMotor motor3(motor3PIN); //back left
AF_DCMotor motor4(motor4PIN); //back right

int speed;

void setup() {

  Serial.begin(9600);
  
  servo.attach(servoPIN);

  xTaskCreate(run, "run", 128, NULL, 0, NULL);
  xTaskCreate(guard, "guard", 128, NULL, 2, NULL);
  xTaskCreate(turnLeft, "turnLeft", 128, NULL, 1, NULL);
  xTaskCreate(turnRight, "turnRight", 128, NULL, 1, NULL);
  xTaskCreate(turn, "turn", 128, NULL, 1, NULL);

  binarySemaphore = xSemaphoreCreateBinary();
  xSemaphoreGive(binarySemaphore);

  pinMode(triggerPIN, OUTPUT);
  pinMode(echoPIN, INPUT);

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  for(speed=0;speed<=255;speed++)
  {
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    motor3.setSpeed(speed);
    motor4.setSpeed(speed);
  }
}
void run(void*){

  speed=255;

  while(1){
    if(state ==1){
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
  }
  }


void guard(void*){
  
  long distance;
  long distanceLeft;
  long distanceRight;
  while(1){
    
    distance=getDistance();
    Serial.println(distance);
    rtDelay(50);


    if(distance<=20){
      xSemaphoreTake(binarySemaphore, portMAX_DELAY);
      for(speed=255;speed>=0;speed--){
        motor1.setSpeed(speed);
        motor2.setSpeed(speed);
        motor3.setSpeed(speed);
        motor4.setSpeed(speed);
      }
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);

      servo.write(0);
      distanceRight=getDistance();
      rtDelay(250);

      servo.write(180);
      distanceLeft=getDistance();
      rtDelay(250);

      long diff;
      diff = distanceLeft-distanceRight;
      if(diff>0&&distanceLeft>=50){
        turnLeft();
        xSemaphoreGive(binarySemaphore);
        servo.write(90);
      }
      else if(diff<0&&distanceRight>=50){
        turnRight();
        xSemaphoreGive(binarySemaphore);
        servo.write(90);
      }
      else turn();
      xSemaphoreGive(binarySemaphore);
      servo.write(90);

    }


  }
}

void turn(void*)
{
  speed=255;

  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);

  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);

  rtDelay(2000);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

}

void turnRight(void*)
{
  speed=255;

  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);

  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);

  rtDelay(1000);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

}

void turnLeft(void*)
{
  speed=255;

  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);

  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);

  rtDelay(1000);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

}

long getDistance(void){
  long distance;
  long time;
  digitalWrite(triggerPIN, LOW);
  rtDelay(1);
  digitalWrite(triggerPIN, HIGH);
  rtDelay(2);
  digitalWrite(triggerPIN, LOW);

  time = pulseIn(echoPIN, HIGH);
  distance=time/29/2; //cm
  return distance;
}

void loop() {}






