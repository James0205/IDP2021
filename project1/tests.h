
void US_test(bool *print_label){
  if(*print_label == true){*print_label = false; Serial.println("Ultrasonic Sensor Test.");}
  Serial.println(US());
}


void LS_test_r(bool *print_label){
  if(*print_label == true){*print_label = false; Serial.println("Light Sensor test on Raw data.");}
  Serial.print(LS_L_r());
  Serial.print(", ");
  Serial.println(LS_R_r());
}

void LS_test_v(bool *print_label){
  if(*print_label == true){*print_label = false; Serial.println("Light Sensor test on Voltage data.");}
  Serial.print(LS_L_v());
  Serial.print(", ");
  Serial.println(LS_R_v());
}

void LS_test(bool *print_label){
  if(*print_label == true){*print_label = false; Serial.println("Light Sensor test on processed data.");}
  Serial.print(LS_L());
  Serial.print(", ");
  Serial.println(LS_R());
}

void motor_test(bool *print_label){
  if(*print_label == true){*print_label = false; Serial.println("Motor Test.");}
  run(255,255); delay(2000); run(0,0); delay(2000); run(-255, -255); delay(2000);run(0,0); delay(2000);
}

int value = 0;
void IR_test_diff(bool *print_label){
  if(*print_label == true){*print_label = false; Serial.println("IR Test Differentiation.");}
  int result = IR_differentiate_test(1000);
  if(result==mixed){Serial.println("mixed");}
  if(result == zigzag){Serial.println("zigzag");}
  if(result == sqr){Serial.println("square");}
}



void IR_test_raw(bool *print_label){
  if(*print_label == true){*print_label = false; Serial.println("IR Test Raw.");}
  bool TSOP = digitalRead(IR_port_TSOP);
  Serial.println(TSOP);
}

void IR_counter_test(bool *print_label){
  if(*print_label == true){*print_label = false; Serial.println("IR receiver counter Test.");}
  Serial.println(IR_counter(1000),6);
}

void servo_test(bool *print_label){
  if(*print_label == true){
    *print_label = false; 
    Serial.println("Servo test. What do you want to do? Rise (1), Grab (2), Deploy (3), or Half Rise (4), or detach (5)?");
    int input = Serial.parseInt();
    while(input == 0){input = Serial.parseInt();}
    if (input == 1) {attach_all_servo();rise();}
    else if (input == 2) {attach_all_servo();grab();}
    else if (input == 3) {attach_all_servo();deploy();}
    else if (input == 4) {attach_all_servo();half_rise();}
    else if (input == 5) {detach_all_servo();}
  }
}
