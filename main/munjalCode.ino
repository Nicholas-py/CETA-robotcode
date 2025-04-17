float leftError = 0;
float rightError = 0;
float stop = 0;
float stopTH = 3;
float BTH = 0.5;
float multiplier = 0.4;

float constant = 2;
float correction = 1;
float aggressiveCorrection = 2.5;

struct motorspeeds mujalMovement(struct lightSensorReadings inputs)
{
  struct motorspeeds newMotorSpeeds = {0,0};
 
  //All three are sensors are black
  if (inputs.left >= BTH && inputs.center >= BTH && inputs.right >= BTH)
  {
    stop += 1;
  }
  else {
    stop = 0;
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
  }

  //Decide what to return
  if (stop >= stopTH) {
    return EXECUTE_TURNAROUND;
  }
  else {
    newMotorSpeeds = {constant+multiplier*leftError, constant+multiplier*rightError}; //Run the robot as normal
  }

  return newMotorSpeeds;
}
