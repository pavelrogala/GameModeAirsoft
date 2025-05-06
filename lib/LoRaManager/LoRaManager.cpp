#include "LoRaManager.h"
#include <SPI.h>
#include <LoRa.h>

#define LORA_SS 18
#define LORA_RST 14
#define LORA_DIO0 26

LoRaManager::LoRaManager(long frequency)
    : _frequency(frequency) {}

bool LoRaManager::begin() {
    LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

    if (!LoRa.begin(_frequency)) {
        Serial.println("LoRa init failed. Check your connections.");
        return false;
    }

    Serial.println("LoRa init succeeded.");
    return true;
}

void LoRaManager::sendMessage(const String& message) {
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket();
}

bool LoRaManager::receiveMessage(String& outMessage) {
    int packetSize = LoRa.parsePacket();
    if (packetSize == 0) {
        return false;
    }

    outMessage = "";
    while (LoRa.available()) {
        outMessage += (char)LoRa.read();
    }
    return true;
}

int LoRaManager::packetRssi() const {
    return LoRa.packetRssi();
}
