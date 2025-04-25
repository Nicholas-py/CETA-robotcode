#include <Servo.h>

struct wheelSpeeds stopSpeeds = {90,90};
float speedAdjustmentFactor[2] = {-21,-20}; 

Servo rServo;
Servo lServo;

void MotorSetup() {
  rServo.attach(4);
  lServo.attach(5);
}

void SetWheelServoSpeed(struct wheelSpeeds newMotorSpeeds) 
{
  lServo.write(newMotorSpeeds.left  * speedAdjustmentFactor[0] + stopSpeeds.left);
  rServo.write(newMotorSpeeds.right * speedAdjustmentFactor[1] + stopSpeeds.right);
  //PrintMotorSpeeds(newMotorSpeeds);
}


void SlowTurnAround() {
  SetWheelServoSpeed({1,1});
  delay(1400); //How long to go straight
  SetWheelServoSpeed({0,0});
  delay(300);
  SetWheelServoSpeed({-1,1});
  delay(600);
  while (SensorsDetectAllWhite(GetCalibratedSensorInputs())) {
    delay(10);
  }
  SetWheelServoSpeed({0,0});
  delay(300);
  setNewRobotMovementState(FOLLOWING);
}

void FastTurnAround() {
  delay(300);
  delay(600);
  while (SensorsDetectAllWhite(GetCalibratedSensorInputs())) {
    delay(10);
  }
  SetWheelServoSpeed({0,0});
  delay(300);
  setNewRobotMovementState(FOLLOWING);

}

void PrintMotorSpeeds(struct wheelSpeeds toprint) {
    Serial.print("Speeds: Left: ");
    Serial.print(toprint.left);
    Serial.print(" Right: ");
    Serial.println(toprint.right);

}

