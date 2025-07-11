#include "ntc_board.hpp"
#include <Wire.h>

NTC_Board::NTC_Board(uint8_t pin) : _pin(pin) {
    pinMode(_pin, ANALOG);
}

// Table de conversion pour la NTC AVX NB12K00103JBB
const uint16_t ntcTable[NTC_Board::NTC_TABLE_SIZE] = {
    3222, 3195, 3161, 3118, 3064, 2998, 2919, 2825, 2716, 2592,
    2455, 2306, 2147, 1983, 1816, 1650, 1489, 1335, 1190, 1056,
    934, 824, 725, 637, 560, 492, 432, 380, 335, 295,
    260, 230, 204
};

int16_t NTC_Board::NTC_Board_convertRawToTemperature(uint16_t regVal) {
    int left = 0;
    int right = NTC_TABLE_SIZE - 1;

    // Hors plage supérieure
    if (regVal > ntcTable[0]) {
        return (NTC_MIN_TEMP * 10);
    }

    // Hors plage inférieure
    if (regVal < ntcTable[NTC_TABLE_SIZE - 1]) {
        return ((NTC_MIN_TEMP + (NTC_TABLE_SIZE - 1) * NTC_TABLE_STEP) * 10);
    }

    // Recherche binaire
    while ((left + 1) != right) {
        int middle = (left + right) >> 1;
        if (ntcTable[middle] <= regVal) {
            right = middle;
        } else {
            left = middle;
        }
    }

    // Interpolation linéaire
    int16_t diff = ntcTable[left] - ntcTable[left + 1];
    int16_t dVal = ntcTable[left] - regVal;

    int8_t degTenths = (diff != 0) ? (dVal * NTC_TABLE_STEP * 10) / diff : 0;
    return ((NTC_MIN_TEMP + left * NTC_TABLE_STEP) * 10 + degTenths);
}

float NTC_Board::NTC_launchTest() {
    Serial.println("------------ NTC ------------");

    uint16_t _data_raw = analogRead(_pin);
    int16_t _temp_raw = NTC_Board::NTC_Board_convertRawToTemperature(_data_raw);
    float _temp = _temp_raw / 10.0f;

    Serial.printf("NTC: .2f °C", _temp);
    Serial.println();

    Serial.println("-----------------------------");
    
    return _temp;
}