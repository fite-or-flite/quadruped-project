//walking ALL the legs
//chris fite
//041220

//change all the if(0||1) statements to switch()
//add circling?!

#include <Servo.h>

// create leg groups
Servo LFleg[3];
Servo RFleg[3];
Servo RBleg[3];
Servo LBleg[3];

//define leg #s
const int RF = 0;
const int LF = 1;
const int LB = 2;
const int RB = 3;

int hipPos[4];   
int kneePos[4];
int anklePos[4];

int speed = 15;

void centerLeg(Servo[], int);
void centerAllLegs();
void kickLeg(int);
void raiseLeg(Servo[], int);
void lowerLeg(Servo[], int);
void stepForward(Servo[], int);
void stepBack(Servo[], int);
void moveLegOut(Servo[], int);
void moveLegIn(Servo[], int);
void leanToSide(int); //int is the leg to raise
void waveLeg(int); //int is the leg to wave

void setup() {
  Serial.begin(9600);
  
//attach servos  
  RFleg[0].attach(4); //hip
  RFleg[1].attach(3); //knee
  RFleg[2].attach(2); //ankle
  
  LFleg[0].attach(13);
  LFleg[1].attach(12);
  LFleg[2].attach(11);

  LBleg[0].attach(10);
  LBleg[1].attach(9);
  LBleg[2].attach(8);

  RBleg[0].attach(7);
  RBleg[1].attach(6);
  RBleg[2].attach(5);   

//0=RF, 1=LF, 2=LB, 3=RB
  for (int i = 0; i < 4; i++) {
    hipPos[i] = 90;
    kneePos[i] = 90;
    anklePos[i] = 90;
  }
//set all joints to 90
  centerAllLegs();
}

void loop() {
  

  delay(500);
}

void centerLeg(Servo leg[], int legNum){
//center ankle
  if (anklePos[legNum] > 90) {
    for (anklePos[legNum]; anklePos[legNum] > 90; anklePos[legNum]--){
      leg[2].write(anklePos[legNum]);
      delay(speed);
    }
  }
  else if (anklePos[legNum] < 90) {
    for (anklePos[legNum]; anklePos[legNum] < 90; anklePos[legNum]++){
      leg[2].write(anklePos[legNum]);
      delay(speed);
    }
  }
  else if (anklePos[legNum] == 90) leg[2].write(anklePos[legNum]);
//center knee
  if (kneePos[legNum] > 90) {
    for (kneePos[legNum]; kneePos[legNum] > 90; kneePos[legNum]--) {
      leg[1].write(kneePos[legNum]);
      delay(speed);
    }
  }
  else if (kneePos[legNum] < 90) {
    for (kneePos[legNum]; kneePos[legNum] < 90; kneePos[legNum]++) {
      leg[1].write(kneePos[legNum]);
      delay(speed);
    }
  }
  else if (kneePos[legNum] == 90) leg[1].write(kneePos[legNum]);
//center hip
  if (hipPos[legNum] > 90) {
    for (hipPos[legNum]; hipPos[legNum] > 90; hipPos[legNum]--){
      leg[0].write(hipPos[legNum]);
      delay(speed);
    }
  }
  else if (hipPos[legNum] < 90) {
    for (hipPos[legNum]; hipPos[legNum] < 90; hipPos[legNum]++) {
      leg[0].write(hipPos[legNum]);
      delay(speed);
    }
  }
  else if (hipPos[legNum] == 90) leg[0].write(hipPos[legNum]);
}

void centerAllLegs() {
  centerLeg(LFleg, LF);
  centerLeg(RFleg, RF);
  centerLeg(RBleg, RB);
  centerLeg(LBleg, LB);
}

