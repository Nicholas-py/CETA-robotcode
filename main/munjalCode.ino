//some general ideas to improve the movement code

//These two variables should retain their values each time the code loops (no reset). Their initial value should be 0
float leftError = 0;
float rightError = 0;


float multiplier = 0.1;
float BTH = 0.5;

struct motorspeeds mujalMovment(struct lightSensorReadings inputs)
{
  struct motorspeeds newMotorSpeeds = {0,0};
 
  //All three black means stop
  if (inputs.left >= BTH && inputs.center >= BTH && inputs.right >= BTH)
  {
    newMotorSpeeds = {0, 0};
  }
 
  //Robot deviated right
  else if (inputs.left > BTH && inputs.right <= BTH)
  {
    rightError += 1;
    leftError = 0;
    newMotorSpeeds = {multiplier*leftError, multiplier*rightError};
  }
 
  //Robot deviated left
  else if (inputs.left <= BTH && inputs.right > BTH)
  {
    leftError += 1;
    rightError = 0;
    newMotorSpeeds = {multiplier*leftError, multiplier*rightError};
  }
 
  //Robot on track
  else
  {
    leftError = 0;
    rightError = 0;
    newMotorSpeeds = {0.5, 0.5};
  }

  return newMotorSpeeds;
}