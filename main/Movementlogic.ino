const int defaultspeed = 90;
const int modifyspeed = 10;

float heading = 0; //Measures drift
float headingchange = 0.01f;


struct motorspeeds MovementLogic(struct sensorreadings inputs) {
  if (inputs.middle + inputs.right + inputs.left < 0.5) {
    return OnWhiteout(heading);
  }
  else if (inputs.middle > inputs.right + inputs.left) {
      heading =  OnPathStraight(heading);
  }
  else if (inputs.middle > 0.5 && inputs.right > inputs.left && inputs.right > 0.3) {
    heading = OnDrifting(heading, false, false);
  }
  else if (inputs.middle > 0.5 && inputs.right < inputs.left && inputs.left > 0.3) {
    heading = OnDrifting(heading, true, false);
  }
  else if (inputs.middle < 0.5 && inputs.right > inputs.left && inputs.right > 0.3) {
    heading = OnDrifting(heading, false, true);
  }  
  else if (inputs.middle < 0.5 && inputs.right < inputs.left && inputs.left > 0.3) {
    heading = OnDrifting(heading, true, true);
  }




  struct motorspeeds toreturn = {defaultspeed + modifyspeed*heading, defaultspeed - modifyspeed*heading};
  return toreturn;
}

int GetDirection(float heading) {
    if (heading != 0){
      return heading/abs(heading);}
    else {
      return 0;
    }

}

float straighteningspeed = 1;

struct motorspeeds OnWhiteout(float heading) {
  if (heading < 0) {
    struct motorspeeds uhoh = {defaultspeed,0};
    return uhoh;
    }
  else {
    struct motorspeeds uhoh = {0,defaultspeed};
    return uhoh;

  }
}

float OnPathStraight(float heading) {
  int direction = GetDirection(heading);
  return heading - direction * max(straighteningspeed*headingchange, heading);

}

float OnDrifting(float heading, bool toleft, bool strong) {
    float multiplier = (int(toleft)-1) * 2 * (int(strong)+1);
    float change = multiplier * headingchange;
    return heading + change;
}