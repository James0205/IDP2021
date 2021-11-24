#include <Servo.h> 
Servo servo_lift, servo_claw;

const int servo_lift_port = 10, servo_claw_port = 9; // inner one 9, outer one 10

const int pos_lift = 130, pos_lay = 30, pos_catch = 163, pos_release = 70, pos_put = 35, pos_half_lift = 90;

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
