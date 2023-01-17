//==| HTTP |=================================================================//
__https http_get(String server){
  __https __httpsGet;

  if (https.begin(server)){
    https.addHeader("Accept-Charset", "utf-8");
    https.addHeader("Accept-Language", "pt-br");
    https.addHeader("Content-Type", "text/csv");
    https.addHeader("Authorization", "Bearer " + __token__);
    https.addHeader("Connection", "close");
    __httpsGet.status = https.GET();
    if ((__httpsGet.status > 0)&&(__httpsGet.status < 400)){
      __httpsGet.res = https.getString();
      https.end();
    }else if(__httpsGet.status == 401){
      http_getLogin();
      if(__token__ != "Invalid"){
        https.addHeader("Accept-Charset", "utf-8");
        https.addHeader("Accept-Language", "pt-br");
        https.addHeader("Content-Type", "application/json");
        https.addHeader("Authorization", "Bearer " + __token__);
        https.addHeader("Connection", "close");
        __httpsGet.status = https.GET();
        if ((__httpsGet.status > 0)&&(__httpsGet.status < 400)){
          __httpsGet.res = https.getString();
          https.end();
        }
      }
    }else if((__httpsGet.status == 400) || (__httpsGet.status >401)){
      __httpsGet.res = https.getString();
      __httpsGet.res = httpstatus(__httpsGet.status, __httpsGet.res);
      https.end();
    }
  }else{
    https.end();
  }
return __httpsGet;
};


__https http_post(String server, String data){
  __https __httpsPost;

  if (https.begin(server)){
    https.addHeader("Accept-Charset", "utf-8");
    https.addHeader("Accept-Language", "pt-br");
    https.addHeader("Content-Type", "application/json");
    https.addHeader("Authorization", "Bearer " + __token__);
    https.addHeader("Connection", "close");
    __httpsPost.status = https.POST(data);

    if ((__httpsPost.status > 0)&&(__httpsPost.status < 400)){
      __httpsPost.res = https.getString();
      https.end();
    }else if(__httpsPost.status == 401){
      http_getLogin();
      if(__token__ != "Invalid"){
        https.addHeader("Accept-Charset", "utf-8");
        https.addHeader("Accept-Language", "pt-br");
        https.addHeader("Content-Type", "application/json");
        https.addHeader("Authorization", "Bearer " + __token__);
        https.addHeader("Connection", "close");
        __httpsPost.status = https.POST(data);
        if ((__httpsPost.status > 0)&&(__httpsPost.status < 400)){
          __httpsPost.res = https.getString();
          https.end();
        }
      }
    }else if((__httpsPost.status == 400) || (__httpsPost.status >401)){
      __httpsPost.res = https.getString();
      __httpsPost.res = httpstatus(__httpsPost.status, __httpsPost.res);
      https.end();
    }else{
      https.end();
    }
  }
return __httpsPost;
};


__https http_put(String server, String data){
  __https __httpsPut;

  if (https.begin(server)){
    https.addHeader("Accept-Charset", "utf-8");
    https.addHeader("Accept-Language", "pt-br");
    https.addHeader("Content-Type", "application/json");
    https.addHeader("Authorization", "Bearer " + __token__);
    https.addHeader("Connection", "close");
    __httpsPut.status = https.PUT(data);

    if ((__httpsPut.status > 0)&&(__httpsPut.status < 400)){
      __httpsPut.res = https.getString();
      https.end();
    }else if(__httpsPut.status == 401){
      http_getLogin();
      if(__token__ != "Invalid"){
        https.addHeader("Accept-Charset", "utf-8");
        https.addHeader("Accept-Language", "pt-br");
        https.addHeader("Content-Type", "application/json");
        https.addHeader("Authorization", "Bearer " + __token__);
        https.addHeader("Connection", "close");
        __httpsPut.status = https.PUT(data);
        if ((__httpsPut.status > 0)&&(__httpsPut.status < 400)){
          __httpsPut.res = https.getString();
          https.end();
        }
      }
    }else if((__httpsPut.status == 400) || (__httpsPut.status >401)){
      __httpsPut.res = https.getString();
      __httpsPut.res = httpstatus(__httpsPut.status, __httpsPut.res);
      https.end();
    }else{
      https.end();
    }
  }
return __httpsPut;
};


