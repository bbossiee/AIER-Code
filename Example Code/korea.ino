#include <QTRSensors.h>
QTRSensors qtr;

const uint8_t SensorCount = 2;
uint16_t sensorValues[SensorCount];
uint16_t line_detect1, line_detect2;  // Declare line_detect1 and line_detect2 variables

#define TIMEOUT 2500
const int trig = 12;      //ประกาศขา trig
const int echo = 13;      //ประกาศขา echo
long duration, distance;  //ประกาศตัวแปรเก็บค่าระยะ
////motor ซ้าย
#define AIN1 4
#define BIN1 8
#define STBY1 6
const int pwm1 = 3;
const int pwm2 = 2;
//// motor ขวา
#define AIN2 5
#define BIN2 9
const int pwm3 = 8;
const int pwm4 = 7;



void setup() {
  // Wire.begin();  // Initialize I2C communication
  Serial.begin(9600);
  // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){ 2, 3 }, SensorCount);
  qtr.setEmitterPin(2);

  Serial.begin(9600);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY1, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(pwm4, OUTPUT);
  pinMode(echo, INPUT);   //สั่งให้ขา echo ใช้งานเป็น input
  pinMode(trig, OUTPUT);  //สั่งให้ขา trig ใช้งานเป็น output


  //เขียนที่นี้
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
  digitalWrite(trig, LOW);  //ใช้งานขา trig

  duration = pulseIn(echo, HIGH);    //อ่านค่าของ echo
  distance = (duration / 2) / 29.1;  //คำนวณเป็น centimeters
  Serial.print(distance);
  Serial.print(" cm\n");

  delay(100);
}
void forward(int period = 0) {
  int time = millis();
  while (millis() - time <= period) {
    long duration, cm;
    analogWrite(pwm1, 100);
    analogWrite(pwm2, 0);
    analogWrite(pwm3, 100);
    analogWrite(pwm4, 0);
  }
  //////////////////////
  if (distance <= 5) {
    analogWrite(pwm1, 0);
    analogWrite(pwm2, 0);
    analogWrite(pwm3, 0);
    analogWrite(pwm4, 0);
  }
}
void left(int period = 0) {
  int time = millis();
  while (millis() - time <= period) {
    analogWrite(pwm1, 100);
    analogWrite(pwm2, 0);
    analogWrite(pwm3, -100);
    analogWrite(pwm4, 0);
  }
}
void right(int period = 0) {
  int time = millis();
  while (millis() - time <= period) {
    analogWrite(pwm1, -100);
    analogWrite(pwm2, 0);
    analogWrite(pwm3, 100);
    analogWrite(pwm4, 0);
  }
}
void trackline(int period = 0) {
  int time = millis();
  while (millis() - time <= period) {
    if (sensorValues[0] >= 800 && sensorValues[1] >= 800) {
      analogWrite(pwm1, 0);
      analogWrite(pwm2, 0);
      analogWrite(pwm3, 0);
      analogWrite(pwm4, 0);
    }
    while (sensorValues[0] <= 400 && sensorValues[1] <= 400) {
      analogWrite(pwm1, 50);
      analogWrite(pwm2, 0);
      analogWrite(pwm3, 50);
      analogWrite(pwm4, 0);
    }
     while (sensorValues[0] >= 800 ) {
      analogWrite(pwm1, 50);
      analogWrite(pwm2, 0);
      analogWrite(pwm3, -50);
      analogWrite(pwm4, 0);
      delay(150);
    }
     while (sensorValues[1]  >= 800 ) {
      analogWrite(pwm1, -50);
      analogWrite(pwm2, 0);
      analogWrite(pwm3, 50);
      analogWrite(pwm4, 0);
      delay(150);
    }
  }
}