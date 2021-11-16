#define White 1; // block color Light: Green and Red
#define Red 2; // Red
#define Blue 3; // Green

const int IR_port_TSOP = 1, IR_port_diff = 2;

bool dummy_detected(void){
  bool result = digitalRead(IR_port_TSOP) || digitalRead(IR_port_diff);
  return result;
}
