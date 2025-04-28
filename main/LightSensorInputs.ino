#define CalButton 15
#define leftSensor A1
#define centerSensor A0
#define rightSensor A2

struct unadjustedLightSensorReadings {
  int left;
  int center;
  int right;
};


struct unadjustedLightSensorReadings WhiteCalibrationValues = {594, 520, 652};
struct unadjustedLightSensorReadings BlackCalibrationValues = {950, 943, 961};


struct lightSensorReadings GetCalibratedSensorInputs() {
  struct unadjustedLightSensorReadings sensorinputs = GetRawSensorInput();
  struct lightSensorReadings output = MapSensorReadings(sensorinputs);
  PrintReadings2(output);
  return output;
}


struct unadjustedLightSensorReadings GetRawSensorInput() {
  struct unadjustedLightSensorReadings sensorinputs = {analogRead(leftSensor), analogRead(centerSensor), analogRead(rightSensor)};
  return sensorinputs;
}


void PrintReadings(struct unadjustedLightSensorReadings thingy) {
  Serial.print("Light Sensor Readings (1): ");
  Serial.print("(");
  Serial.print(thingy.left);
  Serial.print(", ");
  Serial.print(thingy.center);
  Serial.print(", ");
  Serial.print(thingy.right);
  Serial.println(")");
}
void PrintReadings2(struct lightSensorReadings thingy) {
  Serial.print("Light Sensor Readings (2): ");
  Serial.print("(");
  Serial.print(thingy.left);
  Serial.print(", ");
  Serial.print(thingy.center);
  Serial.print(", ");
  Serial.print(thingy.right);
  Serial.println(")");
}



struct lightSensorReadings MapSensorReadings(struct unadjustedLightSensorReadings sensorValue) {
  struct lightSensorReadings output = {0,0,0};
  
  output.left =   1.0*(sensorValue.left  -  WhiteCalibrationValues.left)   /  (BlackCalibrationValues.left  -  WhiteCalibrationValues.left);
  output.left =   max(output.left, 0);
  output.left =   min(output.left, 1);
  
  output.center = 1.0*(sensorValue.center - WhiteCalibrationValues.center) / (BlackCalibrationValues.center - WhiteCalibrationValues.center);
  output.center = max(output.center, 0);
  output.center = min(output.center, 1);
  
  output.right =  1.0*(sensorValue.right -  WhiteCalibrationValues.right)  / (BlackCalibrationValues.right -  WhiteCalibrationValues.right);
  output.right =  max(output.right, 0);
  output.right =  min(output.right, 1);
  return output;
}

//Changes the Calibrattion color values
bool CalibrateLightSensors() 
{
  pinMode(14, OUTPUT);
  struct unadjustedLightSensorReadings inputs = GetRawSensorInput();
  float CalibrationButton = digitalRead(CalButton);
  int CalibrationState = 0; //which color the colour sensors will Calibratte next
  int adjustmentValue = 50;

  
  while (CalibrationState < 3)
  {
    float CalibrationButton = digitalRead(CalButton);
    //Serial.print("Calibrate White: ");
    //Serial.println(CalibrationState);

    //Calibrattes the white color when the button is pressed and it has not Calibrated yet
    if (CalibrationButton == 0 && CalibrationState == 0){
      WhiteCalibrationValues = GetRawSensorInput();
      

      //Blinks the red LED
      digitalWrite(14, HIGH);  
      delay(1000);
      digitalWrite(14, LOW);

      CalibrationState = 1;
      continue;
    }

    //Calibrates black when the button is pressed and after it has Calibrated white
    if (CalibrationButton == 0 && CalibrationState == 1)
    {
      BlackCalibrationValues = GetRawSensorInput();

      //Blinks the red LED
      digitalWrite(14, HIGH);  
      delay(1000);
      digitalWrite(14, LOW);

      CalibrationState = 2;
      continue;

    }

    //starts the robot when the button is pressed and both have been calabrated
    if (CalibrationButton == 0 && CalibrationState == 3)
    {
      CalibrationState = 3;
      continue;
    }

  }
  PrintReadings(WhiteCalibrationValues);
  PrintReadings(BlackCalibrationValues);
  delay(1000);
  return true;
}


//Most important function - Do not remove
void blink() {
  pinMode(14, OUTPUT);
  while (true) {
    digitalWrite(14, HIGH);  
    delay(500);
    digitalWrite(14, LOW);
    delay(500);   }                    
}


