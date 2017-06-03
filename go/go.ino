#include "Functions.h"

int pGain = 500; //--Golbal Var. for gain (here for easy access)
void setup() {
  // put your setup code here, to run once:
  delay(10);
  nick();
  xbee();
  dc_setup();
  //Serial.print(xOpponent);
}

//--------------Main Loop-------------------//
void loop() {
  
  location us = (location) {
   xFilt, yFilt
  };
  police = coordinatesToMap(us);
  //location them = (location) {
   // xOpponent, yOpponent
  //};
  //Tony = coordinatesToMap(them);

  //Sensor Stuff
  nick();              //Vive sensor data acquisition
  //printVive();         //print Vive Sensor data
  xbee();              //Opponent's coordinates over xbee
  //printXbee();       //print Opponent's position

  //Path
//  while (!queue.isEmpty()) {
//    queue.pop();
//  }
  dest = corners[3];
  //a_star_search(costsofar, police, dest, Tony);
//  locationMap nextLocMap = queue.pop();
//  float xOffset = abs( (viveCoordinates[police.X][police.Y].X - viveCoordinates[nextLocMap.X][nextLocMap.Y].X));
//  float yOffset = abs( (viveCoordinates[police.X][police.Y].Y - viveCoordinates[nextLocMap.X][nextLocMap.Y].Y));
//  int dir = queueDir.pop();
//  if (dir == 1 || 2){
//    goDir(dir, xOffset);
//  }
//  else {
//    goDir(dir, yOffset);
//  }
  
//  Serial.print("Tony :");
//  Serial.print(Tony.X);
//  Serial.print(" ");
//  Serial.println(Tony.Y);
//  //  Serial.print("xOpponent: ");
//  //  Serial.print(xOpponent);
//  //  Serial.print(" ");
//  //  Serial.println(yOpponent);
//    Serial.print("police XY:  ");
//    Serial.print(police.X);
//    Serial.print(" ");
//    Serial.println(police.Y);
////  Serial.print("Raw police location");
////  Serial.print(xFilt);
////   Serial.print(" ");
////  Serial.println(yFilt);
//    Serial.print("Dest: ");
//    Serial.print(dest.X);
//    Serial.print(" ");
//    Serial.println(dest.Y);
//    Serial.print("Next: ");
//    Serial.print(nextLocMap.X);
//    Serial.print(" ");
//    Serial.println(nextLocMap.Y);
  //  location nextLoc = mapToCoordinates(nextLocMap);
  // Serial.print("Next Coordinates: ");
  //  Serial.print(nextLoc.X);
  //  Serial.print(" ");
  //  Serial.println(nextLoc.Y);
//  Serial.print("there ");
//  Serial.println(there);
  //delay(100);
  
  while (!there) {
    printVive();
    nick();
    location us = (location) {
    xFilt, yFilt
    };
    police = coordinatesToMap(us);
 
  go2Pos(4.10, -0.33, 0.1); //go to the <margin> close of coordinates (x,y,margin) -.6,-.4
  
  //goDir(<Dir>,<distance>) // Dir {1:+x 2:-x 3:+y 4-y}
  //go2Pos(go2x,go2y,0.25);
  //Driving
  dirCorr();           //correction for the rotational drift
    vLimit(180);         //max limit for the speed
  //Serial.println(Ang);
  go(Mag, Ang);
  //Serial.print(there);
  //Serial.println(there);
  }
  there = 0;
  while (!there) {
    printVive();
    nick();
    location us = (location) {
    xFilt, yFilt
    };
    police = coordinatesToMap(us);
 
  go2Pos(4.45, -5.69, 0.1); //go to the <margin> close of coordinates (x,y,margin) -.6,-.4
  
  //goDir(<Dir>,<distance>) // Dir {1:+x 2:-x 3:+y 4-y}
  //go2Pos(go2x,go2y,0.25);
  //Driving
  dirCorr();           //correction for the rotational drift
  vLimit(180);         //max limit for the speed
  //Serial.println(Ang);
  go(Mag, Ang);
  //Serial.print(there);
  //Serial.println(there);
  }
  there = 0;
  while (!there) {
    nick();
    location us = (location) {
   xFilt, yFilt
  };
  police = coordinatesToMap(us);
  
  go2Pos(-0.54, -6.10, 0.1); //go to the <margin> close of coordinates (x,y,margin) -.6,-.4
  
  //goDir(<Dir>,<distance>) // Dir {1:+x 2:-x 3:+y 4-y}
  //go2Pos(go2x,go2y,0.1);
  //Driving
  dirCorr();           //correction for the rotational drift
  vLimit(180);         //max limit for the speed
  //Serial.println(Ang);
  go(Mag, Ang);

  //Serial.println(there);
  }
  there = 0;
  while (!there) {
    nick();
    location us = (location) {
   xFilt, yFilt
  };
  police = coordinatesToMap(us);
  
  go2Pos(-6.31, -6.58, 0.1); //go to the <margin> close of coordinates (x,y,margin) -.6,-.4
  
  //goDir(<Dir>,<distance>) // Dir {1:+x 2:-x 3:+y 4-y}
  //go2Pos(go2x,go2y,0.1);
  //Driving
  dirCorr();           //correction for the rotational drift
  vLimit(180);         //max limit for the speed
  //Serial.println(Ang);
  go(Mag, Ang);

  //Serial.println(there);
  }
  there = 0;
  while (!there) {
    nick();
    location us = (location) {
   xFilt, yFilt
  };
  police = coordinatesToMap(us);
 
  go2Pos(-6.05, -0.9, 0.1); //go to the <margin> close of coordinates (x,y,margin) -.6,-.4
  
  //goDir(<Dir>,<distance>) // Dir {1:+x 2:-x 3:+y 4-y}
  //go2Pos(go2x,go2y,0.25);
  //Driving
  dirCorr();           //correction for the rotational drift
  vLimit(180);         //max limit for the speed
  //Serial.println(Ang);
  go(Mag, Ang);

  //Serial.println(there);
  }
  there = 0;
  while (!there) {
    nick();
    location us = (location) {
   xFilt, yFilt
  };
  police = coordinatesToMap(us);
 
  go2Pos(-6.29, 3.92, 0.1); //go to the <margin> close of coordinates (x,y,margin) -.6,-.4
  
  //goDir(<Dir>,<distance>) // Dir {1:+x 2:-x 3:+y 4-y}
  //go2Pos(go2x,go2y,0.25);
  //Driving
  dirCorr();           //correction for the rotational drift
  vLimit(180);         //max limit for the speed
  //Serial.println(Ang);
  go(Mag, Ang);

  //Serial.println(there);
  }
  there = 0;
  while (!there) {
    nick();
    location us = (location) {
   xFilt, yFilt
  };
  police = coordinatesToMap(us);
 
  go2Pos(-6.29, 3.92, 0.1); //go to the <margin> close of coordinates (x,y,margin) -.6,-.4
  
  //goDir(<Dir>,<distance>) // Dir {1:+x 2:-x 3:+y 4-y}
  //go2Pos(go2x,go2y,0.25);
  //Driving
  dirCorr();           //correction for the rotational drift
  vLimit(180);         //max limit for the speed
  //Serial.println(Ang);
  go(Mag, Ang);

  //Serial.println(there);
  }
  there = 0;
  while (!there) {
    nick();
    location us = (location) {
   xFilt, yFilt
  };
  police = coordinatesToMap(us);
 
  go2Pos(3.75, 4.40, 0.1); //go to the <margin> close of coordinates (x,y,margin) -.6,-.4
  
  //goDir(<Dir>,<distance>) // Dir {1:+x 2:-x 3:+y 4-y}
  //go2Pos(go2x,go2y,0.25);
  //Driving
  dirCorr();           //correction for the rotational drift
  vLimit(180);         //max limit for the speed
  //Serial.println(Ang);
  go(Mag, Ang);

  //Serial.println(there);
  }
  while (!there) {
    nick();
    location us = (location) {
   xFilt, yFilt
  };
  police = coordinatesToMap(us);
 
  go2Pos(-0.90, 4.13, 0.1); //go to the <margin> close of coordinates (x,y,margin) -.6,-.4
  
  //goDir(<Dir>,<distance>) // Dir {1:+x 2:-x 3:+y 4-y}
  //go2Pos(go2x,go2y,0.25);
  //Driving
  dirCorr();           //correction for the rotational drift
  vLimit(180);         //max limit for the speed
  //Serial.println(Ang);
  go(Mag, Ang);

  //Serial.println(there);
  }
  there = 0;
}
  
 // there = false;
//  Serial.println(there);
  
//------------------------------------------//


