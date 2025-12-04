#include <Servo.h>

//When the motors are at this speed, they will not be moving
struct wheelSpeeds stopSpeeds = {90,90};

//constant to multiply the speed by
float speedAdjustmentFactor[2] = {-21.0,-23.0}; 

Servo rServo;
Servo lServo;

void MotorSetup() {
  rServo.attach(4);
  lServo.attach(5);
}

void SetSpeedAdjustmentFactor(float newAdjustmentFactor[2])
{
  speedAdjustmentFactor[0] = newAdjustmentFactor[0];
  speedAdjustmentFactor[1] = newAdjustmentFactor[1];


}

void SetWheelServoSpeed(struct wheelSpeeds newMotorSpeeds) 
{
  lServo.write(newMotorSpeeds.left  * speedAdjustmentFactor[0] + stopSpeeds.left);
  rServo.write(newMotorSpeeds.right * speedAdjustmentFactor[1] + stopSpeeds.right);
}

void ForwardSlightly() {
    SetWheelServoSpeed({1,1});
    delay(300);
}

void Spin()
{
  SetWheelServoSpeed({0,0});
  delay(10);
  SetWheelServoSpeed({-0.99,0.99});
  delay(425);
  while (SensorsDetectAllWhite(GetCalibratedSensorInputs())) {
    delay(5);
  }
  SetWheelServoSpeed({0,0});
  //SetWheelServoSpeed({-0.75,0.75});
  delay(10);
  setNewRobotMovementState(FOLLOWING);
}

void SlowTurnAround() {
  SetWheelServoSpeed({0.75,1});
  delay(50); //How long to go straight
  Spin();
}

void Turn90Deg(float mult)
{
  SetWheelServoSpeed({-1 * mult,1 * mult});
  delay(600);
  setNewRobotMovementState(FOLLOWING);
}

void SupperTurnAround() {
  SetWheelServoSpeed({2,2});
  delay(300); //How long to go straight
  SetWheelServoSpeed({0,0});
  delay(100);
  SetWheelServoSpeed({-0.75,1.25});
  delay(850);
  while (SensorsDetectAllWhite(GetCalibratedSensorInputs())) {
    delay(5);
  }
  SetWheelServoSpeed({0,0});
  //SetWheelServoSpeed({-0.75,0.75});
  delay(300);
  setNewRobotMovementState(FOLLOWING);
}

void PrintMotorSpeeds(struct wheelSpeeds toprint) {
    Serial.print("Speeds: Left: ");
    Serial.print(toprint.left);
    Serial.print(" Right: ");
    Serial.println(toprint.right);

}

