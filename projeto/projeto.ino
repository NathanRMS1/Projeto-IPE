#import <Servo.h>
#include <Servo.h>
#include <EEPROM.h>//used to store recorded values
Servo motor1;
Servo motor2;
Servo motor3;
float resolution = 1002;//MUST be less than 1024
float recordTime = 100;//MUST be less than 1024
bool recording = false;
int j = 3;
int val[3][16] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
void setup() {
  for(int i = 0; i < 1024; i++){EEPROM.write(i, 0);}
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, INPUT);//m1
  pinMode(A1, INPUT);//m2
  pinMode(A2, INPUT);//m3
  pinMode(11, INPUT);//botao
  pinMode(12, INPUT);//botao
  pinMode(13, INPUT);//botao
  motor1.attach(3);
  motor2.attach(5);
  motor3.attach(6);
  Serial.begin(9600);
}

void loop() {
  if (recording == true) {
    j = 1;
    for (int i = 1; i <= resolution/3; i++) {
      for(int q = 1; q < 16; q++){
        val[0][0] -= val[0][q];
        val[0][q] = analogRead(A0);
        val[0][0] += val[0][q];
      }
      motor1.write(map(val[0][0], 0, 15345, 0, 180));
      EEPROM.write(3*i, map(val[0][0], 0, 15345, 0, 180));
      for(int q = 1; q < 16; q++){
        val[1][0] -= val[1][q];
        val[1][q] = analogRead(A1);
        val[1][0] += val[1][q];
      }
      motor2.write(map(val[1][0], 0, 15345, 0, 180));
      EEPROM.write(3*i+1, map(val[1][0], 0, 15345, 0, 180));
      /*for(int q = 1; q < 16; q++){
        val[2][0] -= val[2][q];
        val[2][q] = analogRead(A2);
        val[2][0] += val[2][q];
      }*/
      /**/if(digitalRead(11)){val[2][0] = 15345;}else{val[2][0] = 0;}
      motor3.write(map(val[2][0], 0, 15345, 0, 180));
      EEPROM.write(3*i+2, map(val[2][0], 0, 15345, 0, 180));
      Serial.print("Saída para motor 1: ");
      Serial.println(EEPROM.read(3*i));
      Serial.print("Saída para motor 2: ");
      Serial.println(EEPROM.read(3*i+1));
      Serial.print("Saída para motor 3: ");
      Serial.println(EEPROM.read(3*i+2));
      delay(recordTime);
      j = 3*i;
      if (digitalRead(13)) {
        recording = false;
        break;
      }
      if (digitalRead(12)) {
        recording = false;
        for (int i = 0 ; i < EEPROM.length() ; i++) {EEPROM.write(i, 0);}
        break;
      }
    }
    recording = false;
    delay(500);
  }else{
    for (int i = 1; i <= j/3; i++){
      digitalWrite(LED_BUILTIN, LOW);
      if (digitalRead(13)) {
        digitalWrite(LED_BUILTIN, HIGH);
        recording = true;
        delay(500);
        break;
      }
      if (digitalRead(12)) {
        recording = false;
        for (int i = 0 ; i < EEPROM.length() ; i++) {EEPROM.write(i, 0);}
        break;
      }
      motor1.write(EEPROM.read(3*i));
      motor2.write(EEPROM.read(3*i+1));
      motor3.write(EEPROM.read(3*i+2));
      delay(recordTime);
    }
  }
}
