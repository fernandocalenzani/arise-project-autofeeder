//==| SETUP |================================================================//
void setSetup(void){

  pinMode(PIN_LED_WIFI, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_RELE_MOTOR, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_VCCBUZZER, OUTPUT);
  pinMode(PIN_BTN_CONFIG, INPUT);
  pinMode(PIN_BTN_DISPLAY, INPUT);

  Serial.begin(9600);
  dht.begin();
  lcd.begin();
  DS1307_RTC.begin();

  lcd.backlight();
  lcd.clear();
  addCustomChar();
  ledColorState(2, 1);

  lcd.setCursor(0,0);
  lcd.print("ARISE TECHNOLOGY");
  lcdScrollMsg("         Bem-vindo    ", 150, 1, 16);
  delay(1000);
  lcd.print("app v." + __xVERSIONFIRMWAREx__);
  delay(1500);
  loadingbar("WIFI CONFIGURING", 0, 15, 100);

  int timeafter = millis();
  bool configWifi = false;
  if(digitalRead(PIN_BTN_CONFIG) == HIGH){
    while((millis() - timeafter) <= 5000){
      if(((millis() - timeafter) >= 3000)&&(digitalRead(PIN_BTN_CONFIG) == HIGH)){
        configWifi = true;
      }
    }
  }

  if(configWifi == true){
    loadingbar("Abrindo config", 0, 15, 100);
    wifiConfig();
  }else{
    lcd.clear();
    wificonnect();
  }

  lcd.clear();
  loadingbar("Checking device ", 0 , 1, 100);
  verifyRegistered(slotx05);

  loadingbar("Checking device ", 0 , 5, 1);
  getLocalDeviceConfigurations(slotx04);

  loadingbar("Checking device ", 0 , 8, 1);
  adjusttime_t();
  loadingbar("Checking device ", 0 , 15, 1);
  delay(1000);
  loadingbar("Iniciando...    ", 0 , 15, 50);
  lcd.clear();
};
