static WiFiClient        wifi;
static WiFiManager       wifiManager;
static HTTPClient        https;
static RTC_DS1307        DS1307_RTC;
static DHT               dht(PIN_DHT_SIG, DHT11);
static HCSR04            hcsr04(PIN_HCSR04_TRIG, PIN_HCSR04_ECHO, 20, 4000);
static LiquidCrystal_I2C lcd(0x27, 16, 2);
static HttpsOTAStatus_t  otastatus;
