// 2022-08-09
//
// Modified Basic Example (Blink") for RPI-Pico-WH-based CETA IoT Robot
// Refer to Schematic Diagram (#14-00069A)
//
// LED ("USER LED") connected to digital pin 14 (GP14)
//
#include <Servo.h>


//int Lspeeds[1] = [-20];
//int Rspeeds[1] = [-20];

Servo rServo;
Servo lServo;

#define SA0 A0
#define SA1 A1
#define SA2 A2

#define CalButton D15

float WhiteValue[3] = {0, 0, 0};
float BlackValue[3] = {1000, 1000, 1000};
bool hasCalibratedWhite = false;

void setup() {

  lServo.attach(5);
  rServo.attach(4);
  Serial.begin(9600);
  Serial.println("5");

}

void loop() {
  float centerSensor = analogRead(SA0); 
  float leftSensor = analogRead(SA1); 
  float rightSensor = analogRead(SA2); 
  float CallibrationButton = digitalRead(CalButton); //left

  //lServo.write(180);
  //rServo.write(0);
  /*
    Serial.print("Center ");
    Serial.println(centerSensor);
    Serial.print("Left ");
    Serial.println(leftSensor);
    Serial.print("Right ");
    Serial.println(rightSensor);
    Serial.print("Button ");
    Serial.println(CallibrationButton);
*/
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


    delay(100);
}


/*
int pin = 14;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(pin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second
}
*/
