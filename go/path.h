#ifndef __PATH_H__
#define __PATH_H__
  //----------include
  #include <math.h>
  #include <float.h>
  #include <QueueList.h>
  #include "Functions.h"
  
  //----------global vars
  unsigned long time1;
  unsigned long time2;
  const int gridSize = 5;

  int mapgrid [gridSize][gridSize] = {0};
  int camefrom [gridSize][gridSize] = {0};
  float costsofar [gridSize][gridSize] = {0};
  int steps = 0;
  int solved = 0;
  
  //-----------structs
  // for grid locaiton
  struct locationMap {
    int X;
    int Y;
  };
  
  // for physical location
  struct location {
    float X;
    float Y;
  };
  
  QueueList <locationMap> queue;
  
  // map locations for the corners
  struct locationMap corners[4] = {(locationMap) {0, 0}, (locationMap) {4, 0}, (locationMap) {0, 4}, (locationMap) {4, 4}};
  location viveCoordinates[5][5] = {
     {(location) {3.9, 4.4},
  (location) {1.59, 4.1}, (location) {-0.9, 4.13}, (location) {-3.49, 3.98}, (location) {-6.29, 3.92}},
  { (location) {3.98, 2.05}, (location) {1.69, 1.93}, (location) {-0.8, 1.85},(location) {-3.6, 1.69}, (location) {-6.4, 1.63}},
  {(location) {4.1, -0.33},(location) {1.80, -0.6},(location) {-0.7, -0.76},(location) {-3.4, -0.79}, (location) {-6.05, -0.9}},
  {(location) {4.3, -2.98},(location) {2.05, -3.01},(location) {-0.63, -3.41},(location) {-3.35, -3.49},(location) {-6.20, -3.7}},
  {(location) {4.45, -5.69},
   (location) {2.13, -5.88},
  (location) {-0.54, -6.1},
  (location) {-3.45, -6.25},
  (location) {-6.31, -6.58}}
  };



    
//  viveCoordinates[0][0] = (location) {3.9, 4.4};
//  viveCoordinates[1][0] = (location) {1.59, 4.1};
//  viveCoordinates[2][0] = (location) {-0.9, 4.13};
//  viveCoordinates[3][0] = (location) {-3.49, 3.98};
//  viveCoordinates[4][0] = (location) {-6.29, 3.92};
//  viveCoordinates[0][1] = (location) {3.98, 2.05};
//  viveCoordinates[1][1] = (location) {1.69, 1.93};
//  viveCoordinates[2][1] = (location) {-0.8, 1.85};
//  viveCoordinates[3][1] = (location) {-3.6, 1.69};
//  viveCoordinates[4][1] = (location) {-6.4, 1.63};
//  viveCoordinates[0][2] = (location) {4.1, -0.33};
//  viveCoordinates[1][2] = (location) {1.80, -0.6};
//  viveCoordinates[2][2] = (location) {-0.7, -0.76};
//  viveCoordinates[3][2] = (location) {-3.4, -0.79};
//  viveCoordinates[4][2] = (location) {-6.05, -0.9};
//  viveCoordinates[0][3] = (location) {4.3, -2.98};
//  viveCoordinates[1][3] = (location) {2.05, -3.01};
//  viveCoordinates[2][3] = (location) {-0.63, -3.41};
//  viveCoordinates[3][3] = (location) {-3.35, -3.49};
//  viveCoordinates[4][3] = (location) {-6.20, -3.7};
//  viveCoordinates[0][4] = (location) {4.45, -5.69};
//  viveCoordinates[1][4] = (location) {2.13, -5.88};
//  viveCoordinates[2][4] = (location) {-0.54, -6.1};
//  viveCoordinates[3][4] = (location) {-3.45, -6.25};
//  viveCoordinates[4][4] = (location) {-6.31, -6.58};
  
  
  //------------prototypes
  float heuristic(locationMap a, locationMap b);
  location mapToCoordinates(locationMap loc);
  locationMap coordinatesToMap(location loc);
  int destinationSelect(locationMap police, locationMap Tony);
  void a_star_search(float (&costsofar)[5][5], locationMap police, locationMap dest, locationMap Tony);
  void PathSetup();
  locationMap Tony;// = (locationMap) {xOpponent,yOpponent};
  locationMap police;// = (locationMap) {xFilt, yFilt};
  locationMap dest;// = corners[destinationSelect(police, Tony)];
  
#endif
