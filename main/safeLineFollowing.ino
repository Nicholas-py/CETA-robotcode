//some general ideas to improve the movment code

float blackThreshhold = 0.5;

struct wheelSpeeds safeLineFollowing(struct lightSensorReadings inputs)
{
  struct wheelSpeeds newMotorSpeeds = {0,0};
  if (inputs.left <= blackThreshhold && inputs.center > blackThreshhold && inputs.right <= blackThreshhold)
  {
    newMotorSpeeds = {1, 1};
  }
  else if (inputs.left > blackThreshhold && inputs.center > blackThreshhold && inputs.right > blackThreshhold)
  {
    newMotorSpeeds = {0.5, 0.5};
  }
  else if (inputs.left > blackThreshhold && inputs.right <= blackThreshhold)
  {
    newMotorSpeeds = {0, 0.5};
  }
  else if (inputs.left <= blackThreshhold && inputs.right > blackThreshhold)
  {
    newMotorSpeeds = {0.5, 0};
  }
  else
  {
    newMotorSpeeds = {-0.5, -0.5};
  }

  return newMotorSpeeds;
}
