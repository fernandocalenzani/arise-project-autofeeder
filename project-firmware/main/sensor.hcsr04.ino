//==| HCSR04 |===============================================================//
float sensor_hcsr04(void){
  float D      = 0;

  for(int i=0;i<=(__xNSAMPLEx__-1);i++){
    D = hcsr04.distanceInMillimeters() + D;
    delay(10);
  }
return D/__xNSAMPLEx__;
};
