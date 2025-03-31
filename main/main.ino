#include <Servo.h>

//int Lspeeds[1] = [-20];
//int Rspeeds[1] = [-20];

Servo rServo;
Servo lServo;

#define SA0 A0
#define SA1 A1
#define SA2 A2

struct sensorreadings {
  float left;
  float middle;
  float right;
};

struct motorspeeds {
  float left;
  float right;
};

#define CalButton 1

float WhiteValue[3] = {0, 0, 0};
float BlackValue[3] = {1000, 1000, 1000};
bool hasCalibratedWhite = false;

void setup() {

  lServo.attach(5);
  rServo.attach(4);
  Serial.begin(9600);
  Serial.println("5");
  struct sensorreadings inp = {1,1,1};
  struct motorspeeds aaa = MovementLogic(inp);
  Serial.print(aaa.left);
}

struct sensorreadings GetInput() {
  float centerSensor = analogRead(SA0); 
  float leftSensor = analogRead(SA1); 
  float rightSensor = analogRead(SA2); 
  float CallibrationButton = digitalRead(CalButton); //left

  //lServo.write(180);
  //rServo.write(0);
    Serial.print("Button ");
    Serial.println(CallibrationButton);
    if (CallibrationButton == 0 && hasCalibratedWhite == false)
    {
      WhiteValue[0] = leftSensor;
      WhiteValue[1] = centerSensor;
      WhiteValue[2] = rightSensor;
      hasCalibratedWhite = true;
      while (CallibrationButton == 0)
      {
        delay(100);
      }
    }
    if (CallibrationButton == 0 && hasCalibratedWhite == true)
    {
      BlackValue[0] = leftSensor;
      BlackValue[1] = centerSensor;
      BlackValue[2] = rightSensor;
      hasCalibratedWhite = false;
      while (CallibrationButton == 0)
      {
        delay(100);
      }
    }
    Serial.println(WhiteValue[0]);
    Serial.println(BlackValue[0]);
  struct sensorreadings dummy = {1,1,1};
  return dummy;
}

void loop() {
    struct sensorreadings inputs = GetInput();
    struct motorspeeds speeds = MovementLogic(inputs);
    ActivateMotors(speeds);
    delay(100);
}

void ActivateMotors(struct motorspeeds speeds) {
  lServo.write(speeds.left);
  rServo.write(speeds.right);
}

void blink() {
  pinMode(14, OUTPUT);
  while (true) {
    digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);                       // wait for a second
    digitalWrite(14, LOW);    // turn the LED off by making the voltage LOW
    delay(500);   }                    // wait for a second
}

