#include "ActionBehavior.h"
#include "Mathf.h"
#include "VsCollision.h"
#include "Movement.h"
#include "Collision.h"
#include "Enemy.h"

ActionBase::State NormalAction::Run(float elapsedTime)
{
	switch (step)
	{
	case 0:
		// �A�j���[�V�����Đ�
		GetActor()->GetModel()->PlayAnimation(0, true);
		step++;
		break;
	case 1:

		// �A�j���[�V�������I�����Ă���Ƃ�
		if (!GetActor()->GetModel()->IsPlayAnimation())
		{
			step = 0;
			// �U��������Ԃ�
			return ActionBase::State::Complete;
		}
		break;
	}
	// �U������Ԃ�
	return ActionBase::State::Run;
}

ActionBase::State SkillAction::Run(float elapsedTime)
{
	switch (step)
	{
	case 0:
		// �A�j���[�V�����Đ�
		GetActor()->GetModel()->PlayAnimation(0, true);
		step++;
	case 1:
		// �A�j���[�V�������I�����Ă���Ƃ�
		if (!GetActor()->GetModel()->IsPlayAnimation())
		{
			step = 0;
			// �U��������Ԃ�
			return ActionBase::State::Complete;
		}
		break;
	}
	// �X�L������Ԃ�
	return ActionBase::State::Run;
}

ActionBase::State WanderAction::Run(float elapsedTime)
{
	switch (step)
	{
	case 0:
		// �p�j���[�V�����ݒ�
		GetActor()->GetModel()->PlayAnimation(0, true);
		step++;
		break;
	case 1:
		if (GetActor()->GetComponent<VsCollision>()->SphereVsSphere(ActorType::Player, nullptr))
		{
			step = 0;
			// �p�j������Ԃ�
			return ActionBase::State::Complete;
		}

		// �ړI�n�_�ֈړ�
		GetActor()->GetComponent<Movement>()->MoveTarget(ActorManager::Instance().GetActor("Player")->GetPosition(), elapsedTime);

		// �v���C���[���G����������
		if (Collision::SphereInPoint(GetActor()->GetPosition(), GetActor()->AddComponent<Enemy>()->GetSearchRange(), ActorManager::Instance().GetActor("Player")->GetPosition()))
		{
			step = 0;
			// �p�j������Ԃ�
			return ActionBase::State::Complete;
		}
		break;
	}
	// ���s��
	return ActionBase::State::Run;
}

ActionBase::State PursuitAction::Run(float elapsedTime)
{
	static float runtimer = rand() % 20 * 60.0f;
	switch (step)
	{
	case 0:
		runtimer = rand() % 20 * 60.0f;
		// �p�j���[�V�����ݒ�
		GetActor()->GetModel()->PlayAnimation(0, true);
		step++;
		break;
	case 1:
		if (GetActor()->GetComponent<VsCollision>()->SphereVsSphere(ActorType::Player, nullptr))
		{
			step = 0;
			// �p�j������Ԃ�
			return ActionBase::State::Complete;
		}
		DirectX::XMFLOAT3 rndp = {
			rand() % 50 - 25 + static_cast<float>(rand() % 1000) / 10000,
			rand() % 50 - 25 + static_cast<float>(rand() % 1000) / 10000,
			rand() % 50 - 25 + static_cast<float>(rand() % 1000) / 10000 };

		// �ړI�n�_�ֈړ�
		GetActor()->GetComponent<Movement>()->MoveTarget(rndp, elapsedTime);

		// �v���C���[���G����������
		if (Collision::SphereInPoint(GetActor()->GetPosition(), GetActor()->AddComponent<Enemy>()->GetSearchRange(), ActorManager::Instance().GetActor("Player")->GetPosition()))
		{
			step = 0;
			// �ǐՐ�����Ԃ�
			return ActionBase::State::Complete;
		}
		else if(runtimer<0)
		{
			step = 0;
			// �ǐՎ��s��Ԃ�
			return ActionBase::State::Failed;
		}
		runtimer--;
		break;
	}
	// ���s��
	return ActionBase::State::Run;
}

ActionBase::State IdleAction::Run(float elapsedTime)
{
	static float runtimer = rand() % 20 * 60.0f;
	switch (step)
	{
	case 0:
		GetActor()->GetModel()->PlayAnimation(0, true);
		step++;
		break;
	case 1:
		// �ҋ@���Ԃ��߂�����
		if (runtimer <= 0.0f)
		{
			DirectX::XMFLOAT3 rndp = {
			rand() % 50 - 25 + static_cast<float>(rand() % 1000) / 10000,
			rand() % 50 - 25 + static_cast<float>(rand() % 1000) / 10000,
			rand() % 50 - 25 + static_cast<float>(rand() % 1000) / 10000 };
			// �ړI�n�_�ֈړ�
			GetActor()->GetComponent<Movement>()->MoveTarget(rndp, elapsedTime);
			step = 0;
			return ActionBase::State::Complete;
		}

		// �v���C���[����������
		if (Collision::SphereInPoint(GetActor()->GetPosition(), GetActor()->AddComponent<Enemy>()->GetSearchRange(), ActorManager::Instance().GetActor("Player")->GetPosition()))
		{
			step = 0;
			return ActionBase::State::Complete;
		}
		break;
	}
	runtimer--;
	return ActionBase::State::Run;
}

ActionBase::State LeaveAction::Run(float elapsedTime)
{
	DirectX::XMFLOAT3 targetPosition;
	switch (step)
	{
	case 0:
		// �ڕW�n�_���v���C���[�Ɛ����΂̃x�N�g���~5�̈ʒu�Ɏw��
		DirectX::XMFLOAT3 tp=Mathf::Distance3(ActorManager::Instance().GetActor("Player")->GetPosition(), GetActor()->GetPosition());
		tp.x *= -5;
        tp.y *= -5;
        tp.z *= -5;
		GetActor()->GetModel()->PlayAnimation(0, true);
		step++;
		break;
	case 1:

		targetPosition = tp;
		// �ړI�n�_�ֈړ�
		GetActor()->GetComponent<Movement>()->MoveTarget(targetPosition, elapsedTime);

		//DirectX::XMFLOAT3 position = owner->GetPosition();
		//targetPosition = owner->GetTargetPosition();

		//float vx = targetPosition.x - position.x;
		//float vz = targetPosition.z - position.z;
		//float distSq = vx * vx + vz * vz;


		// �ړI�n�֒�����
		if (Collision::PointInsideCircle(targetPosition, GetActor()->GetPosition(), GetActor()->GetRadius()))
		{
			step = 0;
			return ActionBase::State::Complete;
		}

		break;
	}

	return ActionBase::State::Run;
}

ActionBase::State RecoverAction::Run(float elapsedTime)
{
	switch (step)
	{
	case 0:
		GetActor()->GetModel()->PlayAnimation(0, true);
		step++;
		break;
	case 1:
		if (!GetActor()->GetModel()->IsPlayAnimation())
		{
			GetActor()->SetHealth(GetActor()->GetMaxHealth());
			step = 0;
			return ActionBase::State::Complete;
		}
		break;
	}

	return ActionBase::State::Run;
}
