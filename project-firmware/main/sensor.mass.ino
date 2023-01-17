//==| STRAIN GAUGE |=========================================================//
float sensor_mass(void){
  float hsensor_i;
  float m = 0;
  float pi = 3.14159;

  for(int i=0;i<=(__xNSAMPLEx__-1);i++){
    hsensor_i = sensor_hcsr04()/10;
    m += (__density__*(pi/12)*(2*__xDx__*__xDx__ + __xdx__*__xdx__)*(__xHx__-hsensor_i))/__xNSAMPLEx__;
    delay(10);
  }
return m;
};


float sensor_mass_flow(void){
  float m = sensor_mass();
  float mass_flow  = m - __massbefore__;

  if(mass_flow < 400){mass_flow = 0;}

__massbefore__ = m;
return mass_flow;
};
