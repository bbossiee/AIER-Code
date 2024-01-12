#include <QTRSensors.h>
#include <SparkFun_TB6612.h>
#include <Wire.h>
QTRSensors qtr;
const uint8_t SensorCount = 2;
uint16_t sensorValues[SensorCount];
uint16_t line_detect1, line_detect2;  // Declare line_detect1 and line_detect2 variables
#define TIMEOUT 2500
const int trig = 12;      //ประกาศขา trig
const int echo = 13;      //ประกาศขา echo
long duration, distance;  //ประกาศตัวแปรเก็บค่าระยะ
#define AIN1 7
#define BIN1 9
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 10
#define STBY 6

int state = 0;
bool state_break = false;
// float
const int offsetA = 1;
const int offsetB = 1;
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
void setup() {
  Wire.begin();  // Initialize I2C communication
  Serial.begin(9600);
  // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){ 2, 3 }, SensorCount);
  qtr.setEmitterPin(2);
  pinMode(echo, INPUT);   //สั่งให้ขา echo ใช้งานเป็น input
  pinMode(trig, OUTPUT);  //สั่งให้ขา trig ใช้งานเป็น output
  pinMode(STBY, HIGH);
  delay(3500);
  //เขียนที่นี้
  // dern(100000);
  // trackline(5000);
}

void loop() {

  // read raw sensor values
  qtr.read(sensorValues);
  line_detect1 = sensorValues[0];  // Correct array name
  line_detect2 = sensorValues[1];  // Correct array name
  Serial.print(line_detect1);
  Serial.print("   ");
  Serial.println(line_detect2);
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);           //ใช้งานขา trig
  duration = pulseIn(echo, HIGH);    //อ่านค่าของ echo
  distance = (duration / 2) / 29.1;  //คำนวณเป็น centimeters
  Serial.print(distance);
  Serial.print(" cm\n");
  state_maze();
  //  trackline//
  //     if (sensorValues[0] > 1200 && sensorValues[1] > 1200) {
  //     brake(motor1, motor2);
  //   } else if (sensorValues[0] < 1200 && sensorValues[1] < 1200) {
  //     motor1.drive(205);
  //     motor2.drive(205);
  //   } else if (sensorValues[0] < 1200 && sensorValues[1] > 1200) {
  //     motor1.drive(-235);
  //     motor2.drive(235);
  //   } else if (sensorValues[0] > 1200 && sensorValues[1] < 1200) {
  //     motor1.drive(235);
  //     motor2.drive(-235);
  // }
}

void getLine() {
  qtr.read(sensorValues);
  line_detect1 = sensorValues[0];  // Correct array name
  line_detect2 = sensorValues[1];  // Correct array name
  Serial.print(line_detect1);
  Serial.print("   ");
  Serial.println(line_detect2);
}

void getDistance() {


  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);           //ใช้งานขา trig
  duration = pulseIn(echo, HIGH);    //อ่านค่าของ echo
  distance = (duration / 2) / 29.1;  //คำนวณเป็น centimeters
  Serial.print(distance);
  Serial.print(" cm\n");
}

void state_maze() {
  getDistance();
  getLine();
  switch (state) {
    case 0:
      motor1.drive(180);
      motor2.drive(160);
      if (distance < 7 ) {
        brake(motor1, motor2);
        state = 1;
      }
      break;
      delay(800);
    case 1:
      motor1.drive(-200);
      motor2.drive(200);
      delay(315);
      brake(motor1, motor2);
      state = 2;
      break;
      delay(500);
    case 2:
      motor1.drive(185);
      motor2.drive(165);
      if (distance <= 7.6) {
        brake(motor1, motor2);
        state = 3;
      }
      break;
      delay(500);
    case 3:
      motor1.drive(-215);
      motor2.drive(215);
      delay(305);
      brake(motor1, motor2);
      state = 4;
      break;
      delay(500);
    case 4:
      motor1.drive(210);
      motor2.drive(195);
      if (distance < 7.98) {
        brake(motor1, motor2);
        delay(2000);
        state = 5;
      }
      break;
      delay(500);
    case 5:
      motor1.drive(215);
      motor2.drive(-215);
      delay(305);
      brake(motor1, motor2);
      state = 6;
      break;
      delay(1000);
    // case 6:
    //   motor1.drive(200);
    //   motor2.drive(180);
    //   if (distance < 7) {
    //     brake(motor1, motor2);
    //     state = 7;
    //   }
    //   break;
    //   delay(800);
    // case 7:
    //   motor1.drive(212);
    //   motor2.drive(-210);
    //   delay(365);
    //   brake(motor1, motor2);
    //   state = 8;
    //   break;
    // case 8:
    //   motor1.drive(200);
    //   motor2.drive(170);
    //   delay(1500);
    //   brake(motor1, motor2);
    //   state = 9;
    //   break;
    //   delay(500);
      // case 6:
      //   motor1.drive(-180);
      //   motor2.drive(-190);
      //   delay(2000);
      //   brake(motor1, motor2);
      //   state = 7;
      //   break;
      //   delay(1000);
      // case 6:
      //   motor1.drive(200);
      //   motor2.drive(170);
      //   delay(500);
      //   brake(motor1, motor2);
      //   state = 7;
      //   break;
      //   delay(500);
      // case 8:
      //   if (sensorValues[0] > 1200 && sensorValues[1] > 1200) {
      //     brake(motor1, motor2);
      //     state = 9;
      //   } else if (sensorValues[0] < 1200 && sensorValues[1] < 1200) {
      //     motor1.drive(240);
      //     motor2.drive(240);
      //   } else if (sensorValues[0] < 1200 && sensorValues[1] > 1200) {
      //     motor1.drive(-235);
      //     motor2.drive(235);
      //   } else if (sensorValues[0] > 1200 && sensorValues[1] < 1200) {
      //     motor1.drive(235);
      //     motor2.drive(-235);
      //   }
      //   break;
  }
}

// void left(int d) {
//   motor1.drive(-255);
//   motor2.drive(255);
//   delay(d);
//   brake(motor1, motor2);
// }
// void right(int d) {
// motor1.drive(255);
// motor2.drive(-255);
// delay(d);
//   brake(motor1, motor2);
// }
void dern(int d) {
  // motor1.drive(125);
  // motor2.drive(110);
  motor1.drive(35);
  motor2.drive(35);
  delay(d);
  brake(motor1, motor2);
}
// void toi(int d) {
//   motor1.drive(-255);
//   motor2.drive(-255);
//   delay(d);
//   brake(motor1, motor2);
//   delay(500);
// }