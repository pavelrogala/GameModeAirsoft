#include "LoRaManager.h"
#include <SPI.h>
#include <LoRa.h>

#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 2


LoRaManager::LoRaManager(long frequency)
    : _frequency(frequency) {}

bool LoRaManager::begin() {
    LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

    if (!LoRa.begin(_frequency)) {
        Serial.println("LoRa init failed. Check your connections.");
        return false;
    }

    // Set sync word to ensure you're not receiving messages from other LoRa modules
    LoRa.setSyncWord(0xF3);

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
