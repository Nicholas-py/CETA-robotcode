//some general ideas to improve the movment code

float blackThreshhold = 0.75;
float fullBlackThreshhold = 0.91;
float speed = 1;
int seeBlack;

struct wheelSpeeds AdrianLineFollowing(struct lightSensorReadings inputs)
{
  struct wheelSpeeds newMotorSpeeds = {0,0};
  // Only center black
  if (inputs.left <= blackThreshhold && inputs.center > blackThreshhold && inputs.right <= blackThreshhold)
  {
    newMotorSpeeds = {speed, speed};
  }
  //All are black but to a lesser degree
  else if (inputs.left > blackThreshhold && inputs.center > blackThreshhold && inputs.right > blackThreshhold)
  {
    newMotorSpeeds = {0.6f * speed, 0.6f * speed};
  }
  //left is black and right is white
  else if (inputs.left > blackThreshhold && inputs.right <= blackThreshhold)
  {
    newMotorSpeeds = {0, 0.6f * speed};
  }
  //left is white and right is black
  else if (inputs.left <= blackThreshhold && inputs.right > blackThreshhold)
  {
    newMotorSpeeds = {0.6f * speed, 0};
  }
  //if nothing else go back
  else
  {
    newMotorSpeeds = {-0.8f * speed, -0.8f * speed};
    delay(10);
  }

  //All are fully black (for detecting 'T')
  if (inputs.left >= fullBlackThreshhold && inputs.center >= fullBlackThreshhold && inputs.right >= fullBlackThreshhold)
  {
    seeBlack++;
    if (seeBlack >= 2)
    {
      newMotorSpeeds = SLOW_TURNAROUND;
      seeBlack = 0;
    }
  }
  else
  {
    seeBlack = 0;
  }

  return newMotorSpeeds;
}
