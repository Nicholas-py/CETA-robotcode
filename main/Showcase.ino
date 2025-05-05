int curtime = 0;

void tdelay(int x) {
  curtime += x;
  delay(x);
}
void w(struct wheelSpeeds inp) {
  SetWheelServoSpeed(inp);
}
void Showcase() {
  w({0.6,0.6});
  tdelay(5400);
  w({0.5,0.8});
  delay(1500);
  w({0,0.8});
  delay(1000);
  //Heart point turnaround
  w({0.8,-0.5});
  delay(500);
  w({0.8,0.8});
  delay(500);
  w({0.5,0.8});
  delay(1000);
  w({0,0.8});
  delay(1500);
  w({0.6,0.6});
  delay(5000);
  




  w({0,0});
  delay(1000000);
}