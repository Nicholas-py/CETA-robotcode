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

enum State {
  STOPPED,
  FOLLOWING,
  TURNING,
  CALIBRATING
};

enum State state = FOLLOWING;

struct motorspeeds EXECUTE_TURNAROUND = {94096584,2398424}; //Values are placeholder, this is an error code
int turnaroundcount = 0;

bool needsToCalibrate = false;
bool stopAfterTwo = false;

void setup() {

  Serial.begin(9600);
  delay(1000);
  Serial.println("Start");
  delay(1000);

  MotorSetup();
  if (needsToCalibrate) {
    state = CALIBRATING;
    CalibrateLightSensors();
    state = FOLLOWING;
  }
 InitalizeConnection();

}



void loop() {
  if (state == FOLLOWING) {
    OnStateFollowing();
  }
  else if (state == STOPPED) {
    SetMotors({0,0});
  }
  sequenceConnect();
 
  //delay(5);
}

void OnStateFollowing() {
  struct lightSensorReadings inputs = GetCalibratedSensorInputs();
  bool collisionBool = GetUltrasonicInput();
  struct motorspeeds newMotorSpeeds = MovementLogic(inputs); //mujalMovement(inputs, collisionBool)

  if (newMotorSpeeds.left == EXECUTE_TURNAROUND.left){
    if (turnaroundcount < 1 || !stopAfterTwo){
    SwitchState(TURNING);
    TurnAround();
    turnaroundcount++;}
   
    else {
      state = STOPPED;
      SetMotors({0,0});
    }
  }
  SetMotors(newMotorSpeeds);

}

void SwitchState(enum State newstate) {
  state = newstate;
}