#include <Servo.h> 

Servo myservo;

int servo_port = 9; // inner one, brown out
int angle = 20;

void setup() 
{ 
    Serial.begin(9600);
  myservo.attach(servo_port);
} 

void loop() 
{
  int new_angle = Serial.parseInt();
 if(new_angle != 0){
    if (new_angle > 180){new_angle = 180;}
    else if (new_angle < 0){new_angle = 0;}
    angle = new_angle;
    Serial.print("New angle set at: ");
    Serial.println(new_angle);
    myservo.write(new_angle);
 }
}
