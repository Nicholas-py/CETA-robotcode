const float defaultspeed = 1.6;
const float turnspeed = 0.16;
const float straighteningspeed = 100;

float heading = 0;  
const float headingchange = 0.16f;

float whitethreshold = 0.3;
float whiteoutspeed = 2.2; //AAAspeed

int blackseeingquantity = 0;
int blackquantitythreshold = 15;
float blackthreshold = 0.6;

int panickingquantity = 0;
int panickingthreshold = 15;

struct wheelSpeeds AgreasiveLineFollowing(struct lightSensorReadings inputs) {

  if (ShouldTurnAround(inputs)) {
    return SLOW_TURNAROUND;
  }

  else if (SensorsDetectAllWhite(inputs)) {
    return OnWhiteout(heading); 
  } 
  else if (Panicking()) {
    heading = 0;
    panickingquantity = 0;
    return {0,0};
  }

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
    if (blackseeingquantity > blackquantitythreshold) {
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
    struct wheelSpeeds uhoh = {defaultspeed - whiteoutspeed, defaultspeed +whiteoutspeed};
    return uhoh;
  } else {
    struct wheelSpeeds uhoh = {defaultspeed + whiteoutspeed, defaultspeed -whiteoutspeed};
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