#include "basic.h"
#include "servo_control.h"
#include "IR_distance.h"
#include "line_follow.h"
#include "IR.h"
#include "tests.h"
#include "task.h"
#include <arduino-timer.h>

auto timer = timer_create_default(); // create a timer with default settings


int test_state = 0;
bool print_label = true;

void task_test(){
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
  if (test_state == 9){IR_search_test_stationary(&print_label);}
  if (test_state == 10){digital_test(&print_label);}
  if (test_state == 11){IR_search_test_r(&print_label);}
  if (test_state == 12){IR_approach();}
  if (test_state == 13){IRd_b_avr();}
  if (test_state == 14){turn_around_test(&print_label);}
  if (test_state == 15){Serial.println(IRd_b());Serial.println(IRd_b_avr());}
  if (test_state == 16){Serial.println(IRd_f());Serial.println(IRd_f_avr());}
  if (test_state == 17){Serial.println(task2_search());}
  if(button() == 0){yellow_blink(500);task();gr_blink(5000);} // start the task
  // return true;
}


void competition() {  
  task();
  // return true; // repeat? true
}

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  pinMode(red_LED_port, OUTPUT);
  pinMode(yellow_LED_port, OUTPUT);
  pinMode(green_LED_port, OUTPUT);
  pinMode(button_port, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IR_port_TSOP_peak, INPUT);
  pinMode(IR_port_diff_peak, INPUT);
  pinMode(IR_port_TSOP, INPUT);
  gr_blink(1000);
  attach_all_servo();
  ini_h();
  while(button() == 0){}
  while(button() == 1){}
  yellow_blink(500);
  Serial.println("Ready to go!");
}

void loop() {
  //timer.tick();
  //competition();delay(200000);
  task_test();
}
