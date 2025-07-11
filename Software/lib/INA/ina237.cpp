#include "ina237.hpp"
#include <Wire.h>
#include "config.hpp"

#define INA237_CURRENT_LSB_uA 6103.515625f // µA/LSB (pour 200 A et 0.5 mΩ)
//#define INA237_CURRENT_LSB_uA 6.103515625

INA237::INA237(uint8_t i2c_addr) : _i2c_addr(i2c_addr) {}

bool INA237::INA237_begin() {
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    return INA237_reset() && INA237_calibrate();
}

bool INA237::INA237_reset() {
    uint8_t data[2] = { 0x80, 0x00 };  // Reset command
    return INA237_writeRegister(INA237_REG_CONFIG, data, 2);
}

bool INA237::INA237_configure() {
    uint8_t config[2] = { 0x00, 0x10 };  // ADC range config
    return INA237_writeRegister(INA237_REG_CONFIG, config, 2);
}

bool INA237::INA237_calibrate() {
    /*
     * Calibration settings for INA237 based on hardware configuration:
     * 
     * Rshunt = 0.5 mΩ (PSR400ITQFF0L50)
     * Max expected current = 200 A
     * 
     * CURRENT_LSB = Max_Current / 2^15
     *             = 200 / 32768
     *             ≈ 0.0061035 A/LSB (or 6103.5 µA/LSB)
     * 
     * Calibration register value =
     *    819.2 × 10^6 × CURRENT_LSB × Rshunt
     *  = 819.2 × 10^6 × 0.0061035 × 0.0005
     *  ≈ 2500 (decimal) = 0x09C4 (hex)
     */
    const uint8_t cal[2] = { 0x09, 0xC4 }; // 2500 = 0x09C4
    return INA237_writeRegister(INA237_REG_CALIB, cal, 2);
}

bool INA237::INA237_readBusVoltage(float& voltage_mV) {
    uint8_t data[2];
    if (!INA237_readRegister(INA237_REG_BUS_VOLT, data, 2)) return false;
    uint16_t raw = (data[0] << 8) | data[1];
    voltage_mV = (raw * 3.125f);  // 3125 µV per LSB -> 3.125 mV
    //voltage_mV = (raw * 1.25f);  // 3125 µV per LSB -> 3.125 mV
    return true;
}

bool INA237::INA237_readShuntVoltage(float& voltage_mV) {
    uint8_t data[2];
    if (!INA237_readRegister(INA237_REG_SHUNT_VOLT, data, 2)) return false;

    int16_t raw = (data[0] << 8) | data[1];  // Signed 16-bit value
    voltage_mV = raw * 0.0025f;  // LSB = 1.25 µV → conversion en mV

    return true;
}

bool INA237::INA237_readCurrent(float& current_mA) {
    uint8_t data[2];
    if (!INA237_readRegister(INA237_REG_CURRENT, data, 2)) return false;
    int16_t raw = (data[0] << 8) | data[1];
    Serial.print("Raw courant reg: ");
    Serial.println(raw);
    current_mA = raw * (INA237_CURRENT_LSB_uA/1000);  // µA per LSB

    return true;
}

bool INA237::INA237_readRegister(INA237_reg_t reg, uint8_t* data, uint8_t size) {
    Wire.beginTransmission(_i2c_addr);
    Wire.write(static_cast<uint8_t>(reg));
    if (Wire.endTransmission(false) != 0) return false;

    uint8_t readBytes = Wire.requestFrom(_i2c_addr, size);
    if (readBytes != size) return false;

    for (uint8_t i = 0; i < size; ++i) {
        if (Wire.available()) data[i] = Wire.read();
        else return false;
    }
    return true;
}

bool INA237::INA237_writeRegister(INA237_reg_t reg, const uint8_t* data, uint8_t size) {
    Wire.beginTransmission(_i2c_addr);
    Wire.write(static_cast<uint8_t>(reg));
    for (uint8_t i = 0; i < size; ++i) {
        Wire.write(data[i]);
    }
    return Wire.endTransmission() == 0;
}

bool INA237::INA237_testINA237Connection() {
    uint8_t data[2];
    if (INA237_readRegister(INA237_REG_MANUFACTURER_ID, data, 2)) {
        uint16_t id = (data[0] << 8) | data[1];
        Serial.print("Manufacturer ID: 0x");
        Serial.println(id, HEX);

        if (id == 0x5449) {
            Serial.println("INA237 communication OK (TI detected)");
        } else {
            Serial.println("Unexpected Manufacturer ID");
        }
    } else {
        Serial.println("Failed to read Manufacturer ID");
    }
    return true; // TODO: ajouter des codes d'erreur si nécessaire
}

void INA237::INA237_launchTest() {
    Serial.println("------------ INA237 ------------");
    
    float _mes_voltage_VBATT = 0.0f;
    float _mes_shunt_current = 0.0f;
    float _mes_shunt_voltage = 0.0f;

    // VBATT
    INA237_readBusVoltage(_mes_voltage_VBATT);
    Serial.print("Voltage : ");
    Serial.print(_mes_voltage_VBATT);
    Serial.println(" mV");

    // Shunt Voltage
    INA237_readShuntVoltage(_mes_shunt_voltage);
    Serial.print("Shunt Voltage : ");
    Serial.print(_mes_shunt_voltage);
    Serial.println(" mV");

    // Shunt Current
    INA237_readCurrent(_mes_shunt_current);
    Serial.print("Current : ");
    Serial.print(_mes_shunt_current);
    Serial.println(" mA");

    Serial.println("--------------------------------");
}