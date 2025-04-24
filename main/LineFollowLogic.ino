int turnAroundCount = 0;

void PickTurnAround(struct motorspeeds code) {
  if (code.left == SLOW_TURNAROUND.left) {
    SlowTurnAround();
  }
  else if (code.left == FAST_TURNAROUND.left) {
    FastTurnAround();
  }
}


void OnLineFollowing() {
  struct lightSensorReadings inputs = GetCalibratedSensorInputs();
  bool collisionBool = GetUltrasonicInput();
  struct motorspeeds newMotorSpeeds = MovementLogic(inputs, collisionBool);

  if (newMotorSpeeds.right == turnaroundcode){
    if (turnAroundCount < 3 || !_StopAfterFourTurns){
      changeState(TURNING);
      PickTurnAround(newMotorSpeeds);
      turnAroundCount++;}
   
    else {
      state = STOPPED;
      SetMotors({0,0});
    }
  }
  SetMotors(newMotorSpeeds);

}
