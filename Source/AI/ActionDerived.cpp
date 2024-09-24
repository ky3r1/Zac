#include "ActionDerived.h"
#include "Enemy.h"
//#include "Player.h"
#include "Mathf.h"
#include "Actor.h"
#include "Movement.h"


// �U���s��
ActionBase::State NormalAction::Run(float elapsedTime)
{
	switch (step)
	{
	case 0:
		// �ڕW�n�_���v���C���[�ʒu�ɐݒ�
		owner->SetTargetPosition(ActorManager::Instance().GetPlayer()->GetPosition());
		// �A�j���[�V�����Đ�
		owner->GetActor()->GetModel()->PlayAnimation(Enemy::Attack01, false);
		step++;
		break;
	case 1:

		// �A�j���[�V�������I�����Ă���Ƃ�
		if (!owner->GetActor()->GetModel()->IsPlayAnimation())
		{
			owner->SetAttackFlag(false);
			ActorManager::Instance().GetPlayer()->GetComponent<Character>()->TakeDamage(1.0f);
			step = 0;
			// �U��������Ԃ�
			return ActionBase::State::Complete;
		}
		break;
	}
	// �X�L������Ԃ�
	return ActionBase::State::Run;
}
// �X�L���U���s��
ActionBase::State SkillAction::Run(float elapsedTime)
{
	switch (step)
	{
		case 0:
			// �ڕW�n�_���v���C���[�ʒu�ɐݒ�
			owner->SetTargetPosition(ActorManager::Instance().GetPlayer()->GetPosition());
			// �A�j���[�V�����Đ�
			owner->GetActor()->GetModel()->PlayAnimation(Enemy::Attack02, false);
			step++;
		case 1:
			// �A�j���[�V�������I�����Ă���Ƃ�
			if (!owner->GetActor()->GetModel()->IsPlayAnimation())
			{
				owner->SetAttackFlag(false);
				owner->ShotObject();
				step = 0;
				// �U��������Ԃ�
				return ActionBase::State::Complete;
			}
			break;
	}
	// �X�L������Ԃ�
	return ActionBase::State::Run;
}

