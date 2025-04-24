int turnAroundCount = 0;


void OnLineFollowing() {
  struct lightSensorReadings inputs = GetCalibratedSensorInputs();
  bool collisionBool = GetUltrasonicInput();
  struct motorspeeds newMotorSpeeds = munjalMovement(inputs, collisionBool);

  if (newMotorSpeeds.left == EXECUTE_TURNAROUND.left){
    if (turnAroundCount < 3 || !_StopAfterFourTurns){
    ChangeState(TURNING);
    TurnAround();
    turnAroundCount++;}
   
    else {
      state = STOPPED;
      SetMotors({0,0});
    }
  }
  SetMotors(newMotorSpeeds);

}
