#include "basic.h"
#include "line_follow.h"
#include "IR.h"
#include "servo_control.h"
#include "tests.h"

#include <arduino-timer.h>

auto timer = timer_create_default(); // create a timer with default settings



void task(){
  int dummy = task1_0(true);
  dummy = Red;
  if (dummy == White){task1_W(true);}
  if (dummy == Red || dummy == Blue){task1_RB(dummy, true);}
}

int task1_0(bool _test) {
  cross_white(255, 50, 1, _test);
  fl_cross(255, -30, 1, 150, _test);
  yellow_blink(1000);
  fl_US(255, -30, 4, _test);
  int dummy = IR_differentiate();
  attach_all_servo();delay(200);
  grab();
  return dummy;
}

void task1_W(bool _test){
  fl_cross(255, -30, 1, 150, _test);
  run(150, 150); delay(400); run(0,0);
  deploy();
  detach_all_servo();
  run(-150, -150); delay(800); run(0,0);
  turn_to_line_l(1500, false);
  fl_cross(255, -30, 2, 150, _test);
}

void task1_RB(int dummy, bool _test){
  fl_cross(255, -30, 1, 0, _test);
  turn_to_line_l(1500, true);
  fl_cross(255, -30, 1, 150, _test);
  fl_time(255, -30, 1000, true);
  if (dummy == Blue){run(-200, 200);}
  else if (dummy == Red){run(200,-200);}
  int delay_time_deploy_dummy = 2500;
  delay(delay_time_deploy_dummy);
  run(0,0);delay(300);
  run(255, 255); delay(300);run(0,0);delay(200);
  deploy();
  detach_all_servo();
  run(-255, -255); delay(300);run(0,0);
  if (dummy == Blue){turn_to_line_r(delay_time_deploy_dummy-1000, true);}
  else if (dummy == Red){turn_to_line_l(delay_time_deploy_dummy-1500, true);}
  fl_cross(255, -30, 1, 150, _test);
}



int test_state = 0;
bool print_label = true;

/*bool task_test_timer(* void){
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
  if(test_state == 10){task();gr_blink(5000);} // start the task
  return true;
}*/

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
  if(test_state == 10){task();gr_blink(5000);} // start the task
  // return true;
}


void setup() {
  AFMS.begin();
  Serial.begin(9600);
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
  // while(button() == 0){}
  Serial.println("Ready to go!");
  attach_all_servo();
  ini();
  delay(500);
  detach_all_servo();
  //timer.every(500, toggle_yellow_led);
  //timer.at(1000, task_test);
}


void loop() {
  //timer.tick();
  task_test();
}
