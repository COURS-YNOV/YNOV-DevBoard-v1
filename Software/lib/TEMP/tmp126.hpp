#ifndef TMP126_HPP
#define TMP126_HPP

#include <Arduino.h>

class TMP126 {
public:
    explicit TMP126(uint8_t csPin);
    void TMP126_begin();
    bool TMP126_readTemperature(float& temp_in_C);
    float TMP126_launchTest();

private:
    uint8_t _csPin;

    void TMP126_select();
    void TMP126_deselect();
};

#endif // TMP126_HPP