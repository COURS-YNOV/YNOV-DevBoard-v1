#ifndef BLE_HPP
#define BLE_HPP

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>
#include <stdint.h>

class BLE {
public:

    BLE(BLEServerCallbacks *serverCallback, BLECharacteristicCallbacks *BLECallbacks);
    void BLE_sendAck(String command);

private:
    BLECharacteristic *_writeCharacteristic;
    BLECharacteristic *_notifyCharacteristic;
};

#endif // BLE_HPP