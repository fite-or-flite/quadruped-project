//redoing with servo shield
//chris fite
//041520


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//defines for the adafruit functions -fiik
#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50

//assign numbers to servos leg joints  
int RFleg[3] = {0, 1, 2}; //HIP, KNEE, ANKLE
int LFleg[3]= {4, 5, 6};
int LBleg[3] = {8, 9, 10};
int RBleg[3]= {12, 13, 14};

//define leg #s
const int RF = 0;
const int LF = 1;
const int LB = 2;
const int RB = 3;
const int hip = 0;
const int knee = 1;
const int ankle = 2;

int hipPos[4];   
int kneePos[4];
int anklePos[4];

int speed = 15;

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//protoyping functions
int pulseWidth(int);
void moveServo(int, int);
void centerAllLegs();
void centerLeg(int[], int);
void moveLegOut(int[], int);
void moveLegIn(int[], int);
void raiseLeg(int[], int);
void lowerLeg(int[], int);
void stepForward(int[], int);
void stepBack(int[], int);
void waveLeg(int);
void leanToSide(int);
void walkForward();

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);  // Analog servos run at ~60 Hz updates

  //0=RF, 1=LF, 2=LB, 3=RB
  for (int i = 0; i < 4; i++) {
    hipPos[i] = 90;
    kneePos[i] = 90;
    anklePos[i] = 90;
  }

  centerAllLegs();
}

void loop() {
  
  leanToSide(RF);
  raiseLeg(RFleg, RF);
  delay(1000);
  centerAllLegs();
  delay(1000);

  leanToSide(LF);
  raiseLeg(LFleg, LF);
  delay(1000);
  centerAllLegs();
  delay(1000);
  
  leanToSide(LB);
  raiseLeg(LBleg, LB);
  delay(1000);
  centerAllLegs();
  delay(1000);
  
  leanToSide(RB);
  raiseLeg(RBleg, RB);
  delay(1000);
  centerAllLegs();
  delay(1000);
  
}

int pulseWidth(int angle) {
//makes this shit less confusing
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}

void moveServo(int servo, int angle) {
//makes this shit less confusing too
  pwm.setPWM(servo, 0, pulseWidth(angle));
}

void centerAllLegs() {
  centerLeg(RFleg, RF);
  centerLeg(LFleg, LF);
  centerLeg(LBleg, LB);
  centerLeg(RBleg, RB);
}

void centerLeg(int leg[], int legNum) {
//center ankle
  if (anklePos[legNum] > 90) {
    for (anklePos[legNum]; anklePos[legNum] > 90; anklePos[legNum]--) { 
      moveServo(leg[ankle], anklePos[legNum]);
      delay(speed);
    }
  }
  else if (anklePos[legNum] < 90) {
    for (anklePos[legNum]; anklePos[legNum] < 90; anklePos[legNum]++) {
      moveServo(leg[ankle], anklePos[legNum]);
      delay(speed);
    }
  }
  else if (anklePos[legNum] == 90) moveServo(leg[ankle], anklePos[legNum]);
//center knee
  if (kneePos[legNum] > 90) {
    for (kneePos[legNum]; kneePos[legNum] > 90; kneePos[legNum]--) {
      moveServo(leg[knee], kneePos[legNum]);
      delay(speed);
    }
  }
  else if (kneePos[legNum] < 90) {
    for (kneePos[legNum]; kneePos[legNum] < 90; kneePos[legNum]++) {
      moveServo(leg[knee], kneePos[legNum]);
      delay(speed);
    }
  }
  else if (kneePos[legNum] == 90) moveServo(leg[knee], kneePos[legNum]);
//center hip  
  if (hipPos[legNum] < 90) {
    for (hipPos[legNum]; hipPos[legNum] < 90; hipPos[legNum]++) {
      moveServo(leg[hip], hipPos[legNum]);
      delay(speed);
    }
  }
  else if (hipPos[legNum] > 90) {
    for (hipPos[legNum]; hipPos[legNum] > 90; hipPos[legNum]--) {
      moveServo(leg[hip], hipPos[legNum]);
      delay(speed);
    }
  }
  else if (hipPos[legNum] == 90) moveServo(leg[hip], hipPos[legNum]);
}

