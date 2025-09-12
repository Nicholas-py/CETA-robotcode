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

bool forward = false;
bool backward = false;
bool left = false;
bool right = false;

struct wheelSpeeds Drive() { 
  speed = 1;
  
  if (left)
  {
    struct wheelSpeeds newMotorSpeeds = {-speed, speed};
    return newMotorSpeeds;
  }
  if (right)
  {
    struct wheelSpeeds newMotorSpeeds = {speed, -speed};
    return newMotorSpeeds;
  }
  if (forward)
  {
  Serial.println("drive");
    struct wheelSpeeds newMotorSpeeds = {speed, speed};
    return newMotorSpeeds;
  }

  if (backward)
  {
    struct wheelSpeeds newMotorSpeeds = {-speed, -speed};
    return newMotorSpeeds;
  }

    struct wheelSpeeds newMotorSpeeds = {0, 0};
    return newMotorSpeeds;
}

void SetMovement(String inp)
{
  Serial.println(inp);
  if (inp == "PF")
    forward = true;
  if (inp == "PB")
    backward = true;
  if (inp == "PL")
    left = true;
  if (inp == "PR")
    right = true;

  if (inp == "RF")
    forward = false;
  if (inp == "RB")
    backward = false;
  if (inp == "RL")
    left = false;
  if (inp == "RR")
    right = false;
}


void SetCarnavalSpeed(float in)
{
  carnavalSpeed = in / 15;
}