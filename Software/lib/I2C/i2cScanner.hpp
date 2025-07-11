#ifndef I2C_SCANNER_HPP
#define I2C_SCANNER_HPP

#include <Arduino.h>
#include <stdint.h>

class I2C_SCANNER {
public:
    I2C_SCANNER();
    String I2C_SCANNER_scanDevices();
    String I2C_SCANNER_launchTest();

private:
    // None
};

#endif // I2C_SCANNER_HPP