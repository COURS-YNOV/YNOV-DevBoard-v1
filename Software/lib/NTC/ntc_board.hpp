#ifndef NTC_BOARD_HPP
#define NTC_BOARD_HPP

#include <Arduino.h>
#include <stdint.h>

class NTC_Board {
public:
    static const int NTC_TABLE_SIZE = 33;
    static const int NTC_TABLE_STEP = 5;
    static const int NTC_MIN_TEMP = -50;

    NTC_Board(uint8_t pin);
    static int16_t NTC_Board_convertRawToTemperature(uint16_t raw);
    float NTC_launchTest();

private:
    uint8_t _pin;
};

#endif // NTC_BOARD_HPP