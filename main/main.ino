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

struct motorspeeds stops = {90,90};
float speedfactors[2] = {-31,-30}; 

//When false will calabrate white, when true will calabrate black
bool hasCalibratedWhite = false;

void setup() {


  lServo.attach(5);
  rServo.attach(4);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Start");
  Serial.println("hiiiiii");
  delay(1000);
  //Calibrate();
  //Test123();

  //blink();

}



void loop() {
    //Serial.print("'newcode");
    struct sensorreadings inputs = GetInput();
    Serial.print("Readings: Left: ");
    Serial.print(inputs.left);
    Serial.print("Center: ");
    Serial.print(inputs.center);
    Serial.print("Right: ");
    Serial.println(inputs.right);

    struct motorspeeds speeds = MovementLogic(inputs);

    Serial.print("Speeds: Left: ");
    Serial.print(speeds.left);
    Serial.print("Right: ");
    Serial.println(speeds.right);


    SetMotorSpeeds(speeds);
    delay(100);
}

void SetMotorSpeeds(struct motorspeeds speeds) {
  lServo.write(speeds.left *speedfactors[0]+stops.left);
  rServo.write(speeds.right*speedfactors[1]+stops.right);
}

void blink() {
  pinMode(14, OUTPUT);
  while (true) {
    digitalWrite(14, HIGH);  
    delay(500);
    digitalWrite(14, LOW);
    delay(500);   }                    
}

