#include "JudgmentDerived.h"
#include "Actor.h"
//#include "Player.h"
#include "Mathf.h"


// BattleNode�ɑJ�ڂł��邩����
bool BattleJudgment::Judgment()
{
	// �v���C���[�������邩
	if (owner->Search(ActorManager::Instance().GetPlayer()->GetPosition()))
	{
		return true;
	}
	return false;
}

// AttackNode�ɑJ�ڂł��邩����
bool AttackJudgment::Judgment()
{
	if (owner->GetAttackFlag())
	{
		// AttackNode�֑J�ڂł���
		return true;
	}
	return false;
}

// AttackNode�ɑJ�ڂł��邩����
bool ShortAttackJudgment::Judgment()
{
	// �ΏۂƂ̋������Z�o
	DirectX::XMFLOAT3 position = owner->GetActor()->GetPosition();
	DirectX::XMFLOAT3 targetPosition = ActorManager::Instance().GetPlayer()->GetPosition();

	float vx = targetPosition.x - position.x;
	float vy = targetPosition.y - position.y;
	float vz = targetPosition.z - position.z;
	float dist = sqrtf(vx * vx + vy * vy + vz * vz);

	if (dist < owner->GetShortAttackRange())
	{
		// AttackNode�֑J�ڂł���
		return true;
	}
	return false;
}

bool LongAttackJudgment::Judgment()
{
	// �ΏۂƂ̋������Z�o
	DirectX::XMFLOAT3 position = owner->GetActor()->GetPosition();
	DirectX::XMFLOAT3 targetPosition = ActorManager::Instance().GetPlayer()->GetPosition();

	float vx = targetPosition.x - position.x;
	float vy = targetPosition.y - position.y;
	float vz = targetPosition.z - position.z;
	float dist = sqrtf(vx * vx + vy * vy + vz * vz);

	if (dist < owner->GetLongAttackRange())
	{
		// AttackNode�֑J�ڂł���
		return true;
	}
	return false;
}





//// SkillNode�ɑJ�ڂł��邩����
//bool SkillShotJudgment::Judgment()
//{
//	// hp�������ȉ��̎�skill�����\
//	int health = owner->GetActor()->GetHealth();
//	int baseHealth = static_cast<int>(owner->GetActor()->GetMaxHealth() * 0.8);
//	if (health < baseHealth)
//	{
//		// SkillNode�֑J�ڂł���
//		return true;
//	}
//	return false;
//}

// WanderNode�ɑJ�ڂł��邩����
bool WanderJudgment::Judgment()
{
	// �ړI�n�_�܂ł�XZ���ʂł̋�������
	DirectX::XMFLOAT3 position = owner->GetActor()->GetPosition();
	DirectX::XMFLOAT3 targetPosition = owner->GetTargetPosition();
	float vx = targetPosition.x - position.x;
	float vz = targetPosition.z - position.z;
	float distSq = vx * vx + vz * vz;

	// �ړI�n���痣��Ă���ꍇ
	float radius = owner->GetActor()->GetRadius();
	if (distSq > radius * radius)
	{
		return true;
	}

	return false;
}

bool EscapeJudgment::Judgment()
{
	if (owner->GetActor()->GetHealth() < (owner->GetActor()->GetMaxHealth() * 0.5))
	{
		return true;
	}
	return false;
}