#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
  //---------------Includes-------------------//
  #include <Coordinates.h>
  #include <math.h>
  #include <avr/io.h>
  #include <avr/interrupt.h>
  //#include "Path.h"
  //------------------------------------------//
  
  //--------------Constants-------------------//
  //1st wheel
  #define dir1 2
  #define pwm1 3
  //2nd wheel
  #define dir2 4
  #define pwm2 5
  //3rd wheel
  #define dir3 6
  #define pwm3 7
  //4th wheel
  #define dir4 8
  #define pwm4 9
  
  #define led1 13 //the led on the board
  #define led2 12
  #ifndef PI
  #define PI 3.1415926535897932384626433832795
  #endif
  //------------------------------------------//
  
  //-------------Lighthouse stuff-------------//
  #define V1PIN 14
  #define V2PIN 15
  #define V3PIN 16
  #define V4PIN 17
  #define DEG_PER_US 0.0216 // (180 deg) / (8333 us)
  #ifndef DEG_TO_RAD
  #define DEG_TO_RAD 3.14/180.0
  #endif
  #define LIGHTHOUSEHEIGHT 7.0
    // structure to store the sensor data
  typedef struct {
    unsigned long changeTime[11];
    double horzAng;
    double vertAng;
    int useMe;
    int collected;
  } viveSensor;
  //------------------------------------------//
  
  //-------------Global Variables-------------//
  Coordinates vector = Coordinates();
  float Mag = 0,Ang = 0;
  bool there = 0;
  // variables for the xbee data
  char msg[100];
  int msg_index = 0;
  float xOpponent=-5.2, yOpponent=-7;
  // variables for the sensor data and filter
  volatile viveSensor V1;
  volatile viveSensor V2;
  volatile viveSensor V3;
  volatile viveSensor V4;
  int state = 0, state2 = 0;
  float xPos, yPos, xOld =0, yOld=0 , xFilt=5.5, yFilt=4;
  float xPos2, yPos2, xOld2 =0, yOld2=0 , xFilt2=5.5, yFilt2=4;
  //------------------------------------------//
  
  //-------Function Prototypes----------------//
  void dc_setup();                            //setup code
  void go(float Amp,float theta);             //driving motors
  void vX(float xVect);                       //motor 1 & 3
  void vY(float yVect);                       //motor 2 & 4
  void circleGo(int radius);                  //test motor functions by making a circle
  void nick();                                //acquire vive sensor data
  void xbee();                                //acquire opponent's position over xbee
  void ISRV1();                               //ISR for 1st vive sensor
  void ISRV2();                               //ISR for 2nd vive sensor
  void go2Pos(float tx, float ty, float margin); //calculate Mag and Ang for the go() function
  void dirCorr();                             //correct the Mag and Ang based on the orientation of the robot
  void vLimit(int lim);                       //limit the speed
  void printVive();                           //print the location
  void printXbee();                           //print opponent location
  void goTillReach(float goX,float goY);      //go until you reach the coordinates
  //------------------------------------------//
#endif
