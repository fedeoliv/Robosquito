#include <Time.h>
#include <TimeAlarms.h>

void setup()
{
  Serial.begin(9600);
  setTime(11, 19, 0, 3, 13, 16);                  // 11:19:00 Março 13 2016
  
  Alarm.alarmRepeat(11, 20, 0, StartMovement);    // Movimentacao do robo comecando as 11:20 todo dia
  Alarm.alarmRepeat(11, 21, 0, StartStandby);     // Robo ficando em standby a partir das 11:21 todo dia
  //Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day
  //Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday 

  //Alarm.timerRepeat(15, Repeats);            // timer for every 15 seconds    
  //Alarm.timerOnce(10, OnceOnly);             // called once after 10 seconds 
}

void  loop(){  
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display
}

void StartMovement(){
  Serial.println("Inicio de movimentacao do robo");    
}

void StartStandby(){
  Serial.println("Robo em standby - Apenas recebendo energia solar");           
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
