#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

namespace Button {
    constexpr uint8_t CONFIRM = 6;
    constexpr uint8_t UP = 2;
    constexpr uint8_t DOWN = 3;
}

namespace LED {
    constexpr uint8_t STATUS = 6;
    constexpr uint8_t ERROR = 7;
}

namespace GameConfig {
    constexpr unsigned long GAME_DURATION_MS = 600000; // 10 minutes
}

namespace ZoneUpdate {
    constexpr unsigned long ScoreIntervalMs = 5000;
    constexpr unsigned long TimeoutMs = 120000;
}

#endif
