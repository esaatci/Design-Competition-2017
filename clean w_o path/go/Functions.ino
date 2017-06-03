#include "Functions.h"
//----------------Functions-----------------//
void xbee(){
  // see if the xbee has sent any data
  if (Serial4.available() > 0) {
    msg[msg_index] = Serial4.read();
    // if you get a newline, there is data to read
    if (msg[msg_index] == '\n') {
      msg_index = 0;
      // data is in the format of two floats seperated by spaces
      sscanf(msg, "%f %f", &xOpponent, &yOpponent);
      /*
      //Serial.print("op: ");
      Serial.print(xOpponent);
      Serial.print(" ");
      Serial.println(yOpponent);
      */
    }
    else {
      // did not get a newline yet, just store for later
      msg_index++;
      if (msg_index == 100) {
        msg_index = 0;
      }
    }
  }
}

void dirCorr(){
  float a;
  float dX = xFilt-xFilt2;
  //Serial.print(dX);
  //Serial.print(" ");
  float dY = yFilt-yFilt2;
  //Serial.println(dY);
  a=0;
  if(dY>=0){
    if(dX>=0){
      a = atan((dY)/(dX))+PI/2;
    }else{
      a = atan((dY)/(dX))-PI/2;
    }
  }else if(dY<0){
    if(dX>=0){
      a = atan((dY)/(dX))+PI/2;
    }else{
      a = atan((dY)/(dX))-PI/2;
    }
  }
  Ang = Ang + a;
}
void go2Pos(float tx, float ty, float margin){
  float dX = tx - xFilt;
  float dY = ty - yFilt;
  vector.fromCartesian(dY,dX);
  Mag = pGain*vector.getR();
  Ang = vector.getAngle();
  if ((abs(dX) <= margin) && (abs(dY) <= margin)) there = true;
  else there = false;
  }

void nick(){
  // if the sensor data is new
  if (V1.useMe == 1) {
    V1.useMe = 0;
    // calculate the position and filter it
    xPos = tan((V1.vertAng - 90.0) * DEG_TO_RAD) * LIGHTHOUSEHEIGHT;
    yPos = tan((V1.horzAng - 90.0) * DEG_TO_RAD) * LIGHTHOUSEHEIGHT;

    if((abs(xPos) > 10) || (abs(yPos) > 10)){
      xPos = xOld;
      yPos = yOld;
    }
    
    xFilt = xOld * 0.5 + xPos * 0.5;
    yFilt = yOld * 0.5 + yPos * 0.5;
    xOld = xFilt;
    yOld = yFilt;
    // blink the led so you can tell if you are getting sensor data
    digitalWrite(led1, state);
    if (state == 1) {
      state = 0;
    }
    else {
      state = 1;
    }
  }
    if (V2.useMe == 1) {
    V2.useMe = 0;
    // calculate the position and filter it
    xPos2 = tan((V2.vertAng - 90.0) * DEG_TO_RAD) * LIGHTHOUSEHEIGHT;
    yPos2 = tan((V2.horzAng - 90.0) * DEG_TO_RAD) * LIGHTHOUSEHEIGHT;

    if((abs(xPos2) > 7) || (abs(yPos2) > 7)){
      xPos2 = xOld2;
      yPos2 = yOld2;
    }
    
    xFilt2 = xOld2 * 0.5 + xPos2 * 0.5;
    yFilt2 = yOld2 * 0.5 + yPos2 * 0.5;
    xOld2 = xFilt2;
    yOld2 = yFilt2;

    // blink the led so you can tell if you are getting sensor data
    digitalWrite(led2, state2);
    if (state2 == 1) {
      state = 0;
    }
    else {
      state2 = 1;
    }
  }
      digitalWrite(led1, state);
      if (state == 1) {
        state = 0;
      }
      else {
        state = 1;
      }
      digitalWrite(led2, state);
      if (state2 == 1) {
        state2 = 0;
      }
      else {
        state2 = 1;
      }
}
  
void circleGo(int radius){
  while(1){
      static float r = radius;
  static float phi = 0;
  if (phi >= 2*PI){
    phi = 0;
    }
  phi = phi+0.01;
  go(r,phi);
  delay(10);
  }
}
void go(float Amp,float theta){
  vector.fromPolar(Amp,theta); //r <! 255
  vX(vector.getX());
  vY(vector.getY());
  //delay(10);
}
void vX(float xVect){
  if(xVect >= 0){
    digitalWrite(dir1, HIGH);
    digitalWrite(dir3, LOW);
  } else {
    digitalWrite(dir1, LOW);
    digitalWrite(dir3, HIGH);
  }
  int x = (int) abs(xVect);
  analogWrite(pwm1, x);
  analogWrite(pwm3, x);
}

