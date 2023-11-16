#include <QTRSensors.h>

QTRSensors qtr;

const uint8_t SensorCount = 2;
uint16_t sensorValues[SensorCount];
uint16_t line_detect1, line_detect2; // Declare line_detect1 and line_detect2 variables

void setup()
{
  // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){2,3}, SensorCount);
  qtr.setEmitterPin(2);

  Serial.begin(9600);
}

void loop()
{
  // read raw sensor values
  qtr.read(sensorValues);


    line_detect1 = sensorValues[0]; // Correct array name
    line_detect2 = sensorValues[1]; // Correct array name
    Serial.print(line_detect1);
    Serial.print("   ");
    Serial.println(line_detect2);
  }

