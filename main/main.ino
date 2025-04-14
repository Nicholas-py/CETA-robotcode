#include <Servo.h>


//int Lspeeds[1] = [-20];
//int Rspeeds[1] = [-20];

Servo rServo;
Servo lServo;



#define SA0 A0
#define SA1 A1
#define SA2 A2



struct lightSensorReadings {
  float left;
  float center;
  float right;
};

struct motorspeeds {
  float left;
  float right;
};

bool hasCalibratedLightSensors = false;
bool willCalibrate = true;

void setup() {

  lServo.attach(5);
  rServo.attach(4);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Start");
  delay(1000);
  if (willCalibrate) {
  hasCalibratedLightSensors = CalibrateLightSensors();}

}



void loop() {
    struct lightSensorReadings inputs = GetCalibratedSensorInputs();
    
    Serial.print("Readings: Left: ");
    Serial.print(inputs.left);
    Serial.print(" Center: ");
    Serial.print(inputs.center);
    Serial.print(" Right: ");
    Serial.println(inputs.right);

    struct motorspeeds newMotorSpeeds = testMovement(inputs);

    Serial.print("Speeds: Left: ");
    Serial.print(newMotorSpeeds.left);
    Serial.print(" Right: ");
    Serial.println(newMotorSpeeds.right);


    SetMotorSpeeds(newMotorSpeeds);
    delay(100);
}

struct motorspeeds stopSpeeds = {90,90};
float speedAdjustmentFactor[2] = {-10,-10}; 

void SetMotorSpeeds(struct motorspeeds newMotorSpeeds) 
{
  if (hasCalibratedLightSensors || !willCalibrate)
  {
  lServo.write(newMotorSpeeds.left  * speedAdjustmentFactor[0] + stopSpeeds.left);
  rServo.write(newMotorSpeeds.right * speedAdjustmentFactor[1] + stopSpeeds.right);
  }
  else
  {
    lServo.write(stopSpeeds.left);
    rServo.write(stopSpeeds.right);
  }
}