void http_getLogin(void){
  int status;

  if (https.begin(__xSERVER__LOGINx__)){
    https.addHeader("Accept-Charset", "utf-8");
    https.addHeader("Accept-Language", "pt-br");
    https.addHeader("Content-Type", "application/json");
    https.addHeader("Connection", "close");

    String data  = "{";
    data += "\"email\": \"" + __xSSIDLOGINx__ + "\",";
    data += "\"password\": \"" + __xPASSLOGINx__ + "\"";
    data += "}";

    status = https.POST(data);

    if ((status > 0)&&(status < 400)){
      String  res    = https.getString();
      int     index  = res.lastIndexOf(':');
      int     len    = res.length();
      __token__         = res.substring(index + 2, len - 2);
    }else{
      __token__ = "Invalid";
      https.end();
    }
  https.end();
  }
};


void registerDevice(const char* slot){
  if (https.begin(__xSERVER__REGISTERx__)){
    https.addHeader("Accept-Charset", "utf-8");
    https.addHeader("Accept-Language", "pt-br");
    https.addHeader("Content-Type", "application/json");
    https.addHeader("Connection", "close");

    String data  = "{";
    data += "\"email\": \""         + __xSSIDLOGINx__    + "\",";
    data += "\"password\": \""      + __xPASSLOGINx__ + "\",";
    data += "\"name\": \""          + __xSNx__   + "\",";
    data += "\"country\": \""       + __xMYCOUNTRYx__  + "\",";
    data += "\"stateFrom\": \""     + __xMYSTATEx__    + "\",";
    data += "\"city\": \""          + __xMYCITYx__     + "\"";
    data += "}";

    int httpCode = https.POST(data);
    if (httpCode > 0){
      if ((httpCode >= 200) && (httpCode < 300)){
        writedata_nvs("OK",slot);
      }else{
        lcd.clear();
        lcdScrollMsg("[ERROR] Não foi possível registrar este dispositivo. Error: " + (String)httpCode, 200, 0, 16);
        writedata_nvs("NOK",slot);
      }
    }else{
      lcd.clear();
      lcdScrollMsg("[ERROR] cannot register this device. Error: " + (String)httpCode, 200, 0, 16);
      writedata_nvs("NOK",slot);
    }
    https.end();
  }else{
    lcd.clear();
    lcdScrollMsg("[ERROR] Não foi possível conectar ao servidor", 200, 0, 16);
    writedata_nvs("NOK",slot);
  }

  if(strcmp(readdata_nvs(slot), "OK") != 0){
    ledColorState(3, 1);
    lcdMessage("ERR:unregistered", "Reiniciando", 0, 0);
    delay(5000);
  }
};


