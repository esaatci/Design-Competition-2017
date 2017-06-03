#include "Functions.h"
/*
 * must include the Coordinates library to compile!!
 * ^ you can find it from Sketch > Include Library > Manage Libraries... >  
 * Type "Coordinates" to the search bar and install the Coordinates library
 * 
 */


//Easy access to some global variables
int pGain = 500;    //-- gain
float margin = 0.1; //-- go2Pos margin
int SpeedLim = 225; //-- speed limit b/w 0 to 255

void setup() {
  dc_setup();
}

//--------------Main Loop-------------------//
void loop() {
  //Sensor Stuff
  //nick();              //Vive sensor data acquisition
  //printVive();         //print Vive Sensor data
  //xbee();              //Opponent's coordinates over xbee
  //printXbee();         //print Opponent's position
  //goTillReach(0,1);    //go until you reach the coordinates (x,y)
  circleGo(150);
  
}
//------------------------------------------//
