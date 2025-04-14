//some general ideas to improve the movment code

float blackThreshhold = 0.5;

struct motorspeeds testMovement(struct lightSensorReadings inputs)
{
  struct motorspeeds newMotorSpeeds = {0,0};
  if (inputs.left <= blackThreshhold && inputs.center > blackThreshhold && inputs.right <= blackThreshhold)
  {
    newMotorSpeeds = {1, 1};
  }
  //else if (inputs.left > blackThreshhold && inputs.center > blackThreshhold && inputs.right > blackThreshhold)
  //{
  //  newMotorSpeeds = {0, 0};
  //}
  else if (inputs.left > blackThreshhold && inputs.right <= blackThreshhold)
  {
    newMotorSpeeds = {0, 1};
  }
  else if (inputs.left <= blackThreshhold && inputs.right > blackThreshhold)
  {
    newMotorSpeeds = {1, 0};
  }
  else
  {
    newMotorSpeeds = {1, 1};
  }

  return newMotorSpeeds;
}
