/*
 * ESP32 TWAI — CAN Send + Receive
 *
 * Sends a heartbeat frame (ID 0x100) every 500ms and prints any received frames.
 * Uses the built-in ESP-IDF TWAI driver — no external library needed.
 *
 * Hardware: ESP32 + external CAN transceiver (e.g. SN65HVD230)
 * TX: GPIO 22, RX: GPIO 21
 */

#include <Arduino.h>
#include "driver/twai.h"

#define TX_PIN GPIO_NUM_22
#define RX_PIN GPIO_NUM_21

uint8_t counter = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 TWAI CAN — starting");

  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(TX_PIN, RX_PIN, TWAI_MODE_NORMAL);
  twai_timing_config_t t_config = TWAI_TIMING_CONFIG_250KBITS();
  twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

  if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK) {
    Serial.println("TWAI driver install failed");
    return;
  }
  if (twai_start() != ESP_OK) {
    Serial.println("TWAI start failed");
    return;
  }

  Serial.println("TWAI ready");
}

void loop() {
  // --- Send heartbeat ---
  twai_message_t tx_msg;
  tx_msg.identifier = 0x100;
  tx_msg.data_length_code = 2;
  tx_msg.flags = 0;
  tx_msg.data[0] = counter++;
  tx_msg.data[1] = (uint8_t)(millis() / 1000);

  if (twai_transmit(&tx_msg, pdMS_TO_TICKS(10)) == ESP_OK) {
    Serial.printf("TX  0x%03lX  [%d]", tx_msg.identifier, tx_msg.data_length_code);
    for (int i = 0; i < tx_msg.data_length_code; i++)
      Serial.printf(" %02X", tx_msg.data[i]);
    Serial.println();
  }

  // --- Receive ---
  twai_message_t rx_msg;
  if (twai_receive(&rx_msg, pdMS_TO_TICKS(100)) == ESP_OK) {
    Serial.printf("RX  0x%03lX  [%d]", rx_msg.identifier, rx_msg.data_length_code);
    for (int i = 0; i < rx_msg.data_length_code; i++)
      Serial.printf(" %02X", rx_msg.data[i]);
    Serial.println();
  }

  delay(500);
}
