//==| ALERTS |=================================================================//
void standbyMode(int timeStandby, int fLed){
  int startStandby = millis();
  int time;

  lcdMessage("STANDBY: " + (String)(timeStandby/1000) + "s","",0,0);
  while((millis() - startStandby) < timeStandby){
    int timeAlert = millis();
    while((millis()-timeAlert)< 1000){
      ledColorState(3, 1);
      delay(500/fLed);
      ledColorState(3, 0);
      delay(500/fLed);
      lcd.setCursor(7,1);
      lcd.print((millis()-startStandby)/1000);
    }
  }
  lcdMessage("aguarde...","",0,0);
}


void alert(String data){
  DateTime __timenow = DS1307_RTC.now();

  ledColorState(3, 1);
  lcdMessage("ALERT:", "", 0, 0);
  lcdScrollMsg(data, 200, 1, 16);

  String json = "{";
  json += "\"serialNumberId\":\"" + __xSNx__ + "\",";
  json += "\"alerts\":\"[ALERT ";
  json += String(__timenow.day(), DEC) + "/" + String(__timenow.month(), DEC) + "/" + String(__timenow.year(), DEC) + " | " + String(__timenow.hour(), DEC) + ":"+ String(__timenow.minute(), DEC) + "] ";
  json += data + "\"";
  json += "}";

  __https alerts = http_post(__xSERVER__ALERTSx__, json);
}


int alertOFF(String data){
  DateTime __timenow = DS1307_RTC.now();

  String json = "{";
  json += "\"serialNumberId\":\"" + __xSNx__ + "\",";
  json += "\"alerts\":\"[ALERT ";
  json += String(__timenow.day(), DEC) + "/" + String(__timenow.month(), DEC) + "/" + String(__timenow.year(), DEC) + " | " + String(__timenow.hour(), DEC) + ":"+ String(__timenow.minute(), DEC) + "] ";
  json += data + "\"";
  json += "}";

  int i = 0;
  int status = 500;
  while((status > 400)&&(i < 3)){
    __https alerts = http_post(__xSERVER__ALERTSx__, json);
    status = alerts.status;
    delay(10);
  }
return status;
}


void deepSleepMode(int minutes){
  minutes = minutes*60*1000*1000;
  lcd.backlight();
  lcdMessage("Modo Standby!", "Sair: config", 0, 0);
  ledColorState(3, 1);
  writeConnectionStatus();

  esp_wifi_stop();
  esp_sleep_enable_timer_wakeup(minutes);
  gpio_wakeup_enable(GPIO_NUM_14, GPIO_INTR_HIGH_LEVEL);
  esp_sleep_enable_gpio_wakeup();
  esp_light_sleep_start();
  esp_wifi_start();

  if(wakeup_reason() == "LOCAL"){
    __mysettings.devicestate = "true";
    writedata_nvs("true", slotx06);
    writedata_nvs("n", slotx07);
    loadingbar("Reiniciando...", 0, 15, 200);
    ESP.restart();
  }
}


String wakeup_reason(void){
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason){
    case ESP_SLEEP_WAKEUP_GPIO : return "LOCAL";
    case ESP_SLEEP_WAKEUP_TIMER : return "TIMER";
    default : return "ANY";
  }
}


void putDeviceConfiguration(void){
  __https putSettings = http_put(__xSERVER__CONFIGx__, "{\"devicestate\": true }");
  if((putSettings.status >= 200)&&(putSettings.status < 400)){
    getServerDeviceConfigurations(slotx04, slotx06);
    alertOFF("Dispositivo LIGADO novamente via LOCAL");
    delay(2000);
  }else{
    alertOFF(putSettings.res);
  }
}


void sendAlertsInfo(void){
  if((WiFi.status() == WL_CONNECTED)&&(testConnection() == true)){
    if(strcmp(readdata_nvs(slotx02), "OK") != 0){
      if(alertOFF(readdata_nvs(slotx02)) < 400){;
        writedata_nvs("OK", slotx02);
      }
    }
    if(strcmp(readdata_nvs(slotx03), "OK") != 0){
      if(alertOFF(readdata_nvs(slotx03)) < 400){;
        writedata_nvs("OK", slotx03);
      }
    }
    if(strcmp(readdata_nvs(slotx07), "OK") != 0){
      if(alertOFF(readdata_nvs("Modo Standby desativado localmente.")) < 400){
        putDeviceConfiguration();
        writedata_nvs("OK", slotx07);
      }
    }
  }
}

void criticalDeepSleep(int minutes){
  lcd.backlight();
  for(int i = 0; i < 10; i++){
    ledColorState(1, 1);delay(500);
    ledColorState(1, 0);delay(500);
  }
  ledColorState(1, 1);
  esp_sleep_enable_timer_wakeup(minutes*60*1000*1000);
  esp_deep_sleep_start();
}
