#include <Servo.h> 
Servo servo_lift, servo_claw;

const int servo_lift_port = 10, servo_claw_port = 9; // inner one 9, outer one 10

const int pos_lift = 130, pos_lay = 33, pos_catch = 163, pos_release = 35, pos_put = 35, pos_half_lift = 100;

void half_lift(){
  servo_lift.write(pos_half_lift);
}


void lift()
{
  servo_lift.write(pos_lift);
}

void lay(){
  servo_lift.write(pos_lay);
}

void capture(){
  servo_claw.write(pos_catch);
}

void releasse(){
  servo_claw.write(pos_release);
}

void ini(){
  lay();
  releasse();
}

void rise(){
  lift();
  releasse();
}

void half_rise(){
  half_lift();
  releasse();
}

void grab(){
  lay();
  delay(700);
  capture();
  delay(700);
  lift();
  delay(700);
}

void deploy(){
  servo_lift.write(pos_put);
  delay(600);
  releasse();
  delay(500);
  half_lift();
  delay(500);
}

void attach_all_servo(){
  servo_lift.attach(servo_lift_port);
  servo_claw.attach(servo_claw_port);
}

void detach_all_servo(){
  servo_lift.detach();
  servo_claw.detach();
}
