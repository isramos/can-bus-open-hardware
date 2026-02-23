# ESP32 (TWAI)

CAN bus examples using the ESP32's built-in TWAI controller.

## Hardware

- ESP32 dev board (ESP32, ESP32-S3, or ESP32-C3)
- External CAN transceiver (e.g. SN65HVD230, TJA1051)

## Library

No external library needed — uses the built-in ESP-IDF TWAI driver via `driver/twai.h`.

## Wiring

| ESP32 | Transceiver |
|-------|-------------|
| GPIO 22 | TX |
| GPIO 21 | RX |
| 3.3V | VCC |
| GND | GND |

GPIO pins are configurable — 21/22 are common defaults.

## Defaults

- **Baud rate**: 250 kbps
