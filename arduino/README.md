# Arduino (MCP2515)

Example sketches for **MCP2515-based CAN shields** (Seeed, Intelery, or any MCP2515 + MCP2551/MCP2562 board).

## Hardware

- Any MCP2515-based CAN shield or breakout board
- Arduino Uno / Mega (or compatible)

## Library Dependency

These sketches use the `MCP_CAN` library. Install one of:

- [Seeed-Studio/CAN_BUS_Shield](https://github.com/Seeed-Studio/CAN_BUS_Shield)
- [coryjfowler/MCP_CAN_lib](https://github.com/coryjfowler/MCP_CAN_lib)

Both expose the same `MCP_CAN` API and are interchangeable.

## Examples

| Sketch | Description |
|--------|-------------|
| `can_test` | Heartbeat TX + loopback RX + status + serial commands |
| `send_11bit_250k_incr` | Send 11-bit frames with incrementing data |
| `can_bus_simulator` | Serial-based CAN bus simulator (no hardware needed) |

## Defaults

- **Baud rate**: 250 kbps
- **Crystal**: 16 MHz
- **CS pin**: 10
