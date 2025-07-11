#include "tmp126.hpp"
#include <SPI.h>
#include "config.hpp"

TMP126::TMP126(uint8_t csPin) : _csPin(csPin) {}

void TMP126::TMP126_begin() {
    pinMode(_csPin, OUTPUT);
    TMP126_deselect();  // Ensure CS is high
    SPI.begin(PIN_SPI_SCK, PIN_SPI_MISO, PIN_SPI_MOSI, _csPin);
}

void TMP126::TMP126_select() {
    digitalWrite(_csPin, LOW);
    delayMicroseconds(1);
}

void TMP126::TMP126_deselect() {
    digitalWrite(_csPin, HIGH);
}

bool TMP126::TMP126_readTemperature(float& temp_in_C) {
    uint8_t tx_buf[2] = { 0x01, TMP126_REG_TEMP_RESULT };
    uint8_t rx_buf[2] = { 0 };

    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    TMP126_select();

    SPI.transfer(tx_buf[0]);
    SPI.transfer(tx_buf[1]);

    rx_buf[0] = SPI.transfer(0xFF);
    rx_buf[1] = SPI.transfer(0xFF);

    TMP126_deselect();
    SPI.endTransaction();

    // Debug
    Serial.printf("TMP126 raw: 0x%02X%02X\n", rx_buf[0], rx_buf[1]);

    // Combine and shift
    uint16_t raw = (rx_buf[0] << 8) | rx_buf[1];
    raw >>= 2;

    // Cast to signed 14-bit
    if (raw & 0x2000) {  // if sign bit is set
        raw |= 0xC000;   // extend sign (2 MSBs)
    }

    int16_t signed_temp = static_cast<int16_t>(raw);
    temp_in_C = signed_temp * 0.03125f;

    return true;
}

float TMP126::TMP126_launchTest() {
    Serial.println("------------ TMP126 ------------");

    float _mes_tmp126_temp;
    if (TMP126_readTemperature(_mes_tmp126_temp)) {
        Serial.print("Température : ");
        Serial.print(_mes_tmp126_temp);
        Serial.println(" °C");
        Serial.println("--------------------------------");
    }
    
    Serial.print("--------------------------------");
    return _mes_tmp126_temp;
}