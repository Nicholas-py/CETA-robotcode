#include "config.h"
#include <ArduinoMqttClient.h>

struct wheelSpeeds {
  float left;
  float right;
};

struct lightSensorReadings {
  float left;
  float center;
  float right;
};

enum RobotMovementStates {
  STOPPED,
  FOLLOWING,
  TURNING,
  CALIBRATING
};

// 'Error' code for executing a turn around
float turnAroundErrorCode = 2398424;
struct wheelSpeeds SLOW_TURNAROUND = {94096584.0,turnAroundErrorCode};
struct wheelSpeeds FAST_TURNAROUND = {82364983.0,turnAroundErrorCode};
struct wheelSpeeds SPIN_TURNAROUND = {71234126.0,turnAroundErrorCode};

// Will have the robot start by following the line
enum RobotMovementStates CurrentRobotMovementState = FOLLOWING;

void setup() {

  // Connects robot to the Serial monitor so we can view its output
  Serial.begin(9600);
  delay(1000);
  Serial.println("Starting Robot");
  delay(1000);

  //Connects wheels to pins so we may comunicate with them
  MotorSetup();

  if (_CurrentLineFollowingLogic == SHOWCASE) {
  Showcase();}

  // Allows toggoling on and off weather the robot should be calabrated
  if (_ShouldCalibrate == true) {
    setNewRobotMovementState(CALIBRATING);
    CalibrateLightSensors();
    setNewRobotMovementState(FOLLOWING);
  }

  // Allows toggoling on and off weather the robot should be started by adafruit
  // Use config.h and secrets.h to configure the HQTTC connection
  if (_shouldConnectToHQTTC)
  {
    InitalizeHQTTCConnection();
  }
  ForwardSlightly();
}



void loop() {
  if (_shouldConnectToHQTTC)
    HQTTCPole();
  
  if (CurrentRobotMovementState == FOLLOWING) {
    WhenLineFollowing();
  }
  else if (CurrentRobotMovementState == STOPPED) {
    SetWheelServoSpeed({0,0});
  }
}


void setNewRobotMovementState(enum RobotMovementStates newstate) {
  CurrentRobotMovementState = newstate;
}