//==| INTERNAL |=============================================================//
float sensor_hall(void){
return hallRead();
};


float sensor_internal_temperature(void){
return ((temprature_sens_read() - 32) / 1.8);
};


float sensor_internal_rssi(void){
  float RSSI = WiFi.RSSI();
  if(WiFi.status() == WL_CONNECTED){
    if(RSSI > -30){
      return 100;
    }else if((RSSI > -52)&&(RSSI < -31)){
      return 90;
    }else if((RSSI > -63)&&(RSSI < -53)){
      return 80;
    }else if((RSSI > -75)&&(RSSI < -64)){
      return 50;
    }else if((RSSI > -89)&&(RSSI < -76)){
      return 35;
    }else if(RSSI < -89){
      return 5;
    }
  }else{
    return 0;
  }
};
