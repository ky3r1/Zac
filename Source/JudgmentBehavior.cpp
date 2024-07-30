#include "JudgmentBehavior.h"
#include "Enemy.h"
#include "Collision.h"
#include "Mathf.h"

bool BattleJudgment::Judgment()
{
	// プレイヤーを見つけた時
	if (Collision::SphereInPoint(GetActor()->GetPosition(), GetActor()->AddComponent<Enemy>()->GetSearchRange(), ActorManager::Instance().GetActor("Player")->GetPosition()))
	{
		return true;
	}
    return false;
}

bool AttackJudgment::Judgment()
{
	//攻撃範囲内にいるか
	if (Mathf::Distance(GetActor()->GetPosition(), ActorManager::Instance().GetActor("Player")->GetPosition()) < GetActor()->GetComponent<Enemy>()->GetAttackRange())
	{
		// AttackNodeへ遷移できる
		return true;
	}
	return false;
}

bool SkillShotJudgment::Judgment()
{
	// hpが半分以下の時skill発動可能
	if (GetActor()->GetHealth() < GetActor()->GetMaxHealth()*0.5f)
	{
		// SkillNodeへ遷移できる
		return true;
	}
	return false;
}

bool WanderJudgment::Judgment()
{
	// 目的地点までのXZ平面での距離判定
	DirectX::XMFLOAT3 position = GetActor()->GetPosition();
	DirectX::XMFLOAT3 targetPosition = ActorManager::Instance().GetActor("Player")->GetPosition();
	float vx = targetPosition.x - position.x;
	float vz = targetPosition.z - position.z;
	float distSq = vx * vx + vz * vz;

	// 目的地から離れている場合
	float radius = GetActor()->GetRadius();
	if (distSq > radius * radius)
	{
		return true;
	}

	return false;
}

bool EscapeJudgment::Judgment()
{
	// hpが半分以下の時skill発動可能
	if (GetActor()->GetHealth() < GetActor()->GetMaxHealth() * 0.5f)
	{
		// SkillNodeへ遷移できる
		return true;
	}
	return false;
}
