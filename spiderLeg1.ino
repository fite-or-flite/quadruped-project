//program to zero the servos

#include <Servo.h>
// create servo object to control a servo
Servo hip;
Servo knee;
Servo ankle;


int pos = 90;   

void setup() {
  // put your setup code here, to run once:
  hip.attach(11);
  knee.attach(10);
  ankle.attach(9); 

}

void loop() {
  // put your main code here, to run repeatedly:
  hip.write(pos);
  knee.write(pos);
  ankle.write(pos);
  
  
  for (pos; pos >= 0; pos--) {
    hip.write(pos);
    //ankle.write(pos);
   // knee.write(pos);
    delay(50);
  }
  delay(1000);
  
  for (pos; pos <= 90; pos++) {
    hip.write(pos);
   // ankle.write(pos);
   // knee.write(pos);
    delay(50);
  }
  delay(1000);
}
