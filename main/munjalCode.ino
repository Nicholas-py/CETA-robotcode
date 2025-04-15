//This probably won't work but hooray if it does!

float leftError = 0;
float rightError = 0;

float multiplier = 0.2;
float constant = 1;
float BTH = 0.5;
float correction = 1;
float aggressiveCorrection = 2.5;

struct motorspeeds mujalMovment(struct lightSensorReadings inputs)
{
  struct motorspeeds newMotorSpeeds = {0,0};
 
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

  newMotorSpeeds = {constant+multiplier*leftError, constant+multiplier*rightError};

  //All three black means stop
  if (inputs.left >= BTH && inputs.center >= BTH && inputs.right >= BTH)
  {
    newMotorSpeeds = {0, 0};
  }

  return newMotorSpeeds;
}