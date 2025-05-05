#include "GameState.h"
#include <Arduino.h>

void GameState::onEnter(StateMachine* sm) {
    Serial.println("[GameState] Entering game state.");

    unsigned long durationMs = sm->selectedGameTimeMin * 60UL * 1000UL;
    endTimeMs = millis() + durationMs;
    lastUpdateMs = 0;
    lastScoreUpdateMs = 0;
    teamAPoints = 0;
    teamBPoints = 0;

    unsigned long now = millis();
    for (auto& z : zones) {
        z.controller = Team::None;
        z.lastUpdateTime = now;
    }

    sm->displayManager.clear();
    sm->displayManager.print("3...", 0, 0, 1);
    sm->displayManager.show();
    delay(1000);
    sm->displayManager.clear();
    sm->displayManager.print("2..", 0, 0, 1);
    sm->displayManager.show();
    delay(1000);
    sm->displayManager.clear();
    sm->displayManager.print("1.", 0, 0, 1);
    sm->displayManager.show();
    delay(1000);
    sm->displayManager.clear();
    sm->displayManager.print("Team A: 0pts", 0, 0);
    sm->displayManager.print("Team B: 0pts", 0, 10);
    sm->displayManager.print("Time:", 0, 20);
    sm->displayManager.print("Mode:", 0, 30);
    sm->displayManager.print(sm->modeOptions[sm->selectedGameMode], 35, 30);
    sm->displayManager.show();
}

void GameState::onUpdate(StateMachine* sm) {
    unsigned long now = millis();
    handleSerialInput(now); // This will be replaced with LoRa or radio comms to accept messages from peripheral devices
    checkZoneTimeouts(now);
    updatePoints(sm, now);
    updateTimer(sm, now);
}

void GameState::handleSerialInput(unsigned long now) {
    if (!Serial.available()) return;

    String input = Serial.readStringUntil('\n');
    input.trim();

    int zoneIndex = -1;
    Team team = Team::None;

    int zonePos = input.indexOf("Zone:");
    if (zonePos != -1 && input.length() > zonePos + 5) {
        char z = input.charAt(zonePos + 5);
        if (z >= 'A' && z <= 'D') zoneIndex = z - 'A';
    }

    int teamPos = input.indexOf("Team:");
    if (teamPos != -1 && input.length() > teamPos + 5) {
        char t = input.charAt(teamPos + 5);
        if (t == 'A') team = Team::A;
        else if (t == 'B') team = Team::B;
    }

    if (zoneIndex != -1) {
        zones[zoneIndex].controller = team;
        zones[zoneIndex].lastUpdateTime = now;

        Serial.print("Zone ");
        Serial.print((char)('A' + zoneIndex));
        Serial.print(" now controlled by Team ");
        Serial.println(team == Team::A ? "A" : (team == Team::B ? "B" : "None"));
    }
}

void GameState::checkZoneTimeouts(unsigned long now) {
    for (int i = 0; i < 4; ++i) {
        if (zones[i].controller != Team::None &&
            now - zones[i].lastUpdateTime > ZoneUpdate::TimeoutMs) {
            Serial.print("Zone ");
            Serial.print((char)('A' + i));
            Serial.println(" lost due to inactivity.");
            zones[i].controller = Team::None;
        }
    }
}

void GameState::updatePoints(StateMachine* sm, unsigned long now) {
    if (now - lastScoreUpdateMs < ZoneUpdate::ScoreIntervalMs) return;
    lastScoreUpdateMs = now;

    int aZones = 0, bZones = 0;
    for (const auto& z : zones) {
        if (z.controller == Team::A) aZones++;
        else if (z.controller == Team::B) bZones++;
    }

    int aPoints = aZones * 10;
    int bPoints = bZones * 10;

    if (aZones > 1) aPoints += (aZones - 1) * 5;
    if (bZones > 1) bPoints += (bZones - 1) * 5;

    teamAPoints += aPoints;
    teamBPoints += bPoints;

    char bufferA[17], bufferB[17];
    snprintf(bufferA, sizeof(bufferA), "Team A: %dpts", teamAPoints);
    snprintf(bufferB, sizeof(bufferB), "Team B: %dpts", teamBPoints);
    sm->displayManager.print(bufferA, 0, 0);
    sm->displayManager.print(bufferB, 0, 1);
}

void GameState::updateTimer(StateMachine* sm, unsigned long now) {
    if (now - lastUpdateMs < 1000) return;
    lastUpdateMs = now;

    long remaining = (long)(endTimeMs - now);
    if (remaining < 0) remaining = 0;

    int seconds = (remaining / 1000) % 60;
    int minutes = (remaining / 1000) / 60;

    char buffer[17];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, seconds);
    sm->displayManager.clearSection(30, 20, 98, 10);
    sm->displayManager.print(buffer, 30, 20);
    sm->displayManager.show();
}

void GameState::onExit() {
    Serial.println("[GameState] Exiting game state.");
}