void moveLegOut(int leg[], int legNum) {
  switch(legNum) {
    case 0:
    case 2:
      for (hipPos[legNum]; hipPos[legNum] <= 135; hipPos[legNum]++) {
        moveServo(leg[hip], hipPos[legNum]);
        delay(speed);
      }
      break;
    case 1:
    case 3:
      for (hipPos[legNum]; hipPos[legNum] >= 45; hipPos[legNum]--) {
        moveServo(leg[hip], hipPos[legNum]);
        delay(speed);
      }
      break;
    default:
      Serial.println("there is no leg with that number.");
  }
}

void moveLegIn(int leg[], int legNum) {
    switch(legNum) {
    case 0:
    case 2:
      for (hipPos[legNum]; hipPos[legNum] >= 45; hipPos[legNum]--) {
        moveServo(leg[hip], hipPos[legNum]);
        delay(speed);
      }
      break;
    case 1:
    case 3:
      for (hipPos[legNum]; hipPos[legNum] <= 135; hipPos[legNum]++) {
        moveServo(leg[hip], hipPos[legNum]);
        delay(speed);
      }
      break;
    default:
      Serial.println("there is no leg with that number.");
  }
}

void raiseLeg(int leg[], int legNum) {
  switch(legNum) {
    case 0:
    case 2:
      for (kneePos[legNum]; kneePos[legNum] >= 45; kneePos[legNum]--) {
        moveServo(leg[knee], kneePos[legNum]);
        if (anklePos[legNum] >= 45) {
          moveServo(leg[ankle], anklePos[legNum]);
          anklePos[legNum]--;
        }
        delay(speed);
      }
      break;
    case 1:
    case 3:
      for (kneePos[legNum]; kneePos[legNum] <= 135; kneePos[legNum]++) {
        moveServo(leg[knee], kneePos[legNum]);
        if (anklePos[legNum] <= 135) {
          moveServo(leg[ankle], anklePos[legNum]);
          anklePos[legNum]++;
        }
        delay(speed);
      }
      break;
    default:
      Serial.println("there is no leg with that number");
      break;
  }
}

void lowerLeg(int leg[], int legNum) {
  switch(legNum) {
    case 0:
    case 2:
      for (kneePos[legNum]; kneePos[legNum] <= 90; kneePos[legNum]++) {
        moveServo(leg[knee], kneePos[legNum]);
        if (anklePos[legNum] <= 90) {
          moveServo(leg[ankle], anklePos[legNum]);
          anklePos[legNum]++;
        }
        delay(speed);
      }
      break;
    case 1:
    case 3:
      for (kneePos[legNum]; kneePos[legNum] >=90; kneePos[legNum]--) {
        moveServo(leg[knee], kneePos[legNum]);
        if (anklePos[legNum] >= 90) {
          moveServo(leg[ankle], anklePos[legNum]);
          anklePos[legNum]--;
        }
        delay(speed);
      }
      break;
    default:
      Serial.println("there is no leg with that number");
  }
  
}
void stepForward(int leg[], int legNum) {
  raiseLeg(leg, legNum);
  switch(legNum) {
    case 0:
    case 1:
      moveLegOut(leg, legNum);
      break;
    case 2:
    case 3:
      moveLegIn(leg, legNum);
      break;
    default:
     Serial.println("there is no leg with that number");
      break;
  }
  lowerLeg(leg,legNum);
}

void stepBack(int leg[], int legNum) {
    raiseLeg(leg, legNum);
  switch(legNum) {
    case 0:
    case 1:
      moveLegIn(leg, legNum);
      break;
    case 2:
    case 3:
      moveLegOut(leg, legNum);
      break;
    default:
     Serial.println("there is no leg with that number");
      break;
  }
  lowerLeg(leg,legNum);
}

