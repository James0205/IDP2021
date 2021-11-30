int task1_0(bool _test) {
  ini_h();
  cross_white(255, 50, 1, _test);
  fl_cross(255, -30, 1, 150, _test);
  fl_time(255, -30, 13000, _test);
  fl_IRd(160, -30, _test);
  ini();
  int dummy = IR_differentiate_blink();
  dummy_offset();
  attach_all_servo();delay(200);
  grab();
  return dummy;
}

void task1_W(bool _test){
  fl_cross(255, -30, 1, 150, _test);
  run(150, 150); delay(700); run(0,0);
  attach_all_servo(); deploy();
  run(-150, -150); delay(700); run(0,0);
}

void task1_RB(int dummy, bool _test){
  fl_cross(255, -30, 1, 0, _test);
  turn_to_line_l(2500, _test);
  fl_cross(255, -30, 1, 150, _test);
  fl_time(255, -30, 900, _test);
  if (dummy == Blue){run(-200, 200);}
  else if (dummy == Red){run(200,-200);}
  int delay_time_deploy_dummy = 3400;
  delay(delay_time_deploy_dummy);
  run(0,0);delay(300);
  run(255, 255); delay(1000);run(0,0);delay(200);
  deploy();
  run(-255, -255); delay(900);run(0,0);
  if (dummy == Blue){turn_to_line_l(delay_time_deploy_dummy-1800, _test);}
  else if (dummy == Red){turn_to_line_r(delay_time_deploy_dummy-1600, _test);}
  fl_cross(255, -30, 1, 150, _test);
}

bool search_test = true;
int task2_search(){
  unsigned long t1 = 3200;
  unsigned long t2 = 7800;
  unsigned long t3 = 3800;
  unsigned long t4 = 9000;
  int value = IR_search();
  int IR_flag = 0, right_flag = 1;
  turn_around(100, 1, t1, search_test);
  run(100, -100);
  unsigned long reference = t2+millis();
  while (IR_flag == 0 && millis() < reference){
    value = IR_search();
    if (value == 1){IR_flag = 1;}
  }
  run(0,0);delay(100);gr_blink(500);
  if (IR_flag == 1){run(-100, 100);delay(200);run(0,0);delay(200); return right_flag;}
  else{ // into right part
    run(200, -200);while(LS_R() < RB){}delay(20); while(LS_R() > RW){}run(0,0);gr_blink(500);
    turn_around(100, 1, t3, search_test);
    IR_flag = 0;  right_flag = 0;
    run(100, -100);
    unsigned long reference = millis()+ t4;
    while (IR_flag == 0 && millis() < reference){
      value = IR_search();
      if (value == 1){IR_flag = 1;}
    }
    run(0,0);gr_blink(500);
    if (IR_flag == 1){run(-100, 100);delay(200);run(0,0);delay(200);return right_flag;}
    else {// fail to detect any dummy
         run(200,-200);while(LS_R() < RB){} delay(20);while(LS_R() > RW){}delay(20);run(0,0);delay(100);
         return -1;
    }
  }
}

int task2_0(bool _test){
  turn_to_line_l(2500, _test);
  attach_all_servo();
  ini();
  fl_time(255, -30, 3500, _test);
  int right_flag = task2_search();
  if (right_flag == -1){run(0,0);fl_cross(255, -30, 2, 150, _test);}
  IR_approach();
  int dummy = IR_differentiate_blink();
  dummy_offset();
  attach_all_servo();delay(200);
  grab();
  turn_around(200, 1, 6450,_test); //full battery 6450
  run(-255, -255); delay(1000);run(0,0);delay(200);
  cross_white(180, 2400, 1, _test);
  if(right_flag == 0){turn_to_line_r(0, _test);}
  else if (right_flag == 1){turn_to_line_l(0, _test);}
  return dummy;
  
}
  

void task3_RB(int dummy, bool _test){
  fl_cross(255, -30, 1, 0, _test);
  turn_to_line_l(2500, _test);
  fl_cross(255, -30, 1, 150, _test);
  fl_time(255, -30, 900, _test);
  if (dummy == Blue){run(-200, 200);}
  else if (dummy == Red){run(200,-200);}
  int delay_time_deploy_dummy = 3400;
  delay(delay_time_deploy_dummy);
  run(0,0);delay(300);
  run(255, 255); delay(1000);run(0,0);delay(200);
  deploy();
  run(-255, -255); delay(900);run(0,0);
  if (dummy == Blue){turn_to_line_r(delay_time_deploy_dummy-1700, _test);}
  else if (dummy == Red){turn_to_line_l(delay_time_deploy_dummy-1600, _test);}
  fl_cross(255, -30, 1, 150, _test);
}

void task3_W(bool _test){
  fl_cross(255, -30, 1, 150, _test);
  run(150, 150); delay(400); run(0,0);
  attach_all_servo(); deploy();
  run(-150, -150); delay(400); run(0,0);
  turn_to_line_l(2500, _test);
  fl_cross(255, -30, 2, 150, _test);
}

void task(){
  int dummy = task1_0(false);
  if (dummy == White){task1_W(false);}
  if (dummy == Red || dummy == Blue){task1_RB(dummy, false);}
  /*dummy = task2_0(true);
  if (dummy == White){task1_W(true);}
  if (dummy == Red || dummy == Blue){task1_RB(dummy, true);*/
  dummy = task2_0(false);
  if (dummy == White){task3_W(false);}
  else if (dummy == Red || dummy == Blue){task3_RB(dummy, false);}
  // if dummy == -1 do nothing above and go back
  attach_all_servo();delay(200);
  ini_h();
  run(255, 255);delay(2200);run(0,0);
}
