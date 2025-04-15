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

struct motorspeeds EXECUTE_TURNAROUND = {94096584,2398424}; //Values are placeholder, this is essentially an error code
int turnaroundcount = 0;

bool needsToCalibrate = true;

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
  struct motorspeeds newMotorSpeeds = munjalMovement(inputs);
  
  if (newMotorSpeeds.left == EXECUTE_TURNAROUND.left){
    TurnAround();
  }
  
  if (!needsToCalibrate) {
    SetMotors(newMotorSpeeds);
  }

  delay(10);
}
