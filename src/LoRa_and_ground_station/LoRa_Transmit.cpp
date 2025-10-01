#include <Arduino.h>
#include <RadioLib.h>
#include <SPI.h>
#include "orbit_pin_def.h"

// SPI bus setup
SPIClass spi1(PIN_SPI_MOSI1, PIN_SPI_MISO1, PIN_SPI_SCK1);

// SPI settings for LoRa module
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

// Flag for transmit completion
volatile bool tx_flag = false;

// Callback when packet is sent
void setFlag(void) {
    tx_flag = true;  // signal that transmission is complete
}

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

    if (lora_state != RADIOLIB_ERR_NONE) {
        Serial.print("Begin failed, code: ");
        while (true) {
            Serial.println(lora_state);
            delay(1000);
        }
    }

    Serial.print("Lora Begin: ");
    Serial.println(lora_state);

    // Configure module safely
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

// Counters
uint32_t t = 0;  // Number of transmissions
unsigned long last_time;  // Timer for sending

void setup() {
    delay(5000);  // Wait before starting

    Serial.begin(115200);
    Serial.println("Connected");

    spi1.begin();  // Initialize SPI bus
    Serial.println("SPI begin");

    delay(1000);

    Serial.print("Lora setup");
    loraSetup();
    Serial.print("success");

    // Set callback for transmit completion
    lora.setPacketSentAction(setFlag);

    // Start first transmission
    tx_flag = true;
    last_time = millis();
}

void loop() {
    // Transmit every 2 seconds
    if (millis() - last_time > 2000) {
        // Transmit a string
        lora.startTransmit("Hello World");

        Serial.println("[TRANSMITTING...]");
        t++;  // increment transmission counter
        last_time = millis();
    }

    // Check if transmission finished
    if (tx_flag) {
        Serial.println("TRANSMITTING FINISH");
        tx_flag = false;  // reset flag
    }
}
