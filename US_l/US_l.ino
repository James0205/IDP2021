#include <hcsr04.h>

#define TRIG_PIN A0
#define ECHO_PIN A1

HCSR04 US(TRIG_PIN, ECHO_PIN, 20, 4000);
int LED = 13;

void setup(){
    Serial.begin(9600);
    pinMode (LED, OUTPUT); // Led pin OUTPUT
}

/*void loop() {

  // Output the distance in mm
  Serial.println(US.distanceInMillimeters());
  
  // Output information about the device, driver, and distance in Bifrost JSON format
  // Serial.println(US.ToString());
  
  delay(250);
}*/


void loop() {
   while(Serial.parseInt() == 0){digitalWrite(LED, LOW);}
   digitalWrite(LED, HIGH);
   long last = US.distanceInMillimeters();
   long value = last;
   while(true) {
    
     /* value = US.distanceInMillimeters();
     Serial.print(value);
     Serial.print(", ");
     Serial.println(value - last);
     last = value;*/
     Serial.println(US());
   }
}
