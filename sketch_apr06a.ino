const int pwm_1=2;
const int pwm_2=3;
int val=0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  forward(3000, 5);
}

void wheelForward(int wheel, unsigned long time, int speed){
  int n = 17.5*speed+62.5;
  switch (wheel){
    case 1:
      analogWrite(pwm_1,n);
      analogWrite(pwm_2,0);
      if (millis() > time){
        analogWrite(pwm_1, 0);
      }
      break;
    case 2:
      analogWrite(pwm_1,n);
      analogWrite(pwm_2,0);
      if (millis() > time){
        analogWrite(pwm_1, 0);
      }
      break;
    case 3:
      analogWrite(pwm_1,n);
      analogWrite(pwm_2,0);
      if (millis() > time){
        analogWrite(pwm_1, 0);
      }
      break;
    case 4:
      analogWrite(pwm_1,n);
      analogWrite(pwm_2,0);
      if (millis() > time){
        analogWrite(pwm_1, 0);
      }
      break;
  }
}

void wheelReverse(int wheel,unsigned long time, int speed){
  int n = 17.5*speed+62.5;
  switch (wheel){
    case 1:
      analogWrite(pwm_1,0);
      analogWrite(pwm_2,n);
        if (millis() > time){
          analogWrite(pwm_2, 0);
         }
    break;
    case 2:
      analogWrite(pwm_1,0);
      analogWrite(pwm_2,n);
        if (millis() > time){
          analogWrite(pwm_2, 0);
         }
    break;
    case 3:
      analogWrite(pwm_1,0);
      analogWrite(pwm_2,n);
        if (millis() > time){
          analogWrite(pwm_2, 0);
         }
    break;
    case 4:
      analogWrite(pwm_1,0);
      analogWrite(pwm_2,n);
      if (millis() > time){
          analogWrite(pwm_2, 0);
      }
      break;
  }
}

void forward(unsigned long time, int speed){
  wheelForward(1, time, speed);
  wheelForward(2, time, speed);
  wheelForward(3, time, speed);
  wheelForward(4, time, speed);
}

void reverse(unsigned long time, int speed){
  wheelReverse(1, time, speed);
  wheelReverse(2, time, speed);
  wheelReverse(3, time, speed);
  wheelReverse(4, time, speed);
}



