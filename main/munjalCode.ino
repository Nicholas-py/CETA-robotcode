float leftError = 0;
float rightError = 0;
float stopSequence = 0; //0 means no intention to stop, 1 means stop warning, 2 means stop
float BTH = 0.5;
float multiplier = 0.2;

float constant = 1;
float correction = 1;
float aggressiveCorrection = 2.5;

struct motorspeeds munjalMovement(struct lightSensorReadings inputs)
{
  struct motorspeeds newMotorSpeeds = {0,0};
 
  //Two of three are sensors are black
  if ((inputs.left >= BTH && inputs.center >= BTH) || (inputs.center >= BTH && inputs.right >= BTH) || (inputs.left >= BTH && inputs.right >= BTH))
  {
    stopSequence = 1;
  }
  else {
    stopSequence = 0;
  }
  
  //Robot deviated right
  if (inputs.left > BTH && inputs.right <= BTH)
  {
    rightError = correction;
    leftError = -correction;
  }
 
  //Robot deviated left
  else if (inputs.left <= BTH && inputs.right > BTH)
  {
    leftError = correction;
    rightError = -correction;
  }
 
  //Robot on track
  else if (inputs.center >= BTH)
  {
    leftError = 0;
    rightError = 0;
  }

  //Robot sees all three white
  else if (inputs.left < BTH && inputs.right < BTH && inputs.center < BTH)
  {
    if (leftError == correction) {
      leftError = aggressiveCorrection;
      rightError = -aggressiveCorrection;
    }
    else if (rightError == correction) {
      rightError = aggressiveCorrection;
      leftError = -aggressiveCorrection;
    }
    if (stopSequence == 1) {
      stopSequence = 2;
    }
  }

  //Decide what to return
  if (stopSequence == 2) {
    newMotorSpeeds = {0, 0}; //Stop the robot
  }
  else {
    newMotorSpeeds = {constant+multiplier*leftError, constant+multiplier*rightError}; //Run the robot as normal
  }

  return newMotorSpeeds;
}
