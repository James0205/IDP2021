#include "basic.h"
#include "line_follow.h"

void setup() {
  AFMS.begin();
  Serial.begin(9600);
  pinMode(red_LED_port, OUTPUT);
  pinMode(button_port, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  red_blink(1000);
  //while(button() == 0){}
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  //LS_test();
  //fl_continue(255, -20);
  //run(255, 255); delay(1000); run(0,0);
  test1();
  /*run(255, 255);
  delay(1000);
  run(0,0);*/
}

void task1() {
  cross_white(255, 50, 1, true);
  fl_cross(255, -30, 1, 150, true);
  fl_US(255, -100, 20, true);
}


int test_state = 0;
void test1(){
  int value = Serial.parseInt();
  if (value!=0){ test_state = value;}
  if (test_state == 1){LS_test_r(); }
  if (test_state == 2){LS_test(); }
  if (test_state == 3){US_test(); }
  if (test_state == 4){run(255,255); delay(2000); run(0,0); delay(2000); run(-255, -255); delay(2000);run(0,0); delay(2000);}
  if(test_state == 10){task1();red_blink(10000);}
}
