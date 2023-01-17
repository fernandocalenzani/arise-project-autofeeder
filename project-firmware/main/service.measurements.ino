//==| MEASUREMENTS |=============================================================//
void getMeasurements(void){
  __measurements.Tmed[__nmeasurement__]       = sensor_dht_temperature();
  __measurements.Umed[__nmeasurement__]       = sensor_dht_humidity();
  __measurements.Hmed[__nmeasurement__]       = sensor_hcsr04();
  __measurements.Mmed[__nmeasurement__]       = sensor_mass();
  __measurements.Mflow[__nmeasurement__]      = sensor_mass_flow();
  __measurements.Bmed[__nmeasurement__]       = sensor_hall();
  __measurements.Tintmed[__nmeasurement__]    = sensor_internal_temperature();
  __measurements.RSSImed[__nmeasurement__]    = sensor_internal_rssi();
  __nmeasurement__++;
  __lastMeasurement__ = millis();
}


void sendMeasurements(void){
  for(int i=0; i<= (__nmeasurement__-1); i++){
    __measurements.average[0] = __measurements.average[0] + __measurements.Tmed[i]/__nmeasurement__;
    __measurements.average[1] = __measurements.average[1] + __measurements.Umed[i]/__nmeasurement__;
    __measurements.average[2] = __measurements.average[2] + __measurements.Hmed[i]/__nmeasurement__;
    __measurements.average[3] = __measurements.average[3] + __measurements.Mmed[i]/__nmeasurement__;
    __measurements.average[4] = __measurements.average[4] + __measurements.Mflow[i]/__nmeasurement__;
    __measurements.average[5] = __measurements.average[5] + __measurements.Bmed[i]/__nmeasurement__;
    __measurements.average[6] = __measurements.average[6] + __measurements.Tintmed[i]/__nmeasurement__;
    __measurements.average[7] = __measurements.average[7] + __measurements.RSSImed[i]/__nmeasurement__;
  }

  examiningMeasurements();

  String data = "{";
  data       += "\"serialNumberId\":\""    + __xSNx__                                + "\",";
  data       += "\"temperature\":"         + String(__measurements.average[0],3)     + ",";
  data       += "\"umidity\":"             + String(__measurements.average[1],3)     + ",";
  data       += "\"tanklevel\":"           + String(__measurements.average[2],3)     + ",";
  data       += "\"totalproduct\":"        + String(__measurements.average[3],3)     + ",";
  data       += "\"productflow\":"         + String(__measurements.average[4],3)     + ",";
  data       += "\"hallfield\":"           + String(__measurements.average[5],3)     + ",";
  data       += "\"InternalTemperature\":" + String(__measurements.average[6],3)     + ",";
  data       += "\"rssi\":"                + String(__measurements.average[7],3)     + "";
  data       += "}";

  int attempts = 0;
  while(attempts< __xNATTEMPTSx__){
    __https senddingData = http_post(__xSERVER__DATAx__, data);
    cleanMeasurements();
    if((senddingData.status >= 200) && (senddingData.status < 400)){
      attempts = 2022;
      cleanMeasurements();
      __lastMeasurementSubmitted__ = millis();
    }else{attempts++; delay(100);}
  }
}


void examiningMeasurements(void){
  DateTime __timenow = DS1307_RTC.now();
  float    criticalTemperature = 70;
  float    criticalUmidity = 100;
  float    criticalLevelTank = 30;
  float    criticalProduct = 0.10*__xMAXTANKCAPACITYx__;
  float    criticalHallField = 100;
  float    criticalInternalTemperature = 90;

  if(__measurements.average[0] >= criticalTemperature){
    alertOFF("Critico: Temperatura do reservatório está muito alta. T = " + (String)__measurements.average[0]);
  }else if(__measurements.average[0] >= 0.8*criticalTemperature){
    alertOFF("Atenção: Temperatura do reservatório está moderadamente alta. T = " + (String)__measurements.average[0]);
  }

  if(__measurements.average[1] >= criticalUmidity){
    alertOFF("Critico: Umidade do reservatório está muito alta. U% = " + (String)__measurements.average[1]);
  }else if(__measurements.average[1] >= 0.9*criticalUmidity){
    alertOFF("Atenção: Umidade do reservatório está muito alta. U% = " + (String)__measurements.average[1]);
  }

  if(__measurements.average[2] <= criticalLevelTank){
    alertOFF("Critico: O nível do reservatório está muito baixo. Nivel = " + (String)__measurements.average[2]);
  }else if(__measurements.average[2] <= 1.2*criticalLevelTank){
    alertOFF("Atenção: O nível do reservatório está baixo. Nivel = " + (String)__measurements.average[2]);
  }

  if(__measurements.average[3] <= criticalProduct){
    alertOFF("Critico: Produto está acabando. Massa = " + (String)__measurements.average[4]);
  }else if(__measurements.average[3] <= 1.2*criticalProduct){
    alertOFF("Atenção: Produto está acabando. Massa = " + (String)__measurements.average[4]);
  }

  if(__measurements.average[5] >= criticalHallField){
    alertOFF("Critico: Campo magnético próximo crítico. B = " + (String)__measurements.average[5]);
  }else if(__measurements.average[5] >= 0.7*criticalHallField){
    alertOFF("Atenção: Campo magnético próximo alto. B = " + (String)__measurements.average[5]);
  }

  if(__measurements.average[6] >= criticalInternalTemperature){
    alertOFF("Critico: Temperatura interna crítica. Desligando dispositivo. Tinterna = " + (String)__measurements.average[6]);
    lcdMessage("PANIC Tint:" + String(__measurements.average[6],0), "Wait for 30 min", 0, 0);
    criticalDeepSleep(30);
  }else if(__measurements.average[6] >= 0.7*criticalInternalTemperature){
    alertOFF("Critico: Temperatura interna alta. Entrando em modo sleep por 5 minutos e reiniciando dispositivo. Tinterna = " + (String)__measurements.average[6]);
    lcdMessage("ALERTA Tint:" + String(__measurements.average[6],0), "Wait for 5 min", 0, 0);
    criticalDeepSleep(5);
  }
}
