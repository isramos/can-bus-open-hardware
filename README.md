# Arduino CAN Bus Examples

Example sketches for the **MCP2515 CAN controller** (Seeed CAN-BUS Shield v1.2 and compatible boards).

Created to support classes at [canbusacademy.com](https://canbusacademy.com).

## Hardware

- Seeed CAN-BUS Shield v1.2 (MCP2515 + MCP2551)
- Arduino Uno / Mega (or compatible)

## Library Dependency

These sketches use the `MCP_CAN` library. Install one of:

- [Seeed-Studio/CAN_BUS_Shield](https://github.com/Seeed-Studio/CAN_BUS_Shield)
- [coryjfowler/MCP_CAN_lib](https://github.com/coryjfowler/MCP_CAN_lib)

Both expose the same `MCP_CAN` API and are interchangeable.

## Examples

| Sketch | Description |
|--------|-------------|
| `can_bus_simulator` | Serial-based CAN bus simulator (no hardware needed) |
| `can_test` | Heartbeat TX + loopback RX diagnostic tool |
| `receive_250k_int` | Interrupt-driven receive at 250 kbps |
| `receive_250k_poll` | Polled receive at 250 kbps |
| `receive_check_cs10_250k_for_inteleryV1` | Receive with CS pin 10 (Intelery v1 board) |
| `send_11bit_250k_incr` | Send 11-bit frames with incrementing data |
| `template_app1` | Starter template for new sketches |

## Defaults

- **Baud rate**: 250 kbps
- **Crystal**: 16 MHz
- **CS pin**: 9 (some sketches use 10)
