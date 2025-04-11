//some general ideas to improve the movment code

float blackThreshhold = 0.5;

struct motorspeeds testMovement(struct lightSensorReadings inputs)
{
  struct motorspeeds newMotorSpeeds = {0,0};
  if (inputs.left <= blackThreshhold && inputs.center > blackThreshhold && input.right <= blackThreshhold)
  {
    newMotorSpeeds = {1, 1};
  }
  if (inputs.left > blackThreshhold && inputs.center > blackThreshhold && input.right > blackThreshhold)
  {
    newMotorSpeeds = {0, 0};
  }
  if (inputs.left > blackThreshhold && input.right <= blackThreshhold)
  {
    newMotorSpeeds = {0, 1};
  }
  if (inputs.left <= blackThreshhold && input.right > blackThreshhold)
  {
    newMotorSpeeds = {1, 0};
  }
}

struct motorspeeds compleatAdjustment(struct lightSensorReadings inputs)
{
  float difference = inputs.left - inputs.right; //pos left, neg right


}
