#include <Time.h>
#include <TimeAlarms.h>

const static int MIN_HOUR_LIMIT = 11;           // Minimum hour limit for robot movements
const static int MIN_MINUTE_LIMIT = 20;         // Minimum minute limit for robot movements
const static int MIN_SECOND_LIMIT = 0;          // Minimum second limit for robot movements

const static int MAX_HOUR_LIMIT = 11;           // Maximum hour limit for robot movements
const static int MAX_MINUTE_LIMIT = 21;         // Maximum minute limit for robot movements
const static int MAX_SECOND_LIMIT = 0;          // Maximum second limit for robot movements

const static float minHour = MIN_HOUR_LIMIT + (MIN_MINUTE_LIMIT / 60.0) + (MIN_SECOND_LIMIT / 3600.0);
const static float maxHour = MAX_HOUR_LIMIT + (MAX_MINUTE_LIMIT / 60.0) + (MAX_SECOND_LIMIT / 3600.0);

void setup()
{
  Serial.begin(9600);
  setDefaultDatetime();
  
  // Robot movements starting every day at minimum time specified
  Alarm.alarmRepeat(MIN_HOUR_LIMIT, MIN_MINUTE_LIMIT, MIN_SECOND_LIMIT, StartMovement);

  // Robot in standby after the maximum time specified
  Alarm.alarmRepeat(MAX_HOUR_LIMIT, MAX_MINUTE_LIMIT, MAX_SECOND_LIMIT + 1, StartStandby);
 
  //Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day
  //Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday 

  //Alarm.timerRepeat(15, Repeats);            // timer for every 15 seconds    
  //Alarm.timerOnce(10, OnceOnly);             // called once after 10 seconds 
}

void  loop(){  
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display
}

// setDefaultDatetime(): Specifies default datetime while uploading
// TODO: Get datetime from computer
void setDefaultDatetime() {
  setTime(11, 19, 0, 3, 13, 16);                  // 11:19:00am March 13 2016
}

void StartMovement(){
  while(isMovementPeriod()) {
    Serial.println("Moving");
    delay(1000);
  }
}

// isMovementPeriod(): Checking if the time range is for robot movement or not
bool isMovementPeriod() {
  float currentHour = hour() + (minute() / 60.0) + (second() / 3600.0);
  return currentHour >= minHour && currentHour <= maxHour;
}

void StartStandby(){
  Serial.println("Standby - Receiving solar energy");           
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
