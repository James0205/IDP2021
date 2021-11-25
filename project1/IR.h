  const int White=1; // block color Light: Green and Red
const int Red=2; // Red
const int Blue=3; // Green

const int zigzag=1;
const int sqr=2;
const int mixed=3;

const float high_reference = 0.0731;
const float low_reference=0.0364;
const float offset=0.9;

int diff_blink_t = 100;

const int IR_port_TSOP_peak = 5, IR_port_diff_peak = 3;
const int IR_port_TSOP = 6, IR_port_QSD = 7;
bool dummy_detected(void){
  bool result = digitalRead(IR_port_TSOP_peak) || digitalRead(IR_port_diff_peak);
  return result;
}

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


int IR_differentiate_test(unsigned long sample_time){
  float ratio = IR_counter(sample_time);
  if (ratio > (high_reference * offset)){return zigzag;}
  else if (ratio > (low_reference * offset)){ return mixed;}
  else {return sqr;}
}

int IR_differentiate()
{
  int dummy = IR_differentiate_test(2000);
  if (dummy == White){gr_blink(diff_blink_t);}
  else if (dummy == Red) {red_blink(diff_blink_t);}
  else if (dummy == Blue) {green_blink(diff_blink_t);} 
  return dummy;
}

int IR_search()
{
  run(150, -150);
  float ratio = IR_counter(18);
  if (ratio > (low_reference * offset)){return 1;}
  else {return 0;}
}

void IR_search_test(){
  Serial.println(IR_search());
}
