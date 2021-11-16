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
