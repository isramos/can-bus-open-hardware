/*
 * STM32 bxCAN — CAN Send + Receive
 *
 * Sends a heartbeat frame (ID 0x100) every 500ms and prints any received frames.
 * Uses the STM32_CAN library with STM32duino core.
 *
 * Hardware: STM32F103 Blue Pill + external CAN transceiver (e.g. TJA1050)
 * CAN TX: PA12, CAN RX: PA11
 */

#include <STM32_CAN.h>

STM32_CAN Can1(CAN1);
CAN_message_t msg;
uint8_t counter = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("STM32 bxCAN — starting");

  Can1.begin();
  Can1.setBaudRate(250000);

  Serial.println("CAN ready");
}

void loop() {
  // --- Send heartbeat ---
  msg.id = 0x100;
  msg.len = 2;
  msg.buf[0] = counter++;
  msg.buf[1] = (uint8_t)(millis() / 1000);
  Can1.write(msg);

  Serial.printf("TX  0x%03lX  [%d] %02X %02X\n", msg.id, msg.len, msg.buf[0], msg.buf[1]);

  // --- Receive ---
  if (Can1.read(msg)) {
    Serial.printf("RX  0x%03lX  [%d]", msg.id, msg.len);
    for (int i = 0; i < msg.len; i++)
      Serial.printf(" %02X", msg.buf[i]);
    Serial.println();
  }

  delay(500);
}
