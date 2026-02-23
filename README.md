# CAN Bus Open Hardware

Example code and drivers for open-source CAN bus hardware platforms.

Created to support classes at [canbusacademy.com](https://canbusacademy.com).

## Platforms

| Platform | MCU | CAN | Notes |
|----------|-----|-----|-------|
| [Arduino](arduino/) | ATmega | MCP2515 (external, SPI) | Needs shield or breakout |
| [ESP32](esp32/) | ESP32 | TWAI (built-in) | Needs external transceiver |
| [STM32](stm32/) | STM32F103+ | bxCAN (built-in) | CAN shares pins with USB on Blue Pill |
| [Teensy 4.x](teensy/) | i.MX RT1062 | FlexCAN (built-in, 3 buses) | Needs external transceiver |
| [Raspberry Pi](raspberry-pi/) | BCM2711/2712 | socketcan (kernel) | Via SPI HAT or USB adapter |

## Getting Started

Each platform folder has its own README with wiring, library dependencies, and defaults.

Every platform includes a simple send + receive example that sends a heartbeat frame and prints received frames.

All examples default to **250 kbps**.

## Hardware

Open-source PCB designs for CAN bus lab equipment, using the [CBA-CAN-TRS](hardware/CBA-CAN-TRS.md) connector spec (CAN bus over 3.5mm TRS audio jacks).

| Board | Description | Folder |
|-------|-------------|--------|
| [CAN Adapter](hardware/can-adapter/) | DB9 to 3x TRS breakout + termination | `hardware/can-adapter/` |
| [CAN Hub](hardware/can-hub/) | 6-port TRS passive CAN bus hub | `hardware/can-hub/` |
