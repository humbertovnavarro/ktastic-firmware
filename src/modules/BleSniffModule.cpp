#include "BleSniffModule.h"
#include "NimBLEDevice.h"
#include "MeshService.h"
#define BLE_SCAN_TIME 5

class MyAdvertisedDeviceCallbacks: public NimBLEAdvertisedDeviceCallbacks {
    void onResult(NimBLEAdvertisedDevice* advertisedDevice) {
        Serial.printf("Advertised Device: %s\n", advertisedDevice->toString().c_str());
    }
};


BleSniffModule::BleSniffModule() : SinglePortModule("blesniff", meshtastic_PortNum_BLESNIFFER_APP), OSThread("blesniff"){}


meshtastic_MeshPacket *BleSniffModule::allocReply()
{
    meshtastic_MeshPacket *reply = new meshtastic_MeshPacket();
    return reply;
}

int scanCount = 0;
NimBLEScan *pScan;

int32_t BleSniffModule::runOnce() {
    if (firstTime) {
        NimBLEDevice::deleteAllBonds();
        pScan = NimBLEDevice::getScan();
        firstTime = false;
        pScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
        pScan->setActiveScan(true);
        pScan->setInterval(1000);
        pScan->setWindow(1000);
        pScan->setDuplicateFilter(true);
        setStartDelay();
    }
    if (scanCount >= 3) {
        pScan->clearDuplicateCache();
    }
    pScan->start(BLE_SCAN_TIME, true);
    NimBLEScanResults results = pScan->getResults();
    for (int i = 0; i < results.getCount(); i++) {
        NimBLEAdvertisedDevice device = results.getDevice(i);
        auto reply = allocDataPacket();
        reply->decoded.payload.size = device.toString().length();
        memcpy(reply->decoded.payload.bytes, device.toString().c_str(), reply->decoded.payload.size);
        service->sendToMesh(reply);
    }
    pScan->clearResults();
    scanCount++;
    return 1000;
}


BleSniffModule *bleSniffModule;
