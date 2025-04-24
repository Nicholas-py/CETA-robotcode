#include "config.h"

struct motorspeeds {
  float left;
  float right;
};

struct lightSensorReadings {
  float left;
  float center;
  float right;
};

enum State {
  STOPPED,
  FOLLOWING,
  TURNING,
  CALIBRATING
};

float turnaroundcode = 2398424;
struct motorspeeds SLOW_TURNAROUND = {94096584.0,turnaroundcode}; //Values are placeholder, this is an error code
struct motorspeeds FAST_TURNAROUND = {82364983.0,turnaroundcode}; //Values are placeholder, this is an error code

enum State state = FOLLOWING;



void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Start");
  delay(1000);

  //Connects wheels to pins so we may comunicate with them
  MotorSetup();

  if (_ShouldCalibrate == true) {
    changeState(CALIBRATING);
    CalibrateLightSensors();
    changeState(FOLLOWING);
  }

  //Connects robot to adafruit to accomplish task #2
  if (_shouldConnectHQTTC)
  {
    InitalizeConnection();
  }
}



void loop() {
  
  if (state == FOLLOWING) {
    OnLineFollowing();
  }

  else if (state == STOPPED) {
    SetMotors({0,0});
  }
  // delay(5);
}


void changeState(enum State newstate) {
  state = newstate;
}