String httpstatus(int httpCode, String httpMessage){
  String response;
  switch(httpCode){
    case 100:;
    response = "[HTTP STATUS: 100]: Continue\n[HTTP RES]:" + httpMessage;
    break;
    case 101:
    response = "[HTTP STATUS: 101]: Switching Protocol\n[HTTP RES]:" + httpMessage;
    break;
    case 103:
    response = "[HTTP STATUS: 103]: Early Hints\n[HTTP RES]:" + httpMessage;
    break;

    case 200:;
    response = "[HTTP STATUS: 200]: OK\n[HTTP RES]:" + httpMessage;
    break;
    case 201:
    response = "[HTTP STATUS: 201]: Created\n[HTTP RES]:" + httpMessage;
    break;
    case 202:
    response = "[HTTP STATUS: 103]: Accepted\n[HTTP RES]:" + httpMessage;
    break;
    case 203:
    response = "[HTTP STATUS: 203]: Non-Authoritative Information\n[HTTP RES]:" + httpMessage;
    break;
    case 204:
    response = "[HTTP STATUS: 204]: No Content\n[HTTP RES]:" + httpMessage;
    break;
    case 205:
    response = "[HTTP STATUS: 205]: Reset Content\n[HTTP RES]:" + httpMessage;
    break;
    case 206:
    response = "[HTTP STATUS: 206]: Partial Content\n[HTTP RES]:" + httpMessage;
    break;

    case 300:
    response = "[HTTP STATUS: 300]: Multiple Choice\n[HTTP RES]:" + httpMessage;
    break;
    case 301:
    response = "[HTTP STATUS: 301]: Moved Permanently\n[HTTP RES]:" + httpMessage;
    break;
    case 302:
    response = "[HTTP STATUS: 302]: Found\n[HTTP RES]:" + httpMessage;
    break;
    case 303:
    response = "[HTTP STATUS: 303]: See Other\n[HTTP RES]:" + httpMessage;
    break;
    case 304:
    response = "[HTTP STATUS: 304]: Not Modified\n[HTTP RES]:" + httpMessage;
    break;
    case 307:
    response = "[HTTP STATUS: 307]: Temporary Redirect\n[HTTP RES]:" + httpMessage;
    break;
    case 308:
    response = "[HTTP STATUS: 308]: Permanent Redirect\n[HTTP RES]:" + httpMessage;
    break;

    case 400:
    response = "[HTTP STATUS: 400]: Bad Request\n[HTTP RES]:" + httpMessage;
    break;
    case 401:
    response = "[HTTP STATUS: 401]: Unauthorized\n[HTTP RES]:" + httpMessage;
    break;
    case 403:
    response = "[HTTP STATUS: 403]: Forbidden\n[HTTP RES]:" + httpMessage;
    break;
    case 404:
    response = "[HTTP STATUS: 404]: Not Found\n[HTTP RES]:" + httpMessage;
    break;
    case 405:
    response = "[HTTP STATUS: 405]: Method Not Allowed\n[HTTP RES]:" + httpMessage;
    break;
    case 406:
    response = "[HTTP STATUS: 406]: Not Acceptable\n[HTTP RES]:" + httpMessage;
    break;
    case 407:
    response = "[HTTP STATUS: 407]: Proxy Authentication Required\n[HTTP RES]:" + httpMessage;
    break;
    case 408:
    response = "[HTTP STATUS: 408]: Request Timeout\n[HTTP RES]:" + httpMessage;
    break;
    case 409:
    response = "[HTTP STATUS: 409]: Conflict\n[HTTP RES]:" + httpMessage;
    break;
    case 410:
    response = "[HTTP STATUS: 410]: Gone\n[HTTP RES]:" + httpMessage;
    break;
    case 411:
    response = "[HTTP STATUS: 411]: Lenght Required\n[HTTP RES]:" + httpMessage;
    break;
    case 412:
    response = "[HTTP STATUS: 412]: Precondition Failed\n[HTTP RES]:" + httpMessage;
    break;
    case 413:
    response = "[HTTP STATUS: 413]: Payload Too Large\n[HTTP RES]:" + httpMessage;
    break;
    case 414:
    response = "[HTTP STATUS: 414]: URI Too Large\n[HTTP RES]:" + httpMessage;
    break;
    case 416:
    response = "[HTTP STATUS: 416]: Range Not Satisfiable\n[HTTP RES]:" + httpMessage;
    break;
    case 417:
    response = "[HTTP STATUS: 417]: Expectation Failed\n[HTTP RES]:" + httpMessage;
    break;
    case 422:
    response = "[HTTP STATUS: 422]: Unprocessable Entity\n[HTTP RES]:" + httpMessage;
    break;
    case 426:
    response = "[HTTP STATUS: 426]:  Upgrade Required\n[HTTP RES]:" + httpMessage;
    break;
    case 428:
    response = "[HTTP STATUS: 428]: Precondition Required\n[HTTP RES]:" + httpMessage;
    break;
    case 429:
    response = "[HTTP STATUS: 429]: Too Many Requests\n[HTTP RES]:" + httpMessage;
    break;
    case 431:
    response = "[HTTP STATUS: 431]: Request Header Fields Too Large\n[HTTP RES]:" + httpMessage;
    break;
    case 451:
    response = "[HTTP STATUS: 451]: Unavailable For Legal Reasons\n[HTTP RES]:" + httpMessage;
    break;

    case 500:
    response = "[HTTP STATUS: 500]: Internal Server Error\n[HTTP RES]:" + httpMessage;
    break;
    case 501:
    response = "[HTTP STATUS: 501]: Not Implemented\n[HTTP RES]:" + httpMessage;
    break;
    case 502:
    response = "[HTTP STATUS: 502]: Bad Gateway\n[HTTP RES]:" + httpMessage;
    break;
    case 503:
    response = "[HTTP STATUS: 503]: Service Unavailable\n[HTTP RES]:" + httpMessage;
    break;
    case 504:
    response = "[HTTP STATUS: 504]: Gateway Timeout\n[HTTP RES]:" + httpMessage;
    break;
    case 505:
    response = "[HTTP STATUS: 505]: HTTP Version Not Supported\n[HTTP RES]:" + httpMessage;
    break;
    case 506:
    response = "[HTTP STATUS: 506]: Variant Also Negotiates\n[HTTP RES]:" + httpMessage;
    break;
    case 507:
    response = "[HTTP STATUS: 507]: Insufficient Storage\n[HTTP RES]:" + httpMessage;
    break;
    case 508:
    response = "[HTTP STATUS: 508]: Loop Detected\n[HTTP RES]:" + httpMessage;
    break;
    case 510:
    response = "[HTTP STATUS: 510]: Not Extended\n[HTTP RES]:" + httpMessage;
    break;
    case 511:
    response = "[HTTP STATUS: 511]: Network Authentication Required\n[HTTP RES]:" + httpMessage;
    break;



  }

return response;
};
