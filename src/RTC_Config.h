#include "RTClib.h"

//Create a object for module RTC 
RTC_DS3231 rtc;


void RctVerify () {
    if(! rtc.begin()){
        Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
    }
    
  }

//Adjust Time for RTC module
void RTCAdjst_Auto(){
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void RTCAdjst(int Year,int Mounth,int Day,int Hour,int Minute,int Second){
    rtc.adjust(DateTime(Year, Mounth, Day, Hour, Minute, Second));
}

