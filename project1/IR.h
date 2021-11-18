const int White=1; // block color Light: Green and Red
const int Red=2; // Red
const int Blue=3; // Green

const int zigzag=1;
const int sqr=2;
const int mixed=3;

const float high_reference = 0.0731;
const float low_reference=0.0364;
const float offset=0.9;


const int IR_port_TSOP_peak = 5, IR_port_diff_peak = 3, IR_port_TSOP = 5, IR_port_QSD = 6;
bool dummy_detected(void){
  bool result = digitalRead(IR_port_TSOP_peak) || digitalRead(IR_port_diff_peak);
  return result;
}

float IR_counter(){
  float total = 0;
  float zeros = 0;
  bool result = true;
  unsigned long t = millis()+1000;
  while (millis() < t)
  {
    result = digitalRead(IR_port_TSOP);
    total += 1;
    if (result == false){zeros += 1;}
  }
  float return_value = zeros/total;
  return return_value;
}


int IR_differentiate(void){
  float ratio = IR_counter();
  if (ratio > (high_reference * offset)){return zigzag;}
  else if (ratio > (low_reference * offset)){ return mixed;}
  else {return sqr;}
}

/*int IR_differentiate2(void){
  bool TSOP_peak = digitalRead(IR_port_TSOP_peak), diff_peak = digitalRead(IR_port_diff_peak);
  if (TSOP_peak && !diff_peak){return zigzag;}
  else if (diff_peak) {return 4;}
  else if (!TSOP_peaks && !diff_peak) {return 0;}
}*/
