#import <Servo.h>
Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(2, INPUT);
  motor1.attach(3);
  pinMode(4, OUTPUT);
  motor2.attach(5);
  motor3.attach(6);
}

void loop() {
  // put your main code here, to run repeatedly:
  motor1.write(analogRead(A0)/4);
  motor2.write(analogRead(A1)/4);
  motor3.write(analogRead(A2)/4);
  if(digitalRead(2)){
    motor4.write(255);
  }else{
    motor4.write(0);
  }
  delay(50);
}
/*
https://create.arduino.cc/projecthub/millerman4487/simple-record-and-playback-0bffa1
#include <Servo.h>
#include <EEPROM.h>//used to store recorded values
Servo myServo;
float resolution = 1000;//MUST be less than EEPROM.length()
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
