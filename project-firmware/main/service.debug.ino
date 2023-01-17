//==| DEBUG |===============================================================//
void debug_ramMemory(void){
  int freeRamMemory = ESP.getFreeHeap();

  if(freeRamMemory < 1000){
    alertOFF("Low RAM memory: " + String(freeRamMemory));
    ESP.restart();
  }
};


void debug_variables(void){
  Serial.println("_______________________________________________");
  Serial.println("__countConnect__                     : " + String(__countConnect__));
  Serial.println("__countDisconnect__                  : " + String(__countDisconnect__));
  Serial.println("__mysettings.devicestate             : " + String(__mysettings.devicestate));
  Serial.println("__mysettings.GMT                     : " + String(__mysettings.GMT));
  Serial.println("__mysettings.KTM                     : " + String(__mysettings.KTM));
  Serial.println("__lastMeasurementSubmitted__ (300000): " + String(millis() - __lastMeasurementSubmitted__));
  Serial.println("__lastMeasurement__           (25000): " + String(millis() - __lastMeasurement__));
  Serial.println("__lastTimelightOn__           (60000): " + String(millis() - __lastTimelightOn__));
  Serial.println("__lastVerifyUpdateFirmware__ (300000): " + String(millis() - __lastVerifyUpdateFirmware__));
  Serial.println("__lastVerifyUpdateSettings__ (300000): " + String(millis() - __lastVerifyUpdateSettings__));
  Serial.println("__timeDisplay__                (5000): " + String(millis() - __timeDisplay__));
  Serial.println("ESP.getFreeHeap          (max: 178kb): " + String(ESP.getFreeHeap()));

  int i=0;
  while(i<100){
    Serial.println("__mysettings.day[" + String(i) +"]                  : " + String(__mysettings.day[i]));
    Serial.println("__mysettings.hour[" + String(i) +"]                 : " + String(__mysettings.hour[i]));
    Serial.println("__mysettings.min[" + String(i) +"]                  : " + String(__mysettings.min[i]));
    Serial.println("__mysettings.amount[" + String(i) +"]               : " + String(__mysettings.amount[i]));
    i++;
    if((__mysettings.day[i] == "")||(__mysettings.day[i] == NULL)||(__mysettings.day[i] == 0)){i=101;}
  }
  Serial.println("_______________________________________________");
}

void restartDevice(int hour, int minutes){
  if((hour == 3)&&(minutes == 5)){
    alertOFF("Reiniciando dispositivo");
    ESP.restart();
  }
}
