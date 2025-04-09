#define CalButton 1
#define leftpin SA1
#define centerpin SA0
#define rightpin SA2

struct rawsensorreadings {
  int left;
  int center;
  int right;
};


struct rawsensorreadings WhiteCalibrationValues = {450, 450, 550};
struct rawsensorreadings BlackCalibrationValues = {950, 950, 950};


struct sensorreadings GetInput() {
  struct rawsensorreadings sensorinputs = GetRawInput();
  struct sensorreadings output = MapSensorTo01(sensorinputs);
  return output;
}


struct rawsensorreadings GetRawInput() {
  struct rawsensorreadings sensorinputs = {analogRead(leftpin), analogRead(centerpin), analogRead(rightpin)};
  return sensorinputs;
}


void PrintReadings(struct rawsensorreadings thingy) {
  Serial.print("(");
  Serial.print(thingy.left);
  Serial.print(", ");
  Serial.print(thingy.center);
  Serial.print(", ");
  Serial.print(thingy.right);
  Serial.println(")");
}


struct sensorreadings MapSensorTo01(struct rawsensorreadings sensorval) {
  struct sensorreadings output = {0,0,0};
  output.left =  1.0*(sensorval.left  -  WhiteCalibrationValues.left)   /  (BlackCalibrationValues.left  -  WhiteCalibrationValues.left);
  output.center =1.0*(sensorval.center - WhiteCalibrationValues.center) / (BlackCalibrationValues.center - WhiteCalibrationValues.center);
  output.right = 1.0*(sensorval.right -  WhiteCalibrationValues.right)  / (BlackCalibrationValues.right -  WhiteCalibrationValues.right);
  return output;
}


struct rawsensorreadings GetCalibrationValues() {
  float CalibrationButton = digitalRead(CalButton);
  struct rawsensorreadings output = GetRawInput();

  while (CalibrationButton == 0) {
    CalibrationButton = digitalRead(CalButton);
    output = GetRawInput();
  }
  return output;
}


void Calibrate() {
  struct rawsensorreadings inputs = GetRawInput();
  float CallibrationButton = digitalRead(CalButton);
  int callibrationState = 0;
  while (callibrationState < 3)
  {
    CallibrationButton = digitalRead(CalButton);
    Serial.println(CalButton);

    if (CallibrationButton == 0 && callibrationState == 0){
      WhiteCalibrationValues = GetCalibrationValues();
      callibrationState = 1;
    }
  }

  if (CallibrationButton == 0 && hasCalibratedWhite == false){

    WhiteCalibrationValues = GetCalibrationValues();
    hasCalibratedWhite = true;
  }
  
  if (CallibrationButton == 0 && hasCalibratedWhite == true){

    BlackCalibrationValues = GetCalibrationValues();
    hasCalibratedWhite = false;

    }
    PrintReadings(WhiteCalibrationValues);
    PrintReadings(BlackCalibrationValues);

}


