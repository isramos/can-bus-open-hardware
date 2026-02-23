# Teensy 4.x (FlexCAN)

CAN bus examples using the Teensy 4.x's built-in FlexCAN controllers.

## Hardware

- Teensy 4.0 or 4.1 (i.MX RT1062)
- External CAN transceiver (e.g. SN65HVD230, MCP2551)

The Teensy 4.x has 3 CAN controllers. CAN3 supports CAN FD.

## Library

- [tonton81/FlexCAN_T4](https://github.com/tonton81/FlexCAN_T4) — install via Arduino Library Manager

## Wiring (CAN1)

| Teensy 4.x | Transceiver |
|------------|-------------|
| Pin 22 (CRX1) | RX |
| Pin 23 (CTX1) | TX |
| 3.3V | VCC |
| GND | GND |

## Defaults

- **Baud rate**: 250 kbps
