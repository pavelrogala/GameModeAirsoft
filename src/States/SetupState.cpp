#include "SetupState.h"
#include <Arduino.h>

void SetupState::onEnter(StateMachine* sm) {
    Serial.println("[SetupState] Entering setup state.");
    stage = MenuStage::TimeSelect;
    selectedTimeIndex = 0;
    selectedModeIndex = 0;
    sm->displayManager.init();
    sm->displayManager.print("WELCOME", 6, 1, 2);
    sm->displayManager.show();
    delay(1000);
    sm->displayManager.clear();
    displayCurrentOption(sm);
}

void SetupState::onUpdate(StateMachine* sm) {
    ButtonManager& up = sm->upButton;
    ButtonManager& down = sm->downButton;
    ButtonManager& confirm = sm->confirmButton;

    static bool confirmed = false;

    // Navigation
    if (up.justPressed() || down.justPressed()) {
        int direction = up.justPressed() ? -1 : 1;
    
        if (stage == MenuStage::TimeSelect) {
            selectedTimeIndex = (selectedTimeIndex + direction + 3) % 3;
        } else if (stage == MenuStage::ModeSelect) {
            selectedModeIndex = (selectedModeIndex + direction + 2) % 2;
        }
    
        displayCurrentOption(sm);
    }

    // Long press to confirm
    if (confirm.heldFor(1000) && !confirmed) {
        confirmed = true;

        if (stage == MenuStage::TimeSelect) {
            stage = MenuStage::ModeSelect;
            sm->displayManager.clear();
            displayCurrentOption(sm);
        } else if (stage == MenuStage::ModeSelect) {
            stage = MenuStage::Complete;
            sm->displayManager.clear();
            sm->displayManager.print("PRESS CONFIRM", 0, 0);
            sm->displayManager.print("TO START", 0, 1);

            // Store or apply settings here:
            sm->selectedGameTimeMin = timeOptions[selectedTimeIndex];
            sm->selectedGameMode = selectedModeIndex;
            Serial.print("Selected Time: ");
            Serial.print(sm->selectedGameTimeMin);
            Serial.println(" min");

            Serial.print("Selected Mode: ");
            Serial.println(sm->modeOptions[sm->selectedGameMode]);
        } else if (stage == MenuStage::Complete) {
            sm->changeState(sm->getGameState());
        }
    }

    if (confirm.justReleased()) {
        confirmed = false;  // reset long-press detection
    }
}

void SetupState::onExit() {
    Serial.println("[SetupState] Exiting setup state.");
}

void SetupState::displayCurrentOption(StateMachine* sm) {
    sm->displayManager.clear();

    if (stage == MenuStage::TimeSelect) {
        sm->displayManager.print("SELECT TIME (min):", 0, 0);
        sm->displayManager.print(String(timeOptions[selectedTimeIndex]), 0, 1);
    } else if (stage == MenuStage::ModeSelect) {
        sm->displayManager.print("SELECT GAME MODE:", 0, 0);
        sm->displayManager.print(sm->modeOptions[selectedModeIndex], 0, 1);
    }
}
