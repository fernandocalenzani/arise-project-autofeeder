#ifdef __cplusplus
  extern "C" {
 #endif
  uint8_t temprature_sens_read(void);
#ifdef __cplusplus
}
#endif

uint8_t      temprature_sens_read(void);
float        sensor_dht_temperature(void);
float        sensor_dht_humidity(void);
float        sensor_hcsr04(void);
float        sensor_hall(void);
float        sensor_internal_temperature(void);
float        sensor_mass(void);
float        sensor_mass_flow(void);
