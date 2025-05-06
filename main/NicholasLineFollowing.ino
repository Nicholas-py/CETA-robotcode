const float defaultspeed = 2; //W - 2
const float turnspeed = 0.2;
const float straighteningspeed = 100;

float heading = 0;  
const float headingchange = 0.08f;  //W - 0.08

float whitethreshold = 0.5;
float whiteoutspeed1 = 2; //AAAspeed /W- 4
float whiteoutspeed2 = -0.5; //AAAspeed /W - 0



int blackseeingquantity = 0;
const int blackquantitythreshold = 9;
const float blackthreshold = 0.6;

int blackwhitequantity = 0;
const int lineskipthreshold = 10;

int panickingquantity = 0;
const int panickingthreshold = 15;

struct wheelSpeeds NicholasLineFollowing(struct lightSensorReadings inputs) {

  if (ShouldTurnAround(inputs)) {
    return SLOW_TURNAROUND;
  }

  else if (SensorsDetectAllWhite(inputs)) {
    return OnWhiteout(heading); 
  } 
  else if (Panicking()) {
    blackwhitequantity++;
    if (blackwhitequantity >= lineskipthreshold) {
      blackwhitequantity = 0;
      heading = 0;
      panickingquantity = 0;
  }
        return {-OnWhiteout(heading).left,-OnWhiteout(heading).right};}


  else if (SensorsDetectStraight(inputs)) {
    heading = OnPathStraight(heading);
  } 
  else if (inputs.right == inputs.left) {
    heading = OnPathStraight(heading);
  } 
  else {
    heading = OnDrifting(heading, inputs.right < inputs.left, inputs.center < 0.5);
  }
  
  struct wheelSpeeds toreturn = { defaultspeed + turnspeed * heading, defaultspeed - turnspeed * heading };
  Serial.println(toreturn.left);
  return toreturn;
}



int sgn(float heading) {
  if (heading != 0) {
    return int(heading / abs(heading));
  } else {
    return 0;
  }
}

bool ShouldTurnAround(struct lightSensorReadings inputs) {
  float minimum = min(min(inputs.center,inputs.left),inputs.right);

  if (minimum > blackthreshold) {
    blackseeingquantity++;
    if (blackseeingquantity >= blackquantitythreshold) {
      return true;
    }
  }
  else {
    blackseeingquantity = 0;
  }
  return false;
}

bool SensorsDetectAllWhite(struct lightSensorReadings inputs) {
  float maximum = max(max(inputs.center,inputs.left),inputs.right);
  return maximum < whitethreshold;

}

bool SensorsDetectStraight(struct lightSensorReadings inputs) {
  if (inputs.center > inputs.right+inputs.left) {
    return true;
  }
  if (inputs.right - inputs.left < 0.2 && inputs.center > whitethreshold){
    return true;
  }
  return false;
}

bool Panicking() {
  return (panickingquantity > panickingthreshold);
}


struct wheelSpeeds OnWhiteout(float heading) {
  Serial.println("Robot is fully on white");
  panickingquantity += 1;
  
  if (heading < 0) {
    struct wheelSpeeds uhoh = {whiteoutspeed2, whiteoutspeed1};
    return uhoh;
  } else {
    struct wheelSpeeds uhoh = {whiteoutspeed1, whiteoutspeed2};
    return uhoh;
  }
}


float OnPathStraight(float heading) {
  Serial.println("Heading: streight");
  int direction = sgn(heading);

  if (abs(straighteningspeed) < abs(heading)){
    return heading - direction * straighteningspeed;}
  else {
    return 0;
  }
}

float OnDrifting(float heading, bool toleft, bool strong) {
  Serial.println("Heading: Drifting");
  int direction = 2*int(toleft)-1;
  if (sgn(heading) == direction ) {
    return -direction * 0.01;
  } 
  float multiplier = direction * (int(strong) + 1);
  float change = multiplier * headingchange;
  return heading - change;
}