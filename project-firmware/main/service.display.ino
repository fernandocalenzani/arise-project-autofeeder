//==| DISPLAY |=================================================================//
void lcdScrollMsg(String message, int delayTime, int row, int lcdColumns){
  for (int i=0; i < lcdColumns; i++) {
    message = " " + message;
  }
  message = message + " ";
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
};


void addCustomChar(void){
  lcd.createChar(3, c3_reconnect);
  lcd.createChar(4, c4_update);
	lcd.createChar(5, c5_wifion);
	lcd.createChar(6, c6_loadbar);
  lcd.createChar(7, c7_check);
  lcd.createChar(8, c8_celsiusdegree);
  lcd.createChar(9, c9_wifioff);

  lcd.home();
};


void displayMenssage(void){
  DateTime __timenow = DS1307_RTC.now();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(String(__timenow.day(), DEC) + "/" + String(__timenow.month(), DEC) + "/" + String(__timenow.year(), DEC).substring(2,4) + " " + String(__timenow.hour(), DEC) + ":" + String(__timenow.minute(), DEC));

  lcd.setCursor(0,1);

  switch(__idisplay__){
    case 0:
      lcd.print("Tres: " + String(sensor_dht_temperature(),1));
      lcdWriteChar(12, 1, 8);
      lcd.setCursor(13,1);
      lcd.print("C");
      break;
    case 1:
      lcd.print("U%: " + String(sensor_dht_humidity(),1) + "%");
      break;
    case 2:
      lcd.print("Nivel: " + String(sensor_hcsr04()/10,1) + "cm");
      break;
    case 3:
      lcd.print("Mass: " + String(sensor_mass()/1000,1) + "kg");
      break;
    case 4:
      lcd.print("Flow: " + String(sensor_mass_flow()/1000,1) + "kg/s");
      break;
    case 5:
      lcd.print("Bhall: " + String(sensor_hall(),1) + "Vh");
      break;
    case 6:
      lcd.print("Tint: " + String(sensor_internal_temperature(),1));
      lcdWriteChar(11, 1, 8);
      lcd.setCursor(12,1);
      lcd.print("C");
      break;
    case 7:
      lcd.print("RSSI: " + String(sensor_internal_rssi(),1) + "%");
    default:
      break;
  }

  writeConnectionStatus();

  if(__adviceUpdateFirmware__ == true){
   lcdWriteChar(15, 1, 4);
  }

  if(__idisplay__ <= 6){__idisplay__++;}
  else{__idisplay__ = 0;}
};


void loadingbar(String message, int start , int end, int delayTime){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
  for(int i=start; i<=end; i++){
    lcd.setCursor(i,1);
    lcd.write(6);
    delay(delayTime);
  }
};


void lcdMessage(String msg1, String msg2, int cursor1, int cursor2){
  lcd.clear();
  lcd.setCursor(cursor1,0);
  lcd.print(msg1);
  lcd.setCursor(cursor2,1);
  lcd.print(msg2);
}


void lcdWriteChar(int pos, int col, int nchar){
  lcd.setCursor(pos, col);
  lcd.write(nchar);
}


void writeConnectionStatus(void){
  if ((WiFi.status() == WL_CONNECTED)&&(testConnection() == true)) {
    lcdWriteChar(15, 0, 5);
  }else{
    lcdWriteChar(15, 0, 9);
  }
}
