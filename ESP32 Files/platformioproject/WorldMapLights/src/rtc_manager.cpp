#include "rtc_manager.h"
#include <Wire.h>
#include <RTClib.h>
#include <WiFi.h>

RTC_DS3231 rtc;
bool rtcAvailable=false;

bool setupRTC(){
  Wire.begin();
  rtcAvailable=rtc.begin();
  if(rtcAvailable && rtc.lostPower()) rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  return rtcAvailable;
}

bool getLocalTime(struct tm *info){
  if(rtcAvailable){
    DateTime now = rtc.now();
    info->tm_hour=now.hour();
    info->tm_min=now.minute();
    info->tm_sec=now.second();
    info->tm_mday=now.day();
    info->tm_mon=now.month()-1;
    info->tm_year=now.year()-1900;
    return true;
  }else if(WiFi.status()==WL_CONNECTED){
    time_t t; if(!getLocalTime(&t,1000)) return false;
    struct tm *lt = localtime(&t);
    *info=*lt; return true;
  }
  return false;
}
