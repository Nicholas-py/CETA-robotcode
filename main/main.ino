#include <Servo.h>


struct lightSensorReadings {
  float left;
  float center;
  float right;
};

struct motorspeeds {
  float left;
  float right;
};

bool needsToCalibrate = false;

void setup() {

  Serial.begin(9600);
  delay(1000);
  Serial.println("Start");
  delay(1000);

  MotorSetup();
  if (needsToCalibrate) {
    CalibrateLightSensors();
    needsToCalibrate = false;
  }
  

}



void loop() {
  struct lightSensorReadings inputs = GetCalibratedSensorInputs();
    
  struct motorspeeds newMotorSpeeds = MovementLogic(inputs);

  if (!needsToCalibrate) {
    SetMotorSpeeds(newMotorSpeeds);
  }

  delay(5);
}
