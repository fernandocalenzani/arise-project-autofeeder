//==| UTILITIES |============================================================//
String getValue(String data, char separator, int index){

  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void setUpdateDate(String data){
  int index;
  int lastIndex;
  int len = data.length();
  String date;


  index = data.indexOf(':');
  lastIndex = data.indexOf(',');
  date = data.substring(index+2, lastIndex-6);

  for(int i=0; i<= len; i++){
    index = data.indexOf('"');
    data.remove(index, 1);
  }

  len = data.length();
  String params = data.substring(lastIndex +2, len-1);
  params.replace(':',',');

  __updateverify.newversion      = getValue(params,',',1);
  __updateverify.currentversion  = getValue(params,',',3);
  __updateverify.keyOTA          = getValue(params,',',5);

  date.replace(':', ',');
  date.replace('-', ',');
  date.replace('T', ',');

  __updateverify.year    = getValue(date,',',0).toInt();
  __updateverify.mon     = getValue(date,',',1).toInt();
  __updateverify.day     = getValue(date,',',2).toInt();
  __updateverify.hour    = getValue(date,',',3).toInt();
  __updateverify.min     = getValue(date,',',4).toInt();
}


void setParameters(String data){
  int index;
  int len    = data.length();

  for(int i=0; i<= len; i++){
    index = data.indexOf('"');
    data.remove(index, 1);
  }

  len = data.length();
  index = data.indexOf('[');
  int lastIndex= data.lastIndexOf(']');
  String applications = data.substring(index+1, lastIndex);
  String params = data.substring(lastIndex +2, len-1);
  params.replace(':',',');

  __mysettings.devicestate    = getValue(params,',',1);
  __mysettings.GMT            = getValue(params,',',3).toInt();
  __mysettings.KTM            = getValue(params,',',5).toFloat();

  len = applications.length();

  int pos = 0;
  int i=0;
  while((i < 100)){
    if((getValue(applications,',',i) == "")||(getValue(applications,',',i) == NULL)){
      i=101;
    }else if((getValue(applications,',',i) != "")&&(getValue(applications,',',i) != NULL)&&(getValue(applications,',',i) != 0)){
      __mysettings.day[pos]    = getValue(applications,',',i);
      __mysettings.hour[pos]   = getValue(applications,',',i+1).toInt();
      __mysettings.min[pos]    = getValue(applications,',',i+2).toInt();
      __mysettings.amount[pos] = getValue(applications,',',i+3).toFloat();
    }
    pos++;
    i = i + 4;
  }
}


void cleanMeasurements(void){
  __nmeasurement__ = 0;
  for(int i=0; i<=12; i++){
    __measurements.Tmed[i]    = 0;
    __measurements.Umed[i]    = 0;
    __measurements.Hmed[i]    = 0;
    __measurements.Mflow[i]   = 0;
    __measurements.Mmed[i]    = 0;
    __measurements.Bmed[i]    = 0;
    __measurements.Tintmed[i] = 0;
    __measurements.RSSImed[i] = 0;
    __measurements.average[i] = 0;
  }
};


void ledColorState(int color, byte ledState){
  switch(color){
    case 0:
     digitalWrite(PIN_LED_RED,   0);
     digitalWrite(PIN_LED_GREEN, 0);
     digitalWrite(PIN_LED_BLUE,  0);
    break;

    case 1:
     digitalWrite(PIN_LED_RED, ledState);
     digitalWrite(PIN_LED_GREEN, 0);
     digitalWrite(PIN_LED_BLUE,  0);
    break;

    case 2:
     digitalWrite(PIN_LED_RED, 0);
     digitalWrite(PIN_LED_GREEN, ledState);
     digitalWrite(PIN_LED_BLUE,  0);
    break;

    case 3:
     digitalWrite(PIN_LED_RED, ledState);
     digitalWrite(PIN_LED_GREEN, ledState);
     digitalWrite(PIN_LED_BLUE,  0);
    break;

    default:
     digitalWrite(PIN_LED_RED,   0);
     digitalWrite(PIN_LED_GREEN, 0);
     digitalWrite(PIN_LED_BLUE,  0);
    break;
  }
}
