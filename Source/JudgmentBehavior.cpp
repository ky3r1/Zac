#include "JudgmentBehavior.h"
#include "Enemy.h"
#include "Collision.h"
#include "Mathf.h"

bool BattleJudgment::Judgment()
{
	// �v���C���[����������
	if (Collision::SphereInPoint(GetActor()->GetPosition(), GetActor()->AddComponent<Enemy>()->GetSearchRange(), ActorManager::Instance().GetActor("Player")->GetPosition()))
	{
		return true;
	}
    return false;
}

bool AttackJudgment::Judgment()
{
	//�U���͈͓��ɂ��邩
	if (Mathf::Distance(GetActor()->GetPosition(), ActorManager::Instance().GetActor("Player")->GetPosition()) < GetActor()->GetComponent<Enemy>()->GetAttackRange())
	{
		// AttackNode�֑J�ڂł���
		return true;
	}
	return false;
}

bool SkillShotJudgment::Judgment()
{
	// hp�������ȉ��̎�skill�����\
	if (GetActor()->GetHealth() < GetActor()->GetMaxHealth()*0.5f)
	{
		// SkillNode�֑J�ڂł���
		return true;
	}
	return false;
}

bool WanderJudgment::Judgment()
{
	// �ړI�n�_�܂ł�XZ���ʂł̋�������
	DirectX::XMFLOAT3 position = GetActor()->GetPosition();
	DirectX::XMFLOAT3 targetPosition = ActorManager::Instance().GetActor("Player")->GetPosition();
	float vx = targetPosition.x - position.x;
	float vz = targetPosition.z - position.z;
	float distSq = vx * vx + vz * vz;

	// �ړI�n���痣��Ă���ꍇ
	float radius = GetActor()->GetRadius();
	if (distSq > radius * radius)
	{
		return true;
	}

	return false;
}

bool EscapeJudgment::Judgment()
{
	// hp�������ȉ��̎�skill�����\
	if (GetActor()->GetHealth() < GetActor()->GetMaxHealth() * 0.5f)
	{
		// SkillNode�֑J�ڂł���
		return true;
	}
	return false;
}
