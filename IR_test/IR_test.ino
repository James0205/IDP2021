int IRSensor = 2; // connect ir sensor to arduino pin 2
int LED = 13; // conect Led to arduino pin 13



void setup() 
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println(analogRead(A0));
}
