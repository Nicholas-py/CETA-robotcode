float iteration = 0;

struct wheelSpeeds RevUp() { 
  struct wheelSpeeds newMotorSpeeds = {0, 0};
  iteration++;
  SetWheelServoSpeed({iteration/100, iteration/100});
  delay(20);
  return newMotorSpeeds;
  }