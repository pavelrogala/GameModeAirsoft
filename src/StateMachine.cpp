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
    : confirmButton(Button::CONFIRM, true), upButton(Button::UP, true), downButton(Button::DOWN, true), displayManager(0x27, 20, 4) {
        setupState = new SetupState();  // ← allocate your states
        gameState = new GameState();
    }

void StateMachine::begin() {
    changeState(setupState);
}

void StateMachine::update() {
    confirmButton.update();
    upButton.update();
    downButton.update();
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
