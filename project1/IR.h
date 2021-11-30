  const int White=1; // block color Light: Green and Red
const int Red=2; // Red
const int Blue=3; // Green

const int zigzag=1;
const int sqr=2;
const int mixed=3;

const float high_reference = 0.0731;
const float low_reference=0.0364;
const float offset=0.8;

int diff_blink_t = 1000;

const int IR_port_TSOP_peak = 5, IR_port_diff_peak = 3;
const int IR_port_TSOP = 6, QSD_port = 5;

float IR_counter(unsigned long sample_time){
  float total = 0;
  float zeros = 0;
  bool result = true;
  unsigned long t = millis()+sample_time;
  while (millis() < t)
  {
    result = digitalRead(IR_port_TSOP);
    total += 1;
    if (result == false){zeros += 1;}
  }
  float return_value = zeros/total;
  return return_value;
}

float QSD_counter(unsigned long sample_time){
  float total = 0;
  float zeros = 0;
  bool result = true;
  unsigned long t = millis()+sample_time;
  while (millis() < t)
  {
    result = digitalRead(QSD_port);
    total += 1;
    if (result == false){zeros += 1;}
  }
  float return_value = zeros/total;
  return return_value;
}


int IR_differentiate(unsigned long sample_time){
  float ratio = IR_counter(sample_time);
  if (ratio > (high_reference * offset)){return zigzag;}
  else if (ratio > (low_reference * offset)){ return mixed;}
  else {return sqr;}
}


int IR_differentiate_blink()
{
  int dummy = IR_differentiate(2000);
  digitalWrite(yellow_LED_port, 0);digitalWrite(red_LED_port, 0);digitalWrite(green_LED_port, 0);delay(1000);
  if (dummy == White){gr_blink(diff_blink_t);}
  else if (dummy == Red) {red_blink(diff_blink_t);}
  else if (dummy == Blue) {green_blink(diff_blink_t);} 
  delay(1000);
  return dummy;
}

int IR_search()
{
  float ratio = IR_counter(50);
  if (ratio > (low_reference * offset)){green_LED(1); return 1;}
  else {green_LED(0);return 0;}
}


float QSD_reference = 0.001;
int QSD_search()
{
  float ratio = QSD_counter(50);
  if (ratio > QSD_reference){green_LED(1); return 1;}
  else {green_LED(0);return 0;}
}

void QSD_search_r(unsigned long QSD_search_r_offset)
{
  int value = QSD_search();
  if(value == 1){
    while (value == 1){
      run(-100, 100);
      value = QSD_search();
    }
    delay(50);
    run(0,0); 
    value = QSD_search();
    delay(120);
  }
  run(100, -100);
  while(value == 0){value = QSD_search();}
  unsigned long start_time = millis();
  delay(50);
  while(value == 1){value = QSD_search();}
  unsigned long end_time = millis();
  delay(150);run(0,0);delay(200);
  unsigned long rotate_time = (end_time - start_time)/2 + QSD_search_r_offset;
  value = QSD_search();
  run(-100, 100);while(value == 0){value = QSD_search();}
  unsigned long reference_time = millis() + rotate_time;
  while (millis() < reference_time){}
  run(0,0);delay(200); 
}



void IR_search_r(unsigned long IR_search_r_offset)
{
  int value = IR_search();
  if(value == 1){
    while (value == 1){
      run(-100, 100);
      value = IR_search();
    }
    delay(50);
    run(0,0); 
    value = IR_search();
    delay(120);
  }
  run(100, -100);
  while(value == 0){value = IR_search();}
  unsigned long start_time = millis();
  delay(50);
  while(value == 1){value = IR_search();}
  unsigned long end_time = millis();
  delay(150);run(0,0);delay(200);
  unsigned long rotate_time = (end_time - start_time)/2 + IR_search_r_offset;
  value = IR_search();
  run(-100, 100);while(value == 0){value = IR_search();}
  unsigned long reference_time = millis() + rotate_time;
  while (millis() < reference_time){}
  run(0,0);delay(200); 
}


unsigned long IR_search_r_offset_std = 140;
unsigned long QSD_search_r_offset_std = 50;
unsigned long each_step_time = 2500;

int US_approach = 25;
int US_catch = 8;

void IR_approach(){
  ini();
  int count = 0;
  while (count < IRd_count){
    IR_search_r(IR_search_r_offset_std);
    unsigned long t = millis() + each_step_time;
    run(200,200);
    while(millis() < t && count < IRd_count){
      // if (US() < US_approach && US() != 0){count += 1;}else{count = 0;}
      if (IRd_f() == 1){count += 1;}else{count = 0;}
    }
  }
  run(0,0);
  gr_blink(500);
  ini_h();delay(1000);
  IRd_approach_dummy();
  gr_blink(500);
  ini();
}


void QSD_approach(){
  ini();
  int count = 0;
  while (count < IRd_count){
    QSD_search_r(QSD_search_r_offset_std);
    unsigned long t = millis() + each_step_time;
    run(200,200);
    while(millis() < t && count < IRd_count){
      // if (US() < US_approach && US() != 0){count += 1;}else{count = 0;}
      if (IRd_f() == 1){count += 1;}else{count = 0;}
    }
  }
  run(0,0);
  gr_blink(500);
  ini_h();delay(1000);
  IRd_approach_dummy();
  gr_blink(500);
  ini();
}
