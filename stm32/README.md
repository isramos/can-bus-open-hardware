# STM32 (bxCAN)

CAN bus examples using the STM32's built-in bxCAN peripheral.

## Hardware

- STM32F103 "Blue Pill" or any STM32 board with bxCAN
- External CAN transceiver (e.g. TJA1050, MCP2551)

## Library

- [STM32duino (Arduino_Core_STM32)](https://github.com/stm32duino/Arduino_Core_STM32)
- [pazi88/STM32_CAN](https://github.com/pazi88/STM32_CAN)

## Wiring (Blue Pill)

| STM32 | Transceiver |
|-------|-------------|
| PA12 (CAN TX) | TX |
| PA11 (CAN RX) | RX |
| 3.3V | VCC |
| GND | GND |

**Note:** On STM32F103 Blue Pill, CAN and USB share PA11/PA12. You cannot use USB serial and CAN simultaneously — use a separate USB-UART adapter for serial output.

## Defaults

- **Baud rate**: 250 kbps
