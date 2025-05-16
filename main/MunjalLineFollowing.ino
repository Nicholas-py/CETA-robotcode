
// float leftError = 0;
// float rightError = 0;
// float stop = 0;
// float originalStopTH = 40;
// float stopTH = originalStopTH;
// float aggressiveStopTH = 70;
// float BTH = 0.6;
// float multiplier = 0.35;

// float originalConstant = 1.4;
// float constant = originalConstant;
// float aggressiveConstant = 0.8;
// float correction = 1;
// float aggressiveCorrection = 3.6;

// Working values:
float leftError = 0;
float rightError = 0;
float stop = 0;
float stopTH = 40;
float BTH = 0.6;
float multiplier = 0.35;

float constant = 1.3;
float correction = 1;
float aggressiveCorrection = 3.7;
// No aggressive constants or stopTH

struct wheelSpeeds MunjalLineFollowing(struct lightSensorReadings inputs)
{
  struct wheelSpeeds newMotorSpeeds = {0,0};

  //inputs.left >= BTH && inputs.center >= BTH && inputs.right >= BTH
  //(inputs.left >= BTH && inputs.center >= BTH) || (inputs.left >= BTH && inputs.right >= BTH) || (inputs.right >= BTH && inputs.center >= BTH)

  //All three are sensors are black
  if (inputs.left >= BTH && inputs.center >= BTH && inputs.right >= BTH)
  {
    stop += 1;
  }
  else {
    if (stop <= 0) {
      stop = 0;
    }
    else {
      stop -= 1;
    }
  }
  
  //Robot on track
  if (inputs.center >= BTH)
  {
    // constant = originalConstant;
    // stopTH = originalStopTH;
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
      // constant = aggressiveConstant;
      // stopTH = aggressiveStopTH;
      leftError = aggressiveCorrection;
      rightError = -aggressiveCorrection;
    }
    else if (rightError > 0) {
      // constant = aggressiveConstant;
      // stopTH = aggressiveStopTH;
      rightError = aggressiveCorrection;
      leftError = -aggressiveCorrection;
    }
  }

  //Decide what to return
  if (stop >= stopTH) {
    stop = 0;
    newMotorSpeeds = SLOW_TURNAROUND;
  }
  else {
    newMotorSpeeds = {constant+multiplier*leftError, constant+multiplier*rightError}; //Run the robot as normal
  }

  return newMotorSpeeds;
}
