#include "StateMachine.h"
#include "States/SetupState.h"
#include "States/GameState.h"

State* StateMachine::getGameState() {
    return gameState;
}

State* StateMachine::getSetupState() {
    return setupState;
}

StateMachine::StateMachine()
    : displayManager(), keypadManager() {
        setupState = new SetupState();  // ← allocate your states
        gameState = new GameState();
    }

void StateMachine::begin() {
    changeState(setupState);
}

void StateMachine::update() {
    keypadManager.update();
    if (currentState) {
        currentState->onUpdate(this);
    }
}

void StateMachine::changeState(State* newState) {
    if (currentState) {
        currentState->onExit();
    }
    currentState = newState;
    if (currentState) {
        currentState->onEnter(this);
    }
}
