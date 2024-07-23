#include "Character.h"

#define MAX_UNBEATABLE 2.0f*60

Character::Character()
{
    current_health = max_health;
}

void Character::Start()
{
}

void Character::Update(float elapsedTime)
{
    GetActor()->UpdateDelayTime(unbeatable_delay, MAX_UNBEATABLE);
}

void Character::DrawImGui()
{
    ImGui::SliderFloat("health", &current_health, 0.0f, max_health);
}

void Character::DrawDebug()
{
}

void Character::TakeDamage(float damage)
{
    current_health -= damage;
}
