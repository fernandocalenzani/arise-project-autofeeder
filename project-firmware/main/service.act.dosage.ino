//==| DOSAGE |===============================================================//
void startOnlineApplication(int pos, float ktm, float amountProduct){
  lcd.setBacklight(HIGH);
  __massbefore__ = sensor_mass();
  lcdMessage("Applying", "wait...", 0, 0);
  buzzer(1000, 1000, 5);

  if((__xHx__ - sensor_hcsr04()/10) > 0){
    motorStart(amountProduct, ktm, 1);
    alert("Produto aplicado: " + String(amountProduct) + " gramas. Dispositivo aguardando por " + (String)(120000/(60*1000)) + " minutos.");
  }else{
    alert("Produto NAO aplicado. Tanque vazio! Dispositivo aguardando por " + (String)(120000/(60*1000)) + " minutos.");
  }
  cleanMeasurements();
  getMeasurements();
  sendMeasurements();
  standbyMode(120000, 1);
}


void startOfflineApplication(int pos, float ktm, float amountProduct){
  lcd.setBacklight(HIGH);
  lcdMessage("Applying", "wait...", 0, 0);
  buzzer(1000, 1000, 5);
  cleanMeasurements();
  getMeasurements();

  if((__xHx__ - sensor_hcsr04()/10) > 0){
    motorStart(amountProduct, ktm, 1);
    const char* msg_slotx03 = ("[ALERT OFFLINE]. Dosagem feita: " + (String)__mysettings.day[pos] + "-" + (String)__mysettings.hour[pos] + "| Quantidade: " + (String)__measurements.Mflow[__nmeasurement__]).c_str();
    writedata_nvs(msg_slotx03, slotx03);
  }else{
    const char* msg_slotx03 = ("[ALERT OFFLINE]. Sem produto no tanque. Dosagem NÃO executada: " + (String)__mysettings.day[pos] + "-" + (String)__mysettings.hour[pos] + "| Quantidade: " + (String)__measurements.Mflow[__nmeasurement__]).c_str();
    writedata_nvs(msg_slotx03, slotx03);
  }
  standbyMode(120000, 1);
}

bool verifyNextDosages(void){
  DateTime __timenow = DS1307_RTC.now();
  bool res = false;
  int i =0;
  time_t timeEpochDosage;
  time_t timeEpochNow = tmEpochConvert_t(__timenow.year(), __timenow.month(), __timenow.day(), __timenow.hour() + __mysettings.GMT, __timenow.minute(), 0);

  while((i<100)){
    if((String(__weekdays__[__timenow.dayOfTheWeek()]) == __mysettings.day[i])||(String(__timenow.day()) == __mysettings.day[i])){
      timeEpochDosage = tmEpochConvert_t(__timenow.year(), __timenow.month(), __timenow.day(), __mysettings.hour[i] + __mysettings.GMT, __mysettings.min[i], 0);
      if(timeEpochNow >= timeEpochDosage - 2*60){
        res = true;
      }
    }
    i++;
    if((__mysettings.day[i]==NULL)||(__mysettings.hour[i]==NULL)){i = 101;}
  }

return res;
}
