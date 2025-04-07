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
  float center;
  float right;
};

struct motorspeeds {
  float left;
  float right;
};


//When false will calabrate white, when true will calabrate black
bool hasCalibratedWhite = false;

void setup() {

  lServo.attach(5);
  rServo.attach(4);
  Serial.begin(9600);
  delay(100);

  Serial.println("Start");
  blink();

}


//Gets inputs from light sensors and button

void loop() {
    Serial.println("loopin");
    struct sensorreadings inputs = GetInput();
    struct motorspeeds speeds = MovementLogic(inputs);
    SetMotorSpeeds(speeds);
    delay(100);
}

void SetMotorSpeeds(struct motorspeeds speeds) {
  lServo.write(speeds.left);
  rServo.write(speeds.right);
}

void blink() {
  pinMode(14, OUTPUT);
  while (true) {
    digitalWrite(14, HIGH);  
    delay(500);
    digitalWrite(14, LOW);
    delay(500);   }                    
}

