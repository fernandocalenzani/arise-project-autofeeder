//==| STORAGE MEMORY |================================================================//
const char* writedata_nvs(const char* nvsdata, const char* memoryAddress){
  nvs_handle  handler_partition_nvs;
  esp_err_t   res;
  const char* response;


  res = nvs_flash_init_partition("nvs");
  if (res != ESP_OK)    {return response = "[ERROR Mx0x2x0] Failed to start NVS partition.";}

  res = nvs_open_from_partition("nvs", "ns_nvs", NVS_READWRITE, &handler_partition_nvs);
  if (res != ESP_OK){return response = "[ERROR Mx0x3x0] Failed to open NVS as read/write";}

  res = nvs_set_str(handler_partition_nvs, memoryAddress, nvsdata);
  if (res != ESP_OK){
    switch (res){
      case ESP_ERR_NVS_READ_ONLY: response = "[ERROR Mx0x0x1] storage handle opened read-only"; break;
      case ESP_ERR_NVS_INVALID_HANDLE: response = "[ERROR Mx0x0x2] identifier has been closed or is NULL"; break;
      case ESP_ERR_NVS_INVALID_NAME: response = "[ERROR Mx0x0x3] probably the key name does not meet the restrictions"; break;
      case ESP_ERR_NVS_NOT_ENOUGH_SPACE: response = "[ERROR Mx0x0x4] there is not enough space in the underlying storage to save the value"; break;
      case ESP_ERR_NVS_REMOVE_FAILED: response = "[ERROR Mx0x0x5] Value written to memory has not been updated. Please try again after NVS restarts";break;
      case ESP_ERR_NVS_VALUE_TOO_LONG: response = "[ERROR Mx0x0x6] string value is too long";break;
      default: response = "[ERROR Mx0x0x0] fatal error"; break;
    };
    nvs_close(handler_partition_nvs);
    return response;

  }else{
    nvs_commit(handler_partition_nvs);
    nvs_close(handler_partition_nvs);
    return response = "Data saved successfully!";
  }

  delay(10);
}


const char* readdata_nvs(const char* memoryAddress){
 const char* response;
 nvs_handle  handler_partition_nvs;
 esp_err_t   req;
 size_t      required_size;

  req = nvs_flash_init_partition("nvs");
  if (req != ESP_OK){return response = "[ERROR] Failed to start NVS partition.";}

  req = nvs_open_from_partition("nvs", "ns_nvs", NVS_READWRITE, &handler_partition_nvs);
  if (req != ESP_OK){return response = "[ERROR]: Failed to open NVS as read/write";}

  nvs_get_str(handler_partition_nvs, memoryAddress, NULL, &required_size);
  char* dataread = (char*)malloc(required_size);
  nvs_get_str(handler_partition_nvs, memoryAddress, dataread, &required_size);
  if (req != ESP_OK){
    switch (req){
      case ESP_FAIL: response = "[ERROR Mx0x1x7] probably due to corrupted NVS partition"; break;
      case ESP_ERR_NVS_NOT_FOUND: response = "[ERROR Mx0x1x8] probably the requested key does not exist"; break;
      case ESP_ERR_NVS_INVALID_HANDLE: response = "[ERROR Mx0x1x2] identifier has been closed or is NULL"; break;
      case ESP_ERR_NVS_INVALID_NAME: response = "[ERROR Mx0x1x3] probably the key name does not meet the restrictions"; break;
      case ESP_ERR_NVS_INVALID_LENGTH: response = "[ERROR Mx0x1x9] probably the accessed length is not enough to store data"; break;
      default: response = "[ERROR Mx0x1x0] fatal error"; break;
    };
    return response;
  }else{
    nvs_close(handler_partition_nvs);
    return response = dataread;
  }
  delay(10);
}


void getServerDeviceConfigurations(const char* slotSet, const char* slotState){
  int attempts = 0;

  while(attempts < __xNATTEMPTSx__){
    __https getsettings = http_get(__xSERVER__CONFIGx__);
    if((getsettings.status >= 200) && (getsettings.status < 400)){
      const char* storageSettings = getsettings.res.c_str();
      setParameters(getsettings.res);
      __lastVerifyUpdateSettings__ = millis();
      attempts = 2022;
      if(strcmp(readdata_nvs(slotSet), storageSettings) != 0) {
        writedata_nvs(storageSettings, slotSet);
      }
      if(__mysettings.devicestate != readdata_nvs(slotState)){
        writedata_nvs(__mysettings.devicestate.c_str(), slotState);
      }
    }else{attempts++; delay(50);}
  }
}


void getLocalDeviceConfigurations(const char* slot){
  const char* storageSettings = readdata_nvs(slot);
  setParameters(String(storageSettings));
  __mysettings.devicestate = String(readdata_nvs(slotx06));
}


void verifyRegistered(const char* slot){
  if(strcmp(readdata_nvs(slot), "OK") != 0){
    if((WiFi.status() == WL_CONNECTED)&&(testConnection() == true)){
      registerDevice(slot);
    }else{
     lcdMessage("Sem internet","Reiniciando", 0, 0);
    }
  }
}
