const int trigPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

const int LED = 13;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
}

long US() {

  long duration, result;
   
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH, 6000);
   if (duration == 0){result=0;}
   else {result =duration / 29 / 2;}
   return result;
}

void loop() {
  while(Serial.parseInt() == 0){digitalWrite(LED, LOW);}
   digitalWrite(LED, HIGH);
   long last = US();
   long value = last;
   while(true) {
    
     value = US();
     Serial.print(value);
     Serial.print(", ");
     Serial.println(value - last);
     last = value;
     // delay(50);
   }
}
