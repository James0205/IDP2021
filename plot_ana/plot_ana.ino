int Port = A0;

void setup() {
  Serial.begin(9600); 
}


void loop() {
  int y1 = analogRead(Port);

  Serial.println(y1);

  delay(100);
}
