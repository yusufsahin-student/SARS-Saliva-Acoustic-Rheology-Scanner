#include <Arduino.h>

// ---- Serial connections ----
#define RQCM_RX_PIN PA10
#define RQCM_TX_PIN PA9
#define RQCM_RTS_PIN PB0

constexpr uint32_t PC_BAUD = 115200;
constexpr uint32_t RQCM_BAUD = 19200;

// ---- RQCM protocol ----
constexpr uint8_t RQCM_HEADER_1 = 0xFF;
constexpr uint8_t RQCM_HEADER_2 = 0xFE;
constexpr uint8_t RQCM_ADDRESS = 0x01;

constexpr uint8_t RQCM_CMD_AUTO_LOG = 0x01;
constexpr uint8_t RQCM_LOG_COUNTER_PERIOD_RESISTANCE = 0x07;

// ---- Measurement data ----
struct RqcmMeasurement {
  uint32_t timestampMs;
  uint8_t messageCounter;
  uint32_t periodCounts;
  uint16_t resistanceCounts;
  float frequencyHz;
  float resistanceOhm;
  bool valid;
};

HardwareSerial RqcmSerial(RQCM_RX_PIN, RQCM_TX_PIN);

RqcmMeasurement latestMeasurement;
bool measurementReady = false;

void rqcmStartAutoLogging() {
  //TODO: Implement the logic to send the command to start auto logging on the RQCM device.
}

void rqcmParserFeedByte(uint8_t byte) {
  //TODO: Implement the parser logic to handle incoming bytes and extract measurement data.
}

void printMeasurement(){
  //TODO: Implement the logic to print the latest measurement data to the Serial monitor.
}

void setup() {
  pinMode(RQCM_RTS_PIN, OUTPUT);
  digitalWrite(RQCM_RTS_PIN, HIGH);  // Permit RQCM transmission

  Serial.begin(PC_BAUD);             // PC / PlatformIO monitor
  RqcmSerial.begin(RQCM_BAUD, SERIAL_8N1);

  delay(500);

  Serial.println("RQCM reader starting");

  rqcmStartAutoLogging();
}

void loop() {
  while (RqcmSerial.available() > 0) {
    uint8_t receivedByte = RqcmSerial.read();
    rqcmParserFeedByte(receivedByte);
  }

  if (measurementReady) {
    printMeasurement(latestMeasurement);
    measurementReady = false;
  }
}