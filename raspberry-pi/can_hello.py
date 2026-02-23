#!/usr/bin/env python3
"""
Raspberry Pi SocketCAN — CAN Send + Receive

Sends a heartbeat frame (ID 0x100) every 500ms and prints any received frames.
Uses the python-can library with the socketcan interface.

Setup: sudo ip link set can0 type can bitrate 250000 && sudo ip link set up can0
Install: pip install python-can
"""

import can
import time

CHANNEL = "can0"  # or "vcan0" for virtual testing

def main():
    bus = can.interface.Bus(channel=CHANNEL, interface="socketcan")
    print(f"SocketCAN ready on {CHANNEL}")

    counter = 0
    try:
        while True:
            # --- Send heartbeat ---
            uptime = int(time.monotonic()) & 0xFF
            data = bytes([counter & 0xFF, uptime])
            tx = can.Message(arbitration_id=0x100, data=data, is_extended_id=False)
            bus.send(tx)
            print(f"TX  0x{tx.arbitration_id:03X}  [{len(tx.data)}] {tx.data.hex(' ').upper()}")
            counter += 1

            # --- Receive (non-blocking) ---
            rx = bus.recv(timeout=0.1)
            if rx is not None:
                print(f"RX  0x{rx.arbitration_id:03X}  [{len(rx.data)}] {rx.data.hex(' ').upper()}")

            time.sleep(0.5)

    except KeyboardInterrupt:
        print("\nDone")
    finally:
        bus.shutdown()

if __name__ == "__main__":
    main()
