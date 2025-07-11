#ifndef INA237_HPP
#define INA237_HPP

#include <Arduino.h>
#include <Wire.h>
#include "config.hpp"

// Énumération des registres de l'INA237
typedef enum {
    INA237_REG_CONFIG = 0x00,
    INA237_REG_ADC_CONFIG = 0x01,
    INA237_REG_CALIB = 0x02,
    INA237_REG_SHUNT_VOLT = 0x04,
    INA237_REG_BUS_VOLT = 0x05,
    INA237_REG_DIETEMP = 0x06,
    INA237_REG_CURRENT = 0x07,
    INA237_REG_POWER = 0x08,
    INA237_REG_ALERT = 0x0B,
    INA237_REG_SOVL = 0x0C,
    INA237_REG_SUVL = 0x0D,
    INA237_REG_BOVL = 0x0E,
    INA237_REG_BUVL = 0x0F,
    INA237_REG_TEMP_LIMIT = 0x10,
    INA237_REG_PWR_LIMIT = 0x11,
    INA237_REG_MANUFACTURER_ID = 0x3E,
    INA237_REG_COUNT
} INA237_reg_t;

class INA237 {
public:
    INA237(uint8_t i2c_addr);

    bool INA237_begin();
    bool INA237_reset();
    bool INA237_testINA237Connection();
    bool INA237_configure();
    bool INA237_calibrate();
    bool INA237_readBusVoltage(float& voltage_mV);
    bool INA237_readShuntVoltage(float& voltage_mV);
    bool INA237_readCurrent(float& current_mA);
    void INA237_launchTest();

private:
    uint8_t _i2c_addr;

    bool INA237_readRegister(INA237_reg_t reg, uint8_t* data, uint8_t size);
    bool INA237_writeRegister(INA237_reg_t reg, const uint8_t* data, uint8_t size);
};

#endif // INA237_HPP