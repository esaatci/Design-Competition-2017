const int pwm_1=1;
const int pwm_2=2;
const int pwm_3=3;
const int pwm_4=4;
const int pwm_5=5;
const int pwm_6=6;
const int pwm_7=7;
const int pwm_8=8;
const int pwm_9=9;

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
      analogWrite(pwm_2,n);
      analogWrite(pwm_3,0);
      if (millis() > time){
        analogWrite(pwm_2, 0);
      }
      break;
    case 2:
      analogWrite(pwm_4,n);
      analogWrite(pwm_5,0);
      if (millis() > time){
        analogWrite(pwm_4, 0);
      }
      break;
    case 3:
      analogWrite(pwm_6,n);
      analogWrite(pwm_7,0);
      if (millis() > time){
        analogWrite(pwm_6, 0);
      }
      break;
    case 4:
      analogWrite(pwm_8,n);
      analogWrite(pwm_9,0);
      if (millis() > time){
        analogWrite(pwm_8, 0);
      }
      break;
  }
}

void wheelReverse(int wheel,unsigned long time, int speed){
  int n = 17.5*speed+62.5;
  switch (wheel){
    case 1:
      analogWrite(pwm_2,0);
      analogWrite(pwm_3,n);
        if (millis() > time){
          analogWrite(pwm_3, 0);
         }
    break;
    case 2:
      analogWrite(pwm_4,0);
      analogWrite(pwm_5,n);
        if (millis() > time){
          analogWrite(pwm_5, 0);
         }
    break;
    case 3:
      analogWrite(pwm_6,0);
      analogWrite(pwm_7,n);
        if (millis() > time){
          analogWrite(pwm_7, 0);
         }
    break;
    case 4:
      analogWrite(pwm_8,0);
      analogWrite(pwm_9,n);
      if (millis() > time){
          analogWrite(pwm_9, 0);
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



