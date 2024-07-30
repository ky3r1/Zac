#include "StateMachine.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::Update(float elapsedTime)
{
    if (current_state != nullptr)
    {
        //switch (state)
        //{
        //StartState:
        //    current_state->Start(elapsedTime);
        //    state = UpdateState;
        //    break;
        //UpdateState:
        //    current_state->Update(elapsedTime);
        //    if (next_state != nullptr)state = EndState;
        //    break;
        //EndState:
        //    current_state->End(elapsedTime);
        //    state = StartState;
        //    current_state = next_state;
        //    next_state = nullptr;
        //    break;
        //}
    }
}
