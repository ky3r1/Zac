#include "JudgmentDerived.h"
#include "Actor.h"
//#include "Player.h"
#include "Mathf.h"


// BattleNode‚É‘JˆÚ‚Å‚«‚é‚©”»’è
bool BattleJudgment::Judgment()
{
	// ƒvƒŒƒCƒ„[‚ªŒ©‚Â‚©‚é‚©
	if (owner->Search(ActorManager::Instance().GetPlayer()->GetPosition()))
	{
		return true;
	}
	return false;
}

// AttackNode‚É‘JˆÚ‚Å‚«‚é‚©”»’è
bool AttackJudgment::Judgment()
{
	if (owner->GetAttackFlag())
	{
		// AttackNode‚Ö‘JˆÚ‚Å‚«‚é
		return true;
	}
	return false;
}

// AttackNode‚É‘JˆÚ‚Å‚«‚é‚©”»’è
bool ShortAttackJudgment::Judgment()
{
	// ‘ÎÛ‚Æ‚Ì‹——£‚ðŽZo
	DirectX::XMFLOAT3 position = owner->GetActor()->GetPosition();
	DirectX::XMFLOAT3 targetPosition = ActorManager::Instance().GetPlayer()->GetPosition();

	float vx = targetPosition.x - position.x;
	float vy = targetPosition.y - position.y;
	float vz = targetPosition.z - position.z;
	float dist = sqrtf(vx * vx + vy * vy + vz * vz);

	if (dist < owner->GetShortAttackRange())
	{
		// AttackNode‚Ö‘JˆÚ‚Å‚«‚é
		return true;
	}
	return false;
}

bool LongAttackJudgment::Judgment()
{
	// ‘ÎÛ‚Æ‚Ì‹——£‚ðŽZo
	DirectX::XMFLOAT3 position = owner->GetActor()->GetPosition();
	DirectX::XMFLOAT3 targetPosition = ActorManager::Instance().GetPlayer()->GetPosition();

	float vx = targetPosition.x - position.x;
	float vy = targetPosition.y - position.y;
	float vz = targetPosition.z - position.z;
	float dist = sqrtf(vx * vx + vy * vy + vz * vz);

	if (dist < owner->GetLongAttackRange())
	{
		// AttackNode‚Ö‘JˆÚ‚Å‚«‚é
		return true;
	}
	return false;
}





//// SkillNode‚É‘JˆÚ‚Å‚«‚é‚©”»’è
//bool SkillShotJudgment::Judgment()
//{
//	// hp‚ª”¼•ªˆÈ‰º‚ÌŽžskill”­“®‰Â”\
//	int health = owner->GetActor()->GetHealth();
//	int baseHealth = static_cast<int>(owner->GetActor()->GetMaxHealth() * 0.8);
//	if (health < baseHealth)
//	{
//		// SkillNode‚Ö‘JˆÚ‚Å‚«‚é
//		return true;
//	}
//	return false;
//}

// WanderNode‚É‘JˆÚ‚Å‚«‚é‚©”»’è
bool WanderJudgment::Judgment()
{
	// –Ú“I’n“_‚Ü‚Å‚ÌXZ•½–Ê‚Å‚Ì‹——£”»’è
	DirectX::XMFLOAT3 position = owner->GetActor()->GetPosition();
	DirectX::XMFLOAT3 targetPosition = owner->GetTargetPosition();
	float vx = targetPosition.x - position.x;
	float vz = targetPosition.z - position.z;
	float distSq = vx * vx + vz * vz;

	// –Ú“I’n‚©‚ç—£‚ê‚Ä‚¢‚éê‡
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