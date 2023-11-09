
// #include <QTRSensors.h>
// #include <SparkFun_TB6612.h>
// const uint8_t SensorCount = 8;  // number of sensors used
#include <Wire.h>
#include <NewPing.h>  // Library for ultrasonic sensor

#define TRIGGER_PIN 21
#define ECHO_PIN 20
#define MAX_DISTANCE 200  // Maximum distance for the sensor in centimeters

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

////motor ซ้าย
#define AIN1 4
#define AIN2 2
#define BIN1 8
#define BIN2 10
#define STBY1 6
const int pwm1 = 3;
const int pwm2 = 2;
const int pwm3 = 5;
const int pwm4 = 4;
//// motor ขวา
#define AIN3 5
#define AIN4 3
#define BIN3 9
#define BIN4 11
#define STBY2 7
const int pwm5 = 8;
const int pwm6 = 7;
const int pwm7 = 11;
const int pwm8 = 12;

unsigned int uS1 = 0;
unsigned int cm1 = 0;
unsigned int uS2 = 0;
unsigned int cm2 = 0;
unsigned int uS3 = 0;
unsigned int cm3 = 0;
unsigned int uS4 = 0;
unsigned int cm4 = 0;

void setup() {
  Wire.begin();  // Initialize I2C communication
  Serial.begin(9600);
  output();
}

void loop() {
  unsigned int uS1 = sonar.ping();           // Send a ping and get the echo time in microseconds
  unsigned int cm1 = sonar.convert_cm(uS1);  // Convert the echo time to centimeters
  unsigned int uS2 = sonar.ping();
  unsigned int cm2 = sonar.convert_cm(uS2);
  unsigned int uS3 = sonar.ping();
  unsigned int cm3 = sonar.convert_cm(uS3);
  unsigned int uS4 = sonar.ping();
  unsigned int cm4 = sonar.convert_cm(uS4);
  Serial.print("Distance1: ");
  Serial.print(cm1);
  Serial.println(" cm1");
  delay(100);
  Serial.print("Distance2: ");
  Serial.print(cm2);
  Serial.println(" cm2");
  delay(100);
  Serial.print("Distance3: ");
  Serial.print(cm3);
  Serial.println(" cm3");
  delay(100);
  Serial.print("Distance4: ");
  Serial.print(cm3);
  Serial.println(" cm4");
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

    analogWrite(pwm5, 100);
    analogWrite(pwm6, 0);
    analogWrite(pwm7, 100);
    analogWrite(pwm8, 0);
    //////////////////////
    if (cm2 >= 5) {
      analogWrite(pwm1, 0);
      analogWrite(pwm2, 0);
      analogWrite(pwm3, 0);
      analogWrite(pwm4, 0);

      analogWrite(pwm5, 0);
      analogWrite(pwm6, 0);
      analogWrite(pwm7, 0);
      analogWrite(pwm8, 0);
      //////////////////////
    } else if (cm1 >= 5) {
      analogWrite(pwm1, 100);
      analogWrite(pwm2, 0);
      analogWrite(pwm3, 100);
      analogWrite(pwm4, 0);

      analogWrite(pwm5, 40);
      analogWrite(pwm6, 0);
      analogWrite(pwm7, 40);
      analogWrite(pwm8, 0);
      delay(200);
      //////////////////////
    } else if (cm3 >= 5) {
      analogWrite(pwm1, 40);
      analogWrite(pwm2, 0);
      analogWrite(pwm3, 40);
      analogWrite(pwm4, 0);

      analogWrite(pwm5, 100);
      analogWrite(pwm6, 0);
      analogWrite(pwm7, 100);
      analogWrite(pwm8, 0);
      delay(200);
    }
  }
}
void left(int period = 0) {
  int time = millis();
  while (millis() - time <= period) {
    analogWrite(pwm1, -100);
    analogWrite(pwm2, 0);
    analogWrite(pwm3, -100);
    analogWrite(pwm4, 0);

    analogWrite(pwm5, 100);
    analogWrite(pwm6, 0);
    analogWrite(pwm7, 100);
    analogWrite(pwm8, 0);
  }
}
void right(int period = 0) {
  int time = millis();
  while (millis() - time <= period) {
    analogWrite(pwm1, 100);
    analogWrite(pwm2, 0);
    analogWrite(pwm3, 100);
    analogWrite(pwm4, 0);

    analogWrite(pwm5, -100);
    analogWrite(pwm6, 0);
    analogWrite(pwm7, -100);
    analogWrite(pwm8, 0);
  }
}
void backward(int period = 0) {
  int time = millis();
  while (millis() - time <= period) {
    long duration, cm;
    if (cm4 >= 4) {
      analogWrite(pwm1, -100);
      analogWrite(pwm2, 0);
      analogWrite(pwm3, -100);
      analogWrite(pwm4, 0);

      analogWrite(pwm5, -100);
      analogWrite(pwm6, 0);
      analogWrite(pwm7, -100);
      analogWrite(pwm8, 0);
    }
  }
}
void output() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY1, OUTPUT);
  pinMode(AIN3, OUTPUT);
  pinMode(AIN4, OUTPUT);
  pinMode(BIN3, OUTPUT);
  pinMode(BIN4, OUTPUT);
  pinMode(STBY2, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(pwm4, OUTPUT);
  pinMode(pwm5, OUTPUT);
  pinMode(pwm6, OUTPUT);
  pinMode(pwm7, OUTPUT);
  pinMode(pwm8, OUTPUT);
}