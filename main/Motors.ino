struct motorspeeds stopSpeeds = {90,90};
float speedAdjustmentFactor[2] = {-20,-20}; 


Servo rServo;
Servo lServo;

void MotorSetup() {
  rServo.attach(4);
  lServo.attach(5);
}

void SetMotorSpeeds(struct motorspeeds newMotorSpeeds) 
{
  lServo.write(newMotorSpeeds.left  * speedAdjustmentFactor[0] + stopSpeeds.left);
  rServo.write(newMotorSpeeds.right * speedAdjustmentFactor[1] + stopSpeeds.right);
  PrintMotorSpeeds(newMotorSpeeds);
}




void PrintMotorSpeeds(struct motorspeeds toprint) {
      Serial.print("Speeds: Left: ");
    Serial.print(toprint.left);
    Serial.print(" Right: ");
    Serial.println(toprint.right);

}