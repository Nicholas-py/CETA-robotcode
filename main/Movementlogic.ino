const float defaultspeed = 1;
const float modifyspeed = 0.3;
const float straighteningspeed = 100;

float heading = 0;  //Measures drift
int headingsign = 0;
const float headingchange = 0.1f;

float whiteoutthreshold = 1.2;

struct motorspeeds MovementLogic(struct lightSensorReadings inputs) {

  Serial.print("Heading: ");
  Serial.println(heading);

  if (inputs.center + inputs.right + inputs.left < whiteoutthreshold && max(max(inputs.right, inputs.left), inputs.center) - min(min(inputs.right, inputs.left), inputs.center) < 0.3) {
    heading = 0;
    return OnWhiteout(heading);
  } 
  else if (  inputs.center > inputs.right + inputs.left || abs(inputs.right-inputs.left) < 0.2 && inputs.center > 0.2) {
    heading = OnPathStraight(heading);
  } 
  else if (inputs.right == inputs.left) {
    heading = OnPathStraight(heading);
  } 
  else {
    heading = OnDrifting(heading, inputs.right < inputs.left, inputs.center < 0.5);
  }
  
  headingsign = GetDirection(heading);

  struct motorspeeds toreturn = { defaultspeed + modifyspeed * heading, defaultspeed - modifyspeed * heading };
  return toreturn;
}

int GetDirection(float heading) {
  if (heading != 0) {
    return heading / abs(heading);
  } else {
    return 0;
  }
}

float aaaspeed = 0.7;
struct motorspeeds OnWhiteout(float heading) {
  Serial.println("WHITEOUT");
  if (headingsign < 0) {
    struct motorspeeds uhoh = {defaultspeed - aaaspeed,defaultspeed +aaaspeed};
    return uhoh;
  } else {
    struct motorspeeds uhoh = {defaultspeed + aaaspeed,defaultspeed -aaaspeed};
    return uhoh;
  }
}

float OnPathStraight(float heading) {
  Serial.println("Straight");
  int direction = GetDirection(heading);
  if (abs(straighteningspeed*headingchange) < abs(heading)){
    return heading - direction * straighteningspeed * headingchange;}
  else {
    return 0;
  }
}

float OnDrifting(float heading, bool toleft, bool strong) {
  Serial.println("Drifting");
  int direction = 2*int(toleft)-1;
  if (heading != 0 && int(heading/abs(heading)) == direction ) {
    return -direction * 0.01;
  } 
  float multiplier = direction * (int(strong) + 1);
  float change = multiplier * headingchange;
  return heading - change;
}