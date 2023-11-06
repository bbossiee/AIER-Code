
// #include <QTRSensors.h>
#include <SparkFun_TB6612.h>
// const uint8_t SensorCount = 8;  // number of sensors used
#include <Wire.h>
#include <NewPing.h>  // Library for ultrasonic sensor

#define TRIGGER_PIN 21
#define ECHO_PIN 20
#define MAX_DISTANCE 200  // Maximum distance for the sensor in centimeters

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

////motor ซ้าย
#define pwm1 4
#define pwm2 5
//// motor ขวา
#define pwm3 7
#define pwm4 6
unsigned int uS1 = 0;
unsigned int cm1 = 0;
unsigned int uS2 = 0;
unsigned int cm2 = 0;
unsigned int uS3 = 0;
unsigned int cm3 = 0;

void setup() {
  Wire.begin();  // Initialize I2C communication
  Serial.begin(9600);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(pwm4, OUTPUT);
}

void loop() {
  unsigned int uS1 = sonar.ping();           // Send a ping and get the echo time in microseconds
  unsigned int cm1 = sonar.convert_cm(uS1);  // Convert the echo time to centimeters
  unsigned int uS2 = sonar.ping();           // Send a ping and get the echo time in microseconds
  unsigned int cm2 = sonar.convert_cm(uS2);  // Convert the echo time to centimeters
  unsigned int uS3 = sonar.ping();           // Send a ping and get the echo time in microseconds
  unsigned int cm3 = sonar.convert_cm(uS3);  // Convert the echo time to centimeters
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
}
void forward(int distance) {
  while (1) {
    long duration, cm;
    analogWrite(pwm1, 220);
    analogWrite(pwm2, 0);

    analogWrite(pwm3, 255);
    analogWrite(pwm4, 0);
    if (cm2 >= 5) {
      analogWrite(pwm1, 220);
      analogWrite(pwm2, 0);

      analogWrite(pwm3, 255);
      analogWrite(pwm4, 0);
    } else if (cm1 >= 5) {
      analogWrite(pwm1, 220);
      analogWrite(pwm2, 0);

      analogWrite(pwm3, 255);
      analogWrite(pwm4, 0);
    } else if (cm3 >= 5) {
      analogWrite(pwm1, 220);
      analogWrite(pwm2, 0);

      analogWrite(pwm3, 255);
      analogWrite(pwm4, 0);
    }
  }
}