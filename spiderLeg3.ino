//program to zero the servos

#include <Servo.h>
// create servo object to control a servo
Servo LFleg[3];
Servo RFleg[3];


int hipPos[4];   
int kneePos[4];
int anklePos[4];
int speed = 15;


void setup() {
  // put your setup code here, to run once:
  RFleg[0].attach(6); //hip
  RFleg[1].attach(5); //knee
  RFleg[2].attach(3); //ankle
  LFleg[0].attach(9);
  LFleg[1].attach(10);
  LFleg[2].attach(11);
}

void loop() {
  // put your main code here, to run repeatedly:
  //set all joint angles to 90
  for (int i = 0; i < 4; i++) {
    hipPos[i] = 90;
    kneePos[i] = 90;
    anklePos[i] = 90;
  }
  //set all joints to 90
  RFleg[0].write(hipPos[0]);
  RFleg[1].write(kneePos[0]);
  RFleg[2].write(anklePos[0]);
  LFleg[0].write(hipPos[1]);
  LFleg[1].write(kneePos[1]);
  LFleg[2].write(anklePos[1]);


  for (hipPos[0]; hipPos[0] >= 45; hipPos[0]++) {
    RFleg[0].write(hipPos[0]);
    delay(speed);
  }
  delay(1000);
  for (hipPos[0]; hipPos[0] <= 90; hipPos[0]--) {
    RFleg[0].write(hipPos[0]);
    delay(speed);
  }
  
}