void waveLeg(int legNum) {
  switch(legNum) {
    case 0:
      moveLegOut(RFleg, RF);
      raiseLeg(RFleg, RF);
      for (int i = 0; i < 3; i++) {
        moveServo(RFleg[ankle], 135);
        delay(200);
        moveServo(RFleg[ankle], 45);
        delay(200);
      }
      centerLeg(RFleg, RF);
      break;  
    case 1:
      moveLegOut(LFleg, LF);
      raiseLeg(LFleg, LF);
      for (int i = 0; i < 3; i++) {
        moveServo(LFleg, 45);
        delay(200);
        moveServo(LFleg, 135);
        delay(200);
      }
      centerLeg(LFleg, LF);
      break;
    case 2:
      moveLegOut(LBleg, LB);
      raiseLeg(LBleg, LB);
      for (int i = 0; i < 3; i++) {
        moveServo(LBleg, 135);
        delay(200);
        moveServo(LBleg, 45);
        delay(200);
      }
      centerLeg(LBleg, LB);
      break;
    case 3:
      moveLegOut(RBleg, RB);
      raiseLeg(RBleg, RB);
      for (int i = 0; i < 3; i++) {
        moveServo(RBleg, 45);
        delay(200);
        moveServo(RBleg, 135);
        delay(200);
      }
      centerLeg(RBleg, RB);
      break;
    default:
      Serial.println("there is no leg with that number");
      break;
  }
}

void leanToSide(int legNum) { //legnum is leg to pick up; everything shifts opposite
  switch(legNum) {
    case 0: // RF
      while ((hipPos[LF] > 45 ) || (hipPos[LB] < 135) || (hipPos[RB] < 135)) {
          if (hipPos[LF] > 45){
            moveServo(LFleg[hip], hipPos[LF]);
            hipPos[LF]--;
          }
          if (hipPos[LB] < 135) {
            moveServo(LBleg[hip], hipPos[LB]);
            hipPos[LB]++;            
          }
          if (hipPos[RB] < 135) {
            moveServo(RBleg[hip], hipPos[RB]);
            hipPos[RB]++;
          }
          delay(speed);
      }
      if (anklePos[LB] > 60) {
        for (anklePos[LB]; anklePos[LB] > 60; anklePos[LB]--) {
          moveServo(LBleg[ankle], anklePos[LB]);
          delay(speed);
        }
      }      
      break;
    case 1: // LF
      while ((hipPos[RF] < 135 ) || (hipPos[LB] > 45) || (hipPos[RB] > 45)) {
          if (hipPos[RF] < 135){
            moveServo(RFleg[hip], hipPos[RF]);
            hipPos[RF]++;
          }
          if (hipPos[LB] > 45) {
            moveServo(LBleg[hip], hipPos[LB]);
            hipPos[LB]--;            
          }
          if (hipPos[RB] > 45) {
            moveServo(RBleg[hip], hipPos[RB]);
            hipPos[RB]--;
          }
          delay(speed);
      }
      if (anklePos[RB] < 120) {
        for (anklePos[RB];anklePos[RB] < 120; anklePos[RB]++) {
          moveServo(RBleg[ankle], anklePos[RB]);
          delay(speed);
        }
      }      
      break;
    case 2: // LB
          while ((hipPos[RF] < 135 ) || (hipPos[LF] > 45) || (hipPos[RB] > 45)) {
          if (hipPos[RF] < 135){
            moveServo(RFleg[hip], hipPos[RF]);
            hipPos[RF]++;
          }
          if (hipPos[LF] > 45) {
            moveServo(LFleg[hip], hipPos[LF]);
            hipPos[LF]--;            
          }
          if (hipPos[RB] > 45) {
            moveServo(RBleg[hip], hipPos[RB]);
            hipPos[RB]--;
          }
          delay(speed);
      }
      if (anklePos[RF] > 60) {
        for (anklePos[RF]; anklePos[RF] > 60; anklePos[RF]--) {
          moveServo(RFleg[ankle], anklePos[RF]);
          delay(speed);
        }
      }      
      break;
    case 3: // RB
          while ((hipPos[RF] > 45 ) || (hipPos[LF] > 45) || (hipPos[LB] < 135)) {
          if (hipPos[RF] > 45){
            moveServo(RFleg[hip], hipPos[RF]);
            hipPos[RF]--;
          }
          if (hipPos[LF] > 45) {
            moveServo(LFleg[hip], hipPos[LF]);
            hipPos[LF]--;            
          }
          if (hipPos[LB] < 135) {
            moveServo(LBleg[hip], hipPos[LB]);
            hipPos[LB]++;
          }
          delay(speed);
      }
      if (anklePos[LF] < 120) {
        for (anklePos[LF]; anklePos[LF] < 120; anklePos[LF]++) {
          moveServo(LFleg[ankle], anklePos[LF]);
          delay(speed);
        }
      }      
      break;
   default:
      Serial.println("there is no leg with that number");
      break;
  }
}

void walkForward() {

}
