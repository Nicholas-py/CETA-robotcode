float leftError = 0;
float rightError = 0;
float stop = 0;
float stopTH = 30;
float BTH = 0.5;
float multiplier = 0.35;

float constant = 1.5;
float correction = 1;
float aggressiveCorrection = 3.5;

struct wheelSpeeds MunjalLineFollowing(struct lightSensorReadings inputs)
{
  struct wheelSpeeds newMotorSpeeds = {0,0};

  //All three are sensors are black
  if (inputs.left >= BTH && inputs.center >= BTH && inputs.right >= BTH)
  {
    stop += 1;
  }
  else {
    stop = 0;
  }
  
  //Robot on track
  if (inputs.center >= BTH)
  {
    leftError = 0;
    rightError = 0;
  }

  //Robot deviated right
  else if (inputs.left > BTH && inputs.right <= BTH)
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
 
  //Robot sees all three white
  else if (inputs.left < BTH && inputs.right < BTH && inputs.center < BTH)
  {
    if (leftError > 0) {
      leftError = aggressiveCorrection;
      rightError = -aggressiveCorrection;
    }
    else if (rightError > 0) {
      rightError = aggressiveCorrection;
      leftError = -aggressiveCorrection;
    }
  }

  //Decide what to return
  if (stop >= stopTH) {
    newMotorSpeeds = SLOW_TURNAROUND;
  }
  else {
    newMotorSpeeds = {constant+multiplier*leftError, constant+multiplier*rightError}; //Run the robot as normal
  }

  return newMotorSpeeds;
}
