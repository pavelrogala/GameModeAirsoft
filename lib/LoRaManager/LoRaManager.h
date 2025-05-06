#ifndef LORA_MANAGER_H
#define LORA_MANAGER_H

#include <Arduino.h>

class LoRaManager {
public:
    LoRaManager(long frequency = 915E6);  // Default to 915 MHz
    bool begin();
    void sendMessage(const String& message);
    bool receiveMessage(String& outMessage);
    int packetRssi() const;

private:
    long _frequency;
};

#endif
