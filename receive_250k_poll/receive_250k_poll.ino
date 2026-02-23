/*
   demo: CAN-BUS Shield, receive data with check mode
   for each message show time stamp in ms, CAN ID, and message content

    Author: Igor Ramos Dec-1-2014
*/


#include <SPI.h>
#include "mcp_can.h"


unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];


MCP_CAN CAN(10);                                            // Set CS to pin 10

void setup()
{
    Serial.begin(115200);

START_INIT:

    if(CAN_OK == CAN.begin(CAN_250KBPS))                   // init can bus : baudrate = 250k
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


void loop()
{
    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        INT32U CanID = CAN.getCanId();  // read CAN ID

	CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        Serial.print(millis());
        Serial.print(" ID: 0x");
        Serial.print(CanID, HEX);
        Serial.print("\t");

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(buf[i]);Serial.print("\t");
        }
        Serial.println();
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
