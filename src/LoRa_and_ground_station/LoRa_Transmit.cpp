#include <Arduino.h>

#include <RadioLib.h>
#include <SPI.h>
#include "orbit_pin_def.h"
#include <EEPROM.h>

// SPI
SPIClass spi1(PIN_SPI_MOSI1, PIN_SPI_MISO1, PIN_SPI_SCK1);

SPISettings lora_spi_settings(4'000'000, MSBFIRST, SPI_MODE0);

constexpr struct
{
    float center_freq = 925.00'000f; // MHz
    float bandwidth = 125.f;         // kHz
    uint8_t spreading_factor = 9;    // SF: 6 to 12
    uint8_t coding_rate = 8;         // CR: 5 to 8
    uint8_t sync_word = 0x12;        // Private SX1262
    int8_t power = 22;               // up to 22 dBm for SX1262
    uint16_t preamble_length = 16;
} lora_params;

SX1262 lora = new Module(LORA_NSS, LORA_DIO1, LORA_NRST, LORA_BUSY, spi1, lora_spi_settings);


void loraSetup(){
  
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

  if(lora_state != RADIOLIB_ERR_NONE) {
    Serial.print("Begin failed, code: ");
    
    while(true){
        Serial.println(lora_state);
        delay(1000);
    };
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

// Lora State
enum class LoRaState
{
  IDLE = 0,
  TRANSMITTING,
  RECEIVING
};

int transmissionState = RADIOLIB_ERR_NONE;

bool transmitFlag = false;

volatile bool operationDone = false;

int state;
uint8_t t;
uint8_t last_ack;
uint8_t last_nack;
uint32_t lora_tx_end_time;
volatile LoRaState lora_state = LoRaState::IDLE;
String line;
String stateR = "STARTUP";
float lora_rssi;
volatile bool rx_flag = false;
volatile bool tx_flag = false;
unsigned long last_time;
unsigned long last_time_line;

void setFlag(void) {
  tx_flag = true;
}

void setup() {
  delay(5000);

  Serial.begin(115200);
  spi1.begin(); // initialize SPI bus

  delay(1000);

  loraSetup();

  lora.setPacketSentAction(setFlag);
  
  last_time = millis();
  last_time_line = millis();
  tx_flag = true;
}

void loop() {
  if(millis() - last_time > 2000){
    lora_state = LoRaState::TRANSMITTING;
    lora.startTransmit("Helle World");
    Serial.println("[TRANSMITTING...]"); 
    ++t;
    last_time = millis();
  }

  if(tx_flag){
    Serial.println("TRANSMITTING FINISH"); 
    tx_flag = false;
  }
}
