//program to zero the servos

#include <Servo.h>
// create servo object to control a servo
Servo hip;
Servo knee;
Servo ankle;

int hipPos = 0;   // 0 front, 180 back
int kneePos = 0; //0 down, 180 up
int anklePos = 0; //0 in, 180 out

void setup() {
  // put your setup code here, to run once:
  hip.attach(11);  
  knee.attach(10);
  ankle.attach(9);

}

void loop() {
  // put your main code here, to run repeatedly:
    //set initial positions
  //  hipPos = 135;
    kneePos = 100;
    //anklePos = 90;
    hip.write(hipPos); 
    knee.write(kneePos);
    ankle.write(anklePos);

    //move knee angle slowly
    for (int i = 0; i > 180; i++) {
      knee.write(kneePos);
      kneePos++;
      delay(500);
    }

}
