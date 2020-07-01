
//chris fite
//060620
//reworking for acryllic frame, servos


//write stepBack()


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

//define hipPos constants
const int frontPos[4] = {30, 145, 90, 120};
const int backPos[4] = {145, 25, 45, 165};
const int diagPos[4] = {90, 90, 90, 90};
const int sidePos[4] = {120, 45, 135, 45}; 
//define kneePos consts
const int kneeUpPos[4] = {0, 180, 0, 180};
const int kneeDownPos[4] = {180, 0, 180, 0};
//define anklePos consts
const int ankleInPos[4] = {0, 180, 0, 180};
const int ankleOutPos[4] = {180, 0, 180, 0};

int hipPos[4];   
int kneePos[4];
int anklePos[4];

int speed = 15;

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//protoyping functions
int pulseWidth(int);
void moveServo(int, int);
void centerAllLegs(); // sets all servos to 90
void centerLeg(int[], int);
void moveLegDiag(int[], int); // puts legs in diagonal
void moveLegFront(int[], int);
void moveLegBack(int[], int);
void moveLegToSide(int[], int); //puts legs out to side
void raiseLeg(int[], int);
void lowerLeg(int[], int);
void stepForward(int[], int);
void stepBack(int[], int);
void moveAllLegsBack();
void moveAllLegsDiag();
void walkForward();
void extendLeg(int[], int);
void extendAll();
void squat();
void bendKnee(int[], int);
void twistCW();
void twistCCW();
void resumeStartPos();


void setup() {
  delay(1000);
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);  // Analog servos run at ~60 Hz updates

  //0=RF, 1=LF, 2=LB, 3=RB
  for (int i = 0; i < 4; i++) {
    hipPos[i] = 90;
    kneePos[i] = 90;
    anklePos[i] = 90;
  }
  
  //resumeStartPos();
  Serial.println("let's make it happen cap'n");
 
}

