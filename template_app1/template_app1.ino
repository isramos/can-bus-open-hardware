/*

// demo: CAN-BUS Shield, receive data with interrupt mode
// when in interrupt mode, the data coming can't be too fast, must >20ms, or else you can use check mode
// loovee, 2014-6-13

Author: Igor Ramos

*/
#include <SPI.h>
#include "mcp_can.h"

MCP_CAN CAN(10);                                            // Set CS to pin 10


unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];

void setup()
{
    Serial.begin(115200);

START_INIT:

    if(CAN_OK == CAN.begin(CAN_250KBPS))                   // init can bus : baudrate = 500k
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

    attachInterrupt(0, MCP2515_ISR, FALLING); // start interrupt
}

void MCP2515_ISR()
{
     Flag_Recv = 1;
}

#define Desired_CAN_ID 0x000000C8
unsigned char SignalA=0;

void loop()
{

  // read sensors
  // read CAN
  // update loads
  // perform diag, update Serial (opt)
  // send CAN feedback

  if(Flag_Recv) {                   // check if get data

    Flag_Recv = 0;                // clear flag

    while (CAN_MSGAVAIL == CAN.checkReceive()) {
      INT32U CanID = CAN.getCanId();  // read CAN ID
      CAN.readMsgBuf(&len, buf);      // read data,  len: data length, buf: data buf

        if (CanID == 0xC8)
        {
          Serial.print(millis());
          Serial.print(" ID: 0x");
          Serial.print(CanID, HEX);
          Serial.print("\t");

           SignalA = buf[0];
           Serial.print(" Signal: ");
           Serial.print(SignalA);Serial.println("\t");
        }
        else
               Serial.println("."); //show some CAN msg received
      }
  }
  updatePWM(buf[0]);
}

void updatePWM(unsigned char val)
{
static unsigned long last=0;

  if ( (last-millis())>2000 )
  {
    last = millis();

   analogWrite(13,val);
  }


}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
