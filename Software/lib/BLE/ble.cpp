#include "ble.hpp"
#include <Wire.h>
#include "config.hpp"
#include "constants.hpp"

BLE::BLE(BLEServerCallbacks *serverCallback, BLECharacteristicCallbacks *BLECallbacks) {
    BLEDevice::init(BLE_DEVICE_NAME);
    BLEServer *server = BLEDevice::createServer();
    server->setCallbacks(serverCallback);  
    BLEService *service = server->createService("2A18");

    _writeCharacteristic = service->createCharacteristic(
        WRITE_CHARACTERISTIC,
        BLECharacteristic::PROPERTY_READ | 
        BLECharacteristic::PROPERTY_WRITE
    );
   
    _writeCharacteristic->setCallbacks(BLECallbacks);

    _notifyCharacteristic = service->createCharacteristic(
        NOTIFY_CHARACTERISTIC,
        BLECharacteristic::PROPERTY_NOTIFY
    );

    _notifyCharacteristic->addDescriptor(new BLE2902()); 
    service->start();

    BLEAdvertising *advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(service->getUUID());
    advertising->start();

    Serial.println("[initialize] BLE    : ✅");
    Serial.println("\t🕗 BLE started, waiting for client...");
}

// TODO refacto message (add command name ex: "Test CTN : 26.3°C, passed !"")
void BLE::BLE_sendAck(String command) {
    String message = "Test " + command + " passed !";
    _notifyCharacteristic->setValue(message.c_str());
    _notifyCharacteristic->notify();
}