// �p�j�s��
ActionBase::State WanderAction::Run(float elapsedTime)
{
	switch (step)
	{
	case 0:
		// �p�j���[�V�����ݒ�
		owner->GetActor()->GetModel()->PlayAnimation(Enemy::WalkFront, true);
        // �ڕW�n�_�ݒ�
        owner->SetTargetPosition({ static_cast<float>(rand() % 400 - 400 * 0.5f), owner->GetActor()->GetPosition().y, static_cast<float>(rand() % 400 - 400 * 0.5f) });
		step++;
		break;
	case 1:
		// �ړI�n�_�܂ł�XZ���ʂł̋�������
		DirectX::XMFLOAT3 position = owner->GetActor()->GetPosition();
		DirectX::XMFLOAT3 targetPosition = owner->GetTargetPosition();
		float vx = targetPosition.x - position.x;
		float vz = targetPosition.z - position.z;
		float distSq = vx * vx + vz * vz;

		// �ړI�n�֒�����
		float radius = owner->GetActor()->GetRadius();
		if (distSq < radius * radius)
		{
			step = 0;
			// �p�j������Ԃ�
			return ActionBase::State::Complete;
		}

		// �ړI�n�_�ֈړ�
		owner->GetActor()->GetComponent<Movement>()->MoveTarget(owner->GetTargetPosition(), elapsedTime);

		// �v���C���[���G����������
		if (owner->Search( ActorManager::Instance().GetPlayer()->GetPosition()))
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

// �ǐՍs��
ActionBase::State PursuitAction::Run(float elapsedTime)
{
	float runTimer = owner->GetRunTimer();
	switch (step)
	{
	case 0:
		// �ڕW�n�_���v���C���[�ʒu�ɐݒ�
		owner->SetTargetPosition(ActorManager::Instance().GetPlayer()->GetPosition());
		owner->SetRunTimer(Mathf::RandomRange(3.0f, 5.0f));
		owner->GetActor()->GetModel()->PlayAnimation(Enemy::Run, true);
		step++;
		break;
	case 1:
		runTimer -= elapsedTime;
		// �^�C�}�[�X�V
		owner->SetRunTimer(runTimer);
		// �ڕW�n�_���v���C���[�ʒu�ɐݒ�
		owner->SetTargetPosition(ActorManager::Instance().GetPlayer()->GetPosition());
		// �ړI�n�_�ֈړ�
		owner->GetActor()->GetComponent<Movement>()->MoveTarget(owner->GetTargetPosition(), elapsedTime);

		// �������U���͈͂ɂ���Ƃ�
		if (owner->GetAttackFlag() && Collision::SphereInPoint(owner->GetActor()->GetPosition(), owner->GetLongAttackRange(), ActorManager::Instance().GetPlayer()->GetPosition()))
		{
			step = 0;
			// �ǐՐ�����Ԃ�
			return ActionBase::State::Complete;
		}
		// �s�����Ԃ��߂�����
		if (runTimer <= 0.0f)
		{
			step = 0;
			// �ǐՎ��s��Ԃ�
			return ActionBase::State::Failed;
		}
		break;
	}
	return ActionBase::State::Run;
}

// �ҋ@�s��
ActionBase::State IdleAction::Run(float elapsedTime)
{
	float runTimer = owner->GetRunTimer();
	switch (step)
	{
	case 0:
		owner->SetRunTimer(Mathf::RandomRange(3.0f, 5.0f));
		owner->GetActor()->GetModel()->PlayAnimation(Enemy::IdleNormal, true);
		step++;
		break;
	case 1:
		runTimer -= elapsedTime;
		// �^�C�}�[�X�V
		owner->SetRunTimer(runTimer);

		// �ҋ@���Ԃ��߂�����
		if (runTimer <= 0.0f)
		{
			owner->SetTargetPosition({ static_cast<float>(rand() % 400 - 400*0.5f), owner->GetActor()->GetPosition().y, static_cast<float>(rand() % 400 - 400 * 0.5f) });
			step = 0;
			return ActionBase::State::Complete;
		}

		// �v���C���[����������
		if (owner->Search(ActorManager::Instance().GetPlayer()->GetPosition()))
		{
			step = 0;
			return ActionBase::State::Complete;
		}
		break;
	}
	return ActionBase::State::Run;
}

// �����s��
ActionBase::State LeaveAction::Run(float elapsedTime)
{
	DirectX::XMFLOAT3 targetPosition;
	switch (step)
	{
	case 0:
		// �ڕW�n�_���v���C���[�Ɛ����΂̃x�N�g���~5�̈ʒu�Ɏw��

		targetPosition=Mathf::Distance3(owner->GetActor()->GetPosition(), ActorManager::Instance().GetPlayer()->GetPosition());
		targetPosition.x *= -5;
		targetPosition.y *= -5;
		targetPosition.z *= -5;
		owner->SetTargetPosition(targetPosition);

		owner->GetActor()->GetModel()->PlayAnimation(Enemy::Run, true);
		step++;
		break;
	case 1:

		targetPosition = owner->GetTargetPosition();
		// �ړI�n�_�ֈړ�
		owner->GetActor()->GetComponent<Movement>()->MoveTarget(owner->GetTargetPosition(), elapsedTime);
		if (Collision::SphereInPoint(owner->GetActor()->GetPosition(),owner->GetActor()->GetRadius(),owner->GetTargetPosition()))
		{
			step = 0;
			return ActionBase::State::Complete;
		}

		break;
	}

	return ActionBase::State::Run;
}
// �񕜍s��
ActionBase::State RecoverAction::Run(float elapsedTime)
{
	switch (step)
	{
	case 0:
		owner->GetActor()->GetModel()->PlayAnimation(Enemy::Taunt, true);
		step++;
		break;
	case 1:
		if (!owner->GetActor()->GetModel()->IsPlayAnimation())
		{
			owner->GetActor()->GetComponent<Character>()->SetHealth(owner->GetActor()->GetComponent<Character>()->GetMaxHealth());
			step = 0;
			return ActionBase::State::Complete;
		}
		break;
	}

	return ActionBase::State::Run;

}