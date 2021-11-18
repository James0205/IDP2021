
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
  int result = IR_differentiate();
  if(result==mixed){Serial.println("mixed");}
  if(result == zigzag){Serial.println("zigzag");}
  if(result == sqr){Serial.println("square");}
}



void IR_test_raw(bool *print_label){
  if(*print_label == true){*print_label = false; Serial.println("IR Test Raw.");}
  bool TSOP_peak = digitalRead(IR_port_TSOP_peak);
  Serial.println(TSOP_peak);
}

void IR_counter_test(bool *print_label){
  if(*print_label == true){*print_label = false; Serial.println("IR receiver counter Test.");}
  Serial.println(IR_counter(),6);
}

void servo_test(bool *print_label){
  if(*print_label == true){
    *print_label = false; 
    Serial.println("Servo test. What do you want to do? Rise (1), Grab (2), or Deploy (3)?");
    int input = Serial.parseInt();
    while(input == 0){input = Serial.parseInt();}
    if (input == 1) {rise();}
    else if (input == 2) {grab();}
    else if (input == 3) {deploy();}
  }
}
