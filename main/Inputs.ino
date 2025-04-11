#define CalButton 15
#define leftSensor SA1
#define centerSensor SA0
#define rightSensor SA2

struct unadjustedLightSensorReadings {
  int left;
  int center;
  int right;
};


struct unadjustedLightSensorReadings WhiteCalibrationValues = {450, 450, 500};
struct unadjustedLightSensorReadings BlackCalibrationValues = {950, 950, 950};


struct lightSensorReadings GetCalabratedSensorInputs() {
  struct unadjustedLightSensorReadings sensorinputs = GetRawSensorInput();
  struct lightSensorReadings output = MapSensorReadings(sensorinputs);
  return output;
}


struct unadjustedLightSensorReadings GetRawSensorInput() {
  struct unadjustedLightSensorReadings sensorinputs = {analogRead(leftSensor), analogRead(centerSensor), analogRead(rightSensor)};
  return sensorinputs;
}


void PrintReadings(struct unadjustedLightSensorReadings thingy) {
  Serial.print("(");
  Serial.print(thingy.left);
  Serial.print(", ");
  Serial.print(thingy.center);
  Serial.print(", ");
  Serial.print(thingy.right);
  Serial.println(")");
}
void PrintReadings2(struct lightSensorReadings thingy) {
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

//Changes the calabration color values
bool CalibrateLightSensors() 
{
  pinMode(14, OUTPUT);
  struct unadjustedLightSensorReadings inputs = GetRawSensorInput();
  float CallibrationButton = digitalRead(CalButton);
  int callibrationState = 0; //which color the colour sensors will calabrate next
  int adjustmentValue = 50;

  
  while (callibrationState < 2)
  {
    float CallibrationButton = digitalRead(CalButton);
    Serial.print("Calibrate White: ");
    Serial.println(callibrationState);

    //Calabrates the white color when the button is pressed and it has not calabrated yet
    if (CallibrationButton == 0 && callibrationState == 0){
      WhiteCalibrationValues = GetRawSensorInput();

      //Blinks the red LED
      digitalWrite(14, HIGH);  
      delay(1000);
      digitalWrite(14, LOW);

      callibrationState = 1;
      continue;
    }

    //Calabrates black when the button is pressed and after it has calabrated white
    if (CallibrationButton == 0 && callibrationState == 1)
    {
      BlackCalibrationValues = GetRawSensorInput();

      //Blinks the red LED
      digitalWrite(14, HIGH);  
      delay(1000);
      digitalWrite(14, LOW);

      callibrationState = 2;
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


