#define CalButton 15
#define leftpin SA1
#define centerpin SA0
#define rightpin SA2

struct rawsensorreadings {
  int left;
  int center;
  int right;
};


struct rawsensorreadings WhiteCalibrationValues = {450, 450, 500};
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
void PrintReadings2(struct sensorreadings thingy) {
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
  output.left =   1.0*(sensorval.left  -  WhiteCalibrationValues.left)   /  (BlackCalibrationValues.left  -  WhiteCalibrationValues.left);
  output.center = 1.0*(sensorval.center - WhiteCalibrationValues.center) / (BlackCalibrationValues.center - WhiteCalibrationValues.center);
  output.right =  1.0*(sensorval.right -  WhiteCalibrationValues.right)  / (BlackCalibrationValues.right -  WhiteCalibrationValues.right);
  return output;
}


struct rawsensorreadings GetCalibrationValues() {
  //float CalibrationButton = digitalRead(CalButton);
  struct rawsensorreadings output = GetRawInput();
  output = GetRawInput();


  //while (CalibrationButton == 0) {
  //  CalibrationButton = digitalRead(CalButton);
  //}
  return output;
}

void Test123()
{
    while (true)
  {
    Serial.println("Test123");
  }
}

//Changes the calabration color values
void Calibrate() 
{
  pinMode(14, OUTPUT);
  struct rawsensorreadings inputs = GetRawInput();
  float CallibrationButton = digitalRead(CalButton);
  int callibrationState = 0; //which color the colour sensors will calabrate next
  
  while (callibrationState < 2)
  {
    float CallibrationButton = digitalRead(CalButton);
    Serial.print("Calibrate White: ");
    Serial.println(callibrationState);

    //Calabrates the white color when the button is pressed and it has not calabrated yet
    if (CallibrationButton == 0 && callibrationState == 0){
      WhiteCalibrationValues = GetCalibrationValues();

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
      BlackCalibrationValues = GetCalibrationValues();

      //Blinks the red LED
      digitalWrite(14, HIGH);  
      delay(1000);
      digitalWrite(14, LOW);

      callibrationState = 2;
      continue;

    }
      //Serial.print("White");
      //Serial.println(WhiteCalibrationValues.left);
      //Serial.println(WhiteCalibrationValues.center);
      //Serial.println(WhiteCalibrationValues.right);
      //Serial.print("Black");
      //Serial.println(BlackCalibrationValues.left);
      //Serial.println(BlackCalibrationValues.center);
      //Serial.println(BlackCalibrationValues.right);

  }
    PrintReadings(WhiteCalibrationValues);
    PrintReadings(BlackCalibrationValues);
    delay(1000);
}


