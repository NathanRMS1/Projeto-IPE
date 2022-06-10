#import <Servo.h>
#include <Servo.h>
#include <EEPROM.h>//used to store recorded values
Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
float resolution = 1002;//MUST be less than 1024
float recordTime = 50;//MUST be less than 1024
bool recording = false;
int val1 = 0, val2 = 0, val3 = 0, vali1, vali2, vali3;
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
      val1 = map(analogRead(A0), 0, 1023, 0, 180);
      val2 = map(analogRead(A1), 0, 1023, 0, 180);
      //if(analogRead(A5)<512){val3 = 180;}else{val3 = 0;}
      val3 = map(analogRead(A5), 0, 1023, 0, 180);
      EEPROM.write(3*i, val1);
      EEPROM.write(3*i+1, val2);
      EEPROM.write(3*i+2, val3);
      motor1.write(val1);
      motor2.write(val2);
      motor3.write(val3);
      delay(recordTime);
      j = 3*i;
      if (analogRead(A3) > 512) {
        recording = false;
        break;
      }
    }
    recording = false;
    delay(1000);
  }else if(j < 200){
      digitalWrite(LED_BUILTIN, LOW);
      //Serial.println(analogRead(A0));
      //Serial.println(analogRead(A1));
      vali1 = map(analogRead(A0), 0, 1023, 0, 180);
      val1 = (val1+3*vali1)/4;
      vali2 = map(analogRead(A1), 0, 1023, 0, 180);
      val2 = (val2+3*vali2)/4;
      vali3 = map(analogRead(A5), 0, 1023, 0, 180);
      val3 = (val3+3*vali3)/4;
      //if(analogRead(A5)<512){val3 = 180;}else{val3 = 0;}
      motor1.write(val1);
      motor2.write(val2);
      motor3.write(val3);
      delay(recordTime);
      if (analogRead(A3) < 512) {
        recording = true;
        delay(1000);
      }
  }else{
    /*for (int i = 1; i <= j/3; i++){
      digitalWrite(LED_BUILTIN, LOW);
      if (analogRead(A3) < 512) {
        recording = true;
        delay(1000);
        break;
      }
      motor1.write(EEPROM.read(j-3*i));
      motor2.write(EEPROM.read(j-3*i-1));
      motor3.write(EEPROM.read(j-3*i-2));
      delay(recordTime);
    }*/
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
