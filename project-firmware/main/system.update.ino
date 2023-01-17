//==| SYSTEM UPDATE |========================================================//
bool getUpdateFirmware(void){
  bool res = false;
  DateTime __timenow = DS1307_RTC.now();
  __https getUpdate = http_get(__xSERVER__ONEUPDATEx__);
  setUpdateDate(getUpdate.res);

  if((__updateverify.newversion != "")||(__updateverify.newversion != NULL)){
    if((__xVERSIONFIRMWAREx__ != __updateverify.newversion)&&(__xVERSIONFIRMWAREx__ == __updateverify.currentversion)){
        if((__timenow.year() >= __updateverify.year)&&(__timenow.month() >= __updateverify.mon)&&(__timenow.day() >= __updateverify.day)&&(__timenow.hour() >= __updateverify.hour)&&(__timenow.minute() >= __updateverify.min)){
          res = false;
          lcd.setBacklight(HIGH);
          firmwareUpdater(__updateverify.keyOTA, __updateverify.currentversion, __updateverify.newversion);
        }else if((__timenow.year() <= __updateverify.year)&&(__timenow.month() <= __updateverify.mon)&&(__timenow.day() <= __updateverify.day)&&(__timenow.hour() <= __updateverify.hour)&&(__timenow.minute() < __updateverify.min)){
          res = false;
        }else{
          res = true;
        }
    }else{
      res = false;
    }
  }
return res;
}


void OnProgress(int progress, int total){
  static int last_percent = 0;
  int percent = (100 * progress) / total;
  if (percent != last_percent){
    for (uint8_t i = 0; i < percent; i+=6)
    lcd.setCursor(7, 1);
    lcd.print((String)percent + "%");
    last_percent = percent;
  }
}


void firmwareUpdater(String KeyDrive, String currentVersion, String newVersion){
  if(WiFi.RSSI() > -85){
    __adviceUpdateFirmware__ = false;
    lcdScrollMsg("Nova atualizacao. NAO DESLIGUE O DISPOSITIVO", 200, 1, 16);
    loadingbar("Iniciando...", 0, 15, 210);
    ledColorState(3, 1);
    OTADRIVE.setInfo(KeyDrive, currentVersion);
    OTADRIVE.onUpdateFirmwareProgress(OnProgress);
    auto inf = OTADRIVE.updateFirmwareInfo();
    if (inf.available){
      lcdMessage("new v." + newVersion, "",0,0);
      OTADRIVE.updateFirmware(false);
      lcdMessage("update completed", "",0,0);
      lcd.write(7);
      delay(2000);
      alert("Device updated to version:" + newVersion);
      loadingbar("reiniciando", 0, 15, 250);
      ESP.restart();
    }else{
      alert("Error when trying to update device: " + inf.toString());
      lcdMessage("ALERT:", "",0,0);
      lcd.setCursor(0,1);
      lcdScrollMsg(inf.toString(), 150, 1, 16);
    }
  }else{
    lcdMessage("poor connection", String(WiFi.RSSI()),0,0);
    alert("Conexao fraca. Nao e possivel atualizar dispositivo. P(dBm) = " + (String)WiFi.RSSI());
    delay(2000);
  }
}
