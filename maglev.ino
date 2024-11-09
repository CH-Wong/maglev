// set pin numbers for switch, joystick axes, and LED:
#define hallXPIN A4
#define hallYPIN A5
#define buttonPIN 2

#define posXOutPIN 5
#define negXOutPIN 6
#define posYOutPIN 9
#define negYOutPIN 10



const int refreshTime = 1000; // [ms]
const int range = 512;

int valX = 0;
int valY = 0;
int mappedX;
int mappedY;

bool button = false;

void setup() {
  Serial.begin(115200);
  pinMode(posXOutPIN, OUTPUT);
  pinMode(negXOutPIN, OUTPUT);
  pinMode(posYOutPIN, OUTPUT);
  pinMode(negYOutPIN, OUTPUT);

  TCCR0B = TCCR0B & B11111000 | B00000001; // set timer 0 divisor to 1 for PWM frequency of 62500.00 Hz
}

void loop() {
  valX = analogRead(hallXPIN);
  valY = analogRead(hallYPIN);

  // map the reading from the analog input range to the output range:
  mappedX = map(valX, 0, 1023, -255, 255);
  // map the reading from the analog input range to the output range:
  mappedY = map(valY, 0, 1023, -255, 255);

  //  button = digitalRead(buttonPIN);

  //  Serial.print(button);

  Serial.print("\nHall sensor Data,\tX: ");
  Serial.print(valX);

  Serial.print("\tY: ");
  Serial.print(valY);
  
  Serial.print("\tMapped value: ");
  Serial.print(mappedX);
  Serial.print("\tY: ");
  Serial.print(mappedY);

  if (mappedX > 0) {
    analogWrite(posXOutPIN, mappedX);
    analogWrite(negXOutPIN, 0);
    }
  else if (mappedX < 0) {
    analogWrite(posXOutPIN, 0);
    analogWrite(negXOutPIN, -mappedX);
  }

  if (mappedY > 0) {
    analogWrite(posYOutPIN, mappedY);
    analogWrite(negYOutPIN, 0);
    }
  else if (mappedY < 0) {
    analogWrite(posYOutPIN, 0);
    analogWrite(negYOutPIN, -mappedY);
  }


  delay(refreshTime);
}
