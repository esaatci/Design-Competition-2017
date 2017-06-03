#include <math.h>
#include <float.h>
unsigned long time1;
unsigned long time2;
const int gridSize = 5;
int startingPointX = 3;
int startingPointY = 3;
int mapgrid [gridSize][gridSize] = {0};
int camefrom [gridSize][gridSize] = {0};
float costsofar [gridSize][gridSize] = {0};
int steps = 0;
int solved = 0;
float cornersX[4] = {0, 4, 0, 4};
float cornersY[4] = {0, 0, 4, 4};


float heuristic(int x1, int y1, int x2, int y2) {
  return sqrt(pow((x1 - x2, 2) + pow(y1 - y2, 2));
}

//------ return an integer indicating the corner furthest away from the enemy-------//
int destinationSelect(float checkX, float checkY, float enemyX, float enemyY) {
  //float TonyToPolice = heuristic(checkX, checkY, enemyX, enemyY);
  float TonytoCorner[4] = {FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX};
  TonytoCorner[0] = heuristic(enemyX, enemyY, cornersX[0], cornersY[0]);
  TonytoCorner[1] = heuristic(enemyX, enemyY, cornersX[1], cornersY[1]);
  TonytoCorner[2] = heuristic(enemyX, enemyY, cornersX[2], cornersY[2]);
  TonytoCorner[3] = heuristic(enemyX, enemyY, cornersX[3], cornersY[3]);
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
void a_star_search(float (&costsofar)[5][5], int checkX, int checkY, int destX, int destY, int enemyX, int enemyY) {
  steps++;
  float minCost = heuristic(checkX, checkY, destX, destY);
  Serial.print("minCost= ");
  Serial.println(minCost);
  int nextLocX = checkX;
  int nextLocY = checkY;
  int i = checkX;
  int j = checkY;
  //while (((checkX != destX) | (checkY != destY))) {
  //    Serial.print("CheckX= ");
  //    Serial.println(checkX);
  //    Serial.print("Check Y= ");
  //    Serial.println(checkY);

  //    float compY = pow(enemyY-checkY, 2);
  //    float compX = pow(enemyX-checkX, 2);
  //    float options[4];
  //    options[0] =
  float compY = pow(checkY-destY,2);
  float compX = pow(checkX-destX,2);
  if (checkX > 0)
    i = checkX - 1;
  costsofar[i][j] =  heuristic(i, j, destX, destY) - heuristic(i, j, enemyX, enemyY);
  if (costsofar[i][j] <= minCost) {
    minCost = costsofar[i][j];
    nextLocX = i;
    nextLocY = j;
  }
  if (checkX < 4) 
    i = checkX + 1;
  costsofar[i][j] =  heuristic(i, j, destX, destY) - heuristic(i, j, enemyX, enemyY);
  if (costsofar[i][j] <= minCost) {
    minCost = costsofar[i][j];
    nextLocX = i;
    nextLocY = j;
  }
  for (int j = checkY - 1; j <= checkY + 1; j++) { ///if not the diagonols
    i = checkX;
    if (j <= 0)
      j = 0;
    if (j >= 4)
      j = 4;
    costsofar[i][j] = heuristic(i, j, destX, destY) - heuristic(i, j, enemyX, enemyY);
    if (costsofar[i][j] <= minCost) {
      minCost = costsofar[i][j];
      nextLocX = i;
      nextLocY = j;
    }
  }
  camefrom[checkX][checkY] = 1;
  //    Serial.println("Cost:");
  //    for (int i = 0; i < 5; i++) {  // PRINT COST
  //      for (int j = 0; j < 5; j++) {
  //        Serial.print(costsofar[i][j]);
  //        Serial.print(" ");
  //      }
  //      Serial.println("");
  //    }
  //    Serial.println("");
  //    Serial.println("Came from:");
  //    for (int i = 0; i < 5; i++) {  // PRINT CAME FROM
  //      for (int j = 0; j < 5; j++) {
  //        Serial.print(camefrom[i][j]);
  //        Serial.print(" ");
  //      }
  //      Serial.println("");
  //    }
  camefrom[nextLocX][nextLocY] = 1;
  checkX = nextLocX;
  checkY = nextLocY;
  if ((checkX == destX) & (checkY == destY))
    solved = 1;
  else
    a_star_search(costsofar, nextLocX, nextLocY, destX, destY, enemyX, enemyY); //decide which is the next one to check
  //}
}


//----------------------------Setup-------------------------------//
void setup() {
  Serial.begin(9600);
  int enemyX = 0, enemyY = 1;
  int destIndex = destinationSelect(startingPointX, startingPointY, enemyX, enemyY);
  Serial.println(destIndex);
  int checkX = startingPointX, checkY = startingPointY;
  int destX = cornersX[destIndex]; int destY = cornersY[destIndex];
  camefrom[startingPointX][startingPointY] = 1;
  a_star_search(costsofar, startingPointX, startingPointY, destX, destY, enemyX, enemyY);
  //IF A-START SOLVED//
  if (solved == 1) {
    Serial.println("Path Solved!");
    camefrom[enemyX][enemyY] = 666;
    camefrom[startingPointX][startingPointY] = 11;
    camefrom[destX][destY] = 22;
    for (int i = 0; i < 5; i++) {  // PRINT MAP
      for (int j = 0; j < 5; j++) {
        Serial.print(camefrom[i][j]);
        Serial.print(" ");
      }
      Serial.println("");
    }
  }
}

int nextPos(float currentX, float currentY){
  cameFrom[
}

//----------------loop----------------------//
void loop() {
  go2Pos(nextPosX, nextPosY);
  go(Mag, Ang);
  nick();
}

