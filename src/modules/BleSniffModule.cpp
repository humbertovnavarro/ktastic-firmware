#include "BleSniffModule.h"
#include "NimBLEDevice.h"
#include "MeshService.h"
#define BLE_SCAN_TIME 5

class MyAdvertisedDeviceCallbacks: public NimBLEAdvertisedDeviceCallbacks {
    void onResult(NimBLEAdvertisedDevice* advertisedDevice) {
    }
};


BleSniffModule::BleSniffModule() : SinglePortModule("Blesniff", meshtastic_PortNum_BLESNIFFER_APP), OSThread("blesniff"){}


meshtastic_MeshPacket *BleSniffModule::allocReply()
{
    meshtastic_MeshPacket *reply = new meshtastic_MeshPacket();
    return reply;
}

int32_t BleSniffModule::runOnce() {
    if(firstTime) {
        if(!NimBLEDevice::getInitialized()) {
            return 1000;
        }
        auto *server = NimBLEDevice::getServer();
        server->stopAdvertising();
        firstTime = false;
    }
    NimBLEScan *pScan = NimBLEDevice::getScan();
    pScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pScan->start(BLE_SCAN_TIME, false);
    NimBLEScanResults results = pScan->getResults();
    for (int i = 0; i < results.getCount(); i++) {
        NimBLEAdvertisedDevice device = results.getDevice(i);
        auto packet = allocDataPacket();
        memccpy(packet->decoded.payload.bytes, device.getPayload(), 0, device.getPayloadLength());
        service->sendToMesh(packet);
    }
    return 0;
}


BleSniffModule *bleSniffModule;
