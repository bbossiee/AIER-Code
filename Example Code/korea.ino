#include <QTRSensors.h>
#include <SparkFun_TB6612.h>
QTRSensors qtr;

const uint8_t SensorCount = 2;
uint16_t sensorValues[SensorCount];
uint16_t line_detect1, line_detect2;  // Declare line_detect1 and line_detect2 variables

#define TIMEOUT 2500
const int trig = 12;      //ประกาศขา trig
const int echo = 13;      //ประกาศขา echo
long duration, distance;  //ประกาศตัวแปรเก็บค่าระยะ
#define AIN1 4
#define BIN1 8
#define AIN2 5
#define BIN2 9
#define PWMA 10
#define PWMB 11
#define STBY 6
const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup() {
  // Wire.begin();  // Initialize I2C communication
  Serial.begin(9600);
  // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){ 2, 3 }, SensorCount);
  qtr.setEmitterPin(2);
  Serial.begin(9600);
  pinMode(echo, INPUT);   //สั่งให้ขา echo ใช้งานเป็น input
  pinMode(trig, OUTPUT);  //สั่งให้ขา trig ใช้งานเป็น output


  //เขียนที่นี้
foward(1000);

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
  delay(300);
}
void forward(int period = 0) {
  int time = millis();
  while (millis() - time <= period) {
    long duration, cm;
    forward(motor1, motor2, 150);
  }
  //////////////////////
  if (distance <= 5) {
    brake(motor1, motor2);
    delay(500);
  }
}
void left(int period = 0) {
  int time = millis();
  while (millis() - time <= period) {
    left(motor1, motor2, 100);
    delay(1000);
    brake(motor1, motor2);
    delay(500);
  }
}
void right(int period = 0) {
  int time = millis();
  while (millis() - time <= period) {
    right(motor1, motor2, 100);
    delay(1000);
    brake(motor1, motor2);
    delay(500);
  }
}
void trackline(int period = 0) {
  int time = millis();
  while (millis() - time <= period) {
    if (sensorValues[0] >= 800 && sensorValues[1] >= 800) {
      brake(motor1, motor2);
      delay(500);
    }
    while (sensorValues[0] <= 400 && sensorValues[1] <= 400) {
      forward(motor1, motor2, 150);
    }
    while (sensorValues[0] >= 800) {
      left(motor1, motor2, 100);
      delay(150);
    }
    while (sensorValues[1] >= 800) {
      right(motor1, motor2, 100);
      delay(150);
    }
  }
}