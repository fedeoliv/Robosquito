#include <TimeAlarms.h>                         // Library for managing time of robot operation

// ===== TIME ========================
const static int MIN_HOUR_LIMIT = 11;           // Minimum hour limit for robot movements
const static int MIN_MINUTE_LIMIT = 20;         // Minimum minute limit for robot movements
const static int MIN_SECOND_LIMIT = 0;          // Minimum second limit for robot movements

const static int MAX_HOUR_LIMIT = 11;           // Maximum hour limit for robot movements
const static int MAX_MINUTE_LIMIT = 21;         // Maximum minute limit for robot movements
const static int MAX_SECOND_LIMIT = 0;          // Maximum second limit for robot movements

const static float minHour = MIN_HOUR_LIMIT + (MIN_MINUTE_LIMIT / 60.0) + (MIN_SECOND_LIMIT / 3600.0);
const static float maxHour = MAX_HOUR_LIMIT + (MAX_MINUTE_LIMIT / 60.0) + (MAX_SECOND_LIMIT / 3600.0);

// ===== DISTANCE SENSORS =============
const static int IR_SENSOR_UP = 0;              // Distance sensor in the front of the robot (A0)
const static int IR_SENSOR_DOWN = 1;            // Distance sensor on the back of the robot
const static int IR_SENSOR_RIGHT = 2;           // Distance sensor on the right of the robot
const static int IR_SENSOR_LEFT = 3;            // Distance sensor on the left of the robot

const static int WATER_SENSOR = 4;              // Water fluid sensor

void setup()
{
  Serial.begin(9600);
  setDefaultDatetime();

  pinMode(IR_SENSOR_UP, INPUT);
  pinMode(IR_SENSOR_DOWN, INPUT);
  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  
  // Robot movements starting every day at minimum time specified
  Alarm.alarmRepeat(MIN_HOUR_LIMIT, MIN_MINUTE_LIMIT, MIN_SECOND_LIMIT, startMovement);

  // Robot in standby after the maximum time specified
  Alarm.alarmRepeat(MAX_HOUR_LIMIT, MAX_MINUTE_LIMIT, MAX_SECOND_LIMIT + 1, startStandby);
 
  //Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day
  //Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday 

  //Alarm.timerRepeat(15, Repeats);            // timer for every 15 seconds    
  //Alarm.timerOnce(10, OnceOnly);             // called once after 10 seconds 
}

void  loop(){  
  digitalClockDisplay();
  Alarm.delay(1000);                              // Waiting one second between clock display
}

// setDefaultDatetime(): Specifies default datetime while uploading
// TODO: Get datetime from computer
void setDefaultDatetime() {
  setTime(11, 19, 0, 3, 13, 16);                  // 11:19:00am March 13 2016
}

void startMovement(){
  while(isMovementPeriod()) {
    Serial.println("MOVING");
    
    float upDistance = getDistance(IR_SENSOR_UP);
    Serial.print("Up distance: ");
    Serial.print(upDistance);
    Serial.println(" cm");

    float downDistance = getDistance(IR_SENSOR_DOWN);
    Serial.print("Down distance: ");
    Serial.print(downDistance);
    Serial.println(" cm");

    float rightDistance = getDistance(IR_SENSOR_RIGHT);
    Serial.print("Right distance: ");
    Serial.print(rightDistance);
    Serial.println(" cm");

    float leftDistance = getDistance(IR_SENSOR_LEFT);
    Serial.print("Left distance: ");
    Serial.print(leftDistance);
    Serial.println(" cm");
    
    delay(1000);
  }
}

// getDistance(sensor): Returns the distance in cm from IR sensor
// Distance theory: http://luckylarry.co.uk/arduino-projects/arduino-using-a-sharp-ir-sensor-for-distance-calculation/
float getDistance(int sensor) {
  float irSensorValue = analogRead(sensor)*0.0048828125;
  return 65*pow(irSensorValue, -1.10);
}

// isMovementPeriod(): Checking if the time range is for robot movement or not
bool isMovementPeriod() {
  float currentHour = hour() + (minute() / 60.0) + (second() / 3600.0);
  return currentHour >= minHour && currentHour <= maxHour;
}

void startStandby(){
  Serial.println("STANDBY - RECEIVING SOLAR ENERGY");
  delay(1000);
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
