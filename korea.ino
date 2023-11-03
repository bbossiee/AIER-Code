const int ul1 = 12;
int ur1 = 13;
const int ul2 = 14;
int ur2 = 15;
const int ul3 = 16;
int ur3 = 17;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  long duration, cm;
  pinMode(ul1, OUTPUT);


  digitalWrite(ul1, LOW);
  delayMicroseconds(2);
  digitalWrite(ul1, HIGH);
  delayMicroseconds(5);
  digitalWrite(ul1, LOW);
  pinMode(ur1, INPUT);
  duration = pulseIn(ur1, HIGH);

  cm = microsecondsToCentimeters(duration);

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
