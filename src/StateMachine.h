#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "DisplayManager.h"
#include "ButtonManager.h"
#include "KeypadManager.h"
#include "LoRaManager.h"
#include "State.h"
#include "Config.h"

class SetupState;
class GameState;

class StateMachine {
public:
    StateMachine();
    void begin();
    void update();
    void changeState(State* newState);
    DisplayManager displayManager;
    KeypadManager keypadManager;
    LoRaManager loraManager;

    State* getSetupState();
    State* getGameState();
    int selectedGameTimeMin = 0;
    int selectedGameMode = 0;
    const char* modeOptions[2] = {"Domination", "Flag Capture"};
private:
    State* currentState = nullptr;

    // internal state instances
    SetupState* setupState;
    GameState* gameState;
};

#endif
