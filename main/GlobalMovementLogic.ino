int numberOfTurnarounds = 0;

//Chooses 1 of the 2 turn arounds to use based on the inputed wheel speeds
void PickWhichTurnAround(struct wheelSpeeds code) {
  pinMode(14, OUTPUT);
  digitalWrite(14,HIGH);
  if (code.left == SLOW_TURNAROUND.left) {
    SlowTurnAround();
  }
  else if (code.left == FAST_TURNAROUND.left) {
    FastTurnAround();
  }
  else if (code.left == SUPPER_TURNAROUND.left) {
    SupperTurnAround();
  }
  digitalWrite(14,LOW);
}

//Picks which line following algarithum to use based on the config
struct wheelSpeeds executeLineFollowing()
{
  struct lightSensorReadings lightSensorInputs = GetCalibratedSensorInputs();
  struct wheelSpeeds newMotorSpeeds;

  //selects which line following code to work
  if (_CurrentLineFollowingLogic == NICHOLAS)
    newMotorSpeeds = NicholasLineFollowing(lightSensorInputs);

  else if (_CurrentLineFollowingLogic == ADRIAN)
    newMotorSpeeds = AdrianLineFollowing(lightSensorInputs);

  else if (_CurrentLineFollowingLogic == MUNJAL)
    newMotorSpeeds = MunjalLineFollowing(lightSensorInputs);

  else if (_CurrentLineFollowingLogic == REVUP)
    newMotorSpeeds = RevUp();

  return newMotorSpeeds;
}

void WhenLineFollowing() {

  struct wheelSpeeds newMotorSpeeds = executeLineFollowing();

  if (_ShouldStopAtWall && GetUltrasonicInput())
  {
    newMotorSpeeds = FAST_TURNAROUND;
  }

  if (newMotorSpeeds.right == turnAroundErrorCode)
  {
    if (numberOfTurnarounds < 3 || !_StopAfterFourTurns)
    {
      setNewRobotMovementState(TURNING);
      PickWhichTurnAround(newMotorSpeeds);
      numberOfTurnarounds++;
    }
    else 
    {
      ForwardSlightly();
      CurrentRobotMovementState = STOPPED;
      SetWheelServoSpeed({0,0});
    }
  }
  else {
    SetWheelServoSpeed(newMotorSpeeds);
  }
}
