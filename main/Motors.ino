struct motorspeeds stopSpeeds = {90,90};
float speedAdjustmentFactor[2] = {-21,-20}; 




Servo rServo;
Servo lServo;

void MotorSetup() {
  rServo.attach(4);
  lServo.attach(5);
}

void SetMotors(struct motorspeeds newMotorSpeeds) 
{
  lServo.write(newMotorSpeeds.left  * speedAdjustmentFactor[0] + stopSpeeds.left);
  rServo.write(newMotorSpeeds.right * speedAdjustmentFactor[1] + stopSpeeds.right);
  //PrintMotorSpeeds(newMotorSpeeds);
}


void TurnAround() {
  SetMotors({1,1});
  delay(1400); //How long to go straight
  SetMotors({0,0});
  delay(300);
  SetMotors({-1,1});
  delay(600);
  while (SensorsDetectAllWhite(GetCalibratedSensorInputs())) {
    delay(10);
  }
  SetMotors({0,0});
  delay(300);
  changeState(FOLLOWING);
}

void PrintMotorSpeeds(struct motorspeeds toprint) {
      Serial.print("Speeds: Left: ");
    Serial.print(toprint.left);
    Serial.print(" Right: ");
    Serial.println(toprint.right);

}

