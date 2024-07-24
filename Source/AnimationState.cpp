#include "AnimationState.h"
#include "Character.h"

AnimationState::AnimationState()
{
}

AnimationState::~AnimationState()
{
}

void AnimationState::DrawImGui()
{
}

void AnimationState::Update(float elapsedTime)
{
	if (GetActor()->GetModel() != nullptr)
	{
		GetActor()->GetModel()->PlayAnimation(GetActor()->GetComponent<Character>()->GetAnimationState(), false);
	}
}