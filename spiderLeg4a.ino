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

void moveLeftLeg(Servo[]);
void moveRightLeg(Servo[]);
void centerLeftLeg(Servo[]);
void centerRightLeg(Servo[]);

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

  moveLeftLeg(LFleg); 
  delay(1000);
  moveRightLeg(RFleg);
  delay(1000);

}

void moveLeftLeg(Servo LFleg[]) {
 for (hipPos[1]; hipPos[1] >= 45; hipPos[1]--) {
    LFleg[0].write(hipPos[1]);
    delay(speed);
  }
  //kick
  for (kneePos[1]; kneePos[1] <= 45; kneePos[1]--) {
    LFleg[1].write(kneePos[1]);
    delay(speed);
  }
  for (kneePos[1]; kneePos[1] >= 90; kneePos[1]++) {
    LFleg[1].write(kneePos[1]);
    delay(speed);
  }
 for (hipPos[1]; hipPos[1] <= 90; hipPos[1]++) {
    LFleg[0].write(hipPos[1]);
    delay(speed);
  } 
  
}

void moveRightLeg(Servo RFleg[]) {
  for (hipPos[0]; hipPos[0] <= 135; hipPos[0]++) {
    RFleg[0].write(hipPos[0]);
    delay(speed);
  }
  for (hipPos[0]; hipPos[0] >= 90; hipPos[0]--) {
    RFleg[0].write(hipPos[0]);
    delay(speed);
  }  
}

void centerLeftLeg(Servo leg[]) {
  if (hipPos[1] > 90) {
    for (hipPos[1]; hipPos[1] <= 90; hipPos[1]--) {
      LFleg[0].write(hipPos[1]);
      delay(speed);
    }
  }
  else if (hipPos[1] < 90) {
    for (hipPos[1]; hipPos[1] >= 90; hipPos[1]++) {
      LFleg[0].write(hipPos[1]);
      delay(speed);
    }
  }
  else LFleg[0].write(90); // hipPos[1] IS 90
}

void centerRightLeg(Servo leg[]) {
  
}