void kickLeg(int legNum) {
  switch(legNum) {
    case 0: //RF
      for (kneePos[RF]; kneePos[RF] >= 45; kneePos[RF]--) {
        RFleg[1].write(kneePos[RF]);
        if (anklePos[RF] < 135) {
          RFleg[2].write(anklePos[RF]);
          anklePos[RF]++;
        }
        delay(speed);
      }
      delay(500);
      for (kneePos[RF]; kneePos[RF] <= 90; kneePos[RF]++) {
        RFleg[1].write(kneePos[RF]);
        if (anklePos[RF] > 90) {
          RFleg[2].write(anklePos[RF]);
          anklePos[RF]--;
        }
        delay(speed);
      }
      delay(500);
      break;
    case 1: // LF
     for (kneePos[LF]; kneePos[LF] <= 135; kneePos[LF]++) {
        LFleg[1].write(kneePos[LF]);
        if (anklePos[LF] > 45) {
          LFleg[2].write(anklePos[LF]);
          anklePos[LF]--;
        }
        delay(speed);
      }
      delay(500);
      for(kneePos[LF]; kneePos[LF] >= 90; kneePos[LF]--) {
        LFleg[1].write(kneePos[LF]);
        if (anklePos[LF] < 90) {
          LFleg[2].write(anklePos[LF]);
          anklePos[LF]++;
        }
        delay(speed);
      }
      delay(500);
      break;
    case 2: // LB 45
      for(kneePos[LB]; kneePos[LB] >= 45; kneePos[LB]--) {
        LBleg[1].write(kneePos[LB]);
        if (anklePos[LB] < 135) {
          LBleg[2].write(anklePos[LB]);
          anklePos[LB]++;
        }
        delay(speed);
      }
      delay(500);
      for (kneePos[LB]; kneePos[LB] <= 90; kneePos[LB]++) {
        LBleg[1].write(kneePos[LB]);
        if (anklePos[LB] > 90) {
          LBleg[2].write(anklePos[LB]);
          anklePos[LB]--;
        }
        delay(speed);
      }
      delay(500);
      break;
    case 3: //RB 135
     for (kneePos[RB]; kneePos[RB] <= 135; kneePos[RB]++) {
        RBleg[1].write(kneePos[RB]);
        if (anklePos[RB] > 45) {
          RBleg[2].write(anklePos[RB]);
          anklePos[RB]--;
        }
        delay(speed);
      }
      delay(500);
      for (kneePos[RB]; kneePos[RB] >= 90; kneePos[RB]--) {
        RBleg[1].write(kneePos[RB]);
        if (anklePos[RB] < 90) {
          RBleg[2].write(anklePos[RB]);
          anklePos[RB]++;
        }
        delay(speed);
      }
      delay(500);
      break;
    default:
      break;
  }
}

void raiseLeg(Servo leg[], int legNum) {
  switch(legNum) {
    case 0:
    case 2:
      for (kneePos[legNum]; kneePos[legNum] >= 45; kneePos[legNum]--) {
        leg[1].write(kneePos[legNum]);
        if (anklePos[legNum] > 45){
          leg[2].write(anklePos[legNum]);
          anklePos[legNum]--;
        }
        delay(speed);
      }
      break;
    case 1:
    case 3:
      for (kneePos[legNum]; kneePos[legNum] <= 135; kneePos[legNum]++) {
        leg[1].write(kneePos[legNum]);
        if (anklePos[legNum] < 135) {
          leg[2].write(anklePos[legNum]);
          anklePos[legNum]++;
        }
        delay(speed);
      }
      break;
  default:
    Serial.print("there is no leg with that number.\n");
    break;
  }
}

void lowerLeg(Servo leg[], int legNum) {
  switch(legNum) {
    case 0:
    case 2:
      for (anklePos[legNum]; anklePos[legNum] <= 90; anklePos[legNum]++) {
        leg[2].write(anklePos[legNum]);
        if (kneePos[legNum] < 90) {
          leg[1].write(kneePos[legNum]);
          kneePos[legNum]++;
        }
        delay(speed);
      }
      break;
    case 1:
    case 3:
      for (anklePos[legNum]; anklePos[legNum] >= 90; anklePos[legNum]--) {
        leg[2].write(anklePos[legNum]);
        if (kneePos[legNum] > 90) {
          leg[1].write(kneePos[legNum]);
          kneePos[legNum]--;
        }
        delay(speed);
      }
      break;
    default:
      Serial.print("there is no leg with that number.\n");
      break;
  }
}

