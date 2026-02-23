# Raspberry Pi (SocketCAN)

CAN bus examples using Linux SocketCAN on Raspberry Pi.

## Hardware

- Raspberry Pi 4 (BCM2711) or Pi 5 (BCM2712)
- CAN interface: SPI HAT (e.g. PiCAN2 with MCP2515) or USB adapter (e.g. CANable, PEAK)

The Pi has no built-in CAN controller — it relies on external hardware.

## Setup

### SPI HAT (MCP2515)

Add to `/boot/config.txt`:
```
dtoverlay=mcp2515-can0,oscillator=16000000,interrupt=25
```
Reboot, then:
```bash
sudo ip link set can0 type can bitrate 250000
sudo ip link set up can0
```

### USB Adapter (CANable, PEAK, etc.)

Most USB adapters appear as `can0` automatically via the `gs_usb` or `peak_usb` kernel module:
```bash
sudo ip link set can0 type can bitrate 250000
sudo ip link set up can0
```

### Virtual Interface (no hardware)

For testing without hardware:
```bash
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
```
Use `vcan0` instead of `can0` in the examples.

## Dependencies

```bash
sudo apt install can-utils
pip install python-can
```

## Defaults

- **Baud rate**: 250 kbps
