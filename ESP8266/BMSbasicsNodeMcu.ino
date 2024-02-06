#include "JbdBms.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D2, D1);
JbdBms myBms(&mySerial);

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup...");
  Serial.println("JBD bms driver");
  
}


void updateBMSData() {
    int attempts = 0;

    bool hasBmsData = false;
    while (!hasBmsData) {
        if (attempts > 8) break;
        Serial.println("Trying for bms data");
        hasBmsData = myBms.readBmsData();
        delay(200);
        attempts++;
    }
    if (hasBmsData) {
        Serial.println("### START: Basic BMS data ###");

        float chargePercentage = myBms.getChargePercentage();
        Serial.println("Charge percentage capacity: " + String(chargePercentage));
        

        float current = myBms.getCurrent();
        Serial.println("Current: " + String(current));
        

        float voltage = myBms.getVoltage();
        Serial.println("Voltage: " + String(voltage));
       

        uint16_t protectionState = myBms.getProtectionState();
        Serial.println("Protection state: " + String(protectionState));
    

        uint16_t cycleCount = (myBms.getCycle());
        Serial.println("Cycle: " + String(cycleCount));
 

        float tempInternal = myBms.getTemp1();
        Serial.println("Temp internal: " + String(tempInternal));
 

        float tempProbe1 = myBms.getTemp2();
        Serial.println("Temp probe 1: " + String(tempProbe1));


       float tempProbe2 = myBms.getTemp3();
       Serial.println("Temp probe 2: " + String(tempProbe2));
    

        Serial.println("### END: Basic BMS data ###");
    } else {
        Serial.println("Communication error while getting basic BMS data");
    }

    attempts = 0;

    bool hasPackData = false;
    while (!hasPackData) {
        if (attempts > 8) break;
        Serial.println("Trying for pack data");
        hasPackData = myBms.readPackData();
        delay(200);
        attempts++;
    }
    if (hasPackData) {
        Serial.println("### START: Battery cell data ###");

        packCellInfoStruct packInfo = myBms.getPackCellInfo();

        Serial.println("Number Of Cell: " + String(packInfo.NumOfCells));
       

        Serial.println("Low: " + String(packInfo.CellLow));
  

        Serial.println("High: " + String(packInfo.CellHigh));
 

        Serial.println("Diff: " + String(packInfo.CellDiff));
 

        Serial.println("Avg: " + String(packInfo.CellAvg));
     

        // go trough individual cells
        for (byte i = 0; i < packInfo.NumOfCells; i++) {
            Serial.println("Cell #" + String(i + 1) + ": " + packInfo.CellVoltage[i]);
        }

        Serial.println("### END: Battery cell data ###");
    } else {
        Serial.println("Communication error while getting cell data");
    }
}


void loop()
{

  Serial.println("Loop start");
  digitalWrite(LED_BUILTIN, LOW);

   updateBMSData();
   
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Loop end");

    delay(10000);
    
}
