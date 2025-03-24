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

#define Button GP15

struct motorspeeds {
  float left;
  float right;
};


void setup() {

  lServo.attach(5);
  rServo.attach(4);
  Serial.begin(9600);
  Serial.println("5");
  struct motorspeeds aaa = MovementLogic(1,1,1);
  Serial.print(aaa.left);
}

void loop() {
  float centerSensor = analogRead(SA0); //right
  float leftSensor = analogRead(SA1); //center
  float rightSensor = analogRead(SA2); //left
  float Button = digitalRead(Bu); //left


  //lServo.write(180);
  //rServo.write(0);
  if (a == 0 && a==1)
  {
    Serial.print("A ");
    Serial.println(a);
    Serial.print("B ");
    Serial.println(b);
    Serial.print("C ");
    Serial.println(c);
    Serial.print("Button ");
    Serial.println(Button);


    delay(100);
  }
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
