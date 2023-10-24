#include <Wire.h>
#include <ArduCAM.h>
#include <SPI.h>

ArduCAM myCAM(OV7670, CS); // Change 'CS' to the appropriate chip select pin

void setup() {
  Serial.begin(115200);
  Wire.begin();
  if (myCAM.init()) {
    Serial.println(F("ArduCAM initialization done."));
  } else {
    Serial.println(F("ArduCAM initialization failed."));
    while (1);
  }
  myCAM.OV7670_set_JPEG_size(OV7670_320x240);
}

void loop() {
  captureImage();
  delay(1000); // Capture an image every 1 second
}

void captureImage() {
  myCAM.flush_fifo();
  myCAM.clear_fifo_flag();
  myCAM.start_capture();
  while (!myCAM.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK));
  Serial.println(F("Image captured."));
}
