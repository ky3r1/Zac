#include "Character.h"

Character::Character()
{
    current_health = max_health;
}

void Character::Start()
{
}

void Character::Update(float elapsedTime)
{
}

void Character::DrawImGui()
{
    ImGui::SliderFloat("health", &current_health, 0.0f, max_health);
}

void Character::DrawDebug()
{
}