void vY(float yVect){
  if(yVect >= 0){
    digitalWrite(dir2, HIGH);
    digitalWrite(dir4, LOW);
  } else {
    digitalWrite(dir2, LOW);
    digitalWrite(dir4, HIGH);
  }
  int y = (int) abs(yVect);
  analogWrite(pwm2, y);
  analogWrite(pwm4, y);
}
void vLimit(int lim){
  if(Mag >= lim) Mag = lim;
}
void printVive(){
  Serial.print(xFilt);
  Serial.print(" ");
  Serial.print(yFilt);
  Serial.print(" ");
  Serial.print(xFilt2);
  Serial.print(" ");
  Serial.println(yFilt2);
}
void printXbee(){
  Serial.print(xOpponent);
  Serial.print(" ");
  Serial.println(yOpponent);
}
void goTillReach(float goX,float goY){
    while (!there) {
    nick();                   //acquire vive sensor data
    go2Pos(goX,goY,margin);   //go to the <margin> close of coordinates syntax: (x,y,margin)
    dirCorr();                //correction for the rotational drift
    vLimit(SpeedLim);         //max limit for the speed
    go(Mag, Ang);             //drive motors
  }
  there = 0;
}
//------------------------------------------//

//------------Interrupts--------------------//
// the sensor interrupt
void ISRV1(){
  // get the time the interrupt occured
  unsigned long mic = micros();
  int i;

  // shift the time into the buffer
  for (i = 0; i < 10; i++) {
    V1.changeTime[i] = V1.changeTime[i + 1];
  }
  V1.changeTime[10] = mic;

  // if the buffer is full
  if (V1.collected < 11) {
    V1.collected++;
  }
  else {
    // if the times match the waveform pattern
    if ((V1.changeTime[1] - V1.changeTime[0] > 7000) && (V1.changeTime[3] - V1.changeTime[2] > 7000) && (V1.changeTime[6] - V1.changeTime[5] < 50) && (V1.changeTime[10] - V1.changeTime[9] < 50)) {
      V1.horzAng = (V1.changeTime[5] - V1.changeTime[4]) * DEG_PER_US;
      V1.vertAng = (V1.changeTime[9] - V1.changeTime[8]) * DEG_PER_US;
      V1.useMe = 1;
    }
  }
}
//second sensor interrupt
void ISRV2(){
  // get the time the interrupt occured
  unsigned long mic = micros();
  int i;

  // shift the time into the buffer
  for (i = 0; i < 10; i++) {
    V2.changeTime[i] = V2.changeTime[i + 1];
  }
  V2.changeTime[10] = mic;

  // if the buffer is full
  if (V2.collected < 11) {
    V2.collected++;
  }
  else {
    // if the times match the waveform pattern
    if ((V2.changeTime[1] - V2.changeTime[0] > 7000) && (V2.changeTime[3] - V2.changeTime[2] > 7000) && (V2.changeTime[6] - V2.changeTime[5] < 50) && (V2.changeTime[10] - V2.changeTime[9] < 50)) {
      V2.horzAng = (V2.changeTime[5] - V2.changeTime[4]) * DEG_PER_US;
      V2.vertAng = (V2.changeTime[9] - V2.changeTime[8]) * DEG_PER_US;
      V2.useMe = 1;
    }
  }
}
//------------------------------------------//

//-----------------Setup--------------------//

void dc_setup(){
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(dir4, OUTPUT);
  
//Lighthouse
  Serial.begin(9600);
  pinMode(led1, OUTPUT); //LED
  pinMode(led2, OUTPUT); 
  pinMode(V1PIN, INPUT);
  pinMode(V2PIN, INPUT);
  
  // initialize the sensor variables
  V1.horzAng = 0;
  V1.vertAng = 0;
  V1.useMe = 0;
  V1.collected = 0;

  V2.horzAng = 0;
  V2.vertAng = 0;
  V2.useMe = 0;
  V2.collected = 0;
  
attachInterrupt(digitalPinToInterrupt(V1PIN), ISRV1, CHANGE);
attachInterrupt(digitalPinToInterrupt(V2PIN), ISRV2, CHANGE);

// to listen to the xbee
  Serial4.begin(9600);
  
//  void PathSetup();
}
//------------------------------------------//
