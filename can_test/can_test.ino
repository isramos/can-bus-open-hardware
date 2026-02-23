/**
 * CAN Workbench — Arduino Heartbeat + Loopback
 *
 * Seeed CAN-BUS Shield v1.2 (MCP2515 + MCP2551)
 *
 * Behavior:
 *   - Serial heartbeat every 1s (always running, proves Arduino is alive)
 *   - CAN TX heartbeat every 500ms: ID 0x123 with counter + uptime
 *   - CAN RX: prints any received frame and echoes it back on ID 0x124 (loopback)
 *   - Serial commands: 'r' = reset MCP2515, 's' = status dump
 */

#include <mcp_can.h>
#include <SPI.h>

const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN);

unsigned long lastCanTx = 0;
unsigned long lastSerialHb = 0;
unsigned long txCount = 0;
unsigned long txOkCount = 0;
unsigned long txFailCount = 0;
unsigned long rxCount = 0;
bool canReady = false;

void initCan() {
  Serial.print("[CAN] Init MCP2515 CS=");
  Serial.print(SPI_CS_PIN);
  Serial.print("... ");

  if (CAN.begin(MCP_ANY, CAN_250KBPS, MCP_16MHZ) == CAN_OK) {
    CAN.setMode(MCP_NORMAL);
    canReady = true;
    Serial.println("OK @ 250kbps NORMAL mode");
  } else {
    canReady = false;
    Serial.println("FAILED");
  }
}

void printStatus() {
  Serial.println("--- STATUS ---");
  Serial.print("  CAN:     ");
  Serial.println(canReady ? "READY" : "NOT READY");
  Serial.print("  TX ok:   "); Serial.println(txOkCount);
  Serial.print("  TX fail: "); Serial.println(txFailCount);
  Serial.print("  RX:      "); Serial.println(rxCount);
  Serial.print("  Uptime:  "); Serial.print(millis() / 1000); Serial.println("s");
  Serial.println("--------------");
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println("=== CAN Workbench v2 ===");
  Serial.println("[SER] Heartbeat every 1s");
  Serial.println("[CAN] TX 0x123 every 500ms, loopback on 0x124");
  Serial.println("[CMD] 'r'=reset CAN, 's'=status");
  Serial.println();

  initCan();
  Serial.println();
}

void loop() {
  // --- Serial heartbeat every 1s (always works, even without CAN) ---
  if (millis() - lastSerialHb >= 1000) {
    lastSerialHb = millis();
    Serial.print("[HB] t=");
    Serial.print(millis() / 1000);
    Serial.print("s can=");
    Serial.print(canReady ? "OK" : "NO");
    Serial.print(" tx=");
    Serial.print(txOkCount);
    Serial.print("/");
    Serial.print(txOkCount + txFailCount);
    Serial.print(" rx=");
    Serial.println(rxCount);
  }

  // --- Serial commands ---
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'r' || c == 'R') {
      Serial.println("[CMD] Resetting MCP2515...");
      canReady = false;
      initCan();
    }
    if (c == 's' || c == 'S') {
      printStatus();
    }
  }

  // --- CAN TX heartbeat every 500ms ---
  if (canReady && millis() - lastCanTx >= 500) {
    lastCanTx = millis();
    txCount++;

    unsigned char txData[8];
    txData[0] = (txCount >> 8) & 0xFF;
    txData[1] = txCount & 0xFF;
    txData[2] = 0xCA;
    txData[3] = 0xFE;
    txData[4] = (millis() >> 24) & 0xFF;
    txData[5] = (millis() >> 16) & 0xFF;
    txData[6] = (millis() >> 8) & 0xFF;
    txData[7] = millis() & 0xFF;

    byte result = CAN.sendMsgBuf(0x123, 0, 8, txData);

    if (result == CAN_OK) {
      txOkCount++;
      Serial.print("[TX] #");
      Serial.print(txCount);
      Serial.print(" OK  0x123 [");
    } else {
      txFailCount++;
      Serial.print("[TX] #");
      Serial.print(txCount);
      Serial.print(" FAIL(");
      Serial.print(result);
      Serial.print(") 0x123 [");
    }
    for (int i = 0; i < 8; i++) {
      if (txData[i] < 0x10) Serial.print("0");
      Serial.print(txData[i], HEX);
      if (i < 7) Serial.print(" ");
    }
    Serial.println("]");
  }

  // --- CAN RX: print + loopback echo ---
  if (canReady && CAN_MSGAVAIL == CAN.checkReceive()) {
    unsigned long rxId;
    unsigned char len = 0;
    unsigned char buf[8];

    CAN.readMsgBuf(&rxId, &len, buf);
    rxCount++;

    Serial.print("[RX] #");
    Serial.print(rxCount);
    Serial.print(" 0x");
    Serial.print(rxId, HEX);
    Serial.print(" DLC=");
    Serial.print(len);
    Serial.print(" [");
    for (int i = 0; i < len; i++) {
      if (buf[i] < 0x10) Serial.print("0");
      Serial.print(buf[i], HEX);
      if (i < len - 1) Serial.print(" ");
    }
    Serial.println("]");

    // Echo back on ID 0x124 (loopback)
    byte echoResult = CAN.sendMsgBuf(0x124, 0, len, buf);
    if (echoResult == CAN_OK) {
      Serial.println("[ECHO] -> 0x124 OK");
    } else {
      Serial.print("[ECHO] -> 0x124 FAIL(");
      Serial.print(echoResult);
      Serial.println(")");
    }
  }
}
