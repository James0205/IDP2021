#include "basic.h"
#include "line_follow.h"
#include "IR.h"
#include "servo_control.h"
#include "tests.h"

void setup() {
  AFMS.begin();
  Serial.begin(9600);
  pinMode(red_LED_port, OUTPUT);
  pinMode(button_port, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IR_port_TSOP_peak, INPUT);
  pinMode(IR_port_diff_peak, INPUT);
  pinMode(IR_port_TSOP, INPUT);
  servo_lift.attach(servo_lift_port);
  servo_claw.attach(servo_claw_port);
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
bool print_label = true;
void test1(){
  int value = Serial.parseInt(); // all those test and be switched by typing the corresponding number
  if (value!=0){ test_state = value; print_label = true;}
  if (test_state == 1){LS_test_r(&print_label);} // line sensor left and right raw data (0 - 1023)
  if (test_state == 2){LS_test(&print_label); } // line sensor left and right converted data (mapped to 0 - 255)
  if (test_state == 3){US_test(&print_label); } // ultrasonic sensor data (0 - 1023)
  if (test_state == 4){motor_test(&print_label);} // go forward and back
  if (test_state == 5){IR_test_diff(&print_label);} // IR differentiate
  if (test_state == 6){IR_test_raw(&print_label);} // IR return sensor port
  if (test_state == 7){IR_counter_test(&print_label);} // IR counter of 0 and 1 ratio in 1 second
  if (test_state == 8){servo_test(&print_label);} // test the servo, need to input another int to specify what action to take
  if(test_state == 10){task1();gr_blink(5000);} // start the task
}
