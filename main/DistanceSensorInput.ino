//Include Files
#include <HCSR04.h>

//Digital I/O Pin Function Assignments
#define HCSR04_TRIGGER_PIN 17   // DIGITAL OUTPUT - connected to HCSR04 Trigger pin
#define HCSR04_ECHO_PIN 16      // DIGITAL INPUT - connected to HCSR04 Echo pin

//Collision sensor sampling interval variables
unsigned long collisionDistanceCurrentSampleTime;  // Used for controlling collision sensor sample rate
unsigned long collisionDistancePreviousSampleTime = 0;
const long collisionDistanceSampleInterval = 10; //Will get a reading every 10 ms
float collisionDetectThreshold = 12; //Threshold is 10 cm
float collisionDistance;

//Instantiate an UltrasonicDistanceSensor object
const byte triggerPin = HCSR04_TRIGGER_PIN;
const byte echoPin = HCSR04_ECHO_PIN;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

//Get the reading at the specified intervals
bool GetUltrasonicInput() {
 
  //Update collision distance measurement at a defined interval
  collisionDistance = distanceSensor.measureDistanceCm();
  Serial.print("Ultrasonic Sensor Distance: ");
  Serial.println(collisionDistance);
   
  if (collisionDistance <= collisionDetectThreshold && collisionDistance > 0) {
      return true; //Executes turnaround if there is an obstacle within the threshold
  }
  else {
      return false;
  }

}