void raiseAllLegs() {
  raiseLeg(RFleg, RF);
  raiseLeg(LFleg, LF);
  raiseLeg(LBleg, LB);
  raiseLeg(RBleg, RB);
  /*
   //this is not working - ???
   while(kneePos[RF] > 45 || kneePos[LF] < 135 || kneePos[LB] > 45 || kneePos[RB] < 135 ||
    anklePos[RF] > 45 || anklePos[LF] < 135 || anklePos[LB] > 45 || anklePos[RB] < 135) {
      if (kneePos[RF] > 45) {
        RFleg[1].write(kneePos[RF]);
        kneePos[RF]--;        
      }
      if (kneePos[LF] < 135) {
        LFleg[1].write(kneePos[LF]);
        kneePos[RF]++;        
      }
      if (kneePos[LB] > 45) {
        LBleg[1].write(kneePos[LB]);
        kneePos[LB]--;        
      }
      if (kneePos[RB] < 135) {
        RBleg[1].write(kneePos[RB]);
        kneePos[RB]--;        
      }
      if (anklePos[RF] > 45) {
        RFleg[2].write(anklePos[RF]);
        anklePos[RF]--;
      }
      if (anklePos[LF] < 135) {
        LFleg[2].write(anklePos[LF]);
        anklePos[LF]++;
      }
      if (anklePos[LB] > 45) {
        LBleg[2].write(anklePos[LB]);
        anklePos[LB]--;
      }
      if (anklePos[RB] < 135) {
        RBleg[2].write(anklePos[RB]);
        anklePos[RB]++;
      }
    }
    */
}
void stepForward(Servo leg[], int legNum) {
  raiseLeg(leg, legNum);
  if (legNum == 0 || legNum == 1)
    moveLegOut(leg, legNum);      
  else if (legNum == 2 || legNum == 3) 
    moveLegIn(leg, legNum);
  else Serial.print("there is no leg with that number.\n");
  lowerLeg(leg, legNum);
}

void stepBack(Servo leg[], int legNum) {
    raiseLeg(leg, legNum);
  if (legNum == 0 || legNum == 1)
    moveLegIn(leg, legNum);      
  else if (legNum == 2 || legNum == 3) 
    moveLegOut(leg, legNum);
  else Serial.print("there is no leg with that number.\n");
  lowerLeg(leg, legNum);
}

void moveLegIn(Servo leg[], int legNum) {
  if (legNum == 0 || legNum == 2){
    for (hipPos[legNum]; hipPos[legNum] >= 45; hipPos[legNum]--) {
      leg[0].write(hipPos[legNum]);
      delay(speed);
    }
  }
  else if (legNum == 1 || legNum == 3) {
   for (hipPos[legNum]; hipPos[legNum] <= 135; hipPos[legNum]++) {
      leg[0].write(hipPos[legNum]);
      delay(speed);
    }
  }
  else Serial.print("there is no leg with that number.\n");
}

void moveLegOut(Servo leg[], int legNum) {
  if (legNum == 0 || legNum == 2) {
    for (hipPos[legNum]; hipPos[legNum] <= 135; hipPos[legNum]++) {
      leg[0].write(hipPos[legNum]);
      delay(speed);
    }
  }
  else if (legNum == 1 || legNum == 3) {
    for (hipPos[legNum]; hipPos[legNum] >= 45; hipPos[legNum]--) {
      leg[0].write(hipPos[legNum]);
      delay(speed);
    }
  }
  else Serial.print("there is no leg with that number.\n");
}

