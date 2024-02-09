#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#include <AFMotor.h>
#include <Servo.h>

#define rtDelay(v) vTaskDelay(v/15)

#define ledPIN 14
#define servoPIN 9
#define motor1PIN 1
#define motor2PIN 2
#define motor3PIN 3
#define motor4PIN 4
#define triggerPIN A5
#define echoPIN A4
#define echoPINhelping1 A3
#define echoPINhelping2 A1

SemaphoreHandle_t binarySemaphore;
Servo servo;
AF_DCMotor motor1(motor1PIN); //top right
AF_DCMotor motor2(motor2PIN); //top left
AF_DCMotor motor3(motor3PIN); //back left
AF_DCMotor motor4(motor4PIN); //back right

int state = 1;
int speed;

void setup() {

  Serial.begin(9600);
  
  servo.attach(servoPIN);

  xTaskCreate(run, "run", 128, NULL, 0, NULL);
  xTaskCreate(guard, "guard", 128, NULL, 2, NULL);
  

  binarySemaphore = xSemaphoreCreateBinary();
  xSemaphoreGive(binarySemaphore);

  pinMode(triggerPIN, OUTPUT);
  pinMode(echoPIN, INPUT);
  pinMode(echoPINhelping1, INPUT);
  pinMode(echoPINhelping2, INPUT);
  pinMode(ledPIN, OUTPUT);
  

}
void run(void*){

  

  while(1){
    Serial.println("RUN");
    speed=255;
    
    if(state==1){
      xSemaphoreTake(binarySemaphore, portMAX_DELAY);
      Serial.println("RUN GGGGGGGGGG");
      digitalWrite(ledPIN, HIGH);
      motor1.setSpeed(speed);
      motor2.setSpeed(speed);
      motor3.setSpeed(speed);
      motor4.setSpeed(speed);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      motor1.setSpeed(speed);
      motor2.setSpeed(speed);
      motor3.setSpeed(speed);
      motor4.setSpeed(speed);
      xSemaphoreGive(binarySemaphore);
    }
  }
}


void guard(void*){
  
  long distance;
  long distance1;
  long distance2;
  long distanceLeft;
  long distanceRight;
  while(1){
    
    distance=getDistance();
    distance1=getDistance1();
    distance2=getDistance2();
    
    rtDelay(50);


    if((distance<=40)||(distance1<=15)||(distance2<=15)){
      state=2;
      xSemaphoreTake(binarySemaphore, portMAX_DELAY);
      Serial.println("Chuj");
      //digitalWrite(ledPIN, LOW);
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
      //digitalWrite(ledPIN, HIGH);
      rtDelay(1000);
      //digitalWrite(ledPIN, LOW);
      distanceRight=getDistance();
      rtDelay(250);

      servo.write(180);
      //digitalWrite(ledPIN, HIGH);
      rtDelay(1000);
      //digitalWrite(ledPIN, LOW);
      distanceLeft=getDistance();
      rtDelay(250);

      long diff;
      diff = distanceLeft-distanceRight;
      if(diff>0&&distanceLeft>=70){
        digitalWrite(ledPIN, HIGH);

        motor1.setSpeed(speed);
        motor2.setSpeed(speed);
        motor3.setSpeed(speed);
        motor4.setSpeed(speed);

        motor1.run(FORWARD);
        motor2.run(BACKWARD);
        motor3.run(BACKWARD);
        motor4.run(FORWARD);

        rtDelay(500);

        motor1.run(RELEASE);
        motor2.run(RELEASE);
        motor3.run(RELEASE);
        motor4.run(RELEASE);
        servo.write(90);
        rtDelay(1100);
      }
      else if(diff<0&&distanceRight>=70){
        speed=255;
        

        //digitalWrite(ledPIN, HIGH);

        motor1.setSpeed(speed);
        motor2.setSpeed(speed);
        motor3.setSpeed(speed);
        motor4.setSpeed(speed);

        motor1.run(BACKWARD);
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(BACKWARD);

        rtDelay(500);

        motor1.run(RELEASE);
        motor2.run(RELEASE);
        motor3.run(RELEASE);
        motor4.run(RELEASE);
        servo.write(90);
        rtDelay(1100);
      }
      else {
        //digitalWrite(ledPIN, HIGH);

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
      }//turn
      xSemaphoreGive(binarySemaphore);
      servo.write(90);
      state=1;
    }
  }
}
/*
void turn(void*)
{
  while(1){
    if(state==3){
      speed=255;
      xSemaphoreTake(binarySemaphore, portMAX_DELAY);

      digitalWrite(ledPIN, HIGH);

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
      state=0;

      xSemaphoreGive(binarySemaphore);
    }
  }
}

void turnRight(void*)
{
  while(1){
    if(state==2){
      speed=255;
      xSemaphoreTake(binarySemaphore, portMAX_DELAY);

      digitalWrite(ledPIN, HIGH);

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
      state=0;
      xSemaphoreGive(binarySemaphore);
    }
  }
}

void turnLeft(void*)
{
  while(1){
    if(state==1){
      speed=255;
      xSemaphoreTake(binarySemaphore, portMAX_DELAY);

      digitalWrite(ledPIN, HIGH);

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
      state=0;
      xSemaphoreGive(binarySemaphore);
    }
  }
}

void control(void*)
{
  while(1){
    Serial.println(state);
    rtDelay(150);
  }
}
*/
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
long getDistance1(void){
  long distance;
  long time;
  digitalWrite(triggerPIN, LOW);
  rtDelay(1);
  digitalWrite(triggerPIN, HIGH);
  rtDelay(2);
  digitalWrite(triggerPIN, LOW);

  time = pulseIn(echoPINhelping1, HIGH);
  distance=time/29/2; //cm
  return distance;
}
long getDistance2(void){
  long distance;
  long time;
  digitalWrite(triggerPIN, LOW);
  rtDelay(1);
  digitalWrite(triggerPIN, HIGH);
  rtDelay(2);
  digitalWrite(triggerPIN, LOW);

  time = pulseIn(echoPINhelping2, HIGH);
  distance=time/29/2; //cm
  return distance;
}

void loop() {}