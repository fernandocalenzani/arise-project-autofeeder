void        standbyMode(int timeStandby, int fLed);
void        alert(String data);
int         alertOFF(String data);
String      wakeup_reason(void);
void        putDeviceConfiguration(void);
void        sendAlertsInfo(void);
void        criticalDeepSleep(int minutes);
void        deepSleepMode(int seconds);
