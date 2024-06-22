// set pin numbers for switch, joystick axes, and LED:
#define hallXPIN A0
#define hallYPIN A1
#define buttonPIN 2

#define enableAPIN 11
#define in1PIN 10
#define in2PIN 9
#define in3PIN 8
#define in4PIN 7
#define enableBPIN 6

const int refreshTime = 50; // [ms]
const int range = 512;

int valX = 0;
int valY = 0;
int mappedX;
int mappedY;

bool button = false;

void setup() {
  Serial.begin(115200);
  pinMode(enableAPIN,OUTPUT);
  pinMode(in1PIN,OUTPUT);
  pinMode(in2PIN,OUTPUT);
  pinMode(in3PIN,OUTPUT);
  pinMode(in4PIN,OUTPUT);
  pinMode(enableBPIN,OUTPUT);

  // Initial direction magnets
  digitalWrite(in1PIN, LOW);
  digitalWrite(in2PIN, HIGH);

  digitalWrite(in3PIN, LOW);
  digitalWrite(in4PIN, HIGH);
  
}

//Measure RPM
void loop() {
  valX = analogRead(hallXPIN);
  valY = analogRead(hallYPIN);

  // map the reading from the analog input range to the output range:
  mappedX = map(valX, 0, 1023, -range, range);
  // map the reading from the analog input range to the output range:
  mappedY = map(valY, 0, 1023, -range, range);

  button = digitalRead(buttonPIN);

  Serial.print(button);

  Serial.print("Hall sensor Data,\tX: ");
  Serial.print(mappedX);
  Serial.print("\tY: ");
  Serial.println(mappedY);

  if (button) {
    analogWrite(enableAPIN, 255);
    analogWrite(enableBPIN, 255);
  } else {
    analogWrite(enableAPIN, 0);
    analogWrite(enableBPIN, 0);
  }



  delay(refreshTime);
}
