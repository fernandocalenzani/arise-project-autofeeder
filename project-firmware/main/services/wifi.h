void        wifiConfig(void);
void        configModeCallback (WiFiManager *myWiFiManager);
void        saveConfigCallback (void);
void        wificonnect(void);
bool        testConnection(void);
bool        reconnectWifiNet(void);
bool        restartEspWifi(void);
bool        eventWifiDisconnect(int attempt);
bool        scanWifi(void);
