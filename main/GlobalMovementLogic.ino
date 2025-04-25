int numberOfTurnarounds = 0;

void PickWhichTurnAround(struct wheelSpeeds code) {
    pinMode(14, OUTPUT);
  digitalWrite(14,HIGH);
  if (code.left == SLOW_TURNAROUND.left) {
    SlowTurnAround();
  }
  else if (code.left == FAST_TURNAROUND.left) {
    FastTurnAround();
  }
}


void WhenLineFollowing() {

  struct lightSensorReadings lightSensorInputs = GetCalibratedSensorInputs();
  struct wheelSpeeds newMotorSpeeds;
  if (_CurrentLineFollowingLogic == NICHOLAS)
  {
    newMotorSpeeds = NicholasLineFollowing(lightSensorInputs);
  } 

  
  if (_ShouldStopAtWall == true && GetUltrasonicInput() == true)
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
      CurrentRobotMovementState = STOPPED;
      SetWheelServoSpeed({0,0});
    }
  }
  else {
  SetWheelServoSpeed(newMotorSpeeds);
  }
}
