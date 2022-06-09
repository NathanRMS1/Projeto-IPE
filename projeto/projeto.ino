#include <Servo.h>
#include <EEPROM.h>//used to store recorded values
Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
float resolution = 1000;//MUST be less than 1024
float recordTime = 50;//MUST be less than 1024
bool recording = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(2, INPUT);
  motor1.attach(3);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  motor2.attach(5);
  motor3.attach(6);
  Serial.begin(9600);
  digitalWrite(4, HIGH);
  digitalWrite(7, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  /*if (recording == true) {
    for (int i = 1; i <= resolution; i++) {
      int val = map(analogRead(A0), 0, 1023, 0, 180);
      EEPROM.write(i, val);
      //Serial.println(EEPROM.read(i));
      motor1.write(val);
      delay(recordTime);
    }
    digitalWrite(13, LOW); //turn off status led
    delay(1000);//give time for person
    recording = false;
  }*/
  Serial.println(analogRead(A0));
  motor1.write(map(analogRead(A0), 0, 1023, 0, 180));
  motor2.write(map(analogRead(A1), 0, 1023, 0, 180));
  motor3.write(map(analogRead(A2), 0, 1023, 0, 180));
  delay(50);
}
/*
https://create.arduino.cc/projecthub/millerman4487/simple-record-and-playback-0bffa1
#include <Servo.h>
Servo myServo;

float recordTime = 5; //delay time
bool recording = false;
void setup() {
 pinMode(13, OUTPUT); //status led
 pinMode(2, OUTPUT);
 myServo.attach(3);
 Serial.begin(9600);
 digitalWrite(2, HIGH);
 //Serial.println(EEPROM.length());
}
void loop() {
 if (recording == true) {//record
   for (int i = 1; i <= resolution; i++) {
     digitalWrite(13, HIGH); //light status led
     int val = map(analogRead(A0), 0, 1023, 0, 180);
     EEPROM.write(i, val);
     //Serial.println(EEPROM.read(i));
     myServo.write(val);
     delay(recordTime);
   }
   digitalWrite(13, LOW); //turn off status led
   delay(1000);//give time for person
   recording = false;
 }
 else {
   for (int i = 1; i <= resolution; i++) {//playback
     if (digitalRead(2) == 0) {//stop playback and record new values
       recording = true;
       break;
     }
     int readval = EEPROM.read(i);
     myServo.write(readval);
     //Serial.println(readval);
     delay(recordTime);
   }
   digitalWrite(13, HIGH); //show a new repeat
   delay(100);
   digitalWrite(13, LOW);
 }
}
*/
