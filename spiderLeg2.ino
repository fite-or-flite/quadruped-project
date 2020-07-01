//program to zero the servos

#include <Servo.h>
// create servo object to control a servo
Servo hip;
Servo knee;
Servo ankle;


int hipPos = 90;   
int kneePos = 90;
int anklePos = 90;
int speed = 15;

void moveLeg(); 

void setup() {
  // put your setup code here, to run once:
  hip.attach(11);
  knee.attach(10);
  ankle.attach(9); 

}

void loop() {
  // put your main code here, to run repeatedly:
  //set all joints to 90
  hip.write(hipPos);
  knee.write(kneePos);
  ankle.write(anklePos);

  moveLeg();

}

void moveLeg() {
  //pick up foot
  for (kneePos; kneePos >= 0; kneePos--) {
    knee.write(kneePos);
    delay(speed);  
  }
  delay(1000);

  for (anklePos; anklePos >= 45; anklePos--) {
    ankle.write(anklePos);
    delay(speed);
  }
  delay(1000);

  //move leg
  for (hipPos; hipPos <= 180; hipPos++) {
    hip.write(hipPos);
    delay(speed);
  }
  delay(1000);

//put down foot
  for (anklePos; anklePos <= 90; anklePos++) {
    ankle.write(anklePos);
    delay(speed);
  }
  delay(1000);
  
  for (kneePos; kneePos <= 90; kneePos++) {
    knee.write(kneePos);
    delay(speed);  
  }
  delay(1000);

  //move leg back
  for (hipPos; hipPos >= 90; hipPos--) {
    hip.write(hipPos);
    delay(speed);
  }
  delay(1000);
  
}
