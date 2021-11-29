const int IRd_f_port = A0, IRd_b_port = A3;
const int IRd_count = 3;

int find_max(int arr[])
{
    int n = sizeof(arr) / sizeof(arr[0]);
    int maximum = arr[0];
    for (int j = 0; j < n; ++j) {
        if (arr[j] > maximum) {
            maximum = arr[j];
        }
    }
    return maximum;
}

int find_min(int arr[])
{
    int n = sizeof(arr) / sizeof(arr[0]);
    int minimum = arr[0];
    for (int j = 0; j < n; ++j) {
        if (arr[j] < minimum) {
            minimum = arr[j];
        }
    }
    return minimum;
}

int result[6];


int IRd_f_avr(){
  int sensor_value;
  //Serial.println("Here are the raw data.");
  for (int j = 0; j<6; j++){
    sensor_value = analogRead(IRd_f_port);
    //Serial.print(sensor_value);Serial.print(" ");
    result[j] = sensor_value;
  }
  //Serial.println(" ");
  //Serial.println("Here are the max min average");
  /*int maximum = find_max(result);
  Serial.print(maximum);Serial.print(" ");
  int minimum = find_min(result);
  Serial.print(minimum);Serial.print(" ");
  int sum = -maximum - minimum;*/
  int sum = 0;
  for (int j = 0; j<6; j++){
    sum += result[j];
  }
  sum /= 6;
  //Serial.println(sum);
  return sum;
}

const int IRd_f_reference = 300;
int IRd_f(){
  if (IRd_f_avr() > IRd_f_reference) {green_LED(1);return 1;}
  else {green_LED(0);return 0;}
}

const int IRd_b_reference = 300;
int IRd_b_avr(){
  int sensor_value;
  //Serial.println("Here are the raw data.");
  for (int j = 0; j<6; j++){
    sensor_value = analogRead(IRd_b_port);
    //Serial.print(sensor_value);Serial.print(" ");
    result[j] = sensor_value;
  }
  //Serial.println(" ");
  //Serial.println("Here are the max min average");
  /*int maximum = find_max(result);
  Serial.print(maximum);Serial.print(" ");
  int minimum = find_min(result);
  Serial.print(minimum);Serial.print(" ");
  int sum = -maximum - minimum;*/
  int sum = 0;
  for (int j = 0; j<6; j++){
    sum += result[j];
  }
  sum /= 6;
  //Serial.println(sum);
  return sum;
}

int IRd_b(){
  if (IRd_b_avr() > IRd_b_reference) {red_LED(1); return 1;}
  else {red_LED(0); return 0;}
}

int IRd_approach_dummy(){
  run(120, 120);
  int count = 0;
  while(count < IRd_count){if(IRd_b()==1){count += 1;}else{count = 0;}}
  run(0,0);delay(100);
}
