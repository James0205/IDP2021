#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *myMotor = AFMS.getMotor(3);

int speed = 100;
void setup()
{
  
  AFMS.begin();
  Serial.begin(9600);
}

void loop()
{  
  int new_speed = Serial.parseInt();
  if (new_speed == -1000){
    speed = 0;
    Serial.println(speed);
    myMotor->setSpeed(speed);
    myMotor->run(FORWARD);
  }
  else if(new_speed > 0){
    if (new_speed > 255){new_speed = 255;}
    speed = new_speed;
    Serial.println(new_speed);
    myMotor->setSpeed(speed);
    myMotor->run(FORWARD);
  }
  else if (new_speed < 0){
    if (new_speed < -255){new_speed = -255;}
    speed = -new_speed;
    Serial.println(new_speed);
    myMotor->setSpeed(speed);
    myMotor->run(BACKWARD);
  }
}
