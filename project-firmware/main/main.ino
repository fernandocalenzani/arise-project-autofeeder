/*_____________________________________________________________________________
  ARISE TECHNOLOGY
  main:    main.ino
  author:  ARISE Technology
  email:   contato.grupobms@gmail.com
  license: MIT
_____________________________________________________________________________*/

/*
*
*
*
*/

//==| IMPORTS |==============================================================//
#include "./project.config.h"

//==| SETUP |================================================================//
void setup(){
setSetup();
};

//==| LOOP |=================================================================//
void loop(){

  /*/-| MAIN FUNCTIONS|-----------------------------------------------------<*/
    DateTime __timenow = DS1307_RTC.now();
    debug_ramMemory();
    debug_variables();

    restartDevice(__timenow.hour(), __timenow.minute());

    if(millis() - __timeDisplay__ >= 5000){
      displayMenssage();
      __timeDisplay__ = millis();
    }

    if(digitalRead(PIN_BTN_DISPLAY) == HIGH){
      lcd.backlight();
      __lastTimelightOn__ = millis();
    }else if((millis() - __lastTimelightOn__) > 60000){
      lcd.noBacklight();
    }
  /*/-----------------------------------------------------------------------<*/

  /*> CONNECTED-------------------------------------------------------------<*/
    if((WiFi.status() == WL_CONNECTED)&&(testConnection() == true)){
      /*> PART 0: STARTING--------------------<*/
        ledColorState(2, 1);
        __countConnect__++;
        __countDisconnect__ = 0;

        if(digitalRead(PIN_LED_WIFI) == 0){
          digitalWrite(PIN_LED_WIFI, HIGH);
          sendAlertsInfo();
        }
      /*>-------------------------------------<*/


      /*> PART 1: UPDATE FIRMWARE VERIFY------<*/
        if((millis()-__lastVerifyUpdateFirmware__) >= 120000){
          if(getUpdateFirmware() == true){
            __adviceUpdateFirmware__ = true;
          }else{
            __adviceUpdateFirmware__ = false;
          }
          __lastVerifyUpdateFirmware__ = millis();
        }
      /*>-------------------------------------<*/


      /*> PART 2: GET SETTINGS----------------<*/
        if((millis()-__lastVerifyUpdateSettings__) >= 120000){
          getServerDeviceConfigurations(slotx04, slotx06);
        }
      /*>-------------------------------------<*/


      /*> PART 3: STATE DEVICE CHECK----------<*/
        if(__mysettings.devicestate == "false"){
          __https getsettings = http_get(__xSERVER__CONFIGx__);
          if((getsettings.status >= 200) && (getsettings.status < 400)){
            setParameters(getsettings.res);
            alertOFF("Modo Economia: No app, ESTADO DO DISPOSITIVO em LIGADO para sair deste modo");
            deepSleepMode(5);
          }
        }
      /*>-------------------------------------<*/


      /*> PART 4: CHECK APPLICATION-----------<*/
        if(__mysettings.devicestate == "true"){
          int i=0;
          bool end=false;
          while(end!=true){
            if((String(__weekdays__[__timenow.dayOfTheWeek()]) == __mysettings.day[i])&&(__timenow.hour() == __mysettings.hour[i])&&(__timenow.minute() == __mysettings.min[i])){
              startOnlineApplication(i, __mysettings.KTM, __mysettings.amount[i]);
            }else if((String(__timenow.day()) == __mysettings.day[i])&&(__timenow.hour() == __mysettings.hour[i])&&(__timenow.minute() == __mysettings.min[i])){
              startOnlineApplication(i, __mysettings.KTM, __mysettings.amount[i]);
            }
            i++;
            if((__mysettings.day[i]==NULL)||(__mysettings.hour[i]==NULL)){end = true;}
          }
        }else if((__mysettings.devicestate != "false")&&(__mysettings.devicestate != "true")){
          lcd.setBacklight(HIGH);
          ledColorState(3, 1);
          alert("Modo standby. Cadastre o dispositivo e configure as aplicacoes para sair deste modo");
        }
      /*>-------------------------------------<*/


      /*> PART 5: MEASUREMENT-----------------<*/
        if(((millis()-__lastMeasurement__) > (1200000/((sizeof(__measurements.Tmed)/sizeof(int)))) )&&(__nmeasurement__<=(sizeof(__measurements.Tmed)/sizeof(int)))){
          getMeasurements();
        }
      /*>-------------------------------------<*/


      /*> PART 6: SEND DATA-------------------<*/
        if((millis() - __lastMeasurementSubmitted__) > 1200000){
          sendMeasurements();
        }
      /*>-------------------------------------<*/


      /*> PART 7: UPDATES MODE----------------<*/
      /*>-------------------------------------<*/
  /*> ----------------------------------------------------------------------<*/

  /*> DISCONNECTED----------------------------------------------------------<*/
    }else{
      /*> PART 0: STARTING--------------------<*/
        ledColorState(1, 1);
        __countDisconnect__++;
        __countConnect__ = 0;

        if(digitalRead(PIN_LED_WIFI) == 1){
          digitalWrite(PIN_LED_WIFI, LOW);
          __countDisconnect__ = 0;

          String str = "Offline: " + String(__timenow.year(), DEC) +"-"+ String(__timenow.month(), DEC) +"-"+ String(__timenow.day(), DEC) +"T"+ String(__timenow.hour(), DEC) + ":"+ String(__timenow.minute(), DEC);
          const char* msg_slotx02 = str.c_str();
          writedata_nvs(msg_slotx02, slotx02);
        }

        if(__countDisconnect__%5 == 0){
          eventWifiDisconnect(__countDisconnect__);
        }
      /*>-------------------------------------<*/


      /*> PART 1: STATE DEVICE CHECK----------<*/
        if((__mysettings.devicestate == "false")){
          deepSleepMode(5);
        }
      /*>-------------------------------------<*/


      /*> PART 2: CHECK APPLICATION-----------<*/
        if(__mysettings.devicestate == "true"){
          int i=0;
          bool end=false;
          while(end!=true){
            if((String(__weekdays__[__timenow.dayOfTheWeek()]) == __mysettings.day[i])&&((__timenow.hour() == __mysettings.hour[i])&&(__timenow.minute() == __mysettings.min[i]))){
              startOfflineApplication(i, __mysettings.KTM, __mysettings.amount[i]);
            }else if((String(__timenow.day()) == __mysettings.day[i])&&(__timenow.hour() == __mysettings.hour[i])&&(__timenow.minute() == __mysettings.min[i])){
              startOfflineApplication(i, __mysettings.KTM, __mysettings.amount[i]);
            }
            i++;
            if((__mysettings.day[i]==NULL)||(__mysettings.hour[i]==NULL)){end = true;}
          }
        }else if((__mysettings.devicestate != "false")&&(__mysettings.devicestate != "true")){
          lcd.setBacklight(HIGH);
          ledColorState(3, 1);
          lcdMessage("N tenho dosagens", "configure no app", 0,0);
        }
      /*>-------------------------------------<*/


      /*> PART 3: UPDATES MODE----------------<*/
        delay(2000);
      /*>-------------------------------------<*/
    }
  /*> ----------------------------------------------------------------------<*/
};
/*>END LOOP<*/
