const int defaultspeed = 0.5;
const int modifyspeed = 0.2;

float heading;

struct motorspeeds MovementLogic(float lsensor, float midsensor, float rsensor) {
  int casenumber = int(lsensor > 0.5)*4+int(midsensor >0.5)*2 + int(rsensor > 0.5);
  struct motorspeeds toreturn = {0,0};
  switch (casenumber) {
      case 0: //White White White
        toreturn = {1,1};
      case 1: //White White Black
        toreturn = {defaultspeed+modifyspeed, defaultspeed-modifyspeed};
      case 2: //White Black White
        toreturn = {defaultspeed, defaultspeed};
  }
  return toreturn;
}