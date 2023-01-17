struct __https {
  String res;
  int    status;
};
typedef struct __https __https;

typedef struct {
    String  day[100];
    int     hour[100];
    int     min[100];
    float   amount[100];
    String  devicestate;
    int     GMT;
    float   KTM;
}__struct_devicesettings;
__struct_devicesettings __mysettings;

typedef struct {
    int  day;
    int  mon;
    int  year;
    int  hour;
    int  min;
    String  newversion;
    String  currentversion;
    String  keyOTA;
}__struct_updateverify;
__struct_updateverify __updateverify;

typedef struct {
  float Tmed[12];
  float Umed[12];
  float Hmed[12];
  float Mflow[12];
  float Mmed[12];
  float Bmed[12];
  float Tintmed[12];
  float RSSImed[12];
  float average[12];
}__struct_measurement;
__struct_measurement __measurements;
