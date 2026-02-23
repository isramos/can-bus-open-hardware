# CBA-CAN-TRS: CAN Bus over 3.5mm Audio Connector

A pinout specification for carrying CAN bus signals over standard 3.5mm TRS or TRRS audio connectors and cables.

Developed by [CAN Bus Academy](https://canbusacademy.com) for lab, classroom, and prototyping use.

## Pinout

| Contact | Signal | Description |
|---------|--------|-------------|
| TIP | CAN_H | CAN High (dominant-high) |
| RING | CAN_L | CAN Low (dominant-low) |
| SLEEVE | GND | Ground / signal reference |

```
        ┌───┐
  TIP   │   │  CAN_H
        ├───┤
  RING  │   │  CAN_L
        ├───┤
  SLEEVE│   │  GND
        └───┘
```

## Cable Compatibility

- **TRS (3-pole stereo)** — fully supported, recommended
- **TRRS (4-pole)** — compatible; RING2 is unused and shorts to SLEEVE (GND) with a TRS plug, which is harmless
- **TS (2-pole mono)** — not compatible; RING (CAN_L) would short to SLEEVE (GND)

### Why CAN_L is on RING (not RING2)

When using a TRRS jack, CAN_L must be assigned to the ring closest to the tip (RING1 / "Ring Tip"). When a TRS plug is inserted into a TRRS jack, the sleeve bridges RING2 and SLEEVE together. If CAN_L were on RING2, it would short to GND and kill the bus. With CAN_L on RING1, the TRS plug contacts it cleanly as its RING, and the RING2-to-SLEEVE short is harmless.

Use standard 3.5mm stereo (TRS) cables. Available everywhere, low cost.

## Rationale

Standard CAN bus connectors (DB9, OBD-II, M12) are bulky and expensive for lab/classroom environments where multiple nodes need quick connect/disconnect. The 3.5mm TRS connector provides:

- **Ubiquitous cables** — stereo audio cables work directly
- **Low cost** — connectors and cables under $1
- **Small footprint** — minimal PCB space
- **Hot-plug safe** — CAN transceivers tolerate the momentary pin-shorting that occurs during 3.5mm plug insertion. The bus sees a brief error frame at worst and recovers automatically per the CAN protocol.
- **No power on signal pins** — this spec intentionally carries only CAN signals and ground, no power. Power should be supplied separately to avoid damage from insertion shorts.

## Design Rules

1. **TIP = CAN_H, RING = CAN_L, SLEEVE = GND** — no exceptions
2. **Do not carry power** on any pin. The insertion wipe across contacts would short power to signal/ground.
3. **Termination** — provide a switchable 120 ohm termination resistor at bus endpoints, as with any CAN bus
4. **Cable length** — keep under 2 meters for 250 kbps; under 1 meter for 500 kbps. These are lab cables, not vehicle harnesses.

## DB9 Pinout Note

There are two competing DB9 CAN pinout conventions. Be aware when bridging between CBA-CAN-TRS and DB9:

| Pin | Seeed / Education | CiA DS102 (Industry) |
|-----|-------------------|----------------------|
| 2 | GND | CAN_L |
| 3 | CAN_H | GND |
| 5 | CAN_L | — |
| 7 | — | CAN_H |

The [CAN Adapter](can-adapter/) reference board uses the Seeed/education convention. Devices from Microchip (APGDT002), PEAK, and Kvaser use CiA DS102. **Do not cross-connect without verifying pinouts.**

## Reference Implementations

| Board | Description | Folder |
|-------|-------------|--------|
| [CAN Adapter](can-adapter/) | DB9 female to 3x CBA-CAN-TRS ports + switchable termination | `hardware/can-adapter/` |
| [CAN Hub](can-hub/) | 6x CBA-CAN-TRS ports, passive bus splitter | `hardware/can-hub/` |

## Version History

| Version | Date | Notes |
|---------|------|-------|
| 1.0 | November 2014 | Original boards fabricated via OSH Park |
| 1.1 | February 2026 | Spec formally documented and open-sourced |
