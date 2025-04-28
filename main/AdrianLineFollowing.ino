//some general ideas to improve the movment code

float blackThreshhold = 0.65;
float fullBlackThreshhold = 0.9;
float speed = 1.2;
int timeBlack = 0;
int neededTimeBlack = 4;

struct wheelSpeeds AdrianLineFollowing(struct lightSensorReadings inputs)
{
  struct wheelSpeeds newMotorSpeeds = {0,0};
  if (inputs.left <= blackThreshhold && inputs.center > blackThreshhold && inputs.right <= blackThreshhold)
  {
    newMotorSpeeds = {speed, speed};
  }
  else if (inputs.left > blackThreshhold && inputs.center > blackThreshhold && inputs.right > blackThreshhold)
  {
    newMotorSpeeds = {0.6f, 0.6f};
  }
  else if (inputs.left > blackThreshhold && inputs.right <= blackThreshhold)
  {
    newMotorSpeeds = {0, 0.6f * speed};
  }
  else if (inputs.left <= blackThreshhold && inputs.right > blackThreshhold)
  {
    newMotorSpeeds = {0.6f * speed, 0};
  }
  else
  {
    newMotorSpeeds = {-0.8f * speed, -0.8f * speed};
  }


  if (inputs.left >= fullBlackThreshhold && inputs.center >= fullBlackThreshhold && inputs.right >= fullBlackThreshhold)
  {
    timeBlack ++; SLOW_TURNAROUND;
  }
  else
  {
    if (inputs.left < blackThreshhold && inputs.center < blackThreshhold && inputs.right < blackThreshhold && timeBlack >= neededTimeBlack)
    {
      return SLOW_TURNAROUND;
    }
    timeBlack = 0;
  }

  return newMotorSpeeds;
}
