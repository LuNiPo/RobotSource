#include "src/cupdate.h"


float xvel,yvel, omega;
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
boolean newData=false;

//X Y Q E
byte stepPin[4] ={54,60,36,26};
byte dirPin[4] = {55,61,34,28};
byte enPin[4] =  {38,56,30,24};

Cupdate updater(stepPin[0], stepPin[1], stepPin[3], stepPin[2], dirPin[0], dirPin[1], dirPin[3], dirPin[2], 110, 800, 270, 250);
//(stepPins 1-4;dirPins 1-4);Raddurchmesser;Schritte_pro_Umdrehung;Radmittenabstand x,y)

void setup(){
  Serial.begin(115200);
  for(byte i = 0; i<4; i++){
    pinMode(stepPin[i],OUTPUT); 
    pinMode(dirPin[i],OUTPUT); 
    pinMode(enPin[i],OUTPUT);
    digitalWrite(enPin[i],LOW);
    delay(1000);
  }	
}

void handleSerial();
void parseData();
void recvWithStartEndMarkers();

void loop(){
  recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        newData = false;
    }
  updater.run();
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}
  
void parseData() {
    char * strtokIndx; 

    strtokIndx = strtok(tempChars,",");      
    xvel = atof(strtokIndx);
 
    strtokIndx = strtok(NULL, ",");
    yvel = atof(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    omega = atof(strtokIndx);
    
    updater.calcVelocity(xvel, yvel, omega);
    Serial.println(xvel);
    Serial.println(yvel);
    Serial.println(omega);    
}  
  
