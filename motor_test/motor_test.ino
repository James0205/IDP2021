#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


Adafruit_MotorShield AFMS = Adafruit_MotorShield();


int moter_port = 3; // the moter port to test
Adafruit_DCMotor *myMotor = AFMS.getMotor(moter_port);





int speed = 100; // initial speed, don't matter much. Cuz could change any time later

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
    Serial.print("Engine Stopped. Speed: ");
    Serial.println(speed);
    myMotor->setSpeed(speed);
    myMotor->run(FORWARD);
  }
  else if(new_speed > 0){
    if (new_speed > 255){new_speed = 255;}
    speed = new_speed;
    Serial.print("New forward speed set at: ");
    Serial.println(speed);
    myMotor->setSpeed(speed);
    myMotor->run(FORWARD);
  }
  else if (new_speed < 0){
    if (new_speed < -255){new_speed = -255;}
    speed = -new_speed;
    Serial.print("New backward speed set at: ");
    Serial.println(speed);
    myMotor->setSpeed(speed);
    myMotor->run(BACKWARD);
  }
}
