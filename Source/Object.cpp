#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::Start()
{
}

void Object::Update(float elapsedTime)
{
    if (GetActor()->GetHealth() <= 0)
    {
        GetActor()->SetDeadFlag(true);
        ActorManager::Instance().Remove(GetActor());
    }
}

void Object::DrawImGui()
{
}
