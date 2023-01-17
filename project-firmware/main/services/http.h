__https     http_get(String server);
__https     http_post(String server, String data);
__https     http_put(String server, String data);
void        http_getLogin(void);
void        registerDevice(const char* slot);
String      httpstatus(int httpCode);
