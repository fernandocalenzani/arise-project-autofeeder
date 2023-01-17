//==| TIMER |================================================================//
void adjusttime_t(void){
  if((WiFi.status() == WL_CONNECTED)&&(testConnection() == true)){
    configTime(__mysettings.GMT*3600, __mysettings.GMT*3600, "pool.ntp.org");
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
    }else{
      DS1307_RTC.adjust(DateTime(timeinfo.tm_year+1900, timeinfo.tm_mon+1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, 30));
    }
  }
};


time_t tmEpochConvert_t(int YYYY, int MM, int DD, int hh, int mm, int ss){
  struct tm dateTime;
  dateTime.tm_year = YYYY - 1900;
  dateTime.tm_mon  = MM - 1;
  dateTime.tm_mday = DD;
  dateTime.tm_hour = hh;
  dateTime.tm_min  = mm;
  dateTime.tm_sec  = ss;

  return mktime(&dateTime);
}
