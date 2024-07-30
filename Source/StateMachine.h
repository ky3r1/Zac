#pragma once
#include "Component.h"
#include "StateBase.h"

class StateMachine :public Component
{
public:
    StateMachine();
    ~StateMachine();

    //���O�擾
    const char* GetName()const override { return "StateMachine"; }

    void Update(float elapsedTime)override;
public:
    void ChangeState(StateBase* state) { next_state = state; }
private:
    StateBase* current_state = nullptr;
    StateBase* next_state = nullptr;
    enum
    {
        StartState,
        UpdateState,
        EndState,
    };
    int state = StartState;
};