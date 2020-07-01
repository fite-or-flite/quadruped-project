//moving the front legs

#include <Servo.h>

// create leg groups
Servo LFleg[3];
Servo RFleg[3];
Servo RBleg[3];
Servo LBleg[3];

//0=RF, 1=LF, 2=LB, 3=RB
int hipPos[4];   
int kneePos[4];
int anklePos[4];

int speed = 15;

void moveRightLegForward(Servo[]); 
void centerLeg(Servo[]);

void setup() {
  //attach servos
  RFleg[0].attach(6); //hip
  RFleg[1].attach(5); //knee
  RFleg[2].attach(3); //ankle
  LFleg[0].attach(9);
  LFleg[1].attach(10);
  LFleg[2].attach(11);
  
  //set all joint angles to 90
  for (int i = 0; i < 4; i++) {
    hipPos[i] = 90;
    kneePos[i] = 90;
    anklePos[i] = 90;
  }
}

void loop() {
  //set all joints to 90
  RFleg[0].write(hipPos[0]);
  RFleg[1].write(kneePos[0]);
  RFleg[2].write(anklePos[0]);
  LFleg[0].write(hipPos[1]);
  LFleg[1].write(kneePos[1]);
  LFleg[2].write(anklePos[1]);

//  moveRightLegForward(RFleg);
  for (hipPos[0]; hipPos[0] <= 45; hipPos[0]--) { //correct???
    RFleg[0].write(hipPos[0]);
    delay(speed);
  }
  delay(1000);
  for (hipPos[0]; hipPos[0] >= 90; hipPos[0]++) {
      RFleg[0].write(hipPos[0]);
      delay(speed);
    }
  //centerLeg(RFleg);
  delay(1000);
  
}

void moveRightLegForward(Servo leg[]) {
  for (hipPos[0]; hipPos[0] >= 135; hipPos[0]++) { //correct???
    leg[0].write(hipPos[0]);
    delay(speed);
  }
}

void centerLeg (Servo leg[]) {
  //this only does RFleg
  if (hipPos[0] > 90) {
    for (hipPos[0]; hipPos[0] <= 90; hipPos[0]--) {
      leg[0].write(hipPos[0]);
      delay(speed);
    }
  }
  else if (hipPos[0] < 90) {
    for (hipPos[0]; hipPos[0] >= 90; hipPos[0]++) {
      leg[0].write(hipPos[0]);
      delay(speed);
    }
  }
  else leg[0].write(90); //hipPos[0] = 90
}
