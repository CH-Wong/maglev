// set pin numbers for switch, joystick axes, and LED:
const int xAxis = A0;
const int yAxis = A1;
const int ledPin = 7;         // Mouse control LED
const int buttonPin = 8;    // input pin for the mouse pushButton


// set pin numbers for motor control
const int sourceApin1 = 2;
const int sourceApin2 = 3;
const int sourceAcontrol = 9;

const int sourceBpin1 = 4;
const int sourceBpin2 = 5;
const int sourceBcontrol = 10;


// parameters for reading the joystick:
int range = 100;               // output range of X or Y movement
int responseDelay = 100;        // response delay of the mouse, in ms
int threshold = range / 10;    // resting threshold
int center = range / 2;       // resting position value
int xValue = 0;
int yValue = 0;
int reading;
int distance;

void setup() {
  pinMode(ledPin, OUTPUT);         // the LED pin
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);

  pinMode(sourceApin1, OUTPUT);
  pinMode(sourceApin2, OUTPUT);
  //Controlling magnetic field direction
  digitalWrite(sourceApin1, HIGH);
  digitalWrite(sourceApin2, LOW);
  
  pinMode(sourceBpin1, OUTPUT);
  pinMode(sourceBpin2, OUTPUT);
  digitalWrite(sourceBpin1, LOW);  
  digitalWrite(sourceBpin2, LOW);

  pinMode(sourceAcontrol, OUTPUT); 
  pinMode(sourceBcontrol, OUTPUT);
  

  // Default values for current source
  analogWrite(sourceAcontrol, 0); //ENA pin
  analogWrite(sourceBcontrol, 0); //ENB pin set default to off
  
}

void loop() {
  // read and scale the two axes:
  int xValue = readAxis(xAxis);
  int yValue = readAxis(yAxis);

  Serial.print(xValue);
  Serial.print("\t");
  Serial.print(yValue);
  Serial.print("\t");


  // read the mouse button and click or not click:
  if (digitalRead(buttonPin) == HIGH) {
    // if the mouse is not pressed, press it:
    digitalWrite(ledPin, LOW);
    analogWrite(sourceAcontrol, 0); //ENA pin
    Serial.println(LOW); //
  }
    // read the mouse button and click or not click:
  else {
    // if the mouse is not pressed, press it:
    digitalWrite(ledPin, HIGH);
    analogWrite(sourceAcontrol, 255); //ENA pin
    Serial.println(HIGH); //
  }
  delay(responseDelay);
}

/*
  reads an axis (0 or 1 for x or y) and scales the analog input range to a range
  from 0 to <range>
*/

int readAxis(int thisAxis) {
  // read the analog input:
  reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the rest position threshold, use it:
  distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  }

  // return the distance for this axis:
  return distance;
}
