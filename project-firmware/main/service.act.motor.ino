//==| MOTOR |=================================================================//
void motorStart(float productQuantity, float Ktm, float Tadjusted){
  float ton = (Ktm*productQuantity)*1000*(1 + Tadjusted/100);
  int tonStart = millis();
  digitalWrite(PIN_RELE_MOTOR, HIGH);
  while((millis() - tonStart) <= ton){ }
  digitalWrite(PIN_RELE_MOTOR, LOW);
};
