///	---------------------------------------
///   Controller Update = Cupdate Libary
///		  Version	1.0		OCT.2020
///				Lukas Possenig
/// ---------------------------------------

#include "cupdate.h"
#include <Arduino.h>

Cupdate::Cupdate(byte m1, byte m2, byte m3, byte m4,byte d1, byte d2, byte d3,byte d4,int wheelDia, int motorSteps,int x,int y) {
  this->m[0] = m1;
  this->m[1] = m2;
  this->m[2] = m3;
  this->m[3] = m4;

  this->d[0] = d1;
  this->d[1] = d2;
  this->d[2] = d3;
  this->d[3] = d4;

  VelocityFactor = motorSteps * 1000/(pi * wheelDia);
  wheelTurnParam = (x+y)/2;
}
void Cupdate::calcVelocity(double vx, double vy, double w){

	//calc wheel frequencies
	wf[0]=(vx - vy - wheelTurnParam*w)*VelocityFactor;
	wf[1]=(vx + vy + wheelTurnParam*w)*VelocityFactor;
	wf[2]=(vx + vy - wheelTurnParam*w)*VelocityFactor;
	wf[3]=(vx - vy + wheelTurnParam*w)*VelocityFactor;	

	Serial.println("Radfrequenz n. invert :");

	//check if frequency is negativ and set Dir Pin
	for (int i=0;i<4;i++){
// invert 2 Outputs because wheels mouted "backwards" on robot
		if(i % 2) wf[i]=-wf[i]; 
//sum serious debugging shit:
//---------------------------	
		Serial.print(i);
		if(wf[i]<0){
			wf[i]=-wf[i];
			digitalWrite(d[i],LOW);
			Serial.print("reseset pin ");
			Serial.println(d[i]);
		}
		else{
			digitalWrite(d[i],HIGH);
			Serial.print("set pin ");
			Serial.println(d[i]);
		}
	}
	//setFrequency(wf[0],wf[1],wf[2],wf[3]);
	setFrequency(wf[0],wf[1],wf[2],wf[3]);
}
// HIER BEI ÜBERGABE JE NACH RADNUMMERIERUNG REIHENFOLGE TAUSCHEN
void Cupdate::setFrequency(int gf1, int gf2, int gf3, int gf4) {

	//Set intervalltime [µs]
	unsigned long g[4]={(unsigned long) gf1,(unsigned long) gf2,(unsigned long) gf3,(unsigned long) gf4};

  for(int i = 0; i < 4; i++) {

	if(g[i]>0){
 		t[i] = timeMultiplier/g[i];
	}
	else{
		t[i]=-1;
	}
    tn[i] = t[i];

  }
}

void Cupdate::run() {
  ct = micros();
  if (ct > lt) dt = ct - lt; 		//prevent error at bufferoverflow
  for (int i = 0; i < 4; i++) { 	//check all 4 drivers
    tn[i] = tn[i] - dt;  		//decrease actual period time by delta t
    if (tn[i] <= 0) {          		//reset actual periode if T is reached
      digitalWrite(m[i], HIGH);
      tn[i] =+ t[i];
    }
    else if (tn[i] <= t[i] / 2) { 	//set output low for 0.5T > tn
      digitalWrite(m[i], LOW);

    }
    else if (tn[i] <= t[i]) {
      digitalWrite(m[i], HIGH); 	//set output high for tn > 0.5T
    }
	//yield();
  }
  lt=ct;
}



void Cupdate::idle(byte motor){
	// IMPLEMENT IDLE HERE
}
