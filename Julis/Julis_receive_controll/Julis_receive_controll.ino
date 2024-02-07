#include <RCSwitch.h>
#include <AFMotor.h>

#define motor1PIN 1
#define motor2PIN 2
#define motor3PIN 3
#define motor4PIN 4

RCSwitch mySwitch = RCSwitch();

AF_DCMotor motor1(motor1PIN); //top right
AF_DCMotor motor2(motor2PIN); //top left
AF_DCMotor motor3(motor3PIN); //back left
AF_DCMotor motor4(motor4PIN); //back right



void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

void loop() {
  
  Serial.println(mySwitch.getReceivedValue());
 

  int speed=255;
  if(mySwitch.getReceivedValue()==5)
  {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    
  }
  else if(mySwitch.getReceivedValue()==1)
  {
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    motor3.setSpeed(speed);
    motor4.setSpeed(speed);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    
  }
  else if(mySwitch.getReceivedValue()==2)
  {
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    motor3.setSpeed(speed);
    motor4.setSpeed(speed);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    
  }
  else if(mySwitch.getReceivedValue()==3)
  {
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    motor3.setSpeed(speed);
    motor4.setSpeed(speed);
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
    
  }
  else if(mySwitch.getReceivedValue()==4)
  {
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    motor3.setSpeed(speed);
    motor4.setSpeed(speed);
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
    
  }
  else
  {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    
  }
}
