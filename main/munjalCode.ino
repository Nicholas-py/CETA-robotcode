//some general ideas to improve the movement code

//These two variables should retain their values each time the code loops (no reset). Their initial value should be 0
float leftError = 0;
float rightError = 0;
float maxError = 100;

float multiplier = 0.05;
float constant = 0.5;
float BTH = 0.5;

struct motorspeeds mujalMovment(struct lightSensorReadings inputs)
{
  struct motorspeeds newMotorSpeeds = {0,0};
 
  // //All three black means stop
  // if (inputs.left >= BTH && inputs.center >= BTH && inputs.right >= BTH)
  // {
  //   newMotorSpeeds = {0, 0};
  // }
 
  //Robot deviated right
  if (inputs.left > BTH && inputs.right <= BTH)
  {
    rightError += 1;
    rightError = min(rightError, maxError);
    leftError = 0;
  }
 
  //Robot deviated left
  else if (inputs.left <= BTH && inputs.right > BTH)
  {
    leftError += 1;
    leftError = min(leftError, maxError);
    rightError = 0;
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
    if (leftError != 0) {
      leftError += 1;
      leftError = min(leftError, maxError);
    }
    else if (rightError != 0) {
      rightError += 1;
      rightError = min(rightError, maxError);
    }
  }

  newMotorSpeeds = {constant+multiplier*leftError, constant+multiplier*rightError};

  return newMotorSpeeds;
}