float iteration = 0;

struct wheelSpeeds RevUp() { 
  struct wheelSpeeds newMotorSpeeds = {0, 0};
  iteration++;
  SetWheelServoSpeed({iteration/100, iteration/100});
  delay(20);
  return newMotorSpeeds;
  }

float carnavalSpeed = 1;

struct wheelSpeeds Carnaval() { 
  struct wheelSpeeds newMotorSpeeds = {carnavalSpeed, carnavalSpeed};
  return newMotorSpeeds;
  }

void SetCarnavalSpeed(float in)
{
  carnavalSpeed = in / 15;
}