#include "JudgmentDerived.h"
#include "Actor.h"
//#include "Player.h"
#include "Mathf.h"


// BattleNodeに遷移できるか判定
bool BattleJudgment::Judgment()
{
	// プレイヤーが見つかるか
	if (owner->Search(ActorManager::Instance().GetPlayer()->GetPosition()))
	{
		return true;
	}
	return false;
}

// AttackNodeに遷移できるか判定
bool AttackJudgment::Judgment()
{
	if (owner->GetAttackFlag())
	{
		// AttackNodeへ遷移できる
		return true;
	}
	return false;
}

// AttackNodeに遷移できるか判定
bool ShortAttackJudgment::Judgment()
{
	// 対象との距離を算出
	DirectX::XMFLOAT3 position = owner->GetActor()->GetPosition();
	DirectX::XMFLOAT3 targetPosition = ActorManager::Instance().GetPlayer()->GetPosition();

	float vx = targetPosition.x - position.x;
	float vy = targetPosition.y - position.y;
	float vz = targetPosition.z - position.z;
	float dist = sqrtf(vx * vx + vy * vy + vz * vz);

	if (dist < owner->GetShortAttackRange())
	{
		// AttackNodeへ遷移できる
		return true;
	}
	return false;
}

bool LongAttackJudgment::Judgment()
{
	// 対象との距離を算出
	DirectX::XMFLOAT3 position = owner->GetActor()->GetPosition();
	DirectX::XMFLOAT3 targetPosition = ActorManager::Instance().GetPlayer()->GetPosition();

	float vx = targetPosition.x - position.x;
	float vy = targetPosition.y - position.y;
	float vz = targetPosition.z - position.z;
	float dist = sqrtf(vx * vx + vy * vy + vz * vz);

	if (dist < owner->GetLongAttackRange())
	{
		// AttackNodeへ遷移できる
		return true;
	}
	return false;
}





//// SkillNodeに遷移できるか判定
//bool SkillShotJudgment::Judgment()
//{
//	// hpが半分以下の時skill発動可能
//	int health = owner->GetActor()->GetHealth();
//	int baseHealth = static_cast<int>(owner->GetActor()->GetMaxHealth() * 0.8);
//	if (health < baseHealth)
//	{
//		// SkillNodeへ遷移できる
//		return true;
//	}
//	return false;
//}

// WanderNodeに遷移できるか判定
bool WanderJudgment::Judgment()
{
	// 目的地点までのXZ平面での距離判定
	DirectX::XMFLOAT3 position = owner->GetActor()->GetPosition();
	DirectX::XMFLOAT3 targetPosition = owner->GetTargetPosition();
	float vx = targetPosition.x - position.x;
	float vz = targetPosition.z - position.z;
	float distSq = vx * vx + vz * vz;

	// 目的地から離れている場合
	float radius = owner->GetActor()->GetRadius();
	if (distSq > radius * radius)
	{
		return true;
	}

	return false;
}

bool EscapeJudgment::Judgment()
{
	if (owner->GetActor()->GetComponent<Character>()->GetHealth() < (owner->GetActor()->GetComponent<Character>()->GetMaxHealth() * 0.5))
	{
		return true;
	}
	return false;
}