#include "BleSniffModule.h"
#include "NimBLEDevice.h"
#include "MeshService.h"
#define BLE_SCAN_TIME 5

class MyAdvertisedDeviceCallbacks: public NimBLEAdvertisedDeviceCallbacks {
    void onResult(NimBLEAdvertisedDevice* advertisedDevice) {
        Serial.printf("Advertised Device: %s\n", advertisedDevice->toString().c_str());
    }
};


meshtastic_MeshPacket *BleSniffModule::allocReply()
{
    meshtastic_MeshPacket *reply = new meshtastic_MeshPacket();
    return reply;
}

int32_t BleSniffModule::runOnce() {
    NimBLEScan *pScan = NimBLEDevice::getScan();
    pScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pScan->setActiveScan(true);
    pScan->setInterval(100);
    pScan->setWindow(99);
    pScan->start(BLE_SCAN_TIME, false);
    NimBLEScanResults results = pScan->getResults();
    for (int i = 0; i < results.getCount(); i++) {
        NimBLEAdvertisedDevice device = results.getDevice(i);
        Serial.printf("Advertised Device: %s\n", device.toString().c_str());
        auto reply = allocDataPacket();
        reply->decoded.payload.size = device.toString().length();
        memcpy(reply->decoded.payload.bytes, device.toString().c_str(), reply->decoded.payload.size);
        service->sendToMesh(reply);
    }
    return BLE_SCAN_TIME;
}