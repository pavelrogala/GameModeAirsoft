#ifndef STATE_H
#define STATE_H

class StateMachine;  // forward declaration

class State {
public:
    virtual void onEnter(StateMachine* sm) = 0;
    virtual void onUpdate(StateMachine* sm) = 0;
    virtual void onExit() = 0;
    virtual ~State() = default;
};

#endif
