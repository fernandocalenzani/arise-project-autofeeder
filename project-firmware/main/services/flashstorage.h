const char* writedata_nvs(const char* nvsdata, const char* memoryAddress);
const char* readdata_nvs(const char* memoryAddress);
void        getLocalDeviceConfigurations(const char* slot);
void        getServerDeviceConfigurations(const char* slotSet, const char* slotState);
void        verifyRegistered(const char* slot);
