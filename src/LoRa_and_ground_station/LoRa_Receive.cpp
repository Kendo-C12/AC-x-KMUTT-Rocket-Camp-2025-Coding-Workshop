#include <Arduino.h>
#include <RadioLib.h>
#include <SPI.h>
#include "orbit_pin_def.h"

// SPI
SPIClass spi1(PIN_SPI_MOSI1, PIN_SPI_MISO1, PIN_SPI_SCK1);

SPISettings lora_spi_settings(4'000'000, MSBFIRST, SPI_MODE0);

// LoRa parameters
constexpr struct {
    float center_freq = 925.00'000f; // MHz
    float bandwidth = 125.f;         // kHz
    uint8_t spreading_factor = 9;    // SF: 6 to 12
    uint8_t coding_rate = 8;         // CR: 5 to 8
    uint8_t sync_word = 0x12;        // Private SX1262
    int8_t power = 22;               // up to 22 dBm for SX1262
    uint16_t preamble_length = 16;
} lora_params;

// Initialize LoRa module
SX1262 lora = new Module(LORA_NSS, LORA_DIO1, LORA_NRST, LORA_BUSY, spi1, lora_spi_settings);

// LoRa setup function
void loraSetup() {
    Serial.println("Initializing SX1262...");

    int16_t lora_state = lora.begin(
        lora_params.center_freq,
        lora_params.bandwidth,
        lora_params.spreading_factor,
        lora_params.coding_rate,
        lora_params.sync_word,
        lora_params.power,
        lora_params.preamble_length,
        0,
        0
    );

    // Check if initialization failed
    if (lora_state != RADIOLIB_ERR_NONE) {
        Serial.print("Begin failed, code: ");
        while (true) {
            Serial.println(lora_state);
            delay(1000);
        }
    }

    Serial.print("Lora Begin: ");
    Serial.println(lora_state);

    // configure module safely
    lora_state = lora.explicitHeader();
    Serial.print("ExplicitHeader: ");
    Serial.println(lora_state);

    lora_state = lora.setCRC(true);
    Serial.print("SetCRC: ");
    Serial.println(lora_state);

    lora_state = lora.autoLDRO();
    Serial.print("AutoLDRO: ");
    Serial.println(lora_state);

    if (lora_state == RADIOLIB_ERR_NONE) {
        Serial.println(F("success!"));
    } else {
        Serial.print(F("failed, code "));
        Serial.println(lora_state);
        while (true) { delay(10); }
    }
}

/* ================================================================================================== */

// LoRa State enum
enum class LoRaState {
    IDLE = 0,
    TRANSMITTING,
    RECEIVING
};

// Counters
uint32_t count = 0;   // Last received packet value
uint32_t t = 0;       // Packet loss counter

// Flags
bool receivedFlag = true;  // Packet received flag

// Packet received callback
void setFlag(void) {
    receivedFlag = true;
}

// Setup function
void setup() {
    delay(5000);            // Wait before starting

    Serial.begin(115200);
    Serial.println("Connected");

    spi1.begin();            // Initialize SPI bus
    Serial.println("SPI begin");

    delay(1000);

    Serial.print("Lora setup");
    loraSetup();
    Serial.print("success");

    // Set callback for received packets
    lora.setPacketReceivedAction(setFlag);

    // Start receiving
    lora.startReceive();
}

// Main loop
void loop() {
    // check if the flag is set and packet is available
    if (receivedFlag && lora.getPacketLength() > 0) {
        receivedFlag = false;

        // Read received data
        String str;
        int state = lora.readData(str);

        str.trim();          // remove whitespace/newlines
        int value = str.toInt();

        // Update packet loss counter
        if (value - count != 1 && value - count > 0) {
            t++;
        }
        count = value;

        lora.standby();       // put module in standby

        if (state == RADIOLIB_ERR_NONE) {
            // packet was successfully received
            Serial.println(F("[SX1262] Received packet!"));

            // print data of the packet
            Serial.print(F("[SX1262] Data:\t\t"));
            Serial.println(str);

            // print RSSI (Received Signal Strength Indicator)
            Serial.print(F("[SX1262] RSSI\t1:\t"));
            Serial.print(lora.getRSSI(1));
            Serial.println(F(" dBm"));

            Serial.print(F("[SX1262] RSSI:\t\t"));
            Serial.print(lora.getRSSI());
            Serial.println(F(" dBm"));

            // print SNR (Signal-to-Noise Ratio)
            Serial.print(F("[SX1262] SNR:\t\t"));
            Serial.print(lora.getSNR());
            Serial.println(F(" dB"));

            // print frequency error
            Serial.print(F("[SX1262] Frequency error:\t"));
            Serial.print(lora.getFrequencyError());
            Serial.println(F(" Hz"));

        } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
            // packet was received, but is malformed
            Serial.println(F("CRC error!"));
        } else {
            // some other error occurred
            Serial.print(F("failed, code "));
            Serial.println(state);
        }

        // print packet loss counter
        Serial.println(t);

        // go back to receive mode
        lora.startReceive();
    }
}
