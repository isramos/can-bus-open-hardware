/*
 * Teensy 4.x FlexCAN — CAN Send + Receive
 *
 * Sends a heartbeat frame (ID 0x100) every 500ms and prints any received frames.
 * Uses the FlexCAN_T4 library.
 *
 * Hardware: Teensy 4.0/4.1 + external CAN transceiver (e.g. SN65HVD230)
 * CAN1: RX pin 22, TX pin 23
 */

#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can1;
CAN_message_t msg;
uint8_t counter = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Teensy FlexCAN — starting");

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

  Serial.printf("TX  0x%03X  [%d] %02X %02X\n", msg.id, msg.len, msg.buf[0], msg.buf[1]);

  // --- Receive ---
  if (Can1.read(msg)) {
    Serial.printf("RX  0x%03X  [%d]", msg.id, msg.len);
    for (int i = 0; i < msg.len; i++)
      Serial.printf(" %02X", msg.buf[i]);
    Serial.println();
  }

  delay(500);
}
