// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13


#include <SPI.h>
#include "mcp_can.h"


// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_250KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok rx! 2-22-18");
}


void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];
    unsigned long Time1 = 0;

//336540243;RX;0x1CFE5FFEx;8;0x00;0x01;0x02;0x03;0x04;0x05;0x06;0x07;

    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        Time1 = millis();
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned int canId = CAN.getCanId();
        Serial.print("@");
        //Serial.print(Time1);
        Serial.print("0x");
        Serial.print(canId, HEX);
        Serial.print(";");
        Serial.print(len);
   
        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(";0x");
            Serial.print(buf[i], HEX);
        }
        Serial.println();
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
