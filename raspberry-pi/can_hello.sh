#!/bin/bash
# Raspberry Pi SocketCAN — CAN Send + Receive (using can-utils)
#
# Setup: sudo ip link set can0 type can bitrate 250000 && sudo ip link set up can0
# Install: sudo apt install can-utils

IFACE="${1:-can0}"

echo "SocketCAN ready on $IFACE"
echo "Sending test frame..."

# Send a single frame: ID 0x100, data DEADBEEF
cansend "$IFACE" 100#DEADBEEF

echo "Listening for frames (Ctrl+C to stop)..."

# Dump all received frames
candump "$IFACE"
