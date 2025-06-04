int numberOfTurnarounds = 0;
int counter = 0;
int counterTH = 75; //How many cycles between ultrasonic readings
int ToTurn = 0;

void SetToTurn()
{
  ToTurn = 1;
}

String direction = "left";
void changeDirection(int d)
{
  if (d == 0)
    direction = "left";
  else
    direction = "right";
}

//Chooses 1 of the 2 turn arounds to use based on the inputed wheel speeds
void PickWhichTurnAround(struct wheelSpeeds code) {
  pinMode(14, OUTPUT);
  digitalWrite(14,HIGH);
  if (_CarnavalTurn == true && direction == "left")
  {
    Turn90Deg(1);
    digitalWrite(14,LOW);
    return;
  }
  if (_CarnavalTurn == true && direction == "right")
  {
    Turn90Deg(-1);
    digitalWrite(14,LOW);
    return;
  }

  if (code.left == SLOW_TURNAROUND.left) {
    SlowTurnAround();
  }
  else if (code.left == SPIN_TURNAROUND.left) {
    Spin();
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
  else if (_CurrentLineFollowingLogic == CARNAVAL)
    newMotorSpeeds = Carnaval();

  return newMotorSpeeds;
}

void WhenLineFollowing() {

  struct wheelSpeeds newMotorSpeeds = executeLineFollowing();

  if (counter >= counterTH) 
  {
    counter = 0;
    if (_ShouldStopAtWall && GetUltrasonicInput())
    {
      newMotorSpeeds = SPIN_TURNAROUND;
    }
  }

  if (ToTurn == 1)
  {
    ToTurn = 0;
    PickWhichTurnAround(newMotorSpeeds);
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

  counter += 1;
}
