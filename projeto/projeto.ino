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
}
