// set pin numbers for switch, joystick axes, and LED:
#define HallX_PIN A0
#define HallY_PIN A1
const int refreshTime = 50; // [ms]
const int range = 512;

int valX = 0;
int valY = 0;
int mappedX;
int mappedY;

void setup() {
  Serial.begin(115200);
}

//Measure RPM
void loop() {
  valX = analogRead(HallX_PIN);
  valY = analogRead(HallY_PIN);

  // map the reading from the analog input range to the output range:
  mappedX = map(valX, 0, 1023, -range, range);
  // map the reading from the analog input range to the output range:
  mappedY = map(valY, 0, 1023, -range, range);

  Serial.print("Hall sensor Data,\tX: ");
  Serial.print(mappedX);
  Serial.print("\tY: ");
  Serial.println(mappedY);



  delay(refreshTime);
}
