#include <Servo.h>
#include "config.h"

struct lightSensorReadings {
  float left;
  float center;
  float right;
};

struct motorspeeds {
  float left;
  float right;
};

enum State {
  STOPPED,
  FOLLOWING,
  TURNING,
  CALIBRATING
};

enum State state = FOLLOWING;

struct motorspeeds EXECUTE_TURNAROUND = {94096584,2398424}; //Values are placeholder, this is an error code

int turnAroundCount = 0;

void setup() {

  //Say that the robot has started
  Serial.begin(9600);
  delay(1000);
  Serial.println("Start");
  delay(1000);

  //Connects wheels to pins so we may comunicate with them
  MotorSetup();

  //So we don't have to calabrate light sensors every time durring testing
  if (_ShouldCalibrate == true) {
    state = CALIBRATING;
    CalibrateLightSensors();
    state = FOLLOWING;
  }

  //Connects robot to adafruit to accomplish task #2
  if (_shouldConnectHQTTC)
  {
    InitalizeConnection();
  }
}



void loop() {
  
  //Why?
  if (state == FOLLOWING) {
    OnStateFollowing();
  }
  //Stops the motors
  else if (state == STOPPED) {
    SetMotors({0,0});
  }
  // delay(5);
}

void OnStateFollowing() {
  struct lightSensorReadings inputs = GetCalibratedSensorInputs();
  bool collisionBool = GetUltrasonicInput();
  struct motorspeeds newMotorSpeeds = munjalMovement(inputs, collisionBool);

  if (newMotorSpeeds.left == EXECUTE_TURNAROUND.left){
    if (turnAroundCount < 1 || !_StopAfterTwoTurns){
    SwitchState(TURNING);
    TurnAround();
    turnAroundCount++;}
   
    else {
      state = STOPPED;
      SetMotors({0,0});
    }
  }
  SetMotors(newMotorSpeeds);

}

//Changes the state to the probivded new state
void SwitchState(enum State newstate) {
  state = newstate;
}