//==| WIFI MANAGER |=========================================================//
void wifiConfig(void){

  loadingbar("Iniciando...", 0, 15, 150);
  digitalWrite(PIN_LED_WIFI,LOW);
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  lcdMessage("abrindo portal","",0,0);
  lcdScrollMsg("Entre no portal e faca a conexao local", 200, 1, 16);
  wifiManager.setConnectTimeout(10);
  wifiManager.setTimeout(60);
  wifiManager.resetSettings();

  if(!wifiManager.startConfigPortal("bms_wifi", "12345678")){
    digitalWrite(PIN_LED_WIFI,LOW);
    lcdMessage("Falhou: X","",0,0);
    lcdScrollMsg("Por favor, tente novamente em 5 segundos", 150, 1, 16);
  }
  else{
    digitalWrite(PIN_LED_WIFI,HIGH);
    lcdScrollMsg("successfully connected", 150, 1, 16);
    writedata_nvs((wifiManager.getWiFiSSID(true)).c_str(), slotx00);
    writedata_nvs((wifiManager.getWiFiPass(true)).c_str(), slotx01);
  }
};


void configModeCallback (WiFiManager *myWiFiManager) {
  lcd.clear();
  lcdScrollMsg("Iniciando configuração wifi", 150, 0, 16);
  lcdMessage("Acesse: bms_wifi", "192.168.4.1",0,0);
  delay(100);
};


void saveConfigCallback(void) {
  lcdMessage("Salvo", "",0,0);
};


void wificonnect(void){
  int i = 0;
  const char* ssid     = readdata_nvs(slotx00);
  const char* password = readdata_nvs(slotx01);
  int tafter = millis();
  WiFi.begin(ssid, password);
  while((WiFi.status() != WL_CONNECTED)&&(i<=16)){
    lcd.setCursor(0, 0);
    lcd.print("Conectando...");
    lcd.setCursor(i,1);
    lcd.write(6);
    delay(500);
    i++;
  };

  if ((WiFi.status() == WL_CONNECTED)&&(testConnection() == true)){
    if(testConnection() == false){
      lcdMessage("Connected:" + String(WiFi.RSSI()) + "dBm", "Sem internet",0,0);
      delay(2000);
      digitalWrite(PIN_LED_WIFI,LOW);
    }else{
      lcdMessage("Connected:" + String(WiFi.RSSI()) + "dBm", "Com internet",0,0);
      delay(2000);
      digitalWrite(PIN_LED_WIFI,HIGH);
    }
  }else{
    lcdMessage("conexao falhou", "",0,0);
    digitalWrite(PIN_LED_WIFI,LOW);
    delay(1500);
  }
};


bool testConnection(void){
  __https textConnection1 = http_get("https://www.google.com");
  if(textConnection1.status < 0){
    return false;
  }else{
    return true;
  }
}


bool reconnectWifiNet(void){

  WiFi.disconnect();while(WiFi.status() == WL_CONNECTED){};

  int timeOut = millis();
  WiFi.reconnect();while((WiFi.status() != WL_CONNECTED)&&(millis() - timeOut < 10000)) {};

  if(WiFi.status() == WL_CONNECTED){
    lcdWriteChar(15, 0, 5);
    digitalWrite(PIN_LED_WIFI, HIGH);
    return true;
  }else{
    return false;
  }
}


bool restartEspWifi(void){
  while(esp_wifi_stop() != ESP_OK){}
  esp_sleep_enable_timer_wakeup(3*1000*1000);
  esp_light_sleep_start();
  while(esp_wifi_start() != ESP_OK){}

  if(WiFi.status() != WL_CONNECTED){
    return reconnectWifiNet();
  }
}


bool eventWifiDisconnect(int attempt){
  bool result;

  if(scanWifi() == true){
    result = reconnectWifiNet();

    if(attempt%50 == 0){
      result = restartEspWifi();
    }else if(attempt%1000 == 0){
      if(verifyNextDosages() != true){
        ESP.restart();
      }
    }
  }
  return result;
}


bool scanWifi(void){
  int n = WiFi.scanNetworks();
  WiFi.scanDelete();
  if(n != 0){return true;
  }else{return false;}
}