void leanToSide(int legNum) {
  switch(legNum) {
    case 0:   //legNum = RF   
      stepBack(LBleg, LB);
      for (hipPos[LF]; hipPos[LF] >= 45; hipPos[LF]--) {
        LFleg[0].write(hipPos[LF]);
        RBleg[0].write(hipPos[RB]);
        if (anklePos[LB] > 75) {
          LBleg[2].write(anklePos[LB]);
          anklePos[LB]--;
        }
        if (hipPos[RB] < 135) 
          hipPos[RB]++; 
        delay(speed);
      }
      raiseLeg(RFleg, legNum);
      break;
    case 1: //legNum = LF
      stepBack(RBleg, RB);
      for (hipPos[RF]; hipPos[RF] <= 135; hipPos[RF]++) {
        RFleg[0].write(hipPos[RF]);
        LBleg[0].write(hipPos[LB]);
        if (anklePos[RB] < 115) {
          RBleg[2].write(anklePos[RB]);
          anklePos[RB]++;
        }
        if (hipPos[LB] > 45)
          hipPos[LB]--;
        delay(speed);
      }
      raiseLeg(LFleg, LF);
      break;
    case 2: // legNum = LB
      stepForward(RFleg, RF);
      for (hipPos[LF]; hipPos[LF] >= 45; hipPos[LF]--) {
        LFleg[0].write(hipPos[LF]);
        RBleg[0].write(hipPos[RB]);
        if (anklePos[RF] >= 75) {
          RFleg[2].write(anklePos[RF]);
          anklePos[RF]--; 
        }
        if (hipPos[RB] < 135)
          hipPos[RB]++;
        delay(speed);
      }
      raiseLeg(LBleg, LB);
      break;
    case 3: //legNum = RB
      stepForward(LFleg, LF);
      for (hipPos[RF]; hipPos[RF] <= 135; hipPos[RF]++) {
        RFleg[0].write(hipPos[RF]);
        LBleg[0].write(hipPos[LB]);
        if (anklePos[LF] <= 115) {
          LFleg[2].write(anklePos[LF]);
          anklePos[LF]++;
        }
        if (hipPos[LB] > 45)
          hipPos[LB]--;
        delay(speed);
      }
      raiseLeg(RBleg, RB);
      break;
    default:
      break;
  }
}

void waveLeg(int legNum) {
  switch(legNum) {
    case 0:
      moveLegOut(RFleg, RF);
      raiseLeg(RFleg, RF);
      for (int i = 0; i < 3; i++) {
        anklePos[RF] = 135;
        RFleg[2].write(anklePos[RF]);
        delay(200);
        anklePos[RF] = 45;
        RFleg[2].write(anklePos[RF]);
        delay(200);
      }
      centerLeg(RFleg, RF);
      break;
    case 1:
      moveLegOut(LFleg, LF);
      raiseLeg(LFleg, LF);
      for (int i = 0; i < 3; i++) {
        anklePos[LF] = 45;
        LFleg[2].write(anklePos[LF]);
        delay(200);
        anklePos[LF] = 135;
        LFleg[2].write(anklePos[LF]);
        delay(200);
      }
      centerLeg(LFleg, LF);
      break;
    case 2: 
      moveLegOut(LBleg, LB);
      raiseLeg(LBleg, LB);
      for (int i = 0; i < 3; i++) {
        anklePos[LB] = 135;
        LBleg[2].write(anklePos[LB]);
        delay(200);
        anklePos[LB] = 45;
        LBleg[2].write(anklePos[LB]);
        delay(200);
      }
      centerLeg(LBleg, LB);
      break;
    case 3:
      moveLegOut(RBleg, RB);
      raiseLeg(RBleg, RB);
      for (int i = 0; i < 3; i++) {
        anklePos[RB] = 45;
        RBleg[2].write(anklePos[RB]);
        delay(200);
        anklePos[RB] = 135;
        RBleg[2].write(anklePos[RB]);
        delay(200);
      }
      centerLeg(RBleg, RB);
      break;
    default:
      Serial.print("\nI don't know which leg to wave.\n");
      break;
  }
}
