//==| BUZZER |===============================================================//
void buzzer(int fhigh_buzzer, int flow_buzzer, int timeOnBuzzer){
  digitalWrite(PIN_VCCBUZZER, HIGH);
  for(int i=0;i<=timeOnBuzzer;i++){
    tone(PIN_BUZZER,fhigh_buzzer,flow_buzzer);
    delay(1000);
  }
  digitalWrite(PIN_VCCBUZZER, LOW);
};