void loop() {

  raiseLeg(RFleg, RF);

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

void moveLegDiag(int leg[], int legNum) {
  if (hipPos[legNum] > diagPos[legNum]) {
    for (hipPos[legNum]; hipPos[legNum] > diagPos[legNum]; hipPos[legNum]--) {
      moveServo(leg[hip], hipPos[legNum]);
      delay(speed);
    }
  }
  else if (hipPos[legNum] < diagPos[legNum]) {
    for (hipPos[legNum]; hipPos[legNum] < diagPos[legNum]; hipPos[legNum]++) {
      moveServo(leg[hip], hipPos[legNum]);
      delay(speed);
    }
  }
}

void moveLegFront(int leg[], int legNum) {
  if (hipPos[legNum] > frontPos[legNum]) {
    for (hipPos[legNum]; hipPos[legNum] > frontPos[legNum]; hipPos[legNum]--) {
      moveServo(leg[hip], hipPos[legNum]);
      delay(speed);
    }
  }
  else if (hipPos[legNum] < frontPos[legNum]) {
    for (hipPos[legNum]; hipPos[legNum] < frontPos[legNum]; hipPos[legNum]++) {
      moveServo(leg[hip], hipPos[legNum]);
      delay(speed);
    }
  }
}

void moveLegBack(int leg[], int legNum) {
  if (hipPos[legNum] > backPos[legNum]) {
    for (hipPos[legNum]; hipPos[legNum] > backPos[legNum]; hipPos[legNum]--) {
      moveServo(leg[hip], hipPos[legNum]);
      delay(speed);
    }
  }
  else if (hipPos[legNum] < backPos[legNum]) {
    for (hipPos[legNum]; hipPos[legNum] < backPos[legNum]; hipPos[legNum]++) {
      moveServo(leg[hip], hipPos[legNum]);
      delay(speed);
    }
  }
}

void moveLegToSide(int leg[], int legNum) { 
  if (hipPos[legNum] > sidePos[legNum]) {
      for (hipPos[legNum]; hipPos[legNum] >= sidePos[legNum]; hipPos[legNum]--){
        moveServo(leg[hip], hipPos[legNum]);
        delay(speed);
      }
  }
  else if (hipPos[legNum] < sidePos[legNum]) {
    for (hipPos[legNum]; hipPos[legNum] <= sidePos[legNum]; hipPos[legNum]++) {
        moveServo(leg[hip], hipPos[legNum]);
        delay(speed);
    }
  }
}

void moveAllLegsDiag() {
  while (hipPos[RF] != diagPos[RF] || hipPos[LF] != diagPos[LF] || hipPos[LB] != diagPos[LB] || hipPos[RB] != diagPos[RB]){ 
    for (int i = 0; i < 4; i++) {
      switch(i) {
        case 0: 
          moveServo(RFleg[hip], hipPos[RF]);
          break; 
        case 1:
          moveServo(LFleg[hip], hipPos[LF]);
          break;
        case 2:
          moveServo(LBleg[hip], hipPos[LB]);
          break;
        case 3:
          moveServo(RBleg[hip], hipPos[RB]);
          break;
        default:
          Serial.println("no such leg");
          break;
      }
      if (hipPos[i] > diagPos[i]) hipPos[i]--;      
      else if (hipPos[i] < diagPos[i]) hipPos[i]++;
      else hipPos[i] = diagPos[i]; //idk if necessary
      delay(speed);     
    }
  }   
}

void raiseLeg(int leg[], int legNum) {
  while (kneePos[legNum] != kneeUpPos[legNum] || anklePos[legNum] != ankleInPos[legNum]) {
    if (kneePos[legNum] > kneeUpPos[legNum]) {
      moveServo(leg[knee], kneePos[legNum]);
      kneePos[legNum]--;
    }
    else if (kneePos[legNum] < kneeUpPos[legNum]) {
      moveServo(leg[knee], kneePos[legNum]);
      kneePos[legNum]++;
    }
    }
    if (anklePos[legNum] > ankleInPos[legNum]) {
      moveServo(leg[ankle], anklePos[legNum]);
      anklePos[legNum]--;
    }
    else if (anklePos[legNum] < ankleInPos[legNum]) {
      moveServo(leg[ankle], anklePos[legNum]);
      anklePos[legNum]++;
    }
    delay(speed);
  /*
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
  */
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
  //assume initial stance

  switch(legNum) {
    case 0: //RF
    //bend LB and move other two legs away from bent leg
      while (hipPos[LF] > 30 || hipPos[RB] > 30 || kneePos[LB] != 90) {
        if (hipPos[LF] > 30) {
          moveServo(LFleg[hip], hipPos[LF]);
          hipPos[LF]--;
        }
        if (hipPos[RB] > 30) {
          moveServo(RBleg[hip], hipPos[RB]);
          hipPos[RB]--;
        }
        if (kneePos[LB] > 90) {
          moveServo(LBleg[knee], kneePos[LB]);
          kneePos[LB]--;
        }
        else if (kneePos[LB] < 90) {
          moveServo(LBleg[knee], kneePos[LB]);
          kneePos[LB]++;
        }
        delay(speed);
      }  
  //pick up and move(RF)
      raiseLeg(RFleg, RF);
      moveLegFront(RFleg, RF);
      extendLeg(RFleg, RF);
      extendLeg(LBleg, LB);
      break;
    case 1: //LF
      while (hipPos[RF] < 150 || hipPos[LB] < 150 || kneePos[RB] != 90) {
        if (hipPos[RF]< 150) {
          moveServo(RFleg[hip], hipPos[RF]);
          hipPos[RF]++;
        }
        if (hipPos[LB] < 150) {
          moveServo(LBleg[hip], hipPos[LB]);
          hipPos[LB]++;
        }
        if (kneePos[RB] > 90) {
          moveServo(RBleg[knee], kneePos[RB]);
          kneePos[RB]--;
        }
        else if (kneePos[RB] < 90) {
          moveServo(RBleg[knee], kneePos[RB]);
          kneePos[RB]++;
        }
        delay(speed);
      }            
      raiseLeg(LFleg, LF);
      moveLegFront(LFleg, LF);
      extendLeg(LFleg, LF);
      extendLeg(RBleg, RB);
      break;
    case 2: //LB
      while (hipPos[LF] < 60 || hipPos[RB] > 20 || kneePos[RF] != 90) {
        if(hipPos[LF] < 60) {
          moveServo(LFleg[hip], hipPos[LF]);
          hipPos[LF]++;
        }
        if (hipPos[RB] > 20) {
          moveServo(RBleg[hip], hipPos[RB]);
          hipPos[RB]--;
        }
        if (kneePos[RF] > 90) {
          moveServo(RFleg[knee], kneePos[RF]);
          kneePos[RF]--;
        }
        else if (kneePos[RF] < 90) {
          moveServo(RFleg[knee], kneePos[RF]);
          kneePos[RF]++;
        }
        delay(speed);
      }
      raiseLeg(LBleg, LB);
      moveLegFront(LBleg, LB);
      extendLeg(LBleg, LB);
      extendLeg(RFleg, RF);
      break;
    case 3: //RB
      while (hipPos[RF] > 120 || hipPos[LB] < 150  || kneePos[LF] != 90) {
        if (hipPos[RF] > 120) {
          moveServo(RFleg[hip], hipPos[RF]);
          hipPos[RF]--;
        }
        if (hipPos[LB] < 150) {
          moveServo(LBleg[hip], hipPos[LB]);
          hipPos[LB]++;
        }
         if (kneePos[LF] > 90) {
          moveServo(LFleg[knee], kneePos[LF]);
          kneePos[LF]--;
        }
        else if (kneePos[LF] < 90) {
          moveServo(LFleg[knee], kneePos[LF]);
          kneePos[LF]++;
        }
        delay(speed);
      }
      raiseLeg(RBleg, RB);
      moveLegFront(RBleg, RB);
      extendLeg(RBleg, RB);
      extendLeg(LFleg, LF);
      break;
    default:
     Serial.println("there is no leg with that number");
      break;
  }
}

void stepBack(int leg[], int legNum) {
  
}

void walkForward() {
/*
 * 4 beat timing
 * RB lift, move forward; everyone move back
 * RF forward
 * LB forward
 * LF forward; RB fully moved back
 */
 
//LB
      while (hipPos[LF] < 60 || hipPos[RB] > 20 || kneePos[RF] != 90) {
        if(hipPos[LF] < 60) {
          moveServo(LFleg[hip], hipPos[LF]);
          hipPos[LF]++;
        }
        if (hipPos[RB] > 20) {
          moveServo(RBleg[hip], hipPos[RB]);
          hipPos[RB]--;
        }
        if (kneePos[RF] > 90) {
          moveServo(RFleg[knee], kneePos[RF]);
          kneePos[RF]--;
        }
        else if (kneePos[RF] < 90) {
          moveServo(RFleg[knee], kneePos[RF]);
          kneePos[RF]++;
        }
        delay(speed);
      }
      raiseLeg(LBleg, LB);
      moveLegFront(LBleg, LB);
      extendLeg(LBleg, LB);
      extendLeg(RFleg, RF);
//LF
  while (kneePos[RB] != 75) { //bend RB knee to 75
    if (kneePos[RB] > 75)  {
      moveServo(RBleg[knee], kneePos[RB]);
      kneePos[RB]--;
      delay(speed);
    }
    else if (kneePos[RB] < 75) {
      moveServo(RBleg[knee], kneePos[RB]);
      kneePos[RB]++;
      delay(speed);    
    }
  }
  raiseLeg(LFleg, LF);
  moveLegFront(LFleg, LF);
  extendLeg(LFleg, LF);
  extendLeg(RBleg, RB);
  
  //move lefts legs back to orig pos
  moveAllLegsDiag();

}

void moveAllLegsBack() {
 //2 135, 3 45 - move out
//0 45, 1 135 - move in
  while ((hipPos[RF] > backPos[RF]) || (hipPos[LF] < backPos[LF]) || (hipPos[LB] < backPos[LB])|| (hipPos[RB] > backPos[RB])) {
    if (hipPos[RF] > backPos[RF]) {
      moveServo(RFleg[hip], hipPos[RF]);
      hipPos[RF]--;
    }
    if (hipPos[LF] < backPos[LF] ) {
      moveServo(LFleg[hip], hipPos[LF]);
      hipPos[LF]++;
    }
    if (hipPos[LB]< backPos[LB]) {
      moveServo(LBleg[hip], hipPos[LB]);
      hipPos[LB]++;
    }
    if (hipPos[RB] > backPos[RB]) {
      moveServo(RBleg[hip], hipPos[RB]);
      hipPos[RB]--;
    }
    delay(speed);
  }
}

void extendLeg(int leg[], int legNum) {
  switch(legNum) {
    case 0:
   
      for (kneePos[legNum]; kneePos[legNum] <= 135; kneePos[legNum]++){
        moveServo(leg[knee], kneePos[legNum]);
        if (anklePos[legNum] <= 135) {
          moveServo(leg[ankle], anklePos[legNum]);
          anklePos[legNum]++;
        }
        delay(speed);
      }
      break;
      case 2:
        for (kneePos[legNum]; kneePos[legNum] >= 45; kneePos[legNum]--){
        moveServo(leg[knee], kneePos[legNum]);
        if (anklePos[legNum] <= 135) {
          moveServo(leg[ankle], anklePos[legNum]);
          anklePos[legNum]++;
        }
        delay(speed);
      }
        break;
    case 1:
    case 3:
      for (kneePos[legNum]; kneePos[legNum] >= 45; kneePos[legNum]--){
        moveServo(leg[knee], kneePos[legNum]);
        if (anklePos[legNum] >= 45) {
          moveServo(leg[ankle], anklePos[legNum]);
          anklePos[legNum]--;
        }
        delay(speed);
      }
      break;
    default:
      Serial.println("There is no such leg number");
      break;
  }
}

void extendAll() {
  while (kneePos[RF] != 135 || kneePos[LF] != 45 || kneePos[LB] != 135 || kneePos[RB] != 45 ||
          anklePos[RF] != 135 || anklePos[LF] != 45 || anklePos[LB] != 135 || anklePos[RB] != 45) {
    if (kneePos[RF] > 135) {
      moveServo(RFleg[knee], kneePos[RF]);
      kneePos[RF]--;        
    }
    else if (kneePos[RF] < 135) {
      moveServo(RFleg[knee], kneePos[RF]);
      kneePos[RF]++;
    }
    if (anklePos[RF] > 135) {
      moveServo(RFleg[ankle], anklePos[RF]);
      anklePos[RF]--;
    }
    else if (anklePos[RF] < 135) {
      moveServo(RFleg[ankle], anklePos[RF]);
      anklePos[RF]++;
    }
    
    if (kneePos[LF] > 45) {
      moveServo(LFleg[knee],kneePos[LF]);
      kneePos[LF]--;        
    }
    else if (kneePos[LF] < 45) {
      moveServo(LFleg[knee], kneePos[LF]);
      kneePos[LF]++;
    }
    if (anklePos[LF] > 45) {
      moveServo(LFleg[ankle], anklePos[LF]);
      anklePos[LF]--;
    }
    else if (anklePos[LF] < 45) {
      moveServo(LFleg[ankle], anklePos[LF]);
      anklePos[LF]++;
    }

    if (kneePos[LB] > 135) {
      moveServo(LBleg[knee], kneePos[LB]);
      kneePos[LB]--;        
    }
    else if (kneePos[LB] < 135) {
      moveServo(LBleg[knee], kneePos[LB]);
      kneePos[LB]++;
    }    
    if (anklePos[LB] > 135) {
      moveServo(LBleg[ankle], anklePos[LB]);
      anklePos[LB]--;
    }
    else if (anklePos[LB] < 135) {
      moveServo(LBleg[ankle], anklePos[LB]);
      anklePos[LB]++;
    }

    if (kneePos[RB] > 45) {
      moveServo(RBleg[knee], kneePos[RB]);
      kneePos[RB]--;        
    }
    else if (kneePos[RB] < 45) {
      moveServo(RBleg[knee], kneePos[RB]);
      kneePos[RB]++;
    }
    if (anklePos[RB] > 45) {
      moveServo(RBleg[ankle], anklePos[RB]);
      anklePos[RB]--;
    }
    else if (anklePos[RB] < 45) {
      moveServo(RBleg[ankle], anklePos[RB]);
      anklePos[RB]++;
    }
    delay(speed);
    }          
}

void squat() { //all together now
  
  while (kneePos[RF] > 90 || kneePos[LF] < 90 || kneePos[LB] >90 || kneePos[RB] < 90 || 
          anklePos[RF] > 90 || anklePos[LF] < 90 || anklePos[LB] >90 || anklePos[RB] < 90) {
    //RF
    if (kneePos[RF] > 90) {
      moveServo(RFleg[knee], kneePos[RF]);
      kneePos[RF]--; 
    }    
    if (anklePos[RF] > 90) {
      moveServo(RFleg[ankle], anklePos[RF]);
      anklePos[RF]--;
    }
    //LF
    if (kneePos[LF] < 90) {
      moveServo(LFleg[knee], kneePos[LF]);
      kneePos[LF]++;
    }
    if (anklePos[LF] < 90) {
      moveServo(LFleg[ankle], anklePos[LF]);
      anklePos[LF]++;
    }
    //LB
    if (kneePos[LB] > 90) {
      moveServo(LBleg[knee], kneePos[LB]);
      kneePos[LB]--;
    }
    if (anklePos[LB] > 90) {
      moveServo(LBleg[ankle], anklePos[LB]);
      anklePos[LB]--;
    }
    //RB
    if (kneePos[RB] < 90) {
      moveServo(RBleg[knee], kneePos[RB]);
      kneePos[RB]++;
    }
    if (anklePos[RB] < 90) {
      moveServo(RBleg[ankle], anklePos[RB]);
      anklePos[RB]++;
    }
    delay(speed);
  }
  
}

void bendKnee(int leg[], int legNum) {
  switch(legNum) {
    case 0:
    case 2:
      for (kneePos[legNum]; kneePos[legNum] >= 90; kneePos[legNum]--) {
        moveServo(leg[knee], kneePos[legNum]);
        delay(speed);
      }
      break;
    case 1:
    case 3:
      for (kneePos[legNum]; kneePos[legNum] <= 90; kneePos[legNum]++) {
              moveServo(leg[knee], kneePos[legNum]);
              delay(speed);
      }
      break;
    default:
      Serial.println("there is no leg by that name");
  }
}

void twistCW() {
/*
  moveServo(RFleg[hip], 150);
  moveServo(LFleg[hip], 60);
  moveServo(LBleg[hip], 150);
  moveServo(RBleg[hip], 60);
*/  
  while (hipPos[RF] != 150 || hipPos[LF] != 60 || hipPos[LB] != 150 || hipPos[RB] != 60) {
    if (hipPos[RF] < 150) {
      moveServo(RFleg[hip], hipPos[RF]);
      hipPos[RF]++;
    }
    else if (hipPos[RF] > 150) {
      moveServo(RFleg[hip], hipPos[RF]);
      hipPos[RF]--;
    }
    if (hipPos[LF] < 60) {
      moveServo(LFleg[hip], hipPos[LF]);
      hipPos[LF]++;
    }
    else if (hipPos[LF] > 60) {
      moveServo(LFleg[hip], hipPos[LF]);
      hipPos[LF]--;
    }
    if (hipPos[LB] < 150) {
      moveServo(LBleg[hip], hipPos[LB]);
      hipPos[LB]++;
    }
    else if (hipPos[LB] > 150) {
      moveServo(LBleg[hip], hipPos[LB]);
      hipPos[LB]--;
    }
    if (hipPos[RB] < 60) {
      moveServo(RBleg[hip], hipPos[RB]);
      hipPos[RB]++;
    }
    else if (hipPos[RB] > 60) {
      moveServo(RBleg[hip], hipPos[RB]);
      hipPos[RB]--;
    }
    delay(speed);
  }
}

void twistCCW() {
  /*
  moveServo(RFleg[hip], 120);
  moveServo(LFleg[hip], 30);
  moveServo(LBleg[hip], 120); 
  moveServo(RBleg[hip], 30);
  */
  while (hipPos[RF] != 120 || hipPos[LF] != 30 || hipPos[LB] != 120 || hipPos[RB] != 30) {
    if (hipPos[RF] > 120) {
      moveServo(RFleg[hip], hipPos[RF]);
      hipPos[RF]--;
    }
    else if (hipPos[RF] < 120) {
      moveServo(RFleg[hip], hipPos[RF]);
      hipPos[RF]++;
    }
    if (hipPos[LF] > 30) {
      moveServo(LFleg[hip], hipPos[LF]);
      hipPos[LF]--;
    }
    else if (hipPos[LF] < 30) {
      moveServo(LFleg[hip], hipPos[LF]);
      hipPos[LF]++;
    }
    if (hipPos[LB] > 120) {
      moveServo(LBleg[hip], hipPos[LB]);
      hipPos[LB]--;
    }
    else if (hipPos[LB] < 120) {
      moveServo(LBleg[hip], hipPos[LB]);
      hipPos[LB]++;
    }
    if (hipPos[RB] > 30) {
      moveServo(RBleg[hip], hipPos[RB]);
      hipPos[RB]--;
    }
    else if (hipPos[RB] < 30) {
      moveServo(RBleg[hip], hipPos[RB]);
      hipPos[RB]++;
    }
    delay(speed);
  }
}

void resumeStartPos() {
  //set legs to inital positions
  centerAllLegs();
 // moveAllLegsOut();
  //extendAll();
}
