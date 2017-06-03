#include <Coordinates.h>

//1st wheel
#define dir1 2
#define pwm1 3
//2nd wheel
#define dir2 4
#define pwm2 5
//3rd wheel
#define dir3 8
#define pwm3 9
//4th wheel
#define dir4 6
#define pwm4 7
float pi = 3.1415926536;

float r = 10;
float phi = 1.57;
Coordinates vector = Coordinates();

void setup() {
  // put your setup code here, to run once:
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(dir4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  r = 200;
  if (phi >= 2*pi){
    phi = 0;
  }
  phi = phi+0.01;
  go(r,phi);

  /*
  Serial.print(phi);
  Serial.print(" ");
  Serial.print(vector.getX());
  Serial.print(" ");
  Serial.println(vector.getY());
  */
  delay(20);
}

void go(float Amp, float theta){
  vector.fromPolar(Amp,theta); //r <! 255
  vX(vector.getX());
  vY(vector.getY());
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
  Serial.print(yVect);
  Serial.print(" ");
  if(yVect >= 0){
    Serial.print("10");
    Serial.print(" ");
    digitalWrite(dir2, 1);
    digitalWrite(dir4, 0);
  } else {
    Serial.print("-10");
    Serial.print(" ");
    digitalWrite(dir2, LOW);
    digitalWrite(dir4, HIGH);
  }
  int y = (int) abs(yVect);
  analogWrite(pwm2, y);
  analogWrite(pwm4, y);
}


