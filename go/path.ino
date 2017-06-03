#include "path.h"
// compute the distance between points
float heuristic(locationMap a, locationMap b) {
  return sqrt(pow(a.X - b.X, 2) + pow(a.Y - b.Y, 2));
}

// translate location to locationMap
locationMap coordinatesToMap(location loc){
  int resultX = (int) -((loc.X-4.76)/2.59);
  int resultY = (int) -((loc.Y-5.31)/2.61);
  return (locationMap) {resultX, resultY};
}

// translate locationMap to location
location mapToCoordinates(locationMap loc){
  float resultX = 4.76 - (2.59/2) - 2.59*loc.X;
  float resultY = 5.31 - (2.61/2) - 2.61*loc.Y ;
  return (location) {resultX, resultY};
}

//------ return an integer indicating the corner furthest away from Tony-------//
int destinationSelect(locationMap police, locationMap Tony) {
    Serial.print(" Destination selection Tony :");

  //float TonyToPolice = heuristic(checkX, checkY, TonyX, TonyY);
  float TonytoCorner[4] = {FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX};
  TonytoCorner[0] = heuristic(Tony, corners[0]);
  TonytoCorner[1] = heuristic(Tony, corners[1]);
  TonytoCorner[2] = heuristic(Tony, corners[2]);
  TonytoCorner[3] = heuristic(Tony, corners[3]);
  float maximum = FLT_MIN;
  int result = -1;
  for (int i = 0; i < 4; i++) {
    if (TonytoCorner[i] > maximum) {
      maximum = TonytoCorner[i];
      result = i;
    }
  }
  return result;
}

//------------A star search meat and potatoes-----------//
void a_star_search(float (&costsofar)[5][5], locationMap police, locationMap dest, locationMap Tony) {
  // record number of steps taken
  // Serial.println("A start search Tony :");

  steps++;
  // current cost
  float minCost = heuristic(police, dest);

  //Serial.print("minCost= ");
  //Serial.println(minCost);

  locationMap next = police;
  int i = police.X;
  int j = police.Y;

  // pre-compute the Y component of the distances
  float compYdest = pow(police.Y - dest.Y, 2);
  float compYTony = pow(police.Y - Tony.Y, 2);
  float compXTony = FLT_MAX;
  float compXdest = FLT_MAX;

  // check the X-1 case
  if (police.X > 0) {
    i = police.X - 1;
    // compute the X component of the distances
    compXdest = pow(i - dest.X, 2);
    compXTony = pow(i - Tony.X, 2);
    // update the cost of the X-1 case
    costsofar[i][j] =  sqrt(compXdest + compYdest) - sqrt(compXTony + compYTony);
  }

  // compare the cost of the X-1 case, update minimum
  if (costsofar[i][j] <= minCost) {
    minCost = costsofar[i][j];
    next.X = i;
    next.Y = j;
  }

  // check the X+1 case
  if (police.X < 4) {
    i = police.X + 1;
    // compute the X component of the distance
    compXdest = pow(i - dest.X, 2);
    compXTony = pow(i - Tony.X, 2);
    // update the cost of the X+1 case
    costsofar[i][j] =  sqrt(compXdest + compYdest) - sqrt(compXTony + compYTony);
  }

  // compare the cost of the X+1 case, update minimum
  if (costsofar[i][j] <= minCost) {
    minCost = costsofar[i][j];
    next.X = i;
    next.Y = j;
  }

  // done with checking X
  i = police.X;

  // pre-compute the X component of the distances
  compXdest = pow(police.X - dest.X, 2);
  compXTony = pow(police.X - Tony.X, 2);

  // check the Y-1 case
  if (police.Y > 0) {
    j = police.Y - 1;
    // compute the Y component of the distances
    compYdest = pow(j - dest.Y, 2);
    compYTony = pow(j - Tony.Y, 2);
    // update the cost of the Y-1 case
    costsofar[i][j] =  sqrt(compXdest + compYdest) - sqrt(compXTony + compYTony);
  }

  // compare the cost of the Y-1 case, update minimum
  if (costsofar[i][j] <= minCost) {
    minCost = costsofar[i][j];
    next.X = i;
    next.Y = j;
  }

  // check the Y+1 case
  if (police.Y < 4) {
    j = police.Y + 1;
    // compute the Y component of the distance
    compYdest = pow(j - dest.Y, 2);
    compYTony = pow(j - Tony.Y, 2);
    // update the cost of the Y+1 case
    costsofar[i][j] =  sqrt(compXdest + compYdest) - sqrt(compXTony + compYTony);
  }

  // compare the cost of the Y+1 case, update minimum
  if (costsofar[i][j] <= minCost) {
    minCost = costsofar[i][j];
    next.X = i;
    next.Y = j;
  }

  // update the camefrom matrix
  camefrom[police.X][police.Y] = 1;
  camefrom[next.X][next.Y] = 1;

  // update the next coordinates
  police.X = next.X;
  police.Y = next.Y;

  queue.push(next);
  
  if ((police.X == dest.X) & (police.Y == dest.Y))
    solved = 1;
  else if(steps<2)
    a_star_search(costsofar, next, dest, Tony); //decide which is the next one to check
  //}
}


//
//float mapToCoordinates(int mapX, int mapY){
//  float X
//}


//----------------------------Setup-------------------------------//
void PathSetup() {
//  Tony = (locationMap) {xOpponent,yOpponent};
//  police = (locationMap) {xFilt, yFilt}; 
 // dest = corners[destinationSelect(police, Tony)];
// 
//  //camefrom[police.X][police.Y] = 1;
//  a_star_search(costsofar, police, dest, Tony); // update
//  //IF A-START SOLVED//
//  if (solved == 1) {
//    //Serial.println("Path Solved!");
//    camefrom[Tony.X][Tony.Y] = 666;
//    camefrom[startingPointX][startingPointY] = 11;
//    camefrom[dest.X][dest.Y] = 22;
//    for (int i = 0; i < 5; i++) {  // PRINT MAP
//      for (int j = 0; j < 5; j++) {
//        //Serial.print(camefrom[i][j]);
//        //Serial.print(" ");
//      }
//      //Serial.println("");
//    }
//  }
}

