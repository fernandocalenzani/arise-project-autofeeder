//==| DHT |==================================================================//
float sensor_dht_temperature(void){
  float T = 0;
  for(int i=0;i<=(__xNSAMPLEx__-1);i++){
    T = dht.readTemperature() + T;
    delay(10);
  }
return (T/__xNSAMPLEx__);
};


float sensor_dht_humidity(void){
  float U = 0;
  for(int i=0;i<=(__xNSAMPLEx__-1);i++){
    U = dht.readHumidity() + U;
    delay(10);
  }
return (U/__xNSAMPLEx__);
};
