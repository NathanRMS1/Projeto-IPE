#import <Servo.h>
#include <Servo.h>
#include <EEPROM.h>//used to store recorded values
Servo motor1;
Servo motor2;
Servo motor3;
float resolution = 1002;//MUST be less than 1024
float recordTime = 70;//MUST be less than 1024
bool recording = false;
int val[3][10];
int j = 1;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, INPUT);//m1
  pinMode(A1, INPUT);//m2
  pinMode(A5, INPUT);//m3
  pinMode(A3, INPUT);//botao
  motor1.attach(3);
  motor2.attach(5);
  motor3.attach(6);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A3));
  if (recording == true) {
    j = 1;
    for (int i = 1; i <= resolution/3; i++) {
      digitalWrite(LED_BUILTIN, HIGH);

      int b = 0, c = 0, d = 0;
      
      for(int loo = 0; loo < 10; loo++){val[0][loo] = analogRead(A0);}
      for(int a = 0; a<10; a++){b+=val[0][a];}
      motor1.write(map(b, 0, 10230, 0, 180));
      EEPROM.write(3*i, map(b, 0, 10230, 0, 180));
      
      for(int loo = 0; loo < 10; loo++){val[1][loo] = analogRead(A1);}
      for(int a = 0; a<10; a++){c+=val[1][a];}
      motor2.write(map(c, 0, 10230, 0, 180));
      EEPROM.write(3*i+1, map(c, 0, 10230, 0, 180));
      
      for(int loo = 0; loo < 10; loo++){val[1][loo] = analogRead(A2);}
      for(int a = 0; a<10; a++){d+=val[2][a];}
      motor3.write(map(d, 0, 10230, 0, 180));
      EEPROM.write(3*i+2, map(d, 0, 10230, 0, 180));
      
      delay(recordTime);
      j = 3*i;
      if (analogRead(A3) > 512) {
        recording = false;
        break;
      }
    }
  }else{
    for (int i = 1; i <= j/3; i++){
      digitalWrite(LED_BUILTIN, LOW);
      if (analogRead(A3) < 512) {
        recording = true;
        delay(1000);
        break;
      }
      motor1.write(EEPROM.read(3*i));
      motor2.write(EEPROM.read(3*i+1));
      motor3.write(EEPROM.read(3*i+2));
      delay(recordTime);
    }
    delay(1000);
  }
}
