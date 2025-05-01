int duration = 2001;

float lwheel(int time) {
  return 0;
}

float rwheel(int time) {
  return 1/(duration - time);
}

void Showcase() {
  int time = 0;
    while (time < duration) {
      time += 50;
      struct wheelSpeeds speds = {lwheel(time), rwheel(time)};
      SetWheelServoSpeed(speds);
      delay(50);
    }
    time = 0;
    while (time > -duration) {
      time -= 50
      struct wheelSpeeds speds = {0.5 - lwheel(duration + time),0.5 - rwheel(duration + time)};
      SetWheelServoSpeed(speds);
      delay(50);
    }
}