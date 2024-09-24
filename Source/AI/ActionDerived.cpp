#include "ActionDerived.h"
#include "Enemy.h"
//#include "Player.h"
#include "Mathf.h"
#include "Actor.h"
#include "Movement.h"


// 攻撃行動
ActionBase::State NormalAction::Run(float elapsedTime)
{
	switch (step)
	{
	case 0:
		// 目標地点をプレイヤー位置に設定
		owner->SetTargetPosition(ActorManager::Instance().GetPlayer()->GetPosition());
		// アニメーション再生
		owner->GetActor()->GetModel()->PlayAnimation(Enemy::Attack01, false);
		step++;
		break;
	case 1:

		// アニメーションが終了しているとき
		if (!owner->GetActor()->GetModel()->IsPlayAnimation())
		{
			owner->SetAttackFlag(false);
			ActorManager::Instance().GetPlayer()->GetComponent<Character>()->TakeDamage(1.0f);
			step = 0;
			// 攻撃成功を返す
			return ActionBase::State::Complete;
		}
		break;
	}
	// スキル中を返す
	return ActionBase::State::Run;
}
// スキル攻撃行動
ActionBase::State SkillAction::Run(float elapsedTime)
{
	switch (step)
	{
		case 0:
			// 目標地点をプレイヤー位置に設定
			owner->SetTargetPosition(ActorManager::Instance().GetPlayer()->GetPosition());
			// アニメーション再生
			owner->GetActor()->GetModel()->PlayAnimation(Enemy::Attack02, false);
			step++;
		case 1:
			// アニメーションが終了しているとき
			if (!owner->GetActor()->GetModel()->IsPlayAnimation())
			{
				owner->SetAttackFlag(false);
				owner->ShotObject();
				step = 0;
				// 攻撃成功を返す
				return ActionBase::State::Complete;
			}
			break;
	}
	// スキル中を返す
	return ActionBase::State::Run;
}

// 徘徊行動
ActionBase::State WanderAction::Run(float elapsedTime)
{
	switch (step)
	{
	case 0:
		// 徘徊モーション設定
		owner->GetActor()->GetModel()->PlayAnimation(Enemy::WalkFront, true);
        // 目標地点設定
        owner->SetTargetPosition({ static_cast<float>(rand() % 400 - 400 * 0.5f), owner->GetActor()->GetPosition().y, static_cast<float>(rand() % 400 - 400 * 0.5f) });
		step++;
		break;
	case 1:
		// 目的地点までのXZ平面での距離判定
		DirectX::XMFLOAT3 position = owner->GetActor()->GetPosition();
		DirectX::XMFLOAT3 targetPosition = owner->GetTargetPosition();
		float vx = targetPosition.x - position.x;
		float vz = targetPosition.z - position.z;
		float distSq = vx * vx + vz * vz;

		// 目的地へ着いた
		float radius = owner->GetActor()->GetRadius();
		if (distSq < radius * radius)
		{
			step = 0;
			// 徘徊成功を返す
			return ActionBase::State::Complete;
		}

		// 目的地点へ移動
		owner->GetActor()->GetComponent<Movement>()->MoveTarget(owner->GetTargetPosition(), elapsedTime);

		// プレイヤー索敵成功したら
		if (owner->Search( ActorManager::Instance().GetPlayer()->GetPosition()))
		{
			step = 0;
			// 徘徊成功を返す
			return ActionBase::State::Complete;
		}
		break;
	}
	// 実行中
	return ActionBase::State::Run;
}

// 追跡行動
ActionBase::State PursuitAction::Run(float elapsedTime)
{
	float runTimer = owner->GetRunTimer();
	switch (step)
	{
	case 0:
		// 目標地点をプレイヤー位置に設定
		owner->SetTargetPosition(ActorManager::Instance().GetPlayer()->GetPosition());
		owner->SetRunTimer(Mathf::RandomRange(3.0f, 5.0f));
		owner->GetActor()->GetModel()->PlayAnimation(Enemy::Run, true);
		step++;
		break;
	case 1:
		runTimer -= elapsedTime;
		// タイマー更新
		owner->SetRunTimer(runTimer);
		// 目標地点をプレイヤー位置に設定
		owner->SetTargetPosition(ActorManager::Instance().GetPlayer()->GetPosition());
		// 目的地点へ移動
		owner->GetActor()->GetComponent<Movement>()->MoveTarget(owner->GetTargetPosition(), elapsedTime);

		// 遠距離攻撃範囲にいるとき
		if (owner->GetAttackFlag() && Collision::SphereInPoint(owner->GetActor()->GetPosition(), owner->GetLongAttackRange(), ActorManager::Instance().GetPlayer()->GetPosition()))
		{
			step = 0;
			// 追跡成功を返す
			return ActionBase::State::Complete;
		}
		// 行動時間が過ぎた時
		if (runTimer <= 0.0f)
		{
			step = 0;
			// 追跡失敗を返す
			return ActionBase::State::Failed;
		}
		break;
	}
	return ActionBase::State::Run;
}

// 待機行動
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
		// タイマー更新
		owner->SetRunTimer(runTimer);

		// 待機時間が過ぎた時
		if (runTimer <= 0.0f)
		{
			owner->SetTargetPosition({ static_cast<float>(rand() % 400 - 400*0.5f), owner->GetActor()->GetPosition().y, static_cast<float>(rand() % 400 - 400 * 0.5f) });
			step = 0;
			return ActionBase::State::Complete;
		}

		// プレイヤーを見つけた時
		if (owner->Search(ActorManager::Instance().GetPlayer()->GetPosition()))
		{
			step = 0;
			return ActionBase::State::Complete;
		}
		break;
	}
	return ActionBase::State::Run;
}

// 逃走行動
ActionBase::State LeaveAction::Run(float elapsedTime)
{
	DirectX::XMFLOAT3 targetPosition;
	switch (step)
	{
	case 0:
		// 目標地点をプレイヤーと正反対のベクトル×5の位置に指定

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
		// 目的地点へ移動
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
// 回復行動
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