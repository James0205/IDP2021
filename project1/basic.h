#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

const float left_white = 44, left_black = 570; // should be raw data (0 - 1023)
const float right_white = 520, right_black = 576;


Adafruit_MotorShield AFMS = Adafruit_MotorShield();

const int red_LED_port = 9, button_port = 12, green_LED_port = 10, yellow_LED_port = 8;

const int trigPin = 1; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 2; // Echo Pin of Ultrasonic Sensor

unsigned long US_time_out = 6000;
const int left_motor_port = 3, right_motor_port = 4;

Adafruit_DCMotor *L_Motor = AFMS.getMotor(left_motor_port);
Adafruit_DCMotor *R_Motor = AFMS.getMotor(right_motor_port);


const int left_light_sensor_port = A2, right_light_sensor_port = A1; 

  
void run(int left_speed, int right_speed)
{
  left_speed = (float)left_speed * 0.9;
  if (left_speed == -1000 || left_speed == 1000) {}
  else if (left_speed >= 0){
    if (left_speed > 255){left_speed = 255;}
    L_Motor->setSpeed(left_speed);
    L_Motor->run(FORWARD);
  }
  else if (left_speed < 0){
    if (left_speed < -255){left_speed = 255;}
    L_Motor->setSpeed(-left_speed);
    L_Motor->run(BACKWARD);
  }
  
  if (right_speed == -1000 || right_speed == 1000) {}
  else if (right_speed >= 0){
    if (right_speed > 255){right_speed = 255;}
    R_Motor->setSpeed(right_speed);
    R_Motor->run(FORWARD);
  }
  else if (right_speed < 0){
    if (right_speed < -255){right_speed = 255;}
    R_Motor->setSpeed(-right_speed);
    R_Motor->run(BACKWARD);
  }
  
}

float LS_L_r(){
  float voltage = analogRead(left_light_sensor_port);
  return voltage;
}

float LS_R_r(){
  float voltage = analogRead(right_light_sensor_port);
  return voltage;
}

float LS_L_v(){
  float voltage = analogRead(left_light_sensor_port) * 5.0 / 1023.0;
  return voltage;
}

float LS_R_v(){
  float voltage = analogRead(right_light_sensor_port) * 5.0 / 1023.0;
  return voltage;
}

float map_n(float x, float in_min, float in_max, float out_min, float out_max) {
  float result = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  return result;
}

int button(){
  Serial.println(digitalRead(button_port));
  return digitalRead(button_port);
}

void red_LED(int value){
  if (value == 0) {digitalWrite(red_LED_port, LOW);}
  else if (value == 1){digitalWrite(red_LED_port, HIGH);}
}

void red_blink(int t){
  red_LED(1);
  delay(t);
  red_LED(0);
}

void green_LED(int value){
  if (value == 0) {digitalWrite(green_LED_port, LOW);}
  else if (value == 1){digitalWrite(green_LED_port, HIGH);}
}

void green_blink(int t){
  green_LED(1);
  delay(t);
  green_LED(0);
}

void gr_LED(int value){
  if (value == 0) {digitalWrite(red_LED_port, LOW);digitalWrite(green_LED_port, LOW);}
  else if (value == 1){digitalWrite(red_LED_port, HIGH);digitalWrite(red_LED_port, HIGH);}
}

void gr_blink(int t){
  green_LED(1);
  red_LED(1);
  delay(t);
  green_LED(0);
  red_LED(0);
}

void yellow_blink(int t){
  digitalWrite(yellow_LED_port, 1);delay(t); digitalWrite(yellow_LED_port, 0);
}

bool toggle_yellow_led(void *) {
  digitalWrite(yellow_LED_port, !digitalRead(yellow_LED_port)); // toggle the LED
  return true; // repeat? true
}

float LS_L(){
  float sensor_value = LS_L_r();
  float result = map_n(sensor_value, left_black, left_white, 0, 255);
  return result;
}

float LS_R(){
  float sensor_value = LS_R_r();
  float result = map_n(sensor_value, right_black, right_white, 0, 255);
  return result;
}


long US() {

  long duration, result;
   
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH, US_time_out);
   if (duration == 0){result=0;}
   else {result =duration / 29 / 2;}
   return result;
}
