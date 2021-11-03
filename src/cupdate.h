///	---------------------------------------
///   Controller Update = Cupdate Libary
///		  Version	1.0		OCT.2020
///				Lukas Possenig
/// ---------------------------------------

#ifndef Cupdate_h
#define Cupdate_h
#include <Arduino.h>

#define timeMultiplier 1000000 // µs - 1000 if milis() is used
#define idleTime 10000 // period time [µs] -> needs to be testet
#define pi 3.141592

class Cupdate {
  public:
    Cupdate(byte m1, byte m2, byte m3, byte m4, byte d1, byte d2, byte d3,byte d4,int wheelDia, int motorSteps,int x,int y);
    void setFrequency(int gf1, int gf2, int gf3, int gf4);
    void calcVelocity(double vx, double vy, double w);
    void run(); 
    void idle(byte Motor);
    int VelocityFactor;
    int wheelTurnParam;
    unsigned long t[4];          //periodic time in µs, delta time since last checkt in µs
    long tn[4];         //left time of current period;

  private:
    unsigned long ct;  //current Time
    unsigned long lt;  //last Time
    unsigned long dt;  //delta Time (time between calls)
    unsigned long g[4];
    byte m[4];         //defines the 4 motors(controllers)
    byte d[4];	       //defines the 4 dir pins for inverting ze movement.

    int wf[4];

};
#endif
