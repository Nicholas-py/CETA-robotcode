#include <Servo.h>

//When the motors are at this speed, they will not be moving
struct wheelSpeeds stopSpeeds = {90,90};

//constant to multiply the speed by
float speedAdjustmentFactor[2] = {-23,-20}; 

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
}


void SlowTurnAround() {
  SetWheelServoSpeed({1,1});
  delay(1000); //How long to go straight
  SetWheelServoSpeed({0,0});
  delay(300);
  SetWheelServoSpeed({-0.75,0.75});
  delay(500);
  while (SensorsDetectAllWhite(GetCalibratedSensorInputs())) {
    delay(5);
  }
  SetWheelServoSpeed({0,0});
  //delay(300);
  setNewRobotMovementState(FOLLOWING);
}

void FastTurnAround() {
  delay(300);
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

