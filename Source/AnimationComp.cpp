#include "AnimationComp.h"
#include "Character.h"

AnimationComp::AnimationComp()
{
	old_animation.state = -1;
	old_animation.blend = -1;
	old_animation.loop = false;
}

AnimationComp::~AnimationComp()
{
}

void AnimationComp::DrawImGui()
{
}

void AnimationComp::Update(float elapsedTime)
{
	if (old_animation.state != GetActor()->GetAnimation().state)
	{
		//if (old_animation.stop)
		//{
			if (!GetActor()->GetModel()->IsPlayAnimation())
			{
				if (GetActor()->GetModel() != nullptr)
				{
					GetActor()->GetModel()->PlayAnimation(GetActor()->GetAnimation());
					old_animation = GetActor()->GetAnimation();
				}
			}
		//}
		//else
		//{
		//	if (GetActor()->GetModel() != nullptr)
		//	{
		//		GetActor()->GetModel()->PlayAnimation(GetActor()->GetAnimation());
		//		old_animation = GetActor()->GetAnimation();
		//	}
		//}
	}
}

bool AnimationComp::IsAnimationStopFlg()
{
	//if (GetActor()->GetAnimation().stop)
	//{
	//	if (!GetActor()->GetModel()->IsPlayAnimation())
	//	{
	//		return true;
	//	}
	//}
	//else return true;
    return false;
}
