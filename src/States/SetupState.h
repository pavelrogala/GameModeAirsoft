#ifndef SETUP_STATE_H
#define SETUP_STATE_H

#include "../StateMachine.h"

enum class MenuStage { TimeSelect, ModeSelect, Complete };

class SetupState : public State {
    public:
        void onEnter(StateMachine* sm) override;
        void onUpdate(StateMachine* sm) override;
        void onExit() override;
    
    private:
        MenuStage stage = MenuStage::TimeSelect;
        int timeOptions[3] = {10, 15, 20};
        int selectedTimeIndex = 0;
    
        int selectedModeIndex = 0;
    
        void displayCurrentOption(StateMachine* sm);
    };

#endif
