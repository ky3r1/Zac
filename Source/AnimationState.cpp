#include "AnimationState.h"
#include "Character.h"

AnimationState::AnimationState()
{
	old_animation.state = -1;
	old_animation.blend = -1;
    old_animation.stop = false;
	old_animation.loop = false;
}

AnimationState::~AnimationState()
{
}

void AnimationState::DrawImGui()
{
}

void AnimationState::Update(float elapsedTime)
{
	if (old_animation.state != GetActor()->GetAnimation().state)
	{
		if (old_animation.stop)
		{
			if (!GetActor()->GetModel()->IsPlayAnimation())
			{
				if (GetActor()->GetModel() != nullptr)
				{
					GetActor()->GetModel()->PlayAnimation(GetActor()->GetAnimation());
					old_animation = GetActor()->GetAnimation();
				}
			}
		}
		else
		{
			if (GetActor()->GetModel() != nullptr)
			{
				GetActor()->GetModel()->PlayAnimation(GetActor()->GetAnimation());
				old_animation = GetActor()->GetAnimation();
			}
		}
	}
}

bool AnimationState::IsAnimationStopFlg()
{
	if (GetActor()->GetAnimation().stop)
	{
		if (!GetActor()->GetModel()->IsPlayAnimation())
		{
			return true;
		}
	}
	else return true;
    return false;
}
