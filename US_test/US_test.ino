const int pingPin = A1; // Trigger Pin of Ultrasonic Sensor
const int echoPin = A0; // Echo Pin of Ultrasonic Sensor

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(pingPin, OUTPUT);
   pinMode(echoPin, INPUT);
}

void loop() {
   while(Serial.parseInt() == 0){}
   long last = US();
   long value = last;
   while(Serial.parseInt() == 0) {
      value = US();
     Serial.print(value);
     Serial.print(", ");
     Serial.println(value - last);
     last = value;
  }
}

long US(){
    long duration, inches, cm;
   
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   cm = duration / 29 / 2;
   return cm;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
