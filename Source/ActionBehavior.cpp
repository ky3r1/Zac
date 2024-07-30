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
		// アニメーション再生
		GetActor()->GetModel()->PlayAnimation(0, true);
		step++;
		break;
	case 1:

		// アニメーションが終了しているとき
		if (!GetActor()->GetModel()->IsPlayAnimation())
		{
			step = 0;
			// 攻撃成功を返す
			return ActionBase::State::Complete;
		}
		break;
	}
	// 攻撃中を返す
	return ActionBase::State::Run;
}

ActionBase::State SkillAction::Run(float elapsedTime)
{
	switch (step)
	{
	case 0:
		// アニメーション再生
		GetActor()->GetModel()->PlayAnimation(0, true);
		step++;
	case 1:
		// アニメーションが終了しているとき
		if (!GetActor()->GetModel()->IsPlayAnimation())
		{
			step = 0;
			// 攻撃成功を返す
			return ActionBase::State::Complete;
		}
		break;
	}
	// スキル中を返す
	return ActionBase::State::Run;
}

ActionBase::State WanderAction::Run(float elapsedTime)
{
	switch (step)
	{
	case 0:
		// 徘徊モーション設定
		GetActor()->GetModel()->PlayAnimation(0, true);
		step++;
		break;
	case 1:
		if (GetActor()->GetComponent<VsCollision>()->SphereVsSphere(ActorType::Player, nullptr))
		{
			step = 0;
			// 徘徊成功を返す
			return ActionBase::State::Complete;
		}

		// 目的地点へ移動
		GetActor()->GetComponent<Movement>()->MoveTarget(ActorManager::Instance().GetActor("Player")->GetPosition(), elapsedTime);

		// プレイヤー索敵成功したら
		if (Collision::SphereInPoint(GetActor()->GetPosition(), GetActor()->AddComponent<Enemy>()->GetSearchRange(), ActorManager::Instance().GetActor("Player")->GetPosition()))
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

ActionBase::State PursuitAction::Run(float elapsedTime)
{
	static float runtimer = rand() % 20 * 60.0f;
	switch (step)
	{
	case 0:
		runtimer = rand() % 20 * 60.0f;
		// 徘徊モーション設定
		GetActor()->GetModel()->PlayAnimation(0, true);
		step++;
		break;
	case 1:
		if (GetActor()->GetComponent<VsCollision>()->SphereVsSphere(ActorType::Player, nullptr))
		{
			step = 0;
			// 徘徊成功を返す
			return ActionBase::State::Complete;
		}
		DirectX::XMFLOAT3 rndp = {
			rand() % 50 - 25 + static_cast<float>(rand() % 1000) / 10000,
			rand() % 50 - 25 + static_cast<float>(rand() % 1000) / 10000,
			rand() % 50 - 25 + static_cast<float>(rand() % 1000) / 10000 };

		// 目的地点へ移動
		GetActor()->GetComponent<Movement>()->MoveTarget(rndp, elapsedTime);

		// プレイヤー索敵成功したら
		if (Collision::SphereInPoint(GetActor()->GetPosition(), GetActor()->AddComponent<Enemy>()->GetSearchRange(), ActorManager::Instance().GetActor("Player")->GetPosition()))
		{
			step = 0;
			// 追跡成功を返す
			return ActionBase::State::Complete;
		}
		else if(runtimer<0)
		{
			step = 0;
			// 追跡失敗を返す
			return ActionBase::State::Failed;
		}
		runtimer--;
		break;
	}
	// 実行中
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
		// 待機時間が過ぎた時
		if (runtimer <= 0.0f)
		{
			DirectX::XMFLOAT3 rndp = {
			rand() % 50 - 25 + static_cast<float>(rand() % 1000) / 10000,
			rand() % 50 - 25 + static_cast<float>(rand() % 1000) / 10000,
			rand() % 50 - 25 + static_cast<float>(rand() % 1000) / 10000 };
			// 目的地点へ移動
			GetActor()->GetComponent<Movement>()->MoveTarget(rndp, elapsedTime);
			step = 0;
			return ActionBase::State::Complete;
		}

		// プレイヤーを見つけた時
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
		// 目標地点をプレイヤーと正反対のベクトル×5の位置に指定
		DirectX::XMFLOAT3 tp=Mathf::Distance3(ActorManager::Instance().GetActor("Player")->GetPosition(), GetActor()->GetPosition());
		tp.x *= -5;
        tp.y *= -5;
        tp.z *= -5;
		GetActor()->GetModel()->PlayAnimation(0, true);
		step++;
		break;
	case 1:

		targetPosition = tp;
		// 目的地点へ移動
		GetActor()->GetComponent<Movement>()->MoveTarget(targetPosition, elapsedTime);

		//DirectX::XMFLOAT3 position = owner->GetPosition();
		//targetPosition = owner->GetTargetPosition();

		//float vx = targetPosition.x - position.x;
		//float vz = targetPosition.z - position.z;
		//float distSq = vx * vx + vz * vz;


		// 目的地へ着いた
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
