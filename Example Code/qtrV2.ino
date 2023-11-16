// QTR-1RC Sensor Example

const int sensorPin = A0; // Analog pin where the QTR-1RC sensor is connected

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Read the analog value from the sensor

  // You can adjust the threshold value based on your environment
  int threshold = 500;

  if (sensorValue < threshold) {
    // The sensor is over a dark surface (line is detected)
    Serial.println("Line detected!");
  } else {
    // The sensor is over a light surface (no line detected)
    Serial.println("No line detected");
  }

  delay(100); // Add a short delay to avoid rapid serial prints
}
