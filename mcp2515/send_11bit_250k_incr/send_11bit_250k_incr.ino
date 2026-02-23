/*
  demo: CAN-BUS Shield, send data

  Author: Igor Ramos

*/
#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN(10);                                      // Set CS to pin 10

void setup()
{
    Serial.begin(115200);

START_INIT:

    if(CAN_OK == CAN.begin(CAN_250KBPS))                   // init can bus
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
}

 // example of 29-bit CAN ID
 // CAN.sendMsgBuf(0x18FFB53F, 1, 8, stmp);  // 0 to 0x1FFFFFFF

unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};
unsigned int var=0;

void loop()
{
   Serial.println("Transmitting CAN");

    // send data:  id = 0x00, standrad frame, data len = 8, stmp: data buf
    CAN.sendMsgBuf( 200, 0, 8, stmp); // 11bit:  0x0000 to 0x7FF

    delay(100);                       // send data per 100ms

    stmp[0]++; //from 0 to 255, then roll over


}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
