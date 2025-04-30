#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../StateMachine.h"

class GameState : public State {
public:
    void onEnter(StateMachine* sm) override;
    void onUpdate(StateMachine* sm) override;
    void onExit() override;

private:
    enum class Team { None, A, B };

    struct ZoneControl {
        Team controller = Team::None;
    };

    unsigned long endTimeMs = 0;
    unsigned long lastUpdateMs = 0;
    unsigned long lastScoreUpdateMs = 0;
    int teamAPoints = 0;
    int teamBPoints = 0;
    ZoneControl zones[4];

    void handleSerialInput();
    void updatePoints(StateMachine* sm, unsigned long now);
    void updateTimer(StateMachine* sm, unsigned long now);
};

#